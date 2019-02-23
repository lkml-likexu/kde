
\n
static inline unsigned int __grow_ple_window(unsigned int val, unsigned int base, unsigned int modifier, unsigned int max)
static inline unsigned int __shrink_ple_window(unsigned int val, unsigned int base, unsigned int modifier, unsigned int min)
static inline void kvm_clear_exception_queue(struct kvm_vcpu *vcpu)
static inline void kvm_queue_interrupt(struct kvm_vcpu *vcpu, u8 vector, bool soft)
static inline void kvm_clear_interrupt_queue(struct kvm_vcpu *vcpu)
static inline bool kvm_event_needs_reinjection(struct kvm_vcpu *vcpu)
static inline bool kvm_exception_is_soft(unsigned int nr)
static inline bool is_protmode(struct kvm_vcpu *vcpu)
static inline int is_long_mode(struct kvm_vcpu *vcpu)
static inline bool is_64_bit_mode(struct kvm_vcpu *vcpu)
static inline bool is_la57_mode(struct kvm_vcpu *vcpu)
static inline bool x86_exception_has_error_code(unsigned int vector)
static inline bool mmu_is_nested(struct kvm_vcpu *vcpu)
static inline int is_pae(struct kvm_vcpu *vcpu)
static inline int is_pse(struct kvm_vcpu *vcpu)
static inline int is_paging(struct kvm_vcpu *vcpu)
static inline u32 bit(int bitno)
static inline u8 vcpu_virt_addr_bits(struct kvm_vcpu *vcpu)
static inline u8 ctxt_virt_addr_bits(struct x86_emulate_ctxt *ctxt)
static inline u64 get_canonical(u64 la, u8 vaddr_bits)
static inline bool is_noncanonical_address(u64 la, struct kvm_vcpu *vcpu)
static inline bool emul_is_noncanonical_address(u64 la, struct x86_emulate_ctxt *ctxt)
static inline void vcpu_cache_mmio_info(struct kvm_vcpu *vcpu, gva_t gva, gfn_t gfn, unsigned access)
static inline bool vcpu_match_mmio_gen(struct kvm_vcpu *vcpu)
static inline void vcpu_clear_mmio_info(struct kvm_vcpu *vcpu, gva_t gva)
static inline bool vcpu_match_mmio_gva(struct kvm_vcpu *vcpu, unsigned long gva)
static inline bool vcpu_match_mmio_gpa(struct kvm_vcpu *vcpu, gpa_t gpa)
static inline unsigned long kvm_register_readl(struct kvm_vcpu *vcpu, enum kvm_reg reg)
static inline void kvm_register_writel(struct kvm_vcpu *vcpu, enum kvm_reg reg, unsigned long val)
static inline bool kvm_check_has_quirk(struct kvm *kvm, u64 quirk)
static inline u64 nsec_to_cycles(struct kvm_vcpu *vcpu, u64 nsec)
static inline bool kvm_mwait_in_guest(struct kvm *kvm)
static inline bool kvm_hlt_in_guest(struct kvm *kvm)
static inline bool kvm_pause_in_guest(struct kvm *kvm)
static inline void kvm_before_interrupt(struct kvm_vcpu *vcpu)
static inline void kvm_after_interrupt(struct kvm_vcpu *vcpu)
\n
     24 struct kvm_vcpu *vcpu
      4 struct kvm *kvm
      3 u64 la
      2 unsigned int val
      2 unsigned int modifier
      2 unsigned int base
      2 struct x86_emulate_ctxt *ctxt
      2 gva_t gva
      2 enum kvm_reg reg
      1 unsigned long val
      1 unsigned long gva
      1 unsigned int vector
      1 unsigned int nr
      1 unsigned int min
      1 unsigned int max
      1 unsigned access
      1 u8 vector
      1 u8 vaddr_bits
      1 u64 quirk
      1 u64 nsec
      1 int bitno
      1 gpa_t gpa
      1 gfn_t gfn
      1 bool soft
