
\n
static struct qcom_iommu_domain *to_qcom_iommu_domain(struct iommu_domain *dom)
static struct qcom_iommu_dev * to_iommu(struct iommu_fwspec *fwspec)
static struct qcom_iommu_ctx * to_ctx(struct iommu_fwspec *fwspec, unsigned asid)
static inline void iommu_writel(struct qcom_iommu_ctx *ctx, unsigned reg, u32 val)
static inline void iommu_writeq(struct qcom_iommu_ctx *ctx, unsigned reg, u64 val)
static inline u32 iommu_readl(struct qcom_iommu_ctx *ctx, unsigned reg)
static inline u64 iommu_readq(struct qcom_iommu_ctx *ctx, unsigned reg)
static void qcom_iommu_tlb_sync(void *cookie)
static void qcom_iommu_tlb_inv_context(void *cookie)
static void qcom_iommu_tlb_inv_range_nosync(unsigned long iova, size_t size, size_t granule, bool leaf, void *cookie)
static irqreturn_t qcom_iommu_fault(int irq, void *dev)
static int qcom_iommu_init_domain(struct iommu_domain *domain, struct qcom_iommu_dev *qcom_iommu, struct iommu_fwspec *fwspec)
static struct iommu_domain *qcom_iommu_domain_alloc(unsigned type)
static void qcom_iommu_domain_free(struct iommu_domain *domain)
static int qcom_iommu_attach_dev(struct iommu_domain *domain, struct device *dev)
static void qcom_iommu_detach_dev(struct iommu_domain *domain, struct device *dev)
static int qcom_iommu_map(struct iommu_domain *domain, unsigned long iova, phys_addr_t paddr, size_t size, int prot)
static size_t qcom_iommu_unmap(struct iommu_domain *domain, unsigned long iova, size_t size)
static void qcom_iommu_iotlb_sync(struct iommu_domain *domain)
static phys_addr_t qcom_iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
static bool qcom_iommu_capable(enum iommu_cap cap)
static int qcom_iommu_add_device(struct device *dev)
static void qcom_iommu_remove_device(struct device *dev)
static int qcom_iommu_of_xlate(struct device *dev, struct of_phandle_args *args)
static int qcom_iommu_enable_clocks(struct qcom_iommu_dev *qcom_iommu)
static void qcom_iommu_disable_clocks(struct qcom_iommu_dev *qcom_iommu)
static int qcom_iommu_sec_ptbl_init(struct device *dev)
static int get_asid(const struct device_node *np)
static int qcom_iommu_ctx_probe(struct platform_device *pdev)
static int qcom_iommu_ctx_remove(struct platform_device *pdev)
static bool qcom_iommu_has_secure_context(struct qcom_iommu_dev *qcom_iommu)
static int qcom_iommu_device_probe(struct platform_device *pdev)
static int qcom_iommu_device_remove(struct platform_device *pdev)
static int __maybe_unused qcom_iommu_resume(struct device *dev)
static int __maybe_unused qcom_iommu_suspend(struct device *dev)
static int __init qcom_iommu_init(void)
\n
      8 struct iommu_domain *domain
      8 struct device *dev
      4 unsigned reg
      4 struct qcom_iommu_dev *qcom_iommu
      4 struct qcom_iommu_ctx *ctx
      4 struct platform_device *pdev
      3 void *cookie
      3 unsigned long iova
      3 struct iommu_fwspec *fwspec
      3 size_t size
      1 void *dev
      1 void
      1 unsigned type
      1 unsigned asid
      1 u64 val
      1 u32 val
      1 struct of_phandle_args *args
      1 struct iommu_domain *dom
      1 size_t granule
      1 phys_addr_t paddr
      1 int prot
      1 int irq
      1 enum iommu_cap cap
      1 dma_addr_t iova
      1 const struct device_node *np
      1 bool leaf
