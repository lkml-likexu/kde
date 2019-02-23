
\n
static struct vfio_dma *vfio_find_dma(struct vfio_iommu *iommu, dma_addr_t start, size_t size)
static void vfio_link_dma(struct vfio_iommu *iommu, struct vfio_dma *new)
static void vfio_unlink_dma(struct vfio_iommu *iommu, struct vfio_dma *old)
static struct vfio_pfn *vfio_find_vpfn(struct vfio_dma *dma, dma_addr_t iova)
static void vfio_link_pfn(struct vfio_dma *dma, struct vfio_pfn *new)
static void vfio_unlink_pfn(struct vfio_dma *dma, struct vfio_pfn *old)
static int vfio_add_to_pfn_list(struct vfio_dma *dma, dma_addr_t iova, unsigned long pfn)
static void vfio_remove_from_pfn_list(struct vfio_dma *dma, struct vfio_pfn *vpfn)
static struct vfio_pfn *vfio_iova_get_vfio_pfn(struct vfio_dma *dma, unsigned long iova)
static int vfio_iova_put_vfio_pfn(struct vfio_dma *dma, struct vfio_pfn *vpfn)
static int vfio_lock_acct(struct vfio_dma *dma, long npage, bool async)
static bool is_invalid_reserved_pfn(unsigned long pfn)
static int put_pfn(unsigned long pfn, int prot)
static int vaddr_get_pfn(struct mm_struct *mm, unsigned long vaddr, int prot, unsigned long *pfn)
static long vfio_pin_pages_remote(struct vfio_dma *dma, unsigned long vaddr, long npage, unsigned long *pfn_base, unsigned long limit)
static long vfio_unpin_pages_remote(struct vfio_dma *dma, dma_addr_t iova, unsigned long pfn, long npage, bool do_accounting)
static int vfio_pin_page_external(struct vfio_dma *dma, unsigned long vaddr, unsigned long *pfn_base, bool do_accounting)
static int vfio_unpin_page_external(struct vfio_dma *dma, dma_addr_t iova, bool do_accounting)
static int vfio_iommu_type1_pin_pages(void *iommu_data, unsigned long *user_pfn, int npage, int prot, unsigned long *phys_pfn)
static int vfio_iommu_type1_unpin_pages(void *iommu_data, unsigned long *user_pfn, int npage)
static long vfio_sync_unpin(struct vfio_dma *dma, struct vfio_domain *domain, struct list_head *regions)
static size_t unmap_unpin_fast(struct vfio_domain *domain, struct vfio_dma *dma, dma_addr_t *iova, size_t len, phys_addr_t phys, long *unlocked, struct list_head *unmapped_list, int *unmapped_cnt)
static size_t unmap_unpin_slow(struct vfio_domain *domain, struct vfio_dma *dma, dma_addr_t *iova, size_t len, phys_addr_t phys, long *unlocked)
static long vfio_unmap_unpin(struct vfio_iommu *iommu, struct vfio_dma *dma, bool do_accounting)
static void vfio_remove_dma(struct vfio_iommu *iommu, struct vfio_dma *dma)
static unsigned long vfio_pgsize_bitmap(struct vfio_iommu *iommu)
static int vfio_dma_do_unmap(struct vfio_iommu *iommu, struct vfio_iommu_type1_dma_unmap *unmap)
static int vfio_iommu_map(struct vfio_iommu *iommu, dma_addr_t iova, unsigned long pfn, long npage, int prot)
static int vfio_pin_map_dma(struct vfio_iommu *iommu, struct vfio_dma *dma, size_t map_size)
static int vfio_dma_do_map(struct vfio_iommu *iommu, struct vfio_iommu_type1_dma_map *map)
static int vfio_bus_type(struct device *dev, void *data)
static int vfio_iommu_replay(struct vfio_iommu *iommu, struct vfio_domain *domain)
static void vfio_test_domain_fgsp(struct vfio_domain *domain)
static struct vfio_group *find_iommu_group(struct vfio_domain *domain, struct iommu_group *iommu_group)
static bool vfio_iommu_has_sw_msi(struct iommu_group *group, phys_addr_t *base)
static int vfio_iommu_type1_attach_group(void *iommu_data, struct iommu_group *iommu_group)
static void vfio_iommu_unmap_unpin_all(struct vfio_iommu *iommu)
static void vfio_iommu_unmap_unpin_reaccount(struct vfio_iommu *iommu)
static void vfio_sanity_check_pfn_list(struct vfio_iommu *iommu)
static void vfio_iommu_type1_detach_group(void *iommu_data, struct iommu_group *iommu_group)
static void *vfio_iommu_type1_open(unsigned long arg)
static void vfio_release_domain(struct vfio_domain *domain, bool external)
static void vfio_iommu_type1_release(void *iommu_data)
static int vfio_domains_have_iommu_cache(struct vfio_iommu *iommu)
static long vfio_iommu_type1_ioctl(void *iommu_data, unsigned int cmd, unsigned long arg)
static int vfio_iommu_type1_register_notifier(void *iommu_data, unsigned long *events, struct notifier_block *nb)
static int vfio_iommu_type1_unregister_notifier(void *iommu_data, struct notifier_block *nb)
static int __init vfio_iommu_type1_init(void)
static void __exit vfio_iommu_type1_cleanup(void)
\n
     18 struct vfio_dma *dma
     15 struct vfio_iommu *iommu
      8 void *iommu_data
      7 struct vfio_domain *domain
      5 unsigned long pfn
      5 dma_addr_t iova
      4 long npage
      4 int prot
      4 bool do_accounting
      3 unsigned long vaddr
      3 struct iommu_group *iommu_group
      2 void
      2 unsigned long *user_pfn
      2 unsigned long *pfn_base
      2 unsigned long arg
      2 struct vfio_pfn *vpfn
      2 struct notifier_block *nb
      2 size_t len
      2 phys_addr_t phys
      2 long *unlocked
      2 int npage
      2 dma_addr_t *iova
      1 void *data
      1 unsigned long *phys_pfn
      1 unsigned long *pfn
      1 unsigned long limit
      1 unsigned long iova
      1 unsigned long *events
      1 unsigned int cmd
      1 struct vfio_pfn *old
      1 struct vfio_pfn *new
      1 struct vfio_iommu_type1_dma_unmap *unmap
      1 struct vfio_iommu_type1_dma_map *map
      1 struct vfio_dma *old
      1 struct vfio_dma *new
      1 struct mm_struct *mm
      1 struct list_head *unmapped_list
      1 struct list_head *regions
      1 struct iommu_group *group
      1 struct device *dev
      1 size_t size
      1 size_t map_size
      1 phys_addr_t *base
      1 int *unmapped_cnt
      1 dma_addr_t start
      1 bool external
      1 bool async
