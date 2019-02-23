
\n
static inline int prepare_hugepage_range(struct file *file, unsigned long addr, unsigned long len)
static inline void arch_clear_hugepage_flags(struct page *page)
static inline void huge_pte_clear(struct mm_struct *mm, unsigned long addr, pte_t *ptep, unsigned long sz)
static inline void huge_ptep_clear_flush(struct vm_area_struct *vma, unsigned long address, pte_t *ptep)
static inline int huge_ptep_set_access_flags(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep, pte_t pte, int dirty)
static inline void huge_ptep_set_wrprotect(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
static inline pte_t mk_huge_pte(struct page *page, pgprot_t pgprot)
static inline int huge_pte_none(pte_t pte)
static inline int huge_pte_write(pte_t pte)
static inline int huge_pte_dirty(pte_t pte)
static inline pte_t huge_pte_mkwrite(pte_t pte)
static inline pte_t huge_pte_mkdirty(pte_t pte)
static inline pte_t huge_pte_wrprotect(pte_t pte)
static inline pte_t huge_pte_modify(pte_t pte, pgprot_t newprot)
\n
      8 pte_t pte
      4 unsigned long addr
      4 pte_t *ptep
      2 struct vm_area_struct *vma
      2 struct page *page
      2 struct mm_struct *mm
      1 unsigned long sz
      1 unsigned long len
      1 unsigned long address
      1 struct file *file
      1 pgprot_t pgprot
      1 pgprot_t newprot
      1 int dirty
