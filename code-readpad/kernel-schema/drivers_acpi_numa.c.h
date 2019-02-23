
\n
int pxm_to_node(int pxm)
int node_to_pxm(int node)
static void __acpi_map_pxm_to_node(int pxm, int node)
int acpi_map_pxm_to_node(int pxm)
int acpi_map_pxm_to_online_node(int pxm)
static void __init acpi_table_print_srat_entry(struct acpi_subtable_header *header)
static int __init slit_valid(struct acpi_table_slit *slit)
void __init bad_srat(void)
int __init srat_disabled(void)
void __init acpi_numa_slit_init(struct acpi_table_slit *slit)
int __init acpi_numa_memory_affinity_init(struct acpi_srat_mem_affinity *ma)
static int __init acpi_parse_slit(struct acpi_table_header *table)
void __init __weak acpi_numa_x2apic_affinity_init(struct acpi_srat_x2apic_cpu_affinity *pa)
static int __init acpi_parse_x2apic_affinity(struct acpi_subtable_header *header, const unsigned long end)
static int __init acpi_parse_processor_affinity(struct acpi_subtable_header *header, const unsigned long end)
static int __init acpi_parse_gicc_affinity(struct acpi_subtable_header *header, const unsigned long end)
static int __init acpi_parse_memory_affinity(struct acpi_subtable_header * header, const unsigned long end)
static int __init acpi_parse_srat(struct acpi_table_header *table)
static int __init acpi_table_parse_srat(enum acpi_srat_type id, acpi_tbl_entry_handler handler, unsigned int max_entries)
int __init acpi_numa_init(void)
static int acpi_get_pxm(acpi_handle h)
int acpi_get_node(acpi_handle handle)
\n
      4 struct acpi_subtable_header *header
      4 int pxm
      4 const unsigned long end
      3 void
      2 struct acpi_table_slit *slit
      2 struct acpi_table_header *table
      2 int node
      1 unsigned int max_entries
      1 struct acpi_subtable_header * header
      1 struct acpi_srat_x2apic_cpu_affinity *pa
      1 struct acpi_srat_mem_affinity *ma
      1 enum acpi_srat_type id
      1 acpi_tbl_entry_handler handler
      1 acpi_handle handle
      1 acpi_handle h
