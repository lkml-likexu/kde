
\n
static inline struct uio_pci_generic_dev * to_uio_pci_generic_dev(struct uio_info *info)
static irqreturn_t irqhandler(int irq, struct uio_info *info)
static int probe(struct pci_dev *pdev, const struct pci_device_id *id)
static void remove(struct pci_dev *pdev)
\n
      2 struct uio_info *info
      2 struct pci_dev *pdev
      1 int irq
      1 const struct pci_device_id *id
