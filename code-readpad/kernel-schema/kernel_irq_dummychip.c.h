
EXPORT_SYMBOL_GPL(dummy_irq_chip);
static void ack_bad(struct irq_data *data)
static unsigned int noop_ret(struct irq_data *data)
   2 struct irq_data *data
   1 dummy_irq_chip
