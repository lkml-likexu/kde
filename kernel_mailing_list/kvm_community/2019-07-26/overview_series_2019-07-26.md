#### [PATCH] KVM: X86: Use IPI shorthands in kvm guest when support
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

IPI shorthand is supported now by linux apic/x2apic driver, switch to 
IPI shorthand for all excluding self and all including self destination 
shorthand in kvm guest, to avoid splitting the target mask into serveral 
PV IPI hypercalls.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Nadav Amit <namit@vmware.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
Note: rebase against tip tree's x86/apic branch

 arch/x86/kernel/kvm.c | 14 ++++++++++++--
 1 file changed, 12 insertions(+), 2 deletions(-)

```
