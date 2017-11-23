
static bool test_aperfmperf(int idx)
static bool test_ptsc(int idx)
static bool test_irperf(int idx)
static bool test_therm_status(int idx)
static bool test_intel(int idx)
static int msr_event_init(struct perf_event *event)
static inline u64 msr_read_counter(struct perf_event *event)
static void msr_event_update(struct perf_event *event)
static void msr_event_start(struct perf_event *event, int flags)
static void msr_event_stop(struct perf_event *event, int flags)
static void msr_event_del(struct perf_event *event, int flags)
static int msr_event_add(struct perf_event *event, int flags)
static int __init msr_init(void)
   7 struct perf_event *event
   5 int idx
   4 int flags
   1 void
