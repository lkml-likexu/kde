
EXPORT_SYMBOL_GPL(acpi_register_gsi);
EXPORT_SYMBOL_GPL(acpi_unregister_gsi);
static unsigned long __init acpi_find_rsdp(void)
const char __init * acpi_get_sysname(void)
int acpi_request_vector(u32 int_type)
void __init __iomem *__acpi_map_table(unsigned long phys, unsigned long size)
void __init __acpi_unmap_table(void __iomem *map, unsigned long size)
static int __init acpi_parse_lapic_addr_ovr(struct acpi_subtable_header * header, const unsigned long end)
static int __init acpi_parse_lsapic(struct acpi_subtable_header * header, const unsigned long end)
static int __init acpi_parse_lapic_nmi(struct acpi_subtable_header * header, const unsigned long end)
static int __init acpi_parse_iosapic(struct acpi_subtable_header * header, const unsigned long end)
static int __init acpi_parse_plat_int_src(struct acpi_subtable_header * header, const unsigned long end)
unsigned int can_cpei_retarget(void)
unsigned int is_cpu_cpei_target(unsigned int cpu)
void set_cpei_target_cpu(unsigned int cpu)
unsigned int get_cpei_target_cpu(void)
static int __init acpi_parse_int_src_ovr(struct acpi_subtable_header * header, const unsigned long end)
static int __init acpi_parse_nmi_src(struct acpi_subtable_header * header, const unsigned long end)
static void __init acpi_madt_oem_check(char *oem_id, char *oem_table_id)
static int __init acpi_parse_madt(struct acpi_table_header *table)
static int __init get_processor_proximity_domain(struct acpi_srat_cpu_affinity *pa)
static int __init get_memory_proximity_domain(struct acpi_srat_mem_affinity *ma)
void __init acpi_numa_slit_init(struct acpi_table_slit *slit)
void __init acpi_numa_processor_affinity_init(struct acpi_srat_cpu_affinity *pa)
int __init acpi_numa_memory_affinity_init(struct acpi_srat_mem_affinity *ma)
void __init acpi_numa_fixup(void)
int acpi_register_gsi(struct device *dev, u32 gsi, int triggering, int polarity)
void acpi_unregister_gsi(u32 gsi)
static int __init acpi_parse_fadt(struct acpi_table_header *table)
int __init early_acpi_boot_init(void)
int __init acpi_boot_init(void)
int acpi_gsi_to_irq(u32 gsi, unsigned int *irq)
int acpi_isa_irq_to_gsi(unsigned isa_irq, u32 *gsi)
int acpi_map_cpu2node(acpi_handle handle, int cpu, int physid)
static __init int setup_additional_cpus(char *s)
__init void prefill_possible_map(void)
static int _acpi_map_lsapic(acpi_handle handle, int physid, int *pcpu)
int __ref acpi_map_cpu(acpi_handle handle, phys_cpuid_t physid, u32 acpi_id, int *pcpu)
int acpi_unmap_cpu(int cpu)
static acpi_status acpi_map_iosapic(acpi_handle handle, u32 depth, void *context, void **ret)
static int __init acpi_map_iosapics (void)
int __ref acpi_register_ioapic(acpi_handle handle, u64 phys_addr, u32 gsi_base)
int acpi_unregister_ioapic(acpi_handle handle, u32 gsi_base)
   9 void
   7 struct acpi_subtable_header * header
   7 const unsigned long end
   6 acpi_handle handle
   3 u32 gsi
   2 unsigned long size
   2 unsigned int cpu
   2 u32 gsi_base
   2 struct acpi_table_header *table
   2 struct acpi_srat_mem_affinity *ma
   2 struct acpi_srat_cpu_affinity *pa
   2 int physid
   2 int cpu
   2 int *pcpu
   1 void __iomem *map
   1 void *context
   1 void **ret
   1 unsigned long phys
   1 unsigned isa_irq
   1 unsigned int *irq
   1 u64 phys_addr
   1 u32 int_type
   1 u32 depth
   1 u32 acpi_id
   1 u32 *gsi
   1 struct device *dev
   1 struct acpi_table_slit *slit
   1 phys_cpuid_t physid
   1 int triggering
   1 int polarity
   1 char *s
   1 char *oem_table_id
   1 char *oem_id
   1 acpi_unregister_gsi
   1 acpi_register_gsi
