
EXPORT_SYMBOL_GPL(start_thread);
\n
void __show_regs(struct pt_regs *regs, enum show_regs_mode mode)
void release_thread(struct task_struct *dead_task)
int copy_thread_tls(unsigned long clone_flags, unsigned long sp, unsigned long arg, struct task_struct *p, unsigned long tls)
void start_thread(struct pt_regs *regs, unsigned long new_ip, unsigned long new_sp)
__visible __notrace_funcgraph struct task_struct * __switch_to(struct task_struct *prev_p, struct task_struct *next_p)
SYSCALL_DEFINE2(arch_prctl, int, option, unsigned long, arg2)
\n
      2 struct pt_regs *regs
      1 unsigned long tls
      1 unsigned long sp
      1 unsigned long new_sp
      1 unsigned long new_ip
      1 unsigned long clone_flags
      1 unsigned long arg
      1 unsigned long
      1 struct task_struct *prev_p
      1 struct task_struct *p
      1 struct task_struct *next_p
      1 struct task_struct *dead_task
      1 start_thread
      1 option
      1 int
      1 enum show_regs_mode mode
      1 arg2
      1 arch_prctl
