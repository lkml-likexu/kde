

#### [PATCH v4 0/8] vfio/mdev: IOMMU aware mediated device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c

Hi,

The Mediate Device is a framework for fine-grained physical device
sharing across the isolated domains. Currently the mdev framework
is designed to be independent of the platform IOMMU support. As the
result, the DMA isolation relies on the mdev parent device in a
vendor specific way.

There are several cases where a mediated device could be protected
and isolated by the platform IOMMU. For example, Intel vt-d rev3.0
[1] introduces a new translation mode called 'scalable mode', which
enables PASID-granular translations. The vt-d scalable mode is the
key ingredient for Scalable I/O Virtualization [2] [3] which allows
sharing a device in minimal possible granularity (ADI - Assignable
Device Interface).

A mediated device backed by an ADI could be protected and isolated
by the IOMMU since 1) the parent device supports tagging an unique
PASID to all DMA traffic out of the mediated device; and 2) the DMA
translation unit (IOMMU) supports the PASID granular translation.
We can apply IOMMU protection and isolation to this kind of devices
just as what we are doing with an assignable PCI device.

In order to distinguish the IOMMU-capable mediated devices from those
which still need to rely on parent devices, this patch set adds two
new members in struct mdev_device.

* iommu_device
  - This, if set, indicates that the mediated device could
    be fully isolated and protected by IOMMU via attaching
    an iommu domain to this device. If empty, it indicates
    using vendor defined isolation.

* iommu_domain
  - This is a place holder for an iommu domain. A domain
    could be store here for later use once it has been
    attached to the iommu_device of this mdev.

Below helpers are added to set and get above iommu device
and iommu domain pointers in mdev core implementation.

* mdev_set/get_iommu_device(dev, iommu_device)
  - Set or get the iommu device which represents this mdev
    in IOMMU's device scope. Drivers don't need to set the
    iommu device if it uses vendor defined isolation.

* mdev_set/get_iommu_domain(domain)
  - A iommu domain which has been attached to the iommu
    device in order to protect and isolate the mediated
    device will be kept in the mdev data structure and
    could be retrieved later.

The mdev parent device driver could opt-in that the mdev could be
fully isolated and protected by the IOMMU when the mdev is being
created by invoking mdev_set_iommu_device() in its @create().

In the vfio_iommu_type1_attach_group(), a domain allocated through
iommu_domain_alloc() will be attached to the mdev iommu device if
an iommu device has been set. Otherwise, the dummy external domain
will be used and all the DMA isolation and protection are routed to
parent driver as the result.

On IOMMU side, a basic requirement is allowing to attach multiple
domains to a PCI device if the device advertises the capability
and the IOMMU hardware supports finer granularity translations than
the normal PCI Source ID based translation.

As the result, a PCI device could work in two modes: normal mode
and auxiliary mode. In the normal mode, a pci device could be
isolated in the Source ID granularity; the pci device itself could
be assigned to a user application by attaching a single domain
to it. In the auxiliary mode, a pci device could be isolated in
finer granularity, hence subsets of the device could be assigned
to different user level application by attaching a different domain
to each subset.

The device driver is able to switch between above two modes with
below interfaces:

* iommu_get_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_CAPABILITY)
  - Represents the ability of supporting multiple domains
    per device.

* iommu_set_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_ENABLE)
  - Enable the multiple domains capability for the device
    referenced by @dev.

* iommu_set_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_DISABLE)
  - Disable the multiple domains capability for the device
    referenced by @dev.

* iommu_domain_get_attr(domain, DOMAIN_ATTR_AUXD_ID)
  - Return ID used for finer-granularity DMA translation.

* iommu_attach_device_aux(domain, dev)
  - Attach a domain to the device in the auxiliary mode.

* iommu_detach_device_aux(domain, dev)
  - Detach the aux domain from device.

In order for the ease of discussion, sometimes we call "a domain in
auxiliary mode' or simply 'an auxiliary domain' when a domain is
attached to a device for finer granularity translations. But we need
to keep in mind that this doesn't mean there is a differnt domain
type. A same domain could be bound to a device for Source ID based
translation, and bound to another device for finer granularity
translation at the same time.

This patch series extends both IOMMU and vfio components to support
mdev device passing through when it could be isolated and protected
by the IOMMU units. The first part of this series (PATCH 1/08~5/08)
adds the interfaces and implementation of the multiple domains per
device. The second part (PATCH 6/08~8/08) adds the iommu device
attribute to each mdev, determines isolation type according to the
existence of an iommu device when attaching group in vfio type1 iommu
module, and attaches the domain to iommu aware mediated devices.

This patch series depends on a patch set posted here [4] for discussion
which added scalable mode support in Intel IOMMU driver.

References:
[1] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[2] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[3] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[4] https://lkml.org/lkml/2018/11/5/136

Best regards,
Lu Baolu

Change log:
  v3->v4:
  - Use aux domain specific interfaces for domain attach and detach.
  - Rebase all patches to 4.20-rc1.

  v2->v3:
  - Remove domain type enum and use a pointer on mdev_device instead.
  - Add a generic interface for getting/setting per device iommu
    attributions. And use it for query aux domain capability, enable
    aux domain and disable aux domain purpose.
  - Reuse iommu_domain_get_attr() to retrieve the id in a aux domain.
  - We discussed the impact of the default domain implementation
    on reusing iommu_at(de)tach_device() interfaces. We agreed
    that reusing iommu_at(de)tach_device() interfaces is the right
    direction and we could tweak the code to remove the impact.
    https://www.spinics.net/lists/kvm/msg175285.html  
  - Removed the RFC tag since no objections received.
  - This patch has been submitted separately.
    https://www.spinics.net/lists/kvm/msg173936.html

  v1->v2:
  - Rewrite the patches with the concept of auxiliary domains.

Lu Baolu (8):
  iommu: Add APIs for multiple domains per device
  iommu/vt-d: Add multiple domains per device query
  iommu/vt-d: Enable/disable multiple domains per device
  iommu/vt-d: Attach/detach domains in auxiliary mode
  iommu/vt-d: Return ID associated with an auxiliary domain
  vfio/mdev: Add iommu place holders in mdev_device
  vfio/type1: Add domain at(de)taching group helpers
  vfio/type1: Handle different mdev isolation type

 drivers/iommu/intel-iommu.c      | 315 ++++++++++++++++++++++++++++---
 drivers/iommu/iommu.c            |  52 +++++
 drivers/vfio/mdev/mdev_core.c    |  36 ++++
 drivers/vfio/mdev/mdev_private.h |   2 +
 drivers/vfio/vfio_iommu_type1.c  | 162 ++++++++++++++--
 include/linux/intel-iommu.h      |  11 ++
 include/linux/iommu.h            |  52 +++++
 include/linux/mdev.h             |  23 +++
 8 files changed, 618 insertions(+), 35 deletions(-)
```
#### [PATCH 0/5] VSOCK: support mergeable rx buffer in vhost-vsock
##### From: jiangyiwen <jiangyiwen@huawei.com>

```c

Now vsock only support send/receive small packet, it can't achieve
high performance. As previous discussed with Jason Wang, I revisit the
idea of vhost-net about mergeable rx buffer and implement the mergeable
rx buffer in vhost-vsock, it can allow big packet to be scattered in
into different buffers and improve performance obviously.

I write a tool to test the vhost-vsock performance, mainly send big
packet(64K) included guest->Host and Host->Guest. The result as
follows:

Before performance:
              Single socket            Multiple sockets(Max Bandwidth)
Guest->Host   ~400MB/s                 ~480MB/s
Host->Guest   ~1450MB/s                ~1600MB/s

After performance:
              Single socket            Multiple sockets(Max Bandwidth)
Guest->Host   ~1700MB/s                ~2900MB/s
Host->Guest   ~1700MB/s                ~2900MB/s

From the test results, the performance is improved obviously, and guest
memory will not be wasted.
---

Yiwen Jiang (5):
  VSOCK: support fill mergeable rx buffer in guest
  VSOCK: support fill data to mergeable rx buffer in host
  VSOCK: support receive mergeable rx buffer in guest
  VSOCK: modify default rx buf size to improve performance
  VSOCK: batch sending rx buffer to increase bandwidth

 drivers/vhost/vsock.c                   | 135 +++++++++++++++++++++++------
 include/linux/virtio_vsock.h            |  15 +++-
 include/uapi/linux/virtio_vsock.h       |   5 ++
 net/vmw_vsock/virtio_transport.c        | 147 ++++++++++++++++++++++++++------
 net/vmw_vsock/virtio_transport_common.c |  59 +++++++++++--
 5 files changed, 300 insertions(+), 61 deletions(-)
```
#### [PATCH 0/4] Workaround for Cortex-A76 erratum 1165522
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c

Early Cortex-A76 suffer from an erratum that can result in invalid
TLBs when the CPU speculatively executes an AT instruction in the
middle of a guest world switch, while the guest virtual memory
configuration is in an inconsistent state.

We handle this issue by mandating the use of VHE and making sure that
the guest context is fully installed before switching HCR_EL2.TGE to
zero. This ensures that a speculated AT instruction is either executed
on the host context (TGE set) or the guest context (TGE clear), and
that there is no intermediate state.

Marc Zyngier (4):
  KVM: arm64: Rework detection of SVE, !VHE systems
  KVM: arm64: Allow implementations to be confined to using VHE
  arm64: KVM: Install stage-2 translation before enabling traps on VHE
  arm64: KVM: Implement workaround for Cortex-A76 erratum 1165522

 Documentation/arm64/silicon-errata.txt |  1 +
 arch/arm/include/asm/kvm_host.h        |  3 ++-
 arch/arm64/Kconfig                     | 12 ++++++++++++
 arch/arm64/include/asm/cpucaps.h       |  3 ++-
 arch/arm64/include/asm/kvm_host.h      | 14 ++++++++++----
 arch/arm64/include/asm/kvm_hyp.h       |  6 ++++++
 arch/arm64/kernel/cpu_errata.c         |  8 ++++++++
 arch/arm64/kvm/hyp/switch.c            | 16 +++++++++++++++-
 virt/kvm/arm/arm.c                     | 17 ++++++++++++-----
 9 files changed, 68 insertions(+), 12 deletions(-)
```
#### [RFC PATCH v4 00/13] ktask: multithread CPU-intensive kernel work
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c

Hi,

This version addresses some of the feedback from Andrew and Michal last year
and describes the plan for tackling the rest.  I'm posting now since I'll be
presenting ktask at Plumbers next week.

Andrew, you asked about parallelizing in more places[0].  This version adds
multithreading for VFIO page pinning, and there are more planned users listed
below.

Michal, you mentioned that ktask should be sensitive to CPU utilization[1].
ktask threads now run at the lowest priority on the system to avoid disturbing
busy CPUs (more details in patches 4 and 5).  Does this address your concern?
The plan to address your other comments is explained below.

Alex, any thoughts about the VFIO changes in patches 6-9?

Tejun and Lai, what do you think of patch 5?

And for everyone, questions and comments welcome.  Any suggestions for more
users?

         Thanks,
            Daniel

P.S.  This series is big to address the above feedback, but I can send patches
7 and 8 separately.


TODO
----

 - Implement cgroup-aware unbound workqueues in a separate series, picking up
   Bandan Das's effort from two years ago[2].  This should hopefully address
   Michal's comment about running ktask threads within the limits of the calling
   context[1].

 - Make ktask aware of power management.  A starting point is to disable the
   framework when energy-conscious cpufreq settings are enabled (e.g.
   powersave, conservative scaling governors).  This should address another
   comment from Michal about keeping CPUs under power constraints idle[1].

 - Add more users.  On my list:
    - __ib_umem_release in IB core, which Jason Gunthorpe mentioned[3]
    - XFS quotacheck and online repair, as suggested by Darrick Wong
    - vfs object teardown at umount time, as Andrew mentioned[0]
    - page freeing in munmap/exit, as Aaron Lu posted[4]
    - page freeing in shmem
   The last three will benefit from scaling zone->lock and lru_lock.

 - CPU hotplug support for ktask to adjust its per-CPU data and resource
   limits.

 - Check with IOMMU folks that iommu_map is safe for all IOMMU backend
   implementations (it is for x86).


Summary
-------

A single CPU can spend an excessive amount of time in the kernel operating
on large amounts of data.  Often these situations arise during initialization-
and destruction-related tasks, where the data involved scales with system size.
These long-running jobs can slow startup and shutdown of applications and the
system itself while extra CPUs sit idle.
    
To ensure that applications and the kernel continue to perform well as core
counts and memory sizes increase, harness these idle CPUs to complete such jobs
more quickly.
    
ktask is a generic framework for parallelizing CPU-intensive work in the
kernel.  The API is generic enough to add concurrency to many different kinds
of tasks--for example, zeroing a range of pages or evicting a list of
inodes--and aims to save its clients the trouble of splitting up the work,
choosing the number of threads to use, maintaining an efficient concurrency
level, starting these threads, and load balancing the work between them.

The first patch has more documentation, and the second patch has the interface.

Current users:
 1) VFIO page pinning before kvm guest startup (others hitting slowness too[5])
 2) deferred struct page initialization at boot time
 3) clearing gigantic pages
 4) fallocate for HugeTLB pages

This patchset is based on the 2018-10-30 head of mmotm/master.

Changelog:

v3 -> v4:
 - Added VFIO page pinning use case (Andrew's "more users" comment)
 - Made ktask helpers run at the lowest priority on the system (Michal's
   concern about sensitivity to CPU utilization)
 - ktask learned to undo part of a task on error (required for VFIO)
 - Changed mm->locked_vm to an atomic to improve performance for VFIO.  This can
   be split out into a smaller series (there wasn't time before posting this)
 - Removed /proc/sys/debug/ktask_max_threads (it was a debug-only thing)
 - Some minor improvements in the ktask code itself (shorter, cleaner, etc)
 - Updated Documentation to cover these changes

v2 -> v3:
 - Changed cpu to CPU in the ktask Documentation, as suggested by Randy Dunlap
 - Saved more boot time now that Pavel Tatashin's deferred struct page init
   patches are in mainline (https://lkml.org/lkml/2017/10/13/692).  New
   performance results in patch 7.
 - Added resource limits, per-node and system-wide, to maintain efficient
   concurrency levels (addresses a concern from my Plumbers talk)
 - ktask no longer allocates memory internally during a task so it can be used
   in sensitive contexts
 - Added the option to run work anywhere on the system rather than always
   confining it to a specific node
 - Updated Documentation patch with these changes and reworked motivation
   section

v1 -> v2:
 - Added deferred struct page initialization use case.
 - Explained the source of the performance improvement from parallelizing
   clear_gigantic_page (comment from Dave Hansen).
 - Fixed Documentation and build warnings from CONFIG_KTASK=n kernels.

ktask v3 RFC: lkml.kernel.org/r/20171205195220.28208-1-daniel.m.jordan@oracle.com

[0] https://lkml.kernel.org/r/20171205142300.67489b1a90605e1089c5aaa9@linux-foundation.org
[1] https://lkml.kernel.org/r/20171206143509.GG7515@dhcp22.suse.cz
[2] https://lkml.kernel.org/r/1458339291-4093-1-git-send-email-bsd@redhat.com
[3] https://lkml.kernel.org/r/20180928153922.GA17076@ziepe.ca
[4] https://lkml.kernel.org/r/1489568404-7817-1-git-send-email-aaron.lu@intel.com
[5] https://www.redhat.com/archives/vfio-users/2018-April/msg00020.html

Daniel Jordan (13):
  ktask: add documentation
  ktask: multithread CPU-intensive kernel work
  ktask: add undo support
  ktask: run helper threads at MAX_NICE
  workqueue, ktask: renice helper threads to prevent starvation
  vfio: parallelize vfio_pin_map_dma
  mm: change locked_vm's type from unsigned long to atomic_long_t
  vfio: remove unnecessary mmap_sem writer acquisition around locked_vm
  vfio: relieve mmap_sem reader cacheline bouncing by holding it longer
  mm: enlarge type of offset argument in mem_map_offset and mem_map_next
  mm: parallelize deferred struct page initialization within each node
  mm: parallelize clear_gigantic_page
  hugetlbfs: parallelize hugetlbfs_fallocate with ktask

 Documentation/core-api/index.rst    |   1 +
 Documentation/core-api/ktask.rst    | 213 +++++++++
 arch/powerpc/kvm/book3s_64_vio.c    |  15 +-
 arch/powerpc/mm/mmu_context_iommu.c |  16 +-
 drivers/fpga/dfl-afu-dma-region.c   |  16 +-
 drivers/vfio/vfio_iommu_spapr_tce.c |  14 +-
 drivers/vfio/vfio_iommu_type1.c     | 159 ++++---
 fs/hugetlbfs/inode.c                | 114 ++++-
 fs/proc/task_mmu.c                  |   2 +-
 include/linux/ktask.h               | 267 ++++++++++++
 include/linux/mm_types.h            |   2 +-
 include/linux/workqueue.h           |   5 +
 init/Kconfig                        |  11 +
 init/main.c                         |   2 +
 kernel/Makefile                     |   2 +-
 kernel/fork.c                       |   2 +-
 kernel/ktask.c                      | 646 ++++++++++++++++++++++++++++
 kernel/workqueue.c                  | 106 ++++-
 mm/debug.c                          |   3 +-
 mm/internal.h                       |   7 +-
 mm/memory.c                         |  32 +-
 mm/mlock.c                          |   4 +-
 mm/mmap.c                           |  18 +-
 mm/mremap.c                         |   6 +-
 mm/page_alloc.c                     |  91 +++-
 25 files changed, 1599 insertions(+), 155 deletions(-)
 create mode 100644 Documentation/core-api/ktask.rst
 create mode 100644 include/linux/ktask.h
 create mode 100644 kernel/ktask.c
```
