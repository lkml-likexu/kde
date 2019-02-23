
\n
static size_t buf_size(struct page *page)
static void * bts_buffer_setup_aux(int cpu, void **pages, int nr_pages, bool overwrite)
static void bts_buffer_free_aux(void *data)
static unsigned long bts_buffer_offset(struct bts_buffer *buf, unsigned int idx)
static void bts_config_buffer(struct bts_buffer *buf)
static void bts_buffer_pad_out(struct bts_phys *phys, unsigned long head)
static void bts_update(struct bts_ctx *bts)
static void __bts_event_start(struct perf_event *event)
static void bts_event_start(struct perf_event *event, int flags)
static void __bts_event_stop(struct perf_event *event, int state)
static void bts_event_stop(struct perf_event *event, int flags)
void intel_bts_enable_local(void)
void intel_bts_disable_local(void)
static int bts_buffer_reset(struct bts_buffer *buf, struct perf_output_handle *handle)
int intel_bts_interrupt(void)
static void bts_event_del(struct perf_event *event, int mode)
static int bts_event_add(struct perf_event *event, int mode)
static void bts_event_destroy(struct perf_event *event)
static int bts_event_init(struct perf_event *event)
static void bts_event_read(struct perf_event *event)
static __init int bts_init(void)
\n
      9 struct perf_event *event
      4 void
      3 struct bts_buffer *buf
      2 int mode
      2 int flags
      1 void **pages
      1 void *data
      1 unsigned long head
      1 unsigned int idx
      1 struct perf_output_handle *handle
      1 struct page *page
      1 struct bts_phys *phys
      1 struct bts_ctx *bts
      1 int state
      1 int nr_pages
      1 int cpu
      1 bool overwrite
