
EXPORT_SYMBOL_GPL(perf_guest_get_msrs);
static u64 intel_perfmon_event_map[PERF_COUNT_HW_MAX] __read_mostly = static struct event_constraint intel_core_event_constraints[] __read_mostly = static struct event_constraint intel_core2_event_constraints[] __read_mostly = static struct event_constraint intel_nehalem_event_constraints[] __read_mostly = static struct extra_reg intel_nehalem_extra_regs[] __read_mostly = static struct event_constraint intel_westmere_event_constraints[] __read_mostly = static struct event_constraint intel_snb_event_constraints[] __read_mostly = static struct event_constraint intel_ivb_event_constraints[] __read_mostly = static struct extra_reg intel_westmere_extra_regs[] __read_mostly = static struct event_constraint intel_v1_event_constraints[] __read_mostly = static struct event_constraint intel_gen_event_constraints[] __read_mostly = static struct event_constraint intel_slm_event_constraints[] __read_mostly = static u64 intel_pmu_event_map(int hw_event)
static __initconst const u64 skl_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 skl_hw_cache_extra_regs [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 snb_hw_cache_extra_regs [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 snb_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 hsw_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 hsw_hw_cache_extra_regs [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 westmere_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 nehalem_hw_cache_extra_regs [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 nehalem_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 core2_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 atom_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static struct extra_reg intel_slm_extra_regs[] __read_mostly = static __initconst const u64 slm_hw_cache_extra_regs [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static __initconst const u64 slm_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] =static void __intel_pmu_disable_all(void)
static void intel_pmu_disable_all(void)
static void __intel_pmu_enable_all(int added, bool pmi)
static void intel_pmu_enable_all(int added)
static void intel_pmu_nhm_workaround(void)
static void intel_pmu_nhm_enable_all(int added)
static void enable_counter_freeze(void)
static void disable_counter_freeze(void)
static inline u64 intel_pmu_get_status(void)
static inline void intel_pmu_ack_status(u64 ack)
static void intel_pmu_disable_fixed(struct hw_perf_event *hwc)
static inline bool event_is_checkpointed(struct perf_event *event)
static void intel_pmu_disable_event(struct perf_event *event)
static void intel_pmu_del_event(struct perf_event *event)
static void intel_pmu_read_event(struct perf_event *event)
static void intel_pmu_enable_fixed(struct perf_event *event)
static void intel_pmu_enable_event(struct perf_event *event)
static void intel_pmu_add_event(struct perf_event *event)
int intel_pmu_save_and_restart(struct perf_event *event)
static void intel_pmu_reset(void)
static int handle_pmi_common(struct pt_regs *regs, u64 status)
static bool disable_counter_freezing; static int __init intel_perf_counter_freezing_setup(char *s)
static int intel_pmu_handle_irq_v4(struct pt_regs *regs)
static int intel_pmu_handle_irq(struct pt_regs *regs)
static struct event_constraint * intel_bts_constraints(struct perf_event *event)
static int intel_alt_er(int idx, u64 config)
static void intel_fixup_er(struct perf_event *event, int idx)
static struct event_constraint * __intel_shared_reg_get_constraints(struct cpu_hw_events *cpuc, struct perf_event *event, struct hw_perf_event_extra *reg)
static void __intel_shared_reg_put_constraints(struct cpu_hw_events *cpuc, struct hw_perf_event_extra *reg)
static struct event_constraint * intel_shared_regs_constraints(struct cpu_hw_events *cpuc, struct perf_event *event)
struct event_constraint * x86_get_event_constraints(struct cpu_hw_events *cpuc, int idx, struct perf_event *event)
static struct event_constraint * __intel_get_event_constraints(struct cpu_hw_events *cpuc, int idx, struct perf_event *event)
static void intel_start_scheduling(struct cpu_hw_events *cpuc)
static void intel_commit_scheduling(struct cpu_hw_events *cpuc, int idx, int cntr)
static void intel_stop_scheduling(struct cpu_hw_events *cpuc)
static struct event_constraint * intel_get_excl_constraints(struct cpu_hw_events *cpuc, struct perf_event *event, int idx, struct event_constraint *c)
static struct event_constraint * intel_get_event_constraints(struct cpu_hw_events *cpuc, int idx, struct perf_event *event)
static void intel_put_excl_constraints(struct cpu_hw_events *cpuc, struct perf_event *event)
static void intel_put_shared_regs_event_constraints(struct cpu_hw_events *cpuc, struct perf_event *event)
static void intel_put_event_constraints(struct cpu_hw_events *cpuc, struct perf_event *event)
static void intel_pebs_aliases_core2(struct perf_event *event)
static void intel_pebs_aliases_snb(struct perf_event *event)
static void intel_pebs_aliases_precdist(struct perf_event *event)
static void intel_pebs_aliases_ivb(struct perf_event *event)
static void intel_pebs_aliases_skl(struct perf_event *event)
static unsigned long intel_pmu_large_pebs_flags(struct perf_event *event)
static int intel_pmu_hw_config(struct perf_event *event)
struct perf_guest_switch_msr *perf_guest_get_msrs(int *nr)
static struct perf_guest_switch_msr *intel_guest_get_msrs(int *nr)
static struct perf_guest_switch_msr *core_guest_get_msrs(int *nr)
static void core_pmu_enable_event(struct perf_event *event)
static void core_pmu_enable_all(int added)
static int hsw_hw_config(struct perf_event *event)
static struct event_constraint * hsw_get_event_constraints(struct cpu_hw_events *cpuc, int idx, struct perf_event *event)
static struct event_constraint * glp_get_event_constraints(struct cpu_hw_events *cpuc, int idx, struct perf_event *event)
static u64 bdw_limit_period(struct perf_event *event, u64 left)
ssize_t intel_event_sysfs_show(char *page, u64 config)
struct intel_shared_regs *allocate_shared_regs(int cpu)
static struct intel_excl_cntrs *allocate_excl_cntrs(int cpu)
static int intel_pmu_cpu_prepare(int cpu)
static void flip_smm_bit(void *data)
static void intel_pmu_cpu_starting(int cpu)
static void free_excl_cntrs(int cpu)
static void intel_pmu_cpu_dying(int cpu)
static void intel_pmu_sched_task(struct perf_event_context *ctx, bool sched_in)
static __init void intel_clovertown_quirk(void)
static int intel_snb_pebs_broken(int cpu)
static void intel_snb_check_microcode(void)
static bool is_lbr_from(unsigned long msr)
static bool check_msr(unsigned long msr, u64 mask)
static __init void intel_sandybridge_quirk(void)
static __init void intel_arch_events_quirk(void)
static __init void intel_nehalem_quirk(void)
static bool intel_glp_counter_freezing_broken(int cpu)
static __init void intel_glp_counter_freezing_quirk(void)
static __init void intel_ht_bug(void)
static ssize_t freeze_on_smi_show(struct device *cdev, struct device_attribute *attr, char *buf)
static ssize_t freeze_on_smi_store(struct device *cdev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t branches_show(struct device *cdev, struct device_attribute *attr, char *buf)
static ssize_t pmu_name_show(struct device *cdev, struct device_attribute *attr, char *buf)
static __init struct attribute ** get_events_attrs(struct attribute **base, struct attribute **mem, struct attribute **tsx)
__init int intel_pmu_init(void)
static __init int fixup_ht_bug(void)
  31 struct perf_event *event
  16 void
  15 struct cpu_hw_events *cpuc
   9 int idx
   8 int cpu
   4 struct device_attribute *attr
   4 struct device *cdev
   4 int added
   3 struct pt_regs *regs
   3 int *nr
   3 char *buf
   2 unsigned long msr
   2 u64 config
   2 struct hw_perf_event_extra *reg
   1 void *data
   1 u64 status
   1 u64 mask
   1 u64 left
   1 u64 ack
   1 struct perf_event_context *ctx
   1 struct hw_perf_event *hwc
   1 struct event_constraint *c
   1 struct attribute **tsx
   1 struct attribute **mem
   1 struct attribute **base
   1 size_t count
   1 perf_guest_get_msrs
   1 int hw_event
   1 int cntr
   1 const char *buf
   1 char *s
   1 char *page
   1 bool sched_in
   1 bool pmi
