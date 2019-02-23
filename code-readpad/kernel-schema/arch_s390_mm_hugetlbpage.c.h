
\n
static inline unsigned long __pte_to_rste(pte_t pte)
static inline pte_t __rste_to_pte(unsigned long rste)
static void clear_huge_pte_skeys(struct mm_struct *mm, unsigned long rste)
void set_huge_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t pte)
pte_t huge_ptep_get(pte_t *ptep)
pte_t huge_ptep_get_and_clear(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
pte_t *huge_pte_alloc(struct mm_struct *mm, unsigned long addr, unsigned long sz)
pte_t *huge_pte_offset(struct mm_struct *mm, unsigned long addr, unsigned long sz)
int pmd_huge(pmd_t pmd)
int pud_huge(pud_t pud)
struct page * follow_huge_pud(struct mm_struct *mm, unsigned long address, pud_t *pud, int flags)
static __init int setup_hugepagesz(char *opt)
\n
      6 struct mm_struct *mm
      4 unsigned long addr
      3 pte_t *ptep
      2 unsigned long sz
      2 unsigned long rste
      2 pte_t pte
      1 unsigned long address
      1 pud_t *pud
      1 pud_t pud
      1 pmd_t pmd
      1 int flags
      1 char *opt
