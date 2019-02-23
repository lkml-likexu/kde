
\n
define is_hugepd(hugepd)
(0)
static inline int gup_huge_pd(hugepd_t hugepd, unsigned long addr, unsigned pdshift, unsigned long end, int write, struct page **pages, int *nr)
static inline void reset_vma_resv_huge_pages(struct vm_area_struct *vma)
static inline unsigned long hugetlb_total_pages(void)
static inline int huge_pmd_unshare(struct mm_struct *mm, unsigned long *addr, pte_t *ptep)
static inline void adjust_range_if_pmd_sharing_possible( struct vm_area_struct *vma, unsigned long *start, unsigned long *end)
define follow_huge_addr(mm, addr, write)
ERR_PTR(-EINVAL)
static inline void hugetlb_report_meminfo(struct seq_file *m)
define follow_huge_addr(mm, addr, write)
ERR_PTR(-EINVAL)
static inline void hugetlb_report_meminfo(struct seq_file *m)
}define hugetlb_report_node_meminfo(n, buf)
0 static inline void hugetlb_show_meminfo(void)
static inline bool isolate_huge_page(struct page *page, struct list_head *list)
static inline unsigned long hugetlb_change_protection(struct vm_area_struct *vma, unsigned long address, unsigned long end, pgprot_t newprot)
static inline void __unmap_hugepage_range_final(struct mmu_gather *tlb, struct vm_area_struct *vma, unsigned long start, unsigned long end, struct page *ref_page)
static inline void __unmap_hugepage_range(struct mmu_gather *tlb, struct vm_area_struct *vma, unsigned long start, unsigned long end, struct page *ref_page)
static inline int pgd_write(pgd_t pgd)
static inline struct hugetlbfs_sb_info *HUGETLBFS_SB(struct super_block *sb)
static inline struct hugetlbfs_inode_info *HUGETLBFS_I(struct inode *inode)
static inline bool is_file_hugepages(struct file *file)
define is_file_hugepages(file)
false static inline struct file * hugetlb_file_setup(const char *name, size_t size, vm_flags_t acctflag, struct user_struct **user, int creat_flags, int page_size_log)
static inline struct hstate *hstate_inode(struct inode *i)
static inline struct hstate *hstate_file(struct file *f)
static inline struct hstate *hstate_sizelog(int page_size_log)
static inline struct hstate *hstate_vma(struct vm_area_struct *vma)
static inline unsigned long huge_page_size(struct hstate *h)
static inline unsigned long huge_page_mask(struct hstate *h)
static inline unsigned int huge_page_order(struct hstate *h)
static inline unsigned huge_page_shift(struct hstate *h)
static inline bool hstate_is_gigantic(struct hstate *h)
static inline unsigned int pages_per_huge_page(struct hstate *h)
static inline unsigned int blocks_per_huge_page(struct hstate *h)
static inline pte_t arch_make_huge_pte(pte_t entry, struct vm_area_struct *vma, struct page *page, int writable)
static inline struct hstate *page_hstate(struct page *page)
static inline unsigned hstate_index_to_shift(unsigned index)
static inline int hstate_index(struct hstate *h)
static inline pgoff_t basepage_index(struct page *page)
extern int dissolve_free_huge_page(struct page *page)
; extern int dissolve_free_huge_pages(unsigned long start_pfn, unsigned long end_pfn)
; static inline bool hugepage_migration_supported(struct hstate *h)
static inline spinlock_t *huge_pte_lockptr(struct hstate *h, struct mm_struct *mm, pte_t *pte)
static inline void hugetlb_count_add(long l, struct mm_struct *mm)
static inline void hugetlb_count_sub(long l, struct mm_struct *mm)
static inline void set_huge_swap_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t pte, unsigned long sz)
static inline void set_huge_swap_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t pte, unsigned long sz)
set_huge_pte_at(mm, addr, ptep, pte)
; }endifdefine alloc_huge_page(v, a, r)
NULLdefine alloc_huge_page_node(h, nid)
NULLdefine alloc_huge_page_nodemask(h, preferred_nid, nmask)
NULLdefine alloc_huge_page_vma(h, vma, address)
NULLdefine alloc_bootmem_huge_page(h)
NULLdefine hstate_file(f)
NULLdefine hstate_sizelog(s)
NULLdefine hstate_vma(v)
NULLdefine hstate_inode(i)
NULLdefine page_hstate(page)
NULLdefine huge_page_size(h)
PAGE_SIZEdefine huge_page_mask(h)
PAGE_MASKdefine vma_kernel_pagesize(v)
PAGE_SIZEdefine vma_mmu_pagesize(v)
PAGE_SIZEdefine huge_page_order(h)
0define huge_page_shift(h)
PAGE_SHIFT static inline bool hstate_is_gigantic(struct hstate *h)
static inline unsigned int pages_per_huge_page(struct hstate *h)
static inline unsigned hstate_index_to_shift(unsigned index)
static inline int hstate_index(struct hstate *h)
static inline pgoff_t basepage_index(struct page *page)
static inline int dissolve_free_huge_page(struct page *page)
static inline int dissolve_free_huge_pages(unsigned long start_pfn, unsigned long end_pfn)
static inline bool hugepage_migration_supported(struct hstate *h)
static inline spinlock_t *huge_pte_lockptr(struct hstate *h, struct mm_struct *mm, pte_t *pte)
static inline void hugetlb_report_usage(struct seq_file *f, struct mm_struct *m)
static inline void hugetlb_count_sub(long l, struct mm_struct *mm)
static inline void set_huge_swap_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t pte, unsigned long sz)
static inline spinlock_t *huge_pte_lock(struct hstate *h, struct mm_struct *mm, pte_t *pte)
\n
     16 struct hstate *h
     10 struct mm_struct *mm
      8 h
      7 struct vm_area_struct *vma
      7 struct page *page
      4 v
      4 unsigned long end
      4 unsigned long addr
      4 pte_t *ptep
      3 unsigned long sz
      3 pte_t *pte
      3 pte_t pte
      3 mm
      3 long l
      3 addr
      2 write
      2 void
      2 unsigned long start_pfn
      2 unsigned long start
      2 unsigned long end_pfn
      2 unsigned index
      2 struct seq_file *m
      2 struct page *ref_page
      2 struct mmu_gather *tlb
      2 int page_size_log
      2 -EINVAL
      1 vm_flags_t acctflag
      1 vma
      1 unsigned pdshift
      1 unsigned long *start
      1 unsigned long *end
      1 unsigned long address
      1 unsigned long *addr
      1 struct user_struct **user
      1 struct super_block *sb
      1 struct seq_file *f
      1 struct page **pages
      1 struct mm_struct *m
      1 struct list_head *list
      1 struct inode *inode
      1 struct inode *i
      1 struct file *file
      1 struct file *f
      1 size_t size
      1 s
      1 r
      1 pte_t entry
      1 ptep
      1 pte
      1 preferred_nid
      1 pgprot_t newprot
      1 pgd_t pgd
      1 page
      1 nmask
      1 nid
      1 n
      1 int write
      1 int writable
      1 int *nr
      1 int creat_flags
      1 i
      1 hugepd_t hugepd
      1 hugepd
      1 file
      1 f
      1 const char *name
      1 buf
      1 address
      1 a
      1 0
