

#### [PATCH v3 00/12] KVM: s390: make use of the GIB
##### From: Michael Mueller <mimu@linux.ibm.com>

```c

The Guest Information Area (GIB) and its mechanics is part of
the AIV facility. It provides hardware support to process
Adapter Interruptions (AI) for pagable storage mode guests. 

Whenever a guest cannot process an AI because none of its
vcpus is running in SIE context, a GIB alert interruption is
sent to and handled by the host program to dispatch a vcpu of
the respective guest.

Eventually, the AI is handled by the guest.

v2->v3:
  patch 01/12: Fixes a resource dealocation issue upon
  	       unsuccessful exit from kvm_arch_init().
	       It is relevant for patch 11/12 as well. 
  patch 08/12: The function process_gib_alert_list() has
               been rewritten to reduce the number of GAL
	       interruptions on the host for many guest
	       scenarios.
  patch 10/12: The IAM is now never cleared before SIE entry.
               It will be cleared by millicode as soon the
	       first guest interruption is made pending and
	       not directly processed in SIE. The IAM gets
	       restored as soon a vm is idle, i.e. no vcpu
	       of that guest is in SIE context anymore.
  patch 11/12: now integrates with new patch 01/12
  patch 12/12: This patch is just experimental and shall not
               be part of the final series.

The first patch of series v2: "leave AIs in IPM of GISA
during vcpu_pre_run()" has been dropped.

All other patches are unchanged.

v1->v2:
  patch 01/12: New patch. Tt can go also standalone without the
  	       rest of the GIB series presented here but is a
	       requirement 
  patch 03/12: kvm_s390_gib_init() now has a return code
  patch 06/12: unlink_gib_alert_list() now uses cmpxchg() instead
    	       of atomic_xchg()
  patch 08/12: New patch. Foctors out __find_vcpu_for_floating_irq()
  patch 09/12: process_gib_alert_list() has been simplified
               the GISA clear/destroy cases have been removed
  patch 11/12: kvm_s390_gisa_clear/destroy() now clear the IAM
               and process the alert list directly
	       The IAM now gets restored in vcpu_post_run() only if
	       the GISA is not in alert list
  patch 12/12: during kvm_arch_init() now the return code of
    	       kvm_s390_gib_init() is honored.

All other patches are unchanged.

Michael Mueller (12):
  KVM: s390: unregister debug feature on failing arch init
  s390/cio: add function chsc_sgib()
  KVM: s390: add the GIB and its related life-cyle functions
  KVM: s390: factor out nullify_gisa()
  KVM: s390: add metric vcpus_in_sie to struct kvm_arch
  KVM: s390: add kvm reference to struct sie_page2
  KVM: s390: factor out __find_vcpu_for_floating_irq()
  KVM: s390: add function process_gib_alert_list()
  KVM: s390: add functions to (un)register GISC with GISA
  KVM: s390: add and wire function gib_alert_irq_handler()
  KVM: s390: start using the GIB
  KVM: s390: allow to change the IAM clear strategy dynamically

 arch/s390/include/asm/cio.h      |   1 +
 arch/s390/include/asm/irq.h      |   1 +
 arch/s390/include/asm/isc.h      |   1 +
 arch/s390/include/asm/kvm_host.h |  20 ++-
 arch/s390/kernel/irq.c           |   1 +
 arch/s390/kvm/interrupt.c        | 272 +++++++++++++++++++++++++++++++++++++--
 arch/s390/kvm/kvm-s390.c         |  31 ++++-
 arch/s390/kvm/kvm-s390.h         |   8 ++
 drivers/s390/cio/chsc.c          |  37 ++++++
 drivers/s390/cio/chsc.h          |   1 +
 10 files changed, 358 insertions(+), 15 deletions(-)
```
#### [PATCH v2 0/3] kvm: split retrieval and clearing of dirty log
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

There are two problems with KVM_GET_DIRTY_LOG.  First, and less important,
it can take kvm->mmu_lock for an extended period of time.  Second, its user
can actually see many false positives in some cases.  The latter is due
to a benign race like this:

  1. KVM_GET_DIRTY_LOG returns a set of dirty pages and write protects
     them.
  2. The guest modifies the pages, causing them to be marked ditry.
  3. Userspace actually copies the pages.
  4. KVM_GET_DIRTY_LOG returns those pages as dirty again, even though
     they were not written to since (3).

This is especially a problem for large guests, where the time between
(1) and (3) can be substantial.  This patch introduces a new
capability which, when enabled, makes KVM_GET_DIRTY_LOG not
write-protect the pages it returns.  Instead, userspace has to
explicitly clear the dirty log bits just before using the content
of the page.  The new KVM_CLEAR_DIRTY_LOG ioctl can operate on a
64-page granularity rather than requiring to sync a full memslot.
This way the mmu_lock is taken for small amounts of time, and
only a small amount of time will pass between write protection
of pages and the sending of their content.

This is entirely implemented in generic code, but only users of
kvm_get_dirty_log_protect get the support (that is x86_64, ARM and MIPS).

There are no code changes from v1, only documentation and comments.

v1->v2: fix documentation and comments to cover PML case [Junaid]
	fix parameter direction [Junaid]
	remark on userspace setting bits beyond the end of the memslot [Junaid]

Paolo Bonzini (3):
  kvm: make KVM_CAP_ENABLE_CAP_VM architecture agnostic
  kvm: rename last argument to kvm_get_dirty_log_protect
  kvm: introduce manual dirty log reprotect

 Documentation/virtual/kvm/api.txt                  |  80 ++++++++++-
 arch/mips/kvm/mips.c                               |  29 +++-
 arch/powerpc/kvm/powerpc.c                         |  14 +-
 arch/s390/kvm/kvm-s390.c                           |  11 +-
 arch/x86/kvm/x86.c                                 |  47 ++++--
 include/linux/kvm_host.h                           |   9 +-
 include/uapi/linux/kvm.h                           |  15 ++
 tools/testing/selftests/kvm/Makefile               |   2 +
 tools/testing/selftests/kvm/clear_dirty_log_test.c |   2 +
 tools/testing/selftests/kvm/dirty_log_test.c       |  19 +++
 tools/testing/selftests/kvm/include/kvm_util.h     |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |  13 ++
 virt/kvm/arm/arm.c                                 |  22 ++-
 virt/kvm/kvm_main.c                                | 159 ++++++++++++++++++---
 14 files changed, 358 insertions(+), 66 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
```
#### [PATCH v3 0/6] vfio: ccw: VFIO CCW cleanup part1
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

The goal of the patches of this serie is to clarify the code
of state/event handling.

- First patch (already acked/applied) makes sure that every structures are initialized
  before the mediated device is registered.
  (Only here to apply the serie on the main tree).

- vfio: ccw: Rework subchannel state on setup
  makes sure that the device can not be used before a guest is
  ready to drive it.

- vfio: ccw: Rework subchannel state on removing
  could be squash with the previous: same kind of rewriting
  but for the removing/release callbacks.

- vfio: ccw: Rework subchannel state on sch_event
  sch_event handling seems quite poor to me.
  Anyway, I do not understand why we hould have state change there.

- vfio: ccw: Documenting state transitions

- vfio: ccw: serialize the write system calls
  Quite independent of the previous patches, this makes sure
  that the entry in the driver is serialized.

Pierre Morel (6):
  vfio: ccw: Register mediated device once all structures are
    initialized
  vfio: ccw: Rework subchannel state on setup
  vfio: ccw: Rework subchannel state on removing
  vfio: ccw: Rework subchannel state on sch_event
  vfio: ccw: Documenting state transitions
  vfio: ccw: serialize the write system calls

 Documentation/s390/vfio-ccw.txt     | 45 +++++++++++++++++++++++++
 drivers/s390/cio/vfio_ccw_async.c   | 11 +++++++
 drivers/s390/cio/vfio_ccw_drv.c     | 30 ++++-------------
 drivers/s390/cio/vfio_ccw_ops.c     | 65 ++++++++++++++++++++++++-------------
 drivers/s390/cio/vfio_ccw_private.h |  1 +
 5 files changed, 105 insertions(+), 47 deletions(-)
```
