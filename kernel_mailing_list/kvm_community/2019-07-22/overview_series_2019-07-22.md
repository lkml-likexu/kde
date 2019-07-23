#### [PATCH 1/2] KVM: X86: Fix fpu state crash in kvm guest
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

The idea before commit 240c35a37 was that we have the following FPU states:

               userspace (QEMU)             guest
---------------------------------------------------------------------------
               processor                    vcpu->arch.guest_fpu
>>> KVM_RUN: kvm_load_guest_fpu
               vcpu->arch.user_fpu          processor
>>> preempt out
               vcpu->arch.user_fpu          current->thread.fpu
>>> preempt in
               vcpu->arch.user_fpu          processor
>>> back to userspace
>>> kvm_put_guest_fpu
               processor                    vcpu->arch.guest_fpu
---------------------------------------------------------------------------

With the new lazy model we want to get the state back to the processor 
when schedule in from current->thread.fpu.

Reported-by: Thomas Lambertz <mail@thomaslambertz.de>
Reported-by: anthony <antdev66@gmail.com>
Tested-by: anthony <antdev66@gmail.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Lambertz <mail@thomaslambertz.de>
Cc: anthony <antdev66@gmail.com>
Cc: stable@vger.kernel.org
Fixes: 5f409e20b (x86/fpu: Defer FPU state load until return to userspace)
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
