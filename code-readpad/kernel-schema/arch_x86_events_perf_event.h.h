
\n
static inline bool x86_pmu_has_lbr_callstack(void)
static inline unsigned int x86_pmu_config_addr(int index)
static inline unsigned int x86_pmu_event_addr(int index)
static inline int x86_pmu_rdpmc_index(int index)
static inline void __x86_pmu_enable_event(struct hw_perf_event *hwc, u64 enable_mask)
static inline void x86_pmu_disable_event(struct perf_event *event)
static inline bool kernel_ip(unsigned long ip)
static inline void set_linear_ip(struct pt_regs *regs, unsigned long ip)
static inline int amd_pmu_init(void)
static inline bool intel_pmu_has_bts_period(struct perf_event *event, u64 period)
static inline bool intel_pmu_has_bts(struct perf_event *event)
static inline int is_ht_workaround_enabled(void)
static inline void reserve_ds_buffers(void)
static inline void release_ds_buffers(void)
static inline int intel_pmu_init(void)
static inline struct intel_shared_regs *allocate_shared_regs(int cpu)
static inline int is_ht_workaround_enabled(void)
\n
      7 void
      3 struct perf_event *event
      3 int index
      2 unsigned long ip
      1 u64 period
      1 u64 enable_mask
      1 struct pt_regs *regs
      1 struct hw_perf_event *hwc
      1 int cpu
