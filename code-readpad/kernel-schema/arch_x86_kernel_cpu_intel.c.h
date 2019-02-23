
\n
static int __init forcempx_setup(char *__unused)
void check_mpx_erratum(struct cpuinfo_x86 *c)
static int __init ring3mwait_disable(char *__unused)
static void probe_xeon_phi_r3mwait(struct cpuinfo_x86 *c)
static bool bad_spectre_microcode(struct cpuinfo_x86 *c)
static void early_init_intel(struct cpuinfo_x86 *c)
int ppro_with_ram_bug(void)
static void intel_smp_check(struct cpuinfo_x86 *c)
static int forcepae; static int __init forcepae_setup(char *__unused)
static void intel_workarounds(struct cpuinfo_x86 *c)
intel_smp_check(c)
; } static void intel_workarounds(struct cpuinfo_x86 *c)
static void srat_detect_node(struct cpuinfo_x86 *c)
static void detect_vmx_virtcap(struct cpuinfo_x86 *c)
static void detect_tme(struct cpuinfo_x86 *c)
static void init_intel_energy_perf(struct cpuinfo_x86 *c)
static void intel_bsp_resume(struct cpuinfo_x86 *c)
static void init_cpuid_fault(struct cpuinfo_x86 *c)
static void init_intel_misc_features(struct cpuinfo_x86 *c)
static void init_intel(struct cpuinfo_x86 *c)
static unsigned int intel_size_cache(struct cpuinfo_x86 *c, unsigned int size)
static void intel_tlb_lookup(const unsigned char desc)
static void intel_detect_tlb(struct cpuinfo_x86 *c)
\n
     17 struct cpuinfo_x86 *c
      3 char *__unused
      1 void
      1 unsigned int size
      1 const unsigned char desc
      1 c
