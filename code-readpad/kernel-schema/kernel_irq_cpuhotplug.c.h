
\n
static inline bool irq_needs_fixup(struct irq_data *d)
static bool migrate_one_irq(struct irq_desc *desc)
void irq_migrate_all_off_this_cpu(void)
static void irq_restore_affinity_of_irq(struct irq_desc *desc, unsigned int cpu)
int irq_affinity_online_cpu(unsigned int cpu)
\n
      2 unsigned int cpu
      2 struct irq_desc *desc
      1 void
      1 struct irq_data *d
