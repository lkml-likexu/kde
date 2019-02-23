
\n
static inline void rb_free_rcu(struct rcu_head *rcu_head)
static inline void rb_toggle_paused(struct ring_buffer *rb, bool pause)
static inline bool rb_has_aux(struct ring_buffer *rb)
static inline int page_order(struct ring_buffer *rb)
static inline int page_order(struct ring_buffer *rb)
static inline unsigned long perf_data_size(struct ring_buffer *rb)
static inline unsigned long perf_aux_size(struct ring_buffer *rb)
define __DEFINE_OUTPUT_COPY_BODY(advance_buf, memcpy_func, ...)
\ static inline unsigned long __output_custom(struct perf_output_handle *handle, perf_copy_f copy_func, const void *buf, unsigned long len)
static inline unsigned long memcpy_common(void *dst, const void *src, unsigned long n)
static inline unsigned long memcpy_skip(void *dst, const void *src, unsigned long n)
static inline unsigned long arch_perf_out_copy_user(void *dst, const void *src, unsigned long n)
static inline int get_recursion_context(int *recursion)
static inline void put_recursion_context(int *recursion, int rctx)
static inline bool arch_perf_have_user_stack_dump(void)
define perf_user_stack_pointer(regs)
user_stack_pointer(regs)
static inline bool arch_perf_have_user_stack_dump(void)
\n
      6 struct ring_buffer *rb
      3 void *dst
      3 unsigned long n
      3 const void *src
      2 void
      2 regs
      2 int *recursion
      1 unsigned long len
      1 struct rcu_head *rcu_head
      1 struct perf_output_handle *handle
      1 perf_copy_f copy_func
      1 memcpy_func
      1 int rctx
      1 const void *buf
      1 bool pause
      1 advance_buf
      1 ...
