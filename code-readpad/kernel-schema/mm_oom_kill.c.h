
EXPORT_SYMBOL_GPL(register_oom_notifier);
EXPORT_SYMBOL_GPL(unregister_oom_notifier);
\n
static bool has_intersects_mems_allowed(struct task_struct *start, const nodemask_t *mask)
return ret; } static bool has_intersects_mems_allowed(struct task_struct *tsk, const nodemask_t *mask)
struct task_struct *find_lock_task_mm(struct task_struct *p)
static inline bool is_sysrq_oom(struct oom_control *oc)
static inline bool is_memcg_oom(struct oom_control *oc)
static bool oom_unkillable_task(struct task_struct *p, struct mem_cgroup *memcg, const nodemask_t *nodemask)
static bool is_dump_unreclaim_slabs(void)
unsigned long oom_badness(struct task_struct *p, struct mem_cgroup *memcg, const nodemask_t *nodemask, unsigned long totalpages)
static enum oom_constraint constrained_alloc(struct oom_control *oc)
static int oom_evaluate_task(struct task_struct *task, void *arg)
static void select_bad_process(struct oom_control *oc)
static void dump_tasks(struct mem_cgroup *memcg, const nodemask_t *nodemask)
static void dump_oom_summary(struct oom_control *oc, struct task_struct *victim)
static void dump_header(struct oom_control *oc, struct task_struct *p)
bool process_shares_mm(struct task_struct *p, struct mm_struct *mm)
bool __oom_reap_task_mm(struct mm_struct *mm)
static bool oom_reap_task_mm(struct task_struct *tsk, struct mm_struct *mm)
define MAX_OOM_REAP_RETRIES 10 static void oom_reap_task(struct task_struct *tsk)
static int oom_reaper(void *unused)
static void wake_oom_reaper(struct task_struct *tsk)
static int __init oom_init(void)
static int __init oom_init(void)
oom_reaper_th = kthread_run(oom_reaper, NULL, "oom_reaper")
;return 0; } subsys_initcall(oom_init)
static inline void wake_oom_reaper(struct task_struct *tsk)
static void mark_oom_victim(struct task_struct *tsk)
void exit_oom_victim(void)
void oom_killer_enable(void)
bool oom_killer_disable(signed long timeout)
static inline bool __task_will_free_mem(struct task_struct *task)
static bool task_will_free_mem(struct task_struct *task)
static void __oom_kill_process(struct task_struct *victim)
static int oom_kill_memcg_member(struct task_struct *task, void *unused)
static void oom_kill_process(struct oom_control *oc, const char *message)
static void check_panic_on_oom(struct oom_control *oc, enum oom_constraint constraint)
int register_oom_notifier(struct notifier_block *nb)
int unregister_oom_notifier(struct notifier_block *nb)
bool out_of_memory(struct oom_control *oc)
void pagefault_out_of_memory(void)
\n
      9 struct oom_control *oc
      6 void
      6 struct task_struct *tsk
      5 struct task_struct *p
      4 struct task_struct *task
      3 struct mm_struct *mm
      3 struct mem_cgroup *memcg
      3 const nodemask_t *nodemask
      2 void *unused
      2 struct task_struct *victim
      2 struct notifier_block *nb
      2 const nodemask_t *mask
      1 void *arg
      1 unsigned long totalpages
      1 unregister_oom_notifier
      1 struct task_struct *start
      1 signed long timeout
      1 register_oom_notifier
      1 oom_reaper
      1 "oom_reaper"
      1 oom_init
      1 NULL
      1 enum oom_constraint constraint
      1 const char *message
