#### [PATCH]  Export mm_update_next_owner function for vhost-net
##### From: gchen.guomin@gmail.com

```c
From: guomin chen <gchen.guomin@gmail.com>

 Under normal circumstances,When do_exit exits, mm->owner will
 be updated on exit_mm(). but when the kernel process calls
 unuse_mm() and then exits,mm->owner cannot be updated. And it
 will point to a task that has been released.

 Below is my issue on vhost_net:
    A, B are two kernel processes(such as vhost_worker),
    C is a user space process(such as qemu), and all
    three use the mm of the user process C.
    Now, because user process C exits abnormally, the owner of this
    mm becomes A. When A calls unuse_mm and exits, this mm->ower
    still points to the A that has been released.
    When B accesses this mm->owner again, A has been released.

 Process A             Process B
 vhost_worker()        vhost_worker()
  ---------             ---------
  use_mm()              use_mm()
   ...
  unuse_mm()
     tsk->mm=NULL
   do_exit()            page fault
    exit_mm()           access mm->owner
   can't update owner   kernel Oops

                        unuse_mm()

Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Jason Wang <jasowang@redhat.com>
Cc: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org
Cc: netdev@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: "Eric W. Biederman" <ebiederm@xmission.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Sudip Mukherjee <sudipm.mukherjee@gmail.com>
Cc: "Luis R. Rodriguez" <mcgrof@kernel.org>
Cc: Dominik Brodowski <linux@dominikbrodowski.net>
Signed-off-by: guomin chen <gchen.guomin@gmail.com>
---
 drivers/vhost/vhost.c | 1 +
 kernel/exit.c         | 1 +
 2 files changed, 2 insertions(+)

```
#### [PATCH net V3 1/3] vhost: make sure used idx is seen before log in vhost_add_used_n()
##### From: Jason Wang <jasowang@redhat.com>

```c
We miss a write barrier that guarantees used idx is updated and seen
before log. This will let userspace sync and copy used ring before
used idx is update. Fix this by adding a barrier before log_write().

Fixes: 8dd014adfea6f ("vhost-net: mergeable buffers support")
Acked-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] kvm: Change offset in kvm_write_guest_offset_cached to unsigned
##### From: Jim Mattson <jmattson@google.com>

```c
Avoid potential out-of-bounds writes due to negative offsets. Note
that all current call sites are fine.

Fixes: 4ec6e8636256 ("kvm: Introduce kvm_write_guest_offset_cached()")
Reported-by: Cfir Cohen <cfir@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Cfir Cohen <cfir@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 include/linux/kvm_host.h | 3 ++-
 virt/kvm/kvm_main.c      | 3 ++-
 2 files changed, 4 insertions(+), 2 deletions(-)

```
#### KVM: nSVM: improve check for invalid VMCB guest state
##### From: Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>

```c
2018-12-12 14:28-0800, Jim Mattson:
> Just out of curiousity, how does the SVM nested implementation deal
> with the potential time-of-check to time-of-use bugs that were fixed
> on the VMX side with commit 4f2777bc9797 ("kvm: x86: nVMX: maintain
> internal copy of current VMCS")?

It'd be best to move the checks after we load the state.

SVM has a simpler model, where the guest state is checked after loading
it to the processor and throws a VM exit if something is invalid.
This means KVM can let the processor do the checks on most fields and
our pre-check only does three things:

 * intercept contains INTERCEPT_VMRUN

   The check is kind of working because we unconditionally add
   INTERCEPT_VMRUN later.
   There is a problem with visibility of writes after the check if we
   get a write that clears INTERCEPT_VMRUN before a write to VMCB -- the
   VMRUN will succeed and the later writer will take effect.

 * asid != 0

   Asid is never loaded, but still has the visibility problem.

 * nested_ctl doesn't set SVM_NESTED_CTL_NP_ENABLE when npt is disabled

   Looks buggy as the field could be set after the check.  It creates an
   interesting scenario where we don't set SVM_NESTED_CTL_NP_ENABLE in
   nested guest, because we actually preserve the original value, but
   register npt handlers with nested_svm_init_mmu_context.

I think the solution below could work, but my machine became a BRYCK
after a reboot, so testing is going to take a while ...

---8<---
SVM first loads all guest the state and then performs consistency
checks, triggering an immediate VM exit if some fail.

KVM currently checks some guest state and only then loads it to parent's
VMCB, which means that the loaded and checked values can differ.  This
poses a problem with nested->control.nested_ctl, where we could be
registering NPT handlers in a situation where NPT is disabled in KVM.

We also need to protect nested_svm_init_mmu_context() by npt_enabled, as
we remove the flimsy condition that was there before.

Reported-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Radim Krčmář <rkrcmar@redhat.com>
---
 arch/x86/kvm/svm.c | 26 +++++++++-----------------
 1 file changed, 9 insertions(+), 17 deletions(-)

```
#### [kvm-unit-test v3 1/4] KVM nVMX: Change the names of the functions test_vmcs_page_* to test_vmcs_addr_*
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
... because these functions can be used for any VMCS address and not just
     a page.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/vmx_tests.c | 65 ++++++++++++++++++++++++++++-----------------------------
 1 file changed, 32 insertions(+), 33 deletions(-)

```
#### [PATCH] kvm: vmx: Pass through IA32_TSC_AUX for read iff guest has RDTSCP
##### From: Jim Mattson <jmattson@google.com>

```c
If the guest supports RDTSCP, it already has read access to the
hardware IA32_TSC_AUX MSR via RDTSCP, so we can allow it read-access
via RDMSR as well. If the guest doesn't support RDTSCP, then we
should not allow it read access to the hardware IA32_TSC_AUX MSR.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v3 1/3] mm/mmu_notifier: use structure for invalidate_range_start/end callback v2
##### From: jglisse@redhat.com

```c
From: Jérôme Glisse <jglisse@redhat.com>

To avoid having to change many callback definition everytime we want
to add a parameter use a structure to group all parameters for the
mmu_notifier invalidate_range_start/end callback. No functional changes
with this patch.

Changed since v1:
    - fix make htmldocs warning in amdgpu_mn.c

Signed-off-by: Jérôme Glisse <jglisse@redhat.com>
Acked-by: Jan Kara <jack@suse.cz>
Acked-by: Felix Kuehling <Felix.Kuehling@amd.com>
Acked-by: Jason Gunthorpe <jgg@mellanox.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Matthew Wilcox <mawilcox@microsoft.com>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Christian Koenig <christian.koenig@amd.com>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>
---
 drivers/gpu/drm/amd/amdgpu/amdgpu_mn.c  | 47 +++++++++++--------------
 drivers/gpu/drm/i915/i915_gem_userptr.c | 14 ++++----
 drivers/gpu/drm/radeon/radeon_mn.c      | 16 ++++-----
 drivers/infiniband/core/umem_odp.c      | 20 +++++------
 drivers/infiniband/hw/hfi1/mmu_rb.c     | 13 +++----
 drivers/misc/mic/scif/scif_dma.c        | 11 ++----
 drivers/misc/sgi-gru/grutlbpurge.c      | 14 ++++----
 drivers/xen/gntdev.c                    | 12 +++----
 include/linux/mmu_notifier.h            | 14 +++++---
 mm/hmm.c                                | 23 +++++-------
 mm/mmu_notifier.c                       | 21 +++++++++--
 virt/kvm/kvm_main.c                     | 14 +++-----
 12 files changed, 103 insertions(+), 116 deletions(-)

```
#### [PATCH 1/2] migration: introduce compress-wait-thread-adaptive
##### From: guangrong.xiao@gmail.com

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

Currently we have two behaviors if all threads are busy to do compression,
the main thread mush wait one of them becoming free if @compress-wait-thread
set to on or the main thread can directly return without wait and post
the page out as normal one

Both of them have its profits and short-comes, however, if the bandwidth is
not limited extremely so that compression can not use out all of it bandwidth,
at the same time, the migration process is easily throttled if we posted too
may pages as normal pages. None of them can work properly under this case

In order to use the bandwidth more effectively, we introduce the third
behavior, compress-wait-thread-adaptive, which make the main thread wait
if there is no bandwidth left or let the page go out as normal page if there
has enough bandwidth to make sure the migration process will not be
throttled

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
---
 hmp.c                 |  11 +++++
 migration/migration.c |  37 ++++++++++++++++
 migration/migration.h |   4 ++
 migration/ram.c       | 118 +++++++++++++++++++++++++++++++++++++++++++++-----
 qapi/migration.json   |  26 ++++++++++-
 5 files changed, 184 insertions(+), 12 deletions(-)

```
#### [PULL 1/2] vfio: ccw: Merge BUSY and BOXED states
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Pierre Morel <pmorel@linux.ibm.com>

VFIO_CCW_STATE_BOXED and VFIO_CCW_STATE_BUSY have
identical actions for the same events.

Let's merge both into a single state to simplify the code.
We choose to keep VFIO_CCW_STATE_BUSY.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Message-Id: <1539767923-10539-2-git-send-email-pmorel@linux.ibm.com>
Reviewed-by: Eric Farman <farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_fsm.c     | 7 +------
 drivers/s390/cio/vfio_ccw_private.h | 1 -
 2 files changed, 1 insertion(+), 7 deletions(-)

```
#### [PATCH RFC] kvm: arm64: export memory error recovery capability to user space
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
When user space do memory recovery, it will check whether KVM and
guest support the error recovery, only when both of them support,
user space will do the error recovery. This patch exports this
capability of KVM to user space.

Cc: Peter Maydell <peter.maydell@linaro.org>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
User space needs to check this capability of KVM is suggested by Peter[1],
this patch as RFC tag because user space patches are still under review,
so this kernel patch is firstly sent out for review.

[1]: https://patchwork.codeaurora.org/patch/652261/
---
 Documentation/virtual/kvm/api.txt | 9 +++++++++
 arch/arm64/kvm/reset.c            | 1 +
 include/uapi/linux/kvm.h          | 1 +
 3 files changed, 11 insertions(+)

```
#### [PATCH net-next 1/3] vhost: generalize adding used elem
##### From: Jason Wang <jasowang@redhat.com>

```c
Use one generic vhost_copy_to_user() instead of two dedicated
accessor. This will simplify the conversion to fine grain accessors.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 11 +----------
 1 file changed, 1 insertion(+), 10 deletions(-)

```
#### [PATCH] vhost: correct the related warning message
##### From: wangyan <wangyan122@huawei.com>

```c
Fixes: 'commit d588cf8f618d ("target: Fix se_tpg_tfo->tf_subsys regression + remove tf_subsystem")'
       'commit cbbd26b8b1a6 ("[iov_iter] new primitives - copy_from_iter_full() and friends")'

Signed-off-by: Yan Wang <wangyan122@huawei.com>
Reviewed-by: Jun Piao <piaojun@huawei.com>
---
 drivers/vhost/scsi.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] vhost: return EINVAL if iovecs size does not match the message size
##### From: Pavel Tikhomirov <ptikhomirov@virtuozzo.com>

```c
We've failed to copy and process vhost_iotlb_msg so let userspace at
least know about it. For instance before these patch the code below runs
without any error:

int main()
{
  struct vhost_msg msg;
  struct iovec iov;
  int fd;

  fd = open("/dev/vhost-net", O_RDWR);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  iov.iov_base = &msg;
  iov.iov_len = sizeof(msg)-4;

  if (writev(fd, &iov,1) == -1) {
    perror("writev");
    return 1;
  }

  return 0;
}

Signed-off-by: Pavel Tikhomirov <ptikhomirov@virtuozzo.com>
---
 drivers/vhost/vhost.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
