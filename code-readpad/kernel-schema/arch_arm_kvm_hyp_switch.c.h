
\n
static void __hyp_text __activate_traps(struct kvm_vcpu *vcpu, u32 *fpexc_host)
static void __hyp_text __deactivate_traps(struct kvm_vcpu *vcpu)
static void __hyp_text __activate_vm(struct kvm_vcpu *vcpu)
static void __hyp_text __deactivate_vm(struct kvm_vcpu *vcpu)
static void __hyp_text __vgic_save_state(struct kvm_vcpu *vcpu)
static void __hyp_text __vgic_restore_state(struct kvm_vcpu *vcpu)
static bool __hyp_text __populate_fault_info(struct kvm_vcpu *vcpu)
int __hyp_text __kvm_vcpu_run_nvhe(struct kvm_vcpu *vcpu)
void __hyp_text __noreturn __hyp_panic(int cause)
\n
      8 struct kvm_vcpu *vcpu
      1 u32 *fpexc_host
      1 int cause
