
EXPORT_SYMBOL_GPL(irq_bypass_register_producer);
EXPORT_SYMBOL_GPL(irq_bypass_unregister_producer);
EXPORT_SYMBOL_GPL(irq_bypass_register_consumer);
EXPORT_SYMBOL_GPL(irq_bypass_unregister_consumer);
\n
static int __connect(struct irq_bypass_producer *prod, struct irq_bypass_consumer *cons)
static void __disconnect(struct irq_bypass_producer *prod, struct irq_bypass_consumer *cons)
int irq_bypass_register_producer(struct irq_bypass_producer *producer)
void irq_bypass_unregister_producer(struct irq_bypass_producer *producer)
int irq_bypass_register_consumer(struct irq_bypass_consumer *consumer)
void irq_bypass_unregister_consumer(struct irq_bypass_consumer *consumer)
\n
      2 struct irq_bypass_producer *producer
      2 struct irq_bypass_producer *prod
      2 struct irq_bypass_consumer *consumer
      2 struct irq_bypass_consumer *cons
      1 irq_bypass_unregister_producer
      1 irq_bypass_unregister_consumer
      1 irq_bypass_register_producer
      1 irq_bypass_register_consumer
