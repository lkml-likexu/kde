
EXPORT_SYMBOL_GPL(register_user_hw_breakpoint);
EXPORT_SYMBOL_GPL(modify_user_hw_breakpoint);
EXPORT_SYMBOL_GPL(unregister_hw_breakpoint);
EXPORT_SYMBOL_GPL(register_wide_hw_breakpoint);
EXPORT_SYMBOL_GPL(unregister_wide_hw_breakpoint);
\n
static struct bp_cpuinfo *get_bp_info(int cpu, enum bp_type_idx type)
__weak int hw_breakpoint_weight(struct perf_event *bp)
static inline enum bp_type_idx find_slot_idx(u64 bp_type)
static unsigned int max_task_bp_pinned(int cpu, enum bp_type_idx type)
static int task_bp_pinned(int cpu, struct perf_event *bp, enum bp_type_idx type)
static const struct cpumask *cpumask_of_bp(struct perf_event *bp)
static void fetch_bp_busy_slots(struct bp_busy_slots *slots, struct perf_event *bp, enum bp_type_idx type)
static void fetch_this_slot(struct bp_busy_slots *slots, int weight)
static void toggle_bp_task_slot(struct perf_event *bp, int cpu, enum bp_type_idx type, int weight)
static void toggle_bp_slot(struct perf_event *bp, bool enable, enum bp_type_idx type, int weight)
__weak void arch_unregister_hw_breakpoint(struct perf_event *bp)
static int __reserve_bp_slot(struct perf_event *bp, u64 bp_type)
int reserve_bp_slot(struct perf_event *bp)
static void __release_bp_slot(struct perf_event *bp, u64 bp_type)
void release_bp_slot(struct perf_event *bp)
static int __modify_bp_slot(struct perf_event *bp, u64 old_type, u64 new_type)
static int modify_bp_slot(struct perf_event *bp, u64 old_type, u64 new_type)
int dbg_reserve_bp_slot(struct perf_event *bp)
int dbg_release_bp_slot(struct perf_event *bp)
static int hw_breakpoint_parse(struct perf_event *bp, const struct perf_event_attr *attr, struct arch_hw_breakpoint *hw)
int register_perf_hw_breakpoint(struct perf_event *bp)
struct perf_event * register_user_hw_breakpoint(struct perf_event_attr *attr, perf_overflow_handler_t triggered, void *context, struct task_struct *tsk)
static void hw_breakpoint_copy_attr(struct perf_event_attr *to, struct perf_event_attr *from)
int modify_user_hw_breakpoint_check(struct perf_event *bp, struct perf_event_attr *attr, bool check)
int modify_user_hw_breakpoint(struct perf_event *bp, struct perf_event_attr *attr)
void unregister_hw_breakpoint(struct perf_event *bp)
struct perf_event * __percpu * register_wide_hw_breakpoint(struct perf_event_attr *attr, perf_overflow_handler_t triggered, void *context)
void unregister_wide_hw_breakpoint(struct perf_event * __percpu *cpu_events)
static void bp_perf_event_destroy(struct perf_event *event)
static int hw_breakpoint_event_init(struct perf_event *bp)
static int hw_breakpoint_add(struct perf_event *bp, int flags)
static void hw_breakpoint_del(struct perf_event *bp, int flags)
static void hw_breakpoint_start(struct perf_event *bp, int flags)
static void hw_breakpoint_stop(struct perf_event *bp, int flags)
int __init init_hw_breakpoint(void)
\n
     25 struct perf_event *bp
      6 enum bp_type_idx type
      4 struct perf_event_attr *attr
      4 int flags
      4 int cpu
      3 u64 bp_type
      3 int weight
      2 void *context
      2 u64 old_type
      2 u64 new_type
      2 struct bp_busy_slots *slots
      2 perf_overflow_handler_t triggered
      1 void
      1 unregister_wide_hw_breakpoint
      1 unregister_hw_breakpoint
      1 struct task_struct *tsk
      1 struct perf_event * __percpu *cpu_events
      1 struct perf_event *event
      1 struct perf_event_attr *to
      1 struct perf_event_attr *from
      1 struct arch_hw_breakpoint *hw
      1 register_wide_hw_breakpoint
      1 register_user_hw_breakpoint
      1 modify_user_hw_breakpoint
      1 const struct perf_event_attr *attr
      1 bool enable
      1 bool check
