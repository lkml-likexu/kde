
int migrate_prep(void)
int migrate_prep_local(void)
int isolate_movable_page(struct page *page, isolate_mode_t mode)
void putback_movable_page(struct page *page)
void putback_movable_pages(struct list_head *l)
static bool remove_migration_pte(struct page *page, struct vm_area_struct *vma, unsigned long addr, void *old)
void remove_migration_ptes(struct page *old, struct page *new, bool locked)
void __migration_entry_wait(struct mm_struct *mm, pte_t *ptep, spinlock_t *ptl)
void migration_entry_wait(struct mm_struct *mm, pmd_t *pmd, unsigned long address)
void migration_entry_wait_huge(struct vm_area_struct *vma, struct mm_struct *mm, pte_t *pte)
void pmd_migration_entry_wait(struct mm_struct *mm, pmd_t *pmd)
static bool buffer_migrate_lock_buffers(struct buffer_head *head, enum migrate_mode mode)
bh = bh->b_this_page;} while (bh != head)
;return true; } static inline bool buffer_migrate_lock_buffers(struct buffer_head *head, enum migrate_mode mode)
int migrate_page_move_mapping(struct address_space *mapping, struct page *newpage, struct page *page, struct buffer_head *head, enum migrate_mode mode, int extra_count)
int migrate_huge_page_move_mapping(struct address_space *mapping, struct page *newpage, struct page *page)
static void __copy_gigantic_page(struct page *dst, struct page *src, int nr_pages)
static void copy_huge_page(struct page *dst, struct page *src)
void migrate_page_states(struct page *newpage, struct page *page)
void migrate_page_copy(struct page *newpage, struct page *page)
int migrate_page(struct address_space *mapping, struct page *newpage, struct page *page, enum migrate_mode mode)
int buffer_migrate_page(struct address_space *mapping, struct page *newpage, struct page *page, enum migrate_mode mode)
static int writeout(struct address_space *mapping, struct page *page)
static int fallback_migrate_page(struct address_space *mapping, struct page *newpage, struct page *page, enum migrate_mode mode)
static int move_to_new_page(struct page *newpage, struct page *page, enum migrate_mode mode)
static int __unmap_and_move(struct page *page, struct page *newpage, int force, enum migrate_mode mode)
static ICE_noinline int unmap_and_move(new_page_t get_new_page, free_page_t put_new_page, unsigned long private, struct page *page, int force, enum migrate_mode mode, enum migrate_reason reason)
static int unmap_and_move_huge_page(new_page_t get_new_page, free_page_t put_new_page, unsigned long private, struct page *hpage, int force, enum migrate_mode mode, int reason)
int migrate_pages(struct list_head *from, new_page_t get_new_page, free_page_t put_new_page, unsigned long private, enum migrate_mode mode, int reason)
static int store_status(int __user *status, int start, int value, int nr)
static int do_move_pages_to_node(struct mm_struct *mm, struct list_head *pagelist, int node)
static int add_page_for_migration(struct mm_struct *mm, unsigned long addr, int node, struct list_head *pagelist, bool migrate_all)
static int do_pages_move(struct mm_struct *mm, nodemask_t task_nodes, unsigned long nr_pages, const void __user * __user *pages, const int __user *nodes, int __user *status, int flags)
static void do_pages_stat_array(struct mm_struct *mm, unsigned long nr_pages, const void __user **pages, int *status)
static int do_pages_stat(struct mm_struct *mm, unsigned long nr_pages, const void __user * __user *pages, int __user *status)
static int kernel_move_pages(pid_t pid, unsigned long nr_pages, const void __user * __user *pages, const int __user *nodes, int __user *status, int flags)
SYSCALL_DEFINE6(move_pages, pid_t, pid, unsigned long, nr_pages, const void __user * __user *, pages, const int __user *, nodes, int __user *, status, int, flags)
COMPAT_SYSCALL_DEFINE6(move_pages, pid_t, pid, compat_ulong_t, nr_pages, compat_uptr_t __user *, pages32, const int __user *, nodes, int __user *, status, int, flags)
static bool migrate_balanced_pgdat(struct pglist_data *pgdat, unsigned long nr_migrate_pages)
static struct page *alloc_misplaced_dst_page(struct page *page, unsigned long data)
static int numamigrate_isolate_page(pg_data_t *pgdat, struct page *page)
bool pmd_trans_migrating(pmd_t pmd)
int migrate_misplaced_page(struct page *page, struct vm_area_struct *vma, int node)
int migrate_misplaced_transhuge_page(struct mm_struct *mm, struct vm_area_struct *vma, pmd_t *pmd, pmd_t entry, unsigned long address, struct page *page, int node)
static int migrate_vma_collect_hole(unsigned long start, unsigned long end, struct mm_walk *walk)
static int migrate_vma_collect_skip(unsigned long start, unsigned long end, struct mm_walk *walk)
static int migrate_vma_collect_pmd(pmd_t *pmdp, unsigned long start, unsigned long end, struct mm_walk *walk)
static void migrate_vma_collect(struct migrate_vma *migrate)
static bool migrate_vma_check_page(struct page *page)
static void migrate_vma_prepare(struct migrate_vma *migrate)
static void migrate_vma_unmap(struct migrate_vma *migrate)
static void migrate_vma_insert_page(struct migrate_vma *migrate, unsigned long addr, struct page *page, unsigned long *src, unsigned long *dst)
static void migrate_vma_pages(struct migrate_vma *migrate)
static void migrate_vma_finalize(struct migrate_vma *migrate)
int migrate_vma(const struct migrate_vma_ops *ops, struct vm_area_struct *vma, unsigned long start, unsigned long end, unsigned long *src, unsigned long *dst, void *private)
  20 struct page *page
  11 enum migrate_mode mode
  10 struct mm_struct *mm
   9 struct page *newpage
   6 struct migrate_vma *migrate
   6 struct address_space *mapping
   5 struct vm_area_struct *vma
   4 unsigned long start
   4 unsigned long nr_pages
   4 unsigned long end
   4 int node
   4 int __user *status
   3 unsigned long private
   3 unsigned long addr
   3 struct mm_walk *walk
   3 struct buffer_head *head
   3 pmd_t *pmd
   3 new_page_t get_new_page
   3 int force
   3 free_page_t put_new_page
   3 const void __user * __user *pages
   2 void
   2 unsigned long address
   2 unsigned long *src
   2 unsigned long *dst
   2 struct page *src
   2 struct page *dst
   2 struct list_head *pagelist
   2 status
   2 pid_t
   2 pid
   2 nr_pages
   2 nodes
   2 move_pages
   2 int reason
   2 int flags
   2 int __user *
   2 int
   2 flags
   2 const int __user *nodes
   2 const int __user *
   1 void *private
   1 void *old
   1 unsigned long nr_migrate_pages
   1 unsigned long data
   1 unsigned long
   1 struct pglist_data *pgdat
   1 struct page *old
   1 struct page *new
   1 struct page *hpage
   1 struct list_head *l
   1 struct list_head *from
   1 spinlock_t *ptl
   1 pte_t *ptep
   1 pte_t *pte
   1 pmd_t pmd
   1 pmd_t entry
   1 pmd_t *pmdp
   1 pid_t pid
   1 pg_data_t *pgdat
   1 pages32
   1 pages
   1 nodemask_t task_nodes
   1 isolate_mode_t mode
   1 int value
   1 int start
   1 int nr_pages
   1 int nr
   1 int extra_count
   1 int *status
   1 enum migrate_reason reason
   1 const void __user **pages
   1 const void __user * __user *
   1 const struct migrate_vma_ops *ops
   1 compat_uptr_t __user *
   1 compat_ulong_t
   1 bool migrate_all
   1 bool locked
   1 bh != head
