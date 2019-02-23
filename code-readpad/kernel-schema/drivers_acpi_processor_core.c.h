
EXPORT_SYMBOL_GPL(acpi_get_phys_id);
EXPORT_SYMBOL_GPL(acpi_get_cpuid);
\n
static struct acpi_table_madt *get_madt_table(void)
static int map_lapic_id(struct acpi_subtable_header *entry, u32 acpi_id, phys_cpuid_t *apic_id)
static int map_x2apic_id(struct acpi_subtable_header *entry, int device_declaration, u32 acpi_id, phys_cpuid_t *apic_id)
static int map_lsapic_id(struct acpi_subtable_header *entry, int device_declaration, u32 acpi_id, phys_cpuid_t *apic_id)
static int map_gicc_mpidr(struct acpi_subtable_header *entry, int device_declaration, u32 acpi_id, phys_cpuid_t *mpidr)
static phys_cpuid_t map_madt_entry(struct acpi_table_madt *madt, int type, u32 acpi_id)
phys_cpuid_t __init acpi_map_madt_entry(u32 acpi_id)
static phys_cpuid_t map_mat_entry(acpi_handle handle, int type, u32 acpi_id)
phys_cpuid_t acpi_get_phys_id(acpi_handle handle, int type, u32 acpi_id)
int acpi_map_cpuid(phys_cpuid_t phys_id, u32 acpi_id)
int acpi_get_cpuid(acpi_handle handle, int type, u32 acpi_id)
static int get_ioapic_id(struct acpi_subtable_header *entry, u32 gsi_base, u64 *phys_addr, int *ioapic_id)
static int parse_madt_ioapic_entry(u32 gsi_base, u64 *phys_addr)
static int parse_mat_ioapic_entry(acpi_handle handle, u32 gsi_base, u64 *phys_addr)
int acpi_get_ioapic_id(acpi_handle handle, u32 gsi_base, u64 *phys_addr)
\n
     10 u32 acpi_id
      5 struct acpi_subtable_header *entry
      5 acpi_handle handle
      4 u64 *phys_addr
      4 u32 gsi_base
      4 int type
      3 phys_cpuid_t *apic_id
      3 int device_declaration
      1 void
      1 struct acpi_table_madt *madt
      1 phys_cpuid_t phys_id
      1 phys_cpuid_t *mpidr
      1 int *ioapic_id
      1 acpi_get_phys_id
      1 acpi_get_cpuid
