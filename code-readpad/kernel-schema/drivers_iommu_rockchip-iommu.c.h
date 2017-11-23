
static inline void rk_table_flush(struct rk_iommu_domain *dom, dma_addr_t dma, unsigned int count)
static struct rk_iommu_domain *to_rk_domain(struct iommu_domain *dom)
static inline phys_addr_t rk_dte_pt_address(u32 dte)
static inline bool rk_dte_is_pt_valid(u32 dte)
static inline u32 rk_mk_dte(dma_addr_t pt_dma)
static inline phys_addr_t rk_pte_page_address(u32 pte)
static inline bool rk_pte_is_page_valid(u32 pte)
static u32 rk_mk_pte(phys_addr_t page, int prot)
static u32 rk_mk_pte_invalid(u32 pte)
static u32 rk_iova_dte_index(dma_addr_t iova)
static u32 rk_iova_pte_index(dma_addr_t iova)
static u32 rk_iova_page_offset(dma_addr_t iova)
static u32 rk_iommu_read(void __iomem *base, u32 offset)
static void rk_iommu_write(void __iomem *base, u32 offset, u32 value)
static void rk_iommu_command(struct rk_iommu *iommu, u32 command)
static void rk_iommu_base_command(void __iomem *base, u32 command)
static void rk_iommu_base_command(void __iomem *base, u32 command)
writel(command, base + RK_MMU_COMMAND)
; } static void rk_iommu_zap_lines(struct rk_iommu *iommu, dma_addr_t iova_start, size_t size)
static bool rk_iommu_is_stall_active(struct rk_iommu *iommu)
static bool rk_iommu_is_paging_enabled(struct rk_iommu *iommu)
static bool rk_iommu_is_reset_done(struct rk_iommu *iommu)
static int rk_iommu_enable_stall(struct rk_iommu *iommu)
static int rk_iommu_disable_stall(struct rk_iommu *iommu)
static int rk_iommu_enable_paging(struct rk_iommu *iommu)
static int rk_iommu_disable_paging(struct rk_iommu *iommu)
static int rk_iommu_force_reset(struct rk_iommu *iommu)
static void log_iova(struct rk_iommu *iommu, int index, dma_addr_t iova)
static irqreturn_t rk_iommu_irq(int irq, void *dev_id)
static phys_addr_t rk_iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
static void rk_iommu_zap_iova(struct rk_iommu_domain *rk_domain, dma_addr_t iova, size_t size)
static void rk_iommu_zap_iova_first_last(struct rk_iommu_domain *rk_domain, dma_addr_t iova, size_t size)
static u32 *rk_dte_get_page_table(struct rk_iommu_domain *rk_domain, dma_addr_t iova)
static size_t rk_iommu_unmap_iova(struct rk_iommu_domain *rk_domain, u32 *pte_addr, dma_addr_t pte_dma, size_t size)
static int rk_iommu_map_iova(struct rk_iommu_domain *rk_domain, u32 *pte_addr, dma_addr_t pte_dma, dma_addr_t iova, phys_addr_t paddr, size_t size, int prot)
static int rk_iommu_map(struct iommu_domain *domain, unsigned long _iova, phys_addr_t paddr, size_t size, int prot)
static size_t rk_iommu_unmap(struct iommu_domain *domain, unsigned long _iova, size_t size)
static struct rk_iommu *rk_iommu_from_dev(struct device *dev)
static void rk_iommu_disable(struct rk_iommu *iommu)
static int rk_iommu_enable(struct rk_iommu *iommu)
static void rk_iommu_detach_device(struct iommu_domain *domain, struct device *dev)
static int rk_iommu_attach_device(struct iommu_domain *domain, struct device *dev)
static struct iommu_domain *rk_iommu_domain_alloc(unsigned type)
static void rk_iommu_domain_free(struct iommu_domain *domain)
static int rk_iommu_add_device(struct device *dev)
static void rk_iommu_remove_device(struct device *dev)
static struct iommu_group *rk_iommu_device_group(struct device *dev)
static int rk_iommu_of_xlate(struct device *dev, struct of_phandle_args *args)
static int rk_iommu_probe(struct platform_device *pdev)
static void rk_iommu_shutdown(struct platform_device *pdev)
static int __maybe_unused rk_iommu_suspend(struct device *dev)
static int __maybe_unused rk_iommu_resume(struct device *dev)
static int __init rk_iommu_init(void)
  13 struct rk_iommu *iommu
   9 struct device *dev
   9 dma_addr_t iova
   7 size_t size
   6 struct iommu_domain *domain
   5 struct rk_iommu_domain *rk_domain
   4 void __iomem *base
   3 u32 pte
   3 u32 command
   3 int prot
   2 unsigned long _iova
   2 u32 offset
   2 u32 dte
   2 u32 *pte_addr
   2 struct platform_device *pdev
   2 phys_addr_t paddr
   2 dma_addr_t pte_dma
   1 void *dev_id
   1 void
   1 unsigned type
   1 unsigned int count
   1 u32 value
   1 struct rk_iommu_domain *dom
   1 struct of_phandle_args *args
   1 struct iommu_domain *dom
   1 phys_addr_t page
   1 int irq
   1 int index
   1 dma_addr_t pt_dma
   1 dma_addr_t iova_start
   1 dma_addr_t dma
   1 command
   1 base + RK_MMU_COMMAND
