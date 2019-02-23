
\n
static inline struct perf_cgroup * perf_cgroup_from_task(struct task_struct *task, struct perf_event_context *ctx)
static inline void perf_sample_data_init(struct perf_sample_data *data, u64 addr, u64 period)
static inline bool is_default_overflow_handler(struct perf_event *event)
static inline bool is_sampling_event(struct perf_event *event)
static inline int is_software_event(struct perf_event *event)
static inline int in_software_context(struct perf_event *event)
static inline void perf_fetch_caller_regs(struct pt_regs *regs)
static __always_inline void perf_sw_event(u32 event_id, u64 nr, struct pt_regs *regs, u64 addr)
static __always_inline void perf_sw_event_sched(u32 event_id, u64 nr, u64 addr)
static __always_inline bool perf_sw_migrate_enabled(void)
static inline void perf_event_task_migrate(struct task_struct *task)
static inline void perf_event_task_sched_in(struct task_struct *prev, struct task_struct *task)
static inline void perf_event_task_sched_out(struct task_struct *prev, struct task_struct *next)
static inline int perf_callchain_store_context(struct perf_callchain_entry_ctx *ctx, u64 ip)
static inline int perf_callchain_store(struct perf_callchain_entry_ctx *ctx, u64 ip)
static inline bool perf_paranoid_tracepoint_raw(void)
static inline bool perf_paranoid_cpu(void)
static inline bool perf_paranoid_kernel(void)
static inline bool has_branch_stack(struct perf_event *event)
static inline bool needs_branch_stack(struct perf_event *event)
static inline bool has_aux(struct perf_event *event)
static inline bool is_write_backward(struct perf_event *event)
static inline bool has_addr_filter(struct perf_event *event)
static inline struct perf_addr_filters_head * perf_event_addr_filters(struct perf_event *event)
extern void perf_output_end(struct perf_output_handle *handle)
; extern unsigned int perf_output_copy(struct perf_output_handle *handle, const void *buf, unsigned int len)
; extern unsigned int perf_output_skip(struct perf_output_handle *handle, unsigned int len)
; extern int perf_swevent_get_recursion_context(void)
; extern void perf_swevent_put_recursion_context(int rctx)
; extern u64 perf_swevent_set_period(struct perf_event *event)
; extern void perf_event_enable(struct perf_event *event)
; extern void perf_event_disable(struct perf_event *event)
; extern void perf_event_disable_local(struct perf_event *event)
; extern void perf_event_disable_inatomic(struct perf_event *event)
; extern void perf_event_task_tick(void)
; extern int perf_event_account_interrupt(struct perf_event *event)
; static inline void * perf_aux_output_begin(struct perf_output_handle *handle, static inline void perf_aux_output_end(struct perf_output_handle *handle, unsigned long size)
static inline int perf_aux_output_skip(struct perf_output_handle *handle, static inline void * static inline void static inline void perf_event_task_sched_in(struct task_struct *prev, static inline void perf_event_task_sched_out(struct task_struct *prev, static inline const struct perf_event *perf_get_event(struct file *file)
extern void perf_output_end(struct perf_output_handle *handle)
; extern unsigned int perf_output_copy(struct perf_output_handle *handle, const void *buf, unsigned int len)
; extern unsigned int perf_output_skip(struct perf_output_handle *handle, unsigned int len)
; extern int perf_swevent_get_recursion_context(void)
; extern void perf_swevent_put_recursion_context(int rctx)
; extern u64 perf_swevent_set_period(struct perf_event *event)
; extern void perf_event_enable(struct perf_event *event)
; extern void perf_event_disable(struct perf_event *event)
; extern void perf_event_disable_local(struct perf_event *event)
; extern void perf_event_disable_inatomic(struct perf_event *event)
; extern void perf_event_task_tick(void)
; extern int perf_event_account_interrupt(struct perf_event *event)
; static inline void * perf_aux_output_begin(struct perf_output_handle *handle, static inline void perf_aux_output_end(struct perf_output_handle *handle, unsigned long size)
static inline int perf_aux_output_skip(struct perf_output_handle *handle, static inline void * static inline void static inline void perf_event_task_sched_in(struct task_struct *prev, static inline void perf_event_task_sched_out(struct task_struct *prev, static inline const struct perf_event *perf_get_event(struct file *file)
return ERR_PTR(-EINVAL)
; } static inline const struct perf_event_attr *perf_event_attrs(struct perf_event *event)
extern void perf_output_end(struct perf_output_handle *handle)
; extern unsigned int perf_output_copy(struct perf_output_handle *handle, const void *buf, unsigned int len)
; extern unsigned int perf_output_skip(struct perf_output_handle *handle, unsigned int len)
; extern int perf_swevent_get_recursion_context(void)
; extern void perf_swevent_put_recursion_context(int rctx)
; extern u64 perf_swevent_set_period(struct perf_event *event)
; extern void perf_event_enable(struct perf_event *event)
; extern void perf_event_disable(struct perf_event *event)
; extern void perf_event_disable_local(struct perf_event *event)
; extern void perf_event_disable_inatomic(struct perf_event *event)
; extern void perf_event_task_tick(void)
; extern int perf_event_account_interrupt(struct perf_event *event)
; static inline void * perf_aux_output_begin(struct perf_output_handle *handle, static inline void perf_aux_output_end(struct perf_output_handle *handle, unsigned long size)
static inline int perf_aux_output_skip(struct perf_output_handle *handle, static inline void * static inline void static inline void perf_event_task_sched_in(struct task_struct *prev, static inline void perf_event_task_sched_out(struct task_struct *prev, static inline const struct perf_event *perf_get_event(struct file *file)
return ERR_PTR(-EINVAL)
; } static inline const struct perf_event_attr *perf_event_attrs(struct perf_event *event)
return ERR_PTR(-EINVAL)
; } static inline int perf_event_read_local(struct perf_event *event, u64 *value, u64 *enabled, u64 *running)
extern void perf_output_end(struct perf_output_handle *handle)
; extern unsigned int perf_output_copy(struct perf_output_handle *handle, const void *buf, unsigned int len)
; extern unsigned int perf_output_skip(struct perf_output_handle *handle, unsigned int len)
; extern int perf_swevent_get_recursion_context(void)
; extern void perf_swevent_put_recursion_context(int rctx)
; extern u64 perf_swevent_set_period(struct perf_event *event)
; extern void perf_event_enable(struct perf_event *event)
; extern void perf_event_disable(struct perf_event *event)
; extern void perf_event_disable_local(struct perf_event *event)
; extern void perf_event_disable_inatomic(struct perf_event *event)
; extern void perf_event_task_tick(void)
; extern int perf_event_account_interrupt(struct perf_event *event)
; static inline void * perf_aux_output_begin(struct perf_output_handle *handle, static inline void perf_aux_output_end(struct perf_output_handle *handle, unsigned long size)
static inline int perf_aux_output_skip(struct perf_output_handle *handle, static inline void * static inline void static inline void perf_event_task_sched_in(struct task_struct *prev, static inline void perf_event_task_sched_out(struct task_struct *prev, static inline const struct perf_event *perf_get_event(struct file *file)
return ERR_PTR(-EINVAL)
; } static inline const struct perf_event_attr *perf_event_attrs(struct perf_event *event)
return ERR_PTR(-EINVAL)
; } static inline int perf_event_read_local(struct perf_event *event, u64 *value, u64 *enabled, u64 *running)
return -EINVAL; } static inline int perf_event_refresh(struct perf_event *event, int refresh)
static __always_inline bool perf_raw_frag_last(const struct perf_raw_frag *frag)
define PMU_FORMAT_ATTR(_name, _format)
\ static ssize_t\ _name_show(struct device *dev, \ struct device_attribute *attr, \ char *page)
\ \n
     40 struct perf_event *event
     20 struct perf_output_handle *handle
     12 void
      8 unsigned int len
      5 -EINVAL
      4 unsigned long size
      4 static inline void * static inline void static inline void perf_event_task_sched_instruct task_struct *prev
      4 static inline void perf_event_task_sched_outstruct task_struct *prev
      4 static inline void perf_aux_output_endstruct perf_output_handle *handle
      4 static inline const struct perf_event *perf_get_eventstruct file *file
      4 int rctx
      4 const void *buf
      3 u64 addr
      3 struct task_struct *task
      2 u64 *value
      2 u64 *running
      2 u64 nr
      2 u64 ip
      2 u64 *enabled
      2 u32 event_id
      2 struct task_struct *prev
      2 struct pt_regs *regs
      2 struct perf_callchain_entry_ctx *ctx
      1 u64 period
      1 struct task_struct *next
      1 struct perf_sample_data *data
      1 struct perf_event_context *ctx
      1 struct device *dev
      1 \ struct device_attribute *attr
      1 _name
      1 int refresh
      1 _format
      1 const struct perf_raw_frag *frag
      1 \ char *page
