
EXPORT_SYMBOL_GPL(split_page);
EXPORT_SYMBOL_GPL(fs_reclaim_acquire);
EXPORT_SYMBOL_GPL(fs_reclaim_release);
EXPORT_SYMBOL_GPL(nr_free_buffer_pages);
EXPORT_SYMBOL_GPL(si_mem_available);
static inline int get_pcppage_migratetype(struct page *page)
static inline void set_pcppage_migratetype(struct page *page, int migratetype)
void pm_restore_gfp_mask(void)
void pm_restrict_gfp_mask(void)
bool pm_suspended_storage(void)
static inline bool __meminit early_page_uninitialised(unsigned long pfn)
static bool __meminit defer_init(int nid, unsigned long pfn, unsigned long end_pfn)
if (end_pfn < pgdat_end_pfn(NODE_DATA(nid)
)
)
return false;nr_initialised++;if ((nr_initialised > NODE_DATA(nid)
->static_init_pgcnt)
&& NODE_DATA(nid)
->first_deferred_pfn = pfn; return true;}return false; } static inline bool early_page_uninitialised(unsigned long pfn)
static inline bool defer_init(int nid, unsigned long pfn, unsigned long end_pfn)
static inline unsigned long *get_pageblock_bitmap(struct page *page, unsigned long pfn)
static inline int pfn_to_bitidx(struct page *page, unsigned long pfn)
static __always_inline unsigned long __get_pfnblock_flags_mask(struct page *page, unsigned long pfn, unsigned long end_bitidx, unsigned long mask)
unsigned long get_pfnblock_flags_mask(struct page *page, unsigned long pfn, unsigned long end_bitidx, unsigned long mask)
static __always_inline int get_pfnblock_migratetype(struct page *page, unsigned long pfn)
void set_pfnblock_flags_mask(struct page *page, unsigned long flags, unsigned long pfn, unsigned long end_bitidx, unsigned long mask)
void set_pageblock_migratetype(struct page *page, int migratetype)
static int page_outside_zone_boundaries(struct zone *zone, struct page *page)
static int page_is_consistent(struct zone *zone, struct page *page)
return 1; }static int __maybe_unused bad_range(struct zone *zone, struct page *page)
return 0; } static inline int __maybe_unused bad_range(struct zone *zone, struct page *page)
static void bad_page(struct page *page, const char *reason, unsigned long bad_flags)
void free_compound_page(struct page *page)
void prep_compound_page(struct page *page, unsigned int order)
static int __init early_debug_pagealloc(char *buf)
static bool need_debug_guardpage(void)
static void init_debug_guardpage(void)
static int __init debug_guardpage_minorder_setup(char *buf)
static inline bool set_page_guard(struct zone *zone, struct page *page, unsigned int order, int migratetype)
static inline void clear_page_guard(struct zone *zone, struct page *page, unsigned int order, int migratetype)
static inline void set_page_order(struct page *page, unsigned int order)
static inline void rmv_page_order(struct page *page)
static inline int page_is_buddy(struct page *page, struct page *buddy, unsigned int order)
static inline void __free_one_page(struct page *page, unsigned long pfn, struct zone *zone, unsigned int order, int migratetype)
static inline bool page_expected_state(struct page *page, unsigned long check_flags)
static void free_pages_check_bad(struct page *page)
static inline int free_pages_check(struct page *page)
static int free_tail_pages_check(struct page *head_page, struct page *page)
static __always_inline bool free_pages_prepare(struct page *page, unsigned int order, bool check_free)
static inline bool free_pcp_prepare(struct page *page)
static inline bool bulkfree_pcp_prepare(struct page *page)
static inline bool bulkfree_pcp_prepare(struct page *page)
return false; } static bool free_pcp_prepare(struct page *page)
static bool bulkfree_pcp_prepare(struct page *page)
static inline void prefetch_buddy(struct page *page)
static void free_pcppages_bulk(struct zone *zone, int count, struct per_cpu_pages *pcp)
static void free_one_page(struct zone *zone, struct page *page, unsigned long pfn, unsigned int order, int migratetype)
static void __meminit __init_single_page(struct page *page, unsigned long pfn, unsigned long zone, int nid)
static void __meminit init_reserved_page(unsigned long pfn)
if (pfn >= zone->zone_start_pfn && pfn < zone_end_pfn(zone)
)
break;}__init_single_page(pfn_to_page(pfn)
, pfn, zid, nid)
; } static inline void init_reserved_page(unsigned long pfn)
void __meminit reserve_bootmem_region(phys_addr_t start, phys_addr_t end)
static void __free_pages_ok(struct page *page, unsigned int order)
static void __init __free_pages_boot_core(struct page *page, unsigned int order)
int __meminit early_pfn_to_nid(unsigned long pfn)
static inline bool __meminit __maybe_unused meminit_pfn_in_nid(unsigned long pfn, int node, struct mminit_pfnnid_cache *state)
static inline bool __meminit early_pfn_in_nid(unsigned long pfn, int node)
static inline bool __meminit early_pfn_in_nid(unsigned long pfn, int node)
static inline bool __meminit early_pfn_in_nid(unsigned long pfn, int node)
return true; } static inline bool __meminit__maybe_unused meminit_pfn_in_nid(unsigned long pfn, int node, struct mminit_pfnnid_cache *state)
void __init __free_pages_bootmem(struct page *page, unsigned long pfn, unsigned int order)
struct page *__pageblock_pfn_to_page(unsigned long start_pfn, unsigned long end_pfn, struct zone *zone)
void set_zone_contiguous(struct zone *zone)
void clear_zone_contiguous(struct zone *zone)
static void __init deferred_free_range(unsigned long pfn, unsigned long nr_pages)
static inline void __init pgdat_init_report_one_done(void)
static inline bool __init deferred_pfn_valid(int nid, unsigned long pfn, struct mminit_pfnnid_cache *nid_init_state)
static void __init deferred_free_pages(int nid, int zid, unsigned long pfn, unsigned long end_pfn)
static unsigned long__init deferred_init_pages(int nid, int zid, unsigned long pfn, unsigned long end_pfn)
static int __init deferred_init_memmap(void *data)
static noinline bool __init deferred_grow_zone(struct zone *zone, unsigned int order)
static bool __ref _deferred_grow_zone(struct zone *zone, unsigned int order)
void __init page_alloc_init_late(void)
void __init init_cma_reserved_pageblock(struct page *page)
static inline void expand(struct zone *zone, struct page *page, int low, int high, struct free_area *area, int migratetype)
static void check_new_page_bad(struct page *page)
static inline int check_new_page(struct page *page)
static inline bool free_pages_prezeroed(void)
static bool check_pcp_refill(struct page *page)
static bool check_new_pcp(struct page *page)
static bool check_new_pcp(struct page *page)
return check_new_page(page)
; } static bool check_pcp_refill(struct page *page)
static bool check_new_pcp(struct page *page)
return check_new_page(page)
; } static bool check_pcp_refill(struct page *page)
return check_new_page(page)
; } static bool check_new_pcp(struct page *page)
static bool check_new_pages(struct page *page, unsigned int order)
inline void post_alloc_hook(struct page *page, unsigned int order, gfp_t gfp_flags)
static void prep_new_page(struct page *page, unsigned int order, gfp_t gfp_flags, unsigned int alloc_flags)
static __always_inline struct page *__rmqueue_smallest(struct zone *zone, unsigned int order, int migratetype)
static __always_inline struct page *__rmqueue_cma_fallback(struct zone *zone, unsigned int order)
static int move_freepages(struct zone *zone, struct page *start_page, struct page *end_page, int migratetype, int *num_movable)
int move_freepages_block(struct zone *zone, struct page *page, int migratetype, int *num_movable)
static void change_pageblock_range(struct page *pageblock_page, int start_order, int migratetype)
static bool can_steal_fallback(unsigned int order, int start_mt)
static void steal_suitable_fallback(struct zone *zone, struct page *page, int start_type, bool whole_block)
int find_suitable_fallback(struct free_area *area, unsigned int order, int migratetype, bool only_stealable, bool *can_steal)
static void reserve_highatomic_pageblock(struct page *page, struct zone *zone, unsigned int alloc_order)
static bool unreserve_highatomic_pageblock(const struct alloc_context *ac, bool force)
static __always_inline bool __rmqueue_fallback(struct zone *zone, int order, int start_migratetype)
static __always_inline struct page * __rmqueue(struct zone *zone, unsigned int order, int migratetype)
static int rmqueue_bulk(struct zone *zone, unsigned int order, unsigned long count, struct list_head *list, int migratetype)
void drain_zone_pages(struct zone *zone, struct per_cpu_pages *pcp)
static void drain_pages_zone(unsigned int cpu, struct zone *zone)
static void drain_pages(unsigned int cpu)
void drain_local_pages(struct zone *zone)
static void drain_local_pages_wq(struct work_struct *work)
void drain_all_pages(struct zone *zone)
void mark_free_pages(struct zone *zone)
static bool free_unref_page_prepare(struct page *page, unsigned long pfn)
static void free_unref_page_commit(struct page *page, unsigned long pfn)
void free_unref_page(struct page *page)
void free_unref_page_list(struct list_head *list)
void split_page(struct page *page, unsigned int order)
int __isolate_free_page(struct page *page, unsigned int order)
static inline void zone_statistics(struct zone *preferred_zone, struct zone *z)
static struct page *__rmqueue_pcplist(struct zone *zone, int migratetype, struct per_cpu_pages *pcp, struct list_head *list)
static struct page *rmqueue_pcplist(struct zone *preferred_zone, struct zone *zone, unsigned int order, gfp_t gfp_flags, int migratetype)
static inline struct page *rmqueue(struct zone *preferred_zone, struct zone *zone, unsigned int order, gfp_t gfp_flags, unsigned int alloc_flags, int migratetype)
static int __init setup_fail_page_alloc(char *str)
static bool should_fail_alloc_page(gfp_t gfp_mask, unsigned int order)
static int __init fail_page_alloc_debugfs(void)
static inline bool should_fail_alloc_page(gfp_t gfp_mask, unsigned int order)
bool __zone_watermark_ok(struct zone *z, unsigned int order, unsigned long mark, int classzone_idx, unsigned int alloc_flags, long free_pages)
bool zone_watermark_ok(struct zone *z, unsigned int order, unsigned long mark, int classzone_idx, unsigned int alloc_flags)
static inline bool zone_watermark_fast(struct zone *z, unsigned int order, unsigned long mark, int classzone_idx, unsigned int alloc_flags)
bool zone_watermark_ok_safe(struct zone *z, unsigned int order, unsigned long mark, int classzone_idx)
static bool zone_allows_reclaim(struct zone *local_zone, struct zone *zone)
static bool zone_allows_reclaim(struct zone *local_zone, struct zone *zone)
return node_distance(zone_to_nid(local_zone)
, zone_to_nid(zone)
)
<= RECLAIM_DISTANCE; } static bool zone_allows_reclaim(struct zone *local_zone, struct zone *zone)
static struct page * get_page_from_freelist(gfp_t gfp_mask, unsigned int order, int alloc_flags, const struct alloc_context *ac)
static void warn_alloc_show_mem(gfp_t gfp_mask, nodemask_t *nodemask)
void warn_alloc(gfp_t gfp_mask, nodemask_t *nodemask, const char *fmt, ...)
static inline struct page * __alloc_pages_cpuset_fallback(gfp_t gfp_mask, unsigned int order, unsigned int alloc_flags, const struct alloc_context *ac)
static inline struct page * __alloc_pages_may_oom(gfp_t gfp_mask, unsigned int order, const struct alloc_context *ac, unsigned long *did_some_progress)
static struct page * __alloc_pages_direct_compact(gfp_t gfp_mask, unsigned int order, unsigned int alloc_flags, const struct alloc_context *ac, enum compact_priority prio, enum compact_result *compact_result)
static inline bool should_compact_retry(struct alloc_context *ac, int order, int alloc_flags, enum compact_result compact_result, enum compact_priority *compact_priority, int *compaction_retries)
(*compact_priority)
--; *compaction_retries = 0; ret = true;} out:trace_compact_retry(order, priority, compact_result, retries, max_retries, ret)
;return ret; } static inline struct page * __alloc_pages_direct_compact(gfp_t gfp_mask, unsigned int order, unsigned int alloc_flags, const struct alloc_context *ac, enum compact_priority prio, enum compact_result *compact_result)
static inline bool should_compact_retry(struct alloc_context *ac, unsigned int order, int alloc_flags, enum compact_result compact_result, enum compact_priority *compact_priority, int *compaction_retries)
static bool __need_fs_reclaim(gfp_t gfp_mask)
void __fs_reclaim_acquire(void)
void __fs_reclaim_release(void)
void fs_reclaim_acquire(gfp_t gfp_mask)
void fs_reclaim_release(gfp_t gfp_mask)
static int __perform_reclaim(gfp_t gfp_mask, unsigned int order, const struct alloc_context *ac)
static inline struct page * __alloc_pages_direct_reclaim(gfp_t gfp_mask, unsigned int order, unsigned int alloc_flags, const struct alloc_context *ac, unsigned long *did_some_progress)
static void wake_all_kswapds(unsigned int order, gfp_t gfp_mask, const struct alloc_context *ac)
static inline unsigned int gfp_to_alloc_flags(gfp_t gfp_mask)
static bool oom_reserves_allowed(struct task_struct *tsk)
static inline int __gfp_pfmemalloc_flags(gfp_t gfp_mask)
bool gfp_pfmemalloc_allowed(gfp_t gfp_mask)
static inline bool should_reclaim_retry(gfp_t gfp_mask, unsigned order, struct alloc_context *ac, int alloc_flags, bool did_some_progress, int *no_progress_loops)
static inline bool check_retry_cpuset(int cpuset_mems_cookie, struct alloc_context *ac)
static inline struct page * __alloc_pages_slowpath(gfp_t gfp_mask, unsigned int order, struct alloc_context *ac)
static inline bool prepare_alloc_pages(gfp_t gfp_mask, unsigned int order, int preferred_nid, nodemask_t *nodemask, struct alloc_context *ac, gfp_t *alloc_mask, unsigned int *alloc_flags)
static inline void finalise_ac(gfp_t gfp_mask, struct alloc_context *ac)
struct page * __alloc_pages_nodemask(gfp_t gfp_mask, unsigned int order, int preferred_nid, nodemask_t *nodemask)
unsigned long __get_free_pages(gfp_t gfp_mask, unsigned int order)
unsigned long get_zeroed_page(gfp_t gfp_mask)
void __free_pages(struct page *page, unsigned int order)
void free_pages(unsigned long addr, unsigned int order)
static struct page *__page_frag_cache_refill(struct page_frag_cache *nc, gfp_t gfp_mask)
void __page_frag_cache_drain(struct page *page, unsigned int count)
void *page_frag_alloc(struct page_frag_cache *nc, unsigned int fragsz, gfp_t gfp_mask)
void page_frag_free(void *addr)
static void *make_alloc_exact(unsigned long addr, unsigned int order, size_t size)
void *alloc_pages_exact(size_t size, gfp_t gfp_mask)
void * __meminit alloc_pages_exact_nid(int nid, size_t size, gfp_t gfp_mask)
void free_pages_exact(void *virt, size_t size)
static unsigned long nr_free_zone_pages(int offset)
unsigned long nr_free_buffer_pages(void)
unsigned long nr_free_pagecache_pages(void)
static inline void show_node(struct zone *zone)
long si_mem_available(void)
void si_meminfo(struct sysinfo *val)
void si_meminfo_node(struct sysinfo *val, int nid)
static bool show_mem_node_skip(unsigned int flags, int nid, nodemask_t *nodemask)
static void show_migration_types(unsigned char type)
void show_free_areas(unsigned int filter, nodemask_t *nodemask)
static void zoneref_set_zone(struct zone *zone, struct zoneref *zoneref)
static int build_zonerefs_node(pg_data_t *pgdat, struct zoneref *zonerefs)
static int __parse_numa_zonelist_order(char *s)
static __init int setup_numa_zonelist_order(char *s)
int numa_zonelist_order_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
static int find_next_best_node(int node, nodemask_t *used_node_mask)
static void build_zonelists_in_node_order(pg_data_t *pgdat, int *node_order, unsigned nr_nodes)
static void build_thisnode_zonelists(pg_data_t *pgdat)
static void build_zonelists(pg_data_t *pgdat)
int local_memory_node(int node)
static void build_zonelists(pg_data_t *pgdat)
static void __build_all_zonelists(void *data)
static noinline void __init build_all_zonelists_init(void)
void __ref build_all_zonelists(pg_data_t *pgdat)
static bool __meminit overlap_memmap_init(unsigned long zone, unsigned long *pfn)
void __meminit memmap_init_zone(unsigned long size, int nid, unsigned long zone, unsigned long start_pfn, enum memmap_context context, struct vmem_altmap *altmap)
void __ref memmap_init_zone_device(struct zone *zone, unsigned long start_pfn, unsigned long size, struct dev_pagemap *pgmap)
endif static void __meminit zone_init_free_lists(struct zone *zone)
void __meminit __weak memmap_init(unsigned long size, int nid, unsigned long zone, unsigned long start_pfn)
static int zone_batchsize(struct zone *zone)
static void pageset_update(struct per_cpu_pages *pcp, unsigned long high, unsigned long batch)
static void pageset_set_batch(struct per_cpu_pageset *p, unsigned long batch)
static void pageset_init(struct per_cpu_pageset *p)
static void setup_pageset(struct per_cpu_pageset *p, unsigned long batch)
static void pageset_set_high(struct per_cpu_pageset *p, unsigned long high)
static void pageset_set_high_and_batch(struct zone *zone, struct per_cpu_pageset *pcp)
static void __meminit zone_pageset_init(struct zone *zone, int cpu)
void __meminit setup_zone_pageset(struct zone *zone)
void __init setup_per_cpu_pageset(void)
static __meminit void zone_pcp_init(struct zone *zone)
void __meminit init_currently_empty_zone(struct zone *zone, unsigned long zone_start_pfn, unsigned long size)
int __meminit __early_pfn_to_nid(unsigned long pfn, struct mminit_pfnnid_cache *state)
void __init free_bootmem_with_active_regions(int nid, unsigned long max_low_pfn)
void __init sparse_memory_present_with_active_regions(int nid)
void __meminit get_pfn_range_for_nid(unsigned int nid, unsigned long *start_pfn, unsigned long *end_pfn)
static void __init find_usable_zone_for_movable(void)
static void __meminit adjust_zone_range_for_zone_movable(int nid, unsigned long zone_type, unsigned long node_start_pfn, unsigned long node_end_pfn, unsigned long *zone_start_pfn, unsigned long *zone_end_pfn)
static unsigned long __meminit zone_spanned_pages_in_node(int nid, unsigned long zone_type, unsigned long node_start_pfn, unsigned long node_end_pfn, unsigned long *zone_start_pfn, unsigned long *zone_end_pfn, unsigned long *ignored)
unsigned long __meminit __absent_pages_in_range(int nid, unsigned long range_start_pfn, unsigned long range_end_pfn)
unsigned long __init absent_pages_in_range(unsigned long start_pfn, unsigned long end_pfn)
static unsigned long __meminit zone_absent_pages_in_node(int nid, unsigned long zone_type, unsigned long node_start_pfn, unsigned long node_end_pfn, unsigned long *ignored)
static inline unsigned long __meminit zone_spanned_pages_in_node(int nid, unsigned long zone_type, unsigned long node_start_pfn, unsigned long node_end_pfn, unsigned long *zone_start_pfn, unsigned long *zone_end_pfn, unsigned long *zones_size)
static inline unsigned long __meminit zone_absent_pages_in_node(int nid, unsigned long zone_type, unsigned long node_start_pfn, unsigned long node_end_pfn, unsigned long *zholes_size)
static void __meminit calculate_node_totalpages(struct pglist_data *pgdat, unsigned long node_start_pfn, unsigned long node_end_pfn, unsigned long *zones_size, unsigned long *zholes_size)
static unsigned long __init usemap_size(unsigned long zone_start_pfn, unsigned long zonesize)
static void __ref setup_usemap(struct pglist_data *pgdat, struct zone *zone, unsigned long zone_start_pfn, unsigned long zonesize)
void __init set_pageblock_order(void)
void __init set_pageblock_order(void)
static unsigned long __init calc_memmap_size(unsigned long spanned_pages, unsigned long present_pages)
static void pgdat_init_split_queue(struct pglist_data *pgdat)
static void pgdat_init_kcompactd(struct pglist_data *pgdat)
static void __meminit pgdat_init_internals(struct pglist_data *pgdat)
static void __meminit zone_init_internals(struct zone *zone, enum zone_type idx, int nid, unsigned long remaining_pages)
void __ref free_area_init_core_hotplug(int nid)
static void __init free_area_init_core(struct pglist_data *pgdat)
static void __ref alloc_node_mem_map(struct pglist_data *pgdat)
static inline void pgdat_set_deferred_range(pg_data_t *pgdat)
void __init free_area_init_node(int nid, unsigned long *zones_size, unsigned long node_start_pfn, unsigned long *zholes_size)
static u64 zero_pfn_range(unsigned long spfn, unsigned long epfn)
void __init zero_resv_unavail(void)
void __init setup_nr_node_ids(void)
unsigned long __init node_map_pfn_alignment(void)
static unsigned long __init find_min_pfn_for_node(int nid)
unsigned long __init find_min_pfn_with_active_regions(void)
static unsigned long __init early_calculate_totalpages(void)
static void __init find_zone_movable_pfns_for_nodes(void)
static void check_for_memory(pg_data_t *pgdat, int nid)
void __init free_area_init_nodes(unsigned long *max_zone_pfn)
static int __init cmdline_parse_core(char *p, unsigned long *core, unsigned long *percent)
static int __init cmdline_parse_kernelcore(char *p)
static int __init cmdline_parse_movablecore(char *p)
void adjust_managed_page_count(struct page *page, long count)
unsigned long free_reserved_area(void *start, void *end, int poison, char *s)
void free_highmem_page(struct page *page)
void __init mem_init_print_info(const char *str)
void __init set_dma_reserve(unsigned long new_dma_reserve)
void __init free_area_init(unsigned long *zones_size)
static int page_alloc_cpu_dead(unsigned int cpu)
void __init page_alloc_init(void)
static void calculate_totalreserve_pages(void)
static void setup_per_zone_lowmem_reserve(void)
static void __setup_per_zone_wmarks(void)
void setup_per_zone_wmarks(void)
int __meminit init_per_zone_wmark_min(void)
int min_free_kbytes_sysctl_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
int watermark_scale_factor_sysctl_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
static void setup_min_unmapped_ratio(void)
int sysctl_min_unmapped_ratio_sysctl_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
static void setup_min_slab_ratio(void)
int sysctl_min_slab_ratio_sysctl_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
int lowmem_reserve_ratio_sysctl_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
int percpu_pagelist_fraction_sysctl_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
static int __init set_hashdist(char *str)
static unsigned long __init arch_reserved_kernel_pages(void)
void *__init alloc_large_system_hash(const char *tablename, unsigned long bucketsize, unsigned long numentries, int scale, int flags, unsigned int *_hash_shift, unsigned int *_hash_mask, unsigned long low_limit, unsigned long high_limit)
bool has_unmovable_pages(struct zone *zone, struct page *page, int count, int migratetype, bool skip_hwpoisoned_pages)
static unsigned long pfn_max_align_down(unsigned long pfn)
static unsigned long pfn_max_align_up(unsigned long pfn)
static int __alloc_contig_migrate_range(struct compact_control *cc, unsigned long start, unsigned long end)
int alloc_contig_range(unsigned long start, unsigned long end, unsigned migratetype, gfp_t gfp_mask)
void free_contig_range(unsigned long pfn, unsigned nr_pages)
void __meminit zone_pcp_update(struct zone *zone)
void zone_pcp_reset(struct zone *zone)
void __offline_isolated_pages(unsigned long start_pfn, unsigned long end_pfn)
bool is_free_buddy_page(struct page *page)
bool set_hwpoison_free_buddy_page(struct page *page)
  67 struct page *page
  50 struct zone *zone
  48 unsigned int order
  34 void
  32 unsigned long pfn
  30 gfp_t gfp_mask
  24 int nid
  18 int migratetype
   9 unsigned int alloc_flags
   9 const struct alloc_context *ac
   8 pg_data_t *pgdat
   7 void __user *buffer
   7 unsigned long node_start_pfn
   7 unsigned long end_pfn
   7 struct pglist_data *pgdat
   7 struct ctl_table *table
   7 struct alloc_context *ac
   7 size_t *length
   7 loff_t *ppos
   7 int write
   7 int node
   6 unsigned long start_pfn
   6 unsigned long node_end_pfn
   6 nodemask_t *nodemask
   5 unsigned long zone_type
   5 struct zone *z
   4 unsigned long zone
   4 unsigned long size
   4 unsigned long mark
   4 unsigned long *zones_size
   4 struct per_cpu_pageset *p
   4 struct per_cpu_pages *pcp
   4 size_t size
   4 int classzone_idx
   4 int alloc_flags
   4 gfp_t gfp_flags
   3 unsigned long zone_start_pfn
   3 unsigned long mask
   3 unsigned long end_bitidx
   3 unsigned long batch
   3 unsigned long *zone_start_pfn
   3 unsigned long *zone_end_pfn
   3 unsigned long *zholes_size
   3 unsigned int cpu
   3 struct zone *preferred_zone
   3 struct zone *local_zone
   3 struct mminit_pfnnid_cache *state
   3 struct list_head *list
   3 page
   3 char *s
   3 char *p
   2 void *data
   2 unsigned long zonesize
   2 unsigned long start
   2 unsigned long high
   2 unsigned long end
   2 unsigned long addr
   2 unsigned long *ignored
   2 unsigned long *did_some_progress
   2 struct sysinfo *val
   2 struct page_frag_cache *nc
   2 struct free_area *area
   2 int zid
   2 int preferred_nid
   2 int order
   2 int count
   2 int *num_movable
   2 int *compaction_retries
   2 enum compact_result compact_result
   2 enum compact_result *compact_result
   2 enum compact_priority prio
   2 enum compact_priority *compact_priority
   2 char *str
   2 char *buf
   1 zone_to_nidlocal_zone
   1 zone
   1 void *virt
   1 void *start
   1 void *end
   1 void *addr
   1 unsigned order
   1 unsigned nr_pages
   1 unsigned nr_nodes
   1 unsigned migratetype
   1 unsigned long spfn
   1 unsigned long spanned_pages
   1 unsigned long remaining_pages
   1 unsigned long range_start_pfn
   1 unsigned long range_end_pfn
   1 unsigned long present_pages
   1 unsigned long numentries
   1 unsigned long nr_pages
   1 unsigned long new_dma_reserve
   1 unsigned long max_low_pfn
   1 unsigned long low_limit
   1 unsigned long high_limit
   1 unsigned long flags
   1 unsigned long epfn
   1 unsigned long count
   1 unsigned long check_flags
   1 unsigned long bucketsize
   1 unsigned long bad_flags
   1 unsigned long *start_pfn
   1 unsigned long *pfn
   1 unsigned long *percent
   1 unsigned long *max_zone_pfn
   1 unsigned long *end_pfn
   1 unsigned long *core
   1 unsigned int nid
   1 unsigned int fragsz
   1 unsigned int flags
   1 unsigned int filter
   1 unsigned int count
   1 unsigned int alloc_order
   1 unsigned int *alloc_flags
   1 unsigned int *_hash_shift
   1 unsigned int *_hash_mask
   1 unsigned char type
   1 struct zoneref *zonerefs
   1 struct zoneref *zoneref
   1 struct work_struct *work
   1 struct vmem_altmap *altmap
   1 struct task_struct *tsk
   1 struct per_cpu_pageset *pcp
   1 struct page *start_page
   1 struct page *pageblock_page
   1 struct page *head_page
   1 struct page *end_page
   1 struct page *buddy
   1 struct mminit_pfnnid_cache *nid_init_state
   1 struct dev_pagemap *pgmap
   1 struct compact_control *cc
   1 split_page
   1 si_mem_available
   1 retries
   1 ret
   1 priority
   1 phys_addr_t start
   1 phys_addr_t end
   1 pfn_to_pagepfn
   1 pfn >= zone->zone_start_pfn && pfn < zone_end_pfnzone
   1 order
   1 nr_initialised > NODE_DATAnid
   1 nr_free_buffer_pages
   1 nodemask_t *used_node_mask
   1 nid
   1 max_retries
   1 long free_pages
   1 long count
   1 int start_type
   1 int start_order
   1 int start_mt
   1 int start_migratetype
   1 int scale
   1 int poison
   1 int offset
   1 int low
   1 int high
   1 int flags
   1 int cpuset_mems_cookie
   1 int cpu
   1 int *node_order
   1 int *no_progress_loops
   1 gfp_t *alloc_mask
   1 fs_reclaim_release
   1 fs_reclaim_acquire
   1 enum zone_type idx
   1 enum memmap_context context
   1 end_pfn < pgdat_end_pfnNODE_DATAnid
   1 const char *tablename
   1 const char *str
   1 const char *reason
   1 const char *fmt
   1 compact_result
   1 bool whole_block
   1 bool skip_hwpoisoned_pages
   1 bool only_stealable
   1 bool force
   1 bool did_some_progress
   1 bool check_free
   1 bool *can_steal
   1 ...
   1 *compact_priority
