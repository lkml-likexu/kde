
EXPORT_SYMBOL_GPL(linear_hugepage_index);
EXPORT_SYMBOL_GPL(vma_kernel_pagesize);
EXPORT_SYMBOL_GPL(PageHuge);
\n
static inline void unlock_or_release_subpool(struct hugepage_subpool *spool)
struct hugepage_subpool *hugepage_new_subpool(struct hstate *h, long max_hpages, long min_hpages)
void hugepage_put_subpool(struct hugepage_subpool *spool)
static long hugepage_subpool_get_pages(struct hugepage_subpool *spool, long delta)
static long hugepage_subpool_put_pages(struct hugepage_subpool *spool, long delta)
static inline struct hugepage_subpool *subpool_inode(struct inode *inode)
static inline struct hugepage_subpool *subpool_vma(struct vm_area_struct *vma)
static long region_add(struct resv_map *resv, long f, long t)
static long region_chg(struct resv_map *resv, long f, long t)
static void region_abort(struct resv_map *resv, long f, long t)
static long region_del(struct resv_map *resv, long f, long t)
void hugetlb_fix_reserve_counts(struct inode *inode)
static long region_count(struct resv_map *resv, long f, long t)
static pgoff_t vma_hugecache_offset(struct hstate *h, struct vm_area_struct *vma, unsigned long address)
pgoff_t linear_hugepage_index(struct vm_area_struct *vma, unsigned long address)
unsigned long vma_kernel_pagesize(struct vm_area_struct *vma)
__weak unsigned long vma_mmu_pagesize(struct vm_area_struct *vma)
static unsigned long get_vma_private_data(struct vm_area_struct *vma)
static void set_vma_private_data(struct vm_area_struct *vma, unsigned long value)
struct resv_map *resv_map_alloc(void)
void resv_map_release(struct kref *ref)
static inline struct resv_map *inode_resv_map(struct inode *inode)
static struct resv_map *vma_resv_map(struct vm_area_struct *vma)
static void set_vma_resv_map(struct vm_area_struct *vma, struct resv_map *map)
static void set_vma_resv_flags(struct vm_area_struct *vma, unsigned long flags)
static int is_vma_resv_set(struct vm_area_struct *vma, unsigned long flag)
void reset_vma_resv_huge_pages(struct vm_area_struct *vma)
static bool vma_has_reserves(struct vm_area_struct *vma, long chg)
static void enqueue_huge_page(struct hstate *h, struct page *page)
static struct page *dequeue_huge_page_node_exact(struct hstate *h, int nid)
static struct page *dequeue_huge_page_nodemask(struct hstate *h, gfp_t gfp_mask, int nid, nodemask_t *nmask)
static inline gfp_t htlb_alloc_mask(struct hstate *h)
static struct page *dequeue_huge_page_vma(struct hstate *h, struct vm_area_struct *vma, unsigned long address, int avoid_reserve, long chg)
static int next_node_allowed(int nid, nodemask_t *nodes_allowed)
static int get_valid_node_allowed(int nid, nodemask_t *nodes_allowed)
static int hstate_next_node_to_alloc(struct hstate *h, nodemask_t *nodes_allowed)
static int hstate_next_node_to_free(struct hstate *h, nodemask_t *nodes_allowed)
static void destroy_compound_gigantic_page(struct page *page, unsigned int order)
static void free_gigantic_page(struct page *page, unsigned int order)
static int __alloc_gigantic_page(unsigned long start_pfn, unsigned long nr_pages, gfp_t gfp_mask)
static bool pfn_range_valid_gigantic(struct zone *z, unsigned long start_pfn, unsigned long nr_pages)
static bool zone_spans_last_pfn(const struct zone *zone, unsigned long start_pfn, unsigned long nr_pages)
static struct page *alloc_gigantic_page(struct hstate *h, gfp_t gfp_mask, int nid, nodemask_t *nodemask)
static void update_and_free_page(struct hstate *h, struct page *page)
struct hstate *size_to_hstate(unsigned long size)
bool page_huge_active(struct page *page)
static void set_page_huge_active(struct page *page)
static void clear_page_huge_active(struct page *page)
static inline bool PageHugeTemporary(struct page *page)
static inline void SetPageHugeTemporary(struct page *page)
static inline void ClearPageHugeTemporary(struct page *page)
void free_huge_page(struct page *page)
static void prep_new_huge_page(struct hstate *h, struct page *page, int nid)
static void prep_compound_gigantic_page(struct page *page, unsigned int order)
int PageHuge(struct page *page)
int PageHeadHuge(struct page *page_head)
pgoff_t __basepage_index(struct page *page)
static struct page *alloc_buddy_huge_page(struct hstate *h, gfp_t gfp_mask, int nid, nodemask_t *nmask)
static struct page *alloc_fresh_huge_page(struct hstate *h, gfp_t gfp_mask, int nid, nodemask_t *nmask)
static int alloc_pool_huge_page(struct hstate *h, nodemask_t *nodes_allowed)
static int free_pool_huge_page(struct hstate *h, nodemask_t *nodes_allowed, bool acct_surplus)
int dissolve_free_huge_page(struct page *page)
int dissolve_free_huge_pages(unsigned long start_pfn, unsigned long end_pfn)
static struct page *alloc_surplus_huge_page(struct hstate *h, gfp_t gfp_mask, int nid, nodemask_t *nmask)
static struct page *alloc_migrate_huge_page(struct hstate *h, gfp_t gfp_mask, int nid, nodemask_t *nmask)
static struct page *alloc_buddy_huge_page_with_mpol(struct hstate *h, struct vm_area_struct *vma, unsigned long addr)
struct page *alloc_huge_page_node(struct hstate *h, int nid)
struct page *alloc_huge_page_nodemask(struct hstate *h, int preferred_nid, nodemask_t *nmask)
struct page *alloc_huge_page_vma(struct hstate *h, struct vm_area_struct *vma, unsigned long address)
static int gather_surplus_pages(struct hstate *h, int delta)
static void return_unused_surplus_pages(struct hstate *h, unsigned long unused_resv_pages)
VMA_NEEDS_RESV, VMA_COMMIT_RESV, VMA_END_RESV, VMA_ADD_RESV, }; static long __vma_reservation_common(struct hstate *h, struct vm_area_struct *vma, unsigned long addr, enum vma_resv_mode mode)
static long vma_needs_reservation(struct hstate *h, struct vm_area_struct *vma, unsigned long addr)
static long vma_commit_reservation(struct hstate *h, struct vm_area_struct *vma, unsigned long addr)
static void vma_end_reservation(struct hstate *h, struct vm_area_struct *vma, unsigned long addr)
static long vma_add_reservation(struct hstate *h, struct vm_area_struct *vma, unsigned long addr)
static void restore_reserve_on_error(struct hstate *h, struct vm_area_struct *vma, unsigned long address, struct page *page)
struct page *alloc_huge_page(struct vm_area_struct *vma, unsigned long addr, int avoid_reserve)
int alloc_bootmem_huge_page(struct hstate *h)
__attribute__ ((weak, alias("__alloc_bootmem_huge_page")
)
)
; int __alloc_bootmem_huge_page(struct hstate *h)
static void __init prep_compound_huge_page(struct page *page, unsigned int order)
static void __init gather_bootmem_prealloc(void)
static void __init hugetlb_hstate_alloc_pages(struct hstate *h)
static void __init hugetlb_init_hstates(void)
static void __init report_hugepages(void)
static void try_to_free_low(struct hstate *h, unsigned long count, nodemask_t *nodes_allowed)
struct page *page, *next; struct list_head *freel = &h->hugepage_freelists[i];if (count >= h->nr_huge_pages)
return;if (PageHighMem(page)
)
continue;list_del(&page->lru)
;update_and_free_page(h, page)
;h->free_huge_pages--;h->free_huge_pages_node[page_to_nid(page)
]--; }} } static inline void try_to_free_low(struct hstate *h, unsigned long count, nodemask_t *nodes_allowed)
static int adjust_pool_surplus(struct hstate *h, nodemask_t *nodes_allowed, int delta)
define persistent_huge_pages(h)
(h->nr_huge_pages - h->surplus_huge_pages)
static unsigned long set_max_huge_pages(struct hstate *h, unsigned long count, nodemask_t *nodes_allowed)
static struct hstate *kobj_to_hstate(struct kobject *kobj, int *nidp)
static ssize_t nr_hugepages_show_common(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t __nr_hugepages_store_common(bool obey_mempolicy, struct hstate *h, int nid, unsigned long count, size_t len)
static ssize_t nr_hugepages_store_common(bool obey_mempolicy, struct kobject *kobj, const char *buf, size_t len)
static ssize_t nr_hugepages_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t nr_hugepages_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len)
static ssize_t nr_hugepages_mempolicy_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t nr_hugepages_mempolicy_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len)
static ssize_t nr_overcommit_hugepages_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t nr_overcommit_hugepages_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t free_hugepages_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t resv_hugepages_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t surplus_hugepages_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static int hugetlb_sysfs_add_hstate(struct hstate *h, struct kobject *parent, struct kobject **hstate_kobjs, const struct attribute_group *hstate_attr_group)
static void __init hugetlb_sysfs_init(void)
static struct hstate *kobj_to_node_hstate(struct kobject *kobj, int *nidp)
static void hugetlb_unregister_node(struct node *node)
static void hugetlb_register_node(struct node *node)
static void __init hugetlb_register_all_nodes(void)
static struct hstate *kobj_to_node_hstate(struct kobject *kobj, int *nidp)
static int __init hugetlb_init(void)
void __init hugetlb_bad_size(void)
void __init hugetlb_add_hstate(unsigned int order)
static int __init hugetlb_nrpages_setup(char *s)
static int __init hugetlb_default_setup(char *s)
static unsigned int cpuset_mems_nr(unsigned int *array)
static int hugetlb_sysctl_handler_common(bool obey_mempolicy, struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
int hugetlb_sysctl_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
int hugetlb_mempolicy_sysctl_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
int hugetlb_overcommit_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
void hugetlb_report_meminfo(struct seq_file *m)
int hugetlb_report_node_meminfo(int nid, char *buf)
void hugetlb_show_meminfo(void)
void hugetlb_report_usage(struct seq_file *m, struct mm_struct *mm)
unsigned long hugetlb_total_pages(void)
static int hugetlb_acct_memory(struct hstate *h, long delta)
static void hugetlb_vm_op_open(struct vm_area_struct *vma)
static void hugetlb_vm_op_close(struct vm_area_struct *vma)
static int hugetlb_vm_op_split(struct vm_area_struct *vma, unsigned long addr)
static unsigned long hugetlb_vm_op_pagesize(struct vm_area_struct *vma)
static vm_fault_t hugetlb_vm_op_fault(struct vm_fault *vmf)
static pte_t make_huge_pte(struct vm_area_struct *vma, struct page *page, int writable)
static void set_huge_ptep_writable(struct vm_area_struct *vma, unsigned long address, pte_t *ptep)
bool is_hugetlb_entry_migration(pte_t pte)
static int is_hugetlb_entry_hwpoisoned(pte_t pte)
int copy_hugetlb_page_range(struct mm_struct *dst, struct mm_struct *src, struct vm_area_struct *vma)
void __unmap_hugepage_range(struct mmu_gather *tlb, struct vm_area_struct *vma, unsigned long start, unsigned long end, struct page *ref_page)
void __unmap_hugepage_range_final(struct mmu_gather *tlb, struct vm_area_struct *vma, unsigned long start, unsigned long end, struct page *ref_page)
void unmap_hugepage_range(struct vm_area_struct *vma, unsigned long start, unsigned long end, struct page *ref_page)
static void unmap_ref_private(struct mm_struct *mm, struct vm_area_struct *vma, struct page *page, unsigned long address)
static vm_fault_t hugetlb_cow(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long address, pte_t *ptep, struct page *pagecache_page, spinlock_t *ptl)
static struct page *hugetlbfs_pagecache_page(struct hstate *h, struct vm_area_struct *vma, unsigned long address)
static bool hugetlbfs_pagecache_present(struct hstate *h, struct vm_area_struct *vma, unsigned long address)
int huge_add_to_page_cache(struct page *page, struct address_space *mapping, pgoff_t idx)
static vm_fault_t hugetlb_no_page(struct mm_struct *mm, struct vm_area_struct *vma, struct address_space *mapping, pgoff_t idx, unsigned long address, pte_t *ptep, unsigned int flags)
u32 hugetlb_fault_mutex_hash(struct hstate *h, struct mm_struct *mm, struct vm_area_struct *vma, struct address_space *mapping, pgoff_t idx, unsigned long address)
return hash & (num_fault_mutexes - 1)
; }u32 hugetlb_fault_mutex_hash(struct hstate *h, struct mm_struct *mm, struct vm_area_struct *vma, struct address_space *mapping, pgoff_t idx, unsigned long address)
vm_fault_t hugetlb_fault(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long address, unsigned int flags)
int hugetlb_mcopy_atomic_pte(struct mm_struct *dst_mm, pte_t *dst_pte, struct vm_area_struct *dst_vma, unsigned long dst_addr, unsigned long src_addr, struct page **pagep)
long follow_hugetlb_page(struct mm_struct *mm, struct vm_area_struct *vma, struct page **pages, struct vm_area_struct **vmas, unsigned long *position, unsigned long *nr_pages, long i, unsigned int flags, int *nonblocking)
unsigned long hugetlb_change_protection(struct vm_area_struct *vma, unsigned long address, unsigned long end, pgprot_t newprot)
int hugetlb_reserve_pages(struct inode *inode, long from, long to, struct vm_area_struct *vma, vm_flags_t vm_flags)
long hugetlb_unreserve_pages(struct inode *inode, long start, long end, long freed)
static unsigned long page_table_shareable(struct vm_area_struct *svma, struct vm_area_struct *vma, unsigned long addr, pgoff_t idx)
static bool vma_shareable(struct vm_area_struct *vma, unsigned long addr)
void adjust_range_if_pmd_sharing_possible(struct vm_area_struct *vma, unsigned long *start, unsigned long *end)
pte_t *huge_pmd_share(struct mm_struct *mm, unsigned long addr, pud_t *pud)
int huge_pmd_unshare(struct mm_struct *mm, unsigned long *addr, pte_t *ptep)
pud_clear(pud)
;put_page(virt_to_page(ptep)
)
;mm_dec_nr_pmds(mm)
;*addr = ALIGN(*addr, HPAGE_SIZE * PTRS_PER_PTE)
- HPAGE_SIZE;return 1; }define want_pmd_share()
(1)
pte_t *huge_pmd_share(struct mm_struct *mm, unsigned long addr, pud_t *pud)
int huge_pmd_unshare(struct mm_struct *mm, unsigned long *addr, pte_t *ptep)
void adjust_range_if_pmd_sharing_possible(struct vm_area_struct *vma, unsigned long *start, unsigned long *end)
pte_t *huge_pte_alloc(struct mm_struct *mm, unsigned long addr, unsigned long sz)
pte_t *huge_pte_offset(struct mm_struct *mm, unsigned long addr, unsigned long sz)
struct page * __weak follow_huge_addr(struct mm_struct *mm, unsigned long address, int write)
struct page * __weak follow_huge_pd(struct vm_area_struct *vma, unsigned long address, hugepd_t hpd, int flags, int pdshift)
struct page * __weak follow_huge_pmd(struct mm_struct *mm, unsigned long address, pmd_t *pmd, int flags)
struct page * __weak follow_huge_pud(struct mm_struct *mm, unsigned long address, pud_t *pud, int flags)
struct page * __weak follow_huge_pgd(struct mm_struct *mm, unsigned long address, pgd_t *pgd, int flags)
bool isolate_huge_page(struct page *page, struct list_head *list)
void putback_active_hugepage(struct page *page)
void move_hugetlb_state(struct page *oldpage, struct page *newpage, int reason)
\n
     49 struct vm_area_struct *vma
     44 struct hstate *h
     23 struct page *page
     20 unsigned long address
     18 struct mm_struct *mm
     14 unsigned long addr
     14 struct kobject *kobj
     13 int nid
     10 void
     10 struct kobj_attribute *attr
     10 nodemask_t *nodes_allowed
      8 char *buf
      7 gfp_t gfp_mask
      6 nodemask_t *nmask
      5 unsigned int order
      5 struct resv_map *resv
      5 struct inode *inode
      5 pte_t *ptep
      5 pgoff_t idx
      5 long t
      5 long f
      5 int write
      4 void __user *buffer
      4 unsigned long start_pfn
      4 unsigned long end
      4 unsigned long count
      4 struct hugepage_subpool *spool
      4 struct ctl_table *table
      4 struct address_space *mapping
      4 size_t *length
      4 size_t len
      4 loff_t *ppos
      4 int flags
      4 const char *buf
      3 unsigned long start
      3 unsigned long nr_pages
      3 unsigned int flags
      3 struct page *ref_page
      3 pud_t *pud
      3 long delta
      3 int *nidp
      3 bool obey_mempolicy
      2 unsigned long sz
      2 unsigned long *start
      2 unsigned long *end
      2 unsigned long *addr
      2 struct seq_file *m
      2 struct node *node
      2 struct mmu_gather *tlb
      2 pte_t pte
      2 page
      2 long chg
      2 int delta
      2 int avoid_reserve
      2 h
      2 char *s
      1 weak
      1 vm_flags_t vm_flags
      1 vma_kernel_pagesize
      1 virt_to_pageptep
      1 unsigned long value
      1 unsigned long unused_resv_pages
      1 unsigned long src_addr
      1 unsigned long size
      1 unsigned long *position
      1 unsigned long *nr_pages
      1 unsigned long flags
      1 unsigned long flag
      1 unsigned long end_pfn
      1 unsigned long dst_addr
      1 unsigned int *array
      1 struct zone *z
      1 struct vm_fault *vmf
      1 struct vm_area_struct **vmas
      1 struct vm_area_struct *svma
      1 struct vm_area_struct *dst_vma
      1 struct resv_map *map
      1 struct page **pages
      1 struct page **pagep
      1 struct page *page_head
      1 struct page *pagecache_page
      1 struct page *oldpage
      1 struct page *newpage
      1 struct mm_struct *src
      1 struct mm_struct *dst_mm
      1 struct mm_struct *dst
      1 struct list_head *list
      1 struct kref *ref
      1 struct kobject *parent
      1 struct kobject **hstate_kobjs
      1 spinlock_t *ptl
      1 size_t count
      1 pud
      1 pte_t *dst_pte
      1 pmd_t *pmd
      1 pgprot_t newprot
      1 pgd_t *pgd
      1 &page->lru
      1 PageHuge
      1 PageHighMempage
      1 num_fault_mutexes - 1
      1 nodemask_t *nodemask
      1 mm
      1 long to
      1 long start
      1 long min_hpages
      1 long max_hpages
      1 long i
      1 long from
      1 long freed
      1 long end
      1 linear_hugepage_index
      1 int writable
      1 int reason
      1 int preferred_nid
      1 int pdshift
      1 int *nonblocking
      1 hugepd_t hpd
      1 HPAGE_SIZE * PTRS_PER_PTE
      1 h->nr_huge_pages - h->surplus_huge_pages
      1 enum vma_resv_mode mode
      1 count >= h->nr_huge_pages
      1 const struct zone *zone
      1 const struct attribute_group *hstate_attr_group
      1 bool acct_surplus
      1 alias"__alloc_bootmem_huge_page"
      1 *addr
      1 1
      1 
