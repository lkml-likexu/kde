
\n
static void save_guest_debug_regs(struct kvm_vcpu *vcpu)
static void restore_guest_debug_regs(struct kvm_vcpu *vcpu)
void kvm_arm_init_debug(void)
void kvm_arm_reset_debug_ptr(struct kvm_vcpu *vcpu)
void kvm_arm_setup_debug(struct kvm_vcpu *vcpu)
void kvm_arm_clear_debug(struct kvm_vcpu *vcpu)
\n
      5 struct kvm_vcpu *vcpu
      1 void
