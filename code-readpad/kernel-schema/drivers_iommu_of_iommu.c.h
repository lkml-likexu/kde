
EXPORT_SYMBOL_GPL(of_get_dma_window);
int of_get_dma_window(struct device_node *dn, const char *prefix, int index, unsigned long *busno, dma_addr_t *addr, size_t *size)
static int of_iommu_xlate(struct device *dev, struct of_phandle_args *iommu_spec)
static int of_pci_iommu_init(struct pci_dev *pdev, u16 alias, void *data)
static int of_fsl_mc_iommu_init(struct fsl_mc_device *mc_dev, struct device_node *master_np)
const struct iommu_ops *of_iommu_configure(struct device *dev, struct device_node *master_np)
   2 struct device_node *master_np
   2 struct device *dev
   1 void *data
   1 unsigned long *busno
   1 u16 alias
   1 struct pci_dev *pdev
   1 struct of_phandle_args *iommu_spec
   1 struct fsl_mc_device *mc_dev
   1 struct device_node *dn
   1 size_t *size
   1 of_get_dma_window
   1 int index
   1 dma_addr_t *addr
   1 const char *prefix
