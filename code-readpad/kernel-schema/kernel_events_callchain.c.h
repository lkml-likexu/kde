
static inline size_t perf_callchain_entry__sizeof(void)
__weak void perf_callchain_kernel(struct perf_callchain_entry_ctx *entry, struct pt_regs *regs)
__weak void perf_callchain_user(struct perf_callchain_entry_ctx *entry, struct pt_regs *regs)
static void release_callchain_buffers_rcu(struct rcu_head *head)
static void release_callchain_buffers(void)
static int alloc_callchain_buffers(void)
int get_callchain_buffers(int event_max_stack)
void put_callchain_buffers(void)
static struct perf_callchain_entry *get_callchain_entry(int *rctx)
static void put_callchain_entry(int rctx)
struct perf_callchain_entry * get_perf_callchain(struct pt_regs *regs, u32 init_nr, bool kernel, bool user, u32 max_stack, bool crosstask, bool add_mark)
int perf_event_max_stack_handler(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
   4 void
   3 struct pt_regs *regs
   2 struct perf_callchain_entry_ctx *entry
   1 void __user *buffer
   1 u32 max_stack
   1 u32 init_nr
   1 struct rcu_head *head
   1 struct ctl_table *table
   1 size_t *lenp
   1 loff_t *ppos
   1 int write
   1 int rctx
   1 int event_max_stack
   1 int *rctx
   1 bool user
   1 bool kernel
   1 bool crosstask
   1 bool add_mark
