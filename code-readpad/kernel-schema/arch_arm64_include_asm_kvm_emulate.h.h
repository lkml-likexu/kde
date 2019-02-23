
\n
static inline bool vcpu_el1_is_32bit(struct kvm_vcpu *vcpu)
static inline void vcpu_reset_hcr(struct kvm_vcpu *vcpu)
static inline unsigned long *vcpu_hcr(struct kvm_vcpu *vcpu)
static inline void vcpu_clear_wfe_traps(struct kvm_vcpu *vcpu)
static inline void vcpu_set_wfe_traps(struct kvm_vcpu *vcpu)
static inline unsigned long vcpu_get_vsesr(struct kvm_vcpu *vcpu)
static inline void vcpu_set_vsesr(struct kvm_vcpu *vcpu, u64 vsesr)
static inline unsigned long *vcpu_pc(const struct kvm_vcpu *vcpu)
static inline unsigned long *__vcpu_elr_el1(const struct kvm_vcpu *vcpu)
static inline unsigned long vcpu_read_elr_el1(const struct kvm_vcpu *vcpu)
static inline void vcpu_write_elr_el1(const struct kvm_vcpu *vcpu, unsigned long v)
static inline unsigned long *vcpu_cpsr(const struct kvm_vcpu *vcpu)
static inline bool vcpu_mode_is_32bit(const struct kvm_vcpu *vcpu)
static inline bool kvm_condition_valid(const struct kvm_vcpu *vcpu)
static inline void vcpu_set_thumb(struct kvm_vcpu *vcpu)
static inline unsigned long vcpu_get_reg(const struct kvm_vcpu *vcpu, u8 reg_num)
static inline void vcpu_set_reg(struct kvm_vcpu *vcpu, u8 reg_num, unsigned long val)
static inline unsigned long vcpu_read_spsr(const struct kvm_vcpu *vcpu)
static inline void vcpu_write_spsr(struct kvm_vcpu *vcpu, unsigned long v)
static inline bool vcpu_mode_priv(const struct kvm_vcpu *vcpu)
static inline u32 kvm_vcpu_get_hsr(const struct kvm_vcpu *vcpu)
static inline int kvm_vcpu_get_condition(const struct kvm_vcpu *vcpu)
static inline unsigned long kvm_vcpu_get_hfar(const struct kvm_vcpu *vcpu)
static inline phys_addr_t kvm_vcpu_get_fault_ipa(const struct kvm_vcpu *vcpu)
static inline u64 kvm_vcpu_get_disr(const struct kvm_vcpu *vcpu)
static inline u32 kvm_vcpu_hvc_get_imm(const struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_isvalid(const struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_issext(const struct kvm_vcpu *vcpu)
static inline int kvm_vcpu_dabt_get_rd(const struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_iss1tw(const struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_iswrite(const struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_is_cm(const struct kvm_vcpu *vcpu)
static inline int kvm_vcpu_dabt_get_as(const struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_trap_il_is32bit(const struct kvm_vcpu *vcpu)
static inline u8 kvm_vcpu_trap_get_class(const struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_trap_is_iabt(const struct kvm_vcpu *vcpu)
static inline u8 kvm_vcpu_trap_get_fault(const struct kvm_vcpu *vcpu)
static inline u8 kvm_vcpu_trap_get_fault_type(const struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_dabt_isextabt(const struct kvm_vcpu *vcpu)
static inline int kvm_vcpu_sys_get_rt(struct kvm_vcpu *vcpu)
static inline unsigned long kvm_vcpu_get_mpidr_aff(struct kvm_vcpu *vcpu)
static inline void kvm_vcpu_set_be(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_is_be(struct kvm_vcpu *vcpu)
static inline unsigned long vcpu_data_guest_to_host(struct kvm_vcpu *vcpu, unsigned long data, unsigned int len)
static inline unsigned long vcpu_data_host_to_guest(struct kvm_vcpu *vcpu, unsigned long data, unsigned int len)
static inline void kvm_skip_instr(struct kvm_vcpu *vcpu, bool is_wide_instr)
static inline void __hyp_text __kvm_skip_instr(struct kvm_vcpu *vcpu)
\n
     29 const struct kvm_vcpu *vcpu
     18 struct kvm_vcpu *vcpu
      2 unsigned long v
      2 unsigned long data
      2 unsigned int len
      2 u8 reg_num
      1 unsigned long val
      1 u64 vsesr
      1 bool is_wide_instr
