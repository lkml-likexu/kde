
EXPORT_SYMBOL_GPL(all_vm_events);
static void zero_zone_numa_counters(struct zone *zone)
static void zero_zones_numa_counters(void)
static void zero_global_numa_counters(void)
static void invalid_numa_statistics(void)
int sysctl_vm_numa_stat_handler(struct ctl_table *table, int write, void __user *buffer, size_t *length, loff_t *ppos)
static void sum_vm_events(unsigned long *ret)
void all_vm_events(unsigned long *ret)
void vm_events_fold_cpu(int cpu)
int calculate_pressure_threshold(struct zone *zone)
int calculate_normal_threshold(struct zone *zone)
void refresh_zone_stat_thresholds(void)
void set_pgdat_percpu_threshold(pg_data_t *pgdat, int (*calculate_pressure)
(struct zone *)
)
void __mod_zone_page_state(struct zone *zone, enum zone_stat_item item, long delta)
void __mod_node_page_state(struct pglist_data *pgdat, enum node_stat_item item, long delta)
void __inc_zone_state(struct zone *zone, enum zone_stat_item item)
void __inc_node_state(struct pglist_data *pgdat, enum node_stat_item item)
void __inc_zone_page_state(struct page *page, enum zone_stat_item item)
void __inc_node_page_state(struct page *page, enum node_stat_item item)
void __dec_zone_state(struct zone *zone, enum zone_stat_item item)
void __dec_node_state(struct pglist_data *pgdat, enum node_stat_item item)
void __dec_zone_page_state(struct page *page, enum zone_stat_item item)
void __dec_node_page_state(struct page *page, enum node_stat_item item)
static inline void mod_zone_state(struct zone *zone, enum zone_stat_item item, long delta, int overstep_mode)
void mod_zone_page_state(struct zone *zone, enum zone_stat_item item, long delta)
void inc_zone_page_state(struct page *page, enum zone_stat_item item)
void dec_zone_page_state(struct page *page, enum zone_stat_item item)
static inline void mod_node_state(struct pglist_data *pgdat, enum node_stat_item item, int delta, int overstep_mode)
void mod_node_page_state(struct pglist_data *pgdat, enum node_stat_item item, long delta)
void inc_node_state(struct pglist_data *pgdat, enum node_stat_item item)
void inc_node_page_state(struct page *page, enum node_stat_item item)
void dec_node_page_state(struct page *page, enum node_stat_item item)
void dec_node_page_state(struct page *page, enum node_stat_item item)
mod_node_state(page_pgdat(page)
, item, -1, -1)
; } EXPORT_SYMBOL(dec_node_page_state)
;void mod_zone_page_state(struct zone *zone, enum zone_stat_item item, long delta)
void inc_zone_page_state(struct page *page, enum zone_stat_item item)
void dec_zone_page_state(struct page *page, enum zone_stat_item item)
void inc_node_state(struct pglist_data *pgdat, enum node_stat_item item)
void mod_node_page_state(struct pglist_data *pgdat, enum node_stat_item item, long delta)
void inc_node_page_state(struct page *page, enum node_stat_item item)
void dec_node_page_state(struct page *page, enum node_stat_item item)
static int fold_diff(int *zone_diff, int *numa_diff, int *node_diff)
for (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++)
atomic_long_add(node_diff[i], &vm_node_stat[i])
;changes++;}return changes; } static int fold_diff(int *zone_diff, int *node_diff)
static int refresh_cpu_vm_stats(bool do_pagesets)
void cpu_vm_stats_fold(int cpu)
void drain_zonestat(struct zone *zone, struct per_cpu_pageset *pset)
void __inc_numa_state(struct zone *zone, enum numa_stat_item item)
unsigned long sum_zone_node_page_state(int node, enum zone_stat_item item)
unsigned long sum_zone_numa_state(int node, enum numa_stat_item item)
unsigned long node_page_state(struct pglist_data *pgdat, enum node_stat_item item)
static void fill_contig_page_info(struct zone *zone, unsigned int suitable_order, struct contig_page_info *info)
static int __fragmentation_index(unsigned int order, struct contig_page_info *info)
int fragmentation_index(struct zone *zone, unsigned int order)
defined(CONFIG_PROC_FS)
static void *frag_start(struct seq_file *m, loff_t *pos)
static void *frag_next(struct seq_file *m, void *arg, loff_t *pos)
static void frag_stop(struct seq_file *m, void *arg)
static void walk_zones_in_node(struct seq_file *m, pg_data_t *pgdat, bool assert_populated, bool nolock, void (*print)
(struct seq_file *m, pg_data_t *, struct zone *)
)
static void frag_show_print(struct seq_file *m, pg_data_t *pgdat, struct zone *zone)
static int frag_show(struct seq_file *m, void *arg)
static void pagetypeinfo_showfree_print(struct seq_file *m, pg_data_t *pgdat, struct zone *zone)
static int pagetypeinfo_showfree(struct seq_file *m, void *arg)
static void pagetypeinfo_showblockcount_print(struct seq_file *m, pg_data_t *pgdat, struct zone *zone)
static int pagetypeinfo_showblockcount(struct seq_file *m, void *arg)
static void pagetypeinfo_showmixedcount(struct seq_file *m, pg_data_t *pgdat)
static int pagetypeinfo_show(struct seq_file *m, void *arg)
static bool is_zone_first_populated(pg_data_t *pgdat, struct zone *zone)
static void zoneinfo_show_print(struct seq_file *m, pg_data_t *pgdat, struct zone *zone)
static int zoneinfo_show(struct seq_file *m, void *arg)
static void *vmstat_start(struct seq_file *m, loff_t *pos)
static void *vmstat_next(struct seq_file *m, void *arg, loff_t *pos)
static int vmstat_show(struct seq_file *m, void *arg)
static void vmstat_stop(struct seq_file *m, void *arg)
static void refresh_vm_stats(struct work_struct *work)
int vmstat_refresh(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static void vmstat_update(struct work_struct *w)
static bool need_update(int cpu)
void quiet_vmstat(void)
static void vmstat_shepherd(struct work_struct *w)
static void __init start_shepherd_timer(void)
static void __init init_cpu_node_state(void)
static int vmstat_cpu_online(unsigned int cpu)
static int vmstat_cpu_down_prep(unsigned int cpu)
static int vmstat_cpu_dead(unsigned int cpu)
void __init init_mm_internals(void)
static int unusable_free_index(unsigned int order, struct contig_page_info *info)
static void unusable_show_print(struct seq_file *m, pg_data_t *pgdat, struct zone *zone)
static int unusable_show(struct seq_file *m, void *arg)
static int unusable_open(struct inode *inode, struct file *file)
static void extfrag_show_print(struct seq_file *m, pg_data_t *pgdat, struct zone *zone)
static int extfrag_show(struct seq_file *m, void *arg)
static int extfrag_open(struct inode *inode, struct file *file)
static int __init extfrag_debug_init(void)
  23 struct seq_file *m
  20 struct zone *zone
  16 enum node_stat_item item
  13 struct page *page
  13 enum zone_stat_item item
  12 void *arg
  10 pg_data_t *pgdat
   9 void
   9 struct pglist_data *pgdat
   7 long delta
   4 loff_t *pos
   3 unsigned int order
   3 unsigned int cpu
   3 struct contig_page_info *info
   3 int cpu
   2 void __user *buffer
   2 unsigned long *ret
   2 struct zone *
   2 struct work_struct *w
   2 struct inode *inode
   2 struct file *file
   2 struct ctl_table *table
   2 loff_t *ppos
   2 int write
   2 int overstep_mode
   2 int node
   2 int *zone_diff
   2 int *node_diff
   2 enum numa_stat_item item
   1 void *print
   1 unsigned int suitable_order
   1 struct work_struct *work
   1 struct per_cpu_pageset *pset
   1 size_t *lenp
   1 size_t *length
   1 pg_data_t *
   1 page_pgdatpage
   1 node_diff[i]
   1 int delta
   1 int *numa_diff
   1 int *calculate_pressure
   1 i = 0; i < NR_VM_NODE_STAT_ITEMS; i++
   1 dec_node_page_state
   1 bool nolock
   1 bool do_pagesets
   1 bool assert_populated
   1 all_vm_events
   1 CONFIG_PROC_FS
   1 &vm_node_stat[i]
