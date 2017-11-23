
static int pci_mcfg_quirk_matches(struct mcfg_fixup *f, u16 segment, struct resource *bus_range)
static void pci_mcfg_apply_quirks(struct acpi_pci_root *root, struct resource *cfgres, struct pci_ecam_ops **ecam_ops)
int pci_mcfg_lookup(struct acpi_pci_root *root, struct resource *cfgres, struct pci_ecam_ops **ecam_ops)
static __init int pci_mcfg_parse(struct acpi_table_header *header)
void __init pci_mmcfg_late_init(void)
   2 struct resource *cfgres
   2 struct pci_ecam_ops **ecam_ops
   2 struct acpi_pci_root *root
   1 void
   1 u16 segment
   1 struct resource *bus_range
   1 struct mcfg_fixup *f
   1 struct acpi_table_header *header
