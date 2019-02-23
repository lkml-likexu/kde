
\n
static bool __maybe_unused is_affected_midr_range(const struct arm64_cpu_capabilities *entry, int scope)
static bool __maybe_unused is_affected_midr_range_list(const struct arm64_cpu_capabilities *entry, int scope)
static bool __maybe_unused is_kryo_midr(const struct arm64_cpu_capabilities *entry, int scope)
static bool has_mismatched_cache_type(const struct arm64_cpu_capabilities *entry, int scope)
static void cpu_enable_trap_ctr_access(const struct arm64_cpu_capabilities *__unused)
static void __copy_hyp_vect_bpi(int slot, const char *hyp_vecs_start, const char *hyp_vecs_end)
static void __install_bp_hardening_cb(bp_hardening_cb_t fn, const char *hyp_vecs_start, const char *hyp_vecs_end)
static void __install_bp_hardening_cb(bp_hardening_cb_t fn, const char *hyp_vecs_start, const char *hyp_vecs_end)
static voidinstall_bp_hardening_cb(const struct arm64_cpu_capabilities *entry, bp_hardening_cb_t fn, const char *hyp_vecs_start, const char *hyp_vecs_end)
static void call_smc_arch_workaround_1(void)
static void call_hvc_arch_workaround_1(void)
static void qcom_link_stack_sanitization(void)
static void enable_smccc_arch_workaround_1(const struct arm64_cpu_capabilities *entry)
static int __init ssbd_cfg(char *buf)
void __init arm64_update_smccc_conduit(struct alt_instr *alt, __le32 *origptr, __le32 *updptr, int nr_inst)
void __init arm64_enable_wa2_handling(struct alt_instr *alt, __le32 *origptr, __le32 *updptr, int nr_inst)
void arm64_set_ssbd_mitigation(bool state)
static bool has_ssbd_mitigation(const struct arm64_cpu_capabilities *entry, int scope)
static void __maybe_unused cpu_enable_cache_maint_trap(const struct arm64_cpu_capabilities *__unused)
\n
      7 const struct arm64_cpu_capabilities *entry
      5 int scope
      4 const char *hyp_vecs_start
      4 const char *hyp_vecs_end
      3 void
      3 bp_hardening_cb_t fn
      2 struct alt_instr *alt
      2 __le32 *updptr
      2 __le32 *origptr
      2 int nr_inst
      2 const struct arm64_cpu_capabilities *__unused
      1 int slot
      1 char *buf
      1 bool state
