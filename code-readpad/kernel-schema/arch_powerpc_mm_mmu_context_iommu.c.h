
EXPORT_SYMBOL_GPL(mm_iommu_preregistered);
EXPORT_SYMBOL_GPL(mm_iommu_new);
EXPORT_SYMBOL_GPL(mm_iommu_newdev);
EXPORT_SYMBOL_GPL(mm_iommu_put);
EXPORT_SYMBOL_GPL(mm_iommu_lookup);
EXPORT_SYMBOL_GPL(mm_iommu_get);
EXPORT_SYMBOL_GPL(mm_iommu_ua_to_hpa);
EXPORT_SYMBOL_GPL(mm_iommu_is_devmem);
EXPORT_SYMBOL_GPL(mm_iommu_mapped_inc);
EXPORT_SYMBOL_GPL(mm_iommu_mapped_dec);
\n
static long mm_iommu_adjust_locked_vm(struct mm_struct *mm, unsigned long npages, bool incr)
bool mm_iommu_preregistered(struct mm_struct *mm)
struct page *new_iommu_non_cma_page(struct page *page, unsigned long private)
static int mm_iommu_move_page_from_cma(struct page *page)
static long mm_iommu_do_alloc(struct mm_struct *mm, unsigned long ua, unsigned long entries, unsigned long dev_hpa, struct mm_iommu_table_group_mem_t **pmem)
long mm_iommu_new(struct mm_struct *mm, unsigned long ua, unsigned long entries, struct mm_iommu_table_group_mem_t **pmem)
long mm_iommu_newdev(struct mm_struct *mm, unsigned long ua, unsigned long entries, unsigned long dev_hpa, struct mm_iommu_table_group_mem_t **pmem)
static void mm_iommu_unpin(struct mm_iommu_table_group_mem_t *mem)
static void mm_iommu_do_free(struct mm_iommu_table_group_mem_t *mem)
static void mm_iommu_free(struct rcu_head *head)
static void mm_iommu_release(struct mm_iommu_table_group_mem_t *mem)
long mm_iommu_put(struct mm_struct *mm, struct mm_iommu_table_group_mem_t *mem)
struct mm_iommu_table_group_mem_t *mm_iommu_lookup(struct mm_struct *mm, unsigned long ua, unsigned long size)
struct mm_iommu_table_group_mem_t *mm_iommu_lookup_rm(struct mm_struct *mm, unsigned long ua, unsigned long size)
struct mm_iommu_table_group_mem_t *mm_iommu_get(struct mm_struct *mm, unsigned long ua, unsigned long entries)
long mm_iommu_ua_to_hpa(struct mm_iommu_table_group_mem_t *mem, unsigned long ua, unsigned int pageshift, unsigned long *hpa)
long mm_iommu_ua_to_hpa_rm(struct mm_iommu_table_group_mem_t *mem, unsigned long ua, unsigned int pageshift, unsigned long *hpa)
extern void mm_iommu_ua_mark_dirty_rm(struct mm_struct *mm, unsigned long ua)
bool mm_iommu_is_devmem(struct mm_struct *mm, unsigned long hpa, unsigned int pageshift, unsigned long *size)
long mm_iommu_mapped_inc(struct mm_iommu_table_group_mem_t *mem)
void mm_iommu_mapped_dec(struct mm_iommu_table_group_mem_t *mem)
void mm_iommu_init(struct mm_struct *mm)
\n
     12 struct mm_struct *mm
      9 unsigned long ua
      8 struct mm_iommu_table_group_mem_t *mem
      4 unsigned long entries
      3 unsigned int pageshift
      3 struct mm_iommu_table_group_mem_t **pmem
      2 unsigned long size
      2 unsigned long *hpa
      2 unsigned long dev_hpa
      2 struct page *page
      1 unsigned long *size
      1 unsigned long private
      1 unsigned long npages
      1 unsigned long hpa
      1 struct rcu_head *head
      1 mm_iommu_ua_to_hpa
      1 mm_iommu_put
      1 mm_iommu_preregistered
      1 mm_iommu_newdev
      1 mm_iommu_new
      1 mm_iommu_mapped_inc
      1 mm_iommu_mapped_dec
      1 mm_iommu_lookup
      1 mm_iommu_is_devmem
      1 mm_iommu_get
      1 bool incr
