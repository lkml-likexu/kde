
static u32 lv1ent_offset(sysmmu_iova_t iova)
static u32 lv2ent_offset(sysmmu_iova_t iova)
static sysmmu_pte_t *section_entry(sysmmu_pte_t *pgtable, sysmmu_iova_t iova)
static sysmmu_pte_t *page_entry(sysmmu_pte_t *sent, sysmmu_iova_t iova)
static struct exynos_iommu_domain *to_exynos_domain(struct iommu_domain *dom)
static void sysmmu_unblock(struct sysmmu_drvdata *data)
static bool sysmmu_block(struct sysmmu_drvdata *data)
static void __sysmmu_tlb_invalidate(struct sysmmu_drvdata *data)
static void __sysmmu_tlb_invalidate_entry(struct sysmmu_drvdata *data, sysmmu_iova_t iova, unsigned int num_inv)
static void __sysmmu_set_ptbase(struct sysmmu_drvdata *data, phys_addr_t pgd)
static void __sysmmu_enable_clocks(struct sysmmu_drvdata *data)
static void __sysmmu_disable_clocks(struct sysmmu_drvdata *data)
static void __sysmmu_get_version(struct sysmmu_drvdata *data)
static void show_fault_information(struct sysmmu_drvdata *data, const struct sysmmu_fault_info *finfo, sysmmu_iova_t fault_addr)
static irqreturn_t exynos_sysmmu_irq(int irq, void *dev_id)
static void __sysmmu_disable(struct sysmmu_drvdata *data)
static void __sysmmu_init_config(struct sysmmu_drvdata *data)
static void __sysmmu_enable(struct sysmmu_drvdata *data)
static void sysmmu_tlb_invalidate_flpdcache(struct sysmmu_drvdata *data, sysmmu_iova_t iova)
static void sysmmu_tlb_invalidate_entry(struct sysmmu_drvdata *data, sysmmu_iova_t iova, size_t size)
static int __init exynos_sysmmu_probe(struct platform_device *pdev)
static int __maybe_unused exynos_sysmmu_suspend(struct device *dev)
static int __maybe_unused exynos_sysmmu_resume(struct device *dev)
static inline void update_pte(sysmmu_pte_t *ent, sysmmu_pte_t val)
static struct iommu_domain *exynos_iommu_domain_alloc(unsigned type)
static void exynos_iommu_domain_free(struct iommu_domain *iommu_domain)
static void exynos_iommu_detach_device(struct iommu_domain *iommu_domain, struct device *dev)
static int exynos_iommu_attach_device(struct iommu_domain *iommu_domain, struct device *dev)
static sysmmu_pte_t *alloc_lv2entry(struct exynos_iommu_domain *domain, sysmmu_pte_t *sent, sysmmu_iova_t iova, short *pgcounter)
static int lv1set_section(struct exynos_iommu_domain *domain, sysmmu_pte_t *sent, sysmmu_iova_t iova, phys_addr_t paddr, int prot, short *pgcnt)
static int lv2set_page(sysmmu_pte_t *pent, phys_addr_t paddr, size_t size, int prot, short *pgcnt)
static int exynos_iommu_map(struct iommu_domain *iommu_domain, unsigned long l_iova, phys_addr_t paddr, size_t size, int prot)
static void exynos_iommu_tlb_invalidate_entry(struct exynos_iommu_domain *domain, sysmmu_iova_t iova, size_t size)
static size_t exynos_iommu_unmap(struct iommu_domain *iommu_domain, unsigned long l_iova, size_t size)
static phys_addr_t exynos_iommu_iova_to_phys(struct iommu_domain *iommu_domain, dma_addr_t iova)
static int exynos_iommu_add_device(struct device *dev)
static void exynos_iommu_remove_device(struct device *dev)
static int exynos_iommu_of_xlate(struct device *dev, struct of_phandle_args *spec)
static int __init exynos_iommu_init(void)
  14 struct sysmmu_drvdata *data
  10 sysmmu_iova_t iova
   7 struct device *dev
   6 struct iommu_domain *iommu_domain
   5 size_t size
   3 sysmmu_pte_t *sent
   3 struct exynos_iommu_domain *domain
   3 phys_addr_t paddr
   3 int prot
   2 unsigned long l_iova
   2 short *pgcnt
   1 void *dev_id
   1 void
   1 unsigned type
   1 unsigned int num_inv
   1 sysmmu_pte_t val
   1 sysmmu_pte_t *pgtable
   1 sysmmu_pte_t *pent
   1 sysmmu_pte_t *ent
   1 sysmmu_iova_t fault_addr
   1 struct platform_device *pdev
   1 struct of_phandle_args *spec
   1 struct iommu_domain *dom
   1 short *pgcounter
   1 phys_addr_t pgd
   1 int irq
   1 dma_addr_t iova
   1 const struct sysmmu_fault_info *finfo
