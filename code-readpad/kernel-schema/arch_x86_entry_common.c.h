
\n
__visible inline void enter_from_user_mode(void)
static void do_audit_syscall_entry(struct pt_regs *regs, u32 arch)
static long syscall_trace_enter(struct pt_regs *regs)
static void exit_to_usermode_loop(struct pt_regs *regs, u32 cached_flags)
__visible inline void prepare_exit_to_usermode(struct pt_regs *regs)
static void syscall_slow_exit_work(struct pt_regs *regs, u32 cached_flags)
__visible inline void syscall_return_slowpath(struct pt_regs *regs)
__visible void do_syscall_64(unsigned long nr, struct pt_regs *regs)
static __always_inline void do_syscall_32_irqs_on(struct pt_regs *regs)
__visible void do_int80_syscall_32(struct pt_regs *regs)
__visible long do_fast_syscall_32(struct pt_regs *regs)
\n
     10 struct pt_regs *regs
      2 u32 cached_flags
      1 void
      1 unsigned long nr
      1 u32 arch
