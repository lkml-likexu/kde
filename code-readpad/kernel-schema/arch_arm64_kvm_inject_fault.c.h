
\n
static u64 get_except_vector(struct kvm_vcpu *vcpu, enum exception_type type)
static void inject_abt64(struct kvm_vcpu *vcpu, bool is_iabt, unsigned long addr)
static void inject_undef64(struct kvm_vcpu *vcpu)
void kvm_inject_dabt(struct kvm_vcpu *vcpu, unsigned long addr)
void kvm_inject_pabt(struct kvm_vcpu *vcpu, unsigned long addr)
void kvm_inject_undefined(struct kvm_vcpu *vcpu)
void kvm_set_sei_esr(struct kvm_vcpu *vcpu, u64 esr)
void kvm_inject_vabt(struct kvm_vcpu *vcpu)
\n
      8 struct kvm_vcpu *vcpu
      3 unsigned long addr
      1 u64 esr
      1 enum exception_type type
      1 bool is_iabt
