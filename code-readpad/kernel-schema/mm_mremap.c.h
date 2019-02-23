
\n
static pmd_t *get_old_pmd(struct mm_struct *mm, unsigned long addr)
static pmd_t *alloc_new_pmd(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long addr)
static void take_rmap_locks(struct vm_area_struct *vma)
static void drop_rmap_locks(struct vm_area_struct *vma)
static pte_t move_soft_dirty_pte(pte_t pte)
static void move_ptes(struct vm_area_struct *vma, pmd_t *old_pmd, unsigned long old_addr, unsigned long old_end, struct vm_area_struct *new_vma, pmd_t *new_pmd, unsigned long new_addr, bool need_rmap_locks)
static bool move_normal_pmd(struct vm_area_struct *vma, unsigned long old_addr, unsigned long new_addr, unsigned long old_end, pmd_t *old_pmd, pmd_t *new_pmd)
unsigned long move_page_tables(struct vm_area_struct *vma, unsigned long old_addr, struct vm_area_struct *new_vma, unsigned long new_addr, unsigned long len, bool need_rmap_locks)
static unsigned long move_vma(struct vm_area_struct *vma, unsigned long old_addr, unsigned long old_len, unsigned long new_len, unsigned long new_addr, bool *locked, struct vm_userfaultfd_ctx *uf, struct list_head *uf_unmap)
static struct vm_area_struct *vma_to_resize(unsigned long addr, unsigned long old_len, unsigned long new_len, unsigned long *p)
static unsigned long mremap_to(unsigned long addr, unsigned long old_len, unsigned long new_addr, unsigned long new_len, bool *locked, struct vm_userfaultfd_ctx *uf, struct list_head *uf_unmap_early, struct list_head *uf_unmap)
static int vma_expandable(struct vm_area_struct *vma, unsigned long delta)
SYSCALL_DEFINE5(mremap, unsigned long, addr, unsigned long, old_len, unsigned long, new_len, unsigned long, flags, unsigned long, new_addr)
\n
      8 struct vm_area_struct *vma
      5 unsigned long new_addr
      5 unsigned long
      4 unsigned long old_addr
      4 unsigned long addr
      3 unsigned long old_len
      3 unsigned long new_len
      2 unsigned long old_end
      2 struct vm_userfaultfd_ctx *uf
      2 struct vm_area_struct *new_vma
      2 struct mm_struct *mm
      2 struct list_head *uf_unmap
      2 pmd_t *old_pmd
      2 pmd_t *new_pmd
      2 bool need_rmap_locks
      2 bool *locked
      1 unsigned long *p
      1 unsigned long len
      1 unsigned long delta
      1 struct list_head *uf_unmap_early
      1 pte_t pte
      1 old_len
      1 new_len
      1 new_addr
      1 mremap
      1 flags
      1 addr
