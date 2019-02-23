
\n
int arch_update_cpu_topology(void)
static inline void smpboot_setup_warm_reset_vector(unsigned long start_eip)
static inline void smpboot_restore_warm_reset_vector(void)
static void smp_callin(void)
static int cpu0_logical_apicid; static int enable_start_cpu0;static void notrace start_secondary(void *unused)
bool topology_is_primary_thread(unsigned int cpu)
bool topology_smt_supported(void)
int topology_phys_to_logical_pkg(unsigned int phys_pkg)
int topology_update_package_map(unsigned int pkg, unsigned int cpu)
void __init smp_store_boot_cpu_info(void)
void smp_store_cpu_info(int id)
static bool topology_same_node(struct cpuinfo_x86 *c, struct cpuinfo_x86 *o)
static bool topology_sane(struct cpuinfo_x86 *c, struct cpuinfo_x86 *o, const char *name)
static bool match_smt(struct cpuinfo_x86 *c, struct cpuinfo_x86 *o)
static bool match_llc(struct cpuinfo_x86 *c, struct cpuinfo_x86 *o)
static bool match_die(struct cpuinfo_x86 *c, struct cpuinfo_x86 *o)
static inline int x86_sched_itmt_flags(void)
static int x86_core_flags(void)
static int x86_core_flags(void)
return cpu_core_flags()
| x86_sched_itmt_flags()
; }endif static int x86_smt_flags(void)
void set_cpu_sibling_map(int cpu)
const struct cpumask *cpu_coregroup_mask(int cpu)
static void impress_friends(void)
void __inquire_remote_apic(int apicid)
static int __init cpu_init_udelay(char *str)
static void __init smp_quirk_init_udelay(void)
int wakeup_secondary_cpu_via_nmi(int apicid, unsigned long start_eip)
static int wakeup_secondary_cpu_via_init(int phys_apicid, unsigned long start_eip)
static void announce_cpu(int cpu, int apicid)
static int wakeup_cpu0_nmi(unsigned int cmd, struct pt_regs *regs)
static int wakeup_cpu_via_init_nmi(int cpu, unsigned long start_ip, int apicid, int *cpu0_nmi_registered)
void common_cpu_up(unsigned int cpu, struct task_struct *idle)
static int do_boot_cpu(int apicid, int cpu, struct task_struct *idle, int *cpu0_nmi_registered)
int native_cpu_up(unsigned int cpu, struct task_struct *tidle)
void arch_disable_smp_support(void)
static __init void disable_smp(void)
static void __init smp_sanity_check(void)
static void __init smp_cpu_index_default(void)
static void __init smp_get_logical_apicid(void)
void __init native_smp_prepare_cpus(unsigned int max_cpus)
void arch_enable_nonboot_cpus_begin(void)
void arch_enable_nonboot_cpus_end(void)
void __init native_smp_prepare_boot_cpu(void)
void __init calculate_max_logical_packages(void)
void __init native_smp_cpus_done(unsigned int max_cpus)
static int __initdata setup_possible_cpus = -1; static int __init _setup_possible_cpus(char *str)
__init void prefill_possible_map(void)
static void recompute_smt_state(void)
static void remove_siblinginfo(int cpu)
static void remove_cpu_from_maps(int cpu)
void cpu_disable_common(void)
int native_cpu_disable(void)
int common_cpu_die(unsigned int cpu)
void native_cpu_die(unsigned int cpu)
void play_dead_common(void)
static bool wakeup_cpu0(void)
static inline void mwait_play_dead(void)
void hlt_play_dead(void)
void native_play_dead(void)
int native_cpu_disable(void)
void native_cpu_die(unsigned int cpu)
void native_play_dead(void)
\n
     31 void
      7 unsigned int cpu
      7 int cpu
      5 struct cpuinfo_x86 *o
      5 struct cpuinfo_x86 *c
      5 int apicid
      3 unsigned long start_eip
      2 unsigned int max_cpus
      2 struct task_struct *idle
      2 int *cpu0_nmi_registered
      2 char *str
      2 
      1 void *unused
      1 unsigned long start_ip
      1 unsigned int pkg
      1 unsigned int phys_pkg
      1 unsigned int cmd
      1 struct task_struct *tidle
      1 struct pt_regs *regs
      1 int phys_apicid
      1 int id
      1 const char *name
