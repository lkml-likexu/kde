
\n
static inline char __iomem *pci_dev_base(unsigned int seg, unsigned int bus, unsigned int devfn)
static int pci_mmcfg_read_numachip(unsigned int seg, unsigned int bus, unsigned int devfn, int reg, int len, u32 *value)
static int pci_mmcfg_write_numachip(unsigned int seg, unsigned int bus, unsigned int devfn, int reg, int len, u32 value)
int __init pci_numachip_init(void)
\n
      3 unsigned int seg
      3 unsigned int devfn
      3 unsigned int bus
      2 int reg
      2 int len
      1 void
      1 u32 *value
      1 u32 value
