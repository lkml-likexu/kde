
void __init intel_pmu_pebs_data_source_nhm(void)
void __init intel_pmu_pebs_data_source_skl(bool pmem)
static u64 precise_store_data(u64 status)
static u64 precise_datala_hsw(struct perf_event *event, u64 status)
static u64 load_latency_data(u64 status)
void init_debug_store_on_cpu(int cpu)
void fini_debug_store_on_cpu(int cpu)
static void ds_update_cea(void *cea, void *addr, size_t size, pgprot_t prot)
static void ds_clear_cea(void *cea, size_t size)
static void *dsalloc_pages(size_t size, gfp_t flags, int cpu)
static void dsfree_pages(const void *buffer, size_t size)
static int alloc_pebs_buffer(int cpu)
static void release_pebs_buffer(int cpu)
static int alloc_bts_buffer(int cpu)
static void release_bts_buffer(int cpu)
static int alloc_ds_buffer(int cpu)
static void release_ds_buffer(int cpu)
void release_ds_buffers(void)
void reserve_ds_buffers(void)
void intel_pmu_enable_bts(u64 config)
void intel_pmu_disable_bts(void)
int intel_pmu_drain_bts_buffer(void)
static inline void intel_pmu_drain_pebs_buffer(void)
struct event_constraint *intel_pebs_constraints(struct perf_event *event)
static inline bool pebs_needs_sched_cb(struct cpu_hw_events *cpuc)
void intel_pmu_pebs_sched_task(struct perf_event_context *ctx, bool sched_in)
static inline void pebs_update_threshold(struct cpu_hw_events *cpuc)
static void pebs_update_state(bool needed_cb, struct cpu_hw_events *cpuc, struct pmu *pmu)
void intel_pmu_pebs_add(struct perf_event *event)
void intel_pmu_pebs_enable(struct perf_event *event)
void intel_pmu_pebs_del(struct perf_event *event)
void intel_pmu_pebs_disable(struct perf_event *event)
void intel_pmu_pebs_enable_all(void)
void intel_pmu_pebs_disable_all(void)
static int intel_pmu_pebs_fixup_ip(struct pt_regs *regs)
static inline u64 intel_hsw_weight(struct pebs_record_skl *pebs)
static inline u64 intel_hsw_transaction(struct pebs_record_skl *pebs)
static void setup_pebs_sample_data(struct perf_event *event, struct pt_regs *iregs, void *__pebs, struct perf_sample_data *data, struct pt_regs *regs)
static inline void * get_next_pebs_record_by_bit(void *base, void *top, int bit)
void intel_pmu_auto_reload_read(struct perf_event *event)
static int intel_pmu_save_and_restart_reload(struct perf_event *event, int count)
static void __intel_pmu_pebs_event(struct perf_event *event, struct pt_regs *iregs, void *base, void *top, int bit, int count)
static void intel_pmu_drain_pebs_core(struct pt_regs *iregs)
static void intel_pmu_drain_pebs_nhm(struct pt_regs *iregs)
void __init intel_ds_init(void)
void perf_restore_debug_store(void)
  10 void
  10 struct perf_event *event
   9 int cpu
   4 struct pt_regs *iregs
   4 size_t size
   3 u64 status
   3 struct cpu_hw_events *cpuc
   2 void *top
   2 void *cea
   2 void *base
   2 struct pt_regs *regs
   2 struct pebs_record_skl *pebs
   2 int count
   2 int bit
   1 void *addr
   1 void *__pebs
   1 u64 config
   1 struct pmu *pmu
   1 struct perf_sample_data *data
   1 struct perf_event_context *ctx
   1 pgprot_t prot
   1 gfp_t flags
   1 const void *buffer
   1 bool sched_in
   1 bool pmem
   1 bool needed_cb
