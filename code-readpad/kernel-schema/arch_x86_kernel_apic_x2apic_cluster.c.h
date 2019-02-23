
\n
static int x2apic_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
static void x2apic_send_IPI(int cpu, int vector)
static void __x2apic_send_IPI_mask(const struct cpumask *mask, int vector, int apic_dest)
static void x2apic_send_IPI_mask(const struct cpumask *mask, int vector)
static void x2apic_send_IPI_mask_allbutself(const struct cpumask *mask, int vector)
static void x2apic_send_IPI_allbutself(int vector)
static void x2apic_send_IPI_all(int vector)
static u32 x2apic_calc_apicid(unsigned int cpu)
static void init_x2apic_ldr(void)
static int alloc_clustermask(unsigned int cpu, int node)
static int x2apic_prepare_cpu(unsigned int cpu)
static int x2apic_dead_cpu(unsigned int dead_cpu)
static int x2apic_cluster_probe(void)
\n
      6 int vector
      3 unsigned int cpu
      3 const struct cpumask *mask
      2 void
      1 unsigned int dead_cpu
      1 int node
      1 int cpu
      1 int apic_dest
      1 char *oem_table_id
      1 char *oem_id
