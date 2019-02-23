
\n
static void __intel_pmu_lbr_enable(bool pmi)
static void __intel_pmu_lbr_disable(void)
static void intel_pmu_lbr_reset_32(void)
static void intel_pmu_lbr_reset_64(void)
void intel_pmu_lbr_reset(void)
static inline u64 intel_pmu_lbr_tos(void)
static inline bool lbr_from_signext_quirk_needed(void)
inline u64 lbr_from_signext_quirk_wr(u64 val)
static u64 lbr_from_signext_quirk_rd(u64 val)
static inline void wrlbr_from(unsigned int idx, u64 val)
static inline void wrlbr_to(unsigned int idx, u64 val)
static inline u64 rdlbr_from(unsigned int idx)
static inline u64 rdlbr_to(unsigned int idx)
static void __intel_pmu_lbr_restore(struct x86_perf_task_context *task_ctx)
static void __intel_pmu_lbr_save(struct x86_perf_task_context *task_ctx)
void intel_pmu_lbr_sched_task(struct perf_event_context *ctx, bool sched_in)
static inline bool branch_user_callstack(unsigned br_sel)
void intel_pmu_lbr_add(struct perf_event *event)
void intel_pmu_lbr_del(struct perf_event *event)
void intel_pmu_lbr_enable_all(bool pmi)
void intel_pmu_lbr_disable_all(void)
static void intel_pmu_lbr_read_32(struct cpu_hw_events *cpuc)
static void intel_pmu_lbr_read_64(struct cpu_hw_events *cpuc)
void intel_pmu_lbr_read(void)
static int intel_pmu_setup_sw_lbr_filter(struct perf_event *event)
static int intel_pmu_setup_hw_lbr_filter(struct perf_event *event)
int intel_pmu_setup_lbr_filter(struct perf_event *event)
static int branch_type(unsigned long from, unsigned long to, int abort)
static int common_branch_type(int type)
static void intel_pmu_lbr_filter(struct cpu_hw_events *cpuc)
void __init intel_pmu_lbr_init_core(void)
void __init intel_pmu_lbr_init_nhm(void)
void __init intel_pmu_lbr_init_snb(void)
void intel_pmu_lbr_init_hsw(void)
__init void intel_pmu_lbr_init_skl(void)
void __init intel_pmu_lbr_init_atom(void)
void __init intel_pmu_lbr_init_slm(void)
void intel_pmu_lbr_init_knl(void)
\n
     16 void
      5 struct perf_event *event
      4 unsigned int idx
      4 u64 val
      3 struct cpu_hw_events *cpuc
      2 struct x86_perf_task_context *task_ctx
      2 bool pmi
      1 unsigned long to
      1 unsigned long from
      1 unsigned br_sel
      1 struct perf_event_context *ctx
      1 int type
      1 int abort
      1 bool sched_in
