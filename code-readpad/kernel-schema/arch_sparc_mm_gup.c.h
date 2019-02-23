
\n
static noinline int gup_pte_range(pmd_t pmd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_huge_pmd(pmd_t *pmdp, pmd_t pmd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_huge_pud(pud_t *pudp, pud_t pud, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_pmd_range(pud_t pud, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_pud_range(pgd_t pgd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
int __get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
int get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
\n
      7 struct page **pages
      7 int write
      5 unsigned long end
      5 unsigned long addr
      5 int *nr
      2 unsigned long start
      2 pud_t pud
      2 pmd_t pmd
      2 int nr_pages
      1 pud_t *pudp
      1 pmd_t *pmdp
      1 pgd_t pgd
