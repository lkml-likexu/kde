
EXPORT_SYMBOL_GPL(perf_aux_output_flag);
EXPORT_SYMBOL_GPL(perf_aux_output_begin);
EXPORT_SYMBOL_GPL(perf_aux_output_end);
EXPORT_SYMBOL_GPL(perf_aux_output_skip);
EXPORT_SYMBOL_GPL(perf_get_aux);
\n
static void perf_output_wakeup(struct perf_output_handle *handle)
static void perf_output_get_handle(struct perf_output_handle *handle)
static void perf_output_put_handle(struct perf_output_handle *handle)
static __always_inline bool ring_buffer_has_space(unsigned long head, unsigned long tail, unsigned long data_size, unsigned int size, bool backward)
static __always_inline int __perf_output_begin(struct perf_output_handle *handle, struct perf_event *event, unsigned int size, bool backward)
int perf_output_begin_forward(struct perf_output_handle *handle, struct perf_event *event, unsigned int size)
int perf_output_begin_backward(struct perf_output_handle *handle, struct perf_event *event, unsigned int size)
int perf_output_begin(struct perf_output_handle *handle, struct perf_event *event, unsigned int size)
unsigned int perf_output_copy(struct perf_output_handle *handle, const void *buf, unsigned int len)
unsigned int perf_output_skip(struct perf_output_handle *handle, unsigned int len)
void perf_output_end(struct perf_output_handle *handle)
static void ring_buffer_init(struct ring_buffer *rb, long watermark, int flags)
void perf_aux_output_flag(struct perf_output_handle *handle, u64 flags)
void *perf_aux_output_begin(struct perf_output_handle *handle, struct perf_event *event)
static __always_inline bool rb_need_aux_wakeup(struct ring_buffer *rb)
void perf_aux_output_end(struct perf_output_handle *handle, unsigned long size)
int perf_aux_output_skip(struct perf_output_handle *handle, unsigned long size)
void *perf_get_aux(struct perf_output_handle *handle)
static struct page *rb_alloc_aux_page(int node, int order)
static void rb_free_aux_page(struct ring_buffer *rb, int idx)
static void __rb_free_aux(struct ring_buffer *rb)
int rb_alloc_aux(struct ring_buffer *rb, struct perf_event *event, pgoff_t pgoff, int nr_pages, long watermark, int flags)
void rb_free_aux(struct ring_buffer *rb)
static struct page * __perf_mmap_to_page(struct ring_buffer *rb, unsigned long pgoff)
static void *perf_mmap_alloc_page(int cpu)
struct ring_buffer *rb_alloc(int nr_pages, long watermark, int cpu, int flags)
static void perf_mmap_free_page(unsigned long addr)
void rb_free(struct ring_buffer *rb)
static int data_page_nr(struct ring_buffer *rb)
static struct page * __perf_mmap_to_page(struct ring_buffer *rb, unsigned long pgoff)
static void perf_mmap_unmark_page(void *addr)
static void rb_free_work(struct work_struct *work)
void rb_free(struct ring_buffer *rb)
struct ring_buffer *rb_alloc(int nr_pages, long watermark, int cpu, int flags)
struct page * perf_mmap_to_page(struct ring_buffer *rb, unsigned long pgoff)
\n
     15 struct perf_output_handle *handle
     12 struct ring_buffer *rb
      6 struct perf_event *event
      5 unsigned int size
      4 long watermark
      4 int flags
      3 unsigned long pgoff
      3 int nr_pages
      3 int cpu
      2 unsigned long size
      2 unsigned int len
      2 bool backward
      1 void *addr
      1 unsigned long tail
      1 unsigned long head
      1 unsigned long data_size
      1 unsigned long addr
      1 u64 flags
      1 struct work_struct *work
      1 pgoff_t pgoff
      1 perf_get_aux
      1 perf_aux_output_skip
      1 perf_aux_output_flag
      1 perf_aux_output_end
      1 perf_aux_output_begin
      1 int order
      1 int node
      1 int idx
      1 const void *buf
