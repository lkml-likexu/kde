
\n
static inline void cond_local_irq_enable(struct pt_regs *regs)
static inline void cond_local_irq_disable(struct pt_regs *regs)
void ist_enter(struct pt_regs *regs)
void ist_exit(struct pt_regs *regs)
void ist_begin_non_atomic(struct pt_regs *regs)
void ist_end_non_atomic(void)
int is_valid_bugaddr(unsigned long addr)
int fixup_bug(struct pt_regs *regs, int trapnr)
static nokprobe_inline int do_trap_no_signal(struct task_struct *tsk, int trapnr, const char *str, struct pt_regs *regs, long error_code)
static void show_signal(struct task_struct *tsk, int signr, const char *type, const char *desc, struct pt_regs *regs, long error_code)
static void do_trap(int trapnr, int signr, char *str, struct pt_regs *regs, long error_code, int sicode, void __user *addr)
static void do_error_trap(struct pt_regs *regs, long error_code, char *str, unsigned long trapnr, int signr, int sicode, void __user *addr)
define IP ((void __user *)
uprobe_get_trap_addr(regs)
)
define DO_ERROR(trapnr, signr, sicode, addr, str, name)
\ dotraplinkage void do_name(struct pt_regs *regs, long error_code)
\ __visible void __noreturn handle_stack_overflow(const char *message, struct pt_regs *regs, unsigned long fault_address)
dotraplinkage void do_double_fault(struct pt_regs *regs, long error_code)
dotraplinkage void do_bounds(struct pt_regs *regs, long error_code)
dotraplinkage void do_general_protection(struct pt_regs *regs, long error_code)
dotraplinkage void notrace do_int3(struct pt_regs *regs, long error_code)
asmlinkage __visible notrace struct pt_regs *sync_regs(struct pt_regs *eregs)
asmlinkage __visible notrace struct bad_iret_stack *fixup_bad_iret(struct bad_iret_stack *s)
static bool is_sysenter_singlestep(struct pt_regs *regs)
dotraplinkage void do_debug(struct pt_regs *regs, long error_code)
static void math_error(struct pt_regs *regs, int error_code, int trapnr)
dotraplinkage void do_coprocessor_error(struct pt_regs *regs, long error_code)
dotraplinkage void do_simd_coprocessor_error(struct pt_regs *regs, long error_code)
dotraplinkage void do_spurious_interrupt_bug(struct pt_regs *regs, long error_code)
dotraplinkage void do_device_not_available(struct pt_regs *regs, long error_code)
dotraplinkage void do_iret_error(struct pt_regs *regs, long error_code)
void __init trap_init(void)
\n
     24 struct pt_regs *regs
     15 long error_code
      4 int trapnr
      3 int signr
      2 void __user *addr
      2 void
      2 struct task_struct *tsk
      2 int sicode
      2 char *str
      1 void __user *
      1 unsigned long trapnr
      1 unsigned long fault_address
      1 unsigned long addr
      1 trapnr
      1 struct pt_regs *eregs
      1 struct bad_iret_stack *s
      1 str
      1 signr
      1 sicode
      1 regs
      1 name
      1 int error_code
      1 const char *type
      1 const char *str
      1 const char *message
      1 const char *desc
      1 addr
