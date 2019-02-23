
EXPORT_SYMBOL_GPL(zap_vma_ptes);
EXPORT_SYMBOL_GPL(apply_to_page_range);
EXPORT_SYMBOL_GPL(handle_mm_fault);
EXPORT_SYMBOL_GPL(generic_access_phys);
EXPORT_SYMBOL_GPL(access_process_vm);
\n
static int __init disable_randmaps(char *s)
static int __init init_zero_pfn(void)
void sync_mm_rss(struct mm_struct *mm)
static void add_mm_counter_fast(struct mm_struct *mm, int member, int val)
define TASK_RSS_EVENTS_THRESH (64)
static void check_sync_rss_stat(struct task_struct *task)
static void check_sync_rss_stat(struct task_struct *task)
static void free_pte_range(struct mmu_gather *tlb, pmd_t *pmd, unsigned long addr)
static inline void free_pmd_range(struct mmu_gather *tlb, pud_t *pud, unsigned long addr, unsigned long end, unsigned long floor, unsigned long ceiling)
static inline void free_pud_range(struct mmu_gather *tlb, p4d_t *p4d, unsigned long addr, unsigned long end, unsigned long floor, unsigned long ceiling)
static inline void free_p4d_range(struct mmu_gather *tlb, pgd_t *pgd, unsigned long addr, unsigned long end, unsigned long floor, unsigned long ceiling)
void free_pgd_range(struct mmu_gather *tlb, unsigned long addr, unsigned long end, unsigned long floor, unsigned long ceiling)
void free_pgtables(struct mmu_gather *tlb, struct vm_area_struct *vma, unsigned long floor, unsigned long ceiling)
int __pte_alloc(struct mm_struct *mm, pmd_t *pmd)
int __pte_alloc_kernel(pmd_t *pmd)
static inline void init_rss_vec(int *rss)
static inline void add_mm_rss_vec(struct mm_struct *mm, int *rss)
static void print_bad_pte(struct vm_area_struct *vma, unsigned long addr, pte_t pte, struct page *page)
struct page *_vm_normal_page(struct vm_area_struct *vma, unsigned long addr, pte_t pte, bool with_public_device)
struct page *vm_normal_page_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t pmd)
static inline unsigned long copy_one_pte(struct mm_struct *dst_mm, struct mm_struct *src_mm, pte_t *dst_pte, pte_t *src_pte, struct vm_area_struct *vma, unsigned long addr, int *rss)
static int copy_pte_range(struct mm_struct *dst_mm, struct mm_struct *src_mm, pmd_t *dst_pmd, pmd_t *src_pmd, struct vm_area_struct *vma, unsigned long addr, unsigned long end)
static inline int copy_pmd_range(struct mm_struct *dst_mm, struct mm_struct *src_mm, pud_t *dst_pud, pud_t *src_pud, struct vm_area_struct *vma, unsigned long addr, unsigned long end)
static inline int copy_pud_range(struct mm_struct *dst_mm, struct mm_struct *src_mm, p4d_t *dst_p4d, p4d_t *src_p4d, struct vm_area_struct *vma, unsigned long addr, unsigned long end)
static inline int copy_p4d_range(struct mm_struct *dst_mm, struct mm_struct *src_mm, pgd_t *dst_pgd, pgd_t *src_pgd, struct vm_area_struct *vma, unsigned long addr, unsigned long end)
int copy_page_range(struct mm_struct *dst_mm, struct mm_struct *src_mm, struct vm_area_struct *vma)
static unsigned long zap_pte_range(struct mmu_gather *tlb, struct vm_area_struct *vma, pmd_t *pmd, unsigned long addr, unsigned long end, struct zap_details *details)
static inline unsigned long zap_pmd_range(struct mmu_gather *tlb, struct vm_area_struct *vma, pud_t *pud, unsigned long addr, unsigned long end, struct zap_details *details)
static inline unsigned long zap_pud_range(struct mmu_gather *tlb, struct vm_area_struct *vma, p4d_t *p4d, unsigned long addr, unsigned long end, struct zap_details *details)
static inline unsigned long zap_p4d_range(struct mmu_gather *tlb, struct vm_area_struct *vma, pgd_t *pgd, unsigned long addr, unsigned long end, struct zap_details *details)
void unmap_page_range(struct mmu_gather *tlb, struct vm_area_struct *vma, unsigned long addr, unsigned long end, struct zap_details *details)
static void unmap_single_vma(struct mmu_gather *tlb, struct vm_area_struct *vma, unsigned long start_addr, unsigned long end_addr, struct zap_details *details)
void unmap_vmas(struct mmu_gather *tlb, struct vm_area_struct *vma, unsigned long start_addr, unsigned long end_addr)
void zap_page_range(struct vm_area_struct *vma, unsigned long start, unsigned long size)
static void zap_page_range_single(struct vm_area_struct *vma, unsigned long address, unsigned long size, struct zap_details *details)
void zap_vma_ptes(struct vm_area_struct *vma, unsigned long address, unsigned long size)
pte_t *__get_locked_pte(struct mm_struct *mm, unsigned long addr, spinlock_t **ptl)
static int insert_page(struct vm_area_struct *vma, unsigned long addr, struct page *page, pgprot_t prot)
int vm_insert_page(struct vm_area_struct *vma, unsigned long addr, struct page *page)
static vm_fault_t insert_pfn(struct vm_area_struct *vma, unsigned long addr, pfn_t pfn, pgprot_t prot, bool mkwrite)
vm_fault_t vmf_insert_pfn_prot(struct vm_area_struct *vma, unsigned long addr, unsigned long pfn, pgprot_t pgprot)
vm_fault_t vmf_insert_pfn(struct vm_area_struct *vma, unsigned long addr, unsigned long pfn)
static bool vm_mixed_ok(struct vm_area_struct *vma, pfn_t pfn)
static vm_fault_t __vm_insert_mixed(struct vm_area_struct *vma, unsigned long addr, pfn_t pfn, bool mkwrite)
vm_fault_t vmf_insert_mixed(struct vm_area_struct *vma, unsigned long addr, pfn_t pfn)
vm_fault_t vmf_insert_mixed_mkwrite(struct vm_area_struct *vma, unsigned long addr, pfn_t pfn)
static int remap_pte_range(struct mm_struct *mm, pmd_t *pmd, unsigned long addr, unsigned long end, unsigned long pfn, pgprot_t prot)
static inline int remap_pmd_range(struct mm_struct *mm, pud_t *pud, unsigned long addr, unsigned long end, unsigned long pfn, pgprot_t prot)
static inline int remap_pud_range(struct mm_struct *mm, p4d_t *p4d, unsigned long addr, unsigned long end, unsigned long pfn, pgprot_t prot)
static inline int remap_p4d_range(struct mm_struct *mm, pgd_t *pgd, unsigned long addr, unsigned long end, unsigned long pfn, pgprot_t prot)
int remap_pfn_range(struct vm_area_struct *vma, unsigned long addr, unsigned long pfn, unsigned long size, pgprot_t prot)
int vm_iomap_memory(struct vm_area_struct *vma, phys_addr_t start, unsigned long len)
static int apply_to_pte_range(struct mm_struct *mm, pmd_t *pmd, unsigned long addr, unsigned long end, pte_fn_t fn, void *data)
static int apply_to_pmd_range(struct mm_struct *mm, pud_t *pud, unsigned long addr, unsigned long end, pte_fn_t fn, void *data)
static int apply_to_pud_range(struct mm_struct *mm, p4d_t *p4d, unsigned long addr, unsigned long end, pte_fn_t fn, void *data)
static int apply_to_p4d_range(struct mm_struct *mm, pgd_t *pgd, unsigned long addr, unsigned long end, pte_fn_t fn, void *data)
int apply_to_page_range(struct mm_struct *mm, unsigned long addr, unsigned long size, pte_fn_t fn, void *data)
static inline int pte_unmap_same(struct mm_struct *mm, pmd_t *pmd, pte_t *page_table, pte_t orig_pte)
static inline void cow_user_page(struct page *dst, struct page *src, unsigned long va, struct vm_area_struct *vma)
static gfp_t __get_fault_gfp_mask(struct vm_area_struct *vma)
static vm_fault_t do_page_mkwrite(struct vm_fault *vmf)
static void fault_dirty_shared_page(struct vm_area_struct *vma, struct page *page)
static inline void wp_page_reuse(struct vm_fault *vmf)
__releases(vmf->ptl)
static vm_fault_t wp_page_copy(struct vm_fault *vmf)
vm_fault_t finish_mkwrite_fault(struct vm_fault *vmf)
static vm_fault_t wp_pfn_shared(struct vm_fault *vmf)
static vm_fault_t wp_page_shared(struct vm_fault *vmf)
__releases(vmf->ptl)
static vm_fault_t do_wp_page(struct vm_fault *vmf)
__releases(vmf->ptl)
static void unmap_mapping_range_vma(struct vm_area_struct *vma, unsigned long start_addr, unsigned long end_addr, struct zap_details *details)
static inline void unmap_mapping_range_tree(struct rb_root_cached *root, struct zap_details *details)
void unmap_mapping_pages(struct address_space *mapping, pgoff_t start, pgoff_t nr, bool even_cows)
void unmap_mapping_range(struct address_space *mapping, loff_t const holebegin, loff_t const holelen, int even_cows)
vm_fault_t do_swap_page(struct vm_fault *vmf)
static vm_fault_t do_anonymous_page(struct vm_fault *vmf)
static vm_fault_t __do_fault(struct vm_fault *vmf)
static int pmd_devmap_trans_unstable(pmd_t *pmd)
static vm_fault_t pte_alloc_one_map(struct vm_fault *vmf)
define HPAGE_CACHE_INDEX_MASK (HPAGE_PMD_NR - 1)
static inline bool transhuge_vma_suitable(struct vm_area_struct *vma, unsigned long haddr)
static void deposit_prealloc_pte(struct vm_fault *vmf)
static vm_fault_t do_set_pmd(struct vm_fault *vmf, struct page *page)
ret = 0;count_vm_event(THP_FILE_MAPPED)
; out:spin_unlock(vmf->ptl)
;return ret; } static vm_fault_t do_set_pmd(struct vm_fault *vmf, struct page *page)
vm_fault_t alloc_set_pte(struct vm_fault *vmf, struct mem_cgroup *memcg, struct page *page)
vm_fault_t finish_fault(struct vm_fault *vmf)
static int fault_around_bytes_get(void *data, u64 *val)
static int fault_around_bytes_set(void *data, u64 val)
static int __init fault_around_debugfs(void)
static vm_fault_t do_fault_around(struct vm_fault *vmf)
static vm_fault_t do_read_fault(struct vm_fault *vmf)
static vm_fault_t do_cow_fault(struct vm_fault *vmf)
static vm_fault_t do_shared_fault(struct vm_fault *vmf)
static vm_fault_t do_fault(struct vm_fault *vmf)
static int numa_migrate_prep(struct page *page, struct vm_area_struct *vma, unsigned long addr, int page_nid, int *flags)
static vm_fault_t do_numa_page(struct vm_fault *vmf)
static inline vm_fault_t create_huge_pmd(struct vm_fault *vmf)
static inline vm_fault_t wp_huge_pmd(struct vm_fault *vmf, pmd_t orig_pmd)
static inline bool vma_is_accessible(struct vm_area_struct *vma)
static vm_fault_t create_huge_pud(struct vm_fault *vmf)
static vm_fault_t wp_huge_pud(struct vm_fault *vmf, pud_t orig_pud)
static vm_fault_t handle_pte_fault(struct vm_fault *vmf)
static vm_fault_t __handle_mm_fault(struct vm_area_struct *vma, unsigned long address, unsigned int flags)
vm_fault_t handle_mm_fault(struct vm_area_struct *vma, unsigned long address, unsigned int flags)
int __p4d_alloc(struct mm_struct *mm, pgd_t *pgd, unsigned long address)
int __pud_alloc(struct mm_struct *mm, p4d_t *p4d, unsigned long address)
int __pmd_alloc(struct mm_struct *mm, pud_t *pud, unsigned long address)
static int __follow_pte_pmd(struct mm_struct *mm, unsigned long address, struct mmu_notifier_range *range, pte_t **ptepp, pmd_t **pmdpp, spinlock_t **ptlp)
static inline int follow_pte(struct mm_struct *mm, unsigned long address, pte_t **ptepp, spinlock_t **ptlp)
int follow_pte_pmd(struct mm_struct *mm, unsigned long address, struct mmu_notifier_range *range, pte_t **ptepp, pmd_t **pmdpp, spinlock_t **ptlp)
int follow_pfn(struct vm_area_struct *vma, unsigned long address, unsigned long *pfn)
int follow_phys(struct vm_area_struct *vma, unsigned long address, unsigned int flags, unsigned long *prot, resource_size_t *phys)
int generic_access_phys(struct vm_area_struct *vma, unsigned long addr, void *buf, int len, int write)
int __access_remote_vm(struct task_struct *tsk, struct mm_struct *mm, unsigned long addr, void *buf, int len, unsigned int gup_flags)
int access_remote_vm(struct mm_struct *mm, unsigned long addr, void *buf, int len, unsigned int gup_flags)
int access_process_vm(struct task_struct *tsk, unsigned long addr, void *buf, int len, unsigned int gup_flags)
void print_vma_addr(char *prefix, unsigned long ip)
void __might_fault(const char *file, int line)
static inline void process_huge_page(unsigned long addr_hint, unsigned int pages_per_huge_page, void (*process_subpage)
(unsigned long addr, int idx, void *arg)
, void *arg)
static void clear_gigantic_page(struct page *page, unsigned long addr, unsigned int pages_per_huge_page)
static void clear_subpage(unsigned long addr, int idx, void *arg)
void clear_huge_page(struct page *page, unsigned long addr_hint, unsigned int pages_per_huge_page)
static void copy_user_gigantic_page(struct page *dst, struct page *src, unsigned long addr, struct vm_area_struct *vma, unsigned int pages_per_huge_page)
static void copy_subpage(unsigned long addr, int idx, void *arg)
void copy_user_huge_page(struct page *dst, struct page *src, unsigned long addr_hint, struct vm_area_struct *vma, unsigned int pages_per_huge_page)
long copy_huge_page_from_user(struct page *dst_page, const void __user *usr_src, unsigned int pages_per_huge_page, bool allow_pagefault)
void __init ptlock_cache_init(void)
bool ptlock_alloc(struct page *page)
void ptlock_free(struct page *page)
\n
     47 unsigned long addr
     45 struct vm_area_struct *vma
     27 struct vm_fault *vmf
     23 struct mm_struct *mm
     21 unsigned long end
     13 struct mmu_gather *tlb
     12 unsigned long address
     12 struct page *page
      9 struct zap_details *details
      8 pmd_t *pmd
      7 void *data
      7 unsigned long pfn
      7 pgprot_t prot
      6 unsigned int pages_per_huge_page
      6 struct mm_struct *src_mm
      6 struct mm_struct *dst_mm
      5 unsigned long size
      5 unsigned long floor
      5 unsigned long ceiling
      5 pud_t *pud
      5 pte_fn_t fn
      5 pgd_t *pgd
      5 pfn_t pfn
      5 p4d_t *p4d
      4 void *buf
      4 vmf->ptl
      4 int len
      3 void *arg
      3 void
      3 unsigned long start_addr
      3 unsigned long end_addr
      3 unsigned long addr_hint
      3 unsigned int gup_flags
      3 unsigned int flags
      3 struct page *src
      3 struct page *dst
      3 spinlock_t **ptlp
      3 pte_t **ptepp
      3 int *rss
      3 int idx
      2 struct task_struct *tsk
      2 struct task_struct *task
      2 struct mmu_notifier_range *range
      2 struct address_space *mapping
      2 pte_t pte
      2 pmd_t **pmdpp
      2 bool mkwrite
      1 zap_vma_ptes
      1 void *process_subpage
      1 unsigned long va
      1 unsigned long start
      1 unsigned long *prot
      1 unsigned long *pfn
      1 unsigned long len
      1 unsigned long ip
      1 unsigned long haddr
      1 u64 *val
      1 u64 val
      1 THP_FILE_MAPPED
      1 struct rb_root_cached *root
      1 struct page *dst_page
      1 struct mem_cgroup *memcg
      1 spinlock_t **ptl
      1 resource_size_t *phys
      1 pud_t *src_pud
      1 pud_t orig_pud
      1 pud_t *dst_pud
      1 pte_t *src_pte
      1 pte_t *page_table
      1 pte_t orig_pte
      1 pte_t *dst_pte
      1 pmd_t *src_pmd
      1 pmd_t pmd
      1 pmd_t orig_pmd
      1 pmd_t *dst_pmd
      1 phys_addr_t start
      1 pgprot_t pgprot
      1 pgoff_t start
      1 pgoff_t nr
      1 pgd_t *src_pgd
      1 pgd_t *dst_pgd
      1 p4d_t *src_p4d
      1 p4d_t *dst_p4d
      1 loff_t const holelen
      1 loff_t const holebegin
      1 int write
      1 int val
      1 int page_nid
      1 int member
      1 int line
      1 int *flags
      1 int even_cows
      1 HPAGE_PMD_NR - 1
      1 handle_mm_fault
      1 generic_access_phys
      1 const void __user *usr_src
      1 const char *file
      1 char *s
      1 char *prefix
      1 bool with_public_device
      1 bool even_cows
      1 bool allow_pagefault
      1 apply_to_page_range
      1 access_process_vm
      1 64
