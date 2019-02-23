
EXPORT_SYMBOL_GPL(thp_get_unmapped_area);
EXPORT_SYMBOL_GPL(vmf_insert_pfn_pmd);
EXPORT_SYMBOL_GPL(vmf_insert_pfn_pud);
\n
bool transparent_hugepage_enabled(struct vm_area_struct *vma)
static struct page *get_huge_zero_page(void)
static void put_huge_zero_page(void)
struct page *mm_get_huge_zero_page(struct mm_struct *mm)
void mm_put_huge_zero_page(struct mm_struct *mm)
static unsigned long shrink_huge_zero_page_count(struct shrinker *shrink, struct shrink_control *sc)
static unsigned long shrink_huge_zero_page_scan(struct shrinker *shrink, struct shrink_control *sc)
static ssize_t enabled_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t enabled_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
ssize_t single_hugepage_flag_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf, enum transparent_hugepage_flag flag)
ssize_t single_hugepage_flag_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count, enum transparent_hugepage_flag flag)
static ssize_t defrag_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t defrag_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t use_zero_page_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t use_zero_page_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
return single_hugepage_flag_show(kobj, attr, buf, TRANSPARENT_HUGEPAGE_USE_ZERO_PAGE_FLAG)
; } static ssize_t use_zero_page_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t hpage_pmd_size_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t debug_cow_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t debug_cow_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
return single_hugepage_flag_show(kobj, attr, buf, TRANSPARENT_HUGEPAGE_DEBUG_COW_FLAG)
; } static ssize_t debug_cow_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static int __init hugepage_init_sysfs(struct kobject **hugepage_kobj)
static void __init hugepage_exit_sysfs(struct kobject *hugepage_kobj)
static void __init hugepage_exit_sysfs(struct kobject *hugepage_kobj)
sysfs_remove_group(hugepage_kobj, &khugepaged_attr_group)
;sysfs_remove_group(hugepage_kobj, &hugepage_attr_group)
;kobject_put(hugepage_kobj)
; } static inline int hugepage_init_sysfs(struct kobject **hugepage_kobj)
static inline void hugepage_exit_sysfs(struct kobject *hugepage_kobj)
static int __init hugepage_init(void)
static int __init setup_transparent_hugepage(char *str)
pmd_t maybe_pmd_mkwrite(pmd_t pmd, struct vm_area_struct *vma)
static inline struct list_head *page_deferred_list(struct page *page)
void prep_transhuge_page(struct page *page)
unsigned long __thp_get_unmapped_area(struct file *filp, unsigned long len, loff_t off, unsigned long flags, unsigned long size)
unsigned long thp_get_unmapped_area(struct file *filp, unsigned long addr, unsigned long len, unsigned long pgoff, unsigned long flags)
static vm_fault_t __do_huge_pmd_anonymous_page(struct vm_fault *vmf, struct page *page, gfp_t gfp)
static inline gfp_t alloc_hugepage_direct_gfpmask(struct vm_area_struct *vma)
static bool set_huge_zero_page(pgtable_t pgtable, struct mm_struct *mm, struct vm_area_struct *vma, unsigned long haddr, pmd_t *pmd, struct page *zero_page)
vm_fault_t do_huge_pmd_anonymous_page(struct vm_fault *vmf)
static void insert_pfn_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmd, pfn_t pfn, pgprot_t prot, bool write, pgtable_t pgtable)
vm_fault_t vmf_insert_pfn_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmd, pfn_t pfn, bool write)
static pud_t maybe_pud_mkwrite(pud_t pud, struct vm_area_struct *vma)
static void insert_pfn_pud(struct vm_area_struct *vma, unsigned long addr, pud_t *pud, pfn_t pfn, pgprot_t prot, bool write)
vm_fault_t vmf_insert_pfn_pud(struct vm_area_struct *vma, unsigned long addr, pud_t *pud, pfn_t pfn, bool write)
static void touch_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmd, int flags)
struct page *follow_devmap_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmd, int flags, struct dev_pagemap **pgmap)
int copy_huge_pmd(struct mm_struct *dst_mm, struct mm_struct *src_mm, pmd_t *dst_pmd, pmd_t *src_pmd, unsigned long addr, struct vm_area_struct *vma)
static void touch_pud(struct vm_area_struct *vma, unsigned long addr, pud_t *pud, int flags)
struct page *follow_devmap_pud(struct vm_area_struct *vma, unsigned long addr, pud_t *pud, int flags, struct dev_pagemap **pgmap)
int copy_huge_pud(struct mm_struct *dst_mm, struct mm_struct *src_mm, pud_t *dst_pud, pud_t *src_pud, unsigned long addr, struct vm_area_struct *vma)
void huge_pud_set_accessed(struct vm_fault *vmf, pud_t orig_pud)
void huge_pmd_set_accessed(struct vm_fault *vmf, pmd_t orig_pmd)
static vm_fault_t do_huge_pmd_wp_page_fallback(struct vm_fault *vmf, pmd_t orig_pmd, struct page *page)
vm_fault_t do_huge_pmd_wp_page(struct vm_fault *vmf, pmd_t orig_pmd)
static inline bool can_follow_write_pmd(pmd_t pmd, unsigned int flags)
struct page *follow_trans_huge_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmd, unsigned int flags)
vm_fault_t do_huge_pmd_numa_page(struct vm_fault *vmf, pmd_t pmd)
bool madvise_free_huge_pmd(struct mmu_gather *tlb, struct vm_area_struct *vma, pmd_t *pmd, unsigned long addr, unsigned long next)
static inline void zap_deposited_table(struct mm_struct *mm, pmd_t *pmd)
int zap_huge_pmd(struct mmu_gather *tlb, struct vm_area_struct *vma, pmd_t *pmd, unsigned long addr)
static inline int pmd_move_must_withdraw(spinlock_t *new_pmd_ptl, spinlock_t *old_pmd_ptl, struct vm_area_struct *vma)
static pmd_t move_soft_dirty_pmd(pmd_t pmd)
bool move_huge_pmd(struct vm_area_struct *vma, unsigned long old_addr, unsigned long new_addr, unsigned long old_end, pmd_t *old_pmd, pmd_t *new_pmd)
int change_huge_pmd(struct vm_area_struct *vma, pmd_t *pmd, unsigned long addr, pgprot_t newprot, int prot_numa)
spinlock_t *__pmd_trans_huge_lock(pmd_t *pmd, struct vm_area_struct *vma)
spinlock_t *__pud_trans_huge_lock(pud_t *pud, struct vm_area_struct *vma)
int zap_huge_pud(struct mmu_gather *tlb, struct vm_area_struct *vma, pud_t *pud, unsigned long addr)
static void __split_huge_pud_locked(struct vm_area_struct *vma, pud_t *pud, unsigned long haddr)
void __split_huge_pud(struct vm_area_struct *vma, pud_t *pud, unsigned long address)
static void __split_huge_zero_page_pmd(struct vm_area_struct *vma, unsigned long haddr, pmd_t *pmd)
static void __split_huge_pmd_locked(struct vm_area_struct *vma, pmd_t *pmd, unsigned long haddr, bool freeze)
void __split_huge_pmd(struct vm_area_struct *vma, pmd_t *pmd, unsigned long address, bool freeze, struct page *page)
void split_huge_pmd_address(struct vm_area_struct *vma, unsigned long address, bool freeze, struct page *page)
void vma_adjust_trans_huge(struct vm_area_struct *vma, unsigned long start, unsigned long end, long adjust_next)
static void unmap_page(struct page *page)
static void remap_page(struct page *page)
static void __split_huge_page_tail(struct page *head, int tail, struct lruvec *lruvec, struct list_head *list)
static void __split_huge_page(struct page *page, struct list_head *list, pgoff_t end, unsigned long flags)
int total_mapcount(struct page *page)
int page_trans_huge_mapcount(struct page *page, int *total_mapcount)
bool can_split_huge_page(struct page *page, int *pextra_pins)
int split_huge_page_to_list(struct page *page, struct list_head *list)
void free_transhuge_page(struct page *page)
void deferred_split_huge_page(struct page *page)
static unsigned long deferred_split_count(struct shrinker *shrink, struct shrink_control *sc)
static unsigned long deferred_split_scan(struct shrinker *shrink, struct shrink_control *sc)
static int split_huge_pages_set(void *data, u64 val)
static int __init split_huge_pages_debugfs(void)
void set_pmd_migration_entry(struct page_vma_mapped_walk *pvmw, struct page *page)
void remove_migration_pmd(struct page_vma_mapped_walk *pvmw, struct page *new)
\n
     31 struct vm_area_struct *vma
     16 unsigned long addr
     16 struct page *page
     14 pmd_t *pmd
     13 struct kobject *kobj
     13 struct kobj_attribute *attr
      8 pud_t *pud
      8 char *buf
      7 struct vm_fault *vmf
      5 size_t count
      5 const char *buf
      4 void
      4 unsigned long haddr
      4 struct shrinker *shrink
      4 struct shrink_control *sc
      4 struct mm_struct *mm
      4 pmd_t pmd
      4 pfn_t pfn
      4 int flags
      4 bool write
      3 unsigned long flags
      3 unsigned long address
      3 struct mmu_gather *tlb
      3 struct list_head *list
      3 struct kobject *hugepage_kobj
      3 pmd_t orig_pmd
      3 hugepage_kobj
      3 bool freeze
      2 unsigned long len
      2 unsigned int flags
      2 struct page_vma_mapped_walk *pvmw
      2 struct mm_struct *src_mm
      2 struct mm_struct *dst_mm
      2 struct kobject **hugepage_kobj
      2 struct file *filp
      2 struct dev_pagemap **pgmap
      2 pgtable_t pgtable
      2 pgprot_t prot
      2 kobj
      2 enum transparent_hugepage_flag flag
      2 buf
      2 attr
      1 void *data
      1 vmf_insert_pfn_pud
      1 vmf_insert_pfn_pmd
      1 unsigned long start
      1 unsigned long size
      1 unsigned long pgoff
      1 unsigned long old_end
      1 unsigned long old_addr
      1 unsigned long next
      1 unsigned long new_addr
      1 unsigned long end
      1 u64 val
      1 TRANSPARENT_HUGEPAGE_USE_ZERO_PAGE_FLAG
      1 TRANSPARENT_HUGEPAGE_DEBUG_COW_FLAG
      1 thp_get_unmapped_area
      1 struct page *zero_page
      1 struct page *new
      1 struct page *head
      1 struct lruvec *lruvec
      1 spinlock_t *old_pmd_ptl
      1 spinlock_t *new_pmd_ptl
      1 pud_t *src_pud
      1 pud_t pud
      1 pud_t orig_pud
      1 pud_t *dst_pud
      1 pmd_t *src_pmd
      1 pmd_t *old_pmd
      1 pmd_t *new_pmd
      1 pmd_t *dst_pmd
      1 pgprot_t newprot
      1 pgoff_t end
      1 long adjust_next
      1 loff_t off
      1 &khugepaged_attr_group
      1 int *total_mapcount
      1 int tail
      1 int prot_numa
      1 int *pextra_pins
      1 &hugepage_attr_group
      1 gfp_t gfp
      1 char *str
