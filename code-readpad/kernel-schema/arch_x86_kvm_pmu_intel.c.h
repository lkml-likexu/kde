
static void reprogram_fixed_counters(struct kvm_pmu *pmu, u64 data)
static void global_ctrl_changed(struct kvm_pmu *pmu, u64 data)
static unsigned intel_find_arch_event(struct kvm_pmu *pmu, u8 event_select, u8 unit_mask)
static unsigned intel_find_fixed_event(int idx)
static bool intel_pmc_is_enabled(struct kvm_pmc *pmc)
static struct kvm_pmc *intel_pmc_idx_to_pmc(struct kvm_pmu *pmu, int pmc_idx)
static int intel_is_valid_msr_idx(struct kvm_vcpu *vcpu, unsigned idx)
static struct kvm_pmc *intel_msr_idx_to_pmc(struct kvm_vcpu *vcpu, unsigned idx)
static bool intel_is_valid_msr(struct kvm_vcpu *vcpu, u32 msr)
static int intel_pmu_get_msr(struct kvm_vcpu *vcpu, u32 msr, u64 *data)
static int intel_pmu_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
static void intel_pmu_refresh(struct kvm_vcpu *vcpu)
static void intel_pmu_init(struct kvm_vcpu *vcpu)
static void intel_pmu_reset(struct kvm_vcpu *vcpu)
   8 struct kvm_vcpu *vcpu
   4 struct kvm_pmu *pmu
   2 unsigned idx
   2 u64 data
   2 u32 msr
   1 u8 unit_mask
   1 u8 event_select
   1 u64 *data
   1 struct msr_data *msr_info
   1 struct kvm_pmc *pmc
   1 int pmc_idx
   1 int idx
