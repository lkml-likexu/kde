
\n
static inline bool can_madv_dontneed_vma(struct vm_area_struct *vma)
static inline unsigned long ra_submit(struct file_ra_state *ra, struct address_space *mapping, struct file *filp)
static inline void set_page_refcounted(struct page *page)
static inline unsigned long __find_buddy_pfn(unsigned long page_pfn, unsigned int order)
static inline struct page *pageblock_pfn_to_page(unsigned long start_pfn, unsigned long end_pfn, struct zone *zone)
static inline unsigned int page_order(struct page *page)
static inline bool is_cow_mapping(vm_flags_t flags)
static inline bool is_exec_mapping(vm_flags_t flags)
static inline bool is_stack_mapping(vm_flags_t flags)
static inline bool is_data_mapping(vm_flags_t flags)
extern long populate_vma_page_range(struct vm_area_struct *vma, unsigned long start, unsigned long end, int *nonblocking)
; extern void munlock_vma_pages_range(struct vm_area_struct *vma, unsigned long start, unsigned long end)
; static inline void munlock_vma_pages_all(struct vm_area_struct *vma)
static inline void mlock_migrate_page(struct page *newpage, struct page *page)
static inline unsigned long __vma_address(struct page *page, struct vm_area_struct *vma)
static inline unsigned long vma_address(struct page *page, struct vm_area_struct *vma)
static inline struct page *mem_map_offset(struct page *base, int offset)
static inline struct page *mem_map_next(struct page *iter, struct page *base, int offset)
static inline void mminit_dprintk(enum mminit_level level, const char *prefix, const char *fmt, ...)
static inline void mminit_verify_pageflags_layout(void)
static inline void mminit_verify_zonelist(void)
extern void mminit_validate_memmodel_limits(unsigned long *start_pfn, unsigned long *end_pfn)
; static inline void mminit_validate_memmodel_limits(unsigned long *start_pfn, unsigned long *end_pfn)
extern int node_reclaim(struct pglist_data *, gfp_t, unsigned int)
; static inline int node_reclaim(struct pglist_data *pgdat, gfp_t mask, unsigned int order)
void try_to_unmap_flush(void)
; void try_to_unmap_flush_dirty(void)
; void flush_tlb_batched_pending(struct mm_struct *mm)
; static inline void try_to_unmap_flush(void)
void try_to_unmap_flush(void)
; void try_to_unmap_flush_dirty(void)
; void flush_tlb_batched_pending(struct mm_struct *mm)
; static inline void try_to_unmap_flush(void)
} static inline void try_to_unmap_flush_dirty(void)
void try_to_unmap_flush(void)
; void try_to_unmap_flush_dirty(void)
; void flush_tlb_batched_pending(struct mm_struct *mm)
; static inline void try_to_unmap_flush(void)
} static inline void try_to_unmap_flush_dirty(void)
} static inline void flush_tlb_batched_pending(struct mm_struct *mm)
static inline bool is_migrate_highatomic(enum migratetype migratetype)
static inline bool is_migrate_highatomic_page(struct page *page)
\n
     13 void
      6 struct vm_area_struct *vma
      6 struct page *page
      4 vm_flags_t flags
      4 struct mm_struct *mm
      2 unsigned long *start_pfn
      2 unsigned long start
      2 unsigned long *end_pfn
      2 unsigned long end
      2 unsigned int order
      2 struct page *base
      2 int offset
      1 unsigned long start_pfn
      1 unsigned long page_pfn
      1 unsigned long end_pfn
      1 unsigned int
      1 struct zone *zone
      1 struct pglist_data *pgdat
      1 struct pglist_data *
      1 struct page *newpage
      1 struct page *iter
      1 struct file_ra_state *ra
      1 struct file *filp
      1 struct address_space *mapping
      1 int *nonblocking
      1 gfp_t mask
      1 gfp_t
      1 enum mminit_level level
      1 enum migratetype migratetype
      1 const char *prefix
      1 const char *fmt
      1 ...
