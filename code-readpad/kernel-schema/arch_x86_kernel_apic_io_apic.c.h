
\n
int mpc_ioapic_id(int ioapic_idx)
unsigned int mpc_ioapic_addr(int ioapic_idx)
static inline struct mp_ioapic_gsi *mp_ioapic_gsi_routing(int ioapic_idx)
static inline int mp_ioapic_pin_count(int ioapic)
static inline u32 mp_pin_to_gsi(int ioapic, int pin)
static inline bool mp_is_legacy_irq(int irq)
static inline int mp_init_irq_at_boot(int ioapic, int irq)
static inline struct irq_domain *mp_ioapic_irqdomain(int ioapic)
void disable_ioapic_support(void)
static int __init parse_noapic(char *str)
void mp_save_irq(struct mpc_intsrc *m)
static void alloc_ioapic_saved_registers(int idx)
static void free_ioapic_saved_registers(int idx)
int __init arch_early_ioapic_init(void)
static __attribute_const__ struct io_apic __iomem *io_apic_base(int idx)
static inline void io_apic_eoi(unsigned int apic, unsigned int vector)
unsigned int native_io_apic_read(unsigned int apic, unsigned int reg)
static void io_apic_write(unsigned int apic, unsigned int reg, unsigned int value)
static struct IO_APIC_route_entry __ioapic_read_entry(int apic, int pin)
static struct IO_APIC_route_entry ioapic_read_entry(int apic, int pin)
static void __ioapic_write_entry(int apic, int pin, struct IO_APIC_route_entry e)
static void ioapic_write_entry(int apic, int pin, struct IO_APIC_route_entry e)
static void ioapic_mask_entry(int apic, int pin)
static int __add_pin_to_irq_node(struct mp_chip_data *data, int node, int apic, int pin)
static void __remove_pin_from_irq(struct mp_chip_data *data, int apic, int pin)
static void add_pin_to_irq_node(struct mp_chip_data *data, int node, int apic, int pin)
static void __init replace_pin_at_irq_node(struct mp_chip_data *data, int node, int oldapic, int oldpin, int newapic, int newpin)
static void io_apic_modify_irq(struct mp_chip_data *data, int mask_and, int mask_or, void (*final)
(struct irq_pin_list *entry)
)
static void io_apic_sync(struct irq_pin_list *entry)
static void mask_ioapic_irq(struct irq_data *irq_data)
static void __unmask_ioapic(struct mp_chip_data *data)
static void unmask_ioapic_irq(struct irq_data *irq_data)
static void __eoi_ioapic_pin(int apic, int pin, int vector)
static void eoi_ioapic_pin(int vector, struct mp_chip_data *data)
static void clear_IO_APIC_pin(unsigned int apic, unsigned int pin)
void clear_IO_APIC (void)
static int __init ioapic_pirq_setup(char *str)
int save_ioapic_entries(void)
void mask_ioapic_entries(void)
int restore_ioapic_entries(void)
static int find_irq_entry(int ioapic_idx, int pin, int type)
static int __init find_isa_irq_pin(int irq, int type)
static int __init find_isa_irq_apic(int irq, int type)
static int EISA_ELCR(unsigned int irq)
static int irq_polarity(int idx)
static int eisa_irq_trigger(int idx, int bus, int trigger)
static int eisa_irq_trigger(int idx, int bus, int trigger)
case MP_BUS_PCI:case MP_BUS_ISA: return trigger;case MP_BUS_EISA: return default_EISA_trigger(idx)
;}pr_warn("IOAPIC: Invalid srcbus: %d defaulting to level\n", bus)
;return IOAPIC_LEVEL; } static inline int eisa_irq_trigger(int idx, int bus, int trigger)
static int irq_trigger(int idx)
void ioapic_set_alloc_attr(struct irq_alloc_info *info, int node, int trigger, int polarity)
static void ioapic_copy_alloc_attr(struct irq_alloc_info *dst, struct irq_alloc_info *src, u32 gsi, int ioapic_idx, int pin)
static int ioapic_alloc_attr_node(struct irq_alloc_info *info)
static void mp_register_handler(unsigned int irq, unsigned long trigger)
static bool mp_check_pin_attr(int irq, struct irq_alloc_info *info)
static int alloc_irq_from_domain(struct irq_domain *domain, int ioapic, u32 gsi, struct irq_alloc_info *info)
static int alloc_isa_irq_from_domain(struct irq_domain *domain, int irq, int ioapic, int pin, struct irq_alloc_info *info)
static int mp_map_pin_to_irq(u32 gsi, int idx, int ioapic, int pin, unsigned int flags, struct irq_alloc_info *info)
static int pin_2_irq(int idx, int ioapic, int pin, unsigned int flags)
int mp_map_gsi_to_irq(u32 gsi, unsigned int flags, struct irq_alloc_info *info)
void mp_unmap_irq(int irq)
int IO_APIC_get_PCI_irq_vector(int bus, int slot, int pin)
static void __init setup_IO_APIC_irqs(void)
void ioapic_zap_locks(void)
static void io_apic_print_entries(unsigned int apic, unsigned int nr_entries)
static void __init print_IO_APIC(int ioapic_idx)
void __init print_IO_APICs(void)
void __init enable_IO_APIC(void)
void native_restore_boot_irq_mode(void)
void restore_boot_irq_mode(void)
void __init setup_ioapic_ids_from_mpc_nocheck(void)
void __init setup_ioapic_ids_from_mpc(void)
static int __init notimercheck(char *s)
static void __init delay_with_tsc(void)
static void __init delay_without_tsc(void)
static int __init timer_irq_works(void)
static unsigned int startup_ioapic_irq(struct irq_data *data)
static bool io_apic_level_ack_pending(struct mp_chip_data *data)
static inline bool ioapic_irqd_mask(struct irq_data *data)
static inline void ioapic_irqd_unmask(struct irq_data *data, bool masked)
static inline void ioapic_irqd_unmask(struct irq_data *data, bool masked)
if (!io_apic_level_ack_pending(data->chip_data)
)
irq_move_masked_irq(data)
; unmask_ioapic_irq(data)
;} } static inline bool ioapic_irqd_mask(struct irq_data *data)
static inline void ioapic_irqd_unmask(struct irq_data *data, bool masked)
if (!io_apic_level_ack_pending(data->chip_data)
)
irq_move_masked_irq(data)
; unmask_ioapic_irq(data)
;} } static inline bool ioapic_irqd_mask(struct irq_data *data)
return false; } static inline void ioapic_irqd_unmask(struct irq_data *data, bool masked)
static void ioapic_ack_level(struct irq_data *irq_data)
static void ioapic_ir_ack_level(struct irq_data *irq_data)
static void ioapic_configure_entry(struct irq_data *irqd)
static int ioapic_set_affinity(struct irq_data *irq_data, const struct cpumask *mask, bool force)
static inline void init_IO_APIC_traps(void)
static void mask_lapic_irq(struct irq_data *data)
static void unmask_lapic_irq(struct irq_data *data)
static void ack_lapic_irq(struct irq_data *data)
static void lapic_register_intr(int irq)
static inline void __init unlock_ExtINT_logic(void)
static int disable_timer_pin_1 __initdata;static int __init disable_timer_pin_setup(char *arg)
static int mp_alloc_timer_irq(int ioapic, int pin)
static inline void __init check_timer(void)
static int mp_irqdomain_create(int ioapic)
static void ioapic_destroy_irqdomain(int idx)
void __init setup_IO_APIC(void)
static void resume_ioapic_id(int ioapic_idx)
static void ioapic_resume(void)
static int __init ioapic_init_ops(void)
static int io_apic_get_redir_entries(int ioapic)
unsigned int arch_dynirq_lower_bound(unsigned int from)
static int io_apic_get_unique_id(int ioapic, int apic_id)
static u8 io_apic_unique_id(int idx, u8 id)
static u8 io_apic_unique_id(int idx, u8 id)
if ((boot_cpu_data.x86_vendor == X86_VENDOR_INTEL)
&&!APIC_XAPIC(boot_cpu_apic_version)
)
return io_apic_get_unique_id(idx, id)
;else return id; } static u8 io_apic_unique_id(int idx, u8 id)
static int io_apic_get_version(int ioapic)
int acpi_get_override_irq(u32 gsi, int *trigger, int *polarity)
static struct resource * __init ioapic_setup_resources(void)
void __init io_apic_init_mappings(void)
void __init ioapic_insert_resources(void)
int mp_find_ioapic(u32 gsi)
int mp_find_ioapic_pin(int ioapic, u32 gsi)
static int bad_ioapic_register(int idx)
static int find_free_ioapic_entry(void)
int mp_register_ioapic(int id, u32 address, u32 gsi_base, struct ioapic_domain_cfg *cfg)
int mp_unregister_ioapic(u32 gsi_base)
int mp_ioapic_registered(u32 gsi_base)
static void mp_irqdomain_get_attr(u32 gsi, struct mp_chip_data *data, struct irq_alloc_info *info)
static void mp_setup_entry(struct irq_cfg *cfg, struct mp_chip_data *data, struct IO_APIC_route_entry *entry)
int mp_irqdomain_alloc(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs, void *arg)
void mp_irqdomain_free(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs)
int mp_irqdomain_activate(struct irq_domain *domain, struct irq_data *irq_data, bool reserve)
void mp_irqdomain_deactivate(struct irq_domain *domain, struct irq_data *irq_data)
int mp_irqdomain_ioapic_idx(struct irq_domain *domain)
\n
     27 void
     17 int pin
     15 int idx
     14 int ioapic
     11 struct irq_data *data
     10 struct mp_chip_data *data
      9 int apic
      8 u32 gsi
      8 struct irq_alloc_info *info
      8 int irq
      7 struct irq_domain *domain
      7 struct irq_data *irq_data
      7 int ioapic_idx
      5 unsigned int apic
      4 int trigger
      4 int node
      4 int bus
      4 data
      4 bool masked
      3 unsigned int flags
      3 u8 id
      3 u32 gsi_base
      3 int type
      2 unsigned int virq
      2 unsigned int reg
      2 unsigned int nr_irqs
      2 unsigned int irq
      2 struct irq_pin_list *entry
      2 struct IO_APIC_route_entry e
      2 !io_apic_level_ack_pendingdata->chip_data
      2 int vector
      2 idx
      2 char *str
      1 void *final
      1 void *arg
      1 unsigned long trigger
      1 unsigned int vector
      1 unsigned int value
      1 unsigned int pin
      1 unsigned int nr_entries
      1 unsigned int from
      1 u32 address
      1 struct mpc_intsrc *m
      1 struct irq_data *irqd
      1 struct irq_cfg *cfg
      1 struct irq_alloc_info *src
      1 struct irq_alloc_info *dst
      1 struct IO_APIC_route_entry *entry
      1 struct ioapic_domain_cfg *cfg
      1 "IOAPIC: Invalid srcbus: %d defaulting to level\n"
      1 int *trigger
      1 int slot
      1 int *polarity
      1 int polarity
      1 int oldpin
      1 int oldapic
      1 int newpin
      1 int newapic
      1 int mask_or
      1 int mask_and
      1 int id
      1 int apic_id
      1 id
      1 const struct cpumask *mask
      1 char *s
      1 char *arg
      1 bus
      1 boot_cpu_data.x86_vendor == X86_VENDOR_INTEL
      1 boot_cpu_apic_version
      1 bool reserve
      1 bool force
