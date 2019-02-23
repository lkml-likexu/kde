
\n
static struct mtk_iommu_data *mtk_iommu_get_m4u_data(void)
static struct mtk_iommu_domain *to_mtk_domain(struct iommu_domain *dom)
static void mtk_iommu_tlb_flush_all(void *cookie)
static void mtk_iommu_tlb_add_flush_nosync(unsigned long iova, size_t size, size_t granule, bool leaf, void *cookie)
static void mtk_iommu_tlb_sync(void *cookie)
static irqreturn_t mtk_iommu_isr(int irq, void *dev_id)
static void mtk_iommu_config(struct mtk_iommu_data *data, struct device *dev, bool enable)
static int mtk_iommu_domain_finalise(struct mtk_iommu_domain *dom)
static struct iommu_domain *mtk_iommu_domain_alloc(unsigned type)
static void mtk_iommu_domain_free(struct iommu_domain *domain)
static int mtk_iommu_attach_device(struct iommu_domain *domain, struct device *dev)
static void mtk_iommu_detach_device(struct iommu_domain *domain, struct device *dev)
static int mtk_iommu_map(struct iommu_domain *domain, unsigned long iova, phys_addr_t paddr, size_t size, int prot)
static size_t mtk_iommu_unmap(struct iommu_domain *domain, unsigned long iova, size_t size)
static void mtk_iommu_iotlb_sync(struct iommu_domain *domain)
static phys_addr_t mtk_iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
static int mtk_iommu_add_device(struct device *dev)
static void mtk_iommu_remove_device(struct device *dev)
static struct iommu_group *mtk_iommu_device_group(struct device *dev)
static int mtk_iommu_of_xlate(struct device *dev, struct of_phandle_args *args)
static int mtk_iommu_hw_init(const struct mtk_iommu_data *data)
static int mtk_iommu_probe(struct platform_device *pdev)
static int mtk_iommu_remove(struct platform_device *pdev)
static int __maybe_unused mtk_iommu_suspend(struct device *dev)
static int __maybe_unused mtk_iommu_resume(struct device *dev)
static int __init mtk_iommu_init(void)
\n
      9 struct device *dev
      7 struct iommu_domain *domain
      3 void *cookie
      3 unsigned long iova
      3 size_t size
      2 void
      2 struct platform_device *pdev
      1 void *dev_id
      1 unsigned type
      1 struct of_phandle_args *args
      1 struct mtk_iommu_domain *dom
      1 struct mtk_iommu_data *data
      1 struct iommu_domain *dom
      1 size_t granule
      1 phys_addr_t paddr
      1 int prot
      1 int irq
      1 dma_addr_t iova
      1 const struct mtk_iommu_data *data
      1 bool leaf
      1 bool enable
