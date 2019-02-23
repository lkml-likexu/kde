
EXPORT_SYMBOL_GPL(acpi_gsi_to_irq);
EXPORT_SYMBOL_GPL(acpi_register_gsi);
EXPORT_SYMBOL_GPL(acpi_unregister_gsi);
\n
void __init __iomem *__acpi_map_table(unsigned long phys, unsigned long size)
void __init __acpi_unmap_table(void __iomem *map, unsigned long size)
static int __init acpi_parse_madt(struct acpi_table_header *table)
static int acpi_register_lapic(int id, u32 acpiid, u8 enabled)
static int __init acpi_parse_x2apic(struct acpi_subtable_header *header, const unsigned long end)
static int __init acpi_parse_lapic(struct acpi_subtable_header * header, const unsigned long end)
static int __init acpi_parse_sapic(struct acpi_subtable_header *header, const unsigned long end)
static int __init acpi_parse_lapic_addr_ovr(struct acpi_subtable_header * header, const unsigned long end)
static int __init acpi_parse_x2apic_nmi(struct acpi_subtable_header *header, const unsigned long end)
static int __init acpi_parse_lapic_nmi(struct acpi_subtable_header * header, const unsigned long end)
static void __init mp_override_legacy_irq(u8 bus_irq, u8 polarity, u8 trigger, u32 gsi)
static int mp_config_acpi_gsi(struct device *dev, u32 gsi, int trigger, int polarity)
static int __init mp_register_ioapic_irq(u8 bus_irq, u8 polarity, u8 trigger, u32 gsi)
static int __init acpi_parse_ioapic(struct acpi_subtable_header * header, const unsigned long end)
static void __init acpi_sci_ioapic_setup(u8 bus_irq, u16 polarity, u16 trigger, u32 gsi)
static int __init acpi_parse_int_src_ovr(struct acpi_subtable_header * header, const unsigned long end)
static int __init acpi_parse_nmi_src(struct acpi_subtable_header * header, const unsigned long end)
void __init acpi_pic_sci_set_trigger(unsigned int irq, u16 trigger)
int acpi_gsi_to_irq(u32 gsi, unsigned int *irqp)
int acpi_isa_irq_to_gsi(unsigned isa_irq, u32 *gsi)
static int acpi_register_gsi_pic(struct device *dev, u32 gsi, int trigger, int polarity)
static int acpi_register_gsi_ioapic(struct device *dev, u32 gsi, int trigger, int polarity)
static void acpi_unregister_gsi_ioapic(u32 gsi)
int acpi_register_gsi(struct device *dev, u32 gsi, int trigger, int polarity)
void acpi_unregister_gsi(u32 gsi)
static void __init acpi_set_irq_model_ioapic(void)
static int acpi_map_cpu2node(acpi_handle handle, int cpu, int physid)
int acpi_map_cpu(acpi_handle handle, phys_cpuid_t physid, u32 acpi_id, int *pcpu)
int acpi_unmap_cpu(int cpu)
int acpi_register_ioapic(acpi_handle handle, u64 phys_addr, u32 gsi_base)
int acpi_unregister_ioapic(acpi_handle handle, u32 gsi_base)
int acpi_ioapic_registered(acpi_handle handle, u32 gsi_base)
static int __init acpi_parse_sbf(struct acpi_table_header *table)
static int __init acpi_parse_hpet(struct acpi_table_header *table)
static __init int hpet_insert_resource(void)
static int __init acpi_parse_fadt(struct acpi_table_header *table)
static int __init early_acpi_parse_madt_lapic_addr_ovr(void)
static int __init acpi_parse_madt_lapic_entries(void)
static void __init mp_config_acpi_legacy_irqs(void)
static int __init acpi_parse_madt_ioapic_entries(void)
return 0; } static inline int acpi_parse_madt_ioapic_entries(void)
static void __init early_acpi_process_madt(void)
static void __init acpi_process_madt(void)
static int __init disable_acpi_irq(const struct dmi_system_id *d)
static int __init disable_acpi_pci(const struct dmi_system_id *d)
static int __init dmi_disable_acpi(const struct dmi_system_id *d)
static int __init dmi_ignore_irq0_timer_override(const struct dmi_system_id *d)
void __init acpi_generic_reduced_hw_init(void)
static void __init acpi_reduced_hw_init(void)
void __init acpi_boot_table_init(void)
int __init early_acpi_boot_init(void)
int __init acpi_boot_init(void)
static int __init parse_acpi(char *arg)
static int __init parse_pci(char *arg)
int __init acpi_mps_check(void)
static int __init parse_acpi_skip_timer_override(char *arg)
static int __init parse_acpi_use_timer_override(char *arg)
static int __init setup_acpi_sci(char *s)
int __acpi_acquire_global_lock(unsigned int *lock)
int __acpi_release_global_lock(unsigned int *lock)
void __init arch_reserve_mem_area(acpi_physical_address addr, size_t size)
u64 x86_default_get_root_pointer(void)
\n
     16 void
     10 u32 gsi
      9 const unsigned long end
      6 struct acpi_subtable_header * header
      5 acpi_handle handle
      4 struct device *dev
      4 struct acpi_table_header *table
      4 int trigger
      4 int polarity
      4 const struct dmi_system_id *d
      4 char *arg
      3 u8 bus_irq
      3 u32 gsi_base
      3 struct acpi_subtable_header *header
      2 unsigned long size
      2 unsigned int *lock
      2 u8 trigger
      2 u8 polarity
      2 u16 trigger
      2 int cpu
      1 void __iomem *map
      1 unsigned long phys
      1 unsigned isa_irq
      1 unsigned int *irqp
      1 unsigned int irq
      1 u8 enabled
      1 u64 phys_addr
      1 u32 *gsi
      1 u32 acpi_id
      1 u32 acpiid
      1 u16 polarity
      1 size_t size
      1 phys_cpuid_t physid
      1 int physid
      1 int *pcpu
      1 int id
      1 char *s
      1 acpi_unregister_gsi
      1 acpi_register_gsi
      1 acpi_physical_address addr
      1 acpi_gsi_to_irq
