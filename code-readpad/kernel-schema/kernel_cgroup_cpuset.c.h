
EXPORT_SYMBOL_GPL(cpuset_mem_spread_node);
\n
static inline struct cpuset *css_cs(struct cgroup_subsys_state *css)
static inline struct cpuset *task_cs(struct task_struct *task)
static inline struct cpuset *parent_cs(struct cpuset *cs)
static inline bool task_has_mempolicy(struct task_struct *task)
static inline bool task_has_mempolicy(struct task_struct *task)
return task->mempolicy; } static inline bool task_has_mempolicy(struct task_struct *task)
static inline bool is_cpuset_online(struct cpuset *cs)
static inline int is_cpu_exclusive(const struct cpuset *cs)
static inline int is_mem_exclusive(const struct cpuset *cs)
static inline int is_mem_hardwall(const struct cpuset *cs)
static inline int is_sched_load_balance(const struct cpuset *cs)
static inline int is_memory_migrate(const struct cpuset *cs)
static inline int is_spread_page(const struct cpuset *cs)
static inline int is_spread_slab(const struct cpuset *cs)
static inline int is_partition_root(const struct cpuset *cs)
static inline bool is_in_v2_mode(void)
static struct dentry *cpuset_mount(struct file_system_type *fs_type, int flags, const char *unused_dev_name, void *data)
static void guarantee_online_cpus(struct cpuset *cs, struct cpumask *pmask)
static void guarantee_online_mems(struct cpuset *cs, nodemask_t *pmask)
static void cpuset_update_task_spread_flag(struct cpuset *cs, struct task_struct *tsk)
static int is_cpuset_subset(const struct cpuset *p, const struct cpuset *q)
static inline int alloc_cpumasks(struct cpuset *cs, struct tmpmasks *tmp)
static inline void free_cpumasks(struct cpuset *cs, struct tmpmasks *tmp)
static struct cpuset *alloc_trial_cpuset(struct cpuset *cs)
static inline void free_cpuset(struct cpuset *cs)
static int validate_change(struct cpuset *cur, struct cpuset *trial)
static int cpusets_overlap(struct cpuset *a, struct cpuset *b)
static void update_domain_attr(struct sched_domain_attr *dattr, struct cpuset *c)
static void update_domain_attr_tree(struct sched_domain_attr *dattr, struct cpuset *root_cs)
static inline int nr_cpusets(void)
static int generate_sched_domains(cpumask_var_t **domains, struct sched_domain_attr **attributes)
static void rebuild_sched_domains_locked(void)
partition_sched_domains(ndoms, doms, attr)
; out:put_online_cpus()
; } static void rebuild_sched_domains_locked(void)
void rebuild_sched_domains(void)
static void update_tasks_cpumask(struct cpuset *cs)
static void compute_effective_cpumask(struct cpumask *new_cpus, struct cpuset *cs, struct cpuset *parent)
static int update_parent_subparts_cpumask(struct cpuset *cpuset, int cmd, struct cpumask *newmask, struct tmpmasks *tmp)
static void update_cpumasks_hier(struct cpuset *cs, struct tmpmasks *tmp)
static void update_sibling_cpumasks(struct cpuset *parent, struct cpuset *cs, struct tmpmasks *tmp)
static int update_cpumask(struct cpuset *cs, struct cpuset *trialcs, const char *buf)
static void cpuset_migrate_mm_workfn(struct work_struct *work)
static void cpuset_migrate_mm(struct mm_struct *mm, const nodemask_t *from, const nodemask_t *to)
static void cpuset_post_attach(void)
static void cpuset_change_task_nodemask(struct task_struct *tsk, nodemask_t *newmems)
static void update_tasks_nodemask(struct cpuset *cs)
static void update_nodemasks_hier(struct cpuset *cs, nodemask_t *new_mems)
static int update_nodemask(struct cpuset *cs, struct cpuset *trialcs, const char *buf)
bool current_cpuset_is_being_rebound(void)
static int update_relax_domain_level(struct cpuset *cs, s64 val)
static void update_tasks_flags(struct cpuset *cs)
static int update_flag(cpuset_flagbits_t bit, struct cpuset *cs, int turning_on)
static int update_prstate(struct cpuset *cs, int val)
static void fmeter_init(struct fmeter *fmp)
static void fmeter_update(struct fmeter *fmp)
static void fmeter_markevent(struct fmeter *fmp)
static int fmeter_getrate(struct fmeter *fmp)
static int cpuset_can_attach(struct cgroup_taskset *tset)
static void cpuset_cancel_attach(struct cgroup_taskset *tset)
static void cpuset_attach(struct cgroup_taskset *tset)
static int cpuset_write_u64(struct cgroup_subsys_state *css, struct cftype *cft, u64 val)
static int cpuset_write_s64(struct cgroup_subsys_state *css, struct cftype *cft, s64 val)
static ssize_t cpuset_write_resmask(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static int cpuset_common_seq_show(struct seq_file *sf, void *v)
static u64 cpuset_read_u64(struct cgroup_subsys_state *css, struct cftype *cft)
static s64 cpuset_read_s64(struct cgroup_subsys_state *css, struct cftype *cft)
static int sched_partition_show(struct seq_file *seq, void *v)
static ssize_t sched_partition_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static struct cgroup_subsys_state * cpuset_css_alloc(struct cgroup_subsys_state *parent_css)
static int cpuset_css_online(struct cgroup_subsys_state *css)
static void cpuset_css_offline(struct cgroup_subsys_state *css)
static void cpuset_css_free(struct cgroup_subsys_state *css)
static void cpuset_bind(struct cgroup_subsys_state *root_css)
static void cpuset_fork(struct task_struct *task)
int __init cpuset_init(void)
static void remove_tasks_in_empty_cpuset(struct cpuset *cs)
static void hotplug_update_tasks_legacy(struct cpuset *cs, struct cpumask *new_cpus, nodemask_t *new_mems, bool cpus_updated, bool mems_updated)
static void hotplug_update_tasks(struct cpuset *cs, struct cpumask *new_cpus, nodemask_t *new_mems, bool cpus_updated, bool mems_updated)
void cpuset_force_rebuild(void)
static void cpuset_hotplug_update_tasks(struct cpuset *cs, struct tmpmasks *tmp)
static void cpuset_hotplug_workfn(struct work_struct *work)
void cpuset_update_active_cpus(void)
void cpuset_wait_for_hotplug(void)
static int cpuset_track_online_nodes(struct notifier_block *self, unsigned long action, void *arg)
void __init cpuset_init_smp(void)
void cpuset_cpus_allowed(struct task_struct *tsk, struct cpumask *pmask)
void cpuset_cpus_allowed_fallback(struct task_struct *tsk)
void __init cpuset_init_current_mems_allowed(void)
nodemask_t cpuset_mems_allowed(struct task_struct *tsk)
int cpuset_nodemask_valid_mems_allowed(nodemask_t *nodemask)
static struct cpuset *nearest_hardwall_ancestor(struct cpuset *cs)
bool __cpuset_node_allowed(int node, gfp_t gfp_mask)
static int cpuset_spread_node(int *rotor)
int cpuset_mem_spread_node(void)
int cpuset_slab_spread_node(void)
int cpuset_mems_allowed_intersects(const struct task_struct *tsk1, const struct task_struct *tsk2)
void cpuset_print_current_mems_allowed(void)
void __cpuset_memory_pressure_bump(void)
int proc_cpuset_show(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *tsk)
void cpuset_task_status_allowed(struct seq_file *m, struct task_struct *task)
\n
     26 struct cpuset *cs
     17 void
      8 struct cgroup_subsys_state *css
      8 const struct cpuset *cs
      6 struct tmpmasks *tmp
      6 struct task_struct *tsk
      6 struct task_struct *task
      4 struct fmeter *fmp
      4 struct cftype *cft
      3 struct cpumask *new_cpus
      3 struct cgroup_taskset *tset
      3 nodemask_t *new_mems
      2 void *v
      2 struct work_struct *work
      2 struct seq_file *m
      2 struct sched_domain_attr *dattr
      2 struct kernfs_open_file *of
      2 struct cpuset *trialcs
      2 struct cpuset *parent
      2 struct cpumask *pmask
      2 size_t nbytes
      2 s64 val
      2 loff_t off
      2 const char *buf
      2 char *buf
      2 bool mems_updated
      2 bool cpus_updated
      1 void *data
      1 void *arg
      1 unsigned long action
      1 u64 val
      1 struct seq_file *sf
      1 struct seq_file *seq
      1 struct sched_domain_attr **attributes
      1 struct pid *pid
      1 struct pid_namespace *ns
      1 struct notifier_block *self
      1 struct mm_struct *mm
      1 struct file_system_type *fs_type
      1 struct cpuset *trial
      1 struct cpuset *root_cs
      1 struct cpuset *cur
      1 struct cpuset *cpuset
      1 struct cpuset *c
      1 struct cpuset *b
      1 struct cpuset *a
      1 struct cpumask *newmask
      1 struct cgroup_subsys_state *root_css
      1 struct cgroup_subsys_state *parent_css
      1 nodemask_t *pmask
      1 nodemask_t *nodemask
      1 nodemask_t *newmems
      1 ndoms
      1 int val
      1 int turning_on
      1 int *rotor
      1 int node
      1 int flags
      1 int cmd
      1 gfp_t gfp_mask
      1 doms
      1 cpuset_mem_spread_node
      1 cpuset_flagbits_t bit
      1 cpumask_var_t **domains
      1 const struct task_struct *tsk2
      1 const struct task_struct *tsk1
      1 const struct cpuset *q
      1 const struct cpuset *p
      1 const nodemask_t *to
      1 const nodemask_t *from
      1 const char *unused_dev_name
      1 attr
      1 
