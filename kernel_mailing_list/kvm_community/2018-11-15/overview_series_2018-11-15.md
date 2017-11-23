#### [PATCH v2 1/6] nVMX x86: Re-name check_vmentry_pre[post]reqs to nested_check_vmentry_pre[post]reqs
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Re-name the functions check_vmentry_pre[post]reqs to
nested_check_pre[post]reqs because these functions are used only in
nested context.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
---
 arch/x86/kvm/vmx.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
