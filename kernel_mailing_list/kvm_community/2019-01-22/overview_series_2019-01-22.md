#### [PATCH 1/2] dma-direct: set_memory_{en,de}crypted() take number of pages
##### From: Thiago Jung Bauermann <bauerman@linux.ibm.com>

```c
From: Ram Pai <linuxram@us.ibm.com>

set_memory_encrypted() and set_memory_decrypted() expect the number of
PAGE_SIZE pages to encrypt or decrypt. dma_direct_alloc() and
dma_direct_free() instead pass number of bytes. This encrypts/decrypts a
huge number of pages resulting in data corruption.

Fixed it.

[ bauermann: Slightly reworded commit message and added Fixes: tag. ]
Fixes: d7b417fa08d1 ("x86/mm: Add DMA support for SEV memory encryption")
Signed-off-by: Ram Pai <linuxram@us.ibm.com>
Signed-off-by: Thiago Jung Bauermann <bauerman@linux.ibm.com>
---
 kernel/dma/direct.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

Notes:

1. This was tested on powerpc with patches adding support for running
   under the ultravisor, which are not yet upstream.

2. The lines changed in this patch were added by commit c10f07aa27da
   ("dma/direct: Handle force decryption for DMA coherent buffers in
   common code"), but it only moves the code from an x86-specific file.
   Therefore the Fixes tag references the commit that first introduced
   the code.

```
#### [PATCH 3/6] x86: kvm: no need to check return value of debugfs_create functions
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
When calling debugfs functions, there is no need to ever check the
return value.  The function can work or not, but the code logic should
never do something different based on this.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: <x86@kernel.org>
Cc: <kvm@vger.kernel.org>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 arch/x86/kvm/debugfs.c | 26 ++++++++------------------
 1 file changed, 8 insertions(+), 18 deletions(-)

```
#### [PATCH] kvm: no need to check return value of debugfs_create functions
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
When calling debugfs functions, there is no need to ever check the
return value.  The function can work or not, but the code logic should
never do something different based on this.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 virt/kvm/kvm_main.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [kvm-unit-test nVMX] If "enable EPT" is enabled in a test, EPT pointer must also be set up
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Commit 2737c0410fa60eeaef8a7af0f8968be40cb1e9d9 move the check for EPT
pointer, from nested_ept_get_cr3() to check_vmentry_prereqs(). As a result
if "enabled EPT" is set in a test but EPT pointer is not, vmentry will fail
even if EPT pointer is not being tested in that particular test.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/vmx_tests.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] KVM: VMX: Fix vm entry failure caused by invalid vmexit controls
##### From: Changbin Du <changbin.du@gmail.com>

```c
The commit c73da3f ("KVM: VMX: Properly handle dynamic VM Entry/Exit
controls") has a typo that cause invalid vmexit controls. The
VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL is against _vmentry_control.

KVM: entry failed, hardware error 0x7
EAX=00000000 EBX=00000000 ECX=00000000 EDX=000206c2
ESI=00000000 EDI=00000000 EBP=00000000 ESP=00000000
EIP=0000fff0 EFL=00000002 [-------] CPL=0 II=0 A20=1 SMM=0 HLT=0
ES =0000 00000000 0000ffff 00009300
CS =f000 ffff0000 0000ffff 00009b00
SS =0000 00000000 0000ffff 00009300
DS =0000 00000000 0000ffff 00009300
FS =0000 00000000 0000ffff 00009300
GS =0000 00000000 0000ffff 00009300
LDT=0000 00000000 0000ffff 00008200
TR =0000 00000000 0000ffff 00008b00
GDT= 00000000 0000ffff
IDT= 00000000 0000ffff
CR0=60000010 CR2=00000000 CR3=00000000 CR4=00000000
DR0=0000000000000000 DR1=0000000000000000 DR2=0000000000000000
DR3=0000000000000000 DR6=00000000ffff0ff0 DR7=0000000000000400
EFER=0000000000000000

Fixes: c73da3f ("KVM: VMX: Properly handle dynamic VM Entry/Exit controls")
Signed-off-by: Changbin Du <changbin.du@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] svm: Add warning message for AVIC IPI invalid targetThread-Topic: [PATCH] svm: Add warning message for AVIC IPI invalid target
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

Print warning message when IPI target ID is invalid due to one of
the following reasons:
  * In logical mode: cluster > max_cluster (64)
  * In physical mode: target > max_physical (512)
  * Address is not present in the physical or logical ID tables

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] svm: Fix AVIC incomplete IPI emulationThread-Topic: [PATCH] svm: Fix AVIC incomplete IPI emulation
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

In case of incomplete IPI with invalid interrupt type, the current
SVM driver does not properly emulate the IPI, and fails to boot
FreeBSD guests with multiple vcpus when enabling AVIC.

Fix this by update APIC ICR high/low registers, which also
emulate sending the IPI.

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c | 19 ++++---------------
 1 file changed, 4 insertions(+), 15 deletions(-)

```
#### [PATCH v2 1/7] KVM:VMX: Define CET VMCS fields and bits
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
On processors that support CET, VMX saves/restores
the states of IA32_S_CET, SSP and IA32_INTERRUPT_SSP_TABLE_ADDR MSR
to the VMCS area for Guest/Host unconditionally.

If VM_EXIT_LOAD_HOST_CET_STATE = 1, the host CET MSRs are
restored from VMCS host-state area at VM exit as follows:

- HOST_IA32_S_CET: Host supervisor mode IA32_S_CET MSR is loaded
                   from this field.

- HOST_SSP : Host SSP is loaded from this field.

- HOST_INTR_SSP_TABLE_ADDR : Host IA32_INTERRUPT_SSP_TABLE_ADDR
                             MSR is loaded from this field.

If VM_ENTRY_LOAD_GUEST_CET_STATE = 1, the guest CET MSRs are loaded
from VMCS guest-state area at VM entry as follows:

- GUEST_IA32_S_CET : Guest supervisor mode IA32_S_CET MSR is loaded
                     from this field.

- GUEST_SSP : Guest SSP is loaded from this field.

- GUEST_INTR_SSP_TABL_ADDR : Guest IA32_INTERRUPT_SSP_TABLE_ADDR
                             MSR is loaded from this field.

Additionally, to context switch guest and host CET states, the VMM
uses xsaves/xrstors instructions to save/restore the guest CET states
at VM exit/entry. The CET xsave area is within thread_struct.fpu area.
If OS execution flow changes during task switch/interrupt/exception etc.,
the OS also relies on xsaves/xrstors to switch CET states accordingly.

Note: Although these VMCS fields are 64-bit, they don't have high fields.

Signed-off-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/vmx.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
