#### [PATCH 1/2] kvm: vmx: fix limit checking in get_vmx_mem_address()
##### From: Eugene Korenevsky <ekorenevsky@gmail.com>

```c
Intel SDM vol. 3, 5.3:
The processor causes a
general-protection exception (or, if the segment is SS, a stack-fault
exception) any time an attempt is made to access the following addresses
in a segment:
- A byte at an offset greater than the effective limit
- A word at an offset greater than the (effective-limit – 1)
- A doubleword at an offset greater than the (effective-limit – 3)
- A quadword at an offset greater than the (effective-limit – 7)

Therefore, the generic limit checking error condition must be

exn = off > limit + 1 - operand_len

but not

exn = off + operand_len > limit

as for now.

Signed-off-by: Eugene Korenevsky <ekorenevsky@gmail.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [5.2 regression] copy_fpstate_to_sigframe() change causing crash in 32-bit process
##### From: Eric Biggers <ebiggers@kernel.org>

```c
On latest Linus' tree I'm getting a crash in a 32-bit Wine process.

I bisected it to the following commit:

commit 39388e80f9b0c3788bfb6efe3054bdce0c3ead45
Author: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Date:   Wed Apr 3 18:41:35 2019 +0200

    x86/fpu: Don't save fxregs for ia32 frames in copy_fpstate_to_sigframe()

Reverting the commit by applying the following diff makes the problem go away.


Apparently the problem is that save_fsave_header() assumes the registers have
been saved to fpu->state.fxsave, yet the code that does so was removed.

Note, bisection was not straightforward because there was another bug also
causing a crash temporarily introduced during the FPU code rework: commit
39ea9baffda9 ("x86/fpu: Remove fpu->initialized usage in __fpu__restore_sig()")
forgot to call fpstate_init() on the temporary 'state' buffer, so
XCOMP_BV_COMPACTED_FORMAT was never set, causing xrstors to fail.  But that bug
went away in later commits.

- Eric

```
#### [RFC PATCH v2 1/3] vfio: Use capability chains to handle device specific irq
##### From: Tina Zhang <tina.zhang@intel.com>

```c
Caps the number of irqs with fixed indexes and uses capability chains
to chain device specific irqs.

VFIO vGPU leverages this mechanism to trigger primary plane and cursor
plane page flip event to the user space.

Signed-off-by: Tina Zhang <tina.zhang@intel.com>
---
 include/uapi/linux/vfio.h | 23 ++++++++++++++++++++++-
 1 file changed, 22 insertions(+), 1 deletion(-)

```
#### [PATCH] kvm: Convert kvm_lock to a mutex
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Junaid Shahid <junaids@google.com>

It doesn't seem as if there is any particular need for kvm_lock to be a
spinlock, so convert the lock to a mutex.

Signed-off-by: Junaid Shahid <junaids@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virtual/kvm/locking.txt |  4 +---
 arch/s390/kvm/kvm-s390.c              |  4 ++--
 arch/x86/kvm/mmu.c                    |  4 ++--
 arch/x86/kvm/x86.c                    | 14 +++++++-------
 include/linux/kvm_host.h              |  2 +-
 virt/kvm/kvm_main.c                   | 30 +++++++++++++++---------------
 6 files changed, 28 insertions(+), 30 deletions(-)

```
#### [PATCH] KVM/nSVM: properly map nested VMCB
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Commit 8c5fbf1a7231 ("KVM/nSVM: Use the new mapping API for mapping guest
memory") broke nested SVM completely: kvm_vcpu_map()'s second parameter is
GFN so vmcb_gpa needs to be converted with gpa_to_gfn(), not the other way
around.

Fixes: 8c5fbf1a7231 ("KVM/nSVM: Use the new mapping API for mapping guest memory")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/svm.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v3 1/4] KVM: x86: Move mmu_memory_cache functions to common code
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
 arch/x86/include/asm/kvm_types.h     | 11 +++++
 arch/x86/kvm/mmu.c                   | 59 ---------------------------
 include/linux/kvm_host.h             | 11 +++++
 include/linux/kvm_types.h            | 13 ++++++
 virt/kvm/kvm_main.c                  | 60 ++++++++++++++++++++++++++++
 11 files changed, 121 insertions(+), 70 deletions(-)
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
#### [patch v2 3/3] cpuidle-haltpoll: disable host side polling when kvm virtualized
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
When performing guest side polling, it is not necessary to 
also perform host side polling. 

So disable host side polling, via the new MSR interface, 
when loading cpuidle-haltpoll driver.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---

v2: remove extra "}"

 arch/x86/Kconfig                        |    7 +++++
 arch/x86/include/asm/cpuidle_haltpoll.h |    8 ++++++
 arch/x86/kernel/kvm.c                   |   40 ++++++++++++++++++++++++++++++++
 drivers/cpuidle/cpuidle-haltpoll.c      |    9 ++++++-
 include/linux/cpuidle_haltpoll.h        |   16 ++++++++++++
 5 files changed, 79 insertions(+), 1 deletion(-)

Index: linux-2.6.git/arch/x86/include/asm/cpuidle_haltpoll.h
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/arch/x86/include/asm/cpuidle_haltpoll.h	2019-06-03 19:38:42.328718617 -0300
@@ -0,0 +1,8 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ARCH_HALTPOLL_H
+#define _ARCH_HALTPOLL_H
+
+void arch_haltpoll_enable(void);
+void arch_haltpoll_disable(void);
+
+#endif
Index: linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c
===================================================================
--- linux-2.6.git.orig/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-03 19:38:12.376619124 -0300
+++ linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-03 19:38:42.328718617 -0300
@@ -15,6 +15,7 @@
 #include <linux/module.h>
 #include <linux/timekeeping.h>
 #include <linux/sched/idle.h>
+#include <linux/cpuidle_haltpoll.h>
 #define CREATE_TRACE_POINTS
 #include "cpuidle-haltpoll-trace.h"
 
@@ -157,11 +158,17 @@
 
 static int __init haltpoll_init(void)
 {
-	return cpuidle_register(&haltpoll_driver, NULL);
+	int ret = cpuidle_register(&haltpoll_driver, NULL);
+
+	if (ret == 0)
+		arch_haltpoll_enable();
+
+	return ret;
 }
 
 static void __exit haltpoll_exit(void)
 {
+	arch_haltpoll_disable();
 	cpuidle_unregister(&haltpoll_driver);
 }
 
Index: linux-2.6.git/include/linux/cpuidle_haltpoll.h
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/include/linux/cpuidle_haltpoll.h	2019-06-03 19:41:57.293366260 -0300
@@ -0,0 +1,16 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _CPUIDLE_HALTPOLL_H
+#define _CPUIDLE_HALTPOLL_H
+
+#ifdef CONFIG_ARCH_CPUIDLE_HALTPOLL
+#include <asm/cpuidle_haltpoll.h>
+#else
+static inline void arch_haltpoll_enable(void)
+{
+}
+
+static inline void arch_haltpoll_disable(void)
+{
+}
+#endif
+#endif
Index: linux-2.6.git/arch/x86/Kconfig
===================================================================
--- linux-2.6.git.orig/arch/x86/Kconfig	2019-06-03 19:38:12.376619124 -0300
+++ linux-2.6.git/arch/x86/Kconfig	2019-06-03 19:42:34.478489868 -0300
@@ -787,6 +787,7 @@
 	bool "KVM Guest support (including kvmclock)"
 	depends on PARAVIRT
 	select PARAVIRT_CLOCK
+	select ARCH_CPUIDLE_HALTPOLL
 	default y
 	---help---
 	  This option enables various optimizations for running under the KVM
@@ -795,6 +796,12 @@
 	  underlying device model, the host provides the guest with
 	  timing infrastructure such as time of day, and system time
 
+config ARCH_CPUIDLE_HALTPOLL
+        def_bool n
+        prompt "Disable host haltpoll when loading haltpoll driver"
+        help
+	  If virtualized under KVM, disable host haltpoll.
+
 config PVH
 	bool "Support for running PVH guests"
 	---help---
Index: linux-2.6.git/arch/x86/kernel/kvm.c
===================================================================
--- linux-2.6.git.orig/arch/x86/kernel/kvm.c	2019-06-03 19:38:12.376619124 -0300
+++ linux-2.6.git/arch/x86/kernel/kvm.c	2019-06-03 19:40:14.359024312 -0300
@@ -853,3 +853,43 @@
 }
 
 #endif	/* CONFIG_PARAVIRT_SPINLOCKS */
+
+#ifdef CONFIG_ARCH_CPUIDLE_HALTPOLL
+
+void kvm_disable_host_haltpoll(void *i)
+{
+	wrmsrl(MSR_KVM_POLL_CONTROL, 0);
+}
+
+void kvm_enable_host_haltpoll(void *i)
+{
+	wrmsrl(MSR_KVM_POLL_CONTROL, 1);
+}
+
+void arch_haltpoll_enable(void)
+{
+	if (!kvm_para_has_feature(KVM_FEATURE_POLL_CONTROL))
+		return;
+
+	preempt_disable();
+	/* Enabling guest halt poll disables host halt poll */
+	kvm_disable_host_haltpoll(NULL);
+	smp_call_function(kvm_disable_host_haltpoll, NULL, 1);
+	preempt_enable();
+}
+EXPORT_SYMBOL_GPL(arch_haltpoll_enable);
+
+void arch_haltpoll_disable(void)
+{
+	if (!kvm_para_has_feature(KVM_FEATURE_POLL_CONTROL))
+		return;
+
+	preempt_disable();
+	/* Enabling guest halt poll disables host halt poll */
+	kvm_enable_host_haltpoll(NULL);
+	smp_call_function(kvm_enable_host_haltpoll, NULL, 1);
+	preempt_enable();
+}
+
+EXPORT_SYMBOL_GPL(arch_haltpoll_disable);
+#endif
```
#### [PATCH v2 07/22] docs: amd-memory-encryption.rst get rid of warnings
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c
Get rid of those warnings:

    Documentation/virtual/kvm/amd-memory-encryption.rst:244: WARNING: Citation [white-paper] is not referenced.
    Documentation/virtual/kvm/amd-memory-encryption.rst:246: WARNING: Citation [amd-apm] is not referenced.
    Documentation/virtual/kvm/amd-memory-encryption.rst:247: WARNING: Citation [kvm-forum] is not referenced.

For references that aren't mentioned at the text by adding an
explicit reference to them.

Signed-off-by: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virtual/kvm/amd-memory-encryption.rst | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v2 1/2] kvm: vmx: fix limit checking in get_vmx_mem_address()
##### From: Eugene Korenevsky <ekorenevsky@gmail.com>

```c
Intel SDM vol. 3, 5.3:
The processor causes a
general-protection exception (or, if the segment is SS, a stack-fault
exception) any time an attempt is made to access the following addresses
in a segment:
- A byte at an offset greater than the effective limit
- A word at an offset greater than the (effective-limit – 1)
- A doubleword at an offset greater than the (effective-limit – 3)
- A quadword at an offset greater than the (effective-limit – 7)

Therefore, the generic limit checking error condition must be

exn = off > limit + 1 - operand_len

but not

exn = off + operand_len > limit

as for now.

Signed-off-by: Eugene Korenevsky <ekorenevsky@gmail.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
