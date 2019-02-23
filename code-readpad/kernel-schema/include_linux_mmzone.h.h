
\n
static inline bool is_migrate_movable(int mt)
static inline int is_file_lru(enum lru_list lru)
static inline int is_active_lru(enum lru_list lru)
static inline unsigned long zone_managed_pages(struct zone *zone)
static inline unsigned long zone_end_pfn(const struct zone *zone)
static inline bool zone_spans_pfn(const struct zone *zone, unsigned long pfn)
static inline bool zone_is_initialized(struct zone *zone)
static inline bool zone_is_empty(struct zone *zone)
static inline bool zone_intersects(struct zone *zone, unsigned long start_pfn, unsigned long nr_pages)
define node_start_pfn(nid)
(NODE_DATA(nid)
->node_start_pfn)
define node_end_pfn(nid)
pgdat_end_pfn(NODE_DATA(nid)
)
static inline spinlock_t *zone_lru_lock(struct zone *zone)
static inline struct lruvec *node_lruvec(struct pglist_data *pgdat)
static inline unsigned long pgdat_end_pfn(pg_data_t *pgdat)
static inline bool pgdat_is_empty(pg_data_t *pgdat)
static inline struct pglist_data *lruvec_pgdat(struct lruvec *lruvec)
static inline bool is_dev_zone(const struct zone *zone)
static inline bool is_dev_zone(const struct zone *zone)
return zone_idx(zone)
== ZONE_DEVICE; } static inline bool is_dev_zone(const struct zone *zone)
static inline bool managed_zone(struct zone *zone)
static inline bool populated_zone(struct zone *zone)
static inline int zone_to_nid(struct zone *zone)
static inline void zone_set_nid(struct zone *zone, int nid)
static inline void zone_set_nid(struct zone *zone, int nid)
zone->node = nid; } static inline int zone_to_nid(struct zone *zone)
static inline int zone_movable_is_highmem(void)
static inline int is_highmem_idx(enum zone_type idx)
static inline int is_highmem(struct zone *zone)
static inline struct zone *zonelist_zone(struct zoneref *zoneref)
static inline int zonelist_zone_idx(struct zoneref *zoneref)
static inline int zonelist_node_idx(struct zoneref *zoneref)
static __always_inline struct zoneref *next_zones_zonelist(struct zoneref *z, enum zone_type highest_zoneidx, nodemask_t *nodes)
static inline struct zoneref *first_zones_zonelist(struct zonelist *zonelist, enum zone_type highest_zoneidx, nodemask_t *nodes)
!defined(CONFIG_HAVE_MEMBLOCK_NODE_MAP)
static inline unsigned long early_pfn_to_nid(unsigned long pfn)
static inline unsigned long pfn_to_section_nr(unsigned long pfn)
static inline unsigned long pfn_to_section_nr(unsigned long pfn)
return pfn >> PFN_SECTION_SHIFT; } static inline unsigned long section_nr_to_pfn(unsigned long sec)
static inline struct mem_section *__nr_to_section(unsigned long nr)
static inline struct page *__section_mem_map_addr(struct mem_section *section)
static inline int present_section(struct mem_section *section)
static inline int present_section_nr(unsigned long nr)
static inline int valid_section(struct mem_section *section)
static inline int valid_section_nr(unsigned long nr)
static inline int online_section(struct mem_section *section)
static inline int online_section_nr(unsigned long nr)
static inline struct mem_section *__pfn_to_section(unsigned long pfn)
static inline int pfn_valid(unsigned long pfn)
static inline int pfn_present(unsigned long pfn)
bool memmap_valid_within(unsigned long pfn, struct page *page, struct zone *zone)
; static inline bool memmap_valid_within(unsigned long pfn, struct page *page, struct zone *zone)
\n
     14 struct zone *zone
      9 unsigned long pfn
      5 const struct zone *zone
      4 unsigned long nr
      4 struct mem_section *section
      3 struct zoneref *zoneref
      2 struct page *page
      2 pg_data_t *pgdat
      2 nodemask_t *nodes
      2 NODE_DATAnid
      2 nid
      2 int nid
      2 enum zone_type highest_zoneidx
      2 enum lru_list lru
      1 zone
      1 void
      1 unsigned long start_pfn
      1 unsigned long sec
      1 unsigned long nr_pages
      1 struct zoneref *z
      1 struct zonelist *zonelist
      1 struct pglist_data *pgdat
      1 struct lruvec *lruvec
      1 int mt
      1 enum zone_type idx
      1 CONFIG_HAVE_MEMBLOCK_NODE_MAP
