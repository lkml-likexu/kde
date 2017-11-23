
static struct ipmmu_vmsa_domain *to_vmsa_domain(struct iommu_domain *dom)
static struct ipmmu_vmsa_device *to_ipmmu(struct device *dev)
static bool ipmmu_is_root(struct ipmmu_vmsa_device *mmu)
static int __ipmmu_check_device(struct device *dev, void *data)
static struct ipmmu_vmsa_device *ipmmu_find_root(void)
static u32 ipmmu_read(struct ipmmu_vmsa_device *mmu, unsigned int offset)
static void ipmmu_write(struct ipmmu_vmsa_device *mmu, unsigned int offset, u32 data)
static u32 ipmmu_ctx_read_root(struct ipmmu_vmsa_domain *domain, unsigned int reg)
static void ipmmu_ctx_write_root(struct ipmmu_vmsa_domain *domain, unsigned int reg, u32 data)
static void ipmmu_ctx_write_all(struct ipmmu_vmsa_domain *domain, unsigned int reg, u32 data)
static void ipmmu_tlb_sync(struct ipmmu_vmsa_domain *domain)
static void ipmmu_tlb_invalidate(struct ipmmu_vmsa_domain *domain)
static void ipmmu_utlb_enable(struct ipmmu_vmsa_domain *domain, unsigned int utlb)
static void ipmmu_utlb_disable(struct ipmmu_vmsa_domain *domain, unsigned int utlb)
static void ipmmu_tlb_flush_all(void *cookie)
static void ipmmu_tlb_add_flush(unsigned long iova, size_t size, size_t granule, bool leaf, void *cookie)
static int ipmmu_domain_allocate_context(struct ipmmu_vmsa_device *mmu, struct ipmmu_vmsa_domain *domain)
static void ipmmu_domain_free_context(struct ipmmu_vmsa_device *mmu, unsigned int context_id)
static int ipmmu_domain_init_context(struct ipmmu_vmsa_domain *domain)
static void ipmmu_domain_destroy_context(struct ipmmu_vmsa_domain *domain)
static irqreturn_t ipmmu_domain_irq(struct ipmmu_vmsa_domain *domain)
static irqreturn_t ipmmu_irq(int irq, void *dev)
static struct iommu_domain *__ipmmu_domain_alloc(unsigned type)
static struct iommu_domain *ipmmu_domain_alloc(unsigned type)
static void ipmmu_domain_free(struct iommu_domain *io_domain)
static int ipmmu_attach_device(struct iommu_domain *io_domain, struct device *dev)
static void ipmmu_detach_device(struct iommu_domain *io_domain, struct device *dev)
static int ipmmu_map(struct iommu_domain *io_domain, unsigned long iova, phys_addr_t paddr, size_t size, int prot)
static size_t ipmmu_unmap(struct iommu_domain *io_domain, unsigned long iova, size_t size)
static void ipmmu_iotlb_sync(struct iommu_domain *io_domain)
static phys_addr_t ipmmu_iova_to_phys(struct iommu_domain *io_domain, dma_addr_t iova)
static int ipmmu_init_platform_device(struct device *dev, struct of_phandle_args *args)
static bool ipmmu_slave_whitelist(struct device *dev)
static int ipmmu_of_xlate(struct device *dev, struct of_phandle_args *spec)
static int ipmmu_init_arm_mapping(struct device *dev)
static int ipmmu_add_device(struct device *dev)
static void ipmmu_remove_device(struct device *dev)
static struct iommu_group *ipmmu_find_group(struct device *dev)
static void ipmmu_device_reset(struct ipmmu_vmsa_device *mmu)
static int ipmmu_probe(struct platform_device *pdev)
static int ipmmu_remove(struct platform_device *pdev)
static int __init ipmmu_init(void)
static void __exit ipmmu_exit(void)
  11 struct ipmmu_vmsa_domain *domain
  11 struct device *dev
   7 struct iommu_domain *io_domain
   6 struct ipmmu_vmsa_device *mmu
   3 void
   3 unsigned long iova
   3 unsigned int reg
   3 u32 data
   3 size_t size
   2 void *cookie
   2 unsigned type
   2 unsigned int utlb
   2 unsigned int offset
   2 struct platform_device *pdev
   1 void *dev
   1 void *data
   1 unsigned int context_id
   1 struct of_phandle_args *spec
   1 struct of_phandle_args *args
   1 struct iommu_domain *dom
   1 size_t granule
   1 phys_addr_t paddr
   1 int prot
   1 int irq
   1 dma_addr_t iova
   1 bool leaf
