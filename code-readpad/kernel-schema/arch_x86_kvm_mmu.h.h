
\n
static inline u64 rsvd_bits(int s, int e)
static inline unsigned int kvm_mmu_available_pages(struct kvm *kvm)
static inline int kvm_mmu_reload(struct kvm_vcpu *vcpu)
static inline unsigned long kvm_get_pcid(struct kvm_vcpu *vcpu, gpa_t cr3)
static inline unsigned long kvm_get_active_pcid(struct kvm_vcpu *vcpu)
static inline void kvm_mmu_load_cr3(struct kvm_vcpu *vcpu)
static inline int is_writable_pte(unsigned long pte)
static inline bool is_write_protection(struct kvm_vcpu *vcpu)
static inline u8 permission_fault(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, unsigned pte_access, unsigned pte_pkey, unsigned pfec)
\n
      6 struct kvm_vcpu *vcpu
      1 unsigned pte_pkey
      1 unsigned pte_access
      1 unsigned pfec
      1 unsigned long pte
      1 struct kvm_mmu *mmu
      1 struct kvm *kvm
      1 int s
      1 int e
      1 gpa_t cr3
