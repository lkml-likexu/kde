
static int __init set_x2apic_phys_mode(char *arg)
static bool x2apic_fadt_phys(void)
static int x2apic_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
static void x2apic_send_IPI(int cpu, int vector)
static void __x2apic_send_IPI_mask(const struct cpumask *mask, int vector, int apic_dest)
static void x2apic_send_IPI_mask(const struct cpumask *mask, int vector)
static voidx2apic_send_IPI_mask_allbutself(const struct cpumask *mask, int vector)
static void x2apic_send_IPI_allbutself(int vector)
static void x2apic_send_IPI_all(int vector)
static void init_x2apic_ldr(void)
static int x2apic_phys_probe(void)
int x2apic_apic_id_valid(u32 apicid)
int x2apic_apic_id_registered(void)
void __x2apic_send_IPI_dest(unsigned int apicid, int vector, unsigned int dest)
unsigned int x2apic_get_apic_id(unsigned long id)
u32 x2apic_set_apic_id(unsigned int id)
int x2apic_phys_pkg_id(int initial_apicid, int index_msb)
void x2apic_send_IPI_self(int vector)
   8 int vector
   4 void
   3 const struct cpumask *mask
   1 unsigned long id
   1 unsigned int id
   1 unsigned int dest
   1 unsigned int apicid
   1 u32 apicid
   1 int initial_apicid
   1 int index_msb
   1 int cpu
   1 int apic_dest
   1 char *oem_table_id
   1 char *oem_id
   1 char *arg
