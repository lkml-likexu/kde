
\n
static inline int ptrace_reparented(struct task_struct *child)
static inline void ptrace_unlink(struct task_struct *child)
static inline struct task_struct *ptrace_parent(struct task_struct *task)
static inline bool ptrace_event_enabled(struct task_struct *task, int event)
static inline void ptrace_event(int event, unsigned long message)
static inline void ptrace_event_pid(int event, struct pid *pid)
static inline void ptrace_init_task(struct task_struct *child, bool ptrace)
static inline void ptrace_release_task(struct task_struct *task)
static inline void user_enable_single_step(struct task_struct *task)
static inline void user_disable_single_step(struct task_struct *task)
static inline void user_enable_block_step(struct task_struct *task)
extern void user_single_step_report(struct pt_regs *regs)
; static inline void user_single_step_report(struct pt_regs *regs)
\n
      6 struct task_struct *task
      3 struct task_struct *child
      3 int event
      2 struct pt_regs *regs
      1 unsigned long message
      1 struct pid *pid
      1 bool ptrace
