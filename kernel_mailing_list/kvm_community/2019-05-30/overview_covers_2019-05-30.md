

#### [PATCH v3 0/3] KVM: Yield to IPI target if necessary
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

The idea is from Xen, when sending a call-function IPI-many to vCPUs, 
yield if any of the IPI target vCPUs was preempted. 17% performance 
increasement of ebizzy benchmark can be observed in an over-subscribe 
environment. (w/ kvm-pv-tlb disabled, testing TLB flush call-function 
IPI-many since call-function is not easy to be trigged by userspace 
workload).

v2 -> v3:
 * add bounds-check on dest_id

v1 -> v2:
 * check map is not NULL
 * check map->phys_map[dest_id] is not NULL
 * make kvm_sched_yield static
 * change dest_id to unsinged long

Wanpeng Li (3):
  KVM: X86: Yield to IPI target if necessary
  KVM: X86: Implement PV sched yield hypercall
  KVM: X86: Expose PV_SCHED_YIELD CPUID feature bit to guest

 Documentation/virtual/kvm/cpuid.txt      |  4 ++++
 Documentation/virtual/kvm/hypercalls.txt | 11 +++++++++++
 arch/x86/include/uapi/asm/kvm_para.h     |  1 +
 arch/x86/kernel/kvm.c                    | 21 +++++++++++++++++++++
 arch/x86/kvm/cpuid.c                     |  3 ++-
 arch/x86/kvm/x86.c                       | 26 ++++++++++++++++++++++++++
 include/uapi/linux/kvm_para.h            |  1 +
 7 files changed, 66 insertions(+), 1 deletion(-)
```
#### [PATCHv5 0/3] vfio/mdev: Improve vfio/mdev core module
##### From: Parav Pandit <parav@mellanox.com>

```c

As we would like to use mdev subsystem for wider use case as
discussed in [1], [2] apart from an offline discussion.
This use case is also discussed with wider forum in [4] in track
'Lightweight NIC HW functions for container offload use cases'.

This series is prep-work and improves vfio/mdev module in following ways.

Patch-1 Improves the mdev create/remove sequence to match Linux
bus, device model
Patch-2 Avoid recreating remove file on stale device to eliminate
call trace
Patch-3 Fix race conditions of create/remove with parent removal.
This is improved version than using srcu as srcu can take seconds
to minutes.

This series is tested using
(a) mtty with VM using vfio_mdev driver for positive tests and device
removal while device in use by VM using vfio_mdev driver.

(b) mlx5 core driver using RFC patches [3] and internal patches.
Internal patches are large and cannot be combined with this prep-work
patches. It will posted once prep-work completes.

[1] https://www.spinics.net/lists/netdev/msg556978.html
[2] https://lkml.org/lkml/2019/3/7/696
[3] https://lkml.org/lkml/2019/3/8/819
[4] https://netdevconf.org/0x13/session.html?workshop-hardware-offload
---
Changelog:
---
v4->v5:
 - Addressed comments from Alex Williamson
 - Added comment around mdev_device_remove_common()
 - Added lockdep assert to catch any missing lock
 - Corrected 'system' to 'sequence' in 2nd patch commit log
 - Refactored mdev_device_remove_cb() to remove unused parent
 - Added Cornelia's Reviewed-by signature to already reviewed patches 1, 2.
v3->v4:
 - Addressed comments from Cornelia for unbalanced mutex_unlock
 - Correct typo of subsquent to subsequent in patch-1 commit log
 - Instead of using refcount and completion, using rwsem to synchronize
   between mdev creation/deletion and parent unregistration
v2->v3:
 - Addressed comment from Cornelia
 - Corrected several errors in commit log, updated commit log
 - Dropped already merged 7 patches
v1->v2:
 - Addressed comments from Alex
 - Rebased
 - Inserted the device checking loop in Patch-6 as original code
 - Added patch 7 to 10
 - Added fixes for race condition in create/remove with parent removal
   Patch-10 uses simplified refcount and completion, instead of srcu
   which might take seconds to minutes on busy system.
 - Added fix for device create/remove sequence to match
   Linux device, bus model
v0->v1:
 - Dropped device placement on bus sequence patch for this series
 - Addressed below comments from Alex, Kirti, Maxim.
 - Added Review-by tag for already reviewed patches.
 - Dropped incorrect patch of put_device().
 - Corrected Fixes commit tag for sysfs remove sequence fix
 - Split last 8th patch to smaller refactor and fixes patch
 - Following coding style commenting format
 - Fixed accidental delete of mutex_lock in mdev_unregister_device
 - Renamed remove helped to mdev_device_remove_common().
 - Rebased for uuid/guid change

Parav Pandit (3):
  vfio/mdev: Improve the create/remove sequence
  vfio/mdev: Avoid creating sysfs remove file on stale device removal
  vfio/mdev: Synchronize device create/remove with parent removal

 drivers/vfio/mdev/mdev_core.c    | 124 ++++++++++++++-----------------
 drivers/vfio/mdev/mdev_private.h |   4 +-
 drivers/vfio/mdev/mdev_sysfs.c   |   6 +-
 3 files changed, 61 insertions(+), 73 deletions(-)
```
#### [PATCH 0/2] scsi: add support for request batching
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

This allows a list of requests to be issued, with the LLD only writing
the hardware doorbell when necessary, after the last request was prepared.
This is more efficient if we have lists of requests to issue, particularly
on virtualized hardware, where writing the doorbell is more expensive than
on real hardware.

This applies to any HBA, either singlequeue or multiqueue; the second
patch implements it for virtio-scsi.

Paolo

Paolo Bonzini (2):
  scsi_host: add support for request batching
  virtio_scsi: implement request batching

 drivers/scsi/scsi_lib.c    | 37 ++++++++++++++++++++++---
 drivers/scsi/virtio_scsi.c | 55 +++++++++++++++++++++++++++-----------
 include/scsi/scsi_cmnd.h   |  1 +
 include/scsi/scsi_host.h   | 16 +++++++++--
 4 files changed, 89 insertions(+), 20 deletions(-)
```
#### [RFC PATCH 00/11] mm / virtio: Provide support for paravirtual
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c

This series provides an asynchronous means of hinting to a hypervisor
that a guest page is no longer in use and can have the data associated
with it dropped. To do this I have implemented functionality that allows
for what I am referring to as "waste page treatment".

I have based many of the terms and functionality off of waste water
treatment, the idea for the similarity occured to me after I had reached
the point of referring to the hints as "bubbles", as the hints used the
same approach as the balloon functionality but would disappear if they
were touched, as a result I started to think of the virtio device as an
aerator. The general idea with all of this is that the guest should be
treating the unused pages so that when they end up heading "downstream"
to either another guest, or back at the host they will not need to be
written to swap.

So for a bit of background for the treatment process, it is based on a
sequencing batch reactor (SBR)[1]. The treatment process itself has five
stages. The first stage is the fill, with this we take the raw pages and
add them to the reactor. The second stage is react, in this stage we hand
the pages off to the Virtio Balloon driver to have hints attached to them
and for those hints to be sent to the hypervisor. The third stage is
settle, in this stage we are waiting for the hypervisor to process the
pages, and we should receive an interrupt when it is completed. The fourth
stage is to decant, or drain the reactor of pages. Finally we have the
idle stage which we will go into if the reference count for the reactor
gets down to 0 after a drain, or if a fill operation fails to obtain any
pages and the reference count has hit 0. Otherwise we return to the first
state and start the cycle over again.

This patch set is still far more intrusive then I would really like for
what it has to do. Currently I am splitting the nr_free_pages into two
values and having to add a pointer and an index to track where we area in
the treatment process for a given free_area. I'm also not sure I have
covered all possible corner cases where pages can get into the free_area
or move from one migratetype to another.

Also I am still leaving a number of things hard-coded such as limiting the
lowest order processed to PAGEBLOCK_ORDER, and have left it up to the
guest to determine what size of reactor it wants to allocate to process
the hints.

Another consideration I am still debating is if I really want to process
the aerator_cycle() function in interrupt context or if I should have it
running in a thread somewhere else.

[1]: https://en.wikipedia.org/wiki/Sequencing_batch_reactor
---

Alexander Duyck (11):
      mm: Move MAX_ORDER definition closer to pageblock_order
      mm: Adjust shuffle code to allow for future coalescing
      mm: Add support for Treated Buddy pages
      mm: Split nr_free into nr_free_raw and nr_free_treated
      mm: Propogate Treated bit when splitting
      mm: Add membrane to free area to use as divider between treated and raw pages
      mm: Add support for acquiring first free "raw" or "untreated" page in zone
      mm: Add support for creating memory aeration
      mm: Count isolated pages as "treated"
      virtio-balloon: Add support for aerating memory via bubble hinting
      mm: Add free page notification hook


 arch/x86/include/asm/page.h         |   11 +
 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   89 ++++++++++
 include/linux/gfp.h                 |   10 +
 include/linux/memory_aeration.h     |   54 ++++++
 include/linux/mmzone.h              |  100 +++++++++--
 include/linux/page-flags.h          |   32 +++
 include/linux/pageblock-flags.h     |    8 +
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |    5 +
 mm/Makefile                         |    1 
 mm/aeration.c                       |  324 +++++++++++++++++++++++++++++++++++
 mm/compaction.c                     |    4 
 mm/page_alloc.c                     |  220 ++++++++++++++++++++----
 mm/shuffle.c                        |   24 ---
 mm/shuffle.h                        |   35 ++++
 mm/vmstat.c                         |    5 -
 17 files changed, 838 insertions(+), 86 deletions(-)
 create mode 100644 include/linux/memory_aeration.h
 create mode 100644 mm/aeration.c

--
```
