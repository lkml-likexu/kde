
\n
static inline void get_anon_vma(struct anon_vma *anon_vma)
static inline void put_anon_vma(struct anon_vma *anon_vma)
static inline void anon_vma_lock_write(struct anon_vma *anon_vma)
static inline void anon_vma_unlock_write(struct anon_vma *anon_vma)
static inline void anon_vma_lock_read(struct anon_vma *anon_vma)
static inline void anon_vma_unlock_read(struct anon_vma *anon_vma)
static inline int anon_vma_prepare(struct vm_area_struct *vma)
static inline void anon_vma_merge(struct vm_area_struct *vma, struct vm_area_struct *next)
static inline void page_dup_rmap(struct page *page, bool compound)
static inline void page_vma_mapped_walk_done(struct page_vma_mapped_walk *pvmw)
static inline int page_referenced(struct page *page, int is_locked, struct mem_cgroup *memcg, unsigned long *vm_flags)
static inline int page_mkclean(struct page *page)
\n
      6 struct anon_vma *anon_vma
      3 struct page *page
      2 struct vm_area_struct *vma
      1 unsigned long *vm_flags
      1 struct vm_area_struct *next
      1 struct page_vma_mapped_walk *pvmw
      1 struct mem_cgroup *memcg
      1 int is_locked
      1 bool compound
