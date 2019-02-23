
\n
static inline pte_t gup_get_pte(pte_t *ptep)
static noinline int gup_pte_range(pmd_t pmd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_pmd_range(pud_t pud, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_pud_range(pgd_t pgd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
int __get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
int get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
\n
      5 struct page **pages
      5 int write
      3 unsigned long end
      3 unsigned long addr
      3 int *nr
      2 unsigned long start
      2 int nr_pages
      1 pud_t pud
      1 pte_t *ptep
      1 pmd_t pmd
      1 pgd_t pgd
