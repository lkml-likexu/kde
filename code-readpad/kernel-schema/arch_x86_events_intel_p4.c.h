
static __initconst const u64 p4_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static u64 p4_get_alias_event(u64 config)
static struct p4_event_bind *p4_config_get_bind(u64 config)
static u64 p4_pmu_event_map(int hw_event)
static bool p4_event_match_cpu_model(unsigned int event_idx)
static int p4_validate_raw_event(struct perf_event *event)
static int p4_hw_config(struct perf_event *event)
static inline int p4_pmu_clear_cccr_ovf(struct hw_perf_event *hwc)
static void p4_pmu_disable_pebs(void)
static inline void p4_pmu_disable_event(struct perf_event *event)
static void p4_pmu_disable_all(void)
static void p4_pmu_enable_pebs(u64 config)
static void p4_pmu_enable_event(struct perf_event *event)
static void p4_pmu_enable_all(int added)
static int p4_pmu_handle_irq(struct pt_regs *regs)
static void p4_pmu_swap_config_ts(struct hw_perf_event *hwc, int cpu)
static int p4_get_escr_idx(unsigned int addr)
static int p4_next_cntr(int thread, unsigned long *used_mask, struct p4_event_bind *bind)
static int p4_pmu_schedule_events(struct cpu_hw_events *cpuc, int n, int *assign)
__init int p4_pmu_init(void)
   4 struct perf_event *event
   3 void
   3 u64 config
   2 struct hw_perf_event *hwc
   1 unsigned long *used_mask
   1 unsigned int event_idx
   1 unsigned int addr
   1 struct pt_regs *regs
   1 struct p4_event_bind *bind
   1 struct cpu_hw_events *cpuc
   1 int thread
   1 int n
   1 int hw_event
   1 int cpu
   1 int added
   1 int *assign
