
\n
static unsigned bigsmp_get_apic_id(unsigned long x)
static int bigsmp_apic_id_registered(void)
static bool bigsmp_check_apicid_used(physid_mask_t *map, int apicid)
static int bigsmp_early_logical_apicid(int cpu)
static inline unsigned long calculate_ldr(int cpu)
static void bigsmp_init_apic_ldr(void)
static void bigsmp_setup_apic_routing(void)
static int bigsmp_cpu_present_to_apicid(int mps_cpu)
static void bigsmp_ioapic_phys_id_map(physid_mask_t *phys_map, physid_mask_t *retmap)
static int bigsmp_check_phys_apicid_present(int phys_apicid)
static int bigsmp_phys_pkg_id(int cpuid_apic, int index_msb)
static void bigsmp_send_IPI_allbutself(int vector)
static void bigsmp_send_IPI_all(int vector)
static int hp_ht_bigsmp(const struct dmi_system_id *d)
static int probe_bigsmp(void)
void __init generic_bigsmp_probe(void)
\n
      5 void
      2 int vector
      2 int cpu
      1 unsigned long x
      1 physid_mask_t *retmap
      1 physid_mask_t *phys_map
      1 physid_mask_t *map
      1 int phys_apicid
      1 int mps_cpu
      1 int index_msb
      1 int cpuid_apic
      1 int apicid
      1 const struct dmi_system_id *d
