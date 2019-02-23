
\n
static inline void __count_vm_event(enum vm_event_item item)
static inline void count_vm_event(enum vm_event_item item)
static inline void __count_vm_events(enum vm_event_item item, long delta)
static inline void count_vm_events(enum vm_event_item item, long delta)
static inline void count_vm_event(enum vm_event_item item)
static inline void count_vm_event(enum vm_event_item item)
} static inline void count_vm_events(enum vm_event_item item, long delta)
static inline void count_vm_event(enum vm_event_item item)
} static inline void count_vm_events(enum vm_event_item item, long delta)
} static inline void __count_vm_event(enum vm_event_item item)
static inline void count_vm_event(enum vm_event_item item)
} static inline void count_vm_events(enum vm_event_item item, long delta)
} static inline void __count_vm_event(enum vm_event_item item)
} static inline void __count_vm_events(enum vm_event_item item, long delta)
static inline void count_vm_event(enum vm_event_item item)
} static inline void count_vm_events(enum vm_event_item item, long delta)
} static inline void __count_vm_event(enum vm_event_item item)
} static inline void __count_vm_events(enum vm_event_item item, long delta)
} static inline void all_vm_events(unsigned long *ret)
static inline void count_vm_event(enum vm_event_item item)
} static inline void count_vm_events(enum vm_event_item item, long delta)
} static inline void __count_vm_event(enum vm_event_item item)
} static inline void __count_vm_events(enum vm_event_item item, long delta)
} static inline void all_vm_events(unsigned long *ret)
} static inline void vm_events_fold_cpu(int cpu)
static inline void zone_numa_state_add(long x, struct zone *zone, enum numa_stat_item item)
static inline unsigned long global_numa_state(enum numa_stat_item item)
static inline unsigned long zone_numa_state_snapshot(struct zone *zone, enum numa_stat_item item)
static inline void zone_page_state_add(long x, struct zone *zone, enum zone_stat_item item)
static inline void node_page_state_add(long x, struct pglist_data *pgdat, enum node_stat_item item)
static inline unsigned long global_zone_page_state(enum zone_stat_item item)
static inline unsigned long global_node_page_state(enum node_stat_item item)
static inline unsigned long zone_page_state(struct zone *zone, enum zone_stat_item item)
static inline unsigned long zone_page_state_snapshot(struct zone *zone, enum zone_stat_item item)
static inline void __mod_zone_page_state(struct zone *zone, enum zone_stat_item item, long delta)
static inline void __mod_node_page_state(struct pglist_data *pgdat, enum node_stat_item item, int delta)
static inline void __inc_zone_state(struct zone *zone, enum zone_stat_item item)
static inline void __inc_node_state(struct pglist_data *pgdat, enum node_stat_item item)
static inline void __dec_zone_state(struct zone *zone, enum zone_stat_item item)
static inline void __dec_node_state(struct pglist_data *pgdat, enum node_stat_item item)
static inline void __inc_zone_page_state(struct page *page, enum zone_stat_item item)
static inline void __inc_node_page_state(struct page *page, enum node_stat_item item)
static inline void __dec_zone_page_state(struct page *page, enum zone_stat_item item)
static inline void __dec_node_page_state(struct page *page, enum node_stat_item item)
static inline void __mod_zone_freepage_state(struct zone *zone, int nr_pages, int migratetype)
\n
     22 enum vm_event_item item
     11 long delta
      9 struct zone *zone
      9 enum zone_stat_item item
      7 enum node_stat_item item
      4 struct pglist_data *pgdat
      4 struct page *page
      3 long x
      3 enum numa_stat_item item
      2 unsigned long *ret
      1 int nr_pages
      1 int migratetype
      1 int delta
      1 int cpu
