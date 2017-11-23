
EXPORT_SYMBOL_GPL(irq_work_queue);
EXPORT_SYMBOL_GPL(irq_work_run);
EXPORT_SYMBOL_GPL(irq_work_sync);
static bool irq_work_claim(struct irq_work *work)
void __weak arch_irq_work_raise(void)
bool irq_work_queue_on(struct irq_work *work, int cpu)
bool irq_work_queue(struct irq_work *work)
bool irq_work_needs_cpu(void)
static void irq_work_run_list(struct llist_head *list)
void irq_work_run(void)
void irq_work_tick(void)
void irq_work_sync(struct irq_work *work)
   4 void
   4 struct irq_work *work
   1 struct llist_head *list
   1 irq_work_sync
   1 irq_work_run
   1 irq_work_queue
   1 int cpu
