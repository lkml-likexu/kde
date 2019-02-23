
EXPORT_SYMBOL_GPL(hmm_devmem_add);
EXPORT_SYMBOL_GPL(hmm_devmem_add_resource);
\n
static struct hmm *hmm_register(struct mm_struct *mm)
void hmm_mm_destroy(struct mm_struct *mm)
static int hmm_invalidate_range(struct hmm *hmm, bool device, const struct hmm_update *update)
static void hmm_release(struct mmu_notifier *mn, struct mm_struct *mm)
static int hmm_invalidate_range_start(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static void hmm_invalidate_range_end(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
int hmm_mirror_register(struct hmm_mirror *mirror, struct mm_struct *mm)
void hmm_mirror_unregister(struct hmm_mirror *mirror)
static int hmm_vma_do_fault(struct mm_walk *walk, unsigned long addr, bool write_fault, uint64_t *pfn)
static int hmm_pfns_bad(unsigned long addr, unsigned long end, struct mm_walk *walk)
static int hmm_vma_walk_hole_(unsigned long addr, unsigned long end, bool fault, bool write_fault, struct mm_walk *walk)
static inline void hmm_pte_need_fault(const struct hmm_vma_walk *hmm_vma_walk, uint64_t pfns, uint64_t cpu_flags, bool *fault, bool *write_fault)
static void hmm_range_need_fault(const struct hmm_vma_walk *hmm_vma_walk, const uint64_t *pfns, unsigned long npages, uint64_t cpu_flags, bool *fault, bool *write_fault)
static int hmm_vma_walk_hole(unsigned long addr, unsigned long end, struct mm_walk *walk)
static inline uint64_t pmd_to_hmm_pfn_flags(struct hmm_range *range, pmd_t pmd)
static int hmm_vma_handle_pmd(struct mm_walk *walk, unsigned long addr, unsigned long end, uint64_t *pfns, pmd_t pmd)
static inline uint64_t pte_to_hmm_pfn_flags(struct hmm_range *range, pte_t pte)
static int hmm_vma_handle_pte(struct mm_walk *walk, unsigned long addr, unsigned long end, pmd_t *pmdp, pte_t *ptep, uint64_t *pfn)
static int hmm_vma_walk_pmd(pmd_t *pmdp, unsigned long start, unsigned long end, struct mm_walk *walk)
static void hmm_pfns_clear(struct hmm_range *range, uint64_t *pfns, unsigned long addr, unsigned long end)
static void hmm_pfns_special(struct hmm_range *range)
int hmm_vma_get_pfns(struct hmm_range *range)
bool hmm_vma_range_done(struct hmm_range *range)
int hmm_vma_fault(struct hmm_range *range, bool block)
struct page *hmm_vma_alloc_locked_page(struct vm_area_struct *vma, unsigned long addr)
static void hmm_devmem_ref_release(struct percpu_ref *ref)
static void hmm_devmem_ref_exit(void *data)
static void hmm_devmem_ref_kill(struct percpu_ref *ref)
static int hmm_devmem_fault(struct vm_area_struct *vma, unsigned long addr, const struct page *page, unsigned int flags, pmd_t *pmdp)
static void hmm_devmem_free(struct page *page, void *data)
struct hmm_devmem *hmm_devmem_add(const struct hmm_devmem_ops *ops, struct device *device, unsigned long size)
struct hmm_devmem *hmm_devmem_add_resource(const struct hmm_devmem_ops *ops, struct device *device, struct resource *res)
static void hmm_device_release(struct device *device)
struct hmm_device *hmm_device_new(void *drvdata)
void hmm_device_put(struct hmm_device *hmm_device)
static int __init hmm_init(void)
\n
      9 unsigned long addr
      7 unsigned long end
      7 struct mm_walk *walk
      7 struct hmm_range *range
      4 struct mm_struct *mm
      3 struct mmu_notifier *mn
      3 struct device *device
      3 pmd_t *pmdp
      2 void *data
      2 uint64_t *pfns
      2 uint64_t *pfn
      2 uint64_t cpu_flags
      2 struct vm_area_struct *vma
      2 struct percpu_ref *ref
      2 struct hmm_mirror *mirror
      2 pmd_t pmd
      2 const struct mmu_notifier_range *range
      2 const struct hmm_vma_walk *hmm_vma_walk
      2 const struct hmm_devmem_ops *ops
      2 bool write_fault
      2 bool *write_fault
      2 bool *fault
      1 void *drvdata
      1 void
      1 unsigned long start
      1 unsigned long size
      1 unsigned long npages
      1 unsigned int flags
      1 uint64_t pfns
      1 struct resource *res
      1 struct page *page
      1 struct hmm *hmm
      1 struct hmm_device *hmm_device
      1 pte_t *ptep
      1 pte_t pte
      1 hmm_devmem_add_resource
      1 hmm_devmem_add
      1 const uint64_t *pfns
      1 const struct page *page
      1 const struct hmm_update *update
      1 bool fault
      1 bool device
      1 bool block
