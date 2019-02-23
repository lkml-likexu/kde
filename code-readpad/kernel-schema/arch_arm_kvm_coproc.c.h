
\n
static bool write_to_read_only(struct kvm_vcpu *vcpu, const struct coproc_params *params)
static bool read_from_write_only(struct kvm_vcpu *vcpu, const struct coproc_params *params)
static inline void vcpu_cp15_reg64_set(struct kvm_vcpu *vcpu, const struct coproc_reg *r, u64 val)
static inline u64 vcpu_cp15_reg64_get(struct kvm_vcpu *vcpu, const struct coproc_reg *r)
int kvm_handle_cp10_id(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_handle_cp_0_13_access(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_handle_cp14_load_store(struct kvm_vcpu *vcpu, struct kvm_run *run)
static void reset_mpidr(struct kvm_vcpu *vcpu, const struct coproc_reg *r)
static bool access_actlr(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static bool access_cbar(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static bool access_l2ctlr(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static void reset_l2ctlr(struct kvm_vcpu *vcpu, const struct coproc_reg *r)
static void reset_actlr(struct kvm_vcpu *vcpu, const struct coproc_reg *r)
static bool access_l2ectlr(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static bool access_dcsw(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
bool access_vm_reg(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static bool access_gic_sgi(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static bool access_gic_sre(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static bool access_cntp_tval(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static bool access_cntp_ctl(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static bool access_cntp_cval(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static bool trap_raz_wi(struct kvm_vcpu *vcpu, const struct coproc_params *p, const struct coproc_reg *r)
static int check_reg_table(const struct coproc_reg *table, unsigned int n)
void kvm_register_target_coproc_table(struct kvm_coproc_target_table *table)
static const struct coproc_reg *get_target_table(unsigned target, size_t *num)
static int match_reg(const void *key, const void *elt)
static const struct coproc_reg *find_reg(const struct coproc_params *params, const struct coproc_reg table[], unsigned int num)
static int emulate_cp15(struct kvm_vcpu *vcpu, const struct coproc_params *params)
static struct coproc_params decode_64bit_hsr(struct kvm_vcpu *vcpu)
int kvm_handle_cp15_64(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_handle_cp14_64(struct kvm_vcpu *vcpu, struct kvm_run *run)
static void reset_coproc_regs(struct kvm_vcpu *vcpu, const struct coproc_reg *table, size_t num)
static struct coproc_params decode_32bit_hsr(struct kvm_vcpu *vcpu)
int kvm_handle_cp15_32(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_handle_cp14_32(struct kvm_vcpu *vcpu, struct kvm_run *run)
static bool index_to_params(u64 id, struct coproc_params *params)
static const struct coproc_reg *index_to_coproc_reg(struct kvm_vcpu *vcpu, u64 id)
static int reg_from_user(void *val, const void __user *uaddr, u64 id)
static int reg_to_user(void __user *uaddr, const void *val, u64 id)
static int get_invariant_cp15(u64 id, void __user *uaddr)
static int set_invariant_cp15(u64 id, void __user *uaddr)
static bool is_valid_cache(u32 val)
static u32 get_ccsidr(u32 csselr)
static int demux_c15_get(u64 id, void __user *uaddr)
static int demux_c15_set(u64 id, void __user *uaddr)
static unsigned int num_fp_regs(void)
static unsigned int num_vfp_regs(void)
static int copy_vfp_regids(u64 __user *uindices)
static int vfp_get_reg(const struct kvm_vcpu *vcpu, u64 id, void __user *uaddr)
static int vfp_set_reg(struct kvm_vcpu *vcpu, u64 id, const void __user *uaddr)
case KVM_REG_ARM_VFP_FPEXC: return reg_from_user(&vcpu->arch.ctxt.vfp.fpexc, uaddr, id)
;case KVM_REG_ARM_VFP_FPSCR: return reg_from_user(&vcpu->arch.ctxt.vfp.fpscr, uaddr, id)
;case KVM_REG_ARM_VFP_FPINST: return reg_from_user(&vcpu->arch.ctxt.vfp.fpinst, uaddr, id)
;case KVM_REG_ARM_VFP_FPINST2: return reg_from_user(&vcpu->arch.ctxt.vfp.fpinst2, uaddr, id)
;case KVM_REG_ARM_VFP_MVFR0: if (reg_from_user(&val, uaddr, id)
)
return -EFAULT; if (val != fmrx(MVFR0)
)
return -EINVAL; return 0;case KVM_REG_ARM_VFP_MVFR1: if (reg_from_user(&val, uaddr, id)
)
return -EFAULT; if (val != fmrx(MVFR1)
)
return -EINVAL; return 0;case KVM_REG_ARM_VFP_FPSID: if (reg_from_user(&val, uaddr, id)
)
return -EFAULT; if (val != fmrx(FPSID)
)
return -EINVAL; return 0;default: return -ENOENT;} } static unsigned int num_vfp_regs(void)
static int copy_vfp_regids(u64 __user *uindices)
static int vfp_get_reg(const struct kvm_vcpu *vcpu, u64 id, void __user *uaddr)
static int vfp_set_reg(struct kvm_vcpu *vcpu, u64 id, const void __user *uaddr)
int kvm_arm_coproc_get_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
int kvm_arm_coproc_set_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
static unsigned int num_demux_regs(void)
static int write_demux_regids(u64 __user *uindices)
static u64 cp15_to_index(const struct coproc_reg *reg)
static bool copy_reg_to_user(const struct coproc_reg *reg, u64 __user **uind)
static int walk_cp15(struct kvm_vcpu *vcpu, u64 __user *uind)
unsigned long kvm_arm_num_coproc_regs(struct kvm_vcpu *vcpu)
int kvm_arm_copy_coproc_indices(struct kvm_vcpu *vcpu, u64 __user *uindices)
void kvm_coproc_table_init(void)
void kvm_reset_coprocs(struct kvm_vcpu *vcpu)
\n
     39 struct kvm_vcpu *vcpu
     17 const struct coproc_reg *r
     12 u64 id
     12 const struct coproc_params *p
      7 void __user *uaddr
      7 uaddr
      7 struct kvm_run *run
      7 id
      5 void
      4 u64 __user *uindices
      4 const struct coproc_params *params
      3 reg_from_user&val
      3 const void __user *uaddr
      2 const struct kvm_vcpu *vcpu
      2 const struct kvm_one_reg *reg
      2 const struct coproc_reg *table
      2 const struct coproc_reg *reg
      1 void *val
      1 &vcpu->arch.ctxt.vfp.fpscr
      1 &vcpu->arch.ctxt.vfp.fpinst2
      1 &vcpu->arch.ctxt.vfp.fpinst
      1 &vcpu->arch.ctxt.vfp.fpexc
      1 val != fmrxMVFR1
      1 val != fmrxMVFR0
      1 val != fmrxFPSID
      1 unsigned target
      1 unsigned int num
      1 unsigned int n
      1 u64 val
      1 u64 __user **uind
      1 u64 __user *uind
      1 u32 val
      1 u32 csselr
      1 struct kvm_coproc_target_table *table
      1 struct coproc_params *params
      1 size_t *num
      1 size_t num
      1 const void *val
      1 const void *key
      1 const void *elt
      1 const struct coproc_reg table[]
