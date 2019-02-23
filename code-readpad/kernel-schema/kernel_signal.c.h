
EXPORT_SYMBOL_GPL(dequeue_signal);
EXPORT_SYMBOL_GPL(kill_pid_info_as_cred);
\n
static void __user *sig_handler(struct task_struct *t, int sig)
static inline bool sig_handler_ignored(void __user *handler, int sig)
static bool sig_task_ignored(struct task_struct *t, int sig, bool force)
static bool sig_ignored(struct task_struct *t, int sig, bool force)
static inline bool has_pending_signals(sigset_t *signal, sigset_t *blocked)
static bool recalc_sigpending_tsk(struct task_struct *t)
void recalc_sigpending_and_wake(struct task_struct *t)
void recalc_sigpending(void)
void calculate_sigpending(void)
int next_signal(struct sigpending *pending, sigset_t *mask)
static inline void print_dropped_signal(int sig)
bool task_set_jobctl_pending(struct task_struct *task, unsigned long mask)
void task_clear_jobctl_trapping(struct task_struct *task)
void task_clear_jobctl_pending(struct task_struct *task, unsigned long mask)
static bool task_participate_group_stop(struct task_struct *task)
void task_join_group_stop(struct task_struct *task)
static struct sigqueue * __sigqueue_alloc(int sig, struct task_struct *t, gfp_t flags, int override_rlimit)
static void __sigqueue_free(struct sigqueue *q)
void flush_sigqueue(struct sigpending *queue)
void flush_signals(struct task_struct *t)
static void __flush_itimer_signals(struct sigpending *pending)
void flush_itimer_signals(void)
void ignore_signals(struct task_struct *t)
void flush_signal_handlers(struct task_struct *t, int force_default)
bool unhandled_signal(struct task_struct *tsk, int sig)
static void collect_signal(int sig, struct sigpending *list, kernel_siginfo_t *info, bool *resched_timer)
static int __dequeue_signal(struct sigpending *pending, sigset_t *mask, kernel_siginfo_t *info, bool *resched_timer)
int dequeue_signal(struct task_struct *tsk, sigset_t *mask, kernel_siginfo_t *info)
static int dequeue_synchronous_signal(kernel_siginfo_t *info)
void signal_wake_up_state(struct task_struct *t, unsigned int state)
static void flush_sigqueue_mask(sigset_t *mask, struct sigpending *s)
static inline int is_si_special(const struct kernel_siginfo *info)
static inline bool si_fromuser(const struct kernel_siginfo *info)
static bool kill_ok_by_cred(struct task_struct *t)
static int check_kill_permission(int sig, struct kernel_siginfo *info, struct task_struct *t)
static void ptrace_trap_notify(struct task_struct *t)
static bool prepare_signal(int sig, struct task_struct *p, bool force)
static inline bool wants_signal(int sig, struct task_struct *p)
static void complete_signal(int sig, struct task_struct *p, enum pid_type type)
static inline bool legacy_queue(struct sigpending *signals, int sig)
static inline void userns_fixup_signal_uid(struct kernel_siginfo *info, struct task_struct *t)
rcu_read_lock()
;info->si_uid = from_kuid_munged(task_cred_xxx(t, user_ns)
, make_kuid(current_user_ns()
, info->si_uid)
)
;rcu_read_unlock()
; } static inline void userns_fixup_signal_uid(struct kernel_siginfo *info, struct task_struct *t)
static int __send_signal(int sig, struct kernel_siginfo *info, struct task_struct *t, enum pid_type type, int from_ancestor_ns)
static int send_signal(int sig, struct kernel_siginfo *info, struct task_struct *t, enum pid_type type)
static void print_fatal_signal(int signr)
static int __init setup_print_fatal_signals(char *str)
int __group_send_sig_info(int sig, struct kernel_siginfo *info, struct task_struct *p)
int do_send_sig_info(int sig, struct kernel_siginfo *info, struct task_struct *p, enum pid_type type)
int force_sig_info(int sig, struct kernel_siginfo *info, struct task_struct *t)
int zap_other_threads(struct task_struct *p)
struct sighand_struct *__lock_task_sighand(struct task_struct *tsk, unsigned long *flags)
int group_send_sig_info(int sig, struct kernel_siginfo *info, struct task_struct *p, enum pid_type type)
int __kill_pgrp_info(int sig, struct kernel_siginfo *info, struct pid *pgrp)
int kill_pid_info(int sig, struct kernel_siginfo *info, struct pid *pid)
static int kill_proc_info(int sig, struct kernel_siginfo *info, pid_t pid)
static inline bool kill_as_cred_perm(const struct cred *cred, struct task_struct *target)
int kill_pid_info_as_cred(int sig, struct kernel_siginfo *info, struct pid *pid, const struct cred *cred)
static int kill_something_info(int sig, struct kernel_siginfo *info, pid_t pid)
int send_sig_info(int sig, struct kernel_siginfo *info, struct task_struct *p)
int send_sig(int sig, struct task_struct *p, int priv)
void force_sig(int sig, struct task_struct *p)
void force_sigsegv(int sig, struct task_struct *p)
int force_sig_fault(int sig, int code, void __user *addr___ARCH_SI_TRAPNO(int trapno)
___ARCH_SI_IA64(int imm, unsigned int flags, unsigned long isr)
, struct task_struct *t)
int send_sig_fault(int sig, int code, void __user *addr___ARCH_SI_TRAPNO(int trapno)
___ARCH_SI_IA64(int imm, unsigned int flags, unsigned long isr)
, struct task_struct *t)
int force_sig_mceerr(int code, void __user *addr, short lsb, struct task_struct *t)
int send_sig_mceerr(int code, void __user *addr, short lsb, struct task_struct *t)
int force_sig_bnderr(void __user *addr, void __user *lower, void __user *upper)
int force_sig_pkuerr(void __user *addr, u32 pkey)
int force_sig_ptrace_errno_trap(int errno, void __user *addr)
int kill_pgrp(struct pid *pid, int sig, int priv)
int kill_pid(struct pid *pid, int sig, int priv)
struct sigqueue *sigqueue_alloc(void)
void sigqueue_free(struct sigqueue *q)
int send_sigqueue(struct sigqueue *q, struct pid *pid, enum pid_type type)
bool do_notify_parent(struct task_struct *tsk, int sig)
static void do_notify_parent_cldstop(struct task_struct *tsk, bool for_ptracer, int why)
static inline bool may_ptrace_stop(void)
static bool sigkill_pending(struct task_struct *tsk)
static void ptrace_stop(int exit_code, int why, int clear_code, kernel_siginfo_t *info)
__releases(&current->sighand->siglock)
__acquires(&current->sighand->siglock)
static void ptrace_do_notify(int signr, int exit_code, int why)
void ptrace_notify(int exit_code)
static bool do_signal_stop(int signr)
__releases(&current->sighand->siglock)
static void do_jobctl_trap(void)
static int ptrace_signal(int signr, kernel_siginfo_t *info)
bool get_signal(struct ksignal *ksig)
static void signal_delivered(struct ksignal *ksig, int stepping)
void signal_setup_done(int failed, struct ksignal *ksig, int stepping)
static void retarget_shared_pending(struct task_struct *tsk, sigset_t *which)
void exit_signals(struct task_struct *tsk)
SYSCALL_DEFINE0(restart_syscall)
long do_no_restart_syscall(struct restart_block *param)
static void __set_task_blocked(struct task_struct *tsk, const sigset_t *newset)
void set_current_blocked(sigset_t *newset)
void __set_current_blocked(const sigset_t *newset)
int sigprocmask(int how, sigset_t *set, sigset_t *oldset)
int set_user_sigmask(const sigset_t __user *usigmask, sigset_t *set, sigset_t *oldset, size_t sigsetsize)
int set_compat_user_sigmask(const compat_sigset_t __user *usigmask, sigset_t *set, sigset_t *oldset, size_t sigsetsize)
void restore_user_sigmask(const void __user *usigmask, sigset_t *sigsaved)
SYSCALL_DEFINE4(rt_sigprocmask, int, how, sigset_t __user *, nset, sigset_t __user *, oset, size_t, sigsetsize)
COMPAT_SYSCALL_DEFINE4(rt_sigprocmask, int, how, compat_sigset_t __user *, nset, compat_sigset_t __user *, oset, compat_size_t, sigsetsize)
static void do_sigpending(sigset_t *set)
SYSCALL_DEFINE2(rt_sigpending, sigset_t __user *, uset, size_t, sigsetsize)
COMPAT_SYSCALL_DEFINE2(rt_sigpending, compat_sigset_t __user *, uset, compat_size_t, sigsetsize)
static bool known_siginfo_layout(unsigned sig, int si_code)
enum siginfo_layout siginfo_layout(unsigned sig, int si_code)
static inline char __user *si_expansion(const siginfo_t __user *info)
int copy_siginfo_to_user(siginfo_t __user *to, const kernel_siginfo_t *from)
static int post_copy_siginfo_from_user(kernel_siginfo_t *info, const siginfo_t __user *from)
static int __copy_siginfo_from_user(int signo, kernel_siginfo_t *to, const siginfo_t __user *from)
int copy_siginfo_from_user(kernel_siginfo_t *to, const siginfo_t __user *from)
int copy_siginfo_to_user32(struct compat_siginfo __user *to, const struct kernel_siginfo *from)
int copy_siginfo_to_user32(struct compat_siginfo __user *to, const struct kernel_siginfo *from)
return __copy_siginfo_to_user32(to, from, in_x32_syscall()
)
; } int __copy_siginfo_to_user32(struct compat_siginfo __user *to, const struct kernel_siginfo *from, bool x32_ABI)
endif static int post_copy_siginfo_from_user32(kernel_siginfo_t *to, const struct compat_siginfo *from)
static int __copy_siginfo_from_user32(int signo, struct kernel_siginfo *to, const struct compat_siginfo __user *ufrom)
int copy_siginfo_from_user32(struct kernel_siginfo *to, const struct compat_siginfo __user *ufrom)
static int do_sigtimedwait(const sigset_t *which, kernel_siginfo_t *info, const struct timespec64 *ts)
SYSCALL_DEFINE4(rt_sigtimedwait, const sigset_t __user *, uthese, siginfo_t __user *, uinfo, const struct __kernel_timespec __user *, uts, size_t, sigsetsize)
SYSCALL_DEFINE4(rt_sigtimedwait_time32, const sigset_t __user *, uthese, siginfo_t __user *, uinfo, const struct old_timespec32 __user *, uts, size_t, sigsetsize)
COMPAT_SYSCALL_DEFINE4(rt_sigtimedwait_time64, compat_sigset_t __user *, uthese, struct compat_siginfo __user *, uinfo, struct __kernel_timespec __user *, uts, compat_size_t, sigsetsize)
COMPAT_SYSCALL_DEFINE4(rt_sigtimedwait, compat_sigset_t __user *, uthese, struct compat_siginfo __user *, uinfo, struct old_timespec32 __user *, uts, compat_size_t, sigsetsize)
SYSCALL_DEFINE2(kill, pid_t, pid, int, sig)
static int do_send_specific(pid_t tgid, pid_t pid, int sig, struct kernel_siginfo *info)
static int do_tkill(pid_t tgid, pid_t pid, int sig)
SYSCALL_DEFINE3(tgkill, pid_t, tgid, pid_t, pid, int, sig)
SYSCALL_DEFINE2(tkill, pid_t, pid, int, sig)
static int do_rt_sigqueueinfo(pid_t pid, int sig, kernel_siginfo_t *info)
SYSCALL_DEFINE3(rt_sigqueueinfo, pid_t, pid, int, sig, siginfo_t __user *, uinfo)
COMPAT_SYSCALL_DEFINE3(rt_sigqueueinfo, compat_pid_t, pid, int, sig, struct compat_siginfo __user *, uinfo)
static int do_rt_tgsigqueueinfo(pid_t tgid, pid_t pid, int sig, kernel_siginfo_t *info)
SYSCALL_DEFINE4(rt_tgsigqueueinfo, pid_t, tgid, pid_t, pid, int, sig, siginfo_t __user *, uinfo)
COMPAT_SYSCALL_DEFINE4(rt_tgsigqueueinfo, compat_pid_t, tgid, compat_pid_t, pid, int, sig, struct compat_siginfo __user *, uinfo)
void kernel_sigaction(int sig, __sighandler_t action)
void __weak sigaction_compat_abi(struct k_sigaction *act, struct k_sigaction *oact)
int do_sigaction(int sig, struct k_sigaction *act, struct k_sigaction *oact)
static int do_sigaltstack (const stack_t *ss, stack_t *oss, unsigned long sp, size_t min_ss_size)
SYSCALL_DEFINE2(sigaltstack, const stack_t __user *, uss, stack_t __user *, uoss)
int restore_altstack(const stack_t __user *uss)
int __save_altstack(stack_t __user *uss, unsigned long sp)
static int do_compat_sigaltstack(const compat_stack_t __user *uss_ptr, compat_stack_t __user *uoss_ptr)
COMPAT_SYSCALL_DEFINE2(sigaltstack, const compat_stack_t __user *, uss_ptr, compat_stack_t __user *, uoss_ptr)
int compat_restore_altstack(const compat_stack_t __user *uss)
int __compat_save_altstack(compat_stack_t __user *uss, unsigned long sp)
SYSCALL_DEFINE1(sigpending, old_sigset_t __user *, uset)
COMPAT_SYSCALL_DEFINE1(sigpending, compat_old_sigset_t __user *, set32)
SYSCALL_DEFINE3(sigprocmask, int, how, old_sigset_t __user *, nset, old_sigset_t __user *, oset)
SYSCALL_DEFINE4(rt_sigaction, int, sig, const struct sigaction __user *, act, struct sigaction __user *, oact, size_t, sigsetsize)
return 0; } COMPAT_SYSCALL_DEFINE4(rt_sigaction, int, sig, const struct compat_sigaction __user *, act, struct compat_sigaction __user *, oact, compat_size_t, sigsetsize)
SYSCALL_DEFINE3(sigaction, int, sig, const struct old_sigaction __user *, act, struct old_sigaction __user *, oact)
return ret; }endif COMPAT_SYSCALL_DEFINE3(sigaction, int, sig, const struct compat_old_sigaction __user *, act, struct compat_old_sigaction __user *, oact)
SYSCALL_DEFINE0(sgetmask)
SYSCALL_DEFINE1(ssetmask, int, newmask)
SYSCALL_DEFINE2(signal, int, sig, __sighandler_t, handler)
SYSCALL_DEFINE0(pause)
static int sigsuspend(sigset_t *set)
SYSCALL_DEFINE2(rt_sigsuspend, sigset_t __user *, unewset, size_t, sigsetsize)
if (copy_from_user(&newset, unewset, sizeof(newset)
)
)
return -EFAULT;return sigsuspend(&newset)
; } COMPAT_SYSCALL_DEFINE2(rt_sigsuspend, compat_sigset_t __user *, unewset, compat_size_t, sigsetsize)
SYSCALL_DEFINE1(sigsuspend, old_sigset_t, mask)
SYSCALL_DEFINE1(sigsuspend, old_sigset_t, mask)
sigset_t blocked;siginitset(&blocked, mask)
;return sigsuspend(&blocked)
; }endif SYSCALL_DEFINE3(sigsuspend, int, unused1, int, unused2, old_sigset_t, mask)
__weak const char *arch_vma_name(struct vm_area_struct *vma)
static inline void siginfo_buildtime_checks(void)
void __init signals_init(void)
include <linux/kdb.h>void kdb_send_sig(struct task_struct *t, int sig)
\n
     40 int sig
     21 struct task_struct *t
     18 int
     16 struct kernel_siginfo *info
     12 sigsetsize
     12 sig
     11 struct task_struct *p
     10 kernel_siginfo_t *info
      9 struct task_struct *tsk
      8 void
      8 uinfo
      7 pid_t
      7 pid
      6 size_t
      6 pid_t pid
      6 enum pid_type type
      6 compat_size_t
      6 compat_sigset_t __user *
      5 void __user *addr
      5 struct task_struct *task
      5 struct pid *pid
      5 sigset_t *set
      4 uts
      4 uthese
      4 struct compat_siginfo __user *
      4 sigset_t __user *
      4 sigset_t *mask
      4 siginfo_t __user *
      4 oact
      4 mask
      4 int signr
      4 int code
      4 act
      3 uset
      3 unsigned long sp
      3 unewset
      3 tgid
      3 struct sigqueue *q
      3 struct sigpending *pending
      3 struct ksignal *ksig
      3 struct compat_siginfo __user *to
      3 sigsuspend
      3 sigset_t *oldset
      3 pid_t tgid
      3 oset
      3 old_sigset_t __user *
      3 old_sigset_t
      3 nset
      3 kernel_siginfo_t *to
      3 int why
      3 int priv
      3 int exit_code
      3 how
      3 &current->sighand->siglock
      3 const struct kernel_siginfo *from
      3 const siginfo_t __user *from
      3 compat_pid_t
      3 bool force
      2 void __user *addr___ARCH_SI_TRAPNOint trapno
      2 unsigned sig
      2 unsigned long mask
      2 unsigned long isr
      2 unsigned int flags
      2 struct k_sigaction *oact
      2 struct k_sigaction *act
      2 struct kernel_siginfo *to
      2 size_t sigsetsize
      2 sigpending
      2 sigaltstack
      2 sigaction
      2 short lsb
      2 rt_tgsigqueueinfo
      2 rt_sigtimedwait
      2 rt_sigsuspend
      2 rt_sigqueueinfo
      2 rt_sigprocmask
      2 rt_sigpending
      2 rt_sigaction
      2 int stepping
      2 int signo
      2 int si_code
      2 int imm
      2 const struct kernel_siginfo *info
      2 const struct cred *cred
      2 const struct compat_siginfo __user *ufrom
      2 const sigset_t __user *
      2 const sigset_t *newset
      2 bool *resched_timer
      2 &blocked
      2 
      1 void __user *upper
      1 void __user *lower
      1 void __user *handler
      1 uss_ptr
      1 uss
      1 user_ns
      1 uoss_ptr
      1 uoss
      1 unused2
      1 unused1
      1 unsigned long *flags
      1 unsigned int state
      1 u32 pkey
      1 to
      1 tkill
      1 tgkill
      1 task_cred_xxxt
      1 struct vm_area_struct *vma
      1 struct task_struct *target
      1 struct sigpending *signals
      1 struct sigpending *s
      1 struct sigpending *queue
      1 struct sigpending *list
      1 struct sigaction __user *
      1 struct restart_block *param
      1 struct pid *pgrp
      1 struct old_timespec32 __user *
      1 struct old_sigaction __user *
      1 struct __kernel_timespec __user *
      1 struct compat_sigaction __user *
      1 struct compat_old_sigaction __user *
      1 stack_t __user *uss
      1 stack_t __user *
      1 stack_t *oss
      1 ssetmask
      1 size_t min_ss_size
      1 sizeofnewset
      1 sigset_t *which
      1 sigset_t *sigsaved
      1 sigset_t *signal
      1 sigset_t *newset
      1 sigset_t *blocked
      1 sigprocmask
      1 signal
      1 siginfo_t __user *to
      1 __sighandler_t action
      1 __sighandler_t
      1 sgetmask
      1 set32
      1 rt_sigtimedwait_time64
      1 rt_sigtimedwait_time32
      1 restart_syscall
      1 pause
      1 &newset
      1 newmask
      1 kill_pid_info_as_cred
      1 kill
      1 in_x32_syscall
      1 int override_rlimit
      1 int how
      1 int from_ancestor_ns
      1 int force_default
      1 int failed
      1 int errno
      1 int clear_code
      1 handler
      1 gfp_t flags
      1 from
      1 dequeue_signal
      1 current_user_ns
      1 copy_from_user&newset
      1 const void __user *usigmask
      1 const struct timespec64 *ts
      1 const struct sigaction __user *
      1 const struct old_timespec32 __user *
      1 const struct old_sigaction __user *
      1 const struct __kernel_timespec __user *
      1 const struct compat_siginfo *from
      1 const struct compat_sigaction __user *
      1 const struct compat_old_sigaction __user *
      1 const stack_t __user *uss
      1 const stack_t __user *
      1 const stack_t *ss
      1 const sigset_t *which
      1 const sigset_t __user *usigmask
      1 const siginfo_t __user *info
      1 const kernel_siginfo_t *from
      1 const compat_stack_t __user *uss_ptr
      1 const compat_stack_t __user *uss
      1 const compat_stack_t __user *
      1 const compat_sigset_t __user *usigmask
      1 compat_stack_t __user *uss
      1 compat_stack_t __user *uoss_ptr
      1 compat_stack_t __user *
      1 compat_old_sigset_t __user *
      1 char *str
      1 bool x32_ABI
      1 bool for_ptracer
