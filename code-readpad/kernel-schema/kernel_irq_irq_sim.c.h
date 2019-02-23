
EXPORT_SYMBOL_GPL(irq_sim_init);
EXPORT_SYMBOL_GPL(irq_sim_fini);
EXPORT_SYMBOL_GPL(devm_irq_sim_init);
EXPORT_SYMBOL_GPL(irq_sim_fire);
EXPORT_SYMBOL_GPL(irq_sim_irqnum);
\n
static void irq_sim_irqmask(struct irq_data *data)
static void irq_sim_irqunmask(struct irq_data *data)
static void irq_sim_handle_irq(struct irq_work *work)
int irq_sim_init(struct irq_sim *sim, unsigned int num_irqs)
void irq_sim_fini(struct irq_sim *sim)
static void devm_irq_sim_release(struct device *dev, void *res)
int devm_irq_sim_init(struct device *dev, struct irq_sim *sim, unsigned int num_irqs)
void irq_sim_fire(struct irq_sim *sim, unsigned int offset)
int irq_sim_irqnum(struct irq_sim *sim, unsigned int offset)
\n
      5 struct irq_sim *sim
      2 unsigned int offset
      2 unsigned int num_irqs
      2 struct irq_data *data
      2 struct device *dev
      1 void *res
      1 struct irq_work *work
      1 irq_sim_irqnum
      1 irq_sim_init
      1 irq_sim_fire
      1 irq_sim_fini
      1 devm_irq_sim_init
