
\n
static inline unsigned long sske_frame(unsigned long addr, unsigned char skey)
void __storage_key_init_range(unsigned long start, unsigned long end)
void arch_report_meminfo(struct seq_file *m)
static void pgt_set(unsigned long *old, unsigned long new, unsigned long addr, unsigned long dtt)
static int walk_pte_level(pmd_t *pmdp, unsigned long addr, unsigned long end, unsigned long flags)
static int split_pmd_page(pmd_t *pmdp, unsigned long addr)
static void modify_pmd_page(pmd_t *pmdp, unsigned long addr, unsigned long flags)
static int walk_pmd_level(pud_t *pudp, unsigned long addr, unsigned long end, unsigned long flags)
static int split_pud_page(pud_t *pudp, unsigned long addr)
static void modify_pud_page(pud_t *pudp, unsigned long addr, unsigned long flags)
static int walk_pud_level(p4d_t *p4d, unsigned long addr, unsigned long end, unsigned long flags)
static int walk_p4d_level(pgd_t *pgd, unsigned long addr, unsigned long end, unsigned long flags)
static int change_page_attr(unsigned long addr, unsigned long end, unsigned long flags)
int __set_memory(unsigned long addr, int numpages, unsigned long flags)
static void ipte_range(pte_t *pte, unsigned long address, int nr)
void __kernel_map_pages(struct page *page, int numpages, int enable)
bool kernel_page_present(struct page *page)
\n
     12 unsigned long addr
      8 unsigned long flags
      6 unsigned long end
      3 pud_t *pudp
      3 pmd_t *pmdp
      2 struct page *page
      2 int numpages
      1 unsigned long start
      1 unsigned long *old
      1 unsigned long new
      1 unsigned long dtt
      1 unsigned long address
      1 unsigned char skey
      1 struct seq_file *m
      1 pte_t *pte
      1 pgd_t *pgd
      1 p4d_t *p4d
      1 int nr
      1 int enable
