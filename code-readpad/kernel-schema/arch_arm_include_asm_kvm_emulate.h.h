
\n
static inline unsigned long *vcpu_reg32(struct kvm_vcpu *vcpu, u8 reg_num)
static inline unsigned long vpcu_read_spsr(struct kvm_vcpu *vcpu)
static inline void vcpu_write_spsr(struct kvm_vcpu *vcpu, unsigned long v)
static inline unsigned long vcpu_get_reg(struct kvm_vcpu *vcpu, u8 reg_num)
static inline void vcpu_set_reg(struct kvm_vcpu *vcpu, u8 reg_num, unsigned long val)
static inline void kvm_inject_undefined(struct kvm_vcpu *vcpu)
static inline void kvm_inject_dabt(struct kvm_vcpu *vcpu, unsigned long addr)
static inline void kvm_inject_pabt(struct kvm_vcpu *vcpu, unsigned long addr)
static inline bool kvm_condition_valid(const struct kvm_vcpu *vcpu)
static inline void kvm_skip_instr(struct kvm_vcpu *vcpu, bool is_wide_instr)
static inline void vcpu_reset_hcr(struct kvm_vcpu *vcpu)
static inline unsigned long *vcpu_hcr(const struct kvm_vcpu *vcpu)
static inline void vcpu_clear_wfe_traps(struct kvm_vcpu *vcpu)
static inline void vcpu_set_wfe_traps(struct kvm_vcpu *vcpu)
static inline bool vcpu_mode_is_32bit(const struct kvm_vcpu *vcpu)
static inline unsigned long *vcpu_pc(struct kvm_vcpu *vcpu)
static inline unsigned long *vcpu_cpsr(const struct kvm_vcpu *vcpu)
static inline void vcpu_set_thumb(struct kvm_vcpu *vcpu)
static inline bool mode_has_spsr(struct kvm_vcpu *vcpu)
static inline bool vcpu_mode_priv(struct kvm_vcpu *vcpu)
static inline u32 kvm_vcpu_get_hsr(const struct kvm_vcpu *vcpu)
static inline int kvm_vcpu_get_condition(const struct kvm_vcpu *vcpu)
static inline unsigned long kvm_vcpu_get_hfar(struct kvm_vcpu *vcpu)
static inline phys_addr_t kvm_vcpu_get_fault_ipa(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_isvalid(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_iswrite(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_issext(struct kvm_vcpu *vcpu)
static inline int kvm_vcpu_dabt_get_rd(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_iss1tw(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_is_cm(struct kvm_vcpu *vcpu)
static inline int kvm_vcpu_dabt_get_as(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_trap_il_is32bit(struct kvm_vcpu *vcpu)
static inline u8 kvm_vcpu_trap_get_class(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_trap_is_iabt(struct kvm_vcpu *vcpu)
static inline u8 kvm_vcpu_trap_get_fault(struct kvm_vcpu *vcpu)
static inline u8 kvm_vcpu_trap_get_fault_type(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_isextabt(struct kvm_vcpu *vcpu)
static inline u32 kvm_vcpu_hvc_get_imm(struct kvm_vcpu *vcpu)
static inline unsigned long kvm_vcpu_get_mpidr_aff(struct kvm_vcpu *vcpu)
static inline void kvm_vcpu_set_be(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_is_be(struct kvm_vcpu *vcpu)
static inline unsigned long vcpu_data_guest_to_host(struct kvm_vcpu *vcpu, unsigned long data, unsigned int len)
static inline unsigned long vcpu_data_host_to_guest(struct kvm_vcpu *vcpu, unsigned long data, unsigned int len)
\n
     37 struct kvm_vcpu *vcpu
      6 const struct kvm_vcpu *vcpu
      3 u8 reg_num
      2 unsigned long data
      2 unsigned long addr
      2 unsigned int len
      1 unsigned long val
      1 unsigned long v
      1 bool is_wide_instr
