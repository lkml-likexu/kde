
EXPORT_SYMBOL_GPL(apic);
\n
static int flat_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
void flat_init_apic_ldr(void)
static void _flat_send_IPI_mask(unsigned long mask, int vector)
static void flat_send_IPI_mask(const struct cpumask *cpumask, int vector)
static void flat_send_IPI_mask_allbutself(const struct cpumask *cpumask, int vector)
static void flat_send_IPI_allbutself(int vector)
static void flat_send_IPI_all(int vector)
static unsigned int flat_get_apic_id(unsigned long x)
static u32 set_apic_id(unsigned int id)
static unsigned int read_xapic_id(void)
static int flat_apic_id_registered(void)
static int flat_phys_pkg_id(int initial_apic_id, int index_msb)
static int flat_probe(void)
static int physflat_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
static void physflat_init_apic_ldr(void)
static void physflat_send_IPI_allbutself(int vector)
static void physflat_send_IPI_all(int vector)
static int physflat_probe(void)
\n
      7 int vector
      6 void
      2 const struct cpumask *cpumask
      2 char *oem_table_id
      2 char *oem_id
      1 unsigned long x
      1 unsigned long mask
      1 unsigned int id
      1 int initial_apic_id
      1 int index_msb
      1 apic
