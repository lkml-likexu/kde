#### [PATCH] KVM: nVMX: Clear pending KVM_REQ_GET_VMCS12_PAGES when leaving nested
##### From: Jan Kiszka <jan.kiszka@web.de>

```c
From: Jan Kiszka <jan.kiszka@siemens.com>

Letting this pend may cause nested_get_vmcs12_pages to run against an
invalid state, corrupting the effective vmcs of L1.

This was triggerable in QEMU after a guest corruption in L2, followed by
a L1 reset.

Signed-off-by: Jan Kiszka <jan.kiszka@siemens.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---

And another gremlin. I'm afraid there is at least one more because
vmport access from L2 is still failing in QEMU. This is just another
fallout from that. At least the host seems stable now.

 arch/x86/kvm/vmx/nested.c | 2 ++
 1 file changed, 2 insertions(+)

--
2.16.4

```
