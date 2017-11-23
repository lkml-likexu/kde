
static ssize_t scan_sleep_millisecs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t scan_sleep_millisecs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t alloc_sleep_millisecs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t alloc_sleep_millisecs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t pages_to_scan_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t pages_to_scan_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
return sprintf(buf, "%u\n", khugepaged_pages_to_scan)
; } static ssize_t pages_to_scan_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t pages_collapsed_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t full_scans_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t khugepaged_defrag_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t khugepaged_defrag_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
return single_hugepage_flag_show(kobj, attr, buf, TRANSPARENT_HUGEPAGE_DEFRAG_KHUGEPAGED_FLAG)
; } static ssize_t khugepaged_defrag_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t khugepaged_max_ptes_none_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t khugepaged_max_ptes_none_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
return sprintf(buf, "%u\n", khugepaged_max_ptes_none)
; } static ssize_t khugepaged_max_ptes_none_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t khugepaged_max_ptes_swap_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t khugepaged_max_ptes_swap_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
int hugepage_madvise(struct vm_area_struct *vma, unsigned long *vm_flags, int advice)
int __init khugepaged_init(void)
void __init khugepaged_destroy(void)
static inline struct mm_slot *alloc_mm_slot(void)
static inline void free_mm_slot(struct mm_slot *mm_slot)
static struct mm_slot *get_mm_slot(struct mm_struct *mm)
static void insert_to_mm_slots_hash(struct mm_struct *mm, struct mm_slot *mm_slot)
static inline int khugepaged_test_exit(struct mm_struct *mm)
static bool hugepage_vma_check(struct vm_area_struct *vma, unsigned long vm_flags)
int __khugepaged_enter(struct mm_struct *mm)
int khugepaged_enter_vma_merge(struct vm_area_struct *vma, unsigned long vm_flags)
void __khugepaged_exit(struct mm_struct *mm)
static void release_pte_page(struct page *page)
static void release_pte_pages(pte_t *pte, pte_t *_pte)
static int __collapse_huge_page_isolate(struct vm_area_struct *vma, unsigned long address, pte_t *pte)
static void __collapse_huge_page_copy(pte_t *pte, struct page *page, struct vm_area_struct *vma, unsigned long address, spinlock_t *ptl)
static void khugepaged_alloc_sleep(void)
static bool khugepaged_scan_abort(int nid)
static inline gfp_t alloc_hugepage_khugepaged_gfpmask(void)
static int khugepaged_find_target_node(void)
static bool khugepaged_prealloc_page(struct page **hpage, bool *wait)
static struct page * khugepaged_alloc_page(struct page **hpage, gfp_t gfp, int node)
prep_transhuge_page(*hpage)
;count_vm_event(THP_COLLAPSE_ALLOC)
;return *hpage; } static int khugepaged_find_target_node(void)
static inline struct page *alloc_khugepaged_hugepage(void)
static struct page *khugepaged_alloc_hugepage(bool *wait)
static bool khugepaged_prealloc_page(struct page **hpage, bool *wait)
static struct page * khugepaged_alloc_page(struct page **hpage, gfp_t gfp, int node)
static int hugepage_vma_revalidate(struct mm_struct *mm, unsigned long address, struct vm_area_struct **vmap)
static bool __collapse_huge_page_swapin(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long address, pmd_t *pmd, int referenced)
static void collapse_huge_page(struct mm_struct *mm, unsigned long address, struct page **hpage, int node, int referenced)
static int khugepaged_scan_pmd(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long address, struct page **hpage)
static void collect_mm_slot(struct mm_slot *mm_slot)
static void retract_page_tables(struct address_space *mapping, pgoff_t pgoff)
static void collapse_shmem(struct mm_struct *mm, struct address_space *mapping, pgoff_t start, struct page **hpage, int node)
static void khugepaged_scan_shmem(struct mm_struct *mm, struct address_space *mapping, pgoff_t start, struct page **hpage)
} static void khugepaged_scan_shmem(struct mm_struct *mm, struct address_space *mapping, pgoff_t start, struct page **hpage)
static unsigned int khugepaged_scan_mm_slot(unsigned int pages, struct page **hpage)
__releases(&khugepaged_mm_lock)
__acquires(&khugepaged_mm_lock)
static int khugepaged_has_work(void)
static int khugepaged_wait_event(void)
static void khugepaged_do_scan(void)
static bool khugepaged_should_wakeup(void)
static void khugepaged_wait_work(void)
static int khugepaged(void *none)
static void set_recommended_min_free_kbytes(void)
int start_stop_khugepaged(void)
  17 struct kobject *kobj
  17 struct kobj_attribute *attr
  15 void
  12 struct mm_struct *mm
  11 char *buf
  10 struct page **hpage
   7 struct vm_area_struct *vma
   6 unsigned long address
   6 size_t count
   6 const char *buf
   4 struct address_space *mapping
   4 int node
   3 struct mm_slot *mm_slot
   3 pte_t *pte
   3 pgoff_t start
   3 buf
   3 bool *wait
   2 unsigned long vm_flags
   2 struct page *page
   2 int referenced
   2 gfp_t gfp
   2 &khugepaged_mm_lock
   2 "%u\n"
   1 void *none
   1 unsigned long *vm_flags
   1 unsigned int pages
   1 struct vm_area_struct **vmap
   1 spinlock_t *ptl
   1 pte_t *_pte
   1 pmd_t *pmd
   1 pgoff_t pgoff
   1 kobj
   1 khugepaged_pages_to_scan
   1 khugepaged_max_ptes_none
   1 int nid
   1 int advice
   1 attr
   1 TRANSPARENT_HUGEPAGE_DEFRAG_KHUGEPAGED_FLAG
   1 THP_COLLAPSE_ALLOC
   1 *hpage
