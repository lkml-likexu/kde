
\n
extern struct perf_guest_switch_msr *perf_guest_get_msrs(int *nr)
; extern void perf_get_x86_pmu_capability(struct x86_pmu_capability *cap)
; extern void perf_check_microcode(void)
; extern int x86_perf_rdpmc_index(struct perf_event *event)
; static inline struct perf_guest_switch_msr *perf_guest_get_msrs(int *nr)
static inline void perf_get_x86_pmu_capability(struct x86_pmu_capability *cap)
\n
      2 struct x86_pmu_capability *cap
      2 int *nr
      1 void
      1 struct perf_event *event
