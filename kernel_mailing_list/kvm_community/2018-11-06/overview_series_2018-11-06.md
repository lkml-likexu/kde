#### [PATCH] KVM/VMX: Check ept_pointer before flushing ept tlb
##### From: ltykernel@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

This patch is to initialize ept_pointer to INVALID_PAGE and check it
before flushing ept tlb. If ept_pointer is invalidated, bypass the flush
request.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
 arch/x86/kvm/vmx.c | 16 +++++++++++++---
 1 file changed, 13 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: nVMX/nSVM: Fix bug which sets vcpu->arch.tsc_offset to L1 tsc_offset
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
In addition, rename write_tsc_offset() callback to write_l1_tsc_offset()
to make it clear that it is meant to set L1 TSC offset.

Fixes: e79f245ddec1 ("X86/KVM: Properly update 'tsc_offset' to represent the running guest")

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Leonid Shatz <leonid.shatz@oracle.com>
---
 arch/x86/include/asm/kvm_host.h |  3 ++-
 arch/x86/kvm/svm.c              |  5 +++--
 arch/x86/kvm/vmx.c              | 18 +++++++++---------
 arch/x86/kvm/x86.c              |  6 +++---
 4 files changed, 17 insertions(+), 15 deletions(-)

```
#### [PATCH v2 1/2] KVM: x86: expose MOVDIRI CPU feature into VM.
##### From: Liu Jingqi <jingqi.liu@intel.com>

```c
MOVDIRI moves doubleword or quadword from register to memory through
direct store which is implemented by using write combining (WC) for
writing data directly into memory without caching the data.

Availability of the MOVDIRI instruction is indicated by the presence of
the CPUID feature flag MOVDIRI(CPUID.0x07.0x0:ECX[bit 27]).

This patch exposes the movdiri feature to the guest.

The release document ref below link:
https://software.intel.com/sites/default/files/managed/c5/15/\
architecture-instruction-set-extensions-programming-reference.pdf

Signed-off-by: Liu Jingqi <jingqi.liu@intel.com>
Cc: Xu Tao <tao3.xu@intel.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86/vPMU: Reprogram fixed counters optimization
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Get fixed PMC is unnecessary if fixed counter configuration
have no changed in KVM Guest.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/pmu_intel.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests] pretty_print_stacks: port to Python 3
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Recognize the line with a byte-based regex, then decode to Unicode
when printing the backtrace.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 scripts/pretty_print_stacks.py | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] kvm-unit-tests: really use QEMU_ACCEL
##### From: Luiz Capitulino <lcapitulino@redhat.com>

```c
According to README.md, users can set QEMU_ACCEL to specify
kvm or tcg. However, get_qemu_acceletor() uses ACCEL instead,
which is wrong since ACCEL is an "internal" variable. The end
result is that tests will still run if the user wants to use
kvm but kvm is unavailable. Fix get_qemu_acceletor() to use
QEMU_ACCEL.

Signed-off-by: Luiz Capitulino <lcapitulino@redhat.com>
---
 scripts/arch-run.bash | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH 1/7] kvm: selftests: x86_64: dirty_log_test: fix -t
##### From: Andrew Jones <drjones@redhat.com>

```c
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH v2 1/5] bitops: introduce change_bit_atomic
##### From: guangrong.xiao@gmail.com

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

It will be used by threaded workqueue

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
---
 include/qemu/bitops.h | 13 +++++++++++++
 1 file changed, 13 insertions(+)

```
#### [kvm PATCH v7 1/2] kvm: x86: Use task structs fpu field for userFrom: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Previously, x86's instantiation of 'struct kvm_vcpu_arch' added an fpu
field to save/restore fpu-related architectural state, which will differ
from kvm's fpu state. However, this is redundant to the 'struct fpu'
field, called fpu, embedded in the task struct, via the thread field.
Thus, this patch removes the user_fpu field from the kvm_vcpu_arch
struct and replaces it with the task struct's fpu field.

This change is significant because the fpu struct is actually quite
large. For example, on the system used to develop this patch, this
change reduces the size of the vcpu_vmx struct from 23680 bytes down to
19520 bytes, when building the kernel with kvmconfig. This reduction in
the size of the vcpu_vmx struct moves us closer to being able to
allocate the struct at order 2, rather than order 3.

Suggested-by: Dave Hansen <dave.hansen@intel.com>
Signed-off-by: Marc Orr <marcorr@google.com>
---
 arch/x86/include/asm/kvm_host.h | 7 +++----
 arch/x86/kvm/x86.c              | 4 ++--
 2 files changed, 5 insertions(+), 6 deletions(-)

```
#### [kvm PATCH v8 1/2] kvm: x86: Use task structs fpu field for userFrom: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Previously, x86's instantiation of 'struct kvm_vcpu_arch' added an fpu
field to save/restore fpu-related architectural state, which will differ
from kvm's fpu state. However, this is redundant to the 'struct fpu'
field, called fpu, embedded in the task struct, via the thread field.
Thus, this patch removes the user_fpu field from the kvm_vcpu_arch
struct and replaces it with the task struct's fpu field.

This change is significant because the fpu struct is actually quite
large. For example, on the system used to develop this patch, this
change reduces the size of the vcpu_vmx struct from 23680 bytes down to
19520 bytes, when building the kernel with kvmconfig. This reduction in
the size of the vcpu_vmx struct moves us closer to being able to
allocate the struct at order 2, rather than order 3.

Suggested-by: Dave Hansen <dave.hansen@intel.com>
Signed-off-by: Marc Orr <marcorr@google.com>
---
 arch/x86/include/asm/kvm_host.h | 7 +++----
 arch/x86/kvm/x86.c              | 4 ++--
 2 files changed, 5 insertions(+), 6 deletions(-)

```
#### [PATCH v2] KVM: arm64: Clarify explanation of STAGE2_PGTABLE_LEVELS
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
In attempting to re-construct the logic for our stage 2 page table
layout I found the reaoning in the comment explaining how we calculate
the number of levels used for stage 2 page tables a bit backwards.

This commit attempts to clarify the comment, to make it slightly easier
to read without having the Arm ARM open on the right page.

While we're at it, fixup a typo in a comment that was recently changed.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Reviewed-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
Changes since v1:
 - Dropped note about (PAGE_SHIFT - 3) > 4

 arch/arm64/include/asm/stage2_pgtable.h | 14 ++++++--------
 virt/kvm/arm/mmu.c                      |  2 +-
 2 files changed, 7 insertions(+), 9 deletions(-)

```
