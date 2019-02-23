
\n
static int usnic_uiom_dma_fault(struct iommu_domain *domain, struct device *dev, unsigned long iova, int flags, void *token)
static void usnic_uiom_put_pages(struct list_head *chunk_list, int dirty)
static int usnic_uiom_get_pages(unsigned long addr, size_t size, int writable, int dmasync, struct usnic_uiom_reg *uiomr)
static void usnic_uiom_unmap_sorted_intervals(struct list_head *intervals, struct usnic_uiom_pd *pd)
static void __usnic_uiom_reg_release(struct usnic_uiom_pd *pd, struct usnic_uiom_reg *uiomr, int dirty)
static int usnic_uiom_map_sorted_intervals(struct list_head *intervals, struct usnic_uiom_reg *uiomr)
struct usnic_uiom_reg *usnic_uiom_reg_get(struct usnic_uiom_pd *pd, unsigned long addr, size_t size, int writable, int dmasync)
static void __usnic_uiom_release_tail(struct usnic_uiom_reg *uiomr)
static inline size_t usnic_uiom_num_pages(struct usnic_uiom_reg *uiomr)
static void usnic_uiom_release_defer(struct work_struct *work)
void usnic_uiom_reg_release(struct usnic_uiom_reg *uiomr, struct ib_ucontext *context)
struct usnic_uiom_pd *usnic_uiom_alloc_pd(void)
void usnic_uiom_dealloc_pd(struct usnic_uiom_pd *pd)
int usnic_uiom_attach_dev_to_pd(struct usnic_uiom_pd *pd, struct device *dev)
void usnic_uiom_detach_dev_from_pd(struct usnic_uiom_pd *pd, struct device *dev)
struct device **usnic_uiom_get_dev_list(struct usnic_uiom_pd *pd)
void usnic_uiom_free_dev_list(struct device **devs)
int usnic_uiom_init(char *drv_name)
void usnic_uiom_fini(void)
\n
      7 struct usnic_uiom_pd *pd
      6 struct usnic_uiom_reg *uiomr
      3 struct device *dev
      2 void
      2 unsigned long addr
      2 struct list_head *intervals
      2 size_t size
      2 int writable
      2 int dmasync
      2 int dirty
      1 void *token
      1 unsigned long iova
      1 struct work_struct *work
      1 struct list_head *chunk_list
      1 struct iommu_domain *domain
      1 struct ib_ucontext *context
      1 struct device **devs
      1 int flags
      1 char *drv_name
