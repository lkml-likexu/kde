
EXPORT_SYMBOL_GPL(nr_swap_pages);
EXPORT_SYMBOL_GPL(add_swap_extent);
EXPORT_SYMBOL_GPL(__page_file_mapping);
EXPORT_SYMBOL_GPL(__page_file_index);
\n
static inline unsigned char swap_count(unsigned char ent)
static int __try_to_reclaim_swap(struct swap_info_struct *si, unsigned long offset, unsigned long flags)
static int discard_swap(struct swap_info_struct *si)
static void discard_swap_cluster(struct swap_info_struct *si, pgoff_t start_page, pgoff_t nr_pages)
static inline void cluster_set_flag(struct swap_cluster_info *info, unsigned int flag)
static inline unsigned int cluster_count(struct swap_cluster_info *info)
static inline void cluster_set_count(struct swap_cluster_info *info, unsigned int c)
static inline void cluster_set_count_flag(struct swap_cluster_info *info, unsigned int c, unsigned int f)
static inline unsigned int cluster_next(struct swap_cluster_info *info)
static inline void cluster_set_next(struct swap_cluster_info *info, unsigned int n)
static inline void cluster_set_next_flag(struct swap_cluster_info *info, unsigned int n, unsigned int f)
static inline bool cluster_is_free(struct swap_cluster_info *info)
static inline bool cluster_is_null(struct swap_cluster_info *info)
static inline void cluster_set_null(struct swap_cluster_info *info)
static inline bool cluster_is_huge(struct swap_cluster_info *info)
static inline void cluster_clear_huge(struct swap_cluster_info *info)
static inline struct swap_cluster_info *lock_cluster(struct swap_info_struct *si, unsigned long offset)
static inline void unlock_cluster(struct swap_cluster_info *ci)
static inline struct swap_cluster_info *lock_cluster_or_swap_info( struct swap_info_struct *si, unsigned long offset)
static inline void unlock_cluster_or_swap_info(struct swap_info_struct *si, struct swap_cluster_info *ci)
static inline bool cluster_list_empty(struct swap_cluster_list *list)
static inline unsigned int cluster_list_first(struct swap_cluster_list *list)
static void cluster_list_init(struct swap_cluster_list *list)
static void cluster_list_add_tail(struct swap_cluster_list *list, struct swap_cluster_info *ci, unsigned int idx)
static unsigned int cluster_list_del_first(struct swap_cluster_list *list, struct swap_cluster_info *ci)
static void swap_cluster_schedule_discard(struct swap_info_struct *si, unsigned int idx)
static void __free_cluster(struct swap_info_struct *si, unsigned long idx)
static void swap_do_scheduled_discard(struct swap_info_struct *si)
static void swap_discard_work(struct work_struct *work)
static void alloc_cluster(struct swap_info_struct *si, unsigned long idx)
static void free_cluster(struct swap_info_struct *si, unsigned long idx)
static void inc_cluster_info_page(struct swap_info_struct *p, struct swap_cluster_info *cluster_info, unsigned long page_nr)
static void dec_cluster_info_page(struct swap_info_struct *p, struct swap_cluster_info *cluster_info, unsigned long page_nr)
static bool scan_swap_map_ssd_cluster_conflict(struct swap_info_struct *si, unsigned long offset)
static bool scan_swap_map_try_ssd_cluster(struct swap_info_struct *si, unsigned long *offset, unsigned long *scan_base)
static void __del_from_avail_list(struct swap_info_struct *p)
static void del_from_avail_list(struct swap_info_struct *p)
static void swap_range_alloc(struct swap_info_struct *si, unsigned long offset, unsigned int nr_entries)
static void add_to_avail_list(struct swap_info_struct *p)
static void swap_range_free(struct swap_info_struct *si, unsigned long offset, unsigned int nr_entries)
static int scan_swap_map_slots(struct swap_info_struct *si, unsigned char usage, int nr, swp_entry_t slots[])
static int swap_alloc_cluster(struct swap_info_struct *si, swp_entry_t *slot)
static void swap_free_cluster(struct swap_info_struct *si, unsigned long idx)
static unsigned long scan_swap_map(struct swap_info_struct *si, unsigned char usage)
int get_swap_pages(int n_goal, swp_entry_t swp_entries[], int entry_size)
swp_entry_t get_swap_page_of_type(int type)
static struct swap_info_struct *__swap_info_get(swp_entry_t entry)
static struct swap_info_struct *_swap_info_get(swp_entry_t entry)
static struct swap_info_struct *swap_info_get(swp_entry_t entry)
static struct swap_info_struct *swap_info_get_cont(swp_entry_t entry, struct swap_info_struct *q)
static unsigned char __swap_entry_free_locked(struct swap_info_struct *p, unsigned long offset, unsigned char usage)
static unsigned char __swap_entry_free(struct swap_info_struct *p, swp_entry_t entry, unsigned char usage)
static void swap_entry_free(struct swap_info_struct *p, swp_entry_t entry)
void swap_free(swp_entry_t entry)
void put_swap_page(struct page *page, swp_entry_t entry)
int split_swap_cluster(swp_entry_t entry)
static int swp_entry_cmp(const void *ent1, const void *ent2)
void swapcache_free_entries(swp_entry_t *entries, int n)
int page_swapcount(struct page *page)
int __swap_count(struct swap_info_struct *si, swp_entry_t entry)
static int swap_swapcount(struct swap_info_struct *si, swp_entry_t entry)
int __swp_swapcount(swp_entry_t entry)
int swp_swapcount(swp_entry_t entry)
static bool swap_page_trans_huge_swapped(struct swap_info_struct *si, swp_entry_t entry)
static bool page_swapped(struct page *page)
static int page_trans_huge_map_swapcount(struct page *page, int *total_mapcount, int *total_swapcount)
bool reuse_swap_page(struct page *page, int *total_map_swapcount)
int try_to_free_swap(struct page *page)
int free_swap_and_cache(swp_entry_t entry)
int swap_type_of(dev_t device, sector_t offset, struct block_device **bdev_p)
sector_t swapdev_block(int type, pgoff_t offset)
unsigned int count_swap_pages(int type, int free)
static inline int pte_same_as_swp(pte_t pte, pte_t swp_pte)
static int unuse_pte(struct vm_area_struct *vma, pmd_t *pmd, unsigned long addr, swp_entry_t entry, struct page *page)
static int unuse_pte_range(struct vm_area_struct *vma, pmd_t *pmd, unsigned long addr, unsigned long end, swp_entry_t entry, struct page *page)
static inline int unuse_pmd_range(struct vm_area_struct *vma, pud_t *pud, unsigned long addr, unsigned long end, swp_entry_t entry, struct page *page)
static inline int unuse_pud_range(struct vm_area_struct *vma, p4d_t *p4d, unsigned long addr, unsigned long end, swp_entry_t entry, struct page *page)
static inline int unuse_p4d_range(struct vm_area_struct *vma, pgd_t *pgd, unsigned long addr, unsigned long end, swp_entry_t entry, struct page *page)
static int unuse_vma(struct vm_area_struct *vma, swp_entry_t entry, struct page *page)
static int unuse_mm(struct mm_struct *mm, swp_entry_t entry, struct page *page)
static unsigned int find_next_to_unuse(struct swap_info_struct *si, unsigned int prev, bool frontswap)
int try_to_unuse(unsigned int type, bool frontswap, unsigned long pages_to_unuse)
static void drain_mmlist(void)
static sector_t map_swap_entry(swp_entry_t entry, struct block_device **bdev)
sector_t map_swap_page(struct page *page, struct block_device **bdev)
static void destroy_swap_extents(struct swap_info_struct *sis)
int add_swap_extent(struct swap_info_struct *sis, unsigned long start_page, unsigned long nr_pages, sector_t start_block)
static int setup_swap_extents(struct swap_info_struct *sis, sector_t *span)
static int swap_node(struct swap_info_struct *p)
static void _enable_swap_info(struct swap_info_struct *p, int prio, unsigned char *swap_map, struct swap_cluster_info *cluster_info)
static void enable_swap_info(struct swap_info_struct *p, int prio, unsigned char *swap_map, struct swap_cluster_info *cluster_info, unsigned long *frontswap_map)
static void reinsert_swap_info(struct swap_info_struct *p)
bool has_usable_swap(void)
SYSCALL_DEFINE1(swapoff, const char __user *, specialfile)
static __poll_t swaps_poll(struct file *file, poll_table *wait)
static void *swap_start(struct seq_file *swap, loff_t *pos)
static void *swap_next(struct seq_file *swap, void *v, loff_t *pos)
static void swap_stop(struct seq_file *swap, void *v)
static int swap_show(struct seq_file *swap, void *v)
static int swaps_open(struct inode *inode, struct file *file)
static int __init procswaps_init(void)
static int __init max_swapfiles_check(void)
static struct swap_info_struct *alloc_swap_info(void)
static int claim_swapfile(struct swap_info_struct *p, struct inode *inode)
unsigned long generic_max_swapfile_size(void)
__weak unsigned long max_swapfile_size(void)
static unsigned long read_swap_header(struct swap_info_struct *p, union swap_header *swap_header, struct inode *inode)
static int setup_swap_map_and_extents(struct swap_info_struct *p, union swap_header *swap_header, unsigned char *swap_map, struct swap_cluster_info *cluster_info, unsigned long maxpages, sector_t *span)
static bool swap_discardable(struct swap_info_struct *si)
SYSCALL_DEFINE2(swapon, const char __user *, specialfile, int, swap_flags)
void si_swapinfo(struct sysinfo *val)
static int __swap_duplicate(swp_entry_t entry, unsigned char usage)
void swap_shmem_alloc(swp_entry_t entry)
int swap_duplicate(swp_entry_t entry)
int swapcache_prepare(swp_entry_t entry)
struct swap_info_struct *swp_swap_info(swp_entry_t entry)
struct swap_info_struct *page_swap_info(struct page *page)
struct address_space *__page_file_mapping(struct page *page)
pgoff_t __page_file_index(struct page *page)
int add_swap_count_continuation(swp_entry_t entry, gfp_t gfp_mask)
static bool swap_count_continued(struct swap_info_struct *si, pgoff_t offset, unsigned char count)
static void free_swap_count_continuations(struct swap_info_struct *si)
void mem_cgroup_throttle_swaprate(struct mem_cgroup *memcg, int node, gfp_t gfp_mask)
static int __init swapfile_init(void)
\n
     29 swp_entry_t entry
     26 struct swap_info_struct *si
     17 struct page *page
     15 struct swap_info_struct *p
     12 struct swap_cluster_info *info
      8 void
      7 unsigned long offset
      6 struct vm_area_struct *vma
      5 unsigned long addr
      5 unsigned char usage
      5 struct swap_cluster_list *list
      5 struct swap_cluster_info *cluster_info
      4 unsigned long idx
      4 unsigned long end
      4 struct swap_cluster_info *ci
      4 struct seq_file *swap
      3 void *v
      3 unsigned char *swap_map
      3 struct swap_info_struct *sis
      3 struct inode *inode
      3 int type
      2 unsigned long page_nr
      2 unsigned int nr_entries
      2 unsigned int n
      2 unsigned int idx
      2 unsigned int f
      2 unsigned int c
      2 union swap_header *swap_header
      2 struct file *file
      2 struct block_device **bdev
      2 specialfile
      2 sector_t *span
      2 pmd_t *pmd
      2 pgoff_t offset
      2 loff_t *pos
      2 int prio
      2 gfp_t gfp_mask
      2 const char __user *
      2 bool frontswap
      1 unsigned long start_page
      1 unsigned long *scan_base
      1 unsigned long pages_to_unuse
      1 unsigned long *offset
      1 unsigned long nr_pages
      1 unsigned long maxpages
      1 unsigned long *frontswap_map
      1 unsigned long flags
      1 unsigned int type
      1 unsigned int prev
      1 unsigned int flag
      1 unsigned char ent
      1 unsigned char count
      1 swp_entry_t swp_entries[]
      1 swp_entry_t slots[]
      1 swp_entry_t *slot
      1 swp_entry_t *entries
      1 swapon
      1 swapoff
      1 swap_flags
      1 struct work_struct *work
      1 struct sysinfo *val
      1 struct swap_info_struct *q
      1 struct mm_struct *mm
      1 struct mem_cgroup *memcg
      1 struct block_device **bdev_p
      1 sector_t start_block
      1 sector_t offset
      1 pud_t *pud
      1 pte_t swp_pte
      1 pte_t pte
      1 poll_table *wait
      1 pgoff_t start_page
      1 pgoff_t nr_pages
      1 pgd_t *pgd
      1 __page_file_mapping
      1 __page_file_index
      1 p4d_t *p4d
      1 nr_swap_pages
      1 int *total_swapcount
      1 int *total_map_swapcount
      1 int *total_mapcount
      1 int nr
      1 int node
      1 int n_goal
      1 int n
      1 int free
      1 int entry_size
      1 int
      1 dev_t device
      1 const void *ent2
      1 const void *ent1
      1 add_swap_extent
