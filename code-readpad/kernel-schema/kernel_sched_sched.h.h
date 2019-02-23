
\n
static inline int idle_policy(int policy)
static inline int idle_policy(int policy)
return policy == SCHED_IDLE; } static inline int fair_policy(int policy)
static inline int rt_policy(int policy)
static inline int dl_policy(int policy)
static inline int dl_policy(int policy)
return policy == SCHED_DEADLINE; } static inline bool valid_policy(int policy)
static inline int task_has_idle_policy(struct task_struct *p)
static inline int task_has_rt_policy(struct task_struct *p)
static inline int task_has_dl_policy(struct task_struct *p)
static inline bool dl_entity_is_special(struct sched_dl_entity *dl_se)
static inline bool dl_entity_preempt(struct sched_dl_entity *a, struct sched_dl_entity *b)
static inline int dl_bandwidth_enabled(void)
static inline void __dl_sub(struct dl_bw *dl_b, u64 tsk_bw, int cpus)
static inline void __dl_add(struct dl_bw *dl_b, u64 tsk_bw, int cpus)
static inline bool __dl_overflow(struct dl_bw *dl_b, int cpus, u64 old_bw, u64 new_bw)
static inline int walk_tg_tree(tg_visitor down, tg_visitor up, void *data)
static inline int rt_bandwidth_enabled(void)
static inline bool rt_rq_is_runnable(struct rt_rq *rt_rq)
static inline long se_weight(struct sched_entity *se)
static inline long se_runnable(struct sched_entity *se)
static inline bool sched_asym_prefer(int a, int b)
static inline int cpu_of(struct rq *rq)
static inline void update_idle_core(struct rq *rq)
static inline u64 __rq_clock_broken(struct rq *rq)
static inline void assert_clock_updated(struct rq *rq)
static inline u64 rq_clock(struct rq *rq)
static inline u64 rq_clock_task(struct rq *rq)
static inline void rq_clock_skip_update(struct rq *rq)
static inline void rq_clock_cancel_skipupdate(struct rq *rq)
static inline void rq_pin_lock(struct rq *rq, struct rq_flags *rf)
static inline void rq_unpin_lock(struct rq *rq, struct rq_flags *rf)
static inline void rq_repin_lock(struct rq *rq, struct rq_flags *rf)
static inline void __task_rq_unlock(struct rq *rq, struct rq_flags *rf)
__releases(rq->lock)
static inline void task_rq_unlock(struct rq *rq, struct task_struct *p, struct rq_flags *rf)
__releases(rq->lock)
__releases(p->pi_lock)
static inline void rq_lock_irqsave(struct rq *rq, struct rq_flags *rf)
__acquires(rq->lock)
static inline void rq_lock_irq(struct rq *rq, struct rq_flags *rf)
__acquires(rq->lock)
static inline void rq_lock(struct rq *rq, struct rq_flags *rf)
__acquires(rq->lock)
static inline void rq_relock(struct rq *rq, struct rq_flags *rf)
__acquires(rq->lock)
static inline void rq_unlock_irqrestore(struct rq *rq, struct rq_flags *rf)
__releases(rq->lock)
static inline void rq_unlock_irq(struct rq *rq, struct rq_flags *rf)
__releases(rq->lock)
static inline void rq_unlock(struct rq *rq, struct rq_flags *rf)
__releases(rq->lock)
static inline struct rq * this_rq_lock_irq(struct rq_flags *rf)
__acquires(rq->lock)
NUMA_MEM = 0, NUMA_CPU, NUMA_MEMBUF, NUMA_CPUBUF }; extern void sched_setnuma(struct task_struct *p, int node)
; extern int migrate_task_to(struct task_struct *p, int cpu)
; extern int migrate_swap(struct task_struct *p, struct task_struct *t, int cpu, int scpu)
; extern void init_numa_balancing(unsigned long clone_flags, struct task_struct *p)
; static inline void init_numa_balancing(unsigned long clone_flags, struct task_struct *p)
static inline void queue_balance_callback(struct rq *rq, struct callback_head *head, void (*func)
(struct rq *rq)
)
static inline struct sched_domain *highest_flag_domain(int cpu, int flag)
static inline struct sched_domain *lowest_flag_domain(int cpu, int flag)
static inline struct cpumask *sched_group_span(struct sched_group *sg)
static inline struct cpumask *group_balance_mask(struct sched_group *sg)
static inline unsigned int group_first_cpu(struct sched_group *group)
void register_sched_domain_sysctl(void)
; void dirty_sched_domain_sysctl(int cpu)
; void unregister_sched_domain_sysctl(void)
; static inline void register_sched_domain_sysctl(void)
void register_sched_domain_sysctl(void)
; void dirty_sched_domain_sysctl(int cpu)
; void unregister_sched_domain_sysctl(void)
; static inline void register_sched_domain_sysctl(void)
} static inline void dirty_sched_domain_sysctl(int cpu)
void register_sched_domain_sysctl(void)
; void dirty_sched_domain_sysctl(int cpu)
; void unregister_sched_domain_sysctl(void)
; static inline void register_sched_domain_sysctl(void)
} static inline void dirty_sched_domain_sysctl(int cpu)
} static inline void unregister_sched_domain_sysctl(void)
static inline struct task_group *task_group(struct task_struct *p)
static inline void set_task_rq(struct task_struct *p, unsigned int cpu)
static inline struct task_group *task_group(struct task_struct *p)
static inline void __set_task_cpu(struct task_struct *p, unsigned int cpu)
define SCHED_FEAT(name, enabled)
\ static __always_inline bool static_branch_name(struct static_key *key)
\ static inline u64 global_rt_period(void)
static inline u64 global_rt_runtime(void)
static inline int task_current(struct rq *rq, struct task_struct *p)
static inline int task_running(struct rq *rq, struct task_struct *p)
static inline int task_on_rq_queued(struct task_struct *p)
static inline int task_on_rq_migrating(struct task_struct *p)
static inline void put_prev_task(struct rq *rq, struct task_struct *prev)
static inline void set_curr_task(struct rq *rq, struct task_struct *curr)
static inline void idle_set_state(struct rq *rq, struct cpuidle_state *idle_state)
static inline struct cpuidle_state *idle_get_state(struct rq *rq)
return rq->idle_state; } static inline void idle_set_state(struct rq *rq, struct cpuidle_state *idle_state)
static inline struct cpuidle_state *idle_get_state(struct rq *rq)
static inline void sched_update_tick_dependency(struct rq *rq)
static inline void add_nr_running(struct rq *rq, unsigned count)
static inline void sub_nr_running(struct rq *rq, unsigned count)
static inline int hrtick_enabled(struct rq *rq)
static inline int hrtick_enabled(struct rq *rq)
static __always_inline unsigned long arch_scale_freq_capacity(int cpu)
static inline int _double_lock_balance(struct rq *this_rq, struct rq *busiest)
__releases(this_rq->lock)
__acquires(busiest->lock)
__acquires(this_rq->lock)
static inline int _double_lock_balance(struct rq *this_rq, struct rq *busiest)
__releases(this_rq->lock)
__acquires(busiest->lock)
__acquires(this_rq->lock)
static inline int double_lock_balance(struct rq *this_rq, struct rq *busiest)
static inline void double_unlock_balance(struct rq *this_rq, struct rq *busiest)
__releases(busiest->lock)
static inline void double_lock(spinlock_t *l1, spinlock_t *l2)
static inline void double_lock_irq(spinlock_t *l1, spinlock_t *l2)
static inline void double_raw_lock(raw_spinlock_t *l1, raw_spinlock_t *l2)
static inline void double_rq_lock(struct rq *rq1, struct rq *rq2)
__acquires(rq1->lock)
__acquires(rq2->lock)
static inline void double_rq_unlock(struct rq *rq1, struct rq *rq2)
__releases(rq1->lock)
__releases(rq2->lock)
static inline void double_rq_lock(struct rq *rq1, struct rq *rq2)
__acquires(rq1->lock)
__acquires(rq2->lock)
static inline void double_rq_unlock(struct rq *rq1, struct rq *rq2)
__releases(rq1->lock)
__releases(rq2->lock)
static inline void __dl_update(struct dl_bw *dl_b, s64 bw)
rq->dl.extra_bw += bw;} } static inline void __dl_update(struct dl_bw *dl_b, s64 bw)
static inline u64 irq_time_read(int cpu)
static inline void cpufreq_update_util(struct rq *rq, unsigned int flags)
static inline unsigned long schedutil_energy_util(int cpu, unsigned long cfs)
static inline unsigned long cpu_bw_dl(struct rq *rq)
static inline unsigned long cpu_util_dl(struct rq *rq)
static inline unsigned long cpu_util_cfs(struct rq *rq)
static inline unsigned long cpu_util_rt(struct rq *rq)
static inline unsigned long cpu_util_rt(struct rq *rq)
return READ_ONCE(rq->avg_rt.util_avg)
; } static inline unsigned long schedutil_energy_util(int cpu, unsigned long cfs)
static inline unsigned long cpu_util_irq(struct rq *rq)
static inline unsigned long scale_irq_capacity(unsigned long util, unsigned long irq, unsigned long max)
} static inline unsigned long cpu_util_irq(struct rq *rq)
static inline unsigned long scale_irq_capacity(unsigned long util, unsigned long irq, unsigned long max)
\n
     43 struct rq *rq
     17 struct task_struct *p
     14 void
     13 struct rq_flags *rf
     13 int cpu
     10 rq->lock
      7 int policy
      5 struct dl_bw *dl_b
      4 this_rq->lock
      4 struct rq *this_rq
      4 struct rq *rq2
      4 struct rq *rq1
      4 struct rq *busiest
      4 rq2->lock
      4 rq1->lock
      3 int cpus
      3 busiest->lock
      2 unsigned long util
      2 unsigned long max
      2 unsigned long irq
      2 unsigned long clone_flags
      2 unsigned long cfs
      2 unsigned int cpu
      2 unsigned count
      2 u64 tsk_bw
      2 struct sched_group *sg
      2 struct sched_entity *se
      2 struct cpuidle_state *idle_state
      2 spinlock_t *l2
      2 spinlock_t *l1
      2 s64 bw
      2 int flag
      1 void *func
      1 void *data
      1 unsigned int flags
      1 u64 old_bw
      1 u64 new_bw
      1 tg_visitor up
      1 tg_visitor down
      1 struct task_struct *t
      1 struct task_struct *prev
      1 struct task_struct *curr
      1 struct static_key *key
      1 struct sched_group *group
      1 struct sched_dl_entity *dl_se
      1 struct sched_dl_entity *b
      1 struct sched_dl_entity *a
      1 struct rt_rq *rt_rq
      1 struct callback_head *head
      1 rq->avg_rt.util_avg
      1 raw_spinlock_t *l2
      1 raw_spinlock_t *l1
      1 p->pi_lock
      1 name
      1 int scpu
      1 int node
      1 int b
      1 int a
      1 enabled
