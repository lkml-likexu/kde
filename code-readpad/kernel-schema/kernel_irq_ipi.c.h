
EXPORT_SYMBOL_GPL(ipi_get_hwirq);
EXPORT_SYMBOL_GPL(ipi_send_single);
EXPORT_SYMBOL_GPL(ipi_send_mask);
\n
int irq_reserve_ipi(struct irq_domain *domain, const struct cpumask *dest)
int irq_destroy_ipi(unsigned int irq, const struct cpumask *dest)
irq_hw_number_t ipi_get_hwirq(unsigned int irq, unsigned int cpu)
static int ipi_send_verify(struct irq_chip *chip, struct irq_data *data, const struct cpumask *dest, unsigned int cpu)
int __ipi_send_single(struct irq_desc *desc, unsigned int cpu)
int __ipi_send_mask(struct irq_desc *desc, const struct cpumask *dest)
int ipi_send_single(unsigned int virq, unsigned int cpu)
int ipi_send_mask(unsigned int virq, const struct cpumask *dest)
\n
      5 const struct cpumask *dest
      4 unsigned int cpu
      2 unsigned int virq
      2 unsigned int irq
      2 struct irq_desc *desc
      1 struct irq_domain *domain
      1 struct irq_data *data
      1 struct irq_chip *chip
      1 ipi_send_single
      1 ipi_send_mask
      1 ipi_get_hwirq
