
EXPORT_SYMBOL_GPL(omap_iommu_save_ctx);
EXPORT_SYMBOL_GPL(omap_iommu_restore_ctx);
\n
static struct omap_iommu_domain *to_omap_domain(struct iommu_domain *dom)
void omap_iommu_save_ctx(struct device *dev)
void omap_iommu_restore_ctx(struct device *dev)
static void dra7_cfg_dspsys_mmu(struct omap_iommu *obj, bool enable)
static void __iommu_set_twl(struct omap_iommu *obj, bool on)
static int omap2_iommu_enable(struct omap_iommu *obj)
static void omap2_iommu_disable(struct omap_iommu *obj)
static int iommu_enable(struct omap_iommu *obj)
static void iommu_disable(struct omap_iommu *obj)
static u32 iotlb_cr_to_virt(struct cr_regs *cr)
static u32 get_iopte_attr(struct iotlb_entry *e)
static u32 iommu_report_fault(struct omap_iommu *obj, u32 *da)
void iotlb_lock_get(struct omap_iommu *obj, struct iotlb_lock *l)
void iotlb_lock_set(struct omap_iommu *obj, struct iotlb_lock *l)
static void iotlb_read_cr(struct omap_iommu *obj, struct cr_regs *cr)
static void iotlb_load_cr(struct omap_iommu *obj, struct cr_regs *cr)
struct cr_regs __iotlb_read_cr(struct omap_iommu *obj, int n)
static struct cr_regs *iotlb_alloc_cr(struct omap_iommu *obj, struct iotlb_entry *e)
static int load_iotlb_entry(struct omap_iommu *obj, struct iotlb_entry *e)
static int load_iotlb_entry(struct omap_iommu *obj, struct iotlb_entry *e)
static int prefetch_iotlb_entry(struct omap_iommu *obj, struct iotlb_entry *e)
static void flush_iotlb_page(struct omap_iommu *obj, u32 da)
static void flush_iotlb_all(struct omap_iommu *obj)
static void flush_iopte_range(struct device *dev, dma_addr_t dma, unsigned long offset, int num_entries)
static void iopte_free(struct omap_iommu *obj, u32 *iopte, bool dma_valid)
static u32 *iopte_alloc(struct omap_iommu *obj, u32 *iopgd, dma_addr_t *pt_dma, u32 da)
static int iopgd_alloc_section(struct omap_iommu *obj, u32 da, u32 pa, u32 prot)
static int iopgd_alloc_super(struct omap_iommu *obj, u32 da, u32 pa, u32 prot)
static int iopte_alloc_page(struct omap_iommu *obj, u32 da, u32 pa, u32 prot)
static int iopte_alloc_large(struct omap_iommu *obj, u32 da, u32 pa, u32 prot)
static int iopgtable_store_entry_core(struct omap_iommu *obj, struct iotlb_entry *e)
static int omap_iopgtable_store_entry(struct omap_iommu *obj, struct iotlb_entry *e)
static void iopgtable_lookup_entry(struct omap_iommu *obj, u32 da, u32 **ppgd, u32 **ppte)
static size_t iopgtable_clear_entry_core(struct omap_iommu *obj, u32 da)
static size_t iopgtable_clear_entry(struct omap_iommu *obj, u32 da)
static void iopgtable_clear_entry_all(struct omap_iommu *obj)
static irqreturn_t iommu_fault_handler(int irq, void *data)
static int omap_iommu_attach(struct omap_iommu *obj, u32 *iopgd)
static void omap_iommu_detach(struct omap_iommu *obj)
static bool omap_iommu_can_register(struct platform_device *pdev)
static int omap_iommu_dra7_get_dsp_system_cfg(struct platform_device *pdev, struct omap_iommu *obj)
static int omap_iommu_probe(struct platform_device *pdev)
static int omap_iommu_remove(struct platform_device *pdev)
static u32 iotlb_init_entry(struct iotlb_entry *e, u32 da, u32 pa, int pgsz)
static int omap_iommu_map(struct iommu_domain *domain, unsigned long da, phys_addr_t pa, size_t bytes, int prot)
static size_t omap_iommu_unmap(struct iommu_domain *domain, unsigned long da, size_t size)
static int omap_iommu_count(struct device *dev)
static int omap_iommu_attach_init(struct device *dev, struct omap_iommu_domain *odomain)
static void omap_iommu_detach_fini(struct omap_iommu_domain *odomain)
static int omap_iommu_attach_dev(struct iommu_domain *domain, struct device *dev)
static void _omap_iommu_detach_dev(struct omap_iommu_domain *omap_domain, struct device *dev)
static void omap_iommu_detach_dev(struct iommu_domain *domain, struct device *dev)
static struct iommu_domain *omap_iommu_domain_alloc(unsigned type)
static void omap_iommu_domain_free(struct iommu_domain *domain)
static phys_addr_t omap_iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t da)
static int omap_iommu_add_device(struct device *dev)
static void omap_iommu_remove_device(struct device *dev)
static struct iommu_group *omap_iommu_device_group(struct device *dev)
static int __init omap_iommu_init(void)
\n
     33 struct omap_iommu *obj
     11 struct device *dev
     10 u32 da
      8 struct iotlb_entry *e
      6 struct iommu_domain *domain
      5 u32 pa
      4 u32 prot
      4 struct platform_device *pdev
      3 struct cr_regs *cr
      2 unsigned long da
      2 u32 *iopgd
      2 struct omap_iommu_domain *odomain
      2 struct iotlb_lock *l
      1 void *data
      1 void
      1 unsigned type
      1 unsigned long offset
      1 u32 **ppte
      1 u32 **ppgd
      1 u32 *iopte
      1 u32 *da
      1 struct omap_iommu_domain *omap_domain
      1 struct iommu_domain *dom
      1 size_t size
      1 size_t bytes
      1 phys_addr_t pa
      1 omap_iommu_save_ctx
      1 omap_iommu_restore_ctx
      1 int prot
      1 int pgsz
      1 int num_entries
      1 int n
      1 int irq
      1 dma_addr_t *pt_dma
      1 dma_addr_t dma
      1 dma_addr_t da
      1 bool on
      1 bool enable
      1 bool dma_valid
