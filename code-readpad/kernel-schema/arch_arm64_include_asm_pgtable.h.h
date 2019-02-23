
\n
static inline pte_t clear_pte_bit(pte_t pte, pgprot_t prot)
static inline pte_t set_pte_bit(pte_t pte, pgprot_t prot)
static inline pte_t pte_wrprotect(pte_t pte)
static inline pte_t pte_mkwrite(pte_t pte)
static inline pte_t pte_mkclean(pte_t pte)
static inline pte_t pte_mkdirty(pte_t pte)
static inline pte_t pte_mkold(pte_t pte)
static inline pte_t pte_mkyoung(pte_t pte)
static inline pte_t pte_mkspecial(pte_t pte)
static inline pte_t pte_mkcont(pte_t pte)
static inline pte_t pte_mknoncont(pte_t pte)
static inline pte_t pte_mkpresent(pte_t pte)
static inline pmd_t pmd_mkcont(pmd_t pmd)
static inline void set_pte(pte_t *ptep, pte_t pte)
static inline void set_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t pte)
define __HAVE_ARCH_PTE_SAME static inline int pte_same(pte_t pte_a, pte_t pte_b)
static inline pte_t pgd_pte(pgd_t pgd)
static inline pte_t pud_pte(pud_t pud)
static inline pud_t pte_pud(pte_t pte)
static inline pmd_t pud_pmd(pud_t pud)
static inline pte_t pmd_pte(pmd_t pmd)
static inline pmd_t pte_pmd(pte_t pte)
static inline pgprot_t mk_sect_prot(pgprot_t prot)
static inline int pte_protnone(pte_t pte)
static inline int pmd_protnone(pmd_t pmd)
static inline bool in_swapper_pgdir(void *addr)
static inline void set_pmd(pmd_t *pmdp, pmd_t pmd)
static inline void pmd_clear(pmd_t *pmdp)
static inline phys_addr_t pmd_page_paddr(pmd_t pmd)
static inline void set_pud(pud_t *pudp, pud_t pud)
static inline void pud_clear(pud_t *pudp)
static inline phys_addr_t pud_page_paddr(pud_t pud)
static inline void set_pgd(pgd_t *pgdp, pgd_t pgd)
static inline void pgd_clear(pgd_t *pgdp)
static inline phys_addr_t pgd_page_paddr(pgd_t pgd)
static inline pte_t pte_modify(pte_t pte, pgprot_t newprot)
static inline pmd_t pmd_modify(pmd_t pmd, pgprot_t newprot)
define __HAVE_ARCH_PMDP_SET_ACCESS_FLAGS static inline int pmdp_set_access_flags(struct vm_area_struct *vma, unsigned long address, pmd_t *pmdp, pmd_t entry, int dirty)
define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG static inline int __ptep_test_and_clear_young(pte_t *ptep)
static inline int ptep_test_and_clear_young(struct vm_area_struct *vma, unsigned long address, pte_t *ptep)
define __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH static inline int ptep_clear_flush_young(struct vm_area_struct *vma, unsigned long address, pte_t *ptep)
define __HAVE_ARCH_PMDP_TEST_AND_CLEAR_YOUNG static inline int pmdp_test_and_clear_young(struct vm_area_struct *vma, unsigned long address, pmd_t *pmdp)
define __HAVE_ARCH_PTEP_GET_AND_CLEAR static inline pte_t ptep_get_and_clear(struct mm_struct *mm, unsigned long address, pte_t *ptep)
define __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR static inline pmd_t pmdp_huge_get_and_clear(struct mm_struct *mm, unsigned long address, pmd_t *pmdp)
define __HAVE_ARCH_PTEP_SET_WRPROTECT static inline void ptep_set_wrprotect(struct mm_struct *mm, unsigned long address, pte_t *ptep)
define __HAVE_ARCH_PMDP_SET_WRPROTECT static inline void pmdp_set_wrprotect(struct mm_struct *mm, unsigned long address, pmd_t *pmdp)
define pmdp_establish pmdp_establish static inline pmd_t pmdp_establish(struct vm_area_struct *vma, unsigned long address, pmd_t *pmdp, pmd_t pmd)
static inline void update_mmu_cache(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep)
\n
     18 pte_t pte
      9 unsigned long address
      8 pte_t *ptep
      7 pmd_t *pmdp
      7 pmd_t pmd
      6 struct vm_area_struct *vma
      5 struct mm_struct *mm
      4 pud_t pud
      3 pgprot_t prot
      3 pgd_t pgd
      2 unsigned long addr
      2 pud_t *pudp
      2 pgprot_t newprot
      2 pgd_t *pgdp
      1 void *addr
      1 pte_t pte_b
      1 pte_t pte_a
      1 pmd_t entry
      1 int dirty
