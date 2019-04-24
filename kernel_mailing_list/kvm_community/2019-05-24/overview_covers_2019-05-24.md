

#### [PATCH v2 0/3] KVM: x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and provide a capability to
enable it. With this capability enabled, a VM can use UMONITOR, UMWAIT
and TPAUSE instructions. If the instruction causes a delay, the amount
of time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay (the time to delay
relative to the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT
and TPAUSE cause an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf
This patch has a dependency on https://lkml.org/lkml/2019/1/16/909

Changelog:
v2:
	Separated from the series https://lkml.org/lkml/2018/7/10/160
	Add provide a capability to enable UMONITOR, UMWAIT and TPAUSE 
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (3):
  KVM: x86: add support for user wait instructions
  KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL
  KVM: vmx: handle vm-exit for UMWAIT and TPAUSE

 Documentation/virtual/kvm/api.txt | 12 ++++++
 arch/x86/include/asm/kvm_host.h   |  1 +
 arch/x86/include/asm/vmx.h        |  1 +
 arch/x86/include/uapi/asm/vmx.h   |  6 ++-
 arch/x86/kvm/cpuid.c              |  2 +-
 arch/x86/kvm/vmx/vmx.c            | 62 +++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h            |  1 +
 arch/x86/kvm/x86.c                |  8 ++++
 arch/x86/kvm/x86.h                |  5 +++
 include/uapi/linux/kvm.h          |  1 +
 10 files changed, 97 insertions(+), 2 deletions(-)
```
#### [PATCH net-next 0/6] vhost: accelerate metadata access
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series tries to access virtqueue metadata through kernel virtual
address instead of copy_user() friends since they had too much
overheads like checks, spec barriers or even hardware feature
toggling like SMAP. This is done through setup kernel address through
direct mapping and co-opreate VM management with MMU notifiers.

Test shows about 23% improvement on TX PPS. TCP_STREAM doesn't see
obvious improvement.

Thanks

Changes from RFC V3:
- rebase to net-next
- Tweak on the comments
Changes from RFC V2:
- switch to use direct mapping instead of vmap()
- switch to use spinlock + RCU to synchronize MMU notifier and vhost
  data/control path
- set dirty pages in the invalidation callbacks
- always use copy_to/from_users() friends for the archs that may need
  flush_dcache_pages()
- various minor fixes
Changes from V4:
- use invalidate_range() instead of invalidate_range_start()
- track dirty pages
Changes from V3:
- don't try to use vmap for file backed pages
- rebase to master
Changes from V2:
- fix buggy range overlapping check
- tear down MMU notifier during vhost ioctl to make sure
  invalidation request can read metadata userspace address and vq size
  without holding vq mutex.
Changes from V1:
- instead of pinning pages, use MMU notifier to invalidate vmaps
  and remap duing metadata prefetch
- fix build warning on MIPS

Jason Wang (6):
  vhost: generalize adding used elem
  vhost: fine grain userspace memory accessors
  vhost: rename vq_iotlb_prefetch() to vq_meta_prefetch()
  vhost: introduce helpers to get the size of metadata area
  vhost: factor out setting vring addr and num
  vhost: access vq metadata through kernel virtual address

 drivers/vhost/net.c   |   4 +-
 drivers/vhost/vhost.c | 850 ++++++++++++++++++++++++++++++++++++------
 drivers/vhost/vhost.h |  38 +-
 3 files changed, 766 insertions(+), 126 deletions(-)
```
#### [PATCH v2 0/2] x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it in kvm and provide a capability to
enable it. Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
QEMU use "-overcommit cpu-pm=on, a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The dependency KVM patch link:
https://lkml.org/lkml/2019/5/24/138

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v2:
	Separated from the series
	https://www.mail-archive.com/qemu-devel@nongnu.org/msg549526.html
	Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
	QEMU use "-overcommit cpu-pm=on"
	
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (2):
  x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
  target/i386: Add support for save/load IA32_UMWAIT_CONTROL MSR

 linux-headers/linux/kvm.h |  1 +
 target/i386/cpu.c         |  3 ++-
 target/i386/cpu.h         |  3 +++
 target/i386/kvm.c         | 28 ++++++++++++++++++++++++++++
 target/i386/machine.c     | 20 ++++++++++++++++++++
 5 files changed, 54 insertions(+), 1 deletion(-)
```
#### [PATCHv4 0/3] vfio/mdev: Improve vfio/mdev core module
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

 drivers/vfio/mdev/mdev_core.c    | 125 ++++++++++++++-----------------
 drivers/vfio/mdev/mdev_private.h |   4 +-
 drivers/vfio/mdev/mdev_sysfs.c   |   6 +-
 3 files changed, 62 insertions(+), 73 deletions(-)
```
