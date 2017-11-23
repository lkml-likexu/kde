
static int __init parse_acpi(char *arg)
static int __init dt_scan_depth1_nodes(unsigned long node, const char *uname, int depth, void *data)
void __init __iomem *__acpi_map_table(unsigned long phys, unsigned long size)
void __init __acpi_unmap_table(void __iomem *map, unsigned long size)
bool __init acpi_psci_present(void)
bool acpi_psci_use_hvc(void)
static int __init acpi_fadt_sanity_check(void)
void __init acpi_boot_table_init(void)
pgprot_t __acpi_get_mem_attribute(phys_addr_t addr)
   4 void
   2 unsigned long size
   1 void __iomem *map
   1 void *data
   1 unsigned long phys
   1 unsigned long node
   1 phys_addr_t addr
   1 int depth
   1 const char *uname
   1 char *arg
