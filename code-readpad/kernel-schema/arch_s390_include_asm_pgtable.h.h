
\n
static inline void update_page_count(int level, long count)
static inline int is_module_addr(void *addr)
static inline bool mm_p4d_folded(struct mm_struct *mm)
static inline bool mm_pud_folded(struct mm_struct *mm)
static inline bool mm_pmd_folded(struct mm_struct *mm)
static inline int mm_has_pgste(struct mm_struct *mm)
static inline int mm_alloc_pgste(struct mm_struct *mm)
define mm_forbids_zeropage mm_has_pgste static inline int mm_uses_skeys(struct mm_struct *mm)
static inline void csp(unsigned int *ptr, unsigned int old, unsigned int new)
static inline void cspg(unsigned long *ptr, unsigned long old, unsigned long new)
static inline void crdte(unsigned long old, unsigned long new, unsigned long table, unsigned long dtt, unsigned long address, unsigned long asce)
static inline int pgd_folded(pgd_t pgd)
static inline int pgd_present(pgd_t pgd)
static inline int pgd_none(pgd_t pgd)
static inline int pgd_bad(pgd_t pgd)
static inline unsigned long pgd_pfn(pgd_t pgd)
static inline int p4d_folded(p4d_t p4d)
static inline int p4d_present(p4d_t p4d)
static inline int p4d_none(p4d_t p4d)
static inline unsigned long p4d_pfn(p4d_t p4d)
static inline int pud_folded(pud_t pud)
static inline int pud_present(pud_t pud)
static inline int pud_none(pud_t pud)
static inline int pud_large(pud_t pud)
static inline unsigned long pud_pfn(pud_t pud)
static inline int pmd_large(pmd_t pmd)
static inline int pmd_bad(pmd_t pmd)
static inline int pud_bad(pud_t pud)
static inline int p4d_bad(p4d_t p4d)
static inline int pmd_present(pmd_t pmd)
static inline int pmd_none(pmd_t pmd)
static inline unsigned long pmd_pfn(pmd_t pmd)
define pmd_write pmd_write static inline int pmd_write(pmd_t pmd)
static inline int pmd_dirty(pmd_t pmd)
static inline int pmd_young(pmd_t pmd)
static inline int pte_present(pte_t pte)
static inline int pte_none(pte_t pte)
static inline int pte_swap(pte_t pte)
static inline int pte_special(pte_t pte)
define __HAVE_ARCH_PTE_SAME static inline int pte_same(pte_t a, pte_t b)
static inline int pte_protnone(pte_t pte)
static inline int pmd_protnone(pmd_t pmd)
static inline int pte_soft_dirty(pte_t pte)
static inline pte_t pte_mksoft_dirty(pte_t pte)
static inline pte_t pte_clear_soft_dirty(pte_t pte)
static inline int pmd_soft_dirty(pmd_t pmd)
static inline pmd_t pmd_mksoft_dirty(pmd_t pmd)
static inline pmd_t pmd_clear_soft_dirty(pmd_t pmd)
static inline int pte_write(pte_t pte)
static inline int pte_dirty(pte_t pte)
static inline int pte_young(pte_t pte)
define __HAVE_ARCH_PTE_UNUSED static inline int pte_unused(pte_t pte)
static inline void pgd_clear(pgd_t *pgd)
static inline void p4d_clear(p4d_t *p4d)
static inline void pud_clear(pud_t *pud)
static inline void pmd_clear(pmd_t *pmdp)
static inline void pte_clear(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
static inline pte_t pte_modify(pte_t pte, pgprot_t newprot)
static inline pte_t pte_wrprotect(pte_t pte)
static inline pte_t pte_mkwrite(pte_t pte)
static inline pte_t pte_mkclean(pte_t pte)
static inline pte_t pte_mkdirty(pte_t pte)
static inline pte_t pte_mkold(pte_t pte)
static inline pte_t pte_mkyoung(pte_t pte)
static inline pte_t pte_mkspecial(pte_t pte)
static inline pte_t pte_mkhuge(pte_t pte)
static inline void __ptep_ipte(unsigned long address, pte_t *ptep, unsigned long opt, unsigned long asce, int local)
static inline void __ptep_ipte_range(unsigned long address, int nr, pte_t *ptep, int local)
define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG static inline int ptep_test_and_clear_young(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep)
define __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH static inline int ptep_clear_flush_young(struct vm_area_struct *vma, unsigned long address, pte_t *ptep)
define __HAVE_ARCH_PTEP_GET_AND_CLEAR static inline pte_t ptep_get_and_clear(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
define __HAVE_ARCH_PTEP_CLEAR_FLUSH static inline pte_t ptep_clear_flush(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep)
define __HAVE_ARCH_PTEP_GET_AND_CLEAR_FULL static inline pte_t ptep_get_and_clear_full(struct mm_struct *mm, unsigned long addr, pte_t *ptep, int full)
define __HAVE_ARCH_PTEP_SET_WRPROTECT static inline void ptep_set_wrprotect(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
define __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS static inline int ptep_set_access_flags(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep, pte_t entry, int dirty)
static inline void set_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t entry)
static inline pte_t mk_pte_phys(unsigned long physpage, pgprot_t pgprot)
static inline pte_t mk_pte(struct page *page, pgprot_t pgprot)
static inline p4d_t *p4d_offset(pgd_t *pgd, unsigned long address)
static inline pud_t *pud_offset(p4d_t *p4d, unsigned long address)
static inline pmd_t *pmd_offset(pud_t *pud, unsigned long address)
static inline pmd_t pmd_wrprotect(pmd_t pmd)
static inline pmd_t pmd_mkwrite(pmd_t pmd)
static inline pmd_t pmd_mkclean(pmd_t pmd)
static inline pmd_t pmd_mkdirty(pmd_t pmd)
static inline pud_t pud_wrprotect(pud_t pud)
static inline pud_t pud_mkwrite(pud_t pud)
static inline pud_t pud_mkclean(pud_t pud)
static inline pud_t pud_mkdirty(pud_t pud)
static inline unsigned long massage_pgprot_pmd(pgprot_t pgprot)
static inline pmd_t pmd_mkyoung(pmd_t pmd)
static inline pmd_t pmd_mkold(pmd_t pmd)
static inline pmd_t pmd_modify(pmd_t pmd, pgprot_t newprot)
static inline pmd_t mk_pmd_phys(unsigned long physpage, pgprot_t pgprot)
static inline void __pmdp_csp(pmd_t *pmdp)
static inline void __pmdp_idte(unsigned long addr, pmd_t *pmdp, unsigned long opt, unsigned long asce, int local)
static inline void __pudp_idte(unsigned long addr, pud_t *pudp, unsigned long opt, unsigned long asce, int local)
define__HAVE_ARCH_PMDP_SET_ACCESS_FLAGS static inline int pmdp_set_access_flags(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmdp, pmd_t entry, int dirty)
define __HAVE_ARCH_PMDP_TEST_AND_CLEAR_YOUNG static inline int pmdp_test_and_clear_young(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmdp)
define __HAVE_ARCH_PMDP_CLEAR_YOUNG_FLUSH static inline int pmdp_clear_flush_young(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmdp)
static inline void set_pmd_at(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp, pmd_t entry)
static inline pmd_t pmd_mkhuge(pmd_t pmd)
define __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR static inline pmd_t pmdp_huge_get_and_clear(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp)
define __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR_FULL static inline pmd_t pmdp_huge_get_and_clear_full(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp, int full)
define __HAVE_ARCH_PMDP_HUGE_CLEAR_FLUSH static inline pmd_t pmdp_huge_clear_flush(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmdp)
define __HAVE_ARCH_PMDP_INVALIDATE static inline pmd_t pmdp_invalidate(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmdp)
define __HAVE_ARCH_PMDP_SET_WRPROTECT static inline void pmdp_set_wrprotect(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp)
static inline pmd_t pmdp_collapse_flush(struct vm_area_struct *vma, unsigned long address, pmd_t *pmdp)
static inline int pmd_trans_huge(pmd_t pmd)
define has_transparent_hugepage has_transparent_hugepage static inline int has_transparent_hugepage(void)
static inline pte_t mk_swap_pte(unsigned long type, unsigned long offset)
static inline unsigned long __swp_type(swp_entry_t entry)
static inline unsigned long __swp_offset(swp_entry_t entry)
static inline swp_entry_t __swp_entry(unsigned long type, unsigned long offset)
\n
     21 pte_t pte
     21 pmd_t pmd
     19 unsigned long addr
     15 struct mm_struct *mm
     13 pmd_t *pmdp
     11 pte_t *ptep
     10 struct vm_area_struct *vma
     10 pud_t pud
      8 unsigned long address
      5 pgd_t pgd
      5 p4d_t p4d
      4 unsigned long asce
      4 pgprot_t pgprot
      4 int local
      3 unsigned long opt
      2 unsigned long type
      2 unsigned long physpage
      2 unsigned long old
      2 unsigned long offset
      2 unsigned long new
      2 swp_entry_t entry
      2 pud_t *pud
      2 pte_t entry
      2 pmd_t entry
      2 pgprot_t newprot
      2 pgd_t *pgd
      2 p4d_t *p4d
      2 int full
      2 int dirty
      1 void *addr
      1 void
      1 unsigned long table
      1 unsigned long *ptr
      1 unsigned long dtt
      1 unsigned int *ptr
      1 unsigned int old
      1 unsigned int new
      1 struct page *page
      1 pud_t *pudp
      1 pte_t b
      1 pte_t a
      1 long count
      1 int nr
      1 int level
