
EXPORT_SYMBOL_GPL(perf_event_disable);
EXPORT_SYMBOL_GPL(perf_event_enable);
EXPORT_SYMBOL_GPL(perf_event_addr_filters_sync);
EXPORT_SYMBOL_GPL(perf_event_refresh);
EXPORT_SYMBOL_GPL(perf_event_release_kernel);
EXPORT_SYMBOL_GPL(perf_event_read_value);
EXPORT_SYMBOL_GPL(perf_event_update_userpage);
EXPORT_SYMBOL_GPL(perf_register_guest_info_callbacks);
EXPORT_SYMBOL_GPL(perf_unregister_guest_info_callbacks);
EXPORT_SYMBOL_GPL(perf_swevent_get_recursion_context);
EXPORT_SYMBOL_GPL(perf_trace_run_bpf_submit);
EXPORT_SYMBOL_GPL(perf_tp_event);
EXPORT_SYMBOL_GPL(perf_pmu_register);
EXPORT_SYMBOL_GPL(perf_pmu_unregister);
EXPORT_SYMBOL_GPL(perf_event_create_kernel_counter);
EXPORT_SYMBOL_GPL(perf_pmu_migrate_context);
EXPORT_SYMBOL_GPL(perf_event_sysfs_show);
\n
static void remote_function(void *data)
static int task_function_call(struct task_struct *p, remote_function_f func, void *info)
static int cpu_function_call(int cpu, remote_function_f func, void *info)
static inline struct perf_cpu_context * __get_cpu_context(struct perf_event_context *ctx)
static void perf_ctx_lock(struct perf_cpu_context *cpuctx, struct perf_event_context *ctx)
static void perf_ctx_unlock(struct perf_cpu_context *cpuctx, struct perf_event_context *ctx)
static bool is_kernel_event(struct perf_event *event)
static int event_function(void *info)
static void event_function_call(struct perf_event *event, event_f func, void *data)
static void event_function_local(struct perf_event *event, event_f func, void *data)
static void update_perf_cpu_limits(void)
int perf_proc_update_handler(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int perf_cpu_time_max_percent_handler(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static void perf_duration_warn(struct irq_work *w)
void perf_sample_event_took(u64 sample_len_ns)
extern __weak const char *perf_pmu_name(void)
static inline u64 perf_clock(void)
static inline u64 perf_event_clock(struct perf_event *event)
static __always_inline enum perf_event_state __perf_effective_state(struct perf_event *event)
static __always_inline void __perf_update_times(struct perf_event *event, u64 now, u64 *enabled, u64 *running)
static void perf_event_update_time(struct perf_event *event)
static void perf_event_update_sibling_time(struct perf_event *leader)
static void perf_event_set_state(struct perf_event *event, enum perf_event_state state)
static inline bool perf_cgroup_match(struct perf_event *event)
static inline void perf_detach_cgroup(struct perf_event *event)
static inline int is_cgroup_event(struct perf_event *event)
static inline u64 perf_cgroup_event_time(struct perf_event *event)
static inline void __update_cgrp_time(struct perf_cgroup *cgrp)
static inline void update_cgrp_time_from_cpuctx(struct perf_cpu_context *cpuctx)
static inline void update_cgrp_time_from_event(struct perf_event *event)
static inline void perf_cgroup_set_timestamp(struct task_struct *task, struct perf_event_context *ctx)
static void perf_cgroup_switch(struct task_struct *task, int mode)
static inline void perf_cgroup_sched_out(struct task_struct *task, struct task_struct *next)
static inline void perf_cgroup_sched_in(struct task_struct *prev, struct task_struct *task)
static inline int perf_cgroup_connect(int fd, struct perf_event *event, struct perf_event_attr *attr, struct perf_event *group_leader)
static inline void perf_cgroup_set_shadow_time(struct perf_event *event, u64 now)
static inline void list_update_cgroup_event(struct perf_event *event, struct perf_event_context *ctx, bool add)
static inline bool perf_cgroup_match(struct perf_event *event)
static inline void perf_detach_cgroup(struct perf_event *event)
static inline int is_cgroup_event(struct perf_event *event)
static inline void update_cgrp_time_from_event(struct perf_event *event)
static inline void update_cgrp_time_from_cpuctx(struct perf_cpu_context *cpuctx)
static inline void perf_cgroup_sched_out(struct task_struct *task, struct task_struct *next)
static inline void perf_cgroup_sched_in(struct task_struct *prev, struct task_struct *task)
static inline int perf_cgroup_connect(pid_t pid, struct perf_event *event, struct perf_event_attr *attr, struct perf_event *group_leader)
static inline void perf_cgroup_set_timestamp(struct task_struct *task, struct perf_event_context *ctx)
void perf_cgroup_switch(struct task_struct *task, struct task_struct *next)
static inline void perf_cgroup_set_shadow_time(struct perf_event *event, u64 now)
static inline u64 perf_cgroup_event_time(struct perf_event *event)
static inline void list_update_cgroup_event(struct perf_event *event, struct perf_event_context *ctx, bool add)
define PERF_CPU_HRTIMER (1000 / HZ)
static enum hrtimer_restart perf_mux_hrtimer_handler(struct hrtimer *hr)
static void __perf_mux_hrtimer_init(struct perf_cpu_context *cpuctx, int cpu)
static int perf_mux_hrtimer_restart(struct perf_cpu_context *cpuctx)
void perf_pmu_disable(struct pmu *pmu)
void perf_pmu_enable(struct pmu *pmu)
static void perf_event_ctx_activate(struct perf_event_context *ctx)
static void perf_event_ctx_deactivate(struct perf_event_context *ctx)
static void get_ctx(struct perf_event_context *ctx)
static void free_ctx(struct rcu_head *head)
static void put_ctx(struct perf_event_context *ctx)
static struct perf_event_context * perf_event_ctx_lock_nested(struct perf_event *event, int nesting)
static inline struct perf_event_context * perf_event_ctx_lock(struct perf_event *event)
static void perf_event_ctx_unlock(struct perf_event *event, struct perf_event_context *ctx)
static __must_check struct perf_event_context * unclone_ctx(struct perf_event_context *ctx)
static u32 perf_event_pid_type(struct perf_event *event, struct task_struct *p, enum pid_type type)
static u32 perf_event_pid(struct perf_event *event, struct task_struct *p)
static u32 perf_event_tid(struct perf_event *event, struct task_struct *p)
static u64 primary_event_id(struct perf_event *event)
static struct perf_event_context * perf_lock_task_context(struct task_struct *task, int ctxn, unsigned long *flags)
static struct perf_event_context * perf_pin_task_context(struct task_struct *task, int ctxn)
static void perf_unpin_context(struct perf_event_context *ctx)
static void update_context_time(struct perf_event_context *ctx)
static u64 perf_event_time(struct perf_event *event)
static enum event_type_t get_event_type(struct perf_event *event)
static void init_event_group(struct perf_event *event)
static struct perf_event_groups * get_event_groups(struct perf_event *event, struct perf_event_context *ctx)
static void perf_event_groups_init(struct perf_event_groups *groups)
static bool perf_event_groups_less(struct perf_event *left, struct perf_event *right)
static void perf_event_groups_insert(struct perf_event_groups *groups, struct perf_event *event)
static void add_event_to_groups(struct perf_event *event, struct perf_event_context *ctx)
static void perf_event_groups_delete(struct perf_event_groups *groups, struct perf_event *event)
static void del_event_from_groups(struct perf_event *event, struct perf_event_context *ctx)
static struct perf_event * perf_event_groups_first(struct perf_event_groups *groups, int cpu)
static struct perf_event * perf_event_groups_next(struct perf_event *event)
static void list_add_event(struct perf_event *event, struct perf_event_context *ctx)
static inline void perf_event__state_init(struct perf_event *event)
static void __perf_event_read_size(struct perf_event *event, int nr_siblings)
static void __perf_event_header_size(struct perf_event *event, u64 sample_type)
static void perf_event__header_size(struct perf_event *event)
static void perf_event__id_header_size(struct perf_event *event)
static bool perf_event_validate_size(struct perf_event *event)
static void perf_group_attach(struct perf_event *event)
static void list_del_event(struct perf_event *event, struct perf_event_context *ctx)
static void perf_group_detach(struct perf_event *event)
static bool is_orphaned_event(struct perf_event *event)
static inline int __pmu_filter_match(struct perf_event *event)
static inline int pmu_filter_match(struct perf_event *event)
static inline int event_filter_match(struct perf_event *event)
static void event_sched_out(struct perf_event *event, struct perf_cpu_context *cpuctx, struct perf_event_context *ctx)
static void group_sched_out(struct perf_event *group_event, struct perf_cpu_context *cpuctx, struct perf_event_context *ctx)
static void __perf_remove_from_context(struct perf_event *event, struct perf_cpu_context *cpuctx, struct perf_event_context *ctx, void *info)
static void perf_remove_from_context(struct perf_event *event, unsigned long flags)
static void __perf_event_disable(struct perf_event *event, struct perf_cpu_context *cpuctx, struct perf_event_context *ctx, void *info)
static void _perf_event_disable(struct perf_event *event)
void perf_event_disable_local(struct perf_event *event)
void perf_event_disable(struct perf_event *event)
void perf_event_disable_inatomic(struct perf_event *event)
static void perf_set_shadow_time(struct perf_event *event, struct perf_event_context *ctx)
static int event_sched_in(struct perf_event *event, struct perf_cpu_context *cpuctx, struct perf_event_context *ctx)
static int group_sched_in(struct perf_event *group_event, struct perf_cpu_context *cpuctx, struct perf_event_context *ctx)
static int group_can_go_on(struct perf_event *event, struct perf_cpu_context *cpuctx, int can_add_hw)
static void add_event_to_ctx(struct perf_event *event, struct perf_event_context *ctx)
static void task_ctx_sched_out(struct perf_cpu_context *cpuctx, struct perf_event_context *ctx, enum event_type_t event_type)
static void perf_event_sched_in(struct perf_cpu_context *cpuctx, struct perf_event_context *ctx, struct task_struct *task)
static void ctx_resched(struct perf_cpu_context *cpuctx, struct perf_event_context *task_ctx, enum event_type_t event_type)
static int__perf_install_in_context(void *info)
static void perf_install_in_context(struct perf_event_context *ctx, struct perf_event *event, int cpu)
static void __perf_event_enable(struct perf_event *event, struct perf_cpu_context *cpuctx, struct perf_event_context *ctx, void *info)
static void _perf_event_enable(struct perf_event *event)
void perf_event_enable(struct perf_event *event)
static int __perf_event_stop(void *info)
static int perf_event_stop(struct perf_event *event, int restart)
void perf_event_addr_filters_sync(struct perf_event *event)
static int _perf_event_refresh(struct perf_event *event, int refresh)
int perf_event_refresh(struct perf_event *event, int refresh)
static int perf_event_modify_breakpoint(struct perf_event *bp, struct perf_event_attr *attr)
static int perf_event_modify_attr(struct perf_event *event, struct perf_event_attr *attr)
static void ctx_sched_out(struct perf_event_context *ctx, struct perf_cpu_context *cpuctx, enum event_type_t event_type)
static int context_equiv(struct perf_event_context *ctx1, struct perf_event_context *ctx2)
static void __perf_event_sync_stat(struct perf_event *event, struct perf_event *next_event)
static void perf_event_sync_stat(struct perf_event_context *ctx, struct perf_event_context *next_ctx)
static void perf_event_context_sched_out(struct task_struct *task, int ctxn, struct task_struct *next)
void perf_sched_cb_dec(struct pmu *pmu)
void perf_sched_cb_inc(struct pmu *pmu)
static void perf_pmu_sched_task(struct task_struct *prev, struct task_struct *next, bool sched_in)
void __perf_event_task_sched_out(struct task_struct *task, struct task_struct *next)
static void cpu_ctx_sched_out(struct perf_cpu_context *cpuctx, enum event_type_t event_type)
static int visit_groups_merge(struct perf_event_groups *groups, int cpu, int (*func)
(struct perf_event *, void *)
, void *data)
static int pinned_sched_in(struct perf_event *event, void *data)
static int flexible_sched_in(struct perf_event *event, void *data)
static void ctx_pinned_sched_in(struct perf_event_context *ctx, struct perf_cpu_context *cpuctx)
static void ctx_flexible_sched_in(struct perf_event_context *ctx, struct perf_cpu_context *cpuctx)
static void ctx_sched_in(struct perf_event_context *ctx, struct perf_cpu_context *cpuctx, enum event_type_t event_type, struct task_struct *task)
static void cpu_ctx_sched_in(struct perf_cpu_context *cpuctx, enum event_type_t event_type, struct task_struct *task)
static void perf_event_context_sched_in(struct perf_event_context *ctx, struct task_struct *task)
void __perf_event_task_sched_in(struct task_struct *prev, struct task_struct *task)
static u64 perf_calculate_period(struct perf_event *event, u64 nsec, u64 count)
static void perf_adjust_period(struct perf_event *event, u64 nsec, u64 count, bool disable)
static void perf_adjust_freq_unthr_context(struct perf_event_context *ctx, int needs_unthr)
static void rotate_ctx(struct perf_event_context *ctx, struct perf_event *event)
static inline struct perf_event * ctx_first_active(struct perf_event_context *ctx)
static bool perf_rotate_context(struct perf_cpu_context *cpuctx)
void perf_event_task_tick(void)
static int event_enable_on_exec(struct perf_event *event, struct perf_event_context *ctx)
static void perf_event_enable_on_exec(int ctxn)
static int __perf_event_read_cpu(struct perf_event *event, int event_cpu)
static void __perf_event_read(void *info)
static inline u64 perf_event_count(struct perf_event *event)
int perf_event_read_local(struct perf_event *event, u64 *value, u64 *enabled, u64 *running)
static int perf_event_read(struct perf_event *event, bool group)
static void __perf_event_init_context(struct perf_event_context *ctx)
static struct perf_event_context * alloc_perf_context(struct pmu *pmu, struct task_struct *task)
static struct task_struct * find_lively_task_by_vpid(pid_t vpid)
static struct perf_event_context * find_get_context(struct pmu *pmu, struct task_struct *task, struct perf_event *event)
static void free_event_rcu(struct rcu_head *head)
static void detach_sb_event(struct perf_event *event)
static bool is_sb_event(struct perf_event *event)
static void unaccount_pmu_sb_event(struct perf_event *event)
static void unaccount_event_cpu(struct perf_event *event, int cpu)
static void unaccount_freq_event_nohz(void)
static void unaccount_freq_event(void)
static void unaccount_event(struct perf_event *event)
static void perf_sched_delayed(struct work_struct *work)
static int exclusive_event_init(struct perf_event *event)
static void exclusive_event_destroy(struct perf_event *event)
static bool exclusive_event_match(struct perf_event *e1, struct perf_event *e2)
static bool exclusive_event_installable(struct perf_event *event, struct perf_event_context *ctx)
static void _free_event(struct perf_event *event)
static void free_event(struct perf_event *event)
static void perf_remove_from_owner(struct perf_event *event)
static void put_event(struct perf_event *event)
int perf_event_release_kernel(struct perf_event *event)
static int perf_release(struct inode *inode, struct file *file)
static u64 __perf_event_read_value(struct perf_event *event, u64 *enabled, u64 *running)
u64 perf_event_read_value(struct perf_event *event, u64 *enabled, u64 *running)
static int __perf_read_group_add(struct perf_event *leader, u64 read_format, u64 *values)
static int perf_read_group(struct perf_event *event, u64 read_format, char __user *buf)
static int perf_read_one(struct perf_event *event, u64 read_format, char __user *buf)
static bool is_event_hup(struct perf_event *event)
static ssize_t __perf_read(struct perf_event *event, char __user *buf, size_t count)
static ssize_t perf_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static __poll_t perf_poll(struct file *file, poll_table *wait)
static void _perf_event_reset(struct perf_event *event)
static void perf_event_for_each_child(struct perf_event *event, void (*func)
(struct perf_event *)
)
static void perf_event_for_each(struct perf_event *event, void (*func)
(struct perf_event *)
)
static void __perf_event_period(struct perf_event *event, struct perf_cpu_context *cpuctx, struct perf_event_context *ctx, void *info)
static int perf_event_check_period(struct perf_event *event, u64 value)
static int perf_event_period(struct perf_event *event, u64 __user *arg)
static inline int perf_fget_light(int fd, struct fd *p)
static long _perf_ioctl(struct perf_event *event, unsigned int cmd, unsigned long arg)
static long perf_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long perf_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
int perf_event_task_enable(void)
int perf_event_task_disable(void)
static int perf_event_index(struct perf_event *event)
static void calc_timer_values(struct perf_event *event, u64 *now, u64 *enabled, u64 *running)
static void perf_event_init_userpage(struct perf_event *event)
void __weak arch_perf_update_userpage(struct perf_event *event, struct perf_event_mmap_page *userpg, u64 now)
void perf_event_update_userpage(struct perf_event *event)
static vm_fault_t perf_mmap_fault(struct vm_fault *vmf)
static void ring_buffer_attach(struct perf_event *event, struct ring_buffer *rb)
static void ring_buffer_wakeup(struct perf_event *event)
struct ring_buffer *ring_buffer_get(struct perf_event *event)
void ring_buffer_put(struct ring_buffer *rb)
static void perf_mmap_open(struct vm_area_struct *vma)
static void perf_mmap_close(struct vm_area_struct *vma)
static int perf_mmap(struct file *file, struct vm_area_struct *vma)
static int perf_fasync(int fd, struct file *filp, int on)
static inline struct fasync_struct **perf_event_fasync(struct perf_event *event)
void perf_event_wakeup(struct perf_event *event)
static void perf_pending_event(struct irq_work *entry)
int perf_register_guest_info_callbacks(struct perf_guest_info_callbacks *cbs)
int perf_unregister_guest_info_callbacks(struct perf_guest_info_callbacks *cbs)
static void perf_output_sample_regs(struct perf_output_handle *handle, struct pt_regs *regs, u64 mask)
static void perf_sample_regs_user(struct perf_regs *regs_user, struct pt_regs *regs, struct pt_regs *regs_user_copy)
static void perf_sample_regs_intr(struct perf_regs *regs_intr, struct pt_regs *regs)
static u64 perf_ustack_task_size(struct pt_regs *regs)
static u16 perf_sample_ustack_size(u16 stack_size, u16 header_size, struct pt_regs *regs)
static void perf_output_sample_ustack(struct perf_output_handle *handle, u64 dump_size, struct pt_regs *regs)
static void __perf_event_header__init_id(struct perf_event_header *header, struct perf_sample_data *data, struct perf_event *event)
void perf_event_header__init_id(struct perf_event_header *header, struct perf_sample_data *data, struct perf_event *event)
static void __perf_event__output_id_sample(struct perf_output_handle *handle, struct perf_sample_data *data)
void perf_event__output_id_sample(struct perf_event *event, struct perf_output_handle *handle, struct perf_sample_data *sample)
static void perf_output_read_one(struct perf_output_handle *handle, struct perf_event *event, u64 enabled, u64 running)
static void perf_output_read_group(struct perf_output_handle *handle, struct perf_event *event, u64 enabled, u64 running)
static void perf_output_read(struct perf_output_handle *handle, struct perf_event *event)
void perf_output_sample(struct perf_output_handle *handle, struct perf_event_header *header, struct perf_sample_data *data, struct perf_event *event)
static u64 perf_virt_to_phys(u64 virt)
struct perf_callchain_entry * perf_callchain(struct perf_event *event, struct pt_regs *regs)
void perf_prepare_sample(struct perf_event_header *header, struct perf_sample_data *data, struct perf_event *event, struct pt_regs *regs)
static __always_inline void __perf_event_output(struct perf_event *event, struct perf_sample_data *data, struct pt_regs *regs, int (*output_begin)
(struct perf_output_handle *, struct perf_event *, unsigned int)
)
void perf_event_output_forward(struct perf_event *event, struct perf_sample_data *data, struct pt_regs *regs)
void perf_event_output_backward(struct perf_event *event, struct perf_sample_data *data, struct pt_regs *regs)
void perf_event_output(struct perf_event *event, struct perf_sample_data *data, struct pt_regs *regs)
static void perf_event_read_event(struct perf_event *event, struct task_struct *task)
static void perf_iterate_ctx(struct perf_event_context *ctx, perf_iterate_f output, void *data, bool all)
static void perf_iterate_sb_cpu(perf_iterate_f output, void *data)
static void perf_iterate_sb(perf_iterate_f output, void *data, struct perf_event_context *task_ctx)
static void perf_event_addr_filters_exec(struct perf_event *event, void *data)
void perf_event_exec(void)
static void __perf_event_output_stop(struct perf_event *event, void *data)
static int __perf_pmu_output_stop(void *info)
static void perf_pmu_output_stop(struct perf_event *event)
static int perf_event_task_match(struct perf_event *event)
static void perf_event_task_output(struct perf_event *event, void *data)
static void perf_event_task(struct task_struct *task, struct perf_event_context *task_ctx, int new)
void perf_event_fork(struct task_struct *task)
static int perf_event_comm_match(struct perf_event *event)
static void perf_event_comm_output(struct perf_event *event, void *data)
static void perf_event_comm_event(struct perf_comm_event *comm_event)
void perf_event_comm(struct task_struct *task, bool exec)
static int perf_event_namespaces_match(struct perf_event *event)
static void perf_event_namespaces_output(struct perf_event *event, void *data)
static void perf_fill_ns_link_info(struct perf_ns_link_info *ns_link_info, struct task_struct *task, const struct proc_ns_operations *ns_ops)
void perf_event_namespaces(struct task_struct *task)
static int perf_event_mmap_match(struct perf_event *event, void *data)
static void perf_event_mmap_output(struct perf_event *event, void *data)
static void perf_event_mmap_event(struct perf_mmap_event *mmap_event)
static bool perf_addr_filter_match(struct perf_addr_filter *filter, struct file *file, unsigned long offset, unsigned long size)
static void __perf_addr_filters_adjust(struct perf_event *event, void *data)
static void perf_addr_filters_adjust(struct vm_area_struct *vma)
void perf_event_mmap(struct vm_area_struct *vma)
void perf_event_aux_event(struct perf_event *event, unsigned long head, unsigned long size, u64 flags)
void perf_log_lost_samples(struct perf_event *event, u64 lost)
static int perf_event_switch_match(struct perf_event *event)
static void perf_event_switch_output(struct perf_event *event, void *data)
static void perf_event_switch(struct task_struct *task, struct task_struct *next_prev, bool sched_in)
static void perf_log_throttle(struct perf_event *event, int enable)
void perf_event_itrace_started(struct perf_event *event)
static void perf_log_itrace_start(struct perf_event *event)
static int __perf_event_account_interrupt(struct perf_event *event, int throttle)
int perf_event_account_interrupt(struct perf_event *event)
static int __perf_event_overflow(struct perf_event *event, int throttle, struct perf_sample_data *data, struct pt_regs *regs)
int perf_event_overflow(struct perf_event *event, struct perf_sample_data *data, struct pt_regs *regs)
u64 perf_swevent_set_period(struct perf_event *event)
static void perf_swevent_overflow(struct perf_event *event, u64 overflow, struct perf_sample_data *data, struct pt_regs *regs)
static void perf_swevent_event(struct perf_event *event, u64 nr, struct perf_sample_data *data, struct pt_regs *regs)
static int perf_exclude_event(struct perf_event *event, struct pt_regs *regs)
static int perf_swevent_match(struct perf_event *event, enum perf_type_id type, u32 event_id, struct perf_sample_data *data, struct pt_regs *regs)
static inline u64 swevent_hash(u64 type, u32 event_id)
static inline struct hlist_head * __find_swevent_head(struct swevent_hlist *hlist, u64 type, u32 event_id)
static inline struct hlist_head * find_swevent_head_rcu(struct swevent_htable *swhash, u64 type, u32 event_id)
static inline struct hlist_head * find_swevent_head(struct swevent_htable *swhash, struct perf_event *event)
static void do_perf_sw_event(enum perf_type_id type, u32 event_id, u64 nr, struct perf_sample_data *data, struct pt_regs *regs)
int perf_swevent_get_recursion_context(void)
void perf_swevent_put_recursion_context(int rctx)
void ___perf_sw_event(u32 event_id, u64 nr, struct pt_regs *regs, u64 addr)
void __perf_sw_event(u32 event_id, u64 nr, struct pt_regs *regs, u64 addr)
static void perf_swevent_read(struct perf_event *event)
static int perf_swevent_add(struct perf_event *event, int flags)
static void perf_swevent_del(struct perf_event *event, int flags)
static void perf_swevent_start(struct perf_event *event, int flags)
static void perf_swevent_stop(struct perf_event *event, int flags)
static inline struct swevent_hlist * swevent_hlist_deref(struct swevent_htable *swhash)
static void swevent_hlist_release(struct swevent_htable *swhash)
static void swevent_hlist_put_cpu(int cpu)
static void swevent_hlist_put(void)
static int swevent_hlist_get_cpu(int cpu)
static int swevent_hlist_get(void)
static void sw_perf_event_destroy(struct perf_event *event)
static int perf_swevent_init(struct perf_event *event)
static int perf_tp_filter_match(struct perf_event *event, struct perf_sample_data *data)
static int perf_tp_event_match(struct perf_event *event, struct perf_sample_data *data, struct pt_regs *regs)
void perf_trace_run_bpf_submit(void *raw_data, int size, int rctx, struct trace_event_call *call, u64 count, struct pt_regs *regs, struct hlist_head *head, struct task_struct *task)
void perf_tp_event(u16 event_type, u64 count, void *record, int entry_size, struct pt_regs *regs, struct hlist_head *head, int rctx, struct task_struct *task)
static void tp_perf_event_destroy(struct perf_event *event)
static int perf_tp_event_init(struct perf_event *event)
static int perf_kprobe_event_init(struct perf_event *event)
static int perf_uprobe_event_init(struct perf_event *event)
static inline void perf_tp_register(void)
static void perf_event_free_filter(struct perf_event *event)
static void bpf_overflow_handler(struct perf_event *event, struct perf_sample_data *data, struct pt_regs *regs)
static int perf_event_set_bpf_handler(struct perf_event *event, u32 prog_fd)
static void perf_event_free_bpf_handler(struct perf_event *event)
WRITE_ONCE(event->overflow_handler, event->orig_overflow_handler)
;event->prog = NULL;bpf_prog_put(prog)
; } static int perf_event_set_bpf_handler(struct perf_event *event, u32 prog_fd)
WRITE_ONCE(event->overflow_handler, event->orig_overflow_handler)
;event->prog = NULL;bpf_prog_put(prog)
; } static int perf_event_set_bpf_handler(struct perf_event *event, u32 prog_fd)
return -EOPNOTSUPP; } static void perf_event_free_bpf_handler(struct perf_event *event)
static inline bool perf_event_is_tracing(struct perf_event *event)
static int perf_event_set_bpf_prog(struct perf_event *event, u32 prog_fd)
static void perf_event_free_bpf_prog(struct perf_event *event)
static inline void perf_tp_register(void)
static void perf_event_free_filter(struct perf_event *event)
static int perf_event_set_bpf_prog(struct perf_event *event, u32 prog_fd)
static void perf_event_free_bpf_prog(struct perf_event *event)
void perf_bp_event(struct perf_event *bp, void *data)
static struct perf_addr_filter * perf_addr_filter_new(struct perf_event *event, struct list_head *filters)
static void free_filters_list(struct list_head *filters)
static void perf_addr_filters_splice(struct perf_event *event, struct list_head *head)
static unsigned long perf_addr_filter_apply(struct perf_addr_filter *filter, struct mm_struct *mm)
static void perf_event_addr_filters_apply(struct perf_event *event)
static int perf_event_parse_addr_filter(struct perf_event *event, char *fstr, struct list_head *filters)
static int perf_event_set_addr_filter(struct perf_event *event, char *filter_str)
static int perf_event_set_filter(struct perf_event *event, void __user *arg)
static enum hrtimer_restart perf_swevent_hrtimer(struct hrtimer *hrtimer)
static void perf_swevent_start_hrtimer(struct perf_event *event)
static void perf_swevent_cancel_hrtimer(struct perf_event *event)
static void perf_swevent_init_hrtimer(struct perf_event *event)
static void cpu_clock_event_update(struct perf_event *event)
static void cpu_clock_event_start(struct perf_event *event, int flags)
static void cpu_clock_event_stop(struct perf_event *event, int flags)
static int cpu_clock_event_add(struct perf_event *event, int flags)
static void cpu_clock_event_del(struct perf_event *event, int flags)
static void cpu_clock_event_read(struct perf_event *event)
static int cpu_clock_event_init(struct perf_event *event)
static void task_clock_event_update(struct perf_event *event, u64 now)
static void task_clock_event_start(struct perf_event *event, int flags)
static void task_clock_event_stop(struct perf_event *event, int flags)
static int task_clock_event_add(struct perf_event *event, int flags)
static void task_clock_event_del(struct perf_event *event, int flags)
static void task_clock_event_read(struct perf_event *event)
static int task_clock_event_init(struct perf_event *event)
static void perf_pmu_nop_void(struct pmu *pmu)
static void perf_pmu_nop_txn(struct pmu *pmu, unsigned int flags)
static int perf_pmu_nop_int(struct pmu *pmu)
static int perf_event_nop_int(struct perf_event *event, u64 value)
static void perf_pmu_start_txn(struct pmu *pmu, unsigned int flags)
static int perf_pmu_commit_txn(struct pmu *pmu)
static void perf_pmu_cancel_txn(struct pmu *pmu)
static int perf_event_idx_default(struct perf_event *event)
static struct perf_cpu_context __percpu *find_pmu_context(int ctxn)
static void free_pmu_context(struct pmu *pmu)
static ssize_t nr_addr_filters_show(struct device *dev, struct device_attribute *attr, char *page)
static ssize_t type_show(struct device *dev, struct device_attribute *attr, char *page)
static ssize_t perf_event_mux_interval_ms_show(struct device *dev, struct device_attribute *attr, char *page)
static ssize_t perf_event_mux_interval_ms_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static void pmu_dev_release(struct device *dev)
static int pmu_dev_alloc(struct pmu *pmu)
int perf_pmu_register(struct pmu *pmu, const char *name, int type)
void perf_pmu_unregister(struct pmu *pmu)
static int perf_try_init_event(struct pmu *pmu, struct perf_event *event)
static struct pmu *perf_init_event(struct perf_event *event)
static void attach_sb_event(struct perf_event *event)
static void account_pmu_sb_event(struct perf_event *event)
static void account_event_cpu(struct perf_event *event, int cpu)
static void account_freq_event_nohz(void)
static void account_freq_event(void)
static void account_event(struct perf_event *event)
static struct perf_event * perf_event_alloc(struct perf_event_attr *attr, int cpu, struct task_struct *task, struct perf_event *group_leader, struct perf_event *parent_event, perf_overflow_handler_t overflow_handler, void *context, int cgroup_fd)
static int perf_copy_attr(struct perf_event_attr __user *uattr, struct perf_event_attr *attr)
static int perf_event_set_output(struct perf_event *event, struct perf_event *output_event)
static void mutex_lock_double(struct mutex *a, struct mutex *b)
static int perf_event_set_clock(struct perf_event *event, clockid_t clk_id)
static struct perf_event_context * __perf_event_ctx_lock_double(struct perf_event *group_leader, struct perf_event_context *ctx)
SYSCALL_DEFINE5(perf_event_open, struct perf_event_attr __user *, attr_uptr, pid_t, pid, int, cpu, int, group_fd, unsigned long, flags)
struct perf_event * perf_event_create_kernel_counter(struct perf_event_attr *attr, int cpu, struct task_struct *task, perf_overflow_handler_t overflow_handler, void *context)
void perf_pmu_migrate_context(struct pmu *pmu, int src_cpu, int dst_cpu)
static void sync_child_event(struct perf_event *child_event, struct task_struct *child)
static void perf_event_exit_event(struct perf_event *child_event, struct perf_event_context *child_ctx, struct task_struct *child)
static void perf_event_exit_task_context(struct task_struct *child, int ctxn)
void perf_event_exit_task(struct task_struct *child)
static void perf_free_event(struct perf_event *event, struct perf_event_context *ctx)
void perf_event_free_task(struct task_struct *task)
void perf_event_delayed_put(struct task_struct *task)
struct file *perf_event_get(unsigned int fd)
const struct perf_event *perf_get_event(struct file *file)
const struct perf_event_attr *perf_event_attrs(struct perf_event *event)
static struct perf_event * inherit_event(struct perf_event *parent_event, struct task_struct *parent, struct perf_event_context *parent_ctx, struct task_struct *child, struct perf_event *group_leader, struct perf_event_context *child_ctx)
static int inherit_group(struct perf_event *parent_event, struct task_struct *parent, struct perf_event_context *parent_ctx, struct task_struct *child, struct perf_event_context *child_ctx)
static int inherit_task_group(struct perf_event *event, struct task_struct *parent, struct perf_event_context *parent_ctx, struct task_struct *child, int ctxn, int *inherited_all)
static int perf_event_init_context(struct task_struct *child, int ctxn)
int perf_event_init_task(struct task_struct *child)
static void __init perf_event_init_all_cpus(void)
void perf_swevent_init_cpu(unsigned int cpu)
static void __perf_event_exit_context(void *__info)
static void perf_event_exit_cpu_context(int cpu)
int perf_event_init_cpu(unsigned int cpu)
int perf_event_exit_cpu(unsigned int cpu)
static int perf_reboot(struct notifier_block *notifier, unsigned long val, void *v)
void __init perf_event_init(void)
ssize_t perf_event_sysfs_show(struct device *dev, struct device_attribute *attr, char *page)
static int __init perf_event_sysfs_init(void)
static struct cgroup_subsys_state * perf_cgroup_css_alloc(struct cgroup_subsys_state *parent_css)
static void perf_cgroup_css_free(struct cgroup_subsys_state *css)
static int __perf_cgroup_move(void *info)
static void perf_cgroup_attach(struct cgroup_taskset *tset)
\n
    228 struct perf_event *event
     48 struct perf_event_context *ctx
     32 struct task_struct *task
     25 struct pt_regs *regs
     25 struct perf_cpu_context *cpuctx
     19 void
     18 void *data
     18 struct pmu *pmu
     18 struct perf_sample_data *data
     12 void *info
     12 int flags
     12 int cpu
      9 struct task_struct *child
      8 struct perf_output_handle *handle
      8 struct file *file
      8 int ctxn
      7 u32 event_id
      7 struct perf_event_attr *attr
      6 struct task_struct *next
      6 struct device *dev
      6 enum event_type_t event_type
      5 u64 *running
      5 u64 now
      5 u64 *enabled
      5 u32 prog_fd
      5 struct vm_area_struct *vma
      5 struct perf_event_groups *groups
      5 struct perf_event *group_leader
      5 struct device_attribute *attr
      4 u64 nr
      4 u64 count
      4 struct task_struct *prev
      4 struct task_struct *p
      4 struct swevent_htable *swhash
      4 struct perf_event_header *header
      4 struct perf_event *
      4 char __user *buf
      4 char *page
      3 unsigned long arg
      3 unsigned int cpu
      3 unsigned int cmd
      3 u64 type
      3 u64 read_format
      3 struct task_struct *parent
      3 struct perf_event *parent_event
      3 struct perf_event_context *task_ctx
      3 struct perf_event_context *parent_ctx
      3 struct perf_event_context *child_ctx
      3 struct list_head *filters
      3 size_t count
      3 perf_iterate_f output
      3 loff_t *ppos
      3 int rctx
      3 int fd
      2 void __user *buffer
      2 void *func
      2 void *context
      2 unsigned long size
      2 unsigned int flags
      2 u64 value
      2 u64 running
      2 u64 nsec
      2 u64 enabled
      2 u64 addr
      2 struct ring_buffer *rb
      2 struct rcu_head *head
      2 struct perf_guest_info_callbacks *cbs
      2 struct perf_event *leader
      2 struct perf_event *group_event
      2 struct perf_event *child_event
      2 struct perf_event *bp
      2 struct perf_addr_filter *filter
      2 struct hlist_head *head
      2 struct ctl_table *table
      2 size_t *lenp
      2 remote_function_f func
      2 prog
      2 perf_overflow_handler_t overflow_handler
      2 int write
      2 int throttle
      2 int refresh
      2 int
      2 event->overflow_handler
      2 event->orig_overflow_handler
      2 event_f func
      2 enum perf_type_id type
      2 bool sched_in
      2 bool add
      1 void *v
      1 void __user *arg
      1 void *record
      1 void *raw_data
      1 void *__info
      1 void *
      1 unsigned long val
      1 unsigned long offset
      1 unsigned long head
      1 unsigned long *flags
      1 unsigned long flags
      1 unsigned long
      1 unsigned int fd
      1 unsigned int
      1 u64 virt
      1 u64 *values
      1 u64 *value
      1 u64 __user *arg
      1 u64 sample_type
      1 u64 sample_len_ns
      1 u64 overflow
      1 u64 *now
      1 u64 mask
      1 u64 lost
      1 u64 flags
      1 u64 dump_size
      1 u16 stack_size
      1 u16 header_size
      1 u16 event_type
      1 struct work_struct *work
      1 struct vm_fault *vmf
      1 struct trace_event_call *call
      1 struct task_struct *next_prev
      1 struct swevent_hlist *hlist
      1 struct pt_regs *regs_user_copy
      1 struct perf_sample_data *sample
      1 struct perf_regs *regs_user
      1 struct perf_regs *regs_intr
      1 struct perf_output_handle *
      1 struct perf_ns_link_info *ns_link_info
      1 struct perf_mmap_event *mmap_event
      1 struct perf_event *right
      1 struct perf_event *output_event
      1 struct perf_event *next_event
      1 struct perf_event_mmap_page *userpg
      1 struct perf_event *left
      1 struct perf_event *e2
      1 struct perf_event *e1
      1 struct perf_event_context *next_ctx
      1 struct perf_event_context *ctx2
      1 struct perf_event_context *ctx1
      1 struct perf_event_attr __user *uattr
      1 struct perf_event_attr __user *
      1 struct perf_comm_event *comm_event
      1 struct perf_cgroup *cgrp
      1 struct notifier_block *notifier
      1 struct mutex *b
      1 struct mutex *a
      1 struct mm_struct *mm
      1 struct list_head *head
      1 struct irq_work *w
      1 struct irq_work *entry
      1 struct inode *inode
      1 struct hrtimer *hrtimer
      1 struct hrtimer *hr
      1 struct file *filp
      1 struct fd *p
      1 struct cgroup_taskset *tset
      1 struct cgroup_subsys_state *parent_css
      1 struct cgroup_subsys_state *css
      1 poll_table *wait
      1 pid_t vpid
      1 pid_t pid
      1 pid_t
      1 pid
      1 perf_unregister_guest_info_callbacks
      1 perf_trace_run_bpf_submit
      1 perf_tp_event
      1 perf_swevent_get_recursion_context
      1 perf_register_guest_info_callbacks
      1 perf_pmu_unregister
      1 perf_pmu_register
      1 perf_pmu_migrate_context
      1 perf_event_update_userpage
      1 perf_event_sysfs_show
      1 perf_event_release_kernel
      1 perf_event_refresh
      1 perf_event_read_value
      1 perf_event_open
      1 perf_event_enable
      1 perf_event_disable
      1 perf_event_create_kernel_counter
      1 perf_event_addr_filters_sync
      1 int type
      1 int src_cpu
      1 int size
      1 int restart
      1 int *output_begin
      1 int on
      1 int nr_siblings
      1 int new
      1 int nesting
      1 int needs_unthr
      1 int mode
      1 int *inherited_all
      1 int *func
      1 int event_cpu
      1 int entry_size
      1 int enable
      1 int dst_cpu
      1 int cgroup_fd
      1 int can_add_hw
      1 group_fd
      1 flags
      1 enum pid_type type
      1 enum perf_event_state state
      1 cpu
      1 const struct proc_ns_operations *ns_ops
      1 const char *name
      1 const char *buf
      1 clockid_t clk_id
      1 char *fstr
      1 char *filter_str
      1 bool group
      1 bool exec
      1 bool disable
      1 bool all
      1 attr_uptr
      1 1000 / HZ
