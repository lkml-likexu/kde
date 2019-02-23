
EXPORT_SYMBOL_GPL(do_exit);
\n
static void __unhash_process(struct task_struct *p, bool group_dead)
static void __exit_signal(struct task_struct *tsk)
static void delayed_put_task_struct(struct rcu_head *rhp)
void release_task(struct task_struct *p)
struct task_struct *task_rcu_dereference(struct task_struct **ptask)
void rcuwait_wake_up(struct rcuwait *w)
static int will_become_orphaned_pgrp(struct pid *pgrp, struct task_struct *ignored_task)
int is_current_pgrp_orphaned(void)
static bool has_stopped_jobs(struct pid *pgrp)
static void kill_orphaned_pgrp(struct task_struct *tsk, struct task_struct *parent)
void mm_update_next_owner(struct mm_struct *mm)
static void exit_mm(void)
static struct task_struct *find_alive_thread(struct task_struct *p)
static struct task_struct *find_child_reaper(struct task_struct *father, struct list_head *dead)
__releases(&tasklist_lock)
__acquires(&tasklist_lock)
static struct task_struct *find_new_reaper(struct task_struct *father, struct task_struct *child_reaper)
static void reparent_leader(struct task_struct *father, struct task_struct *p, struct list_head *dead)
static void forget_original_parent(struct task_struct *father, struct list_head *dead)
static void exit_notify(struct task_struct *tsk, int group_dead)
static void check_stack_usage(void)
void __noreturn do_exit(long code)
void complete_and_exit(struct completion *comp, long code)
SYSCALL_DEFINE1(exit, int, error_code)
void do_group_exit(int exit_code)
SYSCALL_DEFINE1(exit_group, int, error_code)
static int eligible_pid(struct wait_opts *wo, struct task_struct *p)
static int eligible_child(struct wait_opts *wo, bool ptrace, struct task_struct *p)
static int wait_task_zombie(struct wait_opts *wo, struct task_struct *p)
static int *task_stopped_code(struct task_struct *p, bool ptrace)
static int wait_task_stopped(struct wait_opts *wo, int ptrace, struct task_struct *p)
static int wait_task_continued(struct wait_opts *wo, struct task_struct *p)
static int wait_consider_task(struct wait_opts *wo, int ptrace, struct task_struct *p)
static int do_wait_thread(struct wait_opts *wo, struct task_struct *tsk)
static int ptrace_do_wait(struct wait_opts *wo, struct task_struct *tsk)
static int child_wait_callback(wait_queue_entry_t *wait, unsigned mode, int sync, void *key)
void __wake_up_parent(struct task_struct *p, struct task_struct *parent)
static long do_wait(struct wait_opts *wo)
static long kernel_waitid(int which, pid_t upid, struct waitid_info *infop, int options, struct rusage *ru)
SYSCALL_DEFINE5(waitid, int, which, pid_t, upid, struct siginfo __user *, infop, int, options, struct rusage __user *, ru)
long kernel_wait4(pid_t upid, int __user *stat_addr, int options, struct rusage *ru)
SYSCALL_DEFINE4(wait4, pid_t, upid, int __user *, stat_addr, int, options, struct rusage __user *, ru)
SYSCALL_DEFINE3(waitpid, pid_t, pid, int __user *, stat_addr, int, options)
COMPAT_SYSCALL_DEFINE4(wait4, compat_pid_t, pid, compat_uint_t __user *, stat_addr, int, options, struct compat_rusage __user *, ru)
COMPAT_SYSCALL_DEFINE5(waitid, int, which, compat_pid_t, pid, struct compat_siginfo __user *, infop, int, options, struct compat_rusage __user *, uru)
__weak void abort(void)
\n
     12 struct task_struct *p
      9 struct wait_opts *wo
      9 int
      5 struct task_struct *tsk
      5 options
      4 void
      4 struct task_struct *father
      3 struct list_head *dead
      3 stat_addr
      3 ru
      3 pid_t
      3 pid
      2 which
      2 waitid
      2 wait4
      2 upid
      2 &tasklist_lock
      2 struct task_struct *parent
      2 struct rusage __user *
      2 struct rusage *ru
      2 struct pid *pgrp
      2 struct compat_rusage __user *
      2 pid_t upid
      2 long code
      2 int __user *
      2 int ptrace
      2 int options
      2 infop
      2 error_code
      2 compat_pid_t
      2 bool ptrace
      1 wait_queue_entry_t *wait
      1 waitpid
      1 void *key
      1 uru
      1 unsigned mode
      1 struct waitid_info *infop
      1 struct task_struct **ptask
      1 struct task_struct *ignored_task
      1 struct task_struct *child_reaper
      1 struct siginfo __user *
      1 struct rcuwait *w
      1 struct rcu_head *rhp
      1 struct mm_struct *mm
      1 struct completion *comp
      1 struct compat_siginfo __user *
      1 int which
      1 int __user *stat_addr
      1 int sync
      1 int group_dead
      1 int exit_code
      1 exit_group
      1 exit
      1 do_exit
      1 compat_uint_t __user *
      1 bool group_dead
