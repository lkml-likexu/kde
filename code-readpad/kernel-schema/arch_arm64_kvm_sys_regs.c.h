
\n
static bool read_from_write_only(struct kvm_vcpu *vcpu, struct sys_reg_params *params, const struct sys_reg_desc *r)
static bool write_to_read_only(struct kvm_vcpu *vcpu, struct sys_reg_params *params, const struct sys_reg_desc *r)
u64 vcpu_read_sys_reg(const struct kvm_vcpu *vcpu, int reg)
void vcpu_write_sys_reg(struct kvm_vcpu *vcpu, u64 val, int reg)
static u32 get_ccsidr(u32 csselr)
static bool access_dcsw(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_vm_reg(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_gic_sgi(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_gic_sre(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool trap_raz_wi(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool trap_loregion(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool trap_oslsr_el1(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool trap_dbgauthstatus_el1(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool trap_debug_regs(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static void reg_to_dbg(struct kvm_vcpu *vcpu, struct sys_reg_params *p, u64 *dbg_reg)
static void dbg_to_reg(struct kvm_vcpu *vcpu, struct sys_reg_params *p, u64 *dbg_reg)
static bool trap_bvr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *rd)
static int set_bvr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static int get_bvr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static void reset_bvr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd)
static bool trap_bcr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *rd)
static int set_bcr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static int get_bcr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static void reset_bcr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd)
static bool trap_wvr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *rd)
static int set_wvr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static int get_wvr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static void reset_wvr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd)
static bool trap_wcr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *rd)
static int set_wcr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static int get_wcr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static void reset_wcr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd)
static void reset_amair_el1(struct kvm_vcpu *vcpu, const struct sys_reg_desc *r)
static void reset_mpidr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *r)
static void reset_pmcr(struct kvm_vcpu *vcpu, const struct sys_reg_desc *r)
static bool check_pmu_access_disabled(struct kvm_vcpu *vcpu, u64 flags)
static bool pmu_access_el0_disabled(struct kvm_vcpu *vcpu)
static bool pmu_write_swinc_el0_disabled(struct kvm_vcpu *vcpu)
static bool pmu_access_cycle_counter_el0_disabled(struct kvm_vcpu *vcpu)
static bool pmu_access_event_counter_el0_disabled(struct kvm_vcpu *vcpu)
static bool access_pmcr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_pmselr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_pmceid(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool pmu_counter_idx_valid(struct kvm_vcpu *vcpu, u64 idx)
static bool access_pmu_evcntr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_pmu_evtyper(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_pmcnten(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_pminten(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_pmovs(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_pmswinc(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_pmuserenr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_cntp_tval(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_cntp_ctl(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_cntp_cval(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static u64 read_id_reg(struct sys_reg_desc const *r, bool raz)
static bool __access_id_reg(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r, bool raz)
static bool access_id_reg(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool access_raz_id_reg(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static int __get_id_reg(const struct sys_reg_desc *rd, void __user *uaddr, bool raz)
static int __set_id_reg(const struct sys_reg_desc *rd, void __user *uaddr, bool raz)
static int get_id_reg(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static int set_id_reg(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static int get_raz_id_reg(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static int set_raz_id_reg(struct kvm_vcpu *vcpu, const struct sys_reg_desc *rd, const struct kvm_one_reg *reg, void __user *uaddr)
static bool trap_dbgidr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool trap_debug32(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *r)
static bool trap_xvr(struct kvm_vcpu *vcpu, struct sys_reg_params *p, const struct sys_reg_desc *rd)
void kvm_register_target_sys_reg_table(unsigned int target, struct kvm_sys_reg_target_table *table)
static const struct sys_reg_desc *get_target_table(unsigned target, bool mode_is_64, size_t *num)
static int match_sys_reg(const void *key, const void *elt)
static const struct sys_reg_desc *find_reg(const struct sys_reg_params *params, const struct sys_reg_desc table[], unsigned int num)
int kvm_handle_cp14_load_store(struct kvm_vcpu *vcpu, struct kvm_run *run)
static void perform_access(struct kvm_vcpu *vcpu, struct sys_reg_params *params, const struct sys_reg_desc *r)
static int emulate_cp(struct kvm_vcpu *vcpu, struct sys_reg_params *params, const struct sys_reg_desc *table, size_t num)
static void unhandled_cp_access(struct kvm_vcpu *vcpu, struct sys_reg_params *params)
static int kvm_handle_cp_64(struct kvm_vcpu *vcpu, const struct sys_reg_desc *global, size_t nr_global, const struct sys_reg_desc *target_specific, size_t nr_specific)
static int kvm_handle_cp_32(struct kvm_vcpu *vcpu, const struct sys_reg_desc *global, size_t nr_global, const struct sys_reg_desc *target_specific, size_t nr_specific)
int kvm_handle_cp15_64(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_handle_cp15_32(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_handle_cp14_64(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_handle_cp14_32(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int emulate_sys_reg(struct kvm_vcpu *vcpu, struct sys_reg_params *params)
static void reset_sys_reg_descs(struct kvm_vcpu *vcpu, const struct sys_reg_desc *table, size_t num)
int kvm_handle_sys_reg(struct kvm_vcpu *vcpu, struct kvm_run *run)
static bool index_to_params(u64 id, struct sys_reg_params *params)
const struct sys_reg_desc *find_reg_by_id(u64 id, struct sys_reg_params *params, const struct sys_reg_desc table[], unsigned int num)
static const struct sys_reg_desc *index_to_sys_reg_desc(struct kvm_vcpu *vcpu, u64 id)
static int reg_from_user(u64 *val, const void __user *uaddr, u64 id)
static int reg_to_user(void __user *uaddr, const u64 *val, u64 id)
static int get_invariant_sys_reg(u64 id, void __user *uaddr)
static int set_invariant_sys_reg(u64 id, void __user *uaddr)
static bool is_valid_cache(u32 val)
static int demux_c15_get(u64 id, void __user *uaddr)
static int demux_c15_set(u64 id, void __user *uaddr)
int kvm_arm_sys_reg_get_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
int kvm_arm_sys_reg_set_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
static unsigned int num_demux_regs(void)
static int write_demux_regids(u64 __user *uindices)
static u64 sys_reg_to_index(const struct sys_reg_desc *reg)
static bool copy_reg_to_user(const struct sys_reg_desc *reg, u64 __user **uind)
static int walk_one_sys_reg(const struct sys_reg_desc *rd, u64 __user **uind, unsigned int *total)
static int walk_sys_regs(struct kvm_vcpu *vcpu, u64 __user *uind)
unsigned long kvm_arm_num_sys_reg_descs(struct kvm_vcpu *vcpu)
int kvm_arm_copy_sys_reg_indices(struct kvm_vcpu *vcpu, u64 __user *uindices)
static int check_sysreg_table(const struct sys_reg_desc *table, unsigned int n)
void kvm_sys_reg_table_init(void)
void kvm_reset_sys_regs(struct kvm_vcpu *vcpu)
\n
     82 struct kvm_vcpu *vcpu
     34 struct sys_reg_params *p
     33 const struct sys_reg_desc *r
     24 const struct sys_reg_desc *rd
     19 void __user *uaddr
     14 const struct kvm_one_reg *reg
      9 u64 id
      8 struct sys_reg_params *params
      6 struct kvm_run *run
      4 bool raz
      3 const struct sys_reg_desc *table
      2 void
      2 unsigned int num
      2 u64 __user *uindices
      2 u64 __user **uind
      2 u64 *dbg_reg
      2 size_t num
      2 size_t nr_specific
      2 size_t nr_global
      2 int reg
      2 const struct sys_reg_desc *target_specific
      2 const struct sys_reg_desc table[]
      2 const struct sys_reg_desc *reg
      2 const struct sys_reg_desc *global
      1 unsigned target
      1 unsigned int *total
      1 unsigned int target
      1 unsigned int n
      1 u64 *val
      1 u64 val
      1 u64 __user *uind
      1 u64 idx
      1 u64 flags
      1 u32 val
      1 u32 csselr
      1 struct sys_reg_desc const *r
      1 struct kvm_sys_reg_target_table *table
      1 size_t *num
      1 const void __user *uaddr
      1 const void *key
      1 const void *elt
      1 const u64 *val
      1 const struct sys_reg_params *params
      1 const struct kvm_vcpu *vcpu
      1 bool mode_is_64
