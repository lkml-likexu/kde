
EXPORT_SYMBOL_GPL(kvmppc_emulate_instruction);
\n
void kvmppc_emulate_dec(struct kvm_vcpu *vcpu)
u32 kvmppc_get_dec(struct kvm_vcpu *vcpu, u64 tb)
static int kvmppc_emulate_mtspr(struct kvm_vcpu *vcpu, int sprn, int rs)
static int kvmppc_emulate_mfspr(struct kvm_vcpu *vcpu, int sprn, int rt)
int kvmppc_emulate_instruction(struct kvm_run *run, struct kvm_vcpu *vcpu)
\n
      5 struct kvm_vcpu *vcpu
      2 int sprn
      1 u64 tb
      1 struct kvm_run *run
      1 kvmppc_emulate_instruction
      1 int rt
      1 int rs
