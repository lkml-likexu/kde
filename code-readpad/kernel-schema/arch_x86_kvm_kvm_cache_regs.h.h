
\n
static inline unsigned long kvm_register_read(struct kvm_vcpu *vcpu, enum kvm_reg reg)
static inline void kvm_register_write(struct kvm_vcpu *vcpu, enum kvm_reg reg, unsigned long val)
static inline unsigned long kvm_rip_read(struct kvm_vcpu *vcpu)
static inline void kvm_rip_write(struct kvm_vcpu *vcpu, unsigned long val)
static inline u64 kvm_pdptr_read(struct kvm_vcpu *vcpu, int index)
static inline ulong kvm_read_cr0_bits(struct kvm_vcpu *vcpu, ulong mask)
static inline ulong kvm_read_cr0(struct kvm_vcpu *vcpu)
static inline ulong kvm_read_cr4_bits(struct kvm_vcpu *vcpu, ulong mask)
static inline ulong kvm_read_cr3(struct kvm_vcpu *vcpu)
static inline ulong kvm_read_cr4(struct kvm_vcpu *vcpu)
static inline u64 kvm_read_edx_eax(struct kvm_vcpu *vcpu)
static inline void enter_guest_mode(struct kvm_vcpu *vcpu)
static inline void leave_guest_mode(struct kvm_vcpu *vcpu)
static inline bool is_guest_mode(struct kvm_vcpu *vcpu)
static inline bool is_smm(struct kvm_vcpu *vcpu)
\n
     15 struct kvm_vcpu *vcpu
      2 unsigned long val
      2 ulong mask
      2 enum kvm_reg reg
      1 int index
