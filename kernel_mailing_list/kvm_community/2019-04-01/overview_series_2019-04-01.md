#### [PATCH 1/3] kvm: x86: check kvm_apic_sw_enabled() is enough
##### From: Wei Yang <richardw.yang@linux.intel.com>

```c
On delivering irq to apic, we iterate on vcpu and do the check like
this:

    kvm_apic_present(vcpu)
    kvm_lapic_enabled(vpu)
        kvm_apic_present(vcpu) && kvm_apic_sw_enabled(vcpu->arch.apic)

Since we have already checked kvm_apic_present(), it is reasonable to
replace kvm_lapic_enabled() with kvm_apic_sw_enabled().

Signed-off-by: Wei Yang <richardw.yang@linux.intel.com>
---
 arch/x86/kvm/irq_comm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
