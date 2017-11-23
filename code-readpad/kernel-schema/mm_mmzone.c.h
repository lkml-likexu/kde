
struct pglist_data *first_online_pgdat(void)
struct pglist_data *next_online_pgdat(struct pglist_data *pgdat)
struct zone *next_zone(struct zone *zone)
static inline int zref_in_nodemask(struct zoneref *zref, nodemask_t *nodes)
struct zoneref *__next_zones_zonelist(struct zoneref *z, enum zone_type highest_zoneidx, nodemask_t *nodes)
bool memmap_valid_within(unsigned long pfn, struct page *page, struct zone *zone)
void lruvec_init(struct lruvec *lruvec)
int page_cpupid_xchg_last(struct page *page, int cpupid)
   2 struct zone *zone
   2 struct page *page
   2 nodemask_t *nodes
   1 void
   1 unsigned long pfn
   1 struct zoneref *zref
   1 struct zoneref *z
   1 struct pglist_data *pgdat
   1 struct lruvec *lruvec
   1 int cpupid
   1 enum zone_type highest_zoneidx
