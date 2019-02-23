
\n
static struct msm_priv *to_msm_priv(struct iommu_domain *dom)
static int __enable_clocks(struct msm_iommu_dev *iommu)
static void __disable_clocks(struct msm_iommu_dev *iommu)
static void msm_iommu_reset(void __iomem *base, int ncb)
static void __flush_iotlb(void *cookie)
static void __flush_iotlb_range(unsigned long iova, size_t size, size_t granule, bool leaf, void *cookie)
static void __flush_iotlb_sync(void *cookie)
static int msm_iommu_alloc_ctx(unsigned long *map, int start, int end)
static void msm_iommu_free_ctx(unsigned long *map, int idx)
static void config_mids(struct msm_iommu_dev *iommu, struct msm_iommu_ctx_dev *master)
static void __reset_context(void __iomem *base, int ctx)
static void __program_context(void __iomem *base, int ctx, struct msm_priv *priv)
static struct iommu_domain *msm_iommu_domain_alloc(unsigned type)
static void msm_iommu_domain_free(struct iommu_domain *domain)
static int msm_iommu_domain_config(struct msm_priv *priv)
static struct msm_iommu_dev *find_iommu_for_dev(struct device *dev)
static int msm_iommu_add_device(struct device *dev)
static void msm_iommu_remove_device(struct device *dev)
static int msm_iommu_attach_dev(struct iommu_domain *domain, struct device *dev)
static void msm_iommu_detach_dev(struct iommu_domain *domain, struct device *dev)
static int msm_iommu_map(struct iommu_domain *domain, unsigned long iova, phys_addr_t pa, size_t len, int prot)
static size_t msm_iommu_unmap(struct iommu_domain *domain, unsigned long iova, size_t len)
static phys_addr_t msm_iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t va)
static bool msm_iommu_capable(enum iommu_cap cap)
static void print_ctx_regs(void __iomem *base, int ctx)
static void insert_iommu_master(struct device *dev, struct msm_iommu_dev **iommu, struct of_phandle_args *spec)
static int qcom_iommu_of_xlate(struct device *dev, struct of_phandle_args *spec)
irqreturn_t msm_iommu_fault_handler(int irq, void *dev_id)
static int msm_iommu_probe(struct platform_device *pdev)
static int msm_iommu_remove(struct platform_device *pdev)
static int __init msm_iommu_driver_init(void)
\n
      7 struct device *dev
      6 struct iommu_domain *domain
      4 void __iomem *base
      3 void *cookie
      3 unsigned long iova
      3 struct msm_iommu_dev *iommu
      3 int ctx
      2 unsigned long *map
      2 struct platform_device *pdev
      2 struct of_phandle_args *spec
      2 struct msm_priv *priv
      2 size_t len
      1 void *dev_id
      1 void
      1 unsigned type
      1 struct msm_iommu_dev **iommu
      1 struct msm_iommu_ctx_dev *master
      1 struct iommu_domain *dom
      1 size_t size
      1 size_t granule
      1 phys_addr_t pa
      1 int start
      1 int prot
      1 int ncb
      1 int irq
      1 int idx
      1 int end
      1 enum iommu_cap cap
      1 dma_addr_t va
      1 bool leaf
