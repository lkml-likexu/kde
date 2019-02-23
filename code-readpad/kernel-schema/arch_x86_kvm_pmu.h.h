
\n
static inline u64 pmc_bitmask(struct kvm_pmc *pmc)
static inline u64 pmc_read_counter(struct kvm_pmc *pmc)
static inline void pmc_stop_counter(struct kvm_pmc *pmc)
static inline bool pmc_is_gp(struct kvm_pmc *pmc)
static inline bool pmc_is_fixed(struct kvm_pmc *pmc)
static inline bool pmc_is_enabled(struct kvm_pmc *pmc)
static inline struct kvm_pmc *get_gp_pmc(struct kvm_pmu *pmu, u32 msr, u32 base)
static inline struct kvm_pmc *get_fixed_pmc(struct kvm_pmu *pmu, u32 msr)
\n
      6 struct kvm_pmc *pmc
      2 u32 msr
      2 struct kvm_pmu *pmu
      1 u32 base
