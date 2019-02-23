#### [PATCH 1/4 v2][KVM nVMX]: Add a vmentry check for HOST_SYSENTER_ESP and HOST_SYSENTER_EIP fields
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on VMX Controls" in Intel SDM vol 3C, the
following check is performed on vmentry of L2 guests:

    On processors that support Intel 64 architecture, the IA32_SYSENTER_ESP
    field and the IA32_SYSENTER_EIP field must each contain a canonical
    address.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH v2 01/27] KVM: Call kvm_arch_memslots_updated() before updating memslots
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
kvm_arch_memslots_updated() is at this point in time an x86-specific
hook for handling MMIO generation wraparound.  x86 stashes 19 bits of
the memslots generation number in its MMIO sptes in order to avoid
full page fault walks for repeat faults on emulated MMIO addresses.
Because only 19 bits are used, wrapping the MMIO generation number is
possible, if unlikely.  kvm_arch_memslots_updated() alerts x86 that
the generation has changed so that it can invalidate all MMIO sptes in
case the effective MMIO generation has wrapped so as to avoid using a
stale spte, e.g. a (very) old spte that was created with generation==0.

Given that the purpose of kvm_arch_memslots_updated() is to prevent
consuming stale entries, it needs to be called before the new generation
is propagated to memslots.  Invalidating the MMIO sptes after updating
memslots means that there is a window where a vCPU could dereference
the new memslots generation, e.g. 0, and incorrectly reuse an old MMIO
spte that was created with (pre-wrap) generation==0.

Fixes: e59dbe09f8e6 ("KVM: Introduce kvm_arch_memslots_updated()")
Cc: <stable@vger.kernel.org>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/mips/include/asm/kvm_host.h    | 2 +-
 arch/powerpc/include/asm/kvm_host.h | 2 +-
 arch/s390/include/asm/kvm_host.h    | 2 +-
 arch/x86/include/asm/kvm_host.h     | 2 +-
 arch/x86/kvm/mmu.c                  | 4 ++--
 arch/x86/kvm/x86.c                  | 4 ++--
 include/linux/kvm_host.h            | 2 +-
 virt/kvm/arm/mmu.c                  | 2 +-
 virt/kvm/kvm_main.c                 | 7 +++++--
 9 files changed, 15 insertions(+), 12 deletions(-)

```
#### [PATCH 05/22 v2] x86/fpu: Remove fpu->initialized usage in copy_fpstate_to_sigframe()
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
With lazy-FPU support the (now named variable) ->initialized was set to true if
the CPU's FPU registers were holding the a valid state of the FPU registers for
the active process. If it was set to false then the FPU state was saved in
fpu->state and the FPU was deactivated.
With lazy-FPU gone, ->initialized is always true for user threads and kernel
threads never this function so ->initialized is always true in
copy_fpstate_to_sigframe().
The using_compacted_format() check is also a leftover from the lazy-FPU time.
In the `->initialized == false' case copy_to_user() would copy the compacted
buffer while userland would expect the non-compacted format instead. So in
order to save the FPU state in the non-compacted form it issues the xsave
opcode to save the *current* FPU state.
The FPU is not enabled so the attempt raises the FPU trap, the trap restores
the FPU content and re-enables the FPU and the xsave opcode is invoked again and
succeeds. *This* does not longer work since commit

  bef8b6da9522 ("x86/fpu: Handle #NM without FPU emulation as an error")

Remove check for ->initialized because it is always true and remove the
false condition. Update the comment to reflect that the "state is always live".

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
v1…v2: rewrite the patch description.

 arch/x86/kernel/fpu/signal.c | 30 ++++++------------------------
 1 file changed, 6 insertions(+), 24 deletions(-)

Index: staging/arch/x86/kernel/fpu/signal.c
===================================================================
--- staging.orig/arch/x86/kernel/fpu/signal.c
+++ staging/arch/x86/kernel/fpu/signal.c
@@ -144,9 +144,8 @@ static inline int copy_fpregs_to_sigfram
  *	buf == buf_fx for 64-bit frames and 32-bit fsave frame.
  *	buf != buf_fx for 32-bit frames with fxstate.
  *
- * If the fpu, extended register state is live, save the state directly
- * to the user frame pointed by the aligned pointer 'buf_fx'. Otherwise,
- * copy the thread's fpu state to the user frame starting at 'buf_fx'.
+ * Save the state directly to the user frame pointed by the aligned pointer
+ * 'buf_fx'.
  *
  * If this is a 32-bit frame with fxstate, put a fsave header before
  * the aligned state at 'buf_fx'.
@@ -157,7 +156,6 @@ static inline int copy_fpregs_to_sigfram
 int copy_fpstate_to_sigframe(void __user *buf, void __user *buf_fx, int size)
 {
 	struct fpu *fpu = &current->thread.fpu;
-	struct xregs_state *xsave = &fpu->state.xsave;
 	struct task_struct *tsk = current;
 	int ia32_fxstate = (buf != buf_fx);
 
@@ -172,29 +170,12 @@ int copy_fpstate_to_sigframe(void __user
 			sizeof(struct user_i387_ia32_struct), NULL,
 			(struct _fpstate_32 __user *) buf) ? -1 : 1;
 
-	if (fpu->initialized || using_compacted_format()) {
-		/* Save the live register state to the user directly. */
-		if (copy_fpregs_to_sigframe(buf_fx))
-			return -1;
-		/* Update the thread's fxstate to save the fsave header. */
-		if (ia32_fxstate)
-			copy_fxregs_to_kernel(fpu);
-	} else {
-		/*
-		 * It is a *bug* if kernel uses compacted-format for xsave
-		 * area and we copy it out directly to a signal frame. It
-		 * should have been handled above by saving the registers
-		 * directly.
-		 */
-		if (boot_cpu_has(X86_FEATURE_XSAVES)) {
-			WARN_ONCE(1, "x86/fpu: saving compacted-format xsave area to a signal frame!\n");
-			return -1;
-		}
-
-		fpstate_sanitize_xstate(fpu);
-		if (__copy_to_user(buf_fx, xsave, fpu_user_xstate_size))
-			return -1;
-	}
+	/* Save the live register state to the user directly. */
+	if (copy_fpregs_to_sigframe(buf_fx))
+		return -1;
+	/* Update the thread's fxstate to save the fsave header. */
+	if (ia32_fxstate)
+		copy_fxregs_to_kernel(fpu);
 
 	/* Save the fsave header for the 32-bit frames. */
 	if ((ia32_fxstate || !use_fxsr()) && save_fsave_header(tsk, buf))
```
#### [PATCH 06/22 v2] x86/fpu: Don't save fxregs for ia32 frames in
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
In commit 

  72a671ced66db ("x86, fpu: Unify signal handling code paths for x86 and x86_64 kernels")

the 32bit and 64bit path of the signal delivery code were merged. The 32bit version:
|int save_i387_xstate_ia32(void __user *buf)
|…
|       if (cpu_has_xsave)
|               return save_i387_xsave(fp);
|       if (cpu_has_fxsr)
|               return save_i387_fxsave(fp);

The 64bit version:
|int save_i387_xstate(void __user *buf)
|…
|       if (user_has_fpu()) {
|               if (use_xsave())
|                       err = xsave_user(buf);
|               else
|                       err = fxsave_user(buf);
|
|               if (unlikely(err)) {
|                       __clear_user(buf, xstate_size);
|                       return err;

The merge:
|int save_xstate_sig(void __user *buf, void __user *buf_fx, int size)
|…
|       if (user_has_fpu()) {
|               /* Save the live register state to the user directly. */
|               if (save_user_xstate(buf_fx))
|                       return -1;
|               /* Update the thread's fxstate to save the fsave header. */
|               if (ia32_fxstate)
|                       fpu_fxsave(&tsk->thread.fpu);

I don't think that we needed to save the FPU registers to ->thread.fpu because
the registers were stored in `buf_fx'. Today the state will be restored from
`buf_fx' after the signal was handled (I assume that this was also the case
with lazy-FPU). Since commit

  66463db4fc560 ("x86, fpu: shift drop_init_fpu() from save_xstate_sig() to handle_signal()")

it is ensured that the signal handler starts with clear/fresh set of FPU
registers which means that the previous store is futile.

Remove copy_fxregs_to_kernel() because task's FPU state is cleared later in
handle_signal() via fpu__clear().

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
v1…v2:
 - reworte description. Replaced the "I don't know why it is like it is
   makes no sense buh" part with some pointer which might explain why
   copy_fxregs_to_kernel() ended there and since when it definitely is a
   nop.
 - removed `fpu' since it unused after that change.

 arch/x86/kernel/fpu/signal.c | 3 ---
 1 file changed, 3 deletions(-)

Index: staging/arch/x86/kernel/fpu/signal.c
===================================================================
--- staging.orig/arch/x86/kernel/fpu/signal.c
+++ staging/arch/x86/kernel/fpu/signal.c
@@ -155,7 +155,6 @@ static inline int copy_fpregs_to_sigfram
  */
 int copy_fpstate_to_sigframe(void __user *buf, void __user *buf_fx, int size)
 {
-	struct fpu *fpu = &current->thread.fpu;
 	struct task_struct *tsk = current;
 	int ia32_fxstate = (buf != buf_fx);
 
@@ -173,9 +172,6 @@ int copy_fpstate_to_sigframe(void __user
 	/* Save the live register state to the user directly. */
 	if (copy_fpregs_to_sigframe(buf_fx))
 		return -1;
-	/* Update the thread's fxstate to save the fsave header. */
-	if (ia32_fxstate)
-		copy_fxregs_to_kernel(fpu);
 
 	/* Save the fsave header for the 32-bit frames. */
 	if ((ia32_fxstate || !use_fxsr()) && save_fsave_header(tsk, buf))
```
#### [PATCH 07/22 v2] x86/fpu: Remove fpu->initialized
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
The `initialized' member of the fpu struct is always set to one for user
tasks and zero for kernel tasks. This avoids saving/restoring the FPU
registers for kernel threads.

The ->initialized = 0 case for user tasks has been removed in previous changes
for instance by always an explicit init at fork() time for FPU-less system which
was otherwise delayed until the emulated opcode.

The context switch code (switch_fpu_prepare() + switch_fpu_finish())
can't unconditionally save/restore registers for kernel threads. Not only would
it slow down switch but also load a zeroed xcomp_bv for the XSAVES.

For kernel_fpu_begin() (+end) the situation is similar: EFI with runtime
services uses this before alternatives_patched is true. Which means that this
function is used too early and it wasn't the case before.

For those two cases current->mm is used to determine between user &
kernel thread. For kernel_fpu_begin() we skip save/restore of the FPU
registers.
During the context switch into a kernel thread we don't do anything.
There is no reason to save the FPU state of a kernel thread.
The reordering in __switch_to() is important because the current() pointer
needs to be valid before switch_fpu_finish() is invoked so ->mm is seen of the
new task instead the old one.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
v1…v2:
  - patch description changes.
  - dropping brackets around a single statement in fpu__save().

 arch/x86/ia32/ia32_signal.c         | 17 +++-----
 arch/x86/include/asm/fpu/internal.h | 15 +++----
 arch/x86/include/asm/fpu/types.h    |  9 ----
 arch/x86/include/asm/trace/fpu.h    |  5 +--
 arch/x86/kernel/fpu/core.c          | 68 ++++++++---------------------
 arch/x86/kernel/fpu/init.c          |  2 -
 arch/x86/kernel/fpu/regset.c        | 19 ++------
 arch/x86/kernel/fpu/xstate.c        |  2 -
 arch/x86/kernel/process_32.c        |  4 +-
 arch/x86/kernel/process_64.c        |  4 +-
 arch/x86/kernel/signal.c            | 17 +++-----
 arch/x86/mm/pkeys.c                 |  7 +--
 12 files changed, 49 insertions(+), 120 deletions(-)

Index: staging/arch/x86/ia32/ia32_signal.c
===================================================================
--- staging.orig/arch/x86/ia32/ia32_signal.c
+++ staging/arch/x86/ia32/ia32_signal.c
@@ -216,8 +216,7 @@ static void __user *get_sigframe(struct
 				 size_t frame_size,
 				 void __user **fpstate)
 {
-	struct fpu *fpu = &current->thread.fpu;
-	unsigned long sp;
+	unsigned long sp, fx_aligned, math_size;
 
 	/* Default to using normal stack */
 	sp = regs->sp;
@@ -231,15 +230,11 @@ static void __user *get_sigframe(struct
 		 ksig->ka.sa.sa_restorer)
 		sp = (unsigned long) ksig->ka.sa.sa_restorer;
 
-	if (fpu->initialized) {
-		unsigned long fx_aligned, math_size;
-
-		sp = fpu__alloc_mathframe(sp, 1, &fx_aligned, &math_size);
-		*fpstate = (struct _fpstate_32 __user *) sp;
-		if (copy_fpstate_to_sigframe(*fpstate, (void __user *)fx_aligned,
-				    math_size) < 0)
-			return (void __user *) -1L;
-	}
+	sp = fpu__alloc_mathframe(sp, 1, &fx_aligned, &math_size);
+	*fpstate = (struct _fpstate_32 __user *) sp;
+	if (copy_fpstate_to_sigframe(*fpstate, (void __user *)fx_aligned,
+				     math_size) < 0)
+		return (void __user *) -1L;
 
 	sp -= frame_size;
 	/* Align the stack pointer according to the i386 ABI,
Index: staging/arch/x86/include/asm/fpu/internal.h
===================================================================
--- staging.orig/arch/x86/include/asm/fpu/internal.h
+++ staging/arch/x86/include/asm/fpu/internal.h
@@ -525,11 +525,14 @@ static inline void fpregs_activate(struc
  *
  *  - switch_fpu_finish() restores the new state as
  *    necessary.
+ *
+ * The FPU context is only stored/restore for user task and ->mm is used to
+ * distinguish between kernel and user threads.
  */
 static inline void
 switch_fpu_prepare(struct fpu *old_fpu, int cpu)
 {
-	if (static_cpu_has(X86_FEATURE_FPU) && old_fpu->initialized) {
+	if (static_cpu_has(X86_FEATURE_FPU) && current->mm) {
 		if (!copy_fpregs_to_fpstate(old_fpu))
 			old_fpu->last_cpu = -1;
 		else
@@ -537,8 +540,7 @@ switch_fpu_prepare(struct fpu *old_fpu,
 
 		/* But leave fpu_fpregs_owner_ctx! */
 		trace_x86_fpu_regs_deactivated(old_fpu);
-	} else
-		old_fpu->last_cpu = -1;
+	}
 }
 
 /*
@@ -551,12 +553,12 @@ switch_fpu_prepare(struct fpu *old_fpu,
  */
 static inline void switch_fpu_finish(struct fpu *new_fpu, int cpu)
 {
-	bool preload = static_cpu_has(X86_FEATURE_FPU) &&
-		       new_fpu->initialized;
+	if (static_cpu_has(X86_FEATURE_FPU)) {
+		if (!fpregs_state_valid(new_fpu, cpu)) {
+			if (current->mm)
+				copy_kernel_to_fpregs(&new_fpu->state);
+		}
 
-	if (preload) {
-		if (!fpregs_state_valid(new_fpu, cpu))
-			copy_kernel_to_fpregs(&new_fpu->state);
 		fpregs_activate(new_fpu);
 	}
 }
Index: staging/arch/x86/include/asm/fpu/types.h
===================================================================
--- staging.orig/arch/x86/include/asm/fpu/types.h
+++ staging/arch/x86/include/asm/fpu/types.h
@@ -294,15 +294,6 @@ struct fpu {
 	unsigned int			last_cpu;
 
 	/*
-	 * @initialized:
-	 *
-	 * This flag indicates whether this context is initialized: if the task
-	 * is not running then we can restore from this context, if the task
-	 * is running then we should save into this context.
-	 */
-	unsigned char			initialized;
-
-	/*
 	 * @state:
 	 *
 	 * In-memory copy of all FPU registers that we save/restore
Index: staging/arch/x86/include/asm/trace/fpu.h
===================================================================
--- staging.orig/arch/x86/include/asm/trace/fpu.h
+++ staging/arch/x86/include/asm/trace/fpu.h
@@ -13,22 +13,19 @@ DECLARE_EVENT_CLASS(x86_fpu,
 
 	TP_STRUCT__entry(
 		__field(struct fpu *, fpu)
-		__field(bool, initialized)
 		__field(u64, xfeatures)
 		__field(u64, xcomp_bv)
 		),
 
 	TP_fast_assign(
 		__entry->fpu		= fpu;
-		__entry->initialized	= fpu->initialized;
 		if (boot_cpu_has(X86_FEATURE_OSXSAVE)) {
 			__entry->xfeatures = fpu->state.xsave.header.xfeatures;
 			__entry->xcomp_bv  = fpu->state.xsave.header.xcomp_bv;
 		}
 	),
-	TP_printk("x86/fpu: %p initialized: %d xfeatures: %llx xcomp_bv: %llx",
+	TP_printk("x86/fpu: %p xfeatures: %llx xcomp_bv: %llx",
 			__entry->fpu,
-			__entry->initialized,
 			__entry->xfeatures,
 			__entry->xcomp_bv
 	)
Index: staging/arch/x86/kernel/fpu/core.c
===================================================================
--- staging.orig/arch/x86/kernel/fpu/core.c
+++ staging/arch/x86/kernel/fpu/core.c
@@ -101,7 +101,7 @@ static void __kernel_fpu_begin(void)
 
 	kernel_fpu_disable();
 
-	if (fpu->initialized) {
+	if (current->mm) {
 		/*
 		 * Ignore return value -- we don't care if reg state
 		 * is clobbered.
@@ -116,7 +116,7 @@ static void __kernel_fpu_end(void)
 {
 	struct fpu *fpu = &current->thread.fpu;
 
-	if (fpu->initialized)
+	if (current->mm)
 		copy_kernel_to_fpregs(&fpu->state);
 
 	kernel_fpu_enable();
@@ -147,11 +147,10 @@ void fpu__save(struct fpu *fpu)
 
 	preempt_disable();
 	trace_x86_fpu_before_save(fpu);
-	if (fpu->initialized) {
-		if (!copy_fpregs_to_fpstate(fpu)) {
-			copy_kernel_to_fpregs(&fpu->state);
-		}
-	}
+
+	if (!copy_fpregs_to_fpstate(fpu))
+		copy_kernel_to_fpregs(&fpu->state);
+
 	trace_x86_fpu_after_save(fpu);
 	preempt_enable();
 }
@@ -190,7 +189,7 @@ int fpu__copy(struct fpu *dst_fpu, struc
 {
 	dst_fpu->last_cpu = -1;
 
-	if (!src_fpu->initialized || !static_cpu_has(X86_FEATURE_FPU))
+	if (!static_cpu_has(X86_FEATURE_FPU))
 		return 0;
 
 	WARN_ON_FPU(src_fpu != &current->thread.fpu);
@@ -227,14 +226,10 @@ static void fpu__initialize(struct fpu *
 {
 	WARN_ON_FPU(fpu != &current->thread.fpu);
 
-	if (!fpu->initialized) {
-		fpstate_init(&fpu->state);
-		trace_x86_fpu_init_state(fpu);
-
-		trace_x86_fpu_activate_state(fpu);
-		/* Safe to do for the current task: */
-		fpu->initialized = 1;
-	}
+	fpstate_init(&fpu->state);
+	trace_x86_fpu_init_state(fpu);
+
+	trace_x86_fpu_activate_state(fpu);
 }
 
 /*
@@ -247,32 +242,20 @@ static void fpu__initialize(struct fpu *
  *
  * - or it's called for stopped tasks (ptrace), in which case the
  *   registers were already saved by the context-switch code when
- *   the task scheduled out - we only have to initialize the registers
- *   if they've never been initialized.
+ *   the task scheduled out.
  *
  * If the task has used the FPU before then save it.
  */
 void fpu__prepare_read(struct fpu *fpu)
 {
-	if (fpu == &current->thread.fpu) {
+	if (fpu == &current->thread.fpu)
 		fpu__save(fpu);
-	} else {
-		if (!fpu->initialized) {
-			fpstate_init(&fpu->state);
-			trace_x86_fpu_init_state(fpu);
-
-			trace_x86_fpu_activate_state(fpu);
-			/* Safe to do for current and for stopped child tasks: */
-			fpu->initialized = 1;
-		}
-	}
 }
 
 /*
  * This function must be called before we write a task's fpstate.
  *
- * If the task has used the FPU before then invalidate any cached FPU registers.
- * If the task has not used the FPU before then initialize its fpstate.
+ * Invalidate any cached FPU registers.
  *
  * After this function call, after registers in the fpstate are
  * modified and the child task has woken up, the child task will
@@ -289,17 +272,8 @@ void fpu__prepare_write(struct fpu *fpu)
 	 */
 	WARN_ON_FPU(fpu == &current->thread.fpu);
 
-	if (fpu->initialized) {
-		/* Invalidate any cached state: */
-		__fpu_invalidate_fpregs_state(fpu);
-	} else {
-		fpstate_init(&fpu->state);
-		trace_x86_fpu_init_state(fpu);
-
-		trace_x86_fpu_activate_state(fpu);
-		/* Safe to do for stopped child tasks: */
-		fpu->initialized = 1;
-	}
+	/* Invalidate any cached state: */
+	__fpu_invalidate_fpregs_state(fpu);
 }
 
 /*
@@ -316,17 +290,13 @@ void fpu__drop(struct fpu *fpu)
 	preempt_disable();
 
 	if (fpu == &current->thread.fpu) {
-		if (fpu->initialized) {
-			/* Ignore delayed exceptions from user space */
-			asm volatile("1: fwait\n"
-				     "2:\n"
-				     _ASM_EXTABLE(1b, 2b));
-			fpregs_deactivate(fpu);
-		}
+		/* Ignore delayed exceptions from user space */
+		asm volatile("1: fwait\n"
+			     "2:\n"
+			     _ASM_EXTABLE(1b, 2b));
+		fpregs_deactivate(fpu);
 	}
 
-	fpu->initialized = 0;
-
 	trace_x86_fpu_dropped(fpu);
 
 	preempt_enable();
Index: staging/arch/x86/kernel/fpu/init.c
===================================================================
--- staging.orig/arch/x86/kernel/fpu/init.c
+++ staging/arch/x86/kernel/fpu/init.c
@@ -239,8 +239,6 @@ static void __init fpu__init_system_ctx_
 
 	WARN_ON_FPU(!on_boot_cpu);
 	on_boot_cpu = 0;
-
-	WARN_ON_FPU(current->thread.fpu.initialized);
 }
 
 /*
Index: staging/arch/x86/kernel/fpu/regset.c
===================================================================
--- staging.orig/arch/x86/kernel/fpu/regset.c
+++ staging/arch/x86/kernel/fpu/regset.c
@@ -15,16 +15,12 @@
  */
 int regset_fpregs_active(struct task_struct *target, const struct user_regset *regset)
 {
-	struct fpu *target_fpu = &target->thread.fpu;
-
-	return target_fpu->initialized ? regset->n : 0;
+	return regset->n;
 }
 
 int regset_xregset_fpregs_active(struct task_struct *target, const struct user_regset *regset)
 {
-	struct fpu *target_fpu = &target->thread.fpu;
-
-	if (boot_cpu_has(X86_FEATURE_FXSR) && target_fpu->initialized)
+	if (boot_cpu_has(X86_FEATURE_FXSR))
 		return regset->n;
 	else
 		return 0;
@@ -370,16 +366,9 @@ int fpregs_set(struct task_struct *targe
 int dump_fpu(struct pt_regs *regs, struct user_i387_struct *ufpu)
 {
 	struct task_struct *tsk = current;
-	struct fpu *fpu = &tsk->thread.fpu;
-	int fpvalid;
-
-	fpvalid = fpu->initialized;
-	if (fpvalid)
-		fpvalid = !fpregs_get(tsk, NULL,
-				      0, sizeof(struct user_i387_ia32_struct),
-				      ufpu, NULL);
 
-	return fpvalid;
+	return !fpregs_get(tsk, NULL, 0, sizeof(struct user_i387_ia32_struct),
+			   ufpu, NULL);
 }
 EXPORT_SYMBOL(dump_fpu);
 
Index: staging/arch/x86/kernel/fpu/xstate.c
===================================================================
--- staging.orig/arch/x86/kernel/fpu/xstate.c
+++ staging/arch/x86/kernel/fpu/xstate.c
@@ -892,8 +892,6 @@ const void *get_xsave_field_ptr(int xsav
 {
 	struct fpu *fpu = &current->thread.fpu;
 
-	if (!fpu->initialized)
-		return NULL;
 	/*
 	 * fpu__save() takes the CPU's xstate registers
 	 * and saves them off to the 'fpu memory buffer.
Index: staging/arch/x86/kernel/process_32.c
===================================================================
--- staging.orig/arch/x86/kernel/process_32.c
+++ staging/arch/x86/kernel/process_32.c
@@ -288,10 +288,10 @@ __switch_to(struct task_struct *prev_p,
 	if (prev->gs | next->gs)
 		lazy_load_gs(next->gs);
 
-	switch_fpu_finish(next_fpu, cpu);
-
 	this_cpu_write(current_task, next_p);
 
+	switch_fpu_finish(next_fpu, cpu);
+
 	/* Load the Intel cache allocation PQR MSR. */
 	resctrl_sched_in();
 
Index: staging/arch/x86/kernel/process_64.c
===================================================================
--- staging.orig/arch/x86/kernel/process_64.c
+++ staging/arch/x86/kernel/process_64.c
@@ -566,14 +566,14 @@ __switch_to(struct task_struct *prev_p,
 
 	x86_fsgsbase_load(prev, next);
 
-	switch_fpu_finish(next_fpu, cpu);
-
 	/*
 	 * Switch the PDA and FPU contexts.
 	 */
 	this_cpu_write(current_task, next_p);
 	this_cpu_write(cpu_current_top_of_stack, task_top_of_stack(next_p));
 
+	switch_fpu_finish(next_fpu, cpu);
+
 	/* Reload sp0. */
 	update_task_stack(next_p);
 
Index: staging/arch/x86/kernel/signal.c
===================================================================
--- staging.orig/arch/x86/kernel/signal.c
+++ staging/arch/x86/kernel/signal.c
@@ -246,7 +246,7 @@ get_sigframe(struct k_sigaction *ka, str
 	unsigned long sp = regs->sp;
 	unsigned long buf_fx = 0;
 	int onsigstack = on_sig_stack(sp);
-	struct fpu *fpu = &current->thread.fpu;
+	int ret;
 
 	/* redzone */
 	if (IS_ENABLED(CONFIG_X86_64))
@@ -265,11 +265,9 @@ get_sigframe(struct k_sigaction *ka, str
 		sp = (unsigned long) ka->sa.sa_restorer;
 	}
 
-	if (fpu->initialized) {
-		sp = fpu__alloc_mathframe(sp, IS_ENABLED(CONFIG_X86_32),
-					  &buf_fx, &math_size);
-		*fpstate = (void __user *)sp;
-	}
+	sp = fpu__alloc_mathframe(sp, IS_ENABLED(CONFIG_X86_32),
+				  &buf_fx, &math_size);
+	*fpstate = (void __user *)sp;
 
 	sp = align_sigframe(sp - frame_size);
 
@@ -281,8 +279,8 @@ get_sigframe(struct k_sigaction *ka, str
 		return (void __user *)-1L;
 
 	/* save i387 and extended state */
-	if (fpu->initialized &&
-	    copy_fpstate_to_sigframe(*fpstate, (void __user *)buf_fx, math_size) < 0)
+	ret = copy_fpstate_to_sigframe(*fpstate, (void __user *)buf_fx, math_size);
+	if (ret < 0)
 		return (void __user *)-1L;
 
 	return (void __user *)sp;
@@ -763,8 +761,7 @@ handle_signal(struct ksignal *ksig, stru
 		/*
 		 * Ensure the signal handler starts with the new fpu state.
 		 */
-		if (fpu->initialized)
-			fpu__clear(fpu);
+		fpu__clear(fpu);
 	}
 	signal_setup_done(failed, ksig, stepping);
 }
Index: staging/arch/x86/mm/pkeys.c
===================================================================
--- staging.orig/arch/x86/mm/pkeys.c
+++ staging/arch/x86/mm/pkeys.c
@@ -39,17 +39,12 @@ int __execute_only_pkey(struct mm_struct
 	 * dance to set PKRU if we do not need to.  Check it
 	 * first and assume that if the execute-only pkey is
 	 * write-disabled that we do not have to set it
-	 * ourselves.  We need preempt off so that nobody
-	 * can make fpregs inactive.
+	 * ourselves.
 	 */
-	preempt_disable();
 	if (!need_to_set_mm_pkey &&
-	    current->thread.fpu.initialized &&
 	    !__pkru_allows_read(read_pkru(), execute_only_pkey)) {
-		preempt_enable();
 		return execute_only_pkey;
 	}
-	preempt_enable();
 
 	/*
 	 * Set up PKRU so that it denies access for everything
```
