
\n
static bool spr_allowed(struct kvm_vcpu *vcpu, enum priv_level level)
static inline void kvmppc_copyto_vcpu_tm(struct kvm_vcpu *vcpu)
static inline void kvmppc_copyfrom_vcpu_tm(struct kvm_vcpu *vcpu)
static void kvmppc_emulate_treclaim(struct kvm_vcpu *vcpu, int ra_val)
static void kvmppc_emulate_trchkpt(struct kvm_vcpu *vcpu)
void kvmppc_emulate_tabort(struct kvm_vcpu *vcpu, int ra_val)
int kvmppc_core_emulate_op_pr(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int inst, int *advance)
void kvmppc_set_bat(struct kvm_vcpu *vcpu, struct kvmppc_bat *bat, bool upper, u32 val)
static struct kvmppc_bat *kvmppc_find_bat(struct kvm_vcpu *vcpu, int sprn)
int kvmppc_core_emulate_mtspr_pr(struct kvm_vcpu *vcpu, int sprn, ulong spr_val)
int kvmppc_core_emulate_mfspr_pr(struct kvm_vcpu *vcpu, int sprn, ulong *spr_val)
u32 kvmppc_alignment_dsisr(struct kvm_vcpu *vcpu, unsigned int inst)
ulong kvmppc_alignment_dar(struct kvm_vcpu *vcpu, unsigned int inst)
\n
     13 struct kvm_vcpu *vcpu
      3 unsigned int inst
      3 int sprn
      2 int ra_val
      1 ulong spr_val
      1 ulong *spr_val
      1 u32 val
      1 struct kvm_run *run
      1 struct kvmppc_bat *bat
      1 int *advance
      1 enum priv_level level
      1 bool upper
