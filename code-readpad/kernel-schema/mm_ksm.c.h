
static int __init ksm_slab_init(void)
static void __init ksm_slab_free(void)
static __always_inline bool is_stable_node_chain(struct stable_node *chain)
static __always_inline bool is_stable_node_dup(struct stable_node *dup)
static inline void stable_node_chain_add_dup(struct stable_node *dup, struct stable_node *chain)
static inline void __stable_node_dup_del(struct stable_node *dup)
static inline void stable_node_dup_del(struct stable_node *dup)
static inline struct rmap_item *alloc_rmap_item(void)
static inline void free_rmap_item(struct rmap_item *rmap_item)
static inline struct stable_node *alloc_stable_node(void)
static inline void free_stable_node(struct stable_node *stable_node)
static inline struct mm_slot *alloc_mm_slot(void)
static inline void free_mm_slot(struct mm_slot *mm_slot)
static struct mm_slot *get_mm_slot(struct mm_struct *mm)
static void insert_to_mm_slots_hash(struct mm_struct *mm, struct mm_slot *mm_slot)
static inline bool ksm_test_exit(struct mm_struct *mm)
static int break_ksm(struct vm_area_struct *vma, unsigned long addr)
static struct vm_area_struct *find_mergeable_vma(struct mm_struct *mm, unsigned long addr)
static void break_cow(struct rmap_item *rmap_item)
static struct page *get_mergeable_page(struct rmap_item *rmap_item)
static inline int get_kpfn_nid(unsigned long kpfn)
static struct stable_node *alloc_stable_node_chain(struct stable_node *dup, struct rb_root *root)
static inline void free_stable_node_chain(struct stable_node *chain, struct rb_root *root)
static void remove_node_from_stable_tree(struct stable_node *stable_node)
static struct page *get_ksm_page(struct stable_node *stable_node, bool lock_it)
static void remove_rmap_item_from_tree(struct rmap_item *rmap_item)
static void remove_trailing_rmap_items(struct mm_slot *mm_slot, struct rmap_item **rmap_list)
static int unmerge_ksm_pages(struct vm_area_struct *vma, unsigned long start, unsigned long end)
static inline struct stable_node *page_stable_node(struct page *page)
static inline void set_page_stable_node(struct page *page, struct stable_node *stable_node)
static int remove_stable_node(struct stable_node *stable_node)
static int remove_stable_node_chain(struct stable_node *stable_node, struct rb_root *root)
static int remove_all_stable_nodes(void)
static int unmerge_and_remove_all_rmap_items(void)
static u32 calc_checksum(struct page *page)
static int memcmp_pages(struct page *page1, struct page *page2)
static inline int pages_identical(struct page *page1, struct page *page2)
static int write_protect_page(struct vm_area_struct *vma, struct page *page, pte_t *orig_pte)
static int replace_page(struct vm_area_struct *vma, struct page *page, struct page *kpage, pte_t orig_pte)
static int try_to_merge_one_page(struct vm_area_struct *vma, struct page *page, struct page *kpage)
static int try_to_merge_with_ksm_page(struct rmap_item *rmap_item, struct page *page, struct page *kpage)
static struct page *try_to_merge_two_pages(struct rmap_item *rmap_item, struct page *page, struct rmap_item *tree_rmap_item, struct page *tree_page)
static __always_inline bool __is_page_sharing_candidate(struct stable_node *stable_node, int offset)
static __always_inline bool is_page_sharing_candidate(struct stable_node *stable_node)
static struct page *stable_node_dup(struct stable_node **_stable_node_dup, struct stable_node **_stable_node, struct rb_root *root, bool prune_stale_stable_nodes)
static struct stable_node *stable_node_dup_any(struct stable_node *stable_node, struct rb_root *root)
static struct page *__stable_node_chain(struct stable_node **_stable_node_dup, struct stable_node **_stable_node, struct rb_root *root, bool prune_stale_stable_nodes)
static __always_inline struct page *chain_prune(struct stable_node **s_n_d, struct stable_node **s_n, struct rb_root *root)
static __always_inline struct page *chain(struct stable_node **s_n_d, struct stable_node *s_n, struct rb_root *root)
static struct page *stable_tree_search(struct page *page)
static struct stable_node *stable_tree_insert(struct page *kpage)
static struct rmap_item *unstable_tree_search_insert(struct rmap_item *rmap_item, struct page *page, struct page **tree_pagep)
static void stable_tree_append(struct rmap_item *rmap_item, struct stable_node *stable_node, bool max_page_sharing_bypass)
static void cmp_and_merge_page(struct page *page, struct rmap_item *rmap_item)
static struct rmap_item *get_next_rmap_item(struct mm_slot *mm_slot, struct rmap_item **rmap_list, unsigned long addr)
static struct rmap_item *scan_get_next_rmap_item(struct page **page)
static void ksm_do_scan(unsigned int scan_npages)
static int ksmd_should_run(void)
static int ksm_scan_thread(void *nothing)
int ksm_madvise(struct vm_area_struct *vma, unsigned long start, unsigned long end, int advice, unsigned long *vm_flags)
int __ksm_enter(struct mm_struct *mm)
void __ksm_exit(struct mm_struct *mm)
struct page *ksm_might_need_to_copy(struct page *page, struct vm_area_struct *vma, unsigned long address)
void rmap_walk_ksm(struct page *page, struct rmap_walk_control *rwc)
void ksm_migrate_page(struct page *newpage, struct page *oldpage)
static void wait_while_offlining(void)
static bool stable_node_dup_remove_range(struct stable_node *stable_node, unsigned long start_pfn, unsigned long end_pfn)
static bool stable_node_chain_remove_range(struct stable_node *stable_node, unsigned long start_pfn, unsigned long end_pfn, struct rb_root *root)
static void ksm_check_stable_tree(unsigned long start_pfn, unsigned long end_pfn)
static int ksm_memory_callback(struct notifier_block *self, unsigned long action, void *arg)
smp_mb()
;wake_up_bit(&ksm_run, ilog2(KSM_RUN_OFFLINE)
)
; break;}return NOTIFY_OK; } static void wait_while_offlining(void)
static ssize_t sleep_millisecs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t sleep_millisecs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t pages_to_scan_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t pages_to_scan_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t run_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t run_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t merge_across_nodes_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t merge_across_nodes_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t use_zero_pages_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t use_zero_pages_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
return sprintf(buf, "%u\n", ksm_use_zero_pages)
; } static ssize_t use_zero_pages_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t max_page_sharing_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t max_page_sharing_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t pages_shared_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t pages_sharing_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t pages_unshared_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t pages_volatile_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t stable_node_dups_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t stable_node_chains_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t stable_node_chains_prune_millisecs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t stable_node_chains_prune_millisecs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
static ssize_t full_scans_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static int __init ksm_init(void)
  22 struct kobject *kobj
  22 struct kobj_attribute *attr
  15 char *buf
  13 struct page *page
  12 struct stable_node *stable_node
  11 void
   9 struct rmap_item *rmap_item
   9 struct rb_root *root
   7 struct vm_area_struct *vma
   7 size_t count
   7 const char *buf
   6 struct mm_struct *mm
   5 struct stable_node *dup
   4 struct page *kpage
   4 struct mm_slot *mm_slot
   3 unsigned long start_pfn
   3 unsigned long end_pfn
   3 unsigned long addr
   3 struct stable_node *chain
   2 unsigned long start
   2 unsigned long end
   2 struct stable_node **s_n_d
   2 struct stable_node **_stable_node_dup
   2 struct stable_node **_stable_node
   2 struct rmap_item **rmap_list
   2 struct page *page2
   2 struct page *page1
   2 bool prune_stale_stable_nodes
   1 void *nothing
   1 void *arg
   1 unsigned long kpfn
   1 unsigned long address
   1 unsigned long action
   1 unsigned long *vm_flags
   1 unsigned int scan_npages
   1 struct stable_node *s_n
   1 struct stable_node **s_n
   1 struct rmap_walk_control *rwc
   1 struct rmap_item *tree_rmap_item
   1 struct page *tree_page
   1 struct page *oldpage
   1 struct page *newpage
   1 struct page **tree_pagep
   1 struct page **page
   1 struct notifier_block *self
   1 pte_t orig_pte
   1 pte_t *orig_pte
   1 ksm_use_zero_pages
   1 int offset
   1 int advice
   1 ilog2KSM_RUN_OFFLINE
   1 buf
   1 bool max_page_sharing_bypass
   1 bool lock_it
   1 &ksm_run
   1 "%u\n"
