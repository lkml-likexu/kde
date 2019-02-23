
EXPORT_SYMBOL_GPL(load_direct_gdt);
EXPORT_SYMBOL_GPL(load_fixmap_gdt);
\n
void __init setup_cpu_local_masks(void)
static void default_init(struct cpuinfo_x86 *c)
static int __init x86_mpx_setup(char *s)
static int __init x86_nopcid_setup(char *s)
static int __init x86_noinvpcid_setup(char *s)
static int __init cachesize_setup(char *str)
static int __init x86_sep_setup(char *s)
static inline int flag_is_changeable_p(u32 flag)
int have_cpuid_p(void)
static void squash_the_stupid_serial_number(struct cpuinfo_x86 *c)
static int __init x86_serial_nr_setup(char *s)
static int __init x86_serial_nr_setup(char *s)
disable_x86_serial_nr = 0;return 1; } __setup("serialnumber", x86_serial_nr_setup)
; static inline int flag_is_changeable_p(u32 flag)
static int __init x86_serial_nr_setup(char *s)
disable_x86_serial_nr = 0;return 1; } __setup("serialnumber", x86_serial_nr_setup)
; static inline int flag_is_changeable_p(u32 flag)
return 1; } static inline void squash_the_stupid_serial_number(struct cpuinfo_x86 *c)
static __init int setup_disable_smep(char *arg)
static __always_inline void setup_smep(struct cpuinfo_x86 *c)
static __init int setup_disable_smap(char *arg)
static __always_inline void setup_smap(struct cpuinfo_x86 *c)
static __always_inline void setup_umip(struct cpuinfo_x86 *c)
static __always_inline void setup_pku(struct cpuinfo_x86 *c)
static __init int setup_disable_pku(char *arg)
static void filter_cpuid_features(struct cpuinfo_x86 *c, bool warn)
static const char *table_lookup_model(struct cpuinfo_x86 *c)
void load_percpu_segment(int cpu)
void load_direct_gdt(int cpu)
void load_fixmap_gdt(int cpu)
void switch_to_new_gdt(int cpu)
static void get_model_name(struct cpuinfo_x86 *c)
void detect_num_cpu_cores(struct cpuinfo_x86 *c)
void cpu_detect_cache_sizes(struct cpuinfo_x86 *c)
static void cpu_detect_tlb(struct cpuinfo_x86 *c)
int detect_ht_early(struct cpuinfo_x86 *c)
void detect_ht(struct cpuinfo_x86 *c)
static void get_cpu_vendor(struct cpuinfo_x86 *c)
void cpu_detect(struct cpuinfo_x86 *c)
static void apply_forced_caps(struct cpuinfo_x86 *c)
static void init_speculation_control(struct cpuinfo_x86 *c)
void get_cpu_cap(struct cpuinfo_x86 *c)
void get_cpu_address_sizes(struct cpuinfo_x86 *c)
static void identify_cpu_without_cpuid(struct cpuinfo_x86 *c)
static void __init cpu_set_bug_bits(struct cpuinfo_x86 *c)
static void detect_nopl(void)
static void __init early_identify_cpu(struct cpuinfo_x86 *c)
void __init early_cpu_init(void)
static void detect_null_seg_behavior(struct cpuinfo_x86 *c)
static void generic_identify(struct cpuinfo_x86 *c)
static void x86_init_cache_qos(struct cpuinfo_x86 *c)
static void validate_apic_and_package_id(struct cpuinfo_x86 *c)
static void identify_cpu(struct cpuinfo_x86 *c)
void enable_sep_cpu(void)
void __init identify_boot_cpu(void)
void identify_secondary_cpu(struct cpuinfo_x86 *c)
static __init int setup_noclflush(char *arg)
void print_cpu_info(struct cpuinfo_x86 *c)
static __init int setup_clearcpuid(char *arg)
void syscall_init(void)
int is_debug_stack(unsigned long addr)
void debug_stack_set_zero(void)
void debug_stack_reset(void)
static void clear_all_debug_regs(void)
static void dbg_restore_debug_regs(void)
static void wait_for_master_cpu(int cpu)
static void setup_getcpu(int cpu)
void cpu_init(void)
void cpu_init(void)
static void bsp_resume(void)
static int __init init_cpu_syscore(void)
void microcode_check(void)
\n
     31 struct cpuinfo_x86 *c
     16 void
      7 char *s
      6 int cpu
      5 char *arg
      3 u32 flag
      2 x86_serial_nr_setup
      2 "serialnumber"
      1 unsigned long addr
      1 load_fixmap_gdt
      1 load_direct_gdt
      1 char *str
      1 bool warn
