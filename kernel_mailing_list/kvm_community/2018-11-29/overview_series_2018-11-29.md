#### [kvm-unit-tests PATCH] kvm: nVMX: Always VMCLEAR before the first VMPTRLD
##### From: Jim Mattson <jmattson@google.com>

```c
Per SDM volume 3, section 24.11.3: Initializing a VMCS, "to avoid the
uncertainties of implementation-specific behavior, software should
execute VMCLEAR on a VMCS region before making the corresponding VMCS
active with VMPTRLD for the first time."

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 x86/vmx.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
