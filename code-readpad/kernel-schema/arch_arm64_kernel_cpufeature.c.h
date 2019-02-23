
EXPORT_SYMBOL_GPL(elf_hwcap);
\n
static inline void set_sys_caps_initialised(void)
static int dump_cpu_hwcaps(struct notifier_block *self, unsigned long v, void *p)
static int __init register_cpu_hwcaps_dumper(void)
static int search_cmp_ftr_reg(const void *id, const void *regp)
static struct arm64_ftr_reg *get_arm64_ftr_reg(u32 sys_id)
static u64 arm64_ftr_set_value(const struct arm64_ftr_bits *ftrp, s64 reg, s64 ftr_val)
static s64 arm64_ftr_safe_value(const struct arm64_ftr_bits *ftrp, s64 new, s64 cur)
static void __init sort_ftr_regs(void)
static void __init init_cpu_ftr_reg(u32 sys_reg, u64 new)
static void __init init_cpu_hwcaps_indirect_list_from_array(const struct arm64_cpu_capabilities *caps)
static void __init init_cpu_hwcaps_indirect_list(void)
void __init init_cpu_features(struct cpuinfo_arm64 *info)
static void update_cpu_ftr_reg(struct arm64_ftr_reg *reg, u64 new)
static int check_update_ftr_reg(u32 sys_id, int cpu, u64 val, u64 boot)
void update_cpu_features(int cpu, struct cpuinfo_arm64 *info, struct cpuinfo_arm64 *boot)
u64 read_sanitised_ftr_reg(u32 id)
static u64 __read_sysreg_by_encoding(u32 sys_id)
static bool feature_matches(u64 reg, const struct arm64_cpu_capabilities *entry)
static bool has_cpuid_feature(const struct arm64_cpu_capabilities *entry, int scope)
static bool has_useable_gicv3_cpuif(const struct arm64_cpu_capabilities *entry, int scope)
static bool has_no_hw_prefetch(const struct arm64_cpu_capabilities *entry, int __unused)
static bool has_no_fpsimd(const struct arm64_cpu_capabilities *entry, int __unused)
static bool has_cache_idc(const struct arm64_cpu_capabilities *entry, int scope)
static void cpu_emulate_effective_ctr(const struct arm64_cpu_capabilities *__unused)
static bool has_cache_dic(const struct arm64_cpu_capabilities *entry, int scope)
static bool __maybe_unused has_useable_cnp(const struct arm64_cpu_capabilities *entry, int scope)
static bool unmap_kernel_at_el0(const struct arm64_cpu_capabilities *entry, int scope)
static void kpti_install_ng_mappings(const struct arm64_cpu_capabilities *__unused)
static int __init parse_kpti(char *str)
static inline void __cpu_enable_hw_dbm(void)
static bool cpu_has_broken_dbm(void)
static bool cpu_can_use_dbm(const struct arm64_cpu_capabilities *cap)
static void cpu_enable_hw_dbm(struct arm64_cpu_capabilities const *cap)
static bool has_hw_dbm(const struct arm64_cpu_capabilities *cap, int __unused)
static bool runs_at_el2(const struct arm64_cpu_capabilities *entry, int __unused)
static void cpu_copy_el2regs(const struct arm64_cpu_capabilities *__unused)
static void cpu_has_fwb(const struct arm64_cpu_capabilities *__unused)
static int ssbs_emulation_handler(struct pt_regs *regs, u32 instr)
static void cpu_enable_ssbs(const struct arm64_cpu_capabilities *__unused)
static void cpu_enable_pan(const struct arm64_cpu_capabilities *__unused)
static void cpu_clear_disr(const struct arm64_cpu_capabilities *__unused)
static void cpu_enable_address_auth(struct arm64_cpu_capabilities const *cap)
static void __init cap_set_elf_hwcap(const struct arm64_cpu_capabilities *cap)
static bool cpus_have_elf_hwcap(const struct arm64_cpu_capabilities *cap)
static void __init setup_elf_hwcaps(const struct arm64_cpu_capabilities *hwcaps)
static void update_cpu_capabilities(u16 scope_mask)
static int cpu_enable_non_boot_scope_capabilities(void *__unused)
static void __init enable_cpu_capabilities(u16 scope_mask)
static bool verify_local_cpu_caps(u16 scope_mask)
static void check_early_cpu_features(void)
static void verify_local_elf_hwcaps(const struct arm64_cpu_capabilities *caps)
static void verify_sve_features(void)
static void verify_local_cpu_capabilities(void)
void check_local_cpu_capabilities(void)
static void __init setup_boot_cpu_capabilities(void)
static void __init mark_const_caps_ready(void)
bool this_cpu_has_cap(unsigned int n)
static void __init setup_system_capabilities(void)
void __init setup_cpu_features(void)
static bool __maybe_unused cpufeature_pan_not_uao(const struct arm64_cpu_capabilities *entry, int __unused)
static void __maybe_unused cpu_enable_cnp(struct arm64_cpu_capabilities const *cap)
static inline bool __attribute_const__ is_emulated(u32 id)
static inline int emulate_id_reg(u32 id, u64 *valp)
static int emulate_sys_reg(u32 id, u64 *valp)
int do_emulate_mrs(struct pt_regs *regs, u32 sys_reg, u32 rt)
static int emulate_mrs(struct pt_regs *regs, u32 insn)
static int __init enable_mrs_emulation(void)
\n
     15 void
     11 const struct arm64_cpu_capabilities *entry
      7 const struct arm64_cpu_capabilities *__unused
      6 int scope
      5 int __unused
      4 u32 id
      4 const struct arm64_cpu_capabilities *cap
      3 u32 sys_id
      3 u16 scope_mask
      3 struct pt_regs *regs
      3 struct arm64_cpu_capabilities const *cap
      2 u64 *valp
      2 u64 new
      2 u32 sys_reg
      2 struct cpuinfo_arm64 *info
      2 int cpu
      2 const struct arm64_ftr_bits *ftrp
      2 const struct arm64_cpu_capabilities *caps
      1 void *__unused
      1 void *p
      1 unsigned long v
      1 unsigned int n
      1 u64 val
      1 u64 reg
      1 u64 boot
      1 u32 rt
      1 u32 instr
      1 u32 insn
      1 struct notifier_block *self
      1 struct cpuinfo_arm64 *boot
      1 struct arm64_ftr_reg *reg
      1 s64 reg
      1 s64 new
      1 s64 ftr_val
      1 s64 cur
      1 elf_hwcap
      1 const void *regp
      1 const void *id
      1 const struct arm64_cpu_capabilities *hwcaps
      1 char *str
