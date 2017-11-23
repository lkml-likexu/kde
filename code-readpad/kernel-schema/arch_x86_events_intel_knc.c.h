
static const u64 knc_perfmon_event_map[] = static const u64 __initconst knc_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static u64 knc_pmu_event_map(int hw_event)
static struct event_constraint knc_event_constraints[] = static void knc_pmu_disable_all(void)
static void knc_pmu_enable_all(int added)
static inline void knc_pmu_disable_event(struct perf_event *event)
static void knc_pmu_enable_event(struct perf_event *event)
static inline u64 knc_pmu_get_status(void)
static inline void knc_pmu_ack_status(u64 ack)
static int knc_pmu_handle_irq(struct pt_regs *regs)
__init int knc_pmu_init(void)
   3 void
   2 struct perf_event *event
   1 u64 ack
   1 struct pt_regs *regs
   1 int hw_event
   1 int added
