
EXPORT_SYMBOL_GPL(reprogram_gp_counter);
EXPORT_SYMBOL_GPL(reprogram_fixed_counter);
EXPORT_SYMBOL_GPL(reprogram_counter);
static void kvm_pmi_trigger_fn(struct irq_work *irq_work)
static void kvm_perf_overflow(struct perf_event *perf_event, struct perf_sample_data *data, struct pt_regs *regs)
static void kvm_perf_overflow_intr(struct perf_event *perf_event, struct perf_sample_data *data, struct pt_regs *regs)
static void pmc_reprogram_counter(struct kvm_pmc *pmc, u32 type, unsigned config, bool exclude_user, bool exclude_kernel, bool intr, bool in_tx, bool in_tx_cp)
void reprogram_gp_counter(struct kvm_pmc *pmc, u64 eventsel)
void reprogram_fixed_counter(struct kvm_pmc *pmc, u8 ctrl, int idx)
void reprogram_counter(struct kvm_pmu *pmu, int pmc_idx)
void kvm_pmu_handle_event(struct kvm_vcpu *vcpu)
int kvm_pmu_is_valid_msr_idx(struct kvm_vcpu *vcpu, unsigned idx)
bool is_vmware_backdoor_pmc(u32 pmc_idx)
static int kvm_pmu_rdpmc_vmware(struct kvm_vcpu *vcpu, unsigned idx, u64 *data)
int kvm_pmu_rdpmc(struct kvm_vcpu *vcpu, unsigned idx, u64 *data)
void kvm_pmu_deliver_pmi(struct kvm_vcpu *vcpu)
bool kvm_pmu_is_valid_msr(struct kvm_vcpu *vcpu, u32 msr)
int kvm_pmu_get_msr(struct kvm_vcpu *vcpu, u32 msr, u64 *data)
int kvm_pmu_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
void kvm_pmu_refresh(struct kvm_vcpu *vcpu)
void kvm_pmu_reset(struct kvm_vcpu *vcpu)
void kvm_pmu_init(struct kvm_vcpu *vcpu)
void kvm_pmu_destroy(struct kvm_vcpu *vcpu)
  12 struct kvm_vcpu *vcpu
   3 unsigned idx
   3 u64 *data
   3 struct kvm_pmc *pmc
   2 u32 msr
   2 struct pt_regs *regs
   2 struct perf_sample_data *data
   2 struct perf_event *perf_event
   1 unsigned config
   1 u8 ctrl
   1 u64 eventsel
   1 u32 type
   1 u32 pmc_idx
   1 struct msr_data *msr_info
   1 struct kvm_pmu *pmu
   1 struct irq_work *irq_work
   1 reprogram_gp_counter
   1 reprogram_fixed_counter
   1 reprogram_counter
   1 int pmc_idx
   1 int idx
   1 bool intr
   1 bool in_tx_cp
   1 bool in_tx
   1 bool exclude_user
   1 bool exclude_kernel
