
\n
static inline void print_sys_reg_instr(const struct sys_reg_params *p)
static inline bool ignore_write(struct kvm_vcpu *vcpu, const struct sys_reg_params *p)
static inline bool read_zero(struct kvm_vcpu *vcpu, struct sys_reg_params *p)
static inline void reset_unknown(struct kvm_vcpu *vcpu, const struct sys_reg_desc *r)
static inline void reset_val(struct kvm_vcpu *vcpu, const struct sys_reg_desc *r)
static inline int cmp_sys_reg(const struct sys_reg_desc *i1, const struct sys_reg_desc *i2)
\n
      4 struct kvm_vcpu *vcpu
      2 const struct sys_reg_params *p
      2 const struct sys_reg_desc *r
      1 struct sys_reg_params *p
      1 const struct sys_reg_desc *i2
      1 const struct sys_reg_desc *i1
