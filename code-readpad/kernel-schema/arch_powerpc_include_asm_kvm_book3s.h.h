
\n
static inline struct kvmppc_vcpu_book3s *to_book3s(struct kvm_vcpu *vcpu)
static inline void kvmppc_set_gpr(struct kvm_vcpu *vcpu, int num, ulong val)
static inline ulong kvmppc_get_gpr(struct kvm_vcpu *vcpu, int num)
static inline void kvmppc_set_cr(struct kvm_vcpu *vcpu, u32 val)
static inline u32 kvmppc_get_cr(struct kvm_vcpu *vcpu)
static inline void kvmppc_set_xer(struct kvm_vcpu *vcpu, ulong val)
static inline ulong kvmppc_get_xer(struct kvm_vcpu *vcpu)
static inline void kvmppc_set_ctr(struct kvm_vcpu *vcpu, ulong val)
static inline ulong kvmppc_get_ctr(struct kvm_vcpu *vcpu)
static inline void kvmppc_set_lr(struct kvm_vcpu *vcpu, ulong val)
static inline ulong kvmppc_get_lr(struct kvm_vcpu *vcpu)
static inline void kvmppc_set_pc(struct kvm_vcpu *vcpu, ulong val)
static inline ulong kvmppc_get_pc(struct kvm_vcpu *vcpu)
static inline u64 kvmppc_get_msr(struct kvm_vcpu *vcpu)
; static inline bool kvmppc_need_byteswap(struct kvm_vcpu *vcpu)
static inline ulong kvmppc_get_fault_dar(struct kvm_vcpu *vcpu)
static inline bool is_kvmppc_resume_guest(int r)
static inline bool is_kvmppc_hv_enabled(struct kvm *kvm)
; static inline bool kvmppc_supports_magic_page(struct kvm_vcpu *vcpu)
static inline u32 kvmppc_pack_vcpu_id(struct kvm *kvm, u32 id)
\n
     17 struct kvm_vcpu *vcpu
      5 ulong val
      2 struct kvm *kvm
      2 int num
      1 u32 val
      1 u32 id
      1 int r
