
\n
static unsigned int get_msr_base(struct kvm_pmu *pmu, enum pmu_type type)
static enum index msr_to_index(u32 msr)
static inline struct kvm_pmc *get_gp_pmc_amd(struct kvm_pmu *pmu, u32 msr, enum pmu_type type)
static unsigned amd_find_arch_event(struct kvm_pmu *pmu, u8 event_select, u8 unit_mask)
static unsigned amd_find_fixed_event(int idx)
static bool amd_pmc_is_enabled(struct kvm_pmc *pmc)
static struct kvm_pmc *amd_pmc_idx_to_pmc(struct kvm_pmu *pmu, int pmc_idx)
static int amd_is_valid_msr_idx(struct kvm_vcpu *vcpu, unsigned idx)
static struct kvm_pmc *amd_msr_idx_to_pmc(struct kvm_vcpu *vcpu, unsigned idx)
static bool amd_is_valid_msr(struct kvm_vcpu *vcpu, u32 msr)
static int amd_pmu_get_msr(struct kvm_vcpu *vcpu, u32 msr, u64 *data)
static int amd_pmu_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
static void amd_pmu_refresh(struct kvm_vcpu *vcpu)
static void amd_pmu_init(struct kvm_vcpu *vcpu)
static void amd_pmu_reset(struct kvm_vcpu *vcpu)
\n
      8 struct kvm_vcpu *vcpu
      4 u32 msr
      4 struct kvm_pmu *pmu
      2 unsigned idx
      2 enum pmu_type type
      1 u8 unit_mask
      1 u8 event_select
      1 u64 *data
      1 struct msr_data *msr_info
      1 struct kvm_pmc *pmc
      1 int pmc_idx
      1 int idx
