
\n
static inline int of_get_dma_window(struct device_node *dn, const char *prefix, int index, unsigned long *busno, dma_addr_t *addr, size_t *size)
static inline const struct iommu_ops *of_iommu_configure(struct device *dev, struct device_node *master_np)
\n
      1 unsigned long *busno
      1 struct device_node *master_np
      1 struct device_node *dn
      1 struct device *dev
      1 size_t *size
      1 int index
      1 dma_addr_t *addr
      1 const char *prefix
