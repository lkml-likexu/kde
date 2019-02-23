
EXPORT_SYMBOL_GPL(sched_smt_present);
\n
int __weak arch_asym_cpu_priority(int cpu)
static inline void update_load_add(struct load_weight *lw, unsigned long inc)
static inline void update_load_sub(struct load_weight *lw, unsigned long dec)
static inline void update_load_set(struct load_weight *lw, unsigned long w)
static unsigned int get_update_sysctl_factor(void)
static void update_sysctl(void)
void sched_init_granularity(void)
static void __update_inv_weight(struct load_weight *lw)
static u64 __calc_delta(u64 delta_exec, unsigned long weight, struct load_weight *lw)
static inline struct rq *rq_of(struct cfs_rq *cfs_rq)
static inline struct task_struct *task_of(struct sched_entity *se)
static inline struct cfs_rq *task_cfs_rq(struct task_struct *p)
static inline struct cfs_rq *cfs_rq_of(struct sched_entity *se)
static inline struct cfs_rq *group_cfs_rq(struct sched_entity *grp)
static inline void list_add_leaf_cfs_rq(struct cfs_rq *cfs_rq)
static inline void list_del_leaf_cfs_rq(struct cfs_rq *cfs_rq)
static inline struct cfs_rq * is_same_group(struct sched_entity *se, struct sched_entity *pse)
static inline struct sched_entity *parent_entity(struct sched_entity *se)
static void find_matching_se(struct sched_entity **se, struct sched_entity **pse)
static inline struct task_struct *task_of(struct sched_entity *se)
static inline struct rq *rq_of(struct cfs_rq *cfs_rq)
static inline struct cfs_rq *task_cfs_rq(struct task_struct *p)
static inline struct cfs_rq *cfs_rq_of(struct sched_entity *se)
static inline struct cfs_rq *group_cfs_rq(struct sched_entity *grp)
static inline void list_add_leaf_cfs_rq(struct cfs_rq *cfs_rq)
static inline void list_del_leaf_cfs_rq(struct cfs_rq *cfs_rq)
static inline struct sched_entity *parent_entity(struct sched_entity *se)
static inline void find_matching_se(struct sched_entity **se, struct sched_entity **pse)
static inline u64 max_vruntime(u64 max_vruntime, u64 vruntime)
static inline u64 min_vruntime(u64 min_vruntime, u64 vruntime)
static inline int entity_before(struct sched_entity *a, struct sched_entity *b)
static void update_min_vruntime(struct cfs_rq *cfs_rq)
static void __enqueue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se)
static void __dequeue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se)
struct sched_entity *__pick_first_entity(struct cfs_rq *cfs_rq)
static struct sched_entity *__pick_next_entity(struct sched_entity *se)
struct sched_entity *__pick_last_entity(struct cfs_rq *cfs_rq)
int sched_proc_update_handler(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static inline u64 calc_delta_fair(u64 delta, struct sched_entity *se)
static u64 __sched_period(unsigned long nr_running)
static u64 sched_slice(struct cfs_rq *cfs_rq, struct sched_entity *se)
static u64 sched_vslice(struct cfs_rq *cfs_rq, struct sched_entity *se)
void init_entity_runnable_average(struct sched_entity *se)
void post_init_entity_util_avg(struct sched_entity *se)
void init_entity_runnable_average(struct sched_entity *se)
void init_entity_runnable_average(struct sched_entity *se)
} void post_init_entity_util_avg(struct sched_entity *se)
void init_entity_runnable_average(struct sched_entity *se)
} void post_init_entity_util_avg(struct sched_entity *se)
} static void update_tg_load_avg(struct cfs_rq *cfs_rq, int force)
static void update_curr(struct cfs_rq *cfs_rq)
static void update_curr_fair(struct rq *rq)
static inline void update_stats_wait_start(struct cfs_rq *cfs_rq, struct sched_entity *se)
static inline void update_stats_wait_end(struct cfs_rq *cfs_rq, struct sched_entity *se)
static inline void update_stats_enqueue_sleeper(struct cfs_rq *cfs_rq, struct sched_entity *se)
static inline void update_stats_enqueue(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
static inline void update_stats_dequeue(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
static inline void update_stats_curr_start(struct cfs_rq *cfs_rq, struct sched_entity *se)
static unsigned int task_nr_scan_windows(struct task_struct *p)
static unsigned int task_scan_min(struct task_struct *p)
static unsigned int task_scan_start(struct task_struct *p)
static unsigned int task_scan_max(struct task_struct *p)
void init_numa_balancing(unsigned long clone_flags, struct task_struct *p)
static void account_numa_enqueue(struct rq *rq, struct task_struct *p)
static void account_numa_dequeue(struct rq *rq, struct task_struct *p)
pid_t task_numa_group_id(struct task_struct *p)
static inline int task_faults_idx(enum numa_faults_stats s, int nid, int priv)
static inline unsigned long task_faults(struct task_struct *p, int nid)
static inline unsigned long group_faults(struct task_struct *p, int nid)
static inline unsigned long group_faults_cpu(struct numa_group *group, int nid)
static inline unsigned long group_faults_priv(struct numa_group *ng)
static inline unsigned long group_faults_shared(struct numa_group *ng)
static bool numa_is_active_node(int nid, struct numa_group *ng)
static unsigned long score_nearby_nodes(struct task_struct *p, int nid, int maxdist, bool task)
static inline unsigned long task_weight(struct task_struct *p, int nid, int dist)
static inline unsigned long group_weight(struct task_struct *p, int nid, int dist)
bool should_numa_migrate_memory(struct task_struct *p, struct page * page, int src_nid, int dst_cpu)
static void update_numa_stats(struct numa_stats *ns, int nid)
static void task_numa_assign(struct task_numa_env *env, struct task_struct *p, long imp)
static bool load_too_imbalanced(long src_load, long dst_load, struct task_numa_env *env)
static void task_numa_compare(struct task_numa_env *env, long taskimp, long groupimp, bool maymove)
static void task_numa_find_cpu(struct task_numa_env *env, long taskimp, long groupimp)
static int task_numa_migrate(struct task_struct *p)
static void numa_migrate_preferred(struct task_struct *p)
static void numa_group_count_active_nodes(struct numa_group *numa_group)
static void update_task_scan_period(struct task_struct *p, unsigned long shared, unsigned long private)
static u64 numa_get_avg_runtime(struct task_struct *p, u64 *period)
static int preferred_group_nid(struct task_struct *p, int nid)
static void task_numa_placement(struct task_struct *p)
static inline int get_numa_group(struct numa_group *grp)
static inline void put_numa_group(struct numa_group *grp)
static void task_numa_group(struct task_struct *p, int cpupid, int flags, int *priv)
void task_numa_free(struct task_struct *p)
void task_numa_fault(int last_cpupid, int mem_node, int pages, int flags)
static void reset_ptenuma_scan(struct task_struct *p)
void task_numa_work(struct callback_head *work)
void task_tick_numa(struct rq *rq, struct task_struct *curr)
static void update_scan_period(struct task_struct *p, int new_cpu)
static void task_tick_numa(struct rq *rq, struct task_struct *curr)
static inline void account_numa_enqueue(struct rq *rq, struct task_struct *p)
static inline void account_numa_dequeue(struct rq *rq, struct task_struct *p)
static inline void update_scan_period(struct task_struct *p, int new_cpu)
static void account_entity_enqueue(struct cfs_rq *cfs_rq, struct sched_entity *se)
static void account_entity_dequeue(struct cfs_rq *cfs_rq, struct sched_entity *se)
static inline void enqueue_runnable_load_avg(struct cfs_rq *cfs_rq, struct sched_entity *se)
static inline void dequeue_runnable_load_avg(struct cfs_rq *cfs_rq, struct sched_entity *se)
static inline void enqueue_load_avg(struct cfs_rq *cfs_rq, struct sched_entity *se)
static inline void dequeue_load_avg(struct cfs_rq *cfs_rq, struct sched_entity *se)
static void reweight_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, unsigned long weight, unsigned long runnable)
void reweight_task(struct task_struct *p, int prio)
static long calc_group_shares(struct cfs_rq *cfs_rq)
static long calc_group_runnable(struct cfs_rq *cfs_rq, long shares)
static void update_cfs_group(struct sched_entity *se)
static inline void update_cfs_group(struct sched_entity *se)
static inline void cfs_rq_util_change(struct cfs_rq *cfs_rq, int flags)
static inline void update_tg_load_avg(struct cfs_rq *cfs_rq, int force)
void set_task_rq_fair(struct sched_entity *se, struct cfs_rq *prev, struct cfs_rq *next)
static inline void update_tg_cfs_util(struct cfs_rq *cfs_rq, struct sched_entity *se, struct cfs_rq *gcfs_rq)
static inline void update_tg_cfs_runnable(struct cfs_rq *cfs_rq, struct sched_entity *se, struct cfs_rq *gcfs_rq)
static inline void add_tg_cfs_propagate(struct cfs_rq *cfs_rq, long runnable_sum)
static inline int propagate_entity_load_avg(struct sched_entity *se)
static inline bool skip_blocked_update(struct sched_entity *se)
static inline int propagate_entity_load_avg(struct sched_entity *se)
static inline int update_cfs_rq_load_avg(u64 now, struct cfs_rq *cfs_rq)
static void attach_entity_load_avg(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
static void detach_entity_load_avg(struct cfs_rq *cfs_rq, struct sched_entity *se)
static inline void update_load_avg(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
static inline u64 cfs_rq_last_update_time(struct cfs_rq *cfs_rq)
return last_update_time; } static inline u64 cfs_rq_last_update_time(struct cfs_rq *cfs_rq)
void sync_entity_load_avg(struct sched_entity *se)
void remove_entity_load_avg(struct sched_entity *se)
static inline unsigned long cfs_rq_runnable_load_avg(struct cfs_rq *cfs_rq)
static inline unsigned long cfs_rq_load_avg(struct cfs_rq *cfs_rq)
static inline unsigned long task_util(struct task_struct *p)
static inline unsigned long _task_util_est(struct task_struct *p)
static inline unsigned long task_util_est(struct task_struct *p)
static inline void util_est_enqueue(struct cfs_rq *cfs_rq, struct task_struct *p)
static inline bool within_margin(int value, int margin)
static void util_est_dequeue(struct cfs_rq *cfs_rq, struct task_struct *p, bool task_sleep)
static inline int task_fits_capacity(struct task_struct *p, long capacity)
static inline void update_misfit_status(struct task_struct *p, struct rq *rq)
static inline void update_load_avg(struct cfs_rq *cfs_rq, struct sched_entity *se, int not_used1)
static inline int idle_balance(struct rq *rq, struct rq_flags *rf)
static void check_spread(struct cfs_rq *cfs_rq, struct sched_entity *se)
static void place_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int initial)
static inline void check_schedstat_required(void)
static void enqueue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
static void __clear_buddies_last(struct sched_entity *se)
static void __clear_buddies_next(struct sched_entity *se)
static void __clear_buddies_skip(struct sched_entity *se)
static void clear_buddies(struct cfs_rq *cfs_rq, struct sched_entity *se)
static void dequeue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
static void check_preempt_tick(struct cfs_rq *cfs_rq, struct sched_entity *curr)
static void set_next_entity(struct cfs_rq *cfs_rq, struct sched_entity *se)
static struct sched_entity * pick_next_entity(struct cfs_rq *cfs_rq, struct sched_entity *curr)
static void put_prev_entity(struct cfs_rq *cfs_rq, struct sched_entity *prev)
static void entity_tick(struct cfs_rq *cfs_rq, struct sched_entity *curr, int queued)
static inline bool cfs_bandwidth_used(void)
void cfs_bandwidth_usage_inc(void)
void cfs_bandwidth_usage_dec(void)
void cfs_bandwidth_usage_dec(void)
static_key_slow_dec_cpuslocked(&__cfs_bandwidth_used)
; } static bool cfs_bandwidth_used(void)
static inline u64 default_cfs_period(void)
static inline u64 sched_cfs_bandwidth_slice(void)
void __refill_cfs_bandwidth_runtime(struct cfs_bandwidth *cfs_b)
static inline struct cfs_bandwidth *tg_cfs_bandwidth(struct task_group *tg)
static inline u64 cfs_rq_clock_task(struct cfs_rq *cfs_rq)
static int assign_cfs_rq_runtime(struct cfs_rq *cfs_rq)
static void expire_cfs_rq_runtime(struct cfs_rq *cfs_rq)
static void __account_cfs_rq_runtime(struct cfs_rq *cfs_rq, u64 delta_exec)
static __always_inline void account_cfs_rq_runtime(struct cfs_rq *cfs_rq, u64 delta_exec)
static inline int cfs_rq_throttled(struct cfs_rq *cfs_rq)
static inline int throttled_hierarchy(struct cfs_rq *cfs_rq)
static inline int throttled_lb_pair(struct task_group *tg, int src_cpu, int dest_cpu)
static int tg_unthrottle_up(struct task_group *tg, void *data)
static int tg_throttle_down(struct task_group *tg, void *data)
static void throttle_cfs_rq(struct cfs_rq *cfs_rq)
void unthrottle_cfs_rq(struct cfs_rq *cfs_rq)
static u64 distribute_cfs_runtime(struct cfs_bandwidth *cfs_b, u64 remaining, u64 expires)
static int do_sched_cfs_period_timer(struct cfs_bandwidth *cfs_b, int overrun)
static int runtime_refresh_within(struct cfs_bandwidth *cfs_b, u64 min_expire)
static void start_cfs_slack_bandwidth(struct cfs_bandwidth *cfs_b)
static void __return_cfs_rq_runtime(struct cfs_rq *cfs_rq)
static __always_inline void return_cfs_rq_runtime(struct cfs_rq *cfs_rq)
static void do_sched_cfs_slack_timer(struct cfs_bandwidth *cfs_b)
static void check_enqueue_throttle(struct cfs_rq *cfs_rq)
static void sync_throttle(struct task_group *tg, int cpu)
static bool check_cfs_rq_runtime(struct cfs_rq *cfs_rq)
static enum hrtimer_restart sched_cfs_slack_timer(struct hrtimer *timer)
static enum hrtimer_restart sched_cfs_period_timer(struct hrtimer *timer)
void init_cfs_bandwidth(struct cfs_bandwidth *cfs_b)
static void init_cfs_rq_runtime(struct cfs_rq *cfs_rq)
void start_cfs_bandwidth(struct cfs_bandwidth *cfs_b)
static void destroy_cfs_bandwidth(struct cfs_bandwidth *cfs_b)
static void __maybe_unused update_runtime_enabled(struct rq *rq)
static void __maybe_unused unthrottle_offline_cfs_rqs(struct rq *rq)
static inline u64 cfs_rq_clock_task(struct cfs_rq *cfs_rq)
static inline int cfs_rq_throttled(struct cfs_rq *cfs_rq)
static inline int throttled_hierarchy(struct cfs_rq *cfs_rq)
static inline int throttled_lb_pair(struct task_group *tg, int src_cpu, int dest_cpu)
static inline struct cfs_bandwidth *tg_cfs_bandwidth(struct task_group *tg)
static void hrtick_start_fair(struct rq *rq, struct task_struct *p)
static void hrtick_update(struct rq *rq)
if (cfs_rq_of(&curr->se)
->nr_running < sched_nr_latency)
hrtick_start_fair(rq, curr)
; } static inline void hrtick_start_fair(struct rq *rq, struct task_struct *p)
static inline void hrtick_update(struct rq *rq)
static inline bool cpu_overutilized(int cpu)
static inline void update_overutilized_status(struct rq *rq)
static void enqueue_task_fair(struct rq *rq, struct task_struct *p, int flags)
static void dequeue_task_fair(struct rq *rq, struct task_struct *p, int flags)
static unsigned long decay_load_missed(unsigned long load, unsigned long missed_updates, int idx)
static void cpu_load_update(struct rq *this_rq, unsigned long this_load, unsigned long pending_updates)
static unsigned long weighted_cpuload(struct rq *rq)
static void cpu_load_update_nohz(struct rq *this_rq, unsigned long curr_jiffies, unsigned long load)
static void cpu_load_update_idle(struct rq *this_rq)
void cpu_load_update_nohz_start(void)
void cpu_load_update_nohz_stop(void)
static void cpu_load_update_periodic(struct rq *this_rq, unsigned long load)
void cpu_load_update_active(struct rq *this_rq)
static unsigned long source_load(int cpu, int type)
static unsigned long target_load(int cpu, int type)
static unsigned long capacity_of(int cpu)
static unsigned long capacity_orig_of(int cpu)
static unsigned long cpu_avg_load_per_task(int cpu)
static void record_wakee(struct task_struct *p)
static int wake_wide(struct task_struct *p)
static int wake_affine_idle(int this_cpu, int prev_cpu, int sync)
static int wake_affine_weight(struct sched_domain *sd, struct task_struct *p, int this_cpu, int prev_cpu, int sync)
static int wake_affine(struct sched_domain *sd, struct task_struct *p, int this_cpu, int prev_cpu, int sync)
static unsigned long capacity_spare_without(int cpu, struct task_struct *p)
static struct sched_group * find_idlest_group(struct sched_domain *sd, struct task_struct *p, int this_cpu, int sd_flag)
static int find_idlest_group_cpu(struct sched_group *group, struct task_struct *p, int this_cpu)
static inline int find_idlest_cpu(struct sched_domain *sd, struct task_struct *p, int cpu, int prev_cpu, int sd_flag)
static inline void set_idle_cores(int cpu, int val)
static inline bool test_idle_cores(int cpu, bool def)
void __update_idle_core(struct rq *rq)
static int select_idle_core(struct task_struct *p, struct sched_domain *sd, int target)
static int select_idle_smt(struct task_struct *p, struct sched_domain *sd, int target)
static inline int select_idle_core(struct task_struct *p, struct sched_domain *sd, int target)
static inline int select_idle_smt(struct task_struct *p, struct sched_domain *sd, int target)
static int select_idle_cpu(struct task_struct *p, struct sched_domain *sd, int target)
static int select_idle_sibling(struct task_struct *p, int prev, int target)
static inline unsigned long cpu_util(int cpu)
static unsigned long cpu_util_without(int cpu, struct task_struct *p)
static int wake_cap(struct task_struct *p, int cpu, int prev_cpu)
static unsigned long cpu_util_next(int cpu, struct task_struct *p, int dst_cpu)
static long compute_energy(struct task_struct *p, int dst_cpu, struct perf_domain *pd)
static int find_energy_efficient_cpu(struct task_struct *p, int prev_cpu)
static int select_task_rq_fair(struct task_struct *p, int prev_cpu, int sd_flag, int wake_flags)
static void migrate_task_rq_fair(struct task_struct *p, int new_cpu)
static void task_dead_fair(struct task_struct *p)
static unsigned long wakeup_gran(struct sched_entity *se)
static int wakeup_preempt_entity(struct sched_entity *curr, struct sched_entity *se)
static void set_last_buddy(struct sched_entity *se)
static void set_next_buddy(struct sched_entity *se)
static void set_skip_buddy(struct sched_entity *se)
static void check_preempt_wakeup(struct rq *rq, struct task_struct *p, int wake_flags)
static struct task_struct * pick_next_task_fair(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
static void put_prev_task_fair(struct rq *rq, struct task_struct *prev)
static void yield_task_fair(struct rq *rq)
static bool yield_to_task_fair(struct rq *rq, struct task_struct *p, bool preempt)
static int task_hot(struct task_struct *p, struct lb_env *env)
static int migrate_degrades_locality(struct task_struct *p, struct lb_env *env)
static inline int migrate_degrades_locality(struct task_struct *p, struct lb_env *env)
static int can_migrate_task(struct task_struct *p, struct lb_env *env)
static void detach_task(struct task_struct *p, struct lb_env *env)
static struct task_struct *detach_one_task(struct lb_env *env)
static int detach_tasks(struct lb_env *env)
static void attach_task(struct rq *rq, struct task_struct *p)
static void attach_one_task(struct rq *rq, struct task_struct *p)
static void attach_tasks(struct lb_env *env)
static inline bool cfs_rq_has_blocked(struct cfs_rq *cfs_rq)
static inline bool others_have_blocked(struct rq *rq)
static void update_blocked_averages(int cpu)
static void update_cfs_rq_h_load(struct cfs_rq *cfs_rq)
static unsigned long task_h_load(struct task_struct *p)
update_cfs_rq_h_load(cfs_rq)
;return div64_ul(p->se.avg.load_avg * cfs_rq->h_load, cfs_rq_load_avg(cfs_rq)
+ 1)
; } static inline void update_blocked_averages(int cpu)
static unsigned long task_h_load(struct task_struct *p)
static inline void init_sd_lb_stats(struct sd_lb_stats *sds)
static inline int get_sd_load_idx(struct sched_domain *sd, enum cpu_idle_type idle)
static unsigned long scale_rt_capacity(struct sched_domain *sd, int cpu)
static void update_cpu_capacity(struct sched_domain *sd, int cpu)
void update_group_capacity(struct sched_domain *sd, int cpu)
static inline int check_cpu_capacity(struct rq *rq, struct sched_domain *sd)
static inline int sg_imbalanced(struct sched_group *group)
static inline bool group_has_capacity(struct lb_env *env, struct sg_lb_stats *sgs)
static inline bool group_is_overloaded(struct lb_env *env, struct sg_lb_stats *sgs)
static inline bool group_smaller_min_cpu_capacity(struct sched_group *sg, struct sched_group *ref)
static inline bool group_smaller_max_cpu_capacity(struct sched_group *sg, struct sched_group *ref)
static inline enum group_type group_classify(struct sched_group *group, struct sg_lb_stats *sgs)
static bool update_nohz_stats(struct rq *rq, bool force)
static inline void update_sg_lb_stats(struct lb_env *env, struct sched_group *group, struct sg_lb_stats *sgs, int *sg_status)
static bool update_sd_pick_busiest(struct lb_env *env, struct sd_lb_stats *sds, struct sched_group *sg, struct sg_lb_stats *sgs)
static inline enum fbq_type fbq_classify_group(struct sg_lb_stats *sgs)
static inline enum fbq_type fbq_classify_rq(struct rq *rq)
static inline enum fbq_type fbq_classify_rq(struct rq *rq)
if (rq->nr_running > rq->nr_numa_running)
return regular;if (rq->nr_running > rq->nr_preferred_running)
return remote;return all; } static inline enum fbq_type fbq_classify_group(struct sg_lb_stats *sgs)
static inline enum fbq_type fbq_classify_rq(struct rq *rq)
static inline void update_sd_lb_stats(struct lb_env *env, struct sd_lb_stats *sds)
static int check_asym_packing(struct lb_env *env, struct sd_lb_stats *sds)
static inline void fix_small_imbalance(struct lb_env *env, struct sd_lb_stats *sds)
static inline void calculate_imbalance(struct lb_env *env, struct sd_lb_stats *sds)
static struct sched_group *find_busiest_group(struct lb_env *env)
static struct rq *find_busiest_queue(struct lb_env *env, struct sched_group *group)
static int need_active_balance(struct lb_env *env)
static int should_we_balance(struct lb_env *env)
static int load_balance(int this_cpu, struct rq *this_rq, struct sched_domain *sd, enum cpu_idle_type idle, int *continue_balancing)
static inline unsigned long get_sd_balance_interval(struct sched_domain *sd, int cpu_busy)
static inline void update_next_balance(struct sched_domain *sd, unsigned long *next_balance)
static int active_load_balance_cpu_stop(void *data)
void update_max_interval(void)
static void rebalance_domains(struct rq *rq, enum cpu_idle_type idle)
static inline int on_null_domain(struct rq *rq)
static inline int find_new_ilb(void)
static void kick_ilb(unsigned int flags)
static void nohz_balancer_kick(struct rq *rq)
static void set_cpu_sd_state_busy(int cpu)
void nohz_balance_exit_idle(struct rq *rq)
static void set_cpu_sd_state_idle(int cpu)
void nohz_balance_enter_idle(int cpu)
static bool _nohz_idle_balance(struct rq *this_rq, unsigned int flags, enum cpu_idle_type idle)
static bool nohz_idle_balance(struct rq *this_rq, enum cpu_idle_type idle)
static void nohz_newidle_balance(struct rq *this_rq)
static inline bool nohz_idle_balance(struct rq *this_rq, enum cpu_idle_type idle)
static int idle_balance(struct rq *this_rq, struct rq_flags *rf)
static __latent_entropy void run_rebalance_domains(struct softirq_action *h)
void trigger_load_balance(struct rq *rq)
static void rq_online_fair(struct rq *rq)
static void rq_offline_fair(struct rq *rq)
static void task_tick_fair(struct rq *rq, struct task_struct *curr, int queued)
static void task_fork_fair(struct task_struct *p)
static void prio_changed_fair(struct rq *rq, struct task_struct *p, int oldprio)
static inline bool vruntime_normalized(struct task_struct *p)
static void propagate_entity_cfs_rq(struct sched_entity *se)
static void detach_entity_cfs_rq(struct sched_entity *se)
static void attach_entity_cfs_rq(struct sched_entity *se)
static void detach_task_cfs_rq(struct task_struct *p)
static void attach_task_cfs_rq(struct task_struct *p)
static void switched_from_fair(struct rq *rq, struct task_struct *p)
static void switched_to_fair(struct rq *rq, struct task_struct *p)
static void set_curr_task_fair(struct rq *rq)
void init_cfs_rq(struct cfs_rq *cfs_rq)
static void task_set_group_fair(struct task_struct *p)
static void task_move_group_fair(struct task_struct *p)
static void task_change_group_fair(struct task_struct *p, int type)
void free_fair_sched_group(struct task_group *tg)
int alloc_fair_sched_group(struct task_group *tg, struct task_group *parent)
void online_fair_sched_group(struct task_group *tg)
void unregister_fair_sched_group(struct task_group *tg)
void init_tg_cfs_entry(struct task_group *tg, struct cfs_rq *cfs_rq, struct sched_entity *se, int cpu, struct sched_entity *parent)
int sched_group_set_shares(struct task_group *tg, unsigned long shares)
int alloc_fair_sched_group(struct task_group *tg, struct task_group *parent)
static unsigned int get_rr_interval_fair(struct rq *rq, struct task_struct *task)
void print_cfs_stats(struct seq_file *m, int cpu)
void show_numa_stats(struct task_struct *p, struct seq_file *m)
__init void init_sched_fair_class(void)
\n
     86 struct task_struct *p
     77 struct cfs_rq *cfs_rq
     65 struct sched_entity *se
     46 struct rq *rq
     26 int cpu
     20 struct lb_env *env
     17 struct sched_domain *sd
     16 void
     14 struct task_group *tg
     11 struct rq *this_rq
     11 int flags
     10 int nid
      9 struct cfs_bandwidth *cfs_b
      7 struct sg_lb_stats *sgs
      7 int prev_cpu
      6 struct sd_lb_stats *sds
      6 int this_cpu
      6 int target
      6 enum cpu_idle_type idle
      5 struct sched_group *group
      5 struct load_weight *lw
      4 struct task_numa_env *env
      4 struct sched_entity *curr
      3 void *data
      3 unsigned long load
      3 u64 delta_exec
      3 struct task_struct *curr
      3 struct sched_group *sg
      3 struct rq_flags *rf
      3 struct numa_group *ng
      3 int type
      3 int sync
      3 int sd_flag
      3 int new_cpu
      3 int dst_cpu
      2 unsigned long weight
      2 unsigned int flags
      2 u64 vruntime
      2 struct task_struct *prev
      2 struct task_group *parent
      2 struct seq_file *m
      2 struct sched_group *ref
      2 struct sched_entity **se
      2 struct sched_entity **pse
      2 struct sched_entity *grp
      2 struct numa_group *grp
      2 struct hrtimer *timer
      2 struct cfs_rq *gcfs_rq
      2 long taskimp
      2 long groupimp
      2 int wake_flags
      2 int src_cpu
      2 int queued
      2 int force
      2 int dist
      2 int dest_cpu
      1 void __user *buffer
      1 unsigned long w
      1 unsigned long this_load
      1 unsigned long shares
      1 unsigned long shared
      1 unsigned long runnable
      1 unsigned long private
      1 unsigned long pending_updates
      1 unsigned long nr_running
      1 unsigned long *next_balance
      1 unsigned long missed_updates
      1 unsigned long inc
      1 unsigned long dec
      1 unsigned long curr_jiffies
      1 unsigned long clone_flags
      1 u64 remaining
      1 u64 *period
      1 u64 now
      1 u64 min_vruntime
      1 u64 min_expire
      1 u64 max_vruntime
      1 u64 expires
      1 u64 delta
      1 struct task_struct *task
      1 struct softirq_action *h
      1 struct sched_entity *pse
      1 struct sched_entity *prev
      1 struct sched_entity *parent
      1 struct sched_entity *b
      1 struct sched_entity *a
      1 struct perf_domain *pd
      1 struct page * page
      1 struct numa_stats *ns
      1 struct numa_group *numa_group
      1 struct numa_group *group
      1 struct ctl_table *table
      1 struct cfs_rq *prev
      1 struct cfs_rq *next
      1 struct callback_head *work
      1 size_t *lenp
      1 sched_smt_present
      1 rq->nr_running > rq->nr_preferred_running
      1 rq->nr_running > rq->nr_numa_running
      1 rq
      1 p->se.avg.load_avg * cfs_rq->h_load
      1 long src_load
      1 long shares
      1 long runnable_sum
      1 long imp
      1 long dst_load
      1 long capacity
      1 loff_t *ppos
      1 int write
      1 int value
      1 int val
      1 int src_nid
      1 int *sg_status
      1 int *priv
      1 int priv
      1 int prio
      1 int prev
      1 int pages
      1 int overrun
      1 int oldprio
      1 int not_used1
      1 int mem_node
      1 int maxdist
      1 int margin
      1 int last_cpupid
      1 int initial
      1 int idx
      1 int cpupid
      1 int cpu_busy
      1 int *continue_balancing
      1 enum numa_faults_stats s
      1 curr
      1 cfs_rq_of&curr->se
      1 cfs_rq_load_avgcfs_rq
      1 cfs_rq
      1 &__cfs_bandwidth_used
      1 bool task_sleep
      1 bool task
      1 bool preempt
      1 bool maymove
      1 bool force
      1 bool def
