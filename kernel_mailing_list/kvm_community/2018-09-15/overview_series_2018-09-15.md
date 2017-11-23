#### [PATCH] KVM: VMX: Compare against correct size of __launched member
##### From: Johannes Erdfelt <johannes@erdfelt.com>

```c
The bool type is 8-bits, but some assembly code in vmx_vcpu_run
compares the __launched member as 32-bits. While the current layout
of the structure leaves 24-bits of padding after __launched, adding
members with small types after __launched or rearranging members could
result in a "KVM: entry failed, hardware error 0x5" error.

Signed-off-by: Johannes Erdfelt <johannes@erdfelt.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
