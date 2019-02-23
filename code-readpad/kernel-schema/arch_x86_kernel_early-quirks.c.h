
\n
static void __init fix_hypertransport_config(int num, int slot, int func)
static void __init via_bugs(intnum, int slot, int func)
static int __init nvidia_hpet_check(struct acpi_table_header *header)
static void __init nvidia_bugs(int num, int slot, int func)
static u32 __init ati_ixp4x0_rev(int num, int slot, int func)
static void __init ati_bugs(int num, int slot, int func)
static u32 __init ati_sbx00_rev(int num, int slot, int func)
static void __init ati_bugs_contd(int num, int slot, int func)
printk(KERN_INFO "SB600 revision 0x%x\n", rev)
; printk(KERN_INFO "Ignoring ACPI timer override.\n")
; printk(KERN_INFO "If you got timer trouble ""try acpi_use_timer_override\n")
;} } static void __init ati_bugs(int num, int slot, int func)
static void __init ati_bugs_contd(int num, int slot, int func)
static void __init intel_remapping_check(int num, int slot, int func)
static resource_size_t __init i830_tseg_size(void)
static resource_size_t __init i845_tseg_size(void)
static resource_size_t __init i85x_tseg_size(void)
static resource_size_t __init i830_mem_size(void)
static resource_size_t __init i85x_mem_size(void)
static resource_size_t __init i830_stolen_base(int num, int slot, int func, resource_size_t stolen_size)
static resource_size_t __init i845_stolen_base(int num, int slot, int func, resource_size_t stolen_size)
static resource_size_t __init i85x_stolen_base(int num, int slot, int func, resource_size_t stolen_size)
static resource_size_t __init i865_stolen_base(int num, int slot, int func, resource_size_t stolen_size)
static resource_size_t __init gen3_stolen_base(int num, int slot, int func, resource_size_t stolen_size)
static resource_size_t __init gen11_stolen_base(int num, int slot, int func, resource_size_t stolen_size)
static resource_size_t __init i830_stolen_size(int num, int slot, int func)
static resource_size_t __init gen3_stolen_size(int num, int slot, int func)
static resource_size_t __init gen6_stolen_size(int num, int slot, int func)
static resource_size_t __init gen8_stolen_size(int num, int slot, int func)
static resource_size_t __init chv_stolen_size(int num, int slot, int func)
static resource_size_t __init gen9_stolen_size(int num, int slot, int func)
static void __init intel_graphics_stolen(int num, int slot, int func, const struct intel_early_ops *early_ops)
static void __init intel_graphics_quirks(int num, int slot, int func)
static void __init force_disable_hpet(int num, int slot, int func)
static void __init apple_airport_reset(int bus, int slot, int func)
static int __init check_dev_quirk(int num, int slot, int func)
static void __init early_pci_scan_bus(int bus)
void __init early_quirks(void)
\n
     27 int slot
     27 int func
     25 int num
      6 void
      6 resource_size_t stolen_size
      2 int bus
      1 struct acpi_table_header *header
      1 rev
      1 KERN_INFO "SB600 revision 0x%x\n"
      1 KERN_INFO "Ignoring ACPI timer override.\n"
      1 KERN_INFO "If you got timer trouble ""try acpi_use_timer_override\n"
      1 intnum
      1 const struct intel_early_ops *early_ops
