
EXPORT_SYMBOL_GPL(intel_pt_handle_vmx);
static u32 pt_cap_get(enum pt_capabilities cap)
static ssize_t pt_cap_show(struct device *cdev, struct device_attribute *attr, char *buf)
static ssize_t pt_timing_attr_show(struct device *dev, struct device_attribute *attr, char *page)
static int __init pt_pmu_hw_init(void)
static bool pt_event_valid(struct perf_event *event)
static u64 pt_config_filters(struct perf_event *event)
static void pt_config(struct perf_event *event)
static void pt_config_stop(struct perf_event *event)
static void pt_config_buffer(void *buf, unsigned int topa_idx, unsigned int output_off)
static struct topa *topa_alloc(int cpu, gfp_t gfp)
static void topa_free(struct topa *topa)
static void topa_insert_table(struct pt_buffer *buf, struct topa *topa)
static bool topa_table_full(struct topa *topa)
static int topa_insert_pages(struct pt_buffer *buf, gfp_t gfp)
static void pt_topa_dump(struct pt_buffer *buf)
static void pt_buffer_advance(struct pt_buffer *buf)
static void pt_update_head(struct pt *pt)
static void *pt_buffer_region(struct pt_buffer *buf)
static size_t pt_buffer_region_size(struct pt_buffer *buf)
static void pt_handle_status(struct pt *pt)
static void pt_read_offset(struct pt_buffer *buf)
static unsigned int pt_topa_next_entry(struct pt_buffer *buf, unsigned int pg)
static void pt_buffer_setup_topa_index(struct pt_buffer *buf)
static void pt_buffer_reset_offsets(struct pt_buffer *buf, unsigned long head)
static void pt_buffer_fini_topa(struct pt_buffer *buf)
static int pt_buffer_init_topa(struct pt_buffer *buf, unsigned long nr_pages, gfp_t gfp)
static void * pt_buffer_setup_aux(int cpu, void **pages, int nr_pages, bool snapshot)
static void pt_buffer_free_aux(void *data)
static int pt_addr_filters_init(struct perf_event *event)
static void pt_addr_filters_fini(struct perf_event *event)
static inline bool valid_kernel_ip(unsigned long ip)
static int pt_event_addr_filters_validate(struct list_head *filters)
static void pt_event_addr_filters_sync(struct perf_event *event)
void intel_pt_interrupt(void)
void intel_pt_handle_vmx(int on)
static void pt_event_start(struct perf_event *event, int mode)
static void pt_event_stop(struct perf_event *event, int mode)
static void pt_event_del(struct perf_event *event, int mode)
static int pt_event_add(struct perf_event *event, int mode)
static void pt_event_read(struct perf_event *event)
static void pt_event_destroy(struct perf_event *event)
static int pt_event_init(struct perf_event *event)
void cpu_emergency_stop_pt(void)
static __init int pt_init(void)
  14 struct perf_event *event
  12 struct pt_buffer *buf
   4 void
   4 int mode
   3 struct topa *topa
   3 gfp_t gfp
   2 struct pt *pt
   2 struct device_attribute *attr
   2 int cpu
   1 void *data
   1 void *buf
   1 void **pages
   1 unsigned long nr_pages
   1 unsigned long ip
   1 unsigned long head
   1 unsigned int topa_idx
   1 unsigned int pg
   1 unsigned int output_off
   1 struct list_head *filters
   1 struct device *dev
   1 struct device *cdev
   1 intel_pt_handle_vmx
   1 int on
   1 int nr_pages
   1 enum pt_capabilities cap
   1 char *page
   1 char *buf
   1 bool snapshot
