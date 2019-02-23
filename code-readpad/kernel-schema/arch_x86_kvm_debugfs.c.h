
\n
bool kvm_arch_has_vcpu_debugfs(void)
static int vcpu_get_tsc_offset(void *data, u64 *val)
static int vcpu_get_tsc_scaling_ratio(void *data, u64 *val)
static int vcpu_get_tsc_scaling_frac_bits(void *data, u64 *val)
int kvm_arch_create_vcpu_debugfs(struct kvm_vcpu *vcpu)
\n
      3 void *data
      3 u64 *val
      1 void
      1 struct kvm_vcpu *vcpu
