
\n
void __init early_init_dt_scan_chosen_arch(unsigned long node)
void __init early_init_dt_add_memory_arch(u64 base, u64 size)
void __init add_dtb(u64 data)
static int __init add_bus_probe(void)
struct device_node *pcibios_get_phb_of_node(struct pci_bus *bus)
static int x86_of_pci_irq_enable(struct pci_dev *dev)
static void x86_of_pci_irq_disable(struct pci_dev *dev)
void x86_of_pci_init(void)
static void __init dtb_setup_hpet(void)
static void __init dtb_cpu_setup(void)
static void __init dtb_lapic_setup(void)
static struct of_ioapic_type of_ioapic_type[] = static int dt_irqdomain_alloc(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs, void *arg)
static void __init dtb_add_ioapic(struct device_node *dn)
static void __init dtb_ioapic_setup(void)
static void __init dtb_apic_setup(void)
static void __init x86_flattree_get_config(void)
void __init x86_dtb_init(void)
\n
      9 void
      2 struct pci_dev *dev
      1 void *arg
      1 unsigned long node
      1 unsigned int virq
      1 unsigned int nr_irqs
      1 u64 size
      1 u64 data
      1 u64 base
      1 struct pci_bus *bus
      1 struct irq_domain *domain
      1 struct device_node *dn
