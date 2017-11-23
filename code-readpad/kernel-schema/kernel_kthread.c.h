
EXPORT_SYMBOL_GPL(kthread_should_park);
EXPORT_SYMBOL_GPL(kthread_freezable_should_stop);
EXPORT_SYMBOL_GPL(kthread_parkme);
EXPORT_SYMBOL_GPL(kthread_unpark);
EXPORT_SYMBOL_GPL(kthread_park);
EXPORT_SYMBOL_GPL(__kthread_init_worker);
EXPORT_SYMBOL_GPL(kthread_worker_fn);
EXPORT_SYMBOL_GPL(kthread_queue_work);
EXPORT_SYMBOL_GPL(kthread_queue_delayed_work);
EXPORT_SYMBOL_GPL(kthread_flush_work);
EXPORT_SYMBOL_GPL(kthread_mod_delayed_work);
EXPORT_SYMBOL_GPL(kthread_cancel_work_sync);
EXPORT_SYMBOL_GPL(kthread_cancel_delayed_work_sync);
EXPORT_SYMBOL_GPL(kthread_flush_worker);
struct kthread_create_info static inline void set_kthread_struct(void *kthread)
static inline struct kthread *to_kthread(struct task_struct *k)
void free_kthread_struct(struct task_struct *k)
bool kthread_should_stop(void)
bool kthread_should_park(void)
bool kthread_freezable_should_stop(bool *was_frozen)
void *kthread_data(struct task_struct *task)
void *kthread_probe_data(struct task_struct *task)
static void __kthread_parkme(struct kthread *self)
void kthread_parkme(void)
static int kthread(void *_create)
int tsk_fork_get_node(struct task_struct *tsk)
static void create_kthread(struct kthread_create_info *create)
static __printf(4, 0)
struct task_struct *__kthread_create_on_node(int (*threadfn)
(void *data)
, void *data, int node, const char namefmt[], va_list args)
struct task_struct *kthread_create_on_node(int (*threadfn)
(void *data)
, void *data, int node, const char namefmt[], ...)
static void __kthread_bind_mask(struct task_struct *p, const struct cpumask *mask, long state)
static void __kthread_bind(struct task_struct *p, unsigned int cpu, long state)
void kthread_bind_mask(struct task_struct *p, const struct cpumask *mask)
void kthread_bind(struct task_struct *p, unsigned int cpu)
struct task_struct *kthread_create_on_cpu(int (*threadfn)
(void *data)
, void *data, unsigned int cpu, const char *namefmt)
void kthread_unpark(struct task_struct *k)
int kthread_park(struct task_struct *k)
int kthread_stop(struct task_struct *k)
int kthreadd(void *unused)
void __kthread_init_worker(struct kthread_worker *worker, const char *name, struct lock_class_key *key)
int kthread_worker_fn(void *worker_ptr)
static __printf(3, 0)
struct kthread_worker * __kthread_create_worker(int cpu, unsigned int flags, const char namefmt[], va_list args)
struct kthread_worker * kthread_create_worker(unsigned int flags, const char namefmt[], ...)
struct kthread_worker * kthread_create_worker_on_cpu(int cpu, unsigned int flags, const char namefmt[], ...)
static inline bool queuing_blocked(struct kthread_worker *worker, struct kthread_work *work)
static void kthread_insert_work_sanity_check(struct kthread_worker *worker, struct kthread_work *work)
static void kthread_insert_work(struct kthread_worker *worker, struct kthread_work *work, struct list_head *pos)
bool kthread_queue_work(struct kthread_worker *worker, struct kthread_work *work)
void kthread_delayed_work_timer_fn(struct timer_list *t)
void __kthread_queue_delayed_work(struct kthread_worker *worker, struct kthread_delayed_work *dwork, unsigned long delay)
bool kthread_queue_delayed_work(struct kthread_worker *worker, struct kthread_delayed_work *dwork, unsigned long delay)
static void kthread_flush_work_fn(struct kthread_work *work)
void kthread_flush_work(struct kthread_work *work)
static bool __kthread_cancel_work(struct kthread_work *work, bool is_dwork, unsigned long *flags)
bool kthread_mod_delayed_work(struct kthread_worker *worker, struct kthread_delayed_work *dwork, unsigned long delay)
static bool __kthread_cancel_work_sync(struct kthread_work *work, bool is_dwork)
bool kthread_cancel_work_sync(struct kthread_work *work)
bool kthread_cancel_delayed_work_sync(struct kthread_delayed_work *dwork)
void kthread_flush_worker(struct kthread_worker *worker)
void kthread_destroy_worker(struct kthread_worker *worker)
void kthread_associate_blkcg(struct cgroup_subsys_state *css)
struct cgroup_subsys_state *kthread_blkcg(void)
  10 struct kthread_worker *worker
   9 struct kthread_work *work
   5 struct task_struct *k
   4 void
   4 struct task_struct *p
   4 struct kthread_delayed_work *dwork
   3 void *data
   3 unsigned long delay
   3 unsigned int flags
   3 int *threadfn
   3 const char namefmt[]
   2 unsigned int cpu
   2 struct task_struct *task
   2 long state
   2 int cpu
   2 const struct cpumask *mask
   2 bool is_dwork
   2 0
   2 ...
   1 void *worker_ptr
   1 void *unused
   1 void *kthread
   1 void *_create
   1 va_list args
   1 unsigned long *flags
   1 struct timer_list *t
   1 struct task_struct *tsk
   1 struct lock_class_key *key
   1 struct list_head *pos
   1 struct kthread_create_info *create
   1 struct kthread *self
   1 struct cgroup_subsys_state *css
   1 kthread_worker_fn
   1 kthread_unpark
   1 kthread_should_park
   1 kthread_queue_work
   1 kthread_queue_delayed_work
   1 kthread_parkme
   1 kthread_park
   1 kthread_mod_delayed_work
   1 kthread_freezable_should_stop
   1 kthread_flush_worker
   1 kthread_flush_work
   1 kthread_cancel_work_sync
   1 kthread_cancel_delayed_work_sync
   1 const char *name
   1 bool *was_frozen
   1 __kthread_init_worker
   1 4
   1 3
