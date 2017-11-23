#### [RESEND PATCH v3 07/13] KVM/nVMX: Use kvm_vcpu_map when mapping the virtual APIC page
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c
Use kvm_vcpu_map when mapping the virtual APIC page since using
kvm_vcpu_gpa_to_page() and kmap() will only work for guest memory that has
a "struct page".

One additional semantic change is that the virtual host mapping lifecycle
has changed a bit. It now has the same lifetime of the pinning of the
virtual APIC page on the host side.

Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
---
v1 -> v2:
- Do not change the lifecycle of the mapping (pbonzini)
- Use pfn_to_hpa instead of gfn_to_gpa
---
 arch/x86/kvm/vmx.c | 39 +++++++++++++--------------------------
 1 file changed, 13 insertions(+), 26 deletions(-)

```
