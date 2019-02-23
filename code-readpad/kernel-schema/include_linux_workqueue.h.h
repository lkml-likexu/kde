
\n
static inline struct delayed_work *to_delayed_work(struct work_struct *work)
static inline struct rcu_work *to_rcu_work(struct work_struct *work)
extern void __init_work(struct work_struct *work, int onstack)
; extern void destroy_work_on_stack(struct work_struct *work)
; extern void destroy_delayed_work_on_stack(struct delayed_work *work)
; static inline unsigned int work_static(struct work_struct *work)
static inline bool queue_work(struct workqueue_struct *wq, struct work_struct *work)
static inline bool queue_delayed_work(struct workqueue_struct *wq, struct delayed_work *dwork, unsigned long delay)
static inline bool mod_delayed_work(struct workqueue_struct *wq, struct delayed_work *dwork, unsigned long delay)
static inline bool schedule_work_on(int cpu, struct work_struct *work)
static inline bool schedule_work(struct work_struct *work)
static inline void flush_scheduled_work(void)
static inline bool schedule_delayed_work_on(int cpu, struct delayed_work *dwork, unsigned long delay)
static inline bool schedule_delayed_work(struct delayed_work *dwork, unsigned long delay)
static inline long work_on_cpu(int cpu, long (*fn)
(void *)
, void *arg)
static inline long work_on_cpu(int cpu, long (*fn)
(void *)
, void *arg)
return fn(arg)
; } static inline long work_on_cpu_safe(int cpu, long (*fn)
(void *)
, void *arg)
int workqueue_sysfs_register(struct workqueue_struct *wq)
; static inline int workqueue_sysfs_register(struct workqueue_struct *wq)
\n
      8 struct work_struct *work
      5 struct workqueue_struct *wq
      5 int cpu
      4 unsigned long delay
      4 struct delayed_work *dwork
      3 void *
      3 long *fn
      1 void
      1 struct delayed_work *work
      1 int onstack
      1 arg
