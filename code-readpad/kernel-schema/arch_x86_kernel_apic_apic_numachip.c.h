
static unsigned int numachip1_get_apic_id(unsigned long x)
static u32 numachip1_set_apic_id(unsigned int id)
static unsigned int numachip2_get_apic_id(unsigned long x)
static u32 numachip2_set_apic_id(unsigned int id)
static int numachip_apic_id_valid(u32 apicid)
static int numachip_apic_id_registered(void)
static int numachip_phys_pkg_id(int initial_apic_id, int index_msb)
static void numachip1_apic_icr_write(int apicid, unsigned int val)
static void numachip2_apic_icr_write(int apicid, unsigned int val)
static int numachip_wakeup_secondary(int phys_apicid, unsigned long start_rip)
static void numachip_send_IPI_one(int cpu, int vector)
static void numachip_send_IPI_mask(const struct cpumask *mask, int vector)
static void numachip_send_IPI_mask_allbutself(const struct cpumask *mask, int vector)
static void numachip_send_IPI_allbutself(int vector)
static void numachip_send_IPI_all(int vector)
static void numachip_send_IPI_self(int vector)
static int __init numachip1_probe(void)
static int __init numachip2_probe(void)
static void fixup_cpu_id(struct cpuinfo_x86 *c, int node)
static int __init numachip_system_init(void)
static int numachip1_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
static int numachip2_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
static void numachip_apic_wait_icr_idle(void)
static u32 numachip_safe_apic_wait_icr_idle(void)
   6 void
   6 int vector
   2 unsigned long x
   2 unsigned int val
   2 unsigned int id
   2 int apicid
   2 const struct cpumask *mask
   2 char *oem_table_id
   2 char *oem_id
   1 unsigned long start_rip
   1 u32 apicid
   1 struct cpuinfo_x86 *c
   1 int phys_apicid
   1 int node
   1 int initial_apic_id
   1 int index_msb
   1 int cpu
