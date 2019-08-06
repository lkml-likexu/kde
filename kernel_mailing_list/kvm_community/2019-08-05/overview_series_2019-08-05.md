#### [PATCH 1/2] KVM: arm64: Don't write junk to sysregs on reset
##### From: Marc Zyngier <maz@kernel.org>

```c
At the moment, the way we reset system registers is mildly insane:
We write junk to them, call the reset functions, and then check that
we have something else in them.

The "fun" thing is that this can happen while the guest is running
(PSCI, for example). If anything in KVM has to evaluate the state
of a system register while junk is in there, bad thing may happen.

Let's stop doing that. Instead, we track that we have called a
reset function for that register, and assume that the reset
function has done something. This requires fixing a couple of
sysreg refinition in the trap table.

In the end, the very need of this reset check is pretty dubious,
as it doesn't check everything (a lot of the sysregs leave outside of
the sys_regs[] array). It may well be axed in the near future.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/sys_regs.c | 32 ++++++++++++++++++--------------
 1 file changed, 18 insertions(+), 14 deletions(-)

```
#### [PATCH] kvm: remove unnecessary PageReserved check
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
The same check is already done in kvm_is_reserved_pfn.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 virt/kvm/kvm_main.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v3 01/19] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interfaceThread-Topic: [PATCH v3 01/19] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
We will be using ONE_REG interface accessing VCPU registers from
user-space hence we add KVM_REG_RISCV for RISC-V VCPU registers.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 include/uapi/linux/kvm.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v4 1/6] KVM: Fix leak vCPU's VMCS value into other pCPU
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
v3 -> v4:
 * just test KVM_REQ_*
 * rename the hook to apicv_has_pending_interrupt
 * wrap with #ifdef CONFIG_KVM_ASYNC_PF 
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
 arch/x86/kvm/x86.c              | 16 ++++++++++++++++
 include/linux/kvm_host.h        |  1 +
 virt/kvm/arm/arm.c              |  5 +++++
 virt/kvm/kvm_main.c             | 16 +++++++++++++++-
 10 files changed, 65 insertions(+), 1 deletion(-)

```
