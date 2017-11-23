
static bool do_memsw_account(void)
struct vmpressure *memcg_to_vmpressure(struct mem_cgroup *memcg)
struct cgroup_subsys_state *vmpressure_to_css(struct vmpressure *vmpr)
void memcg_get_cache_ids(void)
void memcg_put_cache_ids(void)
static void memcg_free_shrinker_map_rcu(struct rcu_head *head)
static int memcg_expand_one_shrinker_map(struct mem_cgroup *memcg, int size, int old_size)
static void memcg_free_shrinker_maps(struct mem_cgroup *memcg)
static int memcg_alloc_shrinker_maps(struct mem_cgroup *memcg)
int memcg_expand_shrinker_maps(int new_id)
void memcg_set_shrinker_bit(struct mem_cgroup *memcg, int nid, int shrinker_id)
static int memcg_alloc_shrinker_maps(struct mem_cgroup *memcg)
struct cgroup_subsys_state *mem_cgroup_css_from_page(struct page *page)
ino_t page_cgroup_ino(struct page *page)
static struct mem_cgroup_per_node * mem_cgroup_page_nodeinfo(struct mem_cgroup *memcg, struct page *page)
static struct mem_cgroup_tree_per_node * soft_limit_tree_node(int nid)
static struct mem_cgroup_tree_per_node * soft_limit_tree_from_page(struct page *page)
static void __mem_cgroup_insert_exceeded(struct mem_cgroup_per_node *mz, struct mem_cgroup_tree_per_node *mctz, unsigned long new_usage_in_excess)
static void __mem_cgroup_remove_exceeded(struct mem_cgroup_per_node *mz, struct mem_cgroup_tree_per_node *mctz)
static void mem_cgroup_remove_exceeded(struct mem_cgroup_per_node *mz, struct mem_cgroup_tree_per_node *mctz)
static unsigned long soft_limit_excess(struct mem_cgroup *memcg)
static void mem_cgroup_update_tree(struct mem_cgroup *memcg, struct page *page)
static void mem_cgroup_remove_from_trees(struct mem_cgroup *memcg)
static struct mem_cgroup_per_node * __mem_cgroup_largest_soft_limit_node(struct mem_cgroup_tree_per_node *mctz)
static struct mem_cgroup_per_node * mem_cgroup_largest_soft_limit_node(struct mem_cgroup_tree_per_node *mctz)
static unsigned long memcg_sum_events(struct mem_cgroup *memcg, int event)
static void mem_cgroup_charge_statistics(struct mem_cgroup *memcg, struct page *page, bool compound, int nr_pages)
unsigned long mem_cgroup_node_nr_lru_pages(struct mem_cgroup *memcg, int nid, unsigned int lru_mask)
static unsigned long mem_cgroup_nr_lru_pages(struct mem_cgroup *memcg, unsigned int lru_mask)
static bool mem_cgroup_event_ratelimit(struct mem_cgroup *memcg, enum mem_cgroup_events_target target)
static void memcg_check_events(struct mem_cgroup *memcg, struct page *page)
struct mem_cgroup *mem_cgroup_from_task(struct task_struct *p)
struct mem_cgroup *get_mem_cgroup_from_mm(struct mm_struct *mm)
struct mem_cgroup *get_mem_cgroup_from_page(struct page *page)
static __always_inline struct mem_cgroup *get_mem_cgroup_from_current(void)
struct mem_cgroup *mem_cgroup_iter(struct mem_cgroup *root, struct mem_cgroup *prev, struct mem_cgroup_reclaim_cookie *reclaim)
void mem_cgroup_iter_break(struct mem_cgroup *root, struct mem_cgroup *prev)
static void invalidate_reclaim_iterators(struct mem_cgroup *dead_memcg)
int mem_cgroup_scan_tasks(struct mem_cgroup *memcg, int (*fn)
(struct task_struct *, void *)
, void *arg)
struct lruvec *mem_cgroup_page_lruvec(struct page *page, struct pglist_data *pgdat)
void mem_cgroup_update_lru_size(struct lruvec *lruvec, enum lru_list lru, int zid, int nr_pages)
bool task_in_mem_cgroup(struct task_struct *task, struct mem_cgroup *memcg)
static unsigned long mem_cgroup_margin(struct mem_cgroup *memcg)
static bool mem_cgroup_under_move(struct mem_cgroup *memcg)
static bool mem_cgroup_wait_acct_move(struct mem_cgroup *memcg)
define K(x)
((x)
<< (PAGE_SHIFT-10)
)
void mem_cgroup_print_oom_info(struct mem_cgroup *memcg, struct task_struct *p)
unsigned long mem_cgroup_get_max(struct mem_cgroup *memcg)
static bool mem_cgroup_out_of_memory(struct mem_cgroup *memcg, gfp_t gfp_mask, int order)
static bool test_mem_cgroup_node_reclaimable(struct mem_cgroup *memcg, int nid, bool noswap)
static void mem_cgroup_may_update_nodemask(struct mem_cgroup *memcg)
int mem_cgroup_select_victim_node(struct mem_cgroup *memcg)
memcg->last_scanned_node = node;return node; } int mem_cgroup_select_victim_node(struct mem_cgroup *memcg)
static int mem_cgroup_soft_reclaim(struct mem_cgroup *root_memcg, pg_data_t *pgdat, gfp_t gfp_mask, unsigned long *total_scanned)
static bool mem_cgroup_oom_trylock(struct mem_cgroup *memcg)
static void mem_cgroup_oom_unlock(struct mem_cgroup *memcg)
static void mem_cgroup_mark_under_oom(struct mem_cgroup *memcg)
static void mem_cgroup_unmark_under_oom(struct mem_cgroup *memcg)
static int memcg_oom_wake_function(wait_queue_entry_t *wait, unsigned mode, int sync, void *arg)
static void memcg_oom_recover(struct mem_cgroup *memcg)
static enum oom_status mem_cgroup_oom(struct mem_cgroup *memcg, gfp_t mask, int order)
bool mem_cgroup_oom_synchronize(bool handle)
struct mem_cgroup *mem_cgroup_get_oom_group(struct task_struct *victim, struct mem_cgroup *oom_domain)
void mem_cgroup_print_oom_group(struct mem_cgroup *memcg)
struct mem_cgroup *lock_page_memcg(struct page *page)
void __unlock_page_memcg(struct mem_cgroup *memcg)
void unlock_page_memcg(struct page *page)
static bool consume_stock(struct mem_cgroup *memcg, unsigned int nr_pages)
static void drain_stock(struct memcg_stock_pcp *stock)
static void drain_local_stock(struct work_struct *dummy)
static void refill_stock(struct mem_cgroup *memcg, unsigned int nr_pages)
static void drain_all_stock(struct mem_cgroup *root_memcg)
static int memcg_hotplug_cpu_dead(unsigned int cpu)
static void reclaim_high(struct mem_cgroup *memcg, unsigned int nr_pages, gfp_t gfp_mask)
static void high_work_func(struct work_struct *work)
void mem_cgroup_handle_over_high(void)
static int try_charge(struct mem_cgroup *memcg, gfp_t gfp_mask, unsigned int nr_pages)
static void cancel_charge(struct mem_cgroup *memcg, unsigned int nr_pages)
static void lock_page_lru(struct page *page, int *isolated)
static void unlock_page_lru(struct page *page, int isolated)
static void commit_charge(struct page *page, struct mem_cgroup *memcg, bool lrucare)
static int memcg_alloc_cache_id(void)
static void memcg_free_cache_id(int id)
static void memcg_kmem_cache_create_func(struct work_struct *w)
static void memcg_schedule_kmem_cache_create(struct mem_cgroup *memcg, struct kmem_cache *cachep)
static inline bool memcg_kmem_bypass(void)
struct kmem_cache *memcg_kmem_get_cache(struct kmem_cache *cachep)
void memcg_kmem_put_cache(struct kmem_cache *cachep)
int memcg_kmem_charge_memcg(struct page *page, gfp_t gfp, int order, struct mem_cgroup *memcg)
int memcg_kmem_charge(struct page *page, gfp_t gfp, int order)
memcg = get_mem_cgroup_from_current()
; ret = memcg_kmem_charge_memcg(page, gfp, order, memcg)
; if (!ret)
__SetPageKmemcg(page)
;}css_put(&memcg->css)
;return ret; }void memcg_kmem_uncharge(struct page *page, int order)
void mem_cgroup_split_huge_fixup(struct page *head)
static int mem_cgroup_move_swap_account(swp_entry_t entry, struct mem_cgroup *from, struct mem_cgroup *to)
mod_memcg_state(from, MEMCG_SWAP, -1)
; mod_memcg_state(to, MEMCG_SWAP, 1)
; return 0;}return -EINVAL; } static inline int mem_cgroup_move_swap_account(swp_entry_t entry, struct mem_cgroup *from, struct mem_cgroup *to)
static int mem_cgroup_resize_max(struct mem_cgroup *memcg, unsigned long max, bool memsw)
unsigned long mem_cgroup_soft_limit_reclaim(pg_data_t *pgdat, int order, gfp_t gfp_mask, unsigned long *total_scanned)
static inline bool memcg_has_children(struct mem_cgroup *memcg)
static int mem_cgroup_force_empty(struct mem_cgroup *memcg)
static ssize_t mem_cgroup_force_empty_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static u64 mem_cgroup_hierarchy_read(struct cgroup_subsys_state *css, struct cftype *cft)
static int mem_cgroup_hierarchy_write(struct cgroup_subsys_state *css, struct cftype *cft, u64 val)
static void accumulate_memcg_tree(struct mem_cgroup *memcg, struct accumulated_stats *acc)
static unsigned long mem_cgroup_usage(struct mem_cgroup *memcg, bool swap)
static u64 mem_cgroup_read_u64(struct cgroup_subsys_state *css, struct cftype *cft)
static int memcg_online_kmem(struct mem_cgroup *memcg)
static void memcg_offline_kmem(struct mem_cgroup *memcg)
static void memcg_free_kmem(struct mem_cgroup *memcg)
memcg_destroy_kmem_caches(memcg)
; static_branch_dec(&memcg_kmem_enabled_key)
; WARN_ON(page_counter_read(&memcg->kmem)
)
;} } static int memcg_online_kmem(struct mem_cgroup *memcg)
memcg_destroy_kmem_caches(memcg)
; static_branch_dec(&memcg_kmem_enabled_key)
; WARN_ON(page_counter_read(&memcg->kmem)
)
;} } static int memcg_online_kmem(struct mem_cgroup *memcg)
return 0; } static void memcg_offline_kmem(struct mem_cgroup *memcg)
memcg_destroy_kmem_caches(memcg)
; static_branch_dec(&memcg_kmem_enabled_key)
; WARN_ON(page_counter_read(&memcg->kmem)
)
;} } static int memcg_online_kmem(struct mem_cgroup *memcg)
return 0; } static void memcg_offline_kmem(struct mem_cgroup *memcg)
} static void memcg_free_kmem(struct mem_cgroup *memcg)
static int memcg_update_kmem_max(struct mem_cgroup *memcg, unsigned long max)
static int memcg_update_tcp_max(struct mem_cgroup *memcg, unsigned long max)
static ssize_t mem_cgroup_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static ssize_t mem_cgroup_reset(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static u64 mem_cgroup_move_charge_read(struct cgroup_subsys_state *css, struct cftype *cft)
static int mem_cgroup_move_charge_write(struct cgroup_subsys_state *css, struct cftype *cft, u64 val)
memcg->move_charge_at_immigrate = val;return 0; } static int mem_cgroup_move_charge_write(struct cgroup_subsys_state *css, struct cftype *cft, u64 val)
static int memcg_numa_stat_show(struct seq_file *m, void *v)
static int memcg_stat_show(struct seq_file *m, void *v)
static u64 mem_cgroup_swappiness_read(struct cgroup_subsys_state *css, struct cftype *cft)
static int mem_cgroup_swappiness_write(struct cgroup_subsys_state *css, struct cftype *cft, u64 val)
static void __mem_cgroup_threshold(struct mem_cgroup *memcg, bool swap)
static void mem_cgroup_threshold(struct mem_cgroup *memcg)
static int compare_thresholds(const void *a, const void *b)
static int mem_cgroup_oom_notify_cb(struct mem_cgroup *memcg)
static void mem_cgroup_oom_notify(struct mem_cgroup *memcg)
static int __mem_cgroup_usage_register_event(struct mem_cgroup *memcg, struct eventfd_ctx *eventfd, const char *args, enum res_type type)
static int mem_cgroup_usage_register_event(struct mem_cgroup *memcg, struct eventfd_ctx *eventfd, const char *args)
static int memsw_cgroup_usage_register_event(struct mem_cgroup *memcg, struct eventfd_ctx *eventfd, const char *args)
static void __mem_cgroup_usage_unregister_event(struct mem_cgroup *memcg, struct eventfd_ctx *eventfd, enum res_type type)
static void mem_cgroup_usage_unregister_event(struct mem_cgroup *memcg, struct eventfd_ctx *eventfd)
static void memsw_cgroup_usage_unregister_event(struct mem_cgroup *memcg, struct eventfd_ctx *eventfd)
static int mem_cgroup_oom_register_event(struct mem_cgroup *memcg, struct eventfd_ctx *eventfd, const char *args)
static void mem_cgroup_oom_unregister_event(struct mem_cgroup *memcg, struct eventfd_ctx *eventfd)
static int mem_cgroup_oom_control_read(struct seq_file *sf, void *v)
static int mem_cgroup_oom_control_write(struct cgroup_subsys_state *css, struct cftype *cft, u64 val)
static int memcg_wb_domain_init(struct mem_cgroup *memcg, gfp_t gfp)
static void memcg_wb_domain_exit(struct mem_cgroup *memcg)
static void memcg_wb_domain_size_changed(struct mem_cgroup *memcg)
struct wb_domain *mem_cgroup_wb_domain(struct bdi_writeback *wb)
void mem_cgroup_wb_stats(struct bdi_writeback *wb, unsigned long *pfilepages, unsigned long *pheadroom, unsigned long *pdirty, unsigned long *pwriteback)
static int memcg_wb_domain_init(struct mem_cgroup *memcg, gfp_t gfp)
static void memcg_wb_domain_exit(struct mem_cgroup *memcg)
static void memcg_wb_domain_size_changed(struct mem_cgroup *memcg)
static void memcg_event_remove(struct work_struct *work)
static int memcg_event_wake(wait_queue_entry_t *wait, unsigned mode, int sync, void *key)
static void memcg_event_ptable_queue_proc(struct file *file, wait_queue_head_t *wqh, poll_table *pt)
static ssize_t memcg_write_event_control(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static void mem_cgroup_id_remove(struct mem_cgroup *memcg)
static void mem_cgroup_id_get_many(struct mem_cgroup *memcg, unsigned int n)
static void mem_cgroup_id_put_many(struct mem_cgroup *memcg, unsigned int n)
static inline void mem_cgroup_id_get(struct mem_cgroup *memcg)
static inline void mem_cgroup_id_put(struct mem_cgroup *memcg)
struct mem_cgroup *mem_cgroup_from_id(unsigned short id)
static int alloc_mem_cgroup_per_node_info(struct mem_cgroup *memcg, int node)
static void free_mem_cgroup_per_node_info(struct mem_cgroup *memcg, int node)
static void __mem_cgroup_free(struct mem_cgroup *memcg)
static void mem_cgroup_free(struct mem_cgroup *memcg)
static struct mem_cgroup *mem_cgroup_alloc(void)
static struct cgroup_subsys_state * __ref mem_cgroup_css_alloc(struct cgroup_subsys_state *parent_css)
static int mem_cgroup_css_online(struct cgroup_subsys_state *css)
static void mem_cgroup_css_offline(struct cgroup_subsys_state *css)
static void mem_cgroup_css_released(struct cgroup_subsys_state *css)
static void mem_cgroup_css_free(struct cgroup_subsys_state *css)
static void mem_cgroup_css_reset(struct cgroup_subsys_state *css)
static int mem_cgroup_do_precharge(unsigned long count)
static struct page *mc_handle_present_pte(struct vm_area_struct *vma, unsigned long addr, pte_t ptent)
static struct page *mc_handle_swap_pte(struct vm_area_struct *vma, pte_t ptent, swp_entry_t *entry)
return page; } static struct page *mc_handle_swap_pte(struct vm_area_struct *vma, pte_t ptent, swp_entry_t *entry)
static struct page *mc_handle_file_pte(struct vm_area_struct *vma, unsigned long addr, pte_t ptent, swp_entry_t *entry)
static int mem_cgroup_move_account(struct page *page, bool compound, struct mem_cgroup *from, struct mem_cgroup *to)
static enum mc_target_type get_mctgt_type(struct vm_area_struct *vma, unsigned long addr, pte_t ptent, union mc_target *target)
static enum mc_target_type get_mctgt_type_thp(struct vm_area_struct *vma, unsigned long addr, pmd_t pmd, union mc_target *target)
VM_BUG_ON(thp_migration_supported()
&& !is_pmd_migration_entry(pmd)
)
; return ret;}page = pmd_page(pmd)
;VM_BUG_ON_PAGE(!page || !PageHead(page)
, page)
;if (!(mc.flags & MOVE_ANON)
)
return ret; ret = MC_TARGET_PAGE;get_page(page)
;target->page = page; }}return ret; } static inline enum mc_target_type get_mctgt_type_thp(struct vm_area_struct *vma, unsigned long addr, pmd_t pmd, union mc_target *target)
static int mem_cgroup_count_precharge_pte_range(pmd_t *pmd, unsigned long addr, unsigned long end, struct mm_walk *walk)
static unsigned long mem_cgroup_count_precharge(struct mm_struct *mm)
static int mem_cgroup_precharge_mc(struct mm_struct *mm)
static void __mem_cgroup_clear_mc(void)
static void mem_cgroup_clear_mc(void)
static int mem_cgroup_can_attach(struct cgroup_taskset *tset)
static void mem_cgroup_cancel_attach(struct cgroup_taskset *tset)
static int mem_cgroup_move_charge_pte_range(pmd_t *pmd, unsigned long addr, unsigned long end, struct mm_walk *walk)
static void mem_cgroup_move_charge(void)
static void mem_cgroup_move_task(void)
static void mem_cgroup_move_task(void)
mem_cgroup_move_charge()
; mem_cgroup_clear_mc()
;} } static int mem_cgroup_can_attach(struct cgroup_taskset *tset)
static void mem_cgroup_move_task(void)
mem_cgroup_move_charge()
; mem_cgroup_clear_mc()
;} } static int mem_cgroup_can_attach(struct cgroup_taskset *tset)
return 0; } static void mem_cgroup_cancel_attach(struct cgroup_taskset *tset)
static void mem_cgroup_move_task(void)
mem_cgroup_move_charge()
; mem_cgroup_clear_mc()
;} } static int mem_cgroup_can_attach(struct cgroup_taskset *tset)
return 0; } static void mem_cgroup_cancel_attach(struct cgroup_taskset *tset)
} static void mem_cgroup_move_task(void)
static void mem_cgroup_bind(struct cgroup_subsys_state *root_css)
static u64 memory_current_read(struct cgroup_subsys_state *css, struct cftype *cft)
static int memory_min_show(struct seq_file *m, void *v)
static ssize_t memory_min_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static int memory_low_show(struct seq_file *m, void *v)
static ssize_t memory_low_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static int memory_high_show(struct seq_file *m, void *v)
static ssize_t memory_high_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static int memory_max_show(struct seq_file *m, void *v)
static ssize_t memory_max_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static int memory_events_show(struct seq_file *m, void *v)
static int memory_stat_show(struct seq_file *m, void *v)
static int memory_oom_group_show(struct seq_file *m, void *v)
static ssize_t memory_oom_group_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
enum mem_cgroup_protection mem_cgroup_protected(struct mem_cgroup *root, struct mem_cgroup *memcg)
int mem_cgroup_try_charge(struct page *page, struct mm_struct *mm, gfp_t gfp_mask, struct mem_cgroup **memcgp, bool compound)
int mem_cgroup_try_charge_delay(struct page *page, struct mm_struct *mm, gfp_t gfp_mask, struct mem_cgroup **memcgp, bool compound)
void mem_cgroup_commit_charge(struct page *page, struct mem_cgroup *memcg, bool lrucare, bool compound)
void mem_cgroup_cancel_charge(struct page *page, struct mem_cgroup *memcg, bool compound)
static inline void uncharge_gather_clear(struct uncharge_gather *ug)
static void uncharge_batch(const struct uncharge_gather *ug)
static void uncharge_page(struct page *page, struct uncharge_gather *ug)
static void uncharge_list(struct list_head *page_list)
void mem_cgroup_uncharge(struct page *page)
void mem_cgroup_uncharge_list(struct list_head *page_list)
void mem_cgroup_migrate(struct page *oldpage, struct page *newpage)
void mem_cgroup_sk_alloc(struct sock *sk)
void mem_cgroup_sk_free(struct sock *sk)
bool mem_cgroup_charge_skmem(struct mem_cgroup *memcg, unsigned int nr_pages)
void mem_cgroup_uncharge_skmem(struct mem_cgroup *memcg, unsigned int nr_pages)
static int __init cgroup_memory(char *s)
static int __init mem_cgroup_init(void)
static struct mem_cgroup *mem_cgroup_id_get_online(struct mem_cgroup *memcg)
void mem_cgroup_swapout(struct page *page, swp_entry_t entry)
int mem_cgroup_try_charge_swap(struct page *page, swp_entry_t entry)
void mem_cgroup_uncharge_swap(swp_entry_t entry, unsigned int nr_pages)
long mem_cgroup_get_nr_swap_pages(struct mem_cgroup *memcg)
bool mem_cgroup_swap_full(struct page *page)
static int __init enable_swap_account(char *s)
static u64 swap_current_read(struct cgroup_subsys_state *css, struct cftype *cft)
static int swap_max_show(struct seq_file *m, void *v)
static ssize_t swap_max_write(struct kernfs_open_file *of, char *buf, size_t nbytes, loff_t off)
static int swap_events_show(struct seq_file *m, void *v)
static int __init mem_cgroup_swap_init(void)
  94 struct mem_cgroup *memcg
  27 struct page *page
  18 void
  16 struct cgroup_subsys_state *css
  12 void *v
  11 struct seq_file *m
  11 struct cftype *cft
  10 struct kernfs_open_file *of
  10 size_t nbytes
  10 loff_t off
  10 char *buf
   8 unsigned int nr_pages
   8 struct eventfd_ctx *eventfd
   7 unsigned long addr
   7 struct vm_area_struct *vma
   7 struct cgroup_taskset *tset
   7 gfp_t gfp_mask
   6 int order
   6 bool compound
   5 u64 val
   5 swp_entry_t entry
   5 struct mm_struct *mm
   5 struct mem_cgroup_tree_per_node *mctz
   5 pte_t ptent
   4 memcg
   4 int nid
   4 gfp_t gfp
   4 const char *args
   3 unsigned long max
   3 union mc_target *target
   3 swp_entry_t *entry
   3 struct mem_cgroup_per_node *mz
   3 struct mem_cgroup *to
   3 struct mem_cgroup *root
   3 struct mem_cgroup *from
   3 struct kmem_cache *cachep
   3 page_counter_read&memcg->kmem
   3 page
   3 &memcg_kmem_enabled_key
   2 x
   2 wait_queue_entry_t *wait
   2 unsigned mode
   2 unsigned long end
   2 unsigned long *total_scanned
   2 unsigned int n
   2 unsigned int lru_mask
   2 struct work_struct *work
   2 struct uncharge_gather *ug
   2 struct task_struct *p
   2 struct sock *sk
   2 struct mm_walk *walk
   2 struct mem_cgroup *root_memcg
   2 struct mem_cgroup *prev
   2 struct mem_cgroup **memcgp
   2 struct list_head *page_list
   2 struct bdi_writeback *wb
   2 pmd_t pmd
   2 pmd_t *pmd
   2 pmd
   2 pg_data_t *pgdat
   2 int sync
   2 int nr_pages
   2 int node
   2 enum res_type type
   2 char *s
   2 bool swap
   2 bool lrucare
   2 MEMCG_SWAP
   1 wait_queue_head_t *wqh
   1 void *key
   1 void *arg
   1 void *
   1 unsigned short id
   1 unsigned long new_usage_in_excess
   1 unsigned long count
   1 unsigned long *pwriteback
   1 unsigned long *pheadroom
   1 unsigned long *pfilepages
   1 unsigned long *pdirty
   1 unsigned int cpu
   1 to
   1 thp_migration_supported
   1 struct work_struct *w
   1 struct work_struct *dummy
   1 struct vmpressure *vmpr
   1 struct task_struct *victim
   1 struct task_struct *task
   1 struct task_struct *
   1 struct seq_file *sf
   1 struct rcu_head *head
   1 struct pglist_data *pgdat
   1 struct page *oldpage
   1 struct page *newpage
   1 struct page *head
   1 struct memcg_stock_pcp *stock
   1 struct mem_cgroup_reclaim_cookie *reclaim
   1 struct mem_cgroup *oom_domain
   1 struct mem_cgroup *dead_memcg
   1 struct lruvec *lruvec
   1 struct file *file
   1 struct cgroup_subsys_state *root_css
   1 struct cgroup_subsys_state *parent_css
   1 struct accumulated_stats *acc
   1 poll_table *pt
   1 order
   1 int zid
   1 int size
   1 int shrinker_id
   1 int old_size
   1 int new_id
   1 int isolated
   1 int id
   1 int event
   1 int *isolated
   1 int *fn
   1 gfp_t mask
   1 gfp
   1 from
   1 enum mem_cgroup_events_target target
   1 enum lru_list lru
   1 const void *b
   1 const void *a
   1 const struct uncharge_gather *ug
   1 bool noswap
   1 bool memsw
   1 bool handle
   1 PAGE_SHIFT-10
   1 1
   1 -1
   1 &memcg->css
   1 !ret
   1 !page || !PageHeadpage
   1 !mc.flags & MOVE_ANON
