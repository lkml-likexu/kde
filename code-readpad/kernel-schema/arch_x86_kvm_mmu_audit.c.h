
static void __mmu_spte_walk(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, inspect_spte_fn fn, int level)
static void mmu_spte_walk(struct kvm_vcpu *vcpu, inspect_spte_fn fn)
static void walk_all_active_sps(struct kvm *kvm, sp_handler fn)
static void audit_mappings(struct kvm_vcpu *vcpu, u64 *sptep, int level)
static void inspect_spte_has_rmap(struct kvm *kvm, u64 *sptep)
static void audit_sptes_have_rmaps(struct kvm_vcpu *vcpu, u64 *sptep, int level)
static void audit_spte_after_sync(struct kvm_vcpu *vcpu, u64 *sptep, int level)
static void check_mappings_rmap(struct kvm *kvm, struct kvm_mmu_page *sp)
static void audit_write_protection(struct kvm *kvm, struct kvm_mmu_page *sp)
static void audit_sp(struct kvm *kvm, struct kvm_mmu_page *sp)
static void audit_all_active_sps(struct kvm *kvm)
static void audit_spte(struct kvm_vcpu *vcpu, u64 *sptep, int level)
static void audit_vcpu_spte(struct kvm_vcpu *vcpu)
static void __kvm_mmu_audit(struct kvm_vcpu *vcpu, int point)
static inline void kvm_mmu_audit(struct kvm_vcpu *vcpu, int point)
static void mmu_audit_enable(void)
static void mmu_audit_disable(void)
static int mmu_audit_set(const char *val, const struct kernel_param *kp)
   9 struct kvm_vcpu *vcpu
   6 struct kvm *kvm
   5 u64 *sptep
   5 int level
   4 struct kvm_mmu_page *sp
   2 void
   2 int point
   2 inspect_spte_fn fn
   1 sp_handler fn
   1 const struct kernel_param *kp
   1 const char *val
