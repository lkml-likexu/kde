#### [PATCH 1/1] MAINTAINERS: vfio-ccw: Remove myself as the maintainer
##### From: Farhan Ali <alifm@linux.ibm.com>

```c
I will not be able to continue with my maintainership responsibilities
going forward, so remove myself as the maintainer.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
---
 MAINTAINERS | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH 1/1] MAINTAINERS: vfio-ccw: Remove myself as the maintainer
##### From: Farhan Ali <alifm@linux.ibm.com>

```c
I will not be able to continue with my maintainership responsibilities
going forward, so remove myself as the maintainer.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
---
 MAINTAINERS | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH 01/12] mm/gup: add make_dirty arg to put_user_pages_dirty_lock()
##### From: john.hubbard@gmail.com

```c
From: John Hubbard <jhubbard@nvidia.com>

Provide more capable variation of put_user_pages_dirty_lock(),
and delete put_user_pages_dirty(). This is based on the
following:

1. Lots of call sites become simpler if a bool is passed
into put_user_page*(), instead of making the call site
choose which put_user_page*() variant to call.

2. Christoph Hellwig's observation that set_page_dirty_lock()
is usually correct, and set_page_dirty() is usually a
bug, or at least questionable, within a put_user_page*()
calling chain.

This leads to the following API choices:

    * put_user_pages_dirty_lock(page, npages, make_dirty)

    * There is no put_user_pages_dirty(). You have to
      hand code that, in the rare case that it's
      required.

Cc: Matthew Wilcox <willy@infradead.org>
Cc: Jan Kara <jack@suse.cz>
Cc: Christoph Hellwig <hch@lst.de>
Cc: Ira Weiny <ira.weiny@intel.com>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 drivers/infiniband/core/umem.c             |   5 +-
 drivers/infiniband/hw/hfi1/user_pages.c    |   5 +-
 drivers/infiniband/hw/qib/qib_user_pages.c |   5 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c   |   5 +-
 drivers/infiniband/sw/siw/siw_mem.c        |   8 +-
 include/linux/mm.h                         |   5 +-
 mm/gup.c                                   | 115 +++++++++------------
 7 files changed, 58 insertions(+), 90 deletions(-)

```
#### [PATCH] Documentation: move Documentation/virtual to Documentation/virt
##### From: Christoph Hellwig <hch@lst.de>

```c
Renaming docs seems to be en vogue at the moment, so fix on of the
grossly misnamed directories.  We usually never use "virtual" as
a shortcut for virtualization in the kernel, but always virt,
as seen in the virt/ top-level directory.  Fix up the documentation
to match that.

Fixes: ed16648eb5b8 ("Move kvm, uml, and lguest subdirectories under a common "virtual" directory, I.E:")
Signed-off-by: Christoph Hellwig <hch@lst.de>
---
 Documentation/admin-guide/kernel-parameters.txt             | 2 +-
 Documentation/{virtual => virt}/index.rst                   | 0
 .../{virtual => virt}/kvm/amd-memory-encryption.rst         | 0
 Documentation/{virtual => virt}/kvm/api.txt                 | 2 +-
 Documentation/{virtual => virt}/kvm/arm/hyp-abi.txt         | 0
 Documentation/{virtual => virt}/kvm/arm/psci.txt            | 0
 Documentation/{virtual => virt}/kvm/cpuid.rst               | 0
 Documentation/{virtual => virt}/kvm/devices/README          | 0
 .../{virtual => virt}/kvm/devices/arm-vgic-its.txt          | 0
 Documentation/{virtual => virt}/kvm/devices/arm-vgic-v3.txt | 0
 Documentation/{virtual => virt}/kvm/devices/arm-vgic.txt    | 0
 Documentation/{virtual => virt}/kvm/devices/mpic.txt        | 0
 Documentation/{virtual => virt}/kvm/devices/s390_flic.txt   | 0
 Documentation/{virtual => virt}/kvm/devices/vcpu.txt        | 0
 Documentation/{virtual => virt}/kvm/devices/vfio.txt        | 0
 Documentation/{virtual => virt}/kvm/devices/vm.txt          | 0
 Documentation/{virtual => virt}/kvm/devices/xics.txt        | 0
 Documentation/{virtual => virt}/kvm/devices/xive.txt        | 0
 Documentation/{virtual => virt}/kvm/halt-polling.txt        | 0
 Documentation/{virtual => virt}/kvm/hypercalls.txt          | 4 ++--
 Documentation/{virtual => virt}/kvm/index.rst               | 0
 Documentation/{virtual => virt}/kvm/locking.txt             | 0
 Documentation/{virtual => virt}/kvm/mmu.txt                 | 2 +-
 Documentation/{virtual => virt}/kvm/msr.txt                 | 0
 Documentation/{virtual => virt}/kvm/nested-vmx.txt          | 0
 Documentation/{virtual => virt}/kvm/ppc-pv.txt              | 0
 Documentation/{virtual => virt}/kvm/review-checklist.txt    | 2 +-
 Documentation/{virtual => virt}/kvm/s390-diag.txt           | 0
 Documentation/{virtual => virt}/kvm/timekeeping.txt         | 0
 Documentation/{virtual => virt}/kvm/vcpu-requests.rst       | 0
 Documentation/{virtual => virt}/paravirt_ops.rst            | 0
 Documentation/{virtual => virt}/uml/UserModeLinux-HOWTO.txt | 0
 MAINTAINERS                                                 | 6 +++---
 arch/powerpc/include/uapi/asm/kvm_para.h                    | 2 +-
 arch/x86/kvm/mmu.c                                          | 2 +-
 include/uapi/linux/kvm.h                                    | 4 ++--
 tools/include/uapi/linux/kvm.h                              | 4 ++--
 virt/kvm/arm/arm.c                                          | 2 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c                            | 2 +-
 virt/kvm/arm/vgic/vgic.h                                    | 4 ++--
 40 files changed, 19 insertions(+), 19 deletions(-)
 rename Documentation/{virtual => virt}/index.rst (100%)
 rename Documentation/{virtual => virt}/kvm/amd-memory-encryption.rst (100%)
 rename Documentation/{virtual => virt}/kvm/api.txt (99%)
 rename Documentation/{virtual => virt}/kvm/arm/hyp-abi.txt (100%)
 rename Documentation/{virtual => virt}/kvm/arm/psci.txt (100%)
 rename Documentation/{virtual => virt}/kvm/cpuid.rst (100%)
 rename Documentation/{virtual => virt}/kvm/devices/README (100%)
 rename Documentation/{virtual => virt}/kvm/devices/arm-vgic-its.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/arm-vgic-v3.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/arm-vgic.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/mpic.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/s390_flic.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/vcpu.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/vfio.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/vm.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/xics.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/xive.txt (100%)
 rename Documentation/{virtual => virt}/kvm/halt-polling.txt (100%)
 rename Documentation/{virtual => virt}/kvm/hypercalls.txt (97%)
 rename Documentation/{virtual => virt}/kvm/index.rst (100%)
 rename Documentation/{virtual => virt}/kvm/locking.txt (100%)
 rename Documentation/{virtual => virt}/kvm/mmu.txt (99%)
 rename Documentation/{virtual => virt}/kvm/msr.txt (100%)
 rename Documentation/{virtual => virt}/kvm/nested-vmx.txt (100%)
 rename Documentation/{virtual => virt}/kvm/ppc-pv.txt (100%)
 rename Documentation/{virtual => virt}/kvm/review-checklist.txt (95%)
 rename Documentation/{virtual => virt}/kvm/s390-diag.txt (100%)
 rename Documentation/{virtual => virt}/kvm/timekeeping.txt (100%)
 rename Documentation/{virtual => virt}/kvm/vcpu-requests.rst (100%)
 rename Documentation/{virtual => virt}/paravirt_ops.rst (100%)
 rename Documentation/{virtual => virt}/uml/UserModeLinux-HOWTO.txt (100%)

```
#### [GIT PULL] KVM fixes for Linux 5.3-rc2
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 30cd8604323dbaf20a80e797fe7057f5b02e394d:

  KVM: x86: Add fixed counters to PMU filter (2019-07-20 09:00:48 +0200)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 266e85a5ec9100dcd9ae03601453bbc96fefee5d:

  KVM: X86: Boost queue head vCPU to mitigate lock waiter preemption (2019-07-24 13:56:53 +0200)

----------------------------------------------------------------
Bugfixes, and a pvspinlock optimization

----------------------------------------------------------------
Christoph Hellwig (1):
      Documentation: move Documentation/virtual to Documentation/virt

Jan Kiszka (2):
      KVM: nVMX: Clear pending KVM_REQ_GET_VMCS12_PAGES when leaving nested
      KVM: nVMX: Set cached_vmcs12 and cached_shadow_vmcs12 NULL after free

Paolo Bonzini (1):
      Revert "kvm: x86: Use task structs fpu field for user"

Wanpeng Li (3):
      KVM: X86: Fix fpu state crash in kvm guest
      KVM: X86: Dynamically allocate user_fpu
      KVM: X86: Boost queue head vCPU to mitigate lock waiter preemption

 Documentation/admin-guide/kernel-parameters.txt          |  2 +-
 Documentation/{virtual => virt}/index.rst                |  0
 .../{virtual => virt}/kvm/amd-memory-encryption.rst      |  0
 Documentation/{virtual => virt}/kvm/api.txt              |  2 +-
 Documentation/{virtual => virt}/kvm/arm/hyp-abi.txt      |  0
 Documentation/{virtual => virt}/kvm/arm/psci.txt         |  0
 Documentation/{virtual => virt}/kvm/cpuid.rst            |  0
 Documentation/{virtual => virt}/kvm/devices/README       |  0
 .../{virtual => virt}/kvm/devices/arm-vgic-its.txt       |  0
 .../{virtual => virt}/kvm/devices/arm-vgic-v3.txt        |  0
 Documentation/{virtual => virt}/kvm/devices/arm-vgic.txt |  0
 Documentation/{virtual => virt}/kvm/devices/mpic.txt     |  0
 .../{virtual => virt}/kvm/devices/s390_flic.txt          |  0
 Documentation/{virtual => virt}/kvm/devices/vcpu.txt     |  0
 Documentation/{virtual => virt}/kvm/devices/vfio.txt     |  0
 Documentation/{virtual => virt}/kvm/devices/vm.txt       |  0
 Documentation/{virtual => virt}/kvm/devices/xics.txt     |  0
 Documentation/{virtual => virt}/kvm/devices/xive.txt     |  0
 Documentation/{virtual => virt}/kvm/halt-polling.txt     |  0
 Documentation/{virtual => virt}/kvm/hypercalls.txt       |  4 ++--
 Documentation/{virtual => virt}/kvm/index.rst            |  0
 Documentation/{virtual => virt}/kvm/locking.txt          |  0
 Documentation/{virtual => virt}/kvm/mmu.txt              |  2 +-
 Documentation/{virtual => virt}/kvm/msr.txt              |  0
 Documentation/{virtual => virt}/kvm/nested-vmx.txt       |  0
 Documentation/{virtual => virt}/kvm/ppc-pv.txt           |  0
 Documentation/{virtual => virt}/kvm/review-checklist.txt |  2 +-
 Documentation/{virtual => virt}/kvm/s390-diag.txt        |  0
 Documentation/{virtual => virt}/kvm/timekeeping.txt      |  0
 Documentation/{virtual => virt}/kvm/vcpu-requests.rst    |  0
 Documentation/{virtual => virt}/paravirt_ops.rst         |  0
 .../{virtual => virt}/uml/UserModeLinux-HOWTO.txt        |  0
 MAINTAINERS                                              |  6 +++---
 arch/powerpc/include/uapi/asm/kvm_para.h                 |  2 +-
 arch/x86/include/asm/kvm_host.h                          |  7 ++++---
 arch/x86/kvm/mmu.c                                       |  2 +-
 arch/x86/kvm/svm.c                                       | 13 ++++++++++++-
 arch/x86/kvm/vmx/nested.c                                |  4 ++++
 arch/x86/kvm/vmx/vmx.c                                   | 13 ++++++++++++-
 arch/x86/kvm/x86.c                                       | 16 ++++++++++------
 include/uapi/linux/kvm.h                                 |  4 ++--
 tools/include/uapi/linux/kvm.h                           |  4 ++--
 virt/kvm/arm/arm.c                                       |  2 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c                         |  2 +-
 virt/kvm/arm/vgic/vgic.h                                 |  4 ++--
 45 files changed, 61 insertions(+), 30 deletions(-)
 rename Documentation/{virtual => virt}/index.rst (100%)
 rename Documentation/{virtual => virt}/kvm/amd-memory-encryption.rst (100%)
 rename Documentation/{virtual => virt}/kvm/api.txt (99%)
 rename Documentation/{virtual => virt}/kvm/arm/hyp-abi.txt (100%)
 rename Documentation/{virtual => virt}/kvm/arm/psci.txt (100%)
 rename Documentation/{virtual => virt}/kvm/cpuid.rst (100%)
 rename Documentation/{virtual => virt}/kvm/devices/README (100%)
 rename Documentation/{virtual => virt}/kvm/devices/arm-vgic-its.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/arm-vgic-v3.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/arm-vgic.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/mpic.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/s390_flic.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/vcpu.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/vfio.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/vm.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/xics.txt (100%)
 rename Documentation/{virtual => virt}/kvm/devices/xive.txt (100%)
 rename Documentation/{virtual => virt}/kvm/halt-polling.txt (100%)
 rename Documentation/{virtual => virt}/kvm/hypercalls.txt (97%)
 rename Documentation/{virtual => virt}/kvm/index.rst (100%)
 rename Documentation/{virtual => virt}/kvm/locking.txt (100%)
 rename Documentation/{virtual => virt}/kvm/mmu.txt (99%)
 rename Documentation/{virtual => virt}/kvm/msr.txt (100%)
 rename Documentation/{virtual => virt}/kvm/nested-vmx.txt (100%)
 rename Documentation/{virtual => virt}/kvm/ppc-pv.txt (100%)
 rename Documentation/{virtual => virt}/kvm/review-checklist.txt (95%)
 rename Documentation/{virtual => virt}/kvm/s390-diag.txt (100%)
 rename Documentation/{virtual => virt}/kvm/timekeeping.txt (100%)
 rename Documentation/{virtual => virt}/kvm/vcpu-requests.rst (100%)
 rename Documentation/{virtual => virt}/paravirt_ops.rst (100%)
 rename Documentation/{virtual => virt}/uml/UserModeLinux-HOWTO.txt (100%)
```
#### [PATCH 1/3] KVM: arm/arm64: vgic-its: Introduce multiple LPI translation caches
##### From: Xiangyou Xie <xiexiangyou@huawei.com>

```c
Because dist->lpi_list_lock is a perVM lock, when a virtual machine
is configured with multiple virtual NIC devices and receives
network packets at the same time, dist->lpi_list_lock will become
a performance bottleneck.

This patch increases the number of lpi_translation_cache to eight,
hashes the cpuid that executes irqfd_wakeup, and chooses which
lpi_translation_cache to use.

Signed-off-by: Xiangyou Xie <xiexiangyou@huawei.com>
---
 include/kvm/arm_vgic.h        |  13 ++-
 virt/kvm/arm/vgic/vgic-init.c |   6 +-
 virt/kvm/arm/vgic/vgic-its.c  | 199 +++++++++++++++++++++++++-----------------
 3 files changed, 133 insertions(+), 85 deletions(-)

```
#### [PATCH] KVM: X86: Boost queue head vCPU to mitigate lock waiter preemption
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Commit 11752adb (locking/pvqspinlock: Implement hybrid PV queued/unfair locks)
introduces hybrid PV queued/unfair locks 
 - queued mode (no starvation)
 - unfair mode (good performance on not heavily contended lock)
The lock waiter goes into the unfair mode especially in VMs with over-commit
vCPUs since increaing over-commitment increase the likehood that the queue 
head vCPU may have been preempted and not actively spinning.

However, reschedule queue head vCPU timely to acquire the lock still can get 
better performance than just depending on lock stealing in over-subscribe 
scenario.

Testing on 80 HT 2 socket Xeon Skylake server, with 80 vCPUs VM 80GB RAM:
ebizzy -M
             vanilla     boosting    improved
 1VM          23520        25040         6%
 2VM           8000        13600        70%
 3VM           3100         5400        74%

The lock holder vCPU yields to the queue head vCPU when unlock, to boost queue 
head vCPU which is involuntary preemption or the one which is voluntary halt 
due to fail to acquire the lock after a short spin in the guest.

Cc: Waiman Long <longman@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH 1/4] migration: fix migrate_cancel leads live_migration thread endless loop
##### From: Juan Quintela <quintela@redhat.com>

```c
From: Ivan Ren <renyime@gmail.com>

When we 'migrate_cancel' a multifd migration, live_migration thread may
go into endless loop in multifd_send_pages functions.

Reproduce steps:

(qemu) migrate_set_capability multifd on
(qemu) migrate -d url
(qemu) [wait a while]
(qemu) migrate_cancel

Then may get live_migration 100% cpu usage in following stack:

pthread_mutex_lock
qemu_mutex_lock_impl
multifd_send_pages
multifd_queue_page
ram_save_multifd_page
ram_save_target_page
ram_save_host_page
ram_find_and_save_block
ram_find_and_save_block
ram_save_iterate
qemu_savevm_state_iterate
migration_iteration_run
migration_thread
qemu_thread_start
start_thread
clone

Signed-off-by: Ivan Ren <ivanren@tencent.com>
Message-Id: <1561468699-9819-2-git-send-email-ivanren@tencent.com>
Reviewed-by: Juan Quintela <quintela@redhat.com>
Signed-off-by: Juan Quintela <quintela@redhat.com>
Reviewed-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
---
 migration/ram.c | 36 +++++++++++++++++++++++++++++-------
 1 file changed, 29 insertions(+), 7 deletions(-)

```
#### [PATCH v2 1/5] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

This patch is meant to move the head/tail adding logic out of the shuffle
code and into the __free_one_page function since ultimately that is where
it is really needed anyway. By doing this we should be able to reduce the
overhead and can consolidate all of the list addition bits in one spot.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h |   12 --------
 mm/page_alloc.c        |   70 +++++++++++++++++++++++++++---------------------
 mm/shuffle.c           |   24 ----------------
 mm/shuffle.h           |   32 ++++++++++++++++++++++
 4 files changed, 71 insertions(+), 67 deletions(-)

```
#### [PATCH v2 QEMU] virtio-balloon: Provide a interface for "bubble hinting"
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "bubble hinting". Basically the
idea is to function very similar to how the balloon works in that we
basically end up madvising the page as not being used. However we don't
really need to bother with any deflate type logic since the page will be
faulted back into the guest when it is read or written to.

This is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c                      |   40 +++++++++++++++++++++++
 include/hw/virtio/virtio-balloon.h              |    2 +
 include/standard-headers/linux/virtio_balloon.h |    1 +
 3 files changed, 42 insertions(+), 1 deletion(-)

```
