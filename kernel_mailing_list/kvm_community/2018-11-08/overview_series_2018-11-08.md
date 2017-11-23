#### [PATCH v15 01/10] ACPI: add some GHES structures and macros definition
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Add Generic Error Status Block structures and some macros
definitions, which is referred to the ACPI 4.0 or ACPI 6.2. The
HEST table generation and CPER record will use them.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>

Change since v14:
Thanks Igor's review and comments
1. Update spec comment for AcpiHestNotifyType
2. drop () for the macro definition

Change since v13:
1. Clean the new added structures and macros definition

Change since v12:
1. Address Igor's comments to to get rid of most structures and use
build_append_int_noprefix() API to compose whole error status block
and APEI table in [1]

[1]: https://lkml.org/lkml/2017/8/29/187
---
 include/hw/acpi/acpi-defs.h | 52 +++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 52 insertions(+)

```
#### [PATCH RESEND v15 01/10] ACPI: add some GHES structures and macros definition
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Add Generic Error Status Block structures and some macros
definitions, which is referred to the ACPI 4.0 or ACPI 6.2. The
HEST table generation and CPER record will use them.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
Change since v14:
Thanks Igor's review and comments
1. Update spec comment for AcpiHestNotifyType
2. drop () for the macro definition

Change since v13:
1. Clean the new added structures and macros definition

Change since v12:
1. Address Igor's comments to to get rid of most structures and use
build_append_int_noprefix() API to compose whole error status block
and APEI table in [1]

[1]: https://lkml.org/lkml/2017/8/29/187
---
 include/hw/acpi/acpi-defs.h | 52 +++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 52 insertions(+)

```
#### [PATCH] KVM: x86: fix empty-body warnings
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
We get the following warnings about empty statements when building
with 'W=1':

arch/x86/kvm/lapic.c:632:53: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1907:42: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1936:65: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1975:44: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]

Rework the debug helper macro to get rid of these warnings.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH V5 4/10] KVM/VMX: Add hv tlb range flush support
##### From: ltykernel@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

This patch is to register tlb_remote_flush_with_range callback with
hv tlb range flush interface.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
Change since v4:
	- Use new function kvm_fill_hv_flush_list_func() to fill flush
       request.
Change since v3:
	- Merge Vitaly's don't pass EPT configuration info to
vmx_hv_remote_flush_tlb() fix.
Change since v1:
	- Pass flush range with new hyper-v tlb flush struct rather
       than KVM tlb flush struct.
---
 arch/x86/kvm/vmx.c | 69 ++++++++++++++++++++++++++++++++++++++----------------
 1 file changed, 49 insertions(+), 20 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: nVMX: Test of IA32_TSC on VM-exit MSR-store list
##### From: Jim Mattson <jmattson@google.com>

```c
When IA32_TSC is on the VM-exit MSR-store list, the value saved is not
subject to the "use TSC offsetting" VM-execution control for the
current VMCS.

Prior to commit e79f245ddec17 ("X86/KVM: Properly update 'tsc_offset'
to represent the running guest"), kvm did not handle this situation
properly.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 x86/unittests.cfg |  6 ++++++
 x86/vmx.h         |  1 +
 x86/vmx_tests.c   | 45 +++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 52 insertions(+)

```
#### [kvm-unit-tests PATCH] s390x: Fixup interrupt psws
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Let's use the svc psw instead of the mccheck psw for svc interrupts
and name it supervisor call. Also we exchange the io int psw for the
right one.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/interrupt.c | 2 +-
 s390x/cstart64.S      | 4 ++--
 2 files changed, 3 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x: Fixup svc handling
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Let's use the svc psw instead of the mccheck psw for svc interrupts
and name it supervisor call.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 lib/s390x/interrupt.c | 2 +-
 s390x/cstart64.S      | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/2] KVM: nVMX/nSVM: Fix bug which sets vcpu->arch.tsc_offset to L1 tsc_offset
##### From: Liran Alon <liran.alon@oracle.com>

```c
From: Leonid Shatz <leonid.shatz@oracle.com>

Since commit e79f245ddec1 ("X86/KVM: Properly update 'tsc_offset' to
represent the running guest"), vcpu->arch.tsc_offset meaning was
changed to always reflect the tsc_offset value set on active VMCS.
Regardless if vCPU is currently running L1 or L2.

However, above mentioned commit failed to also change
kvm_vcpu_write_tsc_offset() to set vcpu->arch.tsc_offset correctly.
This is because vmx_write_tsc_offset() could set the tsc_offset value
in active VMCS to given offset parameter *plus vmcs12->tsc_offset*.
However, kvm_vcpu_write_tsc_offset() just sets vcpu->arch.tsc_offset
to given offset parameter. Without taking into account the possible
addition of vmcs12->tsc_offset. (Same is true for SVM case).

Fix this issue by changing kvm_x86_ops->write_tsc_offset() to return
actually set tsc_offset in active VMCS and modify
kvm_vcpu_write_tsc_offset() to set returned value in
vcpu->arch.tsc_offset.
In addition, rename write_tsc_offset() argument to clearly indicate
it specifies a L1 TSC offset.

Fixes: e79f245ddec1 ("X86/KVM: Properly update 'tsc_offset' to represent the running guest")

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Leonid Shatz <leonid.shatz@oracle.com>
---
 arch/x86/include/asm/kvm_host.h |  6 +++++-
 arch/x86/kvm/svm.c              |  9 +++++----
 arch/x86/kvm/vmx.c              | 21 +++++++++------------
 arch/x86/kvm/x86.c              |  8 ++++----
 4 files changed, 23 insertions(+), 21 deletions(-)

```
#### [Resend PATCH V5 1/10] KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

Add flush range call back in the kvm_x86_ops and platform can use it
to register its associated function. The parameter "kvm_tlb_range"
accepts a single range and flush list which contains a list of ranges.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
Change since v1:
       Change "end_gfn" to "pages" to aviod confusion as to whether
"end_gfn" is inclusive or exlusive.
---
 arch/x86/include/asm/kvm_host.h | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [PATCH] x86/kvm/vmx: fix old-style function declaration
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
The inline keyword which is not at the beginning of the function
declaration may trigger the following build warnings, so let's fix it:

arch/x86/kvm/vmx.c:1309:1: warning: ‘inline’ is not at beginning of declaration [-Wold-style-declaration]
arch/x86/kvm/vmx.c:5947:1: warning: ‘inline’ is not at beginning of declaration [-Wold-style-declaration]
arch/x86/kvm/vmx.c:5985:1: warning: ‘inline’ is not at beginning of declaration [-Wold-style-declaration]
arch/x86/kvm/vmx.c:6023:1: warning: ‘inline’ is not at beginning of declaration [-Wold-style-declaration]

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kvm/vmx.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
