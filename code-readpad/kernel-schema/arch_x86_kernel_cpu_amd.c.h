
EXPORT_SYMBOL_GPL(amd_get_nb_id);
EXPORT_SYMBOL_GPL(amd_get_nodes_per_socket);
static inline int rdmsrl_amd_safe(unsigned msr, unsigned long long *p)
static inline int wrmsrl_amd_safe(unsigned msr, unsigned long long val)
static void init_amd_k5(struct cpuinfo_x86 *c)
static void init_amd_k6(struct cpuinfo_x86 *c)
static void init_amd_k7(struct cpuinfo_x86 *c)
static int nearby_node(int apicid)
static void legacy_fixup_core_id(struct cpuinfo_x86 *c)
static void amd_get_topology_early(struct cpuinfo_x86 *c)
static void amd_get_topology(struct cpuinfo_x86 *c)
static void amd_detect_cmp(struct cpuinfo_x86 *c)
u16 amd_get_nb_id(int cpu)
u32 amd_get_nodes_per_socket(void)
static void srat_detect_node(struct cpuinfo_x86 *c)
static void early_init_amd_mc(struct cpuinfo_x86 *c)
static void bsp_init_amd(struct cpuinfo_x86 *c)
static void early_detect_mem_encrypt(struct cpuinfo_x86 *c)
static void early_init_amd(struct cpuinfo_x86 *c)
static void init_amd_k8(struct cpuinfo_x86 *c)
static void init_amd_gh(struct cpuinfo_x86 *c)
static void init_amd_ln(struct cpuinfo_x86 *c)
static void init_amd_bd(struct cpuinfo_x86 *c)
static void init_amd_zn(struct cpuinfo_x86 *c)
static void init_amd(struct cpuinfo_x86 *c)
static unsigned int amd_size_cache(struct cpuinfo_x86 *c, unsigned int size)
static void cpu_detect_tlb_amd(struct cpuinfo_x86 *c)
static bool cpu_has_amd_erratum(struct cpuinfo_x86 *cpu, const int *erratum)
void set_dr_addr_mask(unsigned long mask, int dr)
  20 struct cpuinfo_x86 *c
   2 unsigned msr
   1 void
   1 unsigned long mask
   1 unsigned long long val
   1 unsigned long long *p
   1 unsigned int size
   1 struct cpuinfo_x86 *cpu
   1 int dr
   1 int cpu
   1 int apicid
   1 const int *erratum
   1 amd_get_nodes_per_socket
   1 amd_get_nb_id
