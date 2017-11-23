#### [PATCH] KVM: MMU: record maximum physical address width in kvm_mmu_extended_role
##### From: Yu Zhang <yu.c.zhang@linux.intel.com>

```c
Previously, commit 7dcd57552008 ("x86/kvm/mmu: check if tdp/shadow
MMU reconfiguration is needed") offered some optimization to avoid
the unnecessary reconfiguration. Yet one scenario is broken - when
cpuid changes VM's maximum physical address width, reconfiguration
is needed to reset the reserved bits.  Also, the TDP may need to
reset its shadow_root_level when this value is changed.

To fix this, a new field, maxphyaddr, is introduced in the extended
role structure to keep track of the configured guest physical address
width.

Signed-off-by: Yu Zhang <yu.c.zhang@linux.intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: linux-kernel@vger.kernel.org
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/mmu.c              | 1 +
 2 files changed, 2 insertions(+)

```
#### [PATCH v7 01/15] KVM: s390: drop obsolete else path
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
The explicit else path specified in set_intercept_indicators_io
is not required as the function returns in case the first branch
is taken anyway.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
---
 arch/s390/kvm/interrupt.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/4] KVM: x86: Move mmu_memory_cache functions to common code
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
We are currently duplicating the mmu memory cache functionality quite
heavily between the architectures that support KVM.  As a first step,
move the x86 implementation (which seems to have the most recently
maintained version of the mmu memory cache) to common code.

We introduce an arch-specific kvm_types.h which can be used to
define the architecture-specific GFP flags for allocating memory to the
memory cache, and to specify how many objects are required in the memory
cache.  These are the two points where the current implementations
diverge across architectures.  Since kvm_host.h defines structures with
fields of the memcache object, we define the memcache structure in
kvm_types.h, and we include the architecture-specific kvm_types.h to
know the size of object in kvm_host.h.

We only define the functions and data types if
KVM_ARCH_WANT_MMU_MEMORY_CACHE is defined, because not all architectures
require the mmu memory cache.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/arm/include/asm/kvm_types.h     |  5 +++
 arch/arm64/include/asm/kvm_types.h   |  6 +++
 arch/mips/include/asm/kvm_types.h    |  5 +++
 arch/powerpc/include/asm/kvm_types.h |  5 +++
 arch/s390/include/asm/kvm_types.h    |  5 +++
 arch/x86/include/asm/kvm_host.h      | 11 -----
 arch/x86/include/asm/kvm_types.h     | 12 ++++++
 arch/x86/kvm/mmu.c                   | 59 ---------------------------
 include/linux/kvm_host.h             | 11 +++++
 include/linux/kvm_types.h            | 13 ++++++
 virt/kvm/kvm_main.c                  | 60 ++++++++++++++++++++++++++++
 11 files changed, 122 insertions(+), 70 deletions(-)
 create mode 100644 arch/arm/include/asm/kvm_types.h
 create mode 100644 arch/arm64/include/asm/kvm_types.h
 create mode 100644 arch/mips/include/asm/kvm_types.h
 create mode 100644 arch/powerpc/include/asm/kvm_types.h
 create mode 100644 arch/s390/include/asm/kvm_types.h
 create mode 100644 arch/x86/include/asm/kvm_types.h

diff --git a/arch/arm/include/asm/kvm_types.h b/arch/arm/include/asm/kvm_types.h
new file mode 100644
index 000000000000..bc389f82e88d
--- /dev/null
+++ b/arch/arm/include/asm/kvm_types.h
@@ -0,0 +1,5 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_ARM_KVM_TYPES_H
+#define _ASM_ARM_KVM_TYPES_H
+
+#endif /* _ASM_ARM_KVM_TYPES_H */
diff --git a/arch/arm64/include/asm/kvm_types.h b/arch/arm64/include/asm/kvm_types.h
new file mode 100644
index 000000000000..d0987007d581
--- /dev/null
+++ b/arch/arm64/include/asm/kvm_types.h
@@ -0,0 +1,6 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_ARM64_KVM_TYPES_H
+#define _ASM_ARM64_KVM_TYPES_H
+
+#endif /* _ASM_ARM64_KVM_TYPES_H */
+
diff --git a/arch/mips/include/asm/kvm_types.h b/arch/mips/include/asm/kvm_types.h
new file mode 100644
index 000000000000..5efeb32a5926
--- /dev/null
+++ b/arch/mips/include/asm/kvm_types.h
@@ -0,0 +1,5 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_MIPS_KVM_TYPES_H
+#define _ASM_MIPS_KVM_TYPES_H
+
+#endif /* _ASM_MIPS_KVM_TYPES_H */
diff --git a/arch/powerpc/include/asm/kvm_types.h b/arch/powerpc/include/asm/kvm_types.h
new file mode 100644
index 000000000000..f627eceaa314
--- /dev/null
+++ b/arch/powerpc/include/asm/kvm_types.h
@@ -0,0 +1,5 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_POWERPC_KVM_TYPES_H
+#define _ASM_POWERPC_KVM_TYPES_H
+
+#endif /* _ASM_POWERPC_KVM_TYPES_H */
diff --git a/arch/s390/include/asm/kvm_types.h b/arch/s390/include/asm/kvm_types.h
new file mode 100644
index 000000000000..b66a81f8a354
--- /dev/null
+++ b/arch/s390/include/asm/kvm_types.h
@@ -0,0 +1,5 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_S390_KVM_TYPES_H
+#define _ASM_S390_KVM_TYPES_H
+
+#endif /* _ASM_S390_KVM_TYPES_H */
```
#### [PATCH] kvm: vmx: Fix typos in vmentry/vmexit control setting
##### From: Yu Zhang <yu.c.zhang@linux.intel.com>

```c
Previously, 'commit f99e3daf94ff ("KVM: x86: Add Intel PT
virtualization work mode")' work mode' offered framework
to support Intel PT virtualization. However, the patch has
some typos in vmx_vmentry_ctrl() and vmx_vmexit_ctrl(), e.g.
used wrong flags and wrong variable, which will cause the
VM entry failure later.

Fixes: 'commit f99e3daf94ff ("KVM: x86: Add Intel PT virtualization work mode")'
Signed-off-by: Yu Zhang <yu.c.zhang@linux.intel.com>
---
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: linux-kernel@vger.kernel.org
---
 arch/x86/kvm/vmx/vmx.h | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH v6 01/14] X86/nVMX: handle_vmon: Read 4 bytes from guest memory
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c
Read the data directly from guest memory instead of the map->read->unmap
sequence. This also avoids using kvm_vcpu_gpa_to_page() and kmap() which
assumes that there is a "struct page" for guest memory.

Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
---
v1 -> v2:
- Massage commit message a bit.
---
 arch/x86/kvm/vmx/nested.c | 14 +++-----------
 1 file changed, 3 insertions(+), 11 deletions(-)

```
#### [PATCH] kvm: x86: Return LA57 feature based on hardware capability
##### From: Yu Zhang <yu.c.zhang@linux.intel.com>

```c
Previously, 'commit 372fddf70904 ("x86/mm: Introduce the 'no5lvl' kernel
parameter")' cleared X86_FEATURE_LA57 in boot_cpu_data, if Linux chooses
to not run in 5-level paging mode. Yet boot_cpu_data is queried by
do_cpuid_ent() as the host capability later when creating vcpus, and Qemu
will not be able to detect this feature and create VMs with LA57 feature.

As discussed earlier, VMs can still benefit from extended linear address
width, e.g. to enhance features like ASLR. So we would like to fix this,
by return the true hardware capability when Qemu queries.

Signed-off-by: Yu Zhang <yu.c.zhang@linux.intel.com>
---
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: linux-kernel@vger.kernel.org
---
 arch/x86/kvm/cpuid.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v7 15/15] KVM: s390: fix possible null pointer dereference in pending_irqs()
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
Assure a GISA is in use before accessing the IPM to avoid a
null pointer dereference issue.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Reported-by: Halil Pasic <pasic@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Pierre Morel<pmorel@linux.ibm.com>
---
 arch/s390/kvm/interrupt.c | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [RFC PATCH 1/4] uprobes: use set_pte_at() not set_pte_at_notify()
##### From: jglisse@redhat.com

```c
From: Jérôme Glisse <jglisse@redhat.com>

Using set_pte_at_notify() trigger useless calls to change_pte() so just
use set_pte_at() instead. The reason is that set_pte_at_notify() should
only be use when going from either a read and write pte to read only pte
with same pfn, or from read only to read and write with a different pfn.

The set_pte_at_notify() was use because __replace_page() code came from
the mm/ksm.c code in which the above rules are valid.

Signed-off-by: Jérôme Glisse <jglisse@redhat.com>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Arnaldo Carvalho de Melo <acme@kernel.org>
Cc: Alexander Shishkin <alexander.shishkin@linux.intel.com>
Cc: Jiri Olsa <jolsa@redhat.com>
Cc: Namhyung Kim <namhyung@kernel.org>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Matthew Wilcox <mawilcox@microsoft.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: kvm@vger.kernel.org
---
 kernel/events/uprobes.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v6 19/27] kvm: Adapt assembly for PIE support
##### From: Thomas Garnier <thgarnie@chromium.org>

```c
Change the assembly code to use only relative references of symbols for the
kernel to be PIE compatible. The new __ASM_MOVABS macro is used to
get the address of a symbol on both 32 and 64-bit with PIE support.

Position Independent Executable (PIE) support will allow to extend the
KASLR randomization range below 0xffffffff80000000.

Signed-off-by: Thomas Garnier <thgarnie@chromium.org>
---
 arch/x86/include/asm/kvm_host.h | 8 ++++++--
 arch/x86/kernel/kvm.c           | 6 ++++--
 arch/x86/kvm/svm.c              | 4 ++--
 arch/x86/kvm/vmx/vmx.c          | 2 +-
 4 files changed, 13 insertions(+), 7 deletions(-)

```
#### [PATCH V3] KVM: x86: Sync the pending Posted-Interrupts
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Some Posted-Interrupts from passthrough devices may be lost or
overwritten when the vCPU is in runnable state.

The SN (Suppress Notification) of PID (Posted Interrupt Descriptor) will
be set when the vCPU is preempted (vCPU in KVM_MP_STATE_RUNNABLE state
but not running on physical CPU). If a posted interrupt coming at this
time, the irq remmaping facility will set the bit of PIR (Posted
Interrupt Requests) without ON (Outstanding Notification).
So this interrupt can't be sync to APIC virtualization register and
will not be handled by Guest because ON is zero.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 5 +++++
 arch/x86/kvm/x86.c     | 2 +-
 2 files changed, 6 insertions(+), 1 deletion(-)

```
