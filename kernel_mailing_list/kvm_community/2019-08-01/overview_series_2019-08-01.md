#### [PATCH v3 QEMU 2/2] virtio-balloon: Provide a interface for unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "unused page reporting".
Basically the idea is to function very similar to how the balloon works
in that we basically end up madvising the page as not being used. However
we don't really need to bother with any deflate type logic since the page
will be faulted back into the guest when it is read or written to.

This is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c                      |   46 ++++++++++++++++++++++-
 include/hw/virtio/virtio-balloon.h              |    2 +
 include/standard-headers/linux/virtio_balloon.h |    1 +
 3 files changed, 46 insertions(+), 3 deletions(-)

```
#### [PATCH] cpuidle-haltpoll: Enable kvm guest polling when dedicated physical CPUs are available
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

The downside of guest side polling is that polling is performed even 
with other runnable tasks in the host. However, even if poll in kvm 
can aware whether or not other runnable tasks in the same pCPU, it 
can still incur extra overhead in over-subscribe scenario. Now we can 
just enable guest polling when dedicated pCPUs are available.

Cc: Rafael J. Wysocki <rafael.j.wysocki@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 drivers/cpuidle/cpuidle-haltpoll.c   | 3 ++-
 drivers/cpuidle/governors/haltpoll.c | 2 +-
 2 files changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3] KVM: x86: Rename access permissions cache member in struct kvm_vcpu_arch
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Rename "access" to "mmio_access" to match the other MMIO cache members
and to make it more obvious that it's tracking the access permissions
for the MMIO cache.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 Documentation/virtual/kvm/mmu.txt | 4 ++--
 arch/x86/include/asm/kvm_host.h   | 2 +-
 arch/x86/kvm/x86.c                | 2 +-
 arch/x86/kvm/x86.h                | 2 +-
 4 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: x86: Unconditionally call x86 ops that are always implemented
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Remove two stale checks for non-NULL ops now that they're implemented by
both VMX and SVM.

Fixes: 74f169090b6f ("kvm/svm: Setup MCG_CAP on AMD properly")
Fixes: b31c114b82b2 ("KVM: X86: Provide a capability to disable PAUSE intercepts")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 8 ++------
 1 file changed, 2 insertions(+), 6 deletions(-)

```
#### [PATCH v3 1/6] mm: Adjust shuffle code to allow for future coalescing
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
#### [patch 1/5] tracehook: Provide TIF_NOTIFY_RESUME handling for KVMReferences: <20190801143250.370326052@linutronix.de>
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
TIF_NOTITY_RESUME is evaluated on return to user space along with other TIF
flags.

>From the kernels point of view a VMENTER is more or less equivalent to
return to user space which means that at least a subset of TIF flags needs
to be evaluated and handled.

Currently KVM handles only TIF_SIGPENDING and TIF_NEED_RESCHED, but
TIF_NOTIFY_RESUME is ignored. So pending task_work etc, is completely
ignored until the vCPU thread actually goes all the way back into
userspace/qemu.

Provide notify_resume_pending() and tracehook_handle_notify_resume() so
this can be handled similar to SIGPENDING.

Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Oleg Nesterov <oleg@redhat.com>
---
 include/linux/tracehook.h |   15 +++++++++++++++
 kernel/task_work.c        |   19 +++++++++++++++++++
```
#### [PATCH v3 1/3] KVM: Fix leak vCPU's VMCS value into other pCPU
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

After commit d73eb57b80b (KVM: Boost vCPUs that are delivering interrupts), a 
five years old bug is exposed. Running ebizzy benchmark in three 80 vCPUs VMs 
on one 80 pCPUs Skylake server, a lot of rcu_sched stall warning splatting 
in the VMs after stress testing:

 INFO: rcu_sched detected stalls on CPUs/tasks: { 4 41 57 62 77} (detected by 15, t=60004 jiffies, g=899, c=898, q=15073)
 Call Trace:
   flush_tlb_mm_range+0x68/0x140
   tlb_flush_mmu.part.75+0x37/0xe0
   tlb_finish_mmu+0x55/0x60
   zap_page_range+0x142/0x190
   SyS_madvise+0x3cd/0x9c0
   system_call_fastpath+0x1c/0x21

swait_active() sustains to be true before finish_swait() is called in 
kvm_vcpu_block(), voluntarily preempted vCPUs are taken into account 
by kvm_vcpu_on_spin() loop greatly increases the probability condition 
kvm_arch_vcpu_runnable(vcpu) is checked and can be true, when APICv 
is enabled the yield-candidate vCPU's VMCS RVI field leaks(by 
vmx_sync_pir_to_irr()) into spinning-on-a-taken-lock vCPU's current 
VMCS.

This patch fixes it by checking conservatively a subset of events.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Marc Zyngier <Marc.Zyngier@arm.com>
Cc: stable@vger.kernel.org
Fixes: 98f4a1467 (KVM: add kvm_arch_vcpu_runnable() test to kvm_vcpu_on_spin() loop)
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v2 -> v3:
 * check conservatively a subset of events
v1 -> v2:
 * checking swait_active(&vcpu->wq) for involuntary preemption

 arch/mips/kvm/mips.c            |  5 +++++
 arch/powerpc/kvm/powerpc.c      |  5 +++++
 arch/s390/kvm/kvm-s390.c        |  5 +++++
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/svm.c              |  6 ++++++
 arch/x86/kvm/vmx/vmx.c          |  6 ++++++
 arch/x86/kvm/x86.c              | 23 +++++++++++++++++++++++
 include/linux/kvm_host.h        |  1 +
 virt/kvm/arm/arm.c              |  5 +++++
 virt/kvm/kvm_main.c             | 13 ++++++++++++-
 10 files changed, 69 insertions(+), 1 deletion(-)

```
#### [PATCH v3 QEMU 1/2] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

We need to make certain to advertise support for page poison tracking if
we want to actually get data on if the guest will be poisoning pages. So
if free page hinting is active we should add page poisoning support and
let the guest disable it if it isn't using it.

Page poisoning will result in a page being dirtied on free. As such we
cannot really avoid having to copy the page at least one more time since
we will need to write the poison value to the destination. As such we can
just ignore free page hinting if page poisoning is enabled as it will
actually reduce the work we have to do.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   25 +++++++++++++++++++++----
 include/hw/virtio/virtio-balloon.h |    1 +
 2 files changed, 22 insertions(+), 4 deletions(-)

```
#### [PATCH v2 01/11] VSOCK: fix header include in vsock_diag_test
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From: Stefan Hajnoczi <stefanha@redhat.com>

The vsock_diag_test program directly included ../../../include/uapi/
headers from the source tree.  Tests are supposed to use the
usr/include/linux/ headers that have been prepared with make
headers_install instead.

Suggested-by: David S. Miller <davem@davemloft.net>
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 tools/testing/vsock/Makefile          | 2 +-
 tools/testing/vsock/README            | 2 +-
 tools/testing/vsock/vsock_diag_test.c | 5 ++---
 3 files changed, 4 insertions(+), 5 deletions(-)

```
#### [PATCH v3 3/3] KVM: Check preempted_in_kernel for involuntary preemption
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

preempted_in_kernel is updated in preempt_notifier when involuntary preemption 
ocurrs, it can be stale when the voluntarily preempted vCPUs are taken into 
account by kvm_vcpu_on_spin() loop. This patch lets it just check preempted_in_kernel 
for involuntary preemption.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 virt/kvm/kvm_main.c | 7 ++++---
 1 file changed, 4 insertions(+), 3 deletions(-)

```
#### [PATCH 1/5] x86: KVM: svm: don't pretend to advance RIP in case wrmsr_interception() results in #GP
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
svm->next_rip is only used by skip_emulated_instruction() and in case
kvm_set_msr() fails we rightfully don't do that. Move svm->next_rip
advancement to 'else' branch to avoid creating false impression that
it's always advanced (and make it look like rdmsr_interception()).

This is a preparatory change to removing hardcoded RIP advancement
from instruction intercepts, no functional change.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
