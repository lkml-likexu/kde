
\n
static inline int gup_pte_range(pmd_t *pmdp, pmd_t pmd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static inline int gup_huge_pmd(pmd_t *pmdp, pmd_t pmd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static inline int gup_pmd_range(pud_t *pudp, pud_t pud, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_huge_pud(pud_t *pudp, pud_t pud, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static inline int gup_pud_range(p4d_t *p4dp, p4d_t p4d, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static inline int gup_p4d_range(pgd_t *pgdp, pgd_t pgd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
int __get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
int get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
\n
      8 struct page **pages
      8 int write
      6 unsigned long end
      6 unsigned long addr
      6 int *nr
      2 unsigned long start
      2 pud_t *pudp
      2 pud_t pud
      2 pmd_t *pmdp
      2 pmd_t pmd
      2 int nr_pages
      1 pgd_t *pgdp
      1 pgd_t pgd
      1 p4d_t *p4dp
      1 p4d_t p4d
