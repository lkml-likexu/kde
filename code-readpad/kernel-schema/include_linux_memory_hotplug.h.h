
\n
static inline unsigned zone_span_seqbegin(struct zone *zone)
static inline unsigned zone_span_seqbegin(struct zone *zone)
return read_seqbegin(&zone->span_seqlock)
; } static inline int zone_span_seqretry(struct zone *zone, unsigned iv)
static inline unsigned zone_span_seqbegin(struct zone *zone)
return read_seqbegin(&zone->span_seqlock)
; } static inline int zone_span_seqretry(struct zone *zone, unsigned iv)
return read_seqretry(&zone->span_seqlock, iv)
; } static inline void zone_span_writelock(struct zone *zone)
static inline unsigned zone_span_seqbegin(struct zone *zone)
return read_seqbegin(&zone->span_seqlock)
; } static inline int zone_span_seqretry(struct zone *zone, unsigned iv)
return read_seqretry(&zone->span_seqlock, iv)
; } static inline void zone_span_writelock(struct zone *zone)
write_seqlock(&zone->span_seqlock)
; } static inline void zone_span_writeunlock(struct zone *zone)
static inline unsigned zone_span_seqbegin(struct zone *zone)
return read_seqbegin(&zone->span_seqlock)
; } static inline int zone_span_seqretry(struct zone *zone, unsigned iv)
return read_seqretry(&zone->span_seqlock, iv)
; } static inline void zone_span_writelock(struct zone *zone)
write_seqlock(&zone->span_seqlock)
; } static inline void zone_span_writeunlock(struct zone *zone)
write_sequnlock(&zone->span_seqlock)
; } static inline void zone_seqlock_init(struct zone *zone)
extern bool memhp_auto_online;extern bool movable_node_enabled; static inline bool movable_node_is_enabled(void)
static inline int add_pages(int nid, unsigned long start_pfn, unsigned long nr_pages, struct vmem_altmap *altmap, bool want_memblock)
extern int memory_add_physaddr_to_nid(u64 start)
; static inline int memory_add_physaddr_to_nid(u64 start)
extern pg_data_t *node_data[]; static inline void arch_refresh_nodedata(int nid, pg_data_t *pgdat)
static inline pg_data_t *generic_alloc_nodedata(int nid)
static inline pg_data_t *generic_alloc_nodedata(int nid)
BUG()
;return NULL; } static inline void generic_free_nodedata(pg_data_t *pgdat)
static inline pg_data_t *generic_alloc_nodedata(int nid)
BUG()
;return NULL; } static inline void generic_free_nodedata(pg_data_t *pgdat)
} static inline void arch_refresh_nodedata(int nid, pg_data_t *pgdat)
extern void __init register_page_bootmem_info_node(struct pglist_data *pgdat)
; static inline void register_page_bootmem_info_node(struct pglist_data *pgdat)
static inline unsigned zone_span_seqbegin(struct zone *zone)
static inline unsigned zone_span_seqbegin(struct zone *zone)
return 0; } static inline int zone_span_seqretry(struct zone *zone, unsigned iv)
static inline int mhp_notimplemented(const char *func)
static inline void register_page_bootmem_info_node(struct pglist_data *pgdat)
static inline int try_online_node(int nid)
static inline bool movable_node_is_enabled(void)
static inline void pgdat_resize_lock(struct pglist_data *pgdat, unsigned long *flags)
static inline void pgdat_resize_lock(struct pglist_data *pgdat, unsigned long *flags)
spin_lock_irqsave(&pgdat->node_size_lock, *flags)
; } static inline void pgdat_resize_unlock(struct pglist_data *pgdat, unsigned long *flags)
static inline void pgdat_resize_lock(struct pglist_data *pgdat, unsigned long *flags)
spin_lock_irqsave(&pgdat->node_size_lock, *flags)
; } static inline void pgdat_resize_unlock(struct pglist_data *pgdat, unsigned long *flags)
spin_unlock_irqrestore(&pgdat->node_size_lock, *flags)
; } static inline void pgdat_resize_init(struct pglist_data *pgdat)
static inline bool is_mem_section_removable(unsigned long pfn, unsigned long nr_pages)
static inline int offline_pages(unsigned long start_pfn, unsigned long nr_pages)
\n
     18 struct zone *zone
     10 &zone->span_seqlock
      9 struct pglist_data *pgdat
      7 int nid
      5 unsigned long *flags
      5 unsigned iv
      4 pg_data_t *pgdat
      3 unsigned long nr_pages
      3 &pgdat->node_size_lock
      3 iv
      3 *flags
      2 void
      2 unsigned long start_pfn
      2 u64 start
      2 
      1 unsigned long pfn
      1 struct vmem_altmap *altmap
      1 const char *func
      1 bool want_memblock
