
\n
static unsigned long mmu_node_start(struct mmu_rb_node *node)
static unsigned long mmu_node_last(struct mmu_rb_node *node)
int hfi1_mmu_rb_register(void *ops_arg, struct mm_struct *mm, struct mmu_rb_ops *ops, struct workqueue_struct *wq, struct mmu_rb_handler **handler)
void hfi1_mmu_rb_unregister(struct mmu_rb_handler *handler)
int hfi1_mmu_rb_insert(struct mmu_rb_handler *handler, struct mmu_rb_node *mnode)
static struct mmu_rb_node *__mmu_rb_search(struct mmu_rb_handler *handler, unsigned long addr, unsigned long len)
bool hfi1_mmu_rb_remove_unless_exact(struct mmu_rb_handler *handler, unsigned long addr, unsigned long len, struct mmu_rb_node **rb_node)
void hfi1_mmu_rb_evict(struct mmu_rb_handler *handler, void *evict_arg)
void hfi1_mmu_rb_remove(struct mmu_rb_handler *handler, struct mmu_rb_node *node)
static int mmu_notifier_range_start(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static void do_remove(struct mmu_rb_handler *handler, struct list_head *del_list)
static void handle_remove(struct work_struct *work)
\n
      7 struct mmu_rb_handler *handler
      3 struct mmu_rb_node *node
      2 unsigned long len
      2 unsigned long addr
      1 void *ops_arg
      1 void *evict_arg
      1 struct work_struct *work
      1 struct workqueue_struct *wq
      1 struct mmu_rb_ops *ops
      1 struct mmu_rb_node **rb_node
      1 struct mmu_rb_node *mnode
      1 struct mmu_rb_handler **handler
      1 struct mmu_notifier *mn
      1 struct mm_struct *mm
      1 struct list_head *del_list
      1 const struct mmu_notifier_range *range
