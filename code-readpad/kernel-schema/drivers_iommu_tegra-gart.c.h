
\n
static struct gart_domain *to_gart_domain(struct iommu_domain *dom)
static inline void gart_set_pte(struct gart_device *gart, unsigned long offs, u32 pte)
static inline unsigned long gart_read_pte(struct gart_device *gart, unsigned long offs)
static void do_gart_setup(struct gart_device *gart, const u32 *data)
static void gart_dump_table(struct gart_device *gart)
dev_dbg(gart->dev, "%s %08lx:%08lx\n", (GART_ENTRY_PHYS_ADDR_VALID & pte)
? "v" : " ", iova, pte & GART_PAGE_MASK)
;}spin_unlock_irqrestore(&gart->pte_lock, flags)
; } static inline void gart_dump_table(struct gart_device *gart)
static inline bool gart_iova_range_valid(struct gart_device *gart, unsigned long iova, size_t bytes)
static int gart_iommu_attach_dev(struct iommu_domain *domain, struct device *dev)
static void gart_iommu_detach_dev(struct iommu_domain *domain, struct device *dev)
static struct iommu_domain *gart_iommu_domain_alloc(unsigned type)
static void gart_iommu_domain_free(struct iommu_domain *domain)
static int gart_iommu_map(struct iommu_domain *domain, unsigned long iova, phys_addr_t pa, size_t bytes, int prot)
static size_t gart_iommu_unmap(struct iommu_domain *domain, unsigned long iova, size_t bytes)
static phys_addr_t gart_iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
static bool gart_iommu_capable(enum iommu_cap cap)
static int gart_iommu_add_device(struct device *dev)
static void gart_iommu_remove_device(struct device *dev)
static int tegra_gart_suspend(struct device *dev)
static int tegra_gart_resume(struct device *dev)
static int tegra_gart_probe(struct platform_device *pdev)
static int __init tegra_gart_init(void)
\n
      6 struct iommu_domain *domain
      6 struct gart_device *gart
      6 struct device *dev
      3 unsigned long iova
      3 size_t bytes
      2 unsigned long offs
      1 void
      1 unsigned type
      1 u32 pte
      1 struct platform_device *pdev
      1 struct iommu_domain *dom
      1 "%s %08lx:%08lx\n"
      1 phys_addr_t pa
      1 int prot
      1 &gart->pte_lock
      1 GART_ENTRY_PHYS_ADDR_VALID & pte
      1 gart->dev
      1 flags
      1 enum iommu_cap cap
      1 dma_addr_t iova
      1 const u32 *data
