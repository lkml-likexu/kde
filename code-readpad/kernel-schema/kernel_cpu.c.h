
EXPORT_SYMBOL_GPL(cpuhp_tasks_frozen);
EXPORT_SYMBOL_GPL(cpus_read_lock);
EXPORT_SYMBOL_GPL(cpus_read_trylock);
EXPORT_SYMBOL_GPL(cpus_read_unlock);
EXPORT_SYMBOL_GPL(cpu_hotplug_disable);
EXPORT_SYMBOL_GPL(cpu_hotplug_enable);
EXPORT_SYMBOL_GPL(cpu_up);
EXPORT_SYMBOL_GPL(__cpuhp_state_add_instance);
EXPORT_SYMBOL_GPL(__cpuhp_state_remove_instance);
EXPORT_SYMBOL_GPL(cpu_bit_bitmap);
\n
static inline void cpuhp_lock_acquire(bool bringup)
static inline void cpuhp_lock_release(bool bringup)
static struct cpuhp_step *cpuhp_get_step(enum cpuhp_state state)
static int cpuhp_invoke_callback(unsigned int cpu, enum cpuhp_state state, bool bringup, struct hlist_node *node, struct hlist_node **lastp)
static bool cpuhp_is_ap_state(enum cpuhp_state state)
static inline void wait_for_ap_thread(struct cpuhp_cpu_state *st, bool bringup)
static inline void complete_ap_thread(struct cpuhp_cpu_state *st, bool bringup)
static bool cpuhp_is_atomic_state(enum cpuhp_state state)
void cpu_maps_update_begin(void)
void cpu_maps_update_done(void)
void cpus_read_lock(void)
int cpus_read_trylock(void)
void cpus_read_unlock(void)
void cpus_write_lock(void)
void cpus_write_unlock(void)
void lockdep_assert_cpus_held(void)
static void lockdep_acquire_cpus_lock(void)
static void lockdep_release_cpus_lock(void)
void cpu_hotplug_disable(void)
static void __cpu_hotplug_enable(void)
void cpu_hotplug_enable(void)
static void lockdep_acquire_cpus_lock(void)
static void lockdep_release_cpus_lock(void)
void __init cpu_smt_disable(bool force)
void __init cpu_smt_check_topology(void)
static int __init smt_cmdline_disable(char *str)
static inline bool cpu_smt_allowed(unsigned int cpu)
static inline enum cpuhp_state cpuhp_set_state(struct cpuhp_cpu_state *st, enum cpuhp_state target)
static inline void cpuhp_reset_state(struct cpuhp_cpu_state *st, enum cpuhp_state prev_state)
static void __cpuhp_kick_ap(struct cpuhp_cpu_state *st)
static int cpuhp_kick_ap(struct cpuhp_cpu_state *st, enum cpuhp_state target)
static int bringup_wait_for_ap(unsigned int cpu)
static int bringup_cpu(unsigned int cpu)
static void undo_cpu_up(unsigned int cpu, struct cpuhp_cpu_state *st)
static int cpuhp_up_callbacks(unsigned int cpu, struct cpuhp_cpu_state *st, enum cpuhp_state target)
static void cpuhp_create(unsigned int cpu)
static int cpuhp_should_run(unsigned int cpu)
static void cpuhp_thread_fun(unsigned int cpu)
static int cpuhp_invoke_ap_callback(int cpu, enum cpuhp_state state, bool bringup, struct hlist_node *node)
static int cpuhp_kick_ap_work(unsigned int cpu)
void __init cpuhp_threads_init(void)
void clear_tasks_mm_cpumask(int cpu)
static int take_cpu_down(void *_param)
static int takedown_cpu(unsigned int cpu)
static void cpuhp_complete_idle_dead(void *arg)
void cpuhp_report_idle_dead(void)
static void undo_cpu_down(unsigned int cpu, struct cpuhp_cpu_state *st)
static int cpuhp_down_callbacks(unsigned int cpu, struct cpuhp_cpu_state *st, enum cpuhp_state target)
static int __ref _cpu_down(unsigned int cpu, int tasks_frozen, enum cpuhp_state target)
static int cpu_down_maps_locked(unsigned int cpu, enum cpuhp_state target)
static int do_cpu_down(unsigned int cpu, enum cpuhp_state target)
int cpu_down(unsigned int cpu)
void notify_cpu_starting(unsigned int cpu)
void cpuhp_online_idle(enum cpuhp_state state)
static int _cpu_up(unsigned int cpu, int tasks_frozen, enum cpuhp_state target)
static int do_cpu_up(unsigned int cpu, enum cpuhp_state target)
int cpu_up(unsigned int cpu)
int freeze_secondary_cpus(int primary)
void __weak arch_enable_nonboot_cpus_begin(void)
void __weak arch_enable_nonboot_cpus_end(void)
void enable_nonboot_cpus(void)
static int __init alloc_frozen_cpus(void)
static int cpu_hotplug_pm_callback(struct notifier_block *nb, unsigned long action, void *ptr)
static int __init cpu_hotplug_pm_sync_init(void)
static int cpuhp_cb_check(enum cpuhp_state state)
static int cpuhp_reserve_state(enum cpuhp_state state)
static int cpuhp_store_callbacks(enum cpuhp_state state, const char *name, int (*startup)
(unsigned int cpu)
, int (*teardown)
(unsigned int cpu)
, bool multi_instance)
static void *cpuhp_get_teardown_cb(enum cpuhp_state state)
static int cpuhp_issue_call(int cpu, enum cpuhp_state state, bool bringup, struct hlist_node *node)
static void cpuhp_rollback_install(int failedcpu, enum cpuhp_state state, struct hlist_node *node)
int __cpuhp_state_add_instance_cpuslocked(enum cpuhp_state state, struct hlist_node *node, bool invoke)
int __cpuhp_state_add_instance(enum cpuhp_state state, struct hlist_node *node, bool invoke)
int __cpuhp_setup_state_cpuslocked(enum cpuhp_state state, const char *name, bool invoke, int (*startup)
(unsigned int cpu)
, int (*teardown)
(unsigned int cpu)
, bool multi_instance)
int __cpuhp_setup_state(enum cpuhp_state state, const char *name, bool invoke, int (*startup)
(unsigned int cpu)
, int (*teardown)
(unsigned int cpu)
, bool multi_instance)
int __cpuhp_state_remove_instance(enum cpuhp_state state, struct hlist_node *node, bool invoke)
void __cpuhp_remove_state_cpuslocked(enum cpuhp_state state, bool invoke)
void __cpuhp_remove_state(enum cpuhp_state state, bool invoke)
static ssize_t show_cpuhp_state(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t write_cpuhp_target(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t show_cpuhp_target(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t write_cpuhp_fail(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t show_cpuhp_fail(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t show_cpuhp_states(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t show_smt_control(struct device *dev, struct device_attribute *attr, char *buf)
static void cpuhp_offline_cpu_device(unsigned int cpu)
static void cpuhp_online_cpu_device(unsigned int cpu)
static int cpuhp_smt_disable(enum cpuhp_smt_control ctrlval)
static int cpuhp_smt_enable(void)
static ssize_t store_smt_control(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t show_smt_active(struct device *dev, struct device_attribute *attr, char *buf)
static int __init cpu_smt_state_init(void)
static int __init cpuhp_sysfs_init(void)
void init_cpu_present(const struct cpumask *src)
void init_cpu_possible(const struct cpumask *src)
void init_cpu_online(const struct cpumask *src)
void __init boot_cpu_init(void)
void __init boot_cpu_hotplug_init(void)
\n
     29 unsigned int cpu
     28 void
     19 enum cpuhp_state state
     10 struct cpuhp_cpu_state *st
      9 struct device *dev
      9 struct device_attribute *attr
      9 enum cpuhp_state target
      7 struct hlist_node *node
      7 bool invoke
      7 bool bringup
      6 char *buf
      3 *teardown
      3 size_t count
      3 int *startup
      3 int cpu
      3 const struct cpumask *src
      3 const char *name
      3 const char *buf
      2 int tasks_frozen
      1 void *ptr
      1 void *_param
      1 void *arg
      1 unsigned long action
      1 struct notifier_block *nb
      1 struct hlist_node **lastp
      1 int primary
      1 int failedcpu
      1 enum cpuhp_state prev_state
      1 enum cpuhp_smt_control ctrlval
      1 cpu_up
      1 cpus_read_unlock
      1 cpus_read_trylock
      1 cpus_read_lock
      1 cpuhp_tasks_frozen
      1 __cpuhp_state_remove_instance
      1 __cpuhp_state_add_instance
      1 cpu_hotplug_enable
      1 cpu_hotplug_disable
      1 cpu_bit_bitmap
      1 char *str
      1 bool force
