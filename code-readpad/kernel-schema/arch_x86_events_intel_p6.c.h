
static const u64 p6_perfmon_event_map[] = static const u64 __initconst p6_hw_cache_event_ids [PERF_COUNT_HW_CACHE_MAX] [PERF_COUNT_HW_CACHE_OP_MAX] [PERF_COUNT_HW_CACHE_RESULT_MAX] = static u64 p6_pmu_event_map(int hw_event)
static struct event_constraint p6_event_constraints[] = static void p6_pmu_disable_all(void)
static void p6_pmu_enable_all(int added)
static inline void p6_pmu_disable_event(struct perf_event *event)
static void p6_pmu_enable_event(struct perf_event *event)
static __init void p6_pmu_rdpmc_quirk(void)
__init int p6_pmu_init(void)
   3 void
   2 struct perf_event *event
   1 int hw_event
   1 int added
