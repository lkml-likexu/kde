
EXPORT_SYMBOL_GPL(fixup_user_fault);
\n
static struct page *no_page_table(struct vm_area_struct *vma, unsigned int flags)
static int follow_pfn_pte(struct vm_area_struct *vma, unsigned long address, pte_t *pte, unsigned int flags)
static inline bool can_follow_write_pte(pte_t pte, unsigned int flags)
static struct page *follow_page_pte(struct vm_area_struct *vma, unsigned long address, pmd_t *pmd, unsigned int flags, struct dev_pagemap **pgmap)
static struct page *follow_pmd_mask(struct vm_area_struct *vma, unsigned long address, pud_t *pudp, unsigned int flags, struct follow_page_context *ctx)
static struct page *follow_pud_mask(struct vm_area_struct *vma, unsigned long address, p4d_t *p4dp, unsigned int flags, struct follow_page_context *ctx)
static struct page *follow_p4d_mask(struct vm_area_struct *vma, unsigned long address, pgd_t *pgdp, unsigned int flags, struct follow_page_context *ctx)
struct page *follow_page_mask(struct vm_area_struct *vma, unsigned long address, unsigned int flags, struct follow_page_context *ctx)
struct page *follow_page(struct vm_area_struct *vma, unsigned long address, unsigned int foll_flags)
static int get_gate_page(struct mm_struct *mm, unsigned long address, unsigned int gup_flags, struct vm_area_struct **vma, struct page **page)
static int faultin_page(struct task_struct *tsk, struct vm_area_struct *vma, unsigned long address, unsigned int *flags, int *nonblocking)
static int check_vma_flags(struct vm_area_struct *vma, unsigned long gup_flags)
static long __get_user_pages(struct task_struct *tsk, struct mm_struct *mm, unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, struct vm_area_struct **vmas, int *nonblocking)
static bool vma_permits_fault(struct vm_area_struct *vma, unsigned int fault_flags)
int fixup_user_fault(struct task_struct *tsk, struct mm_struct *mm, unsigned long address, unsigned int fault_flags, bool *unlocked)
static __always_inline long __get_user_pages_locked(struct task_struct *tsk, struct mm_struct *mm, unsigned long start, unsigned long nr_pages, struct page **pages, struct vm_area_struct **vmas, int *locked, unsigned int flags)
long get_user_pages_locked(unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, int *locked)
long get_user_pages_unlocked(unsigned long start, unsigned long nr_pages, struct page **pages, unsigned int gup_flags)
long get_user_pages_remote(struct task_struct *tsk, struct mm_struct *mm, unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, struct vm_area_struct **vmas, int *locked)
long get_user_pages(unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, struct vm_area_struct **vmas)
long get_user_pages_longterm(unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, struct vm_area_struct **vmas_arg)
long populate_vma_page_range(struct vm_area_struct *vma, unsigned long start, unsigned long end, int *nonblocking)
int __mm_populate(unsigned long start, unsigned long len, int ignore_errors)
struct page *get_dump_page(unsigned long addr)
static inline pte_t gup_get_pte(pte_t *ptep)
static void undo_dev_pagemap(int *nr, int nr_start, struct page **pages)
static int gup_pte_range(pmd_t pmd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_pte_range(pmd_t pmd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int __gup_device_huge(unsigned long pfn, unsigned long addr, unsigned long end, struct page **pages, int *nr)
static int __gup_device_huge_pmd(pmd_t orig, pmd_t *pmdp, unsigned long addr, unsigned long end, struct page **pages, int *nr)
static int __gup_device_huge_pud(pud_t orig, pud_t *pudp, unsigned long addr, unsigned long end, struct page **pages, int *nr)
undo_dev_pagemap(nr, nr_start, pages)
; return 0;}return 1; } static int __gup_device_huge_pmd(pmd_t orig, pmd_t *pmdp, unsigned long addr, unsigned long end, struct page **pages, int *nr)
static int __gup_device_huge_pud(pud_t pud, pud_t *pudp, unsigned long addr, unsigned long end, struct page **pages, int *nr)
static int gup_huge_pmd(pmd_t orig, pmd_t *pmdp, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_huge_pud(pud_t orig, pud_t *pudp, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_huge_pgd(pgd_t orig, pgd_t *pgdp, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_pmd_range(pud_t pud, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_pud_range(p4d_t p4d, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static int gup_p4d_range(pgd_t pgd, unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
static void gup_pgd_range(unsigned long addr, unsigned long end, int write, struct page **pages, int *nr)
bool gup_fast_permitted(unsigned long start, int nr_pages, int write)
int __get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
int get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
\n
     24 struct page **pages
     15 unsigned long end
     15 unsigned long addr
     15 int *nr
     12 unsigned long start
     12 struct vm_area_struct *vma
     12 int write
     10 unsigned long address
      9 unsigned int flags
      7 unsigned long nr_pages
      7 unsigned int gup_flags
      5 struct task_struct *tsk
      5 struct mm_struct *mm
      4 struct vm_area_struct **vmas
      4 struct follow_page_context *ctx
      4 pud_t *pudp
      3 pmd_t *pmdp
      3 pmd_t orig
      3 int nr_pages
      3 int *nonblocking
      3 int *locked
      2 unsigned int fault_flags
      2 pud_t pud
      2 pud_t orig
      2 pmd_t pmd
      2 pgd_t *pgdp
      1 unsigned long pfn
      1 unsigned long len
      1 unsigned long gup_flags
      1 unsigned int foll_flags
      1 unsigned int *flags
      1 struct vm_area_struct **vmas_arg
      1 struct vm_area_struct **vma
      1 struct page **page
      1 struct dev_pagemap **pgmap
      1 pte_t *ptep
      1 pte_t *pte
      1 pte_t pte
      1 pmd_t *pmd
      1 pgd_t pgd
      1 pgd_t orig
      1 pages
      1 p4d_t *p4dp
      1 p4d_t p4d
      1 nr_start
      1 nr
      1 int nr_start
      1 int ignore_errors
      1 fixup_user_fault
      1 bool *unlocked
