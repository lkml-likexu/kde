
EXPORT_SYMBOL_GPL(system_highpri_wq);
EXPORT_SYMBOL_GPL(system_long_wq);
EXPORT_SYMBOL_GPL(system_unbound_wq);
EXPORT_SYMBOL_GPL(system_freezable_wq);
EXPORT_SYMBOL_GPL(system_power_efficient_wq);
EXPORT_SYMBOL_GPL(system_freezable_power_efficient_wq);
EXPORT_SYMBOL_GPL(__init_work);
EXPORT_SYMBOL_GPL(destroy_work_on_stack);
EXPORT_SYMBOL_GPL(destroy_delayed_work_on_stack);
EXPORT_SYMBOL_GPL(mod_delayed_work_on);
EXPORT_SYMBOL_GPL(drain_workqueue);
EXPORT_SYMBOL_GPL(flush_work);
EXPORT_SYMBOL_GPL(cancel_work_sync);
EXPORT_SYMBOL_GPL(execute_in_process_context);
EXPORT_SYMBOL_GPL(apply_workqueue_attrs);
EXPORT_SYMBOL_GPL(__alloc_workqueue_key);
EXPORT_SYMBOL_GPL(destroy_workqueue);
EXPORT_SYMBOL_GPL(workqueue_set_max_active);
EXPORT_SYMBOL_GPL(workqueue_congested);
EXPORT_SYMBOL_GPL(work_busy);
EXPORT_SYMBOL_GPL(set_worker_desc);
EXPORT_SYMBOL_GPL(work_on_cpu);
EXPORT_SYMBOL_GPL(work_on_cpu_safe);
\n
static void *work_debug_hint(void *addr)
static bool work_is_static_object(void *addr)
static bool work_fixup_init(void *addr, enum debug_obj_state state)
static bool work_fixup_free(void *addr, enum debug_obj_state state)
static inline void debug_work_activate(struct work_struct *work)
static inline void debug_work_deactivate(struct work_struct *work)
void __init_work(struct work_struct *work, int onstack)
void destroy_work_on_stack(struct work_struct *work)
void destroy_delayed_work_on_stack(struct delayed_work *work)
static int worker_pool_assign_id(struct worker_pool *pool)
static struct pool_workqueue *unbound_pwq_by_node(struct workqueue_struct *wq, int node)
static unsigned int work_color_to_flags(int color)
static int get_work_color(struct work_struct *work)
static int work_next_color(int color)
static inline void set_work_data(struct work_struct *work, unsigned long data, unsigned long flags)
static void set_work_pwq(struct work_struct *work, struct pool_workqueue *pwq, unsigned long extra_flags)
static void set_work_pool_and_keep_pending(struct work_struct *work, int pool_id)
static void set_work_pool_and_clear_pending(struct work_struct *work, int pool_id)
static void clear_work_data(struct work_struct *work)
static struct pool_workqueue *get_work_pwq(struct work_struct *work)
static struct worker_pool *get_work_pool(struct work_struct *work)
static int get_work_pool_id(struct work_struct *work)
static void mark_work_canceling(struct work_struct *work)
static bool work_is_canceling(struct work_struct *work)
static bool __need_more_worker(struct worker_pool *pool)
static bool need_more_worker(struct worker_pool *pool)
static bool may_start_working(struct worker_pool *pool)
static bool keep_working(struct worker_pool *pool)
static bool need_to_create_worker(struct worker_pool *pool)
static bool too_many_workers(struct worker_pool *pool)
static struct worker *first_idle_worker(struct worker_pool *pool)
static void wake_up_worker(struct worker_pool *pool)
void wq_worker_waking_up(struct task_struct *task, int cpu)
struct task_struct *wq_worker_sleeping(struct task_struct *task)
work_func_t wq_worker_last_func(struct task_struct *task)
static inline void worker_set_flags(struct worker *worker, unsigned int flags)
static inline void worker_clr_flags(struct worker *worker, unsigned int flags)
static struct worker *find_worker_executing_work(struct worker_pool *pool, struct work_struct *work)
static void move_linked_works(struct work_struct *work, struct list_head *head, struct work_struct **nextp)
static void get_pwq(struct pool_workqueue *pwq)
static void put_pwq(struct pool_workqueue *pwq)
static void put_pwq_unlocked(struct pool_workqueue *pwq)
static void pwq_activate_delayed_work(struct work_struct *work)
static void pwq_activate_first_delayed(struct pool_workqueue *pwq)
static void pwq_dec_nr_in_flight(struct pool_workqueue *pwq, int color)
static int try_to_grab_pending(struct work_struct *work, bool is_dwork, unsigned long *flags)
static void insert_work(struct pool_workqueue *pwq, struct work_struct *work, struct list_head *head, unsigned int extra_flags)
static bool is_chained_work(struct workqueue_struct *wq)
static int wq_select_unbound_cpu(int cpu)
static void __queue_work(int cpu, struct workqueue_struct *wq, struct work_struct *work)
bool queue_work_on(int cpu, struct workqueue_struct *wq, struct work_struct *work)
void delayed_work_timer_fn(struct timer_list *t)
static void __queue_delayed_work(int cpu, struct workqueue_struct *wq, struct delayed_work *dwork, unsigned long delay)
bool queue_delayed_work_on(int cpu, struct workqueue_struct *wq, struct delayed_work *dwork, unsigned long delay)
bool mod_delayed_work_on(int cpu, struct workqueue_struct *wq, struct delayed_work *dwork, unsigned long delay)
static void rcu_work_rcufn(struct rcu_head *rcu)
bool queue_rcu_work(struct workqueue_struct *wq, struct rcu_work *rwork)
static void worker_enter_idle(struct worker *worker)
static void worker_leave_idle(struct worker *worker)
static struct worker *alloc_worker(int node)
static void worker_attach_to_pool(struct worker *worker, struct worker_pool *pool)
static void worker_detach_from_pool(struct worker *worker)
static struct worker *create_worker(struct worker_pool *pool)
static void destroy_worker(struct worker *worker)
static void idle_worker_timeout(struct timer_list *t)
static void send_mayday(struct work_struct *work)
static void pool_mayday_timeout(struct timer_list *t)
static void maybe_create_worker(struct worker_pool *pool)
__releases(&pool->lock)
__acquires(&pool->lock)
static bool manage_workers(struct worker *worker)
static void process_one_work(struct worker *worker, struct work_struct *work)
__releases(&pool->lock)
__acquires(&pool->lock)
static void process_scheduled_works(struct worker *worker)
static void set_pf_worker(bool val)
static int worker_thread(void *__worker)
static int rescuer_thread(void *__rescuer)
static void check_flush_dependency(struct workqueue_struct *target_wq, struct work_struct *target_work)
static void wq_barrier_func(struct work_struct *work)
static void insert_wq_barrier(struct pool_workqueue *pwq, struct wq_barrier *barr, struct work_struct *target, struct worker *worker)
static bool flush_workqueue_prep_pwqs(struct workqueue_struct *wq, int flush_color, int work_color)
void flush_workqueue(struct workqueue_struct *wq)
void drain_workqueue(struct workqueue_struct *wq)
static bool start_flush_work(struct work_struct *work, struct wq_barrier *barr, bool from_cancel)
static bool __flush_work(struct work_struct *work, bool from_cancel)
bool flush_work(struct work_struct *work)
static int cwt_wakefn(wait_queue_entry_t *wait, unsigned mode, int sync, void *key)
static bool __cancel_work_timer(struct work_struct *work, bool is_dwork)
bool cancel_work_sync(struct work_struct *work)
bool flush_delayed_work(struct delayed_work *dwork)
bool flush_rcu_work(struct rcu_work *rwork)
static bool __cancel_work(struct work_struct *work, bool is_dwork)
bool cancel_delayed_work(struct delayed_work *dwork)
bool cancel_delayed_work_sync(struct delayed_work *dwork)
int schedule_on_each_cpu(work_func_t func)
int execute_in_process_context(work_func_t fn, struct execute_work *ew)
void free_workqueue_attrs(struct workqueue_attrs *attrs)
struct workqueue_attrs *alloc_workqueue_attrs(gfp_t gfp_mask)
static void copy_workqueue_attrs(struct workqueue_attrs *to, const struct workqueue_attrs *from)
static u32 wqattrs_hash(const struct workqueue_attrs *attrs)
static bool wqattrs_equal(const struct workqueue_attrs *a, const struct workqueue_attrs *b)
static int init_worker_pool(struct worker_pool *pool)
static void rcu_free_wq(struct rcu_head *rcu)
static void rcu_free_pool(struct rcu_head *rcu)
static void put_unbound_pool(struct worker_pool *pool)
static struct worker_pool *get_unbound_pool(const struct workqueue_attrs *attrs)
static void rcu_free_pwq(struct rcu_head *rcu)
static void pwq_unbound_release_workfn(struct work_struct *work)
static void pwq_adjust_max_active(struct pool_workqueue *pwq)
static void init_pwq(struct pool_workqueue *pwq, struct workqueue_struct *wq, struct worker_pool *pool)
static void link_pwq(struct pool_workqueue *pwq)
static struct pool_workqueue *alloc_unbound_pwq(struct workqueue_struct *wq, const struct workqueue_attrs *attrs)
static bool wq_calc_node_cpumask(const struct workqueue_attrs *attrs, int node, int cpu_going_down, cpumask_t *cpumask)
static struct pool_workqueue *numa_pwq_tbl_install(struct workqueue_struct *wq, int node, struct pool_workqueue *pwq)
static void apply_wqattrs_cleanup(struct apply_wqattrs_ctx *ctx)
static struct apply_wqattrs_ctx * apply_wqattrs_prepare(struct workqueue_struct *wq, const struct workqueue_attrs *attrs)
static void apply_wqattrs_commit(struct apply_wqattrs_ctx *ctx)
static void apply_wqattrs_lock(void)
static void apply_wqattrs_unlock(void)
static int apply_workqueue_attrs_locked(struct workqueue_struct *wq, const struct workqueue_attrs *attrs)
int apply_workqueue_attrs(struct workqueue_struct *wq, const struct workqueue_attrs *attrs)
static void wq_update_unbound_numa(struct workqueue_struct *wq, int cpu, bool online)
static int alloc_and_link_pwqs(struct workqueue_struct *wq)
static int wq_clamp_max_active(int max_active, unsigned int flags, const char *name)
static int init_rescuer(struct workqueue_struct *wq)
struct workqueue_struct *__alloc_workqueue_key(const char *fmt, unsigned int flags, int max_active, struct lock_class_key *key, const char *lock_name, ...)
void destroy_workqueue(struct workqueue_struct *wq)
void workqueue_set_max_active(struct workqueue_struct *wq, int max_active)
struct work_struct *current_work(void)
bool current_is_workqueue_rescuer(void)
bool workqueue_congested(int cpu, struct workqueue_struct *wq)
unsigned int work_busy(struct work_struct *work)
void set_worker_desc(const char *fmt, ...)
void print_worker_info(const char *log_lvl, struct task_struct *task)
static void pr_cont_pool_info(struct worker_pool *pool)
static void pr_cont_work(bool comma, struct work_struct *work)
static void show_pwq(struct pool_workqueue *pwq)
void show_workqueue_state(void)
void wq_worker_comm(char *buf, size_t size, struct task_struct *task)
static void unbind_workers(int cpu)
static void rebind_workers(struct worker_pool *pool)
static void restore_unbound_workers_cpumask(struct worker_pool *pool, int cpu)
int workqueue_prepare_cpu(unsigned int cpu)
int workqueue_online_cpu(unsigned int cpu)
int workqueue_offline_cpu(unsigned int cpu)
static void work_for_cpu_fn(struct work_struct *work)
long work_on_cpu(int cpu, long (*fn)
(void *)
, void *arg)
long work_on_cpu_safe(int cpu, long (*fn)
(void *)
, void *arg)
void freeze_workqueues_begin(void)
bool freeze_workqueues_busy(void)
void thaw_workqueues(void)
static int workqueue_apply_unbound_cpumask(void)
int workqueue_set_unbound_cpumask(cpumask_var_t cpumask)
static struct workqueue_struct *dev_to_wq(struct device *dev)
static ssize_t per_cpu_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t max_active_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t max_active_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t wq_pool_ids_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t wq_nice_show(struct device *dev, struct device_attribute *attr, char *buf)
static struct workqueue_attrs *wq_sysfs_prep_attrs(struct workqueue_struct *wq)
static ssize_t wq_nice_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t wq_cpumask_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t wq_cpumask_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t wq_numa_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t wq_numa_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t wq_unbound_cpumask_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t wq_unbound_cpumask_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static int __init wq_sysfs_init(void)
static void wq_device_release(struct device *dev)
int workqueue_sysfs_register(struct workqueue_struct *wq)
static void workqueue_sysfs_unregister(struct workqueue_struct *wq)
static void wq_watchdog_reset_touched(void)
static void wq_watchdog_timer_fn(struct timer_list *unused)
notrace void wq_watchdog_touch(int cpu)
static void wq_watchdog_set_thresh(unsigned long thresh)
static int wq_watchdog_param_set_thresh(const char *val, const struct kernel_param *kp)
static void wq_watchdog_init(void)
static void __init wq_numa_init(void)
int __init workqueue_init_early(void)
int __init workqueue_init(void)
\n
     35 struct work_struct *work
     26 struct workqueue_struct *wq
     19 struct worker_pool *pool
     15 void
     14 struct device *dev
     14 int cpu
     13 struct pool_workqueue *pwq
     12 struct device_attribute *attr
     11 struct worker *worker
      8 char *buf
      7 const struct workqueue_attrs *attrs
      6 struct delayed_work *dwork
      5 struct task_struct *task
      5 size_t count
      5 const char *buf
      4 void *addr
      4 unsigned int flags
      4 struct rcu_head *rcu
      4 &pool->lock
      4 int node
      3 unsigned long delay
      3 unsigned int cpu
      3 struct timer_list *t
      3 int max_active
      3 int color
      3 bool is_dwork
      2 void *
      2 struct wq_barrier *barr
      2 struct rcu_work *rwork
      2 struct list_head *head
      2 struct apply_wqattrs_ctx *ctx
      2 long *fn
      2 int pool_id
      2 enum debug_obj_state state
      2 const char *fmt
      2 bool from_cancel
      2 ...
      1 workqueue_set_max_active
      1 workqueue_congested
      1 work_on_cpu_safe
      1 work_on_cpu
      1 work_func_t func
      1 work_func_t fn
      1 work_busy
      1 wait_queue_entry_t *wait
      1 void *__worker
      1 void *__rescuer
      1 void *key
      1 unsigned mode
      1 unsigned long thresh
      1 unsigned long *flags
      1 unsigned long flags
      1 unsigned long extra_flags
      1 unsigned long data
      1 unsigned int extra_flags
      1 system_unbound_wq
      1 system_power_efficient_wq
      1 system_long_wq
      1 system_highpri_wq
      1 system_freezable_wq
      1 system_freezable_power_efficient_wq
      1 struct work_struct *target_work
      1 struct work_struct *target
      1 struct work_struct **nextp
      1 struct workqueue_struct *target_wq
      1 struct workqueue_attrs *to
      1 struct workqueue_attrs *attrs
      1 struct timer_list *unused
      1 struct lock_class_key *key
      1 struct execute_work *ew
      1 struct delayed_work *work
      1 size_t size
      1 set_worker_desc
      1 mod_delayed_work_on
      1 int work_color
      1 int sync
      1 int onstack
      1 int flush_color
      1 int cpu_going_down
      1 __init_work
      1 gfp_t gfp_mask
      1 flush_work
      1 execute_in_process_context
      1 drain_workqueue
      1 destroy_workqueue
      1 destroy_work_on_stack
      1 destroy_delayed_work_on_stack
      1 cpumask_var_t cpumask
      1 cpumask_t *cpumask
      1 const struct workqueue_attrs *from
      1 const struct workqueue_attrs *b
      1 const struct workqueue_attrs *a
      1 const struct kernel_param *kp
      1 const char *val
      1 const char *name
      1 const char *log_lvl
      1 const char *lock_name
      1 cancel_work_sync
      1 bool val
      1 bool online
      1 bool comma
      1 apply_workqueue_attrs
      1 __alloc_workqueue_key
