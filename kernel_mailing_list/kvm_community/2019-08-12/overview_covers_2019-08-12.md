

#### [PATCH 0/2] powerpc/xive: Fix race condition leading to host crashes
##### From: Paul Mackerras <paulus@ozlabs.org>

```c

This series fixes a race condition that has been observed in testing
on POWER9 machines running KVM guests.  An interrupt being freed by
free_irq() can have an instance present in a XIVE interrupt queue,
which can then be presented to the generic interrupt code after the
data structures for it have been freed, leading to a variety of
crashes and hangs.

This series is based on current upstream kernel source plus Cédric Le
Goater's patch "KVM: PPC: Book3S HV: XIVE: Free escalation interrupts
before disabling the VP", which is a pre-requisite for this series.
As it touches both KVM and generic PPC code, this series will probably
go in via Michael Ellerman's powerpc tree.

Paul.

 arch/powerpc/include/asm/xive.h         |  8 +++
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 23 ++++++---
 arch/powerpc/kvm/book3s_xive.c          | 31 ++++++++++++
 arch/powerpc/sysdev/xive/common.c       | 87 ++++++++++++++++++++++++---------
 4 files changed, 119 insertions(+), 30 deletions(-)
```
#### [RFC][PATCH v12 0/2] mm: Support for page reporting
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c

This patch series proposes an efficient mechanism for reporting free memory
from a guest to its hypervisor. It especially enables guests with no page cache
(e.g., nvdimm, virtio-pmem) or with small page caches (e.g., ram > disk) to
rapidly hand back free memory to the hypervisor.
This approach has a minimal impact on the existing core-mm infrastructure.

This approach tracks all freed pages of the order MAX_ORDER - 2 in bitmaps.
A new hook after buddy merging is used to set the bits in the bitmap for a freed 
page. Each set bit is cleared after they are processed/checked for
re-allocation.
Bitmaps are stored on a per-zone basis and are protected by the zone lock. A
workqueue asynchronously processes the bitmaps as soon as a pre-defined memory
threshold is met, trying to isolate and report pages that are still free.
The isolated pages are stored in a scatterlist and are reported via
virtio-balloon, which is responsible for sending batched pages to the
hypervisor. Once the hypervisor processed the reporting request, the isolated
pages are returned back to the buddy.
The thershold which defines the number of pages which will be isolated and
reported to the hypervisor at a time is currently hardcoded to 16 in the guest.

Benefit analysis:
Number of 5 GB guests (each touching 4 to 5 GB memory) that can be launched on a
15 GB single NUMA system without using swap space in the host.

	    Guest kernel-->	Unmodified		with v12 page reporting
	Number of guests-->	    2				7

Conclusion: In a page-reporting enabled kernel, the guest is able to report
most of its unused memory back to the host. Due to this on the same host, I was
able to launch 7 guests without touching any swap compared to 2 which were
launched with an unmodified kernel.

Performance Analysis:
In order to measure the performance impact of this patch-series over an
unmodified kernel, I am using will-it-scale/page_fault1 on a 30 GB, 24 vcpus
single NUMA guest which is affined to a single node in the host. Over several
runs, I observed that with this patch-series there is a degradation of around
1-3% for certain cases. This degradation could be a result of page-zeroing
overhead which comes with every page-fault in the guest.
I also tried this test on a 2 NUMA node host running page reporting
enabled 60GB guest also having 2 NUMA nodes and 24 vcpus. I observed a similar
degradation of around 1-3% in most of the cases.
For certain cases, the variability even with an unmodified kernel was around
4-6% with every fresh boot. I will continue to investigate this further to find
the reason behind it.

Ongoing work-items:
* I have a working prototype for supporting memory hotplug/hotremove with page
  reporting. However, it still requires more testing and fixes specifically on
  the hotremove side.
  Right now, for any memory hotplug or hotremove request bitmap or its
  respective fields are not changed. Hence, memory added via hotplug is not
  tracked in the bitmap. Similarly, removed memory is not reported to the
  hypervisor by using an online memory check. 
* I will also have to look into the details about how to handle page poisoning
  scenarios and test with directly assigned devices.


Changes from v11:
https://lkml.org/lkml/2019/7/10/742
* Moved the fields required to manage bitmap of free pages to 'struct zone'.
* Replaced the list which was used to hold and report the free pages with
  scatterlist.
* Tried to fix the anti-kernel patterns and improve overall code quality.
* Fixed a few bugs in the code which were reported in the last posting.
* Moved to use MADV_DONTNEED from MADV_FREE.
* Replaced page hinting in favor of page reporting.
* Addressed other comments which I received in the last posting.	


Changes from v10:
https://lkml.org/lkml/2019/6/3/943
* Added logic to take care of multiple NUMA nodes scenarios.
* Simplified the logic for reporting isolated pages to the host. (Eg. replaced
  dynamically allocated arrays with static ones, introduced wait event instead
  of the loop in order to wait for a response from the host)
* Added a mutex to prevent race condition when page reporting is enabled by
  multiple drivers.
* Simplified the logic responsible for decrementing free page counter for each
  zone.
* Simplified code structuring/naming.
---

Nitesh Narayan Lal (2):
  mm: page_reporting: core infrastructure
  virtio-balloon: interface to support free page reporting

 drivers/virtio/Kconfig              |   1 +
 drivers/virtio/virtio_balloon.c     |  64 +++++-
 include/linux/mmzone.h              |  11 +
 include/linux/page_reporting.h      |  63 ++++++
 include/uapi/linux/virtio_balloon.h |   1 +
 mm/Kconfig                          |   6 +
 mm/Makefile                         |   1 +
 mm/page_alloc.c                     |  42 +++-
 mm/page_reporting.c                 | 332 ++++++++++++++++++++++++++++
 9 files changed, 513 insertions(+), 8 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c

--
```
#### [PATCH v5 0/6] mm / virtio: Provide support for unused page
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c

This series provides an asynchronous means of reporting to a hypervisor
that a guest page is no longer in use and can have the data associated
with it dropped. To do this I have implemented functionality that allows
for what I am referring to as unused page reporting

The functionality for this is fairly simple. When enabled it will allocate
statistics to track the number of reported pages in a given free area.
When the number of free pages exceeds this value plus a high water value,
currently 32, it will begin performing page reporting which consists of
pulling pages off of free list and placing them into a scatter list. The
scatterlist is then given to the page reporting device and it will perform
the required action to make the pages "reported", in the case of
virtio-balloon this results in the pages being madvised as MADV_DONTNEED
and as such they are forced out of the guest. After this they are placed
back on the free list, and an additional bit is added if they are not
merged indicating that they are a reported buddy page instead of a
standard buddy page. The cycle then repeats with additional non-reported
pages being pulled until the free areas all consist of reported pages.

I am leaving a number of things hard-coded such as limiting the lowest
order processed to PAGEBLOCK_ORDER, and have left it up to the guest to
determine what the limit is on how many pages it wants to allocate to
process the hints. The upper limit for this is based on the size of the
queue used to store the scattergather list.

My primary testing has just been to verify the memory is being freed after
allocation by running memhog 40g on a 40g guest and watching the total
free memory via /proc/meminfo on the host. With this I have verified most
of the memory is freed after each iteration. As far as performance I have
been mainly focusing on the will-it-scale/page_fault1 test running with
16 vcpus. I have modified it to use Transparent Huge Pages. With this I
see almost no difference, -0.08%, with the patches applied and the feature
disabled. I see a regression of -0.86% with the feature enabled, but the
madvise disabled in the hypervisor due to a device being assigned. With
the feature fully enabled I see a regression of -3.27% versus the baseline
without these patches applied. In my testing I found that most of the
overhead was due to the page zeroing that comes as a result of the pages
having to be faulted back into the guest.

One side effect of these patches is that the guest becomes much more
resilient in terms of NUMA locality. With the pages being freed and then
reallocated when used it allows for the pages to be much closer to the
active thread, and as a result there can be situations where this patch
set will out-perform the stock kernel when the guest memory is not local
to the guest vCPUs. To avoid that in my testing I set the affinity of all
the vCPUs and QEMU instance to the same node.

Changes from the RFC:
https://lore.kernel.org/lkml/20190530215223.13974.22445.stgit@localhost.localdomain/
Moved aeration requested flag out of aerator and into zone->flags.
Moved boundary out of free_area and into local variables for aeration.
Moved aeration cycle out of interrupt and into workqueue.
Left nr_free as total pages instead of splitting it between raw and aerated.
Combined size and physical address values in virtio ring into one 64b value.

Changes from v1:
https://lore.kernel.org/lkml/20190619222922.1231.27432.stgit@localhost.localdomain/
Dropped "waste page treatment" in favor of "page hinting"
Renamed files and functions from "aeration" to "page_hinting"
Moved from page->lru list to scatterlist
Replaced wait on refcnt in shutdown with RCU and cancel_delayed_work_sync
Virtio now uses scatterlist directly instead of intermediate array
Moved stats out of free_area, now in separate area and pointed to from zone
Merged patch 5 into patch 4 to improve review-ability
Updated various code comments throughout

Changes from v2:
https://lore.kernel.org/lkml/20190724165158.6685.87228.stgit@localhost.localdomain/
Dropped "page hinting" in favor of "page reporting"
Renamed files from "hinting" to "reporting"
Replaced "Hinted" page type with "Reported" page flag
Added support for page poisoning while hinting is active
Add QEMU patch that implements PAGE_POISON feature

Changes from v3:
https://lore.kernel.org/lkml/20190801222158.22190.96964.stgit@localhost.localdomain/
Added mutex lock around page reporting startup and shutdown
Fixed reference to "page aeration" in patch 2
Split page reporting function bit out into separate QEMU patch
Limited capacity of scatterlist to vq size - 1 instead of vq size
Added exception handling for case of virtio descriptor allocation failure

Changes from v4:
https://lore.kernel.org/lkml/20190807224037.6891.53512.stgit@localhost.localdomain/
Replaced spin_(un)lock with spin_(un)lock_irq in page_reporting_cycle()
Dropped if/continue for ternary operator in page_reporting_process()
Added checks for isolate and cma types to for_each_reporting_migratetype_order
Added virtio-dev, Michal Hocko, and Oscar Salvador to to:/cc:
Rebased on latest linux-next and QEMU git trees
---

Alexander Duyck (6):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Move set/get_pcppage_migratetype to mmzone.h
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Reported pages
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing unused page reports to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   84 +++++++++-
 include/linux/mmzone.h              |  116 ++++++++-----
 include/linux/page-flags.h          |   11 +
 include/linux/page_reporting.h      |  138 ++++++++++++++++
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |    5 +
 mm/Makefile                         |    1 
 mm/internal.h                       |   18 ++
 mm/memory_hotplug.c                 |    1 
 mm/page_alloc.c                     |  238 ++++++++++++++++++++-------
 mm/page_reporting.c                 |  308 +++++++++++++++++++++++++++++++++++
 mm/shuffle.c                        |   24 ---
 mm/shuffle.h                        |   32 ++++
 14 files changed, 839 insertions(+), 139 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c

--
```
