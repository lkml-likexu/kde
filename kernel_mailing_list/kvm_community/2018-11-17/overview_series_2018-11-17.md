#### [PATCH 1/7] KVM: nVMX: Prepend "nested_" to check_vmentry_{pre,post}reqs()
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
.. as they are used only in nested context.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
---
 arch/x86/kvm/vmx.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
