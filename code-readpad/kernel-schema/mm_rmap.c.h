
EXPORT_SYMBOL_GPL(page_mkclean);
\n
static inline struct anon_vma *anon_vma_alloc(void)
static inline void anon_vma_free(struct anon_vma *anon_vma)
static inline struct anon_vma_chain *anon_vma_chain_alloc(gfp_t gfp)
static void anon_vma_chain_free(struct anon_vma_chain *anon_vma_chain)
static void anon_vma_chain_link(struct vm_area_struct *vma, struct anon_vma_chain *avc, struct anon_vma *anon_vma)
int __anon_vma_prepare(struct vm_area_struct *vma)
static inline struct anon_vma *lock_anon_vma_root(struct anon_vma *root, struct anon_vma *anon_vma)
static inline void unlock_anon_vma_root(struct anon_vma *root)
int anon_vma_clone(struct vm_area_struct *dst, struct vm_area_struct *src)
int anon_vma_fork(struct vm_area_struct *vma, struct vm_area_struct *pvma)
void unlink_anon_vmas(struct vm_area_struct *vma)
static void anon_vma_ctor(void *data)
void __init anon_vma_init(void)
struct anon_vma *page_get_anon_vma(struct page *page)
struct anon_vma *page_lock_anon_vma_read(struct page *page)
void page_unlock_anon_vma_read(struct anon_vma *anon_vma)
void try_to_unmap_flush(void)
void try_to_unmap_flush_dirty(void)
static void set_tlb_ubc_flush_pending(struct mm_struct *mm, bool writable)
static bool should_defer_flush(struct mm_struct *mm, enum ttu_flags flags)
void flush_tlb_batched_pending(struct mm_struct *mm)
barrier()
; mm->tlb_flush_batched = false;} } static void set_tlb_ubc_flush_pending(struct mm_struct *mm, bool writable)
static bool should_defer_flush(struct mm_struct *mm, enum ttu_flags flags)
unsigned long page_address_in_vma(struct page *page, struct vm_area_struct *vma)
pmd_t *mm_find_pmd(struct mm_struct *mm, unsigned long address)
int mapcount;int referenced;unsigned long vm_flags;struct mem_cgroup *memcg; };static bool page_referenced_one(struct page *page, struct vm_area_struct *vma, unsigned long address, void *arg)
static bool invalid_page_referenced_vma(struct vm_area_struct *vma, void *arg)
int page_referenced(struct page *page, int is_locked, struct mem_cgroup *memcg, unsigned long *vm_flags)
static bool page_mkclean_one(struct page *page, struct vm_area_struct *vma, unsigned long address, void *arg)
static bool invalid_mkclean_vma(struct vm_area_struct *vma, void *arg)
int page_mkclean(struct page *page)
void page_move_anon_rmap(struct page *page, struct vm_area_struct *vma)
static void __page_set_anon_rmap(struct page *page, struct vm_area_struct *vma, unsigned long address, int exclusive)
static void __page_check_anon_rmap(struct page *page, struct vm_area_struct *vma, unsigned long address)
void page_add_anon_rmap(struct page *page, struct vm_area_struct *vma, unsigned long address, bool compound)
void do_page_add_anon_rmap(struct page *page, struct vm_area_struct *vma, unsigned long address, int flags)
void page_add_new_anon_rmap(struct page *page, struct vm_area_struct *vma, unsigned long address, bool compound)
void page_add_file_rmap(struct page *page, bool compound)
static void page_remove_file_rmap(struct page *page, bool compound)
static void page_remove_anon_compound_rmap(struct page *page)
void page_remove_rmap(struct page *page, bool compound)
static bool try_to_unmap_one(struct page *page, struct vm_area_struct *vma, unsigned long address, void *arg)
bool is_vma_temporary_stack(struct vm_area_struct *vma)
static bool invalid_migration_vma(struct vm_area_struct *vma, void *arg)
static int page_mapcount_is_zero(struct page *page)
bool try_to_unmap(struct page *page, enum ttu_flags flags)
static int page_not_mapped(struct page *page)
void try_to_munlock(struct page *page)
void __put_anon_vma(struct anon_vma *anon_vma)
static struct anon_vma *rmap_walk_anon_lock(struct page *page, struct rmap_walk_control *rwc)
static void rmap_walk_anon(struct page *page, struct rmap_walk_control *rwc, bool locked)
static void rmap_walk_file(struct page *page, struct rmap_walk_control *rwc, bool locked)
void rmap_walk(struct page *page, struct rmap_walk_control *rwc)
void rmap_walk_locked(struct page *page, struct rmap_walk_control *rwc)
void hugepage_add_anon_rmap(struct page *page, struct vm_area_struct *vma, unsigned long address)
void hugepage_add_new_anon_rmap(struct page *page, struct vm_area_struct *vma, unsigned long address)
\n
     29 struct page *page
     20 struct vm_area_struct *vma
     11 unsigned long address
      6 void *arg
      6 struct mm_struct *mm
      5 struct rmap_walk_control *rwc
      5 struct anon_vma *anon_vma
      5 bool compound
      4 void
      3 enum ttu_flags flags
      2 struct anon_vma *root
      2 bool writable
      2 bool locked
      1 void *data
      1 unsigned long *vm_flags
      1 struct vm_area_struct *src
      1 struct vm_area_struct *pvma
      1 struct vm_area_struct *dst
      1 struct mem_cgroup *memcg
      1 struct anon_vma_chain *avc
      1 struct anon_vma_chain *anon_vma_chain
      1 page_mkclean
      1 int is_locked
      1 int flags
      1 int exclusive
      1 gfp_t gfp
      1 
