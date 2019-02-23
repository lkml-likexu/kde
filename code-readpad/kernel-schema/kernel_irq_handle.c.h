
EXPORT_SYMBOL_GPL(handle_bad_irq);
EXPORT_SYMBOL_GPL(no_action);
\n
void handle_bad_irq(struct irq_desc *desc)
irqreturn_t no_action(int cpl, void *dev_id)
static void warn_no_thread(unsigned int irq, struct irqaction *action)
void __irq_wake_thread(struct irq_desc *desc, struct irqaction *action)
irqreturn_t __handle_irq_event_percpu(struct irq_desc *desc, unsigned int *flags)
irqreturn_t handle_irq_event_percpu(struct irq_desc *desc)
irqreturn_t handle_irq_event(struct irq_desc *desc)
int __init set_handle_irq(void (*handle_irq)
(struct pt_regs *)
)
\n
      5 struct irq_desc *desc
      2 struct irqaction *action
      1 void *handle_irq
      1 void *dev_id
      1 unsigned int irq
      1 unsigned int *flags
      1 struct pt_regs *
      1 no_action
      1 int cpl
      1 handle_bad_irq
