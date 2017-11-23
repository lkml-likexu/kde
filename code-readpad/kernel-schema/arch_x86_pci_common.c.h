
EXPORT_SYMBOL_GPL(add_dma_domain);
EXPORT_SYMBOL_GPL(del_dma_domain);
int raw_pci_read(unsigned int domain, unsigned int bus, unsigned int devfn, int reg, int len, u32 *val)
int raw_pci_write(unsigned int domain, unsigned int bus, unsigned int devfn, int reg, int len, u32 val)
static int pci_read(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 *value)
static int pci_write(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 value)
static int __init can_skip_ioresource_align(const struct dmi_system_id *d)
void __init dmi_check_skip_isa_align(void)
static void pcibios_fixup_device_resources(struct pci_dev *dev)
void pcibios_fixup_bus(struct pci_bus *b)
void pcibios_add_bus(struct pci_bus *bus)
void pcibios_remove_bus(struct pci_bus *bus)
static int __init set_bf_sort(const struct dmi_system_id *d)
static void __init read_dmi_type_b1(const struct dmi_header *dm, void *private_data)
static int __init find_sort_method(const struct dmi_system_id *d)
static int __init assign_all_busses(const struct dmi_system_id *d)
static int __init set_scan_all(const struct dmi_system_id *d)
void __init dmi_check_pciprobe(void)
void pcibios_scan_root(int busnum)
void __init pcibios_set_cache_line_size(void)
int __init pcibios_init(void)
char *__init pcibios_setup(char *str)
unsigned int pcibios_assign_all_busses(void)
void add_dma_domain(struct dma_domain *domain)
void del_dma_domain(struct dma_domain *domain)
static void set_dma_domain_ops(struct pci_dev *pdev)
static void set_dev_domain_options(struct pci_dev *pdev)
int pcibios_add_device(struct pci_dev *dev)
int pcibios_enable_device(struct pci_dev *dev, int mask)
void pcibios_disable_device (struct pci_dev *dev)
void pcibios_release_device(struct pci_dev *dev)
int pci_ext_cfg_avail(void)
   6 void
   5 struct pci_dev *dev
   5 const struct dmi_system_id *d
   4 unsigned int devfn
   4 struct pci_bus *bus
   2 unsigned int domain
   2 unsigned int bus
   2 struct pci_dev *pdev
   2 struct dma_domain *domain
   2 int where
   2 int size
   2 int reg
   2 int len
   1 void *private_data
   1 u32 value
   1 u32 val
   1 u32 *value
   1 u32 *val
   1 struct pci_bus *b
   1 int mask
   1 int busnum
   1 del_dma_domain
   1 const struct dmi_header *dm
   1 char *str
   1 add_dma_domain
