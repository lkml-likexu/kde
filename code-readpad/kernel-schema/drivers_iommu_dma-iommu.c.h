
\n
static inline size_t cookie_msi_granule(struct iommu_dma_cookie *cookie)
static struct iommu_dma_cookie *cookie_alloc(enum iommu_dma_cookie_type type)
int iommu_dma_init(void)
int iommu_get_dma_cookie(struct iommu_domain *domain)
int iommu_get_msi_cookie(struct iommu_domain *domain, dma_addr_t base)
void iommu_put_dma_cookie(struct iommu_domain *domain)
void iommu_dma_get_resv_regions(struct device *dev, struct list_head *list)
static int cookie_init_hw_msi_region(struct iommu_dma_cookie *cookie, phys_addr_t start, phys_addr_t end)
static void iova_reserve_pci_windows(struct pci_dev *dev, struct iova_domain *iovad)
static int iova_reserve_iommu_regions(struct device *dev, struct iommu_domain *domain)
static void iommu_dma_flush_iotlb_all(struct iova_domain *iovad)
int iommu_dma_init_domain(struct iommu_domain *domain, dma_addr_t base, u64 size, struct device *dev)
int dma_info_to_prot(enum dma_data_direction dir, bool coherent, unsigned long attrs)
static dma_addr_t iommu_dma_alloc_iova(struct iommu_domain *domain, size_t size, dma_addr_t dma_limit, struct device *dev)
static void iommu_dma_free_iova(struct iommu_dma_cookie *cookie, dma_addr_t iova, size_t size)
static void __iommu_dma_unmap(struct iommu_domain *domain, dma_addr_t dma_addr, size_t size)
static void __iommu_dma_free_pages(struct page **pages, int count)
static struct page **__iommu_dma_alloc_pages(struct device *dev, unsigned int count, unsigned long order_mask, gfp_t gfp)
void iommu_dma_free(struct device *dev, struct page **pages, size_t size, dma_addr_t *handle)
struct page **iommu_dma_alloc(struct device *dev, size_t size, gfp_t gfp, unsigned long attrs, int prot, dma_addr_t *handle, void (*flush_page)
(struct device *, const void *, phys_addr_t)
)
int iommu_dma_mmap(struct page **pages, size_t size, struct vm_area_struct *vma)
static dma_addr_t __iommu_dma_map(struct device *dev, phys_addr_t phys, size_t size, int prot, struct iommu_domain *domain)
dma_addr_t iommu_dma_map_page(struct device *dev, struct page *page, unsigned long offset, size_t size, int prot)
void iommu_dma_unmap_page(struct device *dev, dma_addr_t handle, size_t size, enum dma_data_direction dir, unsigned long attrs)
static int __finalise_sg(struct device *dev, struct scatterlist *sg, int nents, dma_addr_t dma_addr)
static void __invalidate_sg(struct scatterlist *sg, int nents)
int iommu_dma_map_sg(struct device *dev, struct scatterlist *sg, int nents, int prot)
void iommu_dma_unmap_sg(struct device *dev, struct scatterlist *sg, int nents, enum dma_data_direction dir, unsigned long attrs)
dma_addr_t iommu_dma_map_resource(struct device *dev, phys_addr_t phys, size_t size, enum dma_data_direction dir, unsigned long attrs)
void iommu_dma_unmap_resource(struct device *dev, dma_addr_t handle, size_t size, enum dma_data_direction dir, unsigned long attrs)
static struct iommu_dma_msi_page *iommu_dma_get_msi_page(struct device *dev, phys_addr_t msi_addr, struct iommu_domain *domain)
void iommu_dma_map_msi_msg(int irq, struct msi_msg *msg)
\n
     16 struct device *dev
     11 size_t size
      9 struct iommu_domain *domain
      6 unsigned long attrs
      5 enum dma_data_direction dir
      4 struct scatterlist *sg
      4 int prot
      4 int nents
      3 struct page **pages
      3 struct iommu_dma_cookie *cookie
      2 struct iova_domain *iovad
      2 phys_addr_t phys
      2 gfp_t gfp
      2 dma_addr_t *handle
      2 dma_addr_t handle
      2 dma_addr_t dma_addr
      2 dma_addr_t base
      1 void *flush_page
      1 void
      1 unsigned long order_mask
      1 unsigned long offset
      1 unsigned int count
      1 u64 size
      1 struct vm_area_struct *vma
      1 struct pci_dev *dev
      1 struct page *page
      1 struct msi_msg *msg
      1 struct list_head *list
      1 struct device *
      1 phys_addr_t start
      1 phys_addr_t msi_addr
      1 phys_addr_t end
      1 phys_addr_t
      1 int irq
      1 int count
      1 enum iommu_dma_cookie_type type
      1 dma_addr_t iova
      1 dma_addr_t dma_limit
      1 const void *
      1 bool coherent
