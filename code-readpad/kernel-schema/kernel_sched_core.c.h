
EXPORT_SYMBOL_GPL(set_cpus_allowed_ptr);
EXPORT_SYMBOL_GPL(kick_process);
EXPORT_SYMBOL_GPL(preempt_notifier_inc);
EXPORT_SYMBOL_GPL(preempt_notifier_dec);
EXPORT_SYMBOL_GPL(preempt_notifier_register);
EXPORT_SYMBOL_GPL(preempt_notifier_unregister);
EXPORT_SYMBOL_GPL(preempt_schedule_notrace);
EXPORT_SYMBOL_GPL(sched_setscheduler);
EXPORT_SYMBOL_GPL(sched_setattr);
EXPORT_SYMBOL_GPL(sched_setscheduler_nocheck);
EXPORT_SYMBOL_GPL(yield_to);
EXPORT_SYMBOL_GPL(sched_show_task);
\n
struct rq *__task_rq_lock(struct task_struct *p, struct rq_flags *rf)
__acquires(rq->lock)
struct rq *task_rq_lock(struct task_struct *p, struct rq_flags *rf)
__acquires(p->pi_lock)
__acquires(rq->lock)
static void update_rq_clock_task(struct rq *rq, s64 delta)
void update_rq_clock(struct rq *rq)
static void hrtick_clear(struct rq *rq)
static enum hrtimer_restart hrtick(struct hrtimer *timer)
static void __hrtick_restart(struct rq *rq)
static void __hrtick_start(void *arg)
void hrtick_start(struct rq *rq, u64 delay)
void hrtick_start(struct rq *rq, u64 delay)
static void hrtick_rq_init(struct rq *rq)
hrtimer_init(&rq->hrtick_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL)
;rq->hrtick_timer.function = hrtick; } static inline void hrtick_clear(struct rq *rq)
static inline void hrtick_rq_init(struct rq *rq)
static bool set_nr_and_not_polling(struct task_struct *p)
static bool set_nr_if_polling(struct task_struct *p)
static bool set_nr_and_not_polling(struct task_struct *p)
static bool set_nr_if_polling(struct task_struct *p)
void wake_q_add(struct wake_q_head *head, struct task_struct *task)
void wake_up_q(struct wake_q_head *head)
void resched_curr(struct rq *rq)
void resched_cpu(int cpu)
int get_nohz_timer_target(void)
static void wake_up_idle_cpu(int cpu)
static bool wake_up_full_nohz_cpu(int cpu)
void wake_up_nohz_cpu(int cpu)
static inline bool got_nohz_idle_kick(void)
static inline bool got_nohz_idle_kick(void)
bool sched_can_stop_tick(struct rq *rq)
(defined(CONFIG_SMP)
|| defined(CONFIG_CFS_BANDWIDTH)
)
)
int walk_tg_tree_from(struct task_group *from, tg_visitor down, tg_visitor up, void *data)
int tg_nop(struct task_group *tg, void *data)
static void set_load_weight(struct task_struct *p, bool update_load)
static inline void enqueue_task(struct rq *rq, struct task_struct *p, int flags)
static inline void dequeue_task(struct rq *rq, struct task_struct *p, int flags)
void activate_task(struct rq *rq, struct task_struct *p, int flags)
void deactivate_task(struct rq *rq, struct task_struct *p, int flags)
static inline int __normal_prio(struct task_struct *p)
static inline int normal_prio(struct task_struct *p)
static int effective_prio(struct task_struct *p)
inline int task_curr(const struct task_struct *p)
static inline void check_class_changed(struct rq *rq, struct task_struct *p, const struct sched_class *prev_class, int oldprio)
void check_preempt_curr(struct rq *rq, struct task_struct *p, int flags)
static inline bool is_per_cpu_kthread(struct task_struct *p)
static inline bool is_cpu_allowed(struct task_struct *p, int cpu)
static struct rq *move_queued_task(struct rq *rq, struct rq_flags *rf, struct task_struct *p, int new_cpu)
static struct rq *__migrate_task(struct rq *rq, struct rq_flags *rf, struct task_struct *p, int dest_cpu)
static int migration_cpu_stop(void *data)
void set_cpus_allowed_common(struct task_struct *p, const struct cpumask *new_mask)
void do_set_cpus_allowed(struct task_struct *p, const struct cpumask *new_mask)
static int __set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask, bool check)
int set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask)
void set_task_cpu(struct task_struct *p, unsigned int new_cpu)
static void __migrate_swap_task(struct task_struct *p, int cpu)
static int migrate_swap_stop(void *data)
int migrate_swap(struct task_struct *cur, struct task_struct *p, int target_cpu, int curr_cpu)
unsigned long wait_task_inactive(struct task_struct *p, long match_state)
void kick_process(struct task_struct *p)
static int select_fallback_rq(int cpu, struct task_struct *p)
static inline int select_task_rq(struct task_struct *p, int cpu, int sd_flags, int wake_flags)
static void update_avg(u64 *avg, u64 sample)
void sched_set_stop_task(int cpu, struct task_struct *stop)
static inline int __set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask, bool check)
static void ttwu_stat(struct task_struct *p, int cpu, int wake_flags)
static inline void ttwu_activate(struct rq *rq, struct task_struct *p, int en_flags)
static void ttwu_do_wakeup(struct rq *rq, struct task_struct *p, int wake_flags, struct rq_flags *rf)
static void ttwu_do_activate(struct rq *rq, struct task_struct *p, int wake_flags, struct rq_flags *rf)
static int ttwu_remote(struct task_struct *p, int wake_flags)
void sched_ttwu_pending(void)
void scheduler_ipi(void)
static void ttwu_queue_remote(struct task_struct *p, int cpu, int wake_flags)
void wake_up_if_idle(int cpu)
bool cpus_share_cache(int this_cpu, int that_cpu)
static void ttwu_queue(struct task_struct *p, int cpu, int wake_flags)
static int try_to_wake_up(struct task_struct *p, unsigned int state, int wake_flags)
static void try_to_wake_up_local(struct task_struct *p, struct rq_flags *rf)
int wake_up_process(struct task_struct *p)
int wake_up_state(struct task_struct *p, unsigned int state)
static void __sched_fork(unsigned long clone_flags, struct task_struct *p)
void set_numabalancing_state(bool enabled)
int sysctl_numa_balancing(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static void set_schedstats(bool enabled)
void force_schedstat_enabled(void)
static int __init setup_schedstats(char *str)
static void __init init_schedstats(void)
int sysctl_schedstats(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int sched_fork(unsigned long clone_flags, struct task_struct *p)
unsigned long to_ratio(u64 period, u64 runtime)
void wake_up_new_task(struct task_struct *p)
void preempt_notifier_inc(void)
void preempt_notifier_dec(void)
void preempt_notifier_register(struct preempt_notifier *notifier)
void preempt_notifier_unregister(struct preempt_notifier *notifier)
static void __fire_sched_in_preempt_notifiers(struct task_struct *curr)
static __always_inline void fire_sched_in_preempt_notifiers(struct task_struct *curr)
static void __fire_sched_out_preempt_notifiers(struct task_struct *curr, struct task_struct *next)
static __always_inline void fire_sched_out_preempt_notifiers(struct task_struct *curr, struct task_struct *next)
static inline void fire_sched_in_preempt_notifiers(struct task_struct *curr)
static inline void fire_sched_out_preempt_notifiers(struct task_struct *curr, struct task_struct *next)
static inline void prepare_task(struct task_struct *next)
static inline void finish_task(struct task_struct *prev)
static inline void prepare_lock_switch(struct rq *rq, struct task_struct *next, struct rq_flags *rf)
static inline void finish_lock_switch(struct rq *rq)
static inline void prepare_task_switch(struct rq *rq, struct task_struct *prev, struct task_struct *next)
static struct rq *finish_task_switch(struct task_struct *prev)
__releases(rq->lock)
static void __balance_callback(struct rq *rq)
static inline void balance_callback(struct rq *rq)
static inline void balance_callback(struct rq *rq)
asmlinkage __visible void schedule_tail(struct task_struct *prev)
__releases(rq->lock)
static __always_inline struct rq * context_switch(struct rq *rq, struct task_struct *prev, struct task_struct *next, struct rq_flags *rf)
unsigned long nr_running(void)
bool single_task_running(void)
unsigned long long nr_context_switches(void)
unsigned long nr_iowait_cpu(int cpu)
unsigned long nr_iowait(void)
void sched_exec(void)
static inline void prefetch_curr_exec_start(struct task_struct *p)
unsigned long long task_sched_runtime(struct task_struct *p)
void scheduler_tick(void)
static void sched_tick_remote(struct work_struct *work)
static void sched_tick_start(int cpu)
static void sched_tick_stop(int cpu)
int __init sched_tick_offload_init(void)
defined(CONFIG_TRACE_PREEMPT_TOGGLE)
)
static inline void preempt_latency_start(int val)
void preempt_count_add(int val)
static inline void preempt_latency_stop(int val)
void preempt_count_sub(int val)
static inline unsigned long get_preempt_disable_ip(struct task_struct *p)
static noinline void __schedule_bug(struct task_struct *prev)
static inline void schedule_debug(struct task_struct *prev)
static inline struct task_struct * pick_next_task(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
static void __sched notrace __schedule(bool preempt)
void __noreturn do_task_dead(void)
static inline void sched_submit_work(struct task_struct *tsk)
asmlinkage __visible void __sched schedule(void)
void __sched schedule_idle(void)
asmlinkage __visible void __sched schedule_user(void)
void __sched schedule_preempt_disabled(void)
static void __sched notrace preempt_schedule_common(void)
asmlinkage __visible void __sched notrace preempt_schedule(void)
asmlinkage __visible void __sched notrace preempt_schedule_notrace(void)
asmlinkage __visible void __sched preempt_schedule_irq(void)
int default_wake_function(wait_queue_entry_t *curr, unsigned mode, int wake_flags, void *key)
static inline int __rt_effective_prio(struct task_struct *pi_task, int prio)
static inline int rt_effective_prio(struct task_struct *p, int prio)
void rt_mutex_setprio(struct task_struct *p, struct task_struct *pi_task)
balance_callback(rq)
;preempt_enable()
; } static inline int rt_effective_prio(struct task_struct *p, int prio)
void set_user_nice(struct task_struct *p, long nice)
int can_nice(const struct task_struct *p, const int nice)
SYSCALL_DEFINE1(nice, int, increment)
int task_prio(const struct task_struct *p)
int idle_cpu(int cpu)
int available_idle_cpu(int cpu)
struct task_struct *idle_task(int cpu)
static struct task_struct *find_process_by_pid(pid_t pid)
static void __setscheduler_params(struct task_struct *p, const struct sched_attr *attr)
static void __setscheduler(struct rq *rq, struct task_struct *p, const struct sched_attr *attr, bool keep_boost)
static bool check_same_owner(struct task_struct *p)
static int __sched_setscheduler(struct task_struct *p, const struct sched_attr *attr, bool user, bool pi)
static int _sched_setscheduler(struct task_struct *p, int policy, const struct sched_param *param, bool check)
return __sched_setscheduler(p, &attr, check, true)
; }int sched_setscheduler(struct task_struct *p, int policy, const struct sched_param *param)
int sched_setattr(struct task_struct *p, const struct sched_attr *attr)
int sched_setattr_nocheck(struct task_struct *p, const struct sched_attr *attr)
int sched_setscheduler_nocheck(struct task_struct *p, int policy, const struct sched_param *param)
static int do_sched_setscheduler(pid_t pid, int policy, struct sched_param __user *param)
static int sched_copy_attr(struct sched_attr __user *uattr, struct sched_attr *attr)
SYSCALL_DEFINE3(sched_setscheduler, pid_t, pid, int, policy, struct sched_param __user *, param)
SYSCALL_DEFINE2(sched_setparam, pid_t, pid, struct sched_param __user *, param)
SYSCALL_DEFINE3(sched_setattr, pid_t, pid, struct sched_attr __user *, uattr, unsigned int, flags)
SYSCALL_DEFINE1(sched_getscheduler, pid_t, pid)
SYSCALL_DEFINE2(sched_getparam, pid_t, pid, struct sched_param __user *, param)
static int sched_read_attr(struct sched_attr __user *uattr, struct sched_attr *attr, unsigned int usize)
SYSCALL_DEFINE4(sched_getattr, pid_t, pid, struct sched_attr __user *, uattr, unsigned int, size, unsigned int, flags)
long sched_setaffinity(pid_t pid, const struct cpumask *in_mask)
static int get_user_cpu_mask(unsigned long __user *user_mask_ptr, unsigned len, struct cpumask *new_mask)
SYSCALL_DEFINE3(sched_setaffinity, pid_t, pid, unsigned int, len, unsigned long __user *, user_mask_ptr)
long sched_getaffinity(pid_t pid, struct cpumask *mask)
SYSCALL_DEFINE3(sched_getaffinity, pid_t, pid, unsigned int, len, unsigned long __user *, user_mask_ptr)
static void do_sched_yield(void)
SYSCALL_DEFINE0(sched_yield)
int __sched _cond_resched(void)
int __cond_resched_lock(spinlock_t *lock)
void __sched yield(void)
int __sched yield_to(struct task_struct *p, bool preempt)
int io_schedule_prepare(void)
void io_schedule_finish(int token)
long __sched io_schedule_timeout(long timeout)
void io_schedule(void)
SYSCALL_DEFINE1(sched_get_priority_max, int, policy)
SYSCALL_DEFINE1(sched_get_priority_min, int, policy)
static int sched_rr_get_interval(pid_t pid, struct timespec64 *t)
SYSCALL_DEFINE2(sched_rr_get_interval, pid_t, pid, struct __kernel_timespec __user *, interval)
COMPAT_SYSCALL_DEFINE2(sched_rr_get_interval, compat_pid_t, pid, struct old_timespec32 __user *, interval)
void sched_show_task(struct task_struct *p)
static inline bool state_filter_match(unsigned long state_filter, struct task_struct *p)
void show_state_filter(unsigned long state_filter)
void init_idle(struct task_struct *idle, int cpu)
int cpuset_cpumask_can_shrink(const struct cpumask *cur, const struct cpumask *trial)
int task_can_attach(struct task_struct *p, const struct cpumask *cs_cpus_allowed)
int migrate_task_to(struct task_struct *p, int target_cpu)
void sched_setnuma(struct task_struct *p, int nid)
void idle_task_exit(void)
static void calc_load_migrate(struct rq *rq)
static void put_prev_task_fake(struct rq *rq, struct task_struct *prev)
static void migrate_tasks(struct rq *dead_rq, struct rq_flags *rf)
void set_rq_online(struct rq *rq)
void set_rq_offline(struct rq *rq)
static void cpuset_cpu_active(void)
static int cpuset_cpu_inactive(unsigned int cpu)
int sched_cpu_activate(unsigned int cpu)
int sched_cpu_deactivate(unsigned int cpu)
static void sched_rq_cpu_starting(unsigned int cpu)
int sched_cpu_starting(unsigned int cpu)
int sched_cpu_dying(unsigned int cpu)
void __init sched_init_smp(void)
static int __init migration_init(void)
void __init sched_init_smp(void)
int in_sched_functions(unsigned long addr)
void __init sched_init(void)
static inline int preempt_count_equals(int preempt_offset)
void __might_sleep(const char *file, int line, int preempt_offset)
void ___might_sleep(const char *file, int line, int preempt_offset)
void normalize_rt_tasks(void)
struct task_struct *curr_task(int cpu)
void ia64_set_curr_task(int cpu, struct task_struct *p)
static void sched_free_group(struct task_group *tg)
struct task_group *sched_create_group(struct task_group *parent)
void sched_online_group(struct task_group *tg, struct task_group *parent)
static void sched_free_group_rcu(struct rcu_head *rhp)
void sched_destroy_group(struct task_group *tg)
void sched_offline_group(struct task_group *tg)
static void sched_change_group(struct task_struct *tsk, int type)
void sched_move_task(struct task_struct *tsk)
static inline struct task_group *css_tg(struct cgroup_subsys_state *css)
static struct cgroup_subsys_state * cpu_cgroup_css_alloc(struct cgroup_subsys_state *parent_css)
static int cpu_cgroup_css_online(struct cgroup_subsys_state *css)
static void cpu_cgroup_css_released(struct cgroup_subsys_state *css)
static void cpu_cgroup_css_free(struct cgroup_subsys_state *css)
static void cpu_cgroup_fork(struct task_struct *task)
static int cpu_cgroup_can_attach(struct cgroup_taskset *tset)
static void cpu_cgroup_attach(struct cgroup_taskset *tset)
static int cpu_shares_write_u64(struct cgroup_subsys_state *css, struct cftype *cftype, u64 shareval)
static u64 cpu_shares_read_u64(struct cgroup_subsys_state *css, struct cftype *cft)
static int tg_set_cfs_bandwidth(struct task_group *tg, u64 period, u64 quota)
int tg_set_cfs_quota(struct task_group *tg, long cfs_quota_us)
long tg_get_cfs_quota(struct task_group *tg)
int tg_set_cfs_period(struct task_group *tg, long cfs_period_us)
long tg_get_cfs_period(struct task_group *tg)
static s64 cpu_cfs_quota_read_s64(struct cgroup_subsys_state *css, struct cftype *cft)
static int cpu_cfs_quota_write_s64(struct cgroup_subsys_state *css, struct cftype *cftype, s64 cfs_quota_us)
static u64 cpu_cfs_period_read_u64(struct cgroup_subsys_state *css, struct cftype *cft)
static int cpu_cfs_period_write_u64(struct cgroup_subsys_state *css, struct cftype *cftype, u64 cfs_period_us)
static u64 normalize_cfs_quota(struct task_group *tg, struct cfs_schedulable_data *d)
static int tg_cfs_schedulable_down(struct task_group *tg, void *data)
static int __cfs_schedulable(struct task_group *tg, u64 period, u64 quota)
static int cpu_cfs_stat_show(struct seq_file *sf, void *v)
static int cpu_rt_runtime_write(struct cgroup_subsys_state *css, struct cftype *cft, s64 val)
static s64 cpu_rt_runtime_read(struct cgroup_subsys_state *css, struct cftype *cft)
static int cpu_rt_period_write_uint(struct cgroup_subsys_state *css, struct cftype *cftype, u64 rt_period_us)
static u64 cpu_rt_period_read_uint(struct cgroup_subsys_state *css, struct cftype *cft)
static int cpu_extra_stat_show(struct seq_file *sf, struct cgroup_subsys_state *css)
static u64 cpu_weight_read_u64(struct cgroup_subsys_state *css, struct cftype *cft)
static int cpu_weight_write_u64(struct cgroup_subsys_state *css, struct cftype *cft, u64 weight)
static s64 cpu_weight_nice_read_s64(struct cgroup_subsys_state *css, struct cftype *cft)
static int cpu_weight_nice_write_s64(struct cgroup_subsys_state *css, struct cftype *cft, s64 nice)
static void __maybe_unused cpu_period_quota_print(struct seq_file *sf, long period, long quota)
static int __maybe_unused cpu_period_quota_parse(char *buf, u64 *periodp, u64 *quotap)
static int cpu_max_show(struct seq_file *sf, void *v)
static ssize_t cpu_max_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
void dump_cpu_task(int cpu)
\n
     69 struct task_struct *p
     37 void
     35 struct rq *rq
     23 int cpu
     19 struct cgroup_subsys_state *css
     13 struct task_group *tg
     11 struct rq_flags *rf
     10 struct cftype *cft
     10 pid
      9 struct task_struct *prev
      9 pid_t
      9 int wake_flags
      7 struct task_struct *next
      6 unsigned int cpu
      6 struct task_struct *curr
      5 void *data
      5 unsigned int
      5 pid_t pid
      5 int flags
      5 const struct sched_attr *attr
      5 const struct cpumask *new_mask
      4 struct seq_file *sf
      4 struct cftype *cftype
      4 rq->lock
      4 int val
      4 int policy
      4 int
      3 u64 period
      3 struct task_struct *tsk
      3 struct sched_param __user *
      3 policy
      3 param
      3 int prio
      3 int preempt_offset
      3 const struct task_struct *p
      3 const struct sched_param *param
      3 bool check
      2 void *v
      2 void __user *buffer
      2 user_mask_ptr
      2 unsigned long __user *
      2 unsigned long state_filter
      2 unsigned long clone_flags
      2 unsigned int state
      2 uattr
      2 u64 quota
      2 u64 delay
      2 struct wake_q_head *head
      2 struct task_struct *task
      2 struct task_struct *pi_task
      2 struct task_group *parent
      2 struct sched_attr __user *uattr
      2 struct sched_attr __user *
      2 struct sched_attr *attr
      2 struct preempt_notifier *notifier
      2 struct ctl_table *table
      2 struct cgroup_taskset *tset
      2 size_t *lenp
      2 sched_setscheduler
      2 sched_setattr
      2 sched_rr_get_interval
      2 loff_t *ppos
      2 len
      2 int write
      2 int target_cpu
      2 int line
      2 interval
      2 flags
      2 const char *file
      2 char *buf
      2 bool preempt
      2 bool enabled
      1 yield_to
      1 wait_queue_entry_t *curr
      1 void *key
      1 void *arg
      1 unsigned mode
      1 unsigned long __user *user_mask_ptr
      1 unsigned long addr
      1 unsigned len
      1 unsigned int usize
      1 unsigned int new_cpu
      1 u64 weight
      1 u64 shareval
      1 u64 sample
      1 u64 runtime
      1 u64 rt_period_us
      1 u64 *quotap
      1 u64 *periodp
      1 u64 cfs_period_us
      1 u64 *avg
      1 true
      1 tg_visitor up
      1 tg_visitor down
      1 struct work_struct *work
      1 struct timespec64 *t
      1 struct task_struct *stop
      1 struct task_struct *idle
      1 struct task_struct *cur
      1 struct task_group *from
      1 struct sched_param __user *param
      1 struct rq *dead_rq
      1 struct rcu_head *rhp
      1 struct old_timespec32 __user *
      1 struct kernfs_open_file *of
      1 struct __kernel_timespec __user *
      1 struct hrtimer *timer
      1 struct cpumask *new_mask
      1 struct cpumask *mask
      1 struct cgroup_subsys_state *parent_css
      1 struct cfs_schedulable_data *d
      1 spinlock_t *lock
      1 size_t nbytes
      1 size
      1 set_cpus_allowed_ptr
      1 sched_yield
      1 sched_show_task
      1 sched_setscheduler_nocheck
      1 sched_setparam
      1 sched_setaffinity
      1 sched_getscheduler
      1 sched_get_priority_min
      1 sched_get_priority_max
      1 sched_getparam
      1 sched_getattr
      1 sched_getaffinity
      1 s64 val
      1 s64 nice
      1 s64 delta
      1 s64 cfs_quota_us
      1 &rq->hrtick_timer
      1 rq
      1 preempt_schedule_notrace
      1 preempt_notifier_unregister
      1 preempt_notifier_register
      1 preempt_notifier_inc
      1 preempt_notifier_dec
      1 p->pi_lock
      1 p
      1 nice
      1 long timeout
      1 long quota
      1 long period
      1 long nice
      1 long match_state
      1 long cfs_quota_us
      1 long cfs_period_us
      1 loff_t off
      1 kick_process
      1 int type
      1 int token
      1 int this_cpu
      1 int that_cpu
      1 int sd_flags
      1 int oldprio
      1 int nid
      1 int new_cpu
      1 int en_flags
      1 int dest_cpu
      1 int curr_cpu
      1 increment
      1 HRTIMER_MODE_REL
      1 definedCONFIG_SMP
      1 const struct sched_class *prev_class
      1 const struct cpumask *trial
      1 const struct cpumask *in_mask
      1 const struct cpumask *cur
      1 const struct cpumask *cs_cpus_allowed
      1 const int nice
      1 CONFIG_TRACE_PREEMPT_TOGGLE
      1 CONFIG_CFS_BANDWIDTH
      1 compat_pid_t
      1 CLOCK_MONOTONIC
      1 check
      1 char *str
      1 bool user
      1 bool update_load
      1 bool pi
      1 bool keep_boost
      1 &attr
      1 
