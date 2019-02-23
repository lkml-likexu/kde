
\n
static inline struct pid *task_pid(struct task_struct *task)
static inline pid_t task_pid_nr(struct task_struct *tsk)
static inline pid_t task_pid_nr_ns(struct task_struct *tsk, struct pid_namespace *ns)
static inline pid_t task_pid_vnr(struct task_struct *tsk)
static inline pid_t task_tgid_nr(struct task_struct *tsk)
static inline int pid_alive(const struct task_struct *p)
static inline pid_t task_pgrp_nr_ns(struct task_struct *tsk, struct pid_namespace *ns)
static inline pid_t task_pgrp_vnr(struct task_struct *tsk)
static inline pid_t task_session_nr_ns(struct task_struct *tsk, struct pid_namespace *ns)
static inline pid_t task_session_vnr(struct task_struct *tsk)
static inline pid_t task_tgid_nr_ns(struct task_struct *tsk, struct pid_namespace *ns)
static inline pid_t task_tgid_vnr(struct task_struct *tsk)
static inline pid_t task_ppid_nr_ns(const struct task_struct *tsk, struct pid_namespace *ns)
static inline pid_t task_ppid_nr(const struct task_struct *tsk)
static inline pid_t task_pgrp_nr(struct task_struct *tsk)
static inline unsigned int task_state_index(struct task_struct *tsk)
static inline char task_index_to_char(unsigned int state)
static inline char task_state_to_char(struct task_struct *tsk)
static inline int is_global_init(struct task_struct *tsk)
static inline bool is_percpu_thread(void)
static inline void current_restore_flags(unsigned long orig_flags, unsigned long flags)
extern int cpuset_cpumask_can_shrink(const struct cpumask *cur, const struct cpumask *trial)
; extern int task_can_attach(struct task_struct *p, const struct cpumask *cs_cpus_allowed)
; extern void do_set_cpus_allowed(struct task_struct *p, const struct cpumask *new_mask)
; extern int set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask)
; static inline void do_set_cpus_allowed(struct task_struct *p, const struct cpumask *new_mask)
extern int cpuset_cpumask_can_shrink(const struct cpumask *cur, const struct cpumask *trial)
; extern int task_can_attach(struct task_struct *p, const struct cpumask *cs_cpus_allowed)
; extern void do_set_cpus_allowed(struct task_struct *p, const struct cpumask *new_mask)
; extern int set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask)
; static inline void do_set_cpus_allowed(struct task_struct *p, const struct cpumask *new_mask)
} static inline int set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask)
static inline int task_nice(const struct task_struct *p)
static inline bool is_idle_task(const struct task_struct *p)
static inline struct thread_info *task_thread_info(struct task_struct *task)
static inline void set_task_comm(struct task_struct *tsk, const char *from)
void scheduler_ipi(void)
; extern unsigned long wait_task_inactive(struct task_struct *, long match_state)
; static inline unsigned long wait_task_inactive(struct task_struct *p, long match_state)
static inline void set_tsk_thread_flag(struct task_struct *tsk, int flag)
static inline void clear_tsk_thread_flag(struct task_struct *tsk, int flag)
static inline void update_tsk_thread_flag(struct task_struct *tsk, int flag, bool value)
static inline int test_and_set_tsk_thread_flag(struct task_struct *tsk, int flag)
static inline int test_and_clear_tsk_thread_flag(struct task_struct *tsk, int flag)
static inline int test_tsk_thread_flag(struct task_struct *tsk, int flag)
static inline void set_tsk_need_resched(struct task_struct *tsk)
static inline void clear_tsk_need_resched(struct task_struct *tsk)
static inline int test_tsk_need_resched(struct task_struct *tsk)
static inline void cond_resched_rcu(void)
static inline int spin_needbreak(spinlock_t *lock)
static __always_inline bool need_resched(void)
static inline unsigned int task_cpu(const struct task_struct *p)
static inline unsigned int task_cpu(const struct task_struct *p)
static inline void set_task_cpu(struct task_struct *p, unsigned int cpu)
static inline void rseq_set_notify_resume(struct task_struct *t)
static inline void rseq_handle_notify_resume(struct ksignal *ksig, struct pt_regs *regs)
static inline void rseq_signal_deliver(struct ksignal *ksig, struct pt_regs *regs)
static inline void rseq_preempt(struct task_struct *t)
static inline void rseq_migrate(struct task_struct *t)
static inline void rseq_fork(struct task_struct *t, unsigned long clone_flags)
static inline void rseq_execve(struct task_struct *t)
static inline void rseq_set_notify_resume(struct task_struct *t)
static inline void rseq_set_notify_resume(struct task_struct *t)
} static inline void rseq_handle_notify_resume(struct ksignal *ksig, struct pt_regs *regs)
static inline void rseq_set_notify_resume(struct task_struct *t)
} static inline void rseq_handle_notify_resume(struct ksignal *ksig, struct pt_regs *regs)
} static inline void rseq_signal_deliver(struct ksignal *ksig, struct pt_regs *regs)
static inline void rseq_set_notify_resume(struct task_struct *t)
} static inline void rseq_handle_notify_resume(struct ksignal *ksig, struct pt_regs *regs)
} static inline void rseq_signal_deliver(struct ksignal *ksig, struct pt_regs *regs)
} static inline void rseq_preempt(struct task_struct *t)
static inline void rseq_set_notify_resume(struct task_struct *t)
} static inline void rseq_handle_notify_resume(struct ksignal *ksig, struct pt_regs *regs)
} static inline void rseq_signal_deliver(struct ksignal *ksig, struct pt_regs *regs)
} static inline void rseq_preempt(struct task_struct *t)
} static inline void rseq_migrate(struct task_struct *t)
static inline void rseq_set_notify_resume(struct task_struct *t)
} static inline void rseq_handle_notify_resume(struct ksignal *ksig, struct pt_regs *regs)
} static inline void rseq_signal_deliver(struct ksignal *ksig, struct pt_regs *regs)
} static inline void rseq_preempt(struct task_struct *t)
} static inline void rseq_migrate(struct task_struct *t)
} static inline void rseq_fork(struct task_struct *t, unsigned long clone_flags)
static inline void rseq_set_notify_resume(struct task_struct *t)
} static inline void rseq_handle_notify_resume(struct ksignal *ksig, struct pt_regs *regs)
} static inline void rseq_signal_deliver(struct ksignal *ksig, struct pt_regs *regs)
} static inline void rseq_preempt(struct task_struct *t)
} static inline void rseq_migrate(struct task_struct *t)
} static inline void rseq_fork(struct task_struct *t, unsigned long clone_flags)
} static inline void rseq_execve(struct task_struct *t)
static inline void exit_umh(struct task_struct *tsk)
static inline void rseq_syscall(struct pt_regs *regs)
\n
     25 struct task_struct *tsk
     22 struct task_struct *t
     14 struct pt_regs *regs
     13 struct ksignal *ksig
     11 struct task_struct *p
      7 const struct cpumask *new_mask
      6 int flag
      5 struct pid_namespace *ns
      5 const struct task_struct *p
      4 void
      3 unsigned long clone_flags
      2 struct task_struct *task
      2 long match_state
      2 const struct task_struct *tsk
      2 const struct cpumask *trial
      2 const struct cpumask *cur
      2 const struct cpumask *cs_cpus_allowed
      1 unsigned long orig_flags
      1 unsigned long flags
      1 unsigned int state
      1 unsigned int cpu
      1 struct task_struct *
      1 spinlock_t *lock
      1 const char *from
      1 bool value
