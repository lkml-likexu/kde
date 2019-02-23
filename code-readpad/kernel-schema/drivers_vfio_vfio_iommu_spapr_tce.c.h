
\n
static long try_increment_locked_vm(struct mm_struct *mm, long npages)
static void decrement_locked_vm(struct mm_struct *mm, long npages)
static long tce_iommu_mm_set(struct tce_container *container)
static long tce_iommu_prereg_free(struct tce_container *container, struct tce_iommu_prereg *tcemem)
static long tce_iommu_unregister_pages(struct tce_container *container, __u64 vaddr, __u64 size)
static long tce_iommu_register_pages(struct tce_container *container, __u64 vaddr, __u64 size)
static bool tce_page_is_contained(struct mm_struct *mm, unsigned long hpa, unsigned int page_shift)
static inline bool tce_groups_attached(struct tce_container *container)
static long tce_iommu_find_table(struct tce_container *container, phys_addr_t ioba, struct iommu_table **ptbl)
static int tce_iommu_find_free_table(struct tce_container *container)
static int tce_iommu_enable(struct tce_container *container)
static void tce_iommu_disable(struct tce_container *container)
static void *tce_iommu_open(unsigned long arg)
static void tce_iommu_release(void *iommu_data)
static void tce_iommu_unuse_page(struct tce_container *container, unsigned long hpa)
static int tce_iommu_prereg_ua_to_hpa(struct tce_container *container, unsigned long tce, unsigned long shift, unsigned long *phpa, struct mm_iommu_table_group_mem_t **pmem)
static void tce_iommu_unuse_page_v2(struct tce_container *container, struct iommu_table *tbl, unsigned long entry)
static int tce_iommu_clear(struct tce_container *container, struct iommu_table *tbl, unsigned long entry, unsigned long pages)
static int tce_iommu_use_page(unsigned long tce, unsigned long *hpa)
static long tce_iommu_build(struct tce_container *container, struct iommu_table *tbl, unsigned long entry, unsigned long tce, unsigned long pages, enum dma_data_direction direction)
static long tce_iommu_build_v2(struct tce_container *container, struct iommu_table *tbl, unsigned long entry, unsigned long tce, unsigned long pages, enum dma_data_direction direction)
static long tce_iommu_create_table(struct tce_container *container, struct iommu_table_group *table_group, int num, __u32 page_shift, __u64 window_size, __u32 levels, struct iommu_table **ptbl)
static void tce_iommu_free_table(struct tce_container *container, struct iommu_table *tbl)
static long tce_iommu_create_window(struct tce_container *container, __u32 page_shift, __u64 window_size, __u32 levels, __u64 *start_addr)
static long tce_iommu_remove_window(struct tce_container *container, __u64 start_addr)
static long tce_iommu_create_default_window(struct tce_container *container)
static long tce_iommu_ioctl(void *iommu_data, unsigned int cmd, unsigned long arg)
static void tce_iommu_release_ownership(struct tce_container *container, struct iommu_table_group *table_group)
static int tce_iommu_take_ownership(struct tce_container *container, struct iommu_table_group *table_group)
static void tce_iommu_release_ownership_ddw(struct tce_container *container, struct iommu_table_group *table_group)
static long tce_iommu_take_ownership_ddw(struct tce_container *container, struct iommu_table_group *table_group)
static int tce_iommu_attach_group(void *iommu_data, struct iommu_group *iommu_group)
static void tce_iommu_detach_group(void *iommu_data, struct iommu_group *iommu_group)
static int __init tce_iommu_init(void)
static void __exit tce_iommu_cleanup(void)
\n
     24 struct tce_container *container
      5 struct iommu_table *tbl
      5 struct iommu_table_group *table_group
      4 void *iommu_data
      4 unsigned long tce
      4 unsigned long entry
      3 unsigned long pages
      3 struct mm_struct *mm
      2 void
      2 unsigned long hpa
      2 unsigned long arg
      2 __u64 window_size
      2 __u64 vaddr
      2 __u64 size
      2 __u32 page_shift
      2 __u32 levels
      2 struct iommu_table **ptbl
      2 struct iommu_group *iommu_group
      2 long npages
      2 enum dma_data_direction direction
      1 unsigned long shift
      1 unsigned long *phpa
      1 unsigned long *hpa
      1 unsigned int page_shift
      1 unsigned int cmd
      1 __u64 start_addr
      1 __u64 *start_addr
      1 struct tce_iommu_prereg *tcemem
      1 struct mm_iommu_table_group_mem_t **pmem
      1 phys_addr_t ioba
      1 int num
