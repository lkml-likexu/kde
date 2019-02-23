
\n
static inline phys_addr_t stage2_pgd_addr_end(struct kvm *kvm, phys_addr_t addr, phys_addr_t end)
static inline phys_addr_t stage2_pmd_addr_end(struct kvm *kvm, phys_addr_t addr, phys_addr_t end)
static inline bool kvm_stage2_has_pud(struct kvm *kvm)
static inline bool kvm_stage2_has_pmd(struct kvm *kvm)
\n
      4 struct kvm *kvm
      2 phys_addr_t end
      2 phys_addr_t addr
