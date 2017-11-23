
static int prealloc_memcg_shrinker(struct shrinker *shrinker)
static void unregister_memcg_shrinker(struct shrinker *shrinker)
down_write(&shrinker_rwsem)
;idr_remove(&shrinker_idr, id)
;up_write(&shrinker_rwsem)
; } static int prealloc_memcg_shrinker(struct shrinker *shrinker)
static void unregister_memcg_shrinker(struct shrinker *shrinker)
static bool global_reclaim(struct scan_control *sc)
static bool sane_reclaim(struct scan_control *sc)
static void set_memcg_congestion(pg_data_t *pgdat, struct mem_cgroup *memcg, bool congested)
static bool memcg_congested(pg_data_t *pgdat, struct mem_cgroup *memcg)
} static bool global_reclaim(struct scan_control *sc)
static bool sane_reclaim(struct scan_control *sc)
static inline void set_memcg_congestion(struct pglist_data *pgdat, struct mem_cgroup *memcg, bool congested)
static inline bool memcg_congested(struct pglist_data *pgdat, struct mem_cgroup *memcg)
unsigned long zone_reclaimable_pages(struct zone *zone)
unsigned long lruvec_lru_size(struct lruvec *lruvec, enum lru_list lru, int zone_idx)
int prealloc_shrinker(struct shrinker *shrinker)
void free_prealloced_shrinker(struct shrinker *shrinker)
void register_shrinker_prepared(struct shrinker *shrinker)
int register_shrinker(struct shrinker *shrinker)
void unregister_shrinker(struct shrinker *shrinker)
static unsigned long do_shrink_slab(struct shrink_control *shrinkctl, struct shrinker *shrinker, int priority)
static unsigned long shrink_slab_memcg(gfp_t gfp_mask, int nid, struct mem_cgroup *memcg, int priority)
freed = freed ? : 1;break; }} unlock:up_read(&shrinker_rwsem)
;return freed; } static unsigned long shrink_slab_memcg(gfp_t gfp_mask, int nid, struct mem_cgroup *memcg, int priority)
static unsigned long shrink_slab(gfp_t gfp_mask, int nid, struct mem_cgroup *memcg, int priority)
void drop_slab_node(int nid)
void drop_slab(void)
static inline int is_page_cache_freeable(struct page *page)
static int may_write_to_inode(struct inode *inode, struct scan_control *sc)
static void handle_write_error(struct address_space *mapping, struct page *page, int error)
static pageout_t pageout(struct page *page, struct address_space *mapping, struct scan_control *sc)
static int __remove_mapping(struct address_space *mapping, struct page *page, bool reclaimed)
int remove_mapping(struct address_space *mapping, struct page *page)
void putback_lru_page(struct page *page)
static enum page_references page_check_references(struct page *page, struct scan_control *sc)
static void page_check_dirty_writeback(struct page *page, bool *dirty, bool *writeback)
static unsigned long shrink_page_list(struct list_head *page_list, struct pglist_data *pgdat, struct scan_control *sc, enum ttu_flags ttu_flags, struct reclaim_stat *stat, bool force_reclaim)
unsigned long reclaim_clean_pages_from_list(struct zone *zone, struct list_head *page_list)
int __isolate_lru_page(struct page *page, isolate_mode_t mode)
static __always_inline void update_lru_sizes(struct lruvec *lruvec, enum lru_list lru, unsigned long *nr_zone_taken)
static unsigned long isolate_lru_pages(unsigned long nr_to_scan, struct lruvec *lruvec, struct list_head *dst, unsigned long *nr_scanned, struct scan_control *sc, isolate_mode_t mode, enum lru_list lru)
int isolate_lru_page(struct page *page)
static int too_many_isolated(struct pglist_data *pgdat, int file, struct scan_control *sc)
static noinline_for_stack void putback_inactive_pages(struct lruvec *lruvec, struct list_head *page_list)
static int current_may_throttle(void)
static noinline_for_stack unsigned long shrink_inactive_list(unsigned long nr_to_scan, struct lruvec *lruvec, struct scan_control *sc, enum lru_list lru)
static unsigned move_active_pages_to_lru(struct lruvec *lruvec, struct list_head *list, struct list_head *pages_to_free, enum lru_list lru)
static void shrink_active_list(unsigned long nr_to_scan, struct lruvec *lruvec, struct scan_control *sc, enum lru_list lru)
static bool inactive_list_is_low(struct lruvec *lruvec, bool file, struct mem_cgroup *memcg, struct scan_control *sc, bool actual_reclaim)
static unsigned long shrink_list(enum lru_list lru, unsigned long nr_to_scan, struct lruvec *lruvec, struct mem_cgroup *memcg, struct scan_control *sc)
static void get_scan_count(struct lruvec *lruvec, struct mem_cgroup *memcg, struct scan_control *sc, unsigned long *nr, unsigned long *lru_pages)
static void shrink_node_memcg(struct pglist_data *pgdat, struct mem_cgroup *memcg, struct scan_control *sc, unsigned long *lru_pages)
static bool in_reclaim_compaction(struct scan_control *sc)
static inline bool should_continue_reclaim(struct pglist_data *pgdat, unsigned long nr_reclaimed, unsigned long nr_scanned, struct scan_control *sc)
static bool pgdat_memcg_congested(pg_data_t *pgdat, struct mem_cgroup *memcg)
static bool shrink_node(pg_data_t *pgdat, struct scan_control *sc)
static inline bool compaction_ready(struct zone *zone, struct scan_control *sc)
static void shrink_zones(struct zonelist *zonelist, struct scan_control *sc)
static void snapshot_refaults(struct mem_cgroup *root_memcg, pg_data_t *pgdat)
static unsigned long do_try_to_free_pages(struct zonelist *zonelist, struct scan_control *sc)
static bool allow_direct_reclaim(pg_data_t *pgdat)
static bool throttle_direct_reclaim(gfp_t gfp_mask, struct zonelist *zonelist, nodemask_t *nodemask)
unsigned long try_to_free_pages(struct zonelist *zonelist, int order, gfp_t gfp_mask, nodemask_t *nodemask)
unsigned long mem_cgroup_shrink_node(struct mem_cgroup *memcg, gfp_t gfp_mask, bool noswap, pg_data_t *pgdat, unsigned long *nr_scanned)
unsigned long try_to_free_mem_cgroup_pages(struct mem_cgroup *memcg, unsigned long nr_pages, gfp_t gfp_mask, bool may_swap)
static void age_active_anon(struct pglist_data *pgdat, struct scan_control *sc)
static bool pgdat_balanced(pg_data_t *pgdat, int order, int classzone_idx)
static void clear_pgdat_congested(pg_data_t *pgdat)
static bool prepare_kswapd_sleep(pg_data_t *pgdat, int order, int classzone_idx)
static bool kswapd_shrink_node(pg_data_t *pgdat, struct scan_control *sc)
static int balance_pgdat(pg_data_t *pgdat, int order, int classzone_idx)
static enum zone_type kswapd_classzone_idx(pg_data_t *pgdat, enum zone_type classzone_idx)
static void kswapd_try_to_sleep(pg_data_t *pgdat, int alloc_order, int reclaim_order, unsigned int classzone_idx)
static int kswapd(void *p)
void wakeup_kswapd(struct zone *zone, gfp_t gfp_flags, int order, enum zone_type classzone_idx)
unsigned long shrink_all_memory(unsigned long nr_to_reclaim)
static int kswapd_cpu_online(unsigned int cpu)
int kswapd_run(int nid)
void kswapd_stop(int nid)
static int __init kswapd_init(void)
static inline unsigned long node_unmapped_file_pages(struct pglist_data *pgdat)
static unsigned long node_pagecache_reclaimable(struct pglist_data *pgdat)
static int __node_reclaim(struct pglist_data *pgdat, gfp_t gfp_mask, unsigned int order)
int node_reclaim(struct pglist_data *pgdat, gfp_t gfp_mask, unsigned int order)
int page_evictable(struct page *page)
void check_move_unevictable_pages(struct page **pages, int nr_pages)
  24 struct scan_control *sc
  14 struct mem_cgroup *memcg
  14 pg_data_t *pgdat
  11 struct pglist_data *pgdat
  11 struct page *page
  10 struct shrinker *shrinker
  10 struct lruvec *lruvec
   9 gfp_t gfp_mask
   7 enum lru_list lru
   6 int nid
   5 int order
   4 unsigned long nr_to_scan
   4 struct zonelist *zonelist
   4 struct zone *zone
   4 struct address_space *mapping
   4 int priority
   3 void
   3 struct list_head *page_list
   3 int classzone_idx
   3 &shrinker_rwsem
   2 unsigned long *nr_scanned
   2 unsigned long *lru_pages
   2 unsigned int order
   2 nodemask_t *nodemask
   2 isolate_mode_t mode
   2 enum zone_type classzone_idx
   2 bool congested
   1 void *p
   1 unsigned long nr_to_reclaim
   1 unsigned long nr_scanned
   1 unsigned long nr_reclaimed
   1 unsigned long nr_pages
   1 unsigned long *nr_zone_taken
   1 unsigned long *nr
   1 unsigned int cpu
   1 unsigned int classzone_idx
   1 struct shrink_control *shrinkctl
   1 struct reclaim_stat *stat
   1 struct page **pages
   1 struct mem_cgroup *root_memcg
   1 struct list_head *pages_to_free
   1 struct list_head *list
   1 struct list_head *dst
   1 struct inode *inode
   1 int zone_idx
   1 int reclaim_order
   1 int nr_pages
   1 int file
   1 int error
   1 int alloc_order
   1 id
   1 gfp_t gfp_flags
   1 enum ttu_flags ttu_flags
   1 bool reclaimed
   1 bool noswap
   1 bool may_swap
   1 bool force_reclaim
   1 bool file
   1 bool actual_reclaim
   1 bool *writeback
   1 bool *dirty
   1 &shrinker_idr
