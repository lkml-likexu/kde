
\n
static inline int iommu_dma_init(void)
static inline int iommu_get_dma_cookie(struct iommu_domain *domain)
static inline int iommu_get_msi_cookie(struct iommu_domain *domain, dma_addr_t base)
static inline void iommu_put_dma_cookie(struct iommu_domain *domain)
static inline void iommu_dma_map_msi_msg(int irq, struct msi_msg *msg)
static inline void iommu_dma_get_resv_regions(struct device *dev, struct list_head *list)
\n
      3 struct iommu_domain *domain
      1 void
      1 struct msi_msg *msg
      1 struct list_head *list
      1 struct device *dev
      1 int irq
      1 dma_addr_t base
