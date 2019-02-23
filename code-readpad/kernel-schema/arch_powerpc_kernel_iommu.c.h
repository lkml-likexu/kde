
EXPORT_SYMBOL_GPL(iommu_tce_table_get);
EXPORT_SYMBOL_GPL(iommu_tce_table_put);
EXPORT_SYMBOL_GPL(iommu_direction_to_tce_perm);
EXPORT_SYMBOL_GPL(iommu_tce_direction);
EXPORT_SYMBOL_GPL(iommu_flush_tce);
EXPORT_SYMBOL_GPL(iommu_tce_check_ioba);
EXPORT_SYMBOL_GPL(iommu_tce_check_gpa);
EXPORT_SYMBOL_GPL(iommu_tce_xchg);
EXPORT_SYMBOL_GPL(iommu_take_ownership);
EXPORT_SYMBOL_GPL(iommu_release_ownership);
EXPORT_SYMBOL_GPL(iommu_add_device);
EXPORT_SYMBOL_GPL(iommu_del_device);
\n
static int __init setup_iommu(char *str)
static int __init setup_iommu_pool_hash(void)
static int __init setup_fail_iommu(char *str)
static bool should_fail_iommu(struct device *dev)
static int __init fail_iommu_debugfs(void)
static ssize_t fail_iommu_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t fail_iommu_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static int fail_iommu_bus_notify(struct notifier_block *nb, unsigned long action, void *data)
static int __init fail_iommu_setup(void)
return 0; }arch_initcall(fail_iommu_setup)
; static inline bool should_fail_iommu(struct device *dev)
static unsigned long iommu_range_alloc(struct device *dev, struct iommu_table *tbl, unsigned long npages, unsigned long *handle, unsigned long mask, unsigned int align_order)
static dma_addr_t iommu_alloc(struct device *dev, struct iommu_table *tbl, void *page, unsigned int npages, enum dma_data_direction direction, unsigned long mask, unsigned int align_order, unsigned long attrs)
static bool iommu_free_check(struct iommu_table *tbl, dma_addr_t dma_addr, unsigned int npages)
static struct iommu_pool *get_pool(struct iommu_table *tbl, unsigned long entry)
static void __iommu_free(struct iommu_table *tbl, dma_addr_t dma_addr, unsigned int npages)
static void iommu_free(struct iommu_table *tbl, dma_addr_t dma_addr, unsigned int npages)
int ppc_iommu_map_sg(struct device *dev, struct iommu_table *tbl, struct scatterlist *sglist, int nelems, unsigned long mask, enum dma_data_direction direction, unsigned long attrs)
void ppc_iommu_unmap_sg(struct iommu_table *tbl, struct scatterlist *sglist, int nelems, enum dma_data_direction direction, unsigned long attrs)
static void iommu_table_clear(struct iommu_table *tbl)
struct iommu_table *iommu_init_table(struct iommu_table *tbl, int nid)
static void iommu_table_free(struct kref *kref)
struct iommu_table *iommu_tce_table_get(struct iommu_table *tbl)
int iommu_tce_table_put(struct iommu_table *tbl)
dma_addr_t iommu_map_page(struct device *dev, struct iommu_table *tbl, struct page *page, unsigned long offset, size_t size, unsigned long mask, enum dma_data_direction direction, unsigned long attrs)
void iommu_unmap_page(struct iommu_table *tbl, dma_addr_t dma_handle, size_t size, enum dma_data_direction direction, unsigned long attrs)
void *iommu_alloc_coherent(struct device *dev, struct iommu_table *tbl, size_t size, dma_addr_t *dma_handle, unsigned long mask, gfp_t flag, int node)
void iommu_free_coherent(struct iommu_table *tbl, size_t size, void *vaddr, dma_addr_t dma_handle)
unsigned long iommu_direction_to_tce_perm(enum dma_data_direction dir)
static void group_release(void *iommu_data)
void iommu_register_group(struct iommu_table_group *table_group, int pci_domain_number, unsigned long pe_num)
enum dma_data_direction iommu_tce_direction(unsigned long tce)
void iommu_flush_tce(struct iommu_table *tbl)
int iommu_tce_check_ioba(unsigned long page_shift, unsigned long offset, unsigned long size, unsigned long ioba, unsigned long npages)
int iommu_tce_check_gpa(unsigned long page_shift, unsigned long gpa)
long iommu_tce_xchg(struct mm_struct *mm, struct iommu_table *tbl, unsigned long entry, unsigned long *hpa, enum dma_data_direction *direction)
int iommu_take_ownership(struct iommu_table *tbl)
void iommu_release_ownership(struct iommu_table *tbl)
int iommu_add_device(struct iommu_table_group *table_group, struct device *dev)
void iommu_del_device(struct device *dev)
\n
     20 struct iommu_table *tbl
     11 struct device *dev
      5 unsigned long mask
      5 unsigned long attrs
      5 enum dma_data_direction direction
      4 unsigned int npages
      4 size_t size
      3 void
      3 dma_addr_t dma_addr
      2 unsigned long page_shift
      2 unsigned long offset
      2 unsigned long npages
      2 unsigned long entry
      2 unsigned int align_order
      2 struct scatterlist *sglist
      2 struct iommu_table_group *table_group
      2 struct device_attribute *attr
      2 int nelems
      2 dma_addr_t dma_handle
      2 char *str
      1 void *vaddr
      1 void *page
      1 void *iommu_data
      1 void *data
      1 unsigned long tce
      1 unsigned long size
      1 unsigned long pe_num
      1 unsigned long ioba
      1 unsigned long *hpa
      1 unsigned long *handle
      1 unsigned long gpa
      1 unsigned long action
      1 struct page *page
      1 struct notifier_block *nb
      1 struct mm_struct *mm
      1 struct kref *kref
      1 size_t count
      1 iommu_tce_xchg
      1 iommu_tce_table_put
      1 iommu_tce_table_get
      1 iommu_tce_direction
      1 iommu_tce_check_ioba
      1 iommu_tce_check_gpa
      1 iommu_take_ownership
      1 iommu_release_ownership
      1 iommu_flush_tce
      1 iommu_direction_to_tce_perm
      1 iommu_del_device
      1 iommu_add_device
      1 int pci_domain_number
      1 int node
      1 int nid
      1 gfp_t flag
      1 fail_iommu_setup
      1 enum dma_data_direction *direction
      1 enum dma_data_direction dir
      1 dma_addr_t *dma_handle
      1 const char *buf
      1 char *buf
