
\n
void __init init_IRQ(void)
void do_IRQ(struct pt_regs *regs, int irq)
int show_interrupts(struct seq_file *p, void *v)
unsigned int arch_dynirq_lower_bound(unsigned int from)
void do_softirq_own_stack(void)
static inline int ext_hash(u16 code)
int register_external_irq(u16 code, ext_int_handler_t handler)
int unregister_external_irq(u16 code, ext_int_handler_t handler)
static irqreturn_t do_ext_interrupt(int irq, void *dummy)
void __init init_ext_interrupts(void)
void irq_subclass_register(enum irq_subclass subclass)
void irq_subclass_unregister(enum irq_subclass subclass)
\n
      3 void
      3 u16 code
      2 int irq
      2 ext_int_handler_t handler
      2 enum irq_subclass subclass
      1 void *v
      1 void *dummy
      1 unsigned int from
      1 struct seq_file *p
      1 struct pt_regs *regs
