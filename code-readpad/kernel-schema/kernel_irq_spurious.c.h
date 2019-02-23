
\n
bool irq_wait_for_poll(struct irq_desc *desc)
static int try_one_irq(struct irq_desc *desc, bool force)
static int misrouted_irq(int irq)
static void poll_spurious_irqs(struct timer_list *unused)
static inline int bad_action_ret(irqreturn_t action_ret)
static void __report_bad_irq(struct irq_desc *desc, irqreturn_t action_ret)
static void report_bad_irq(struct irq_desc *desc, irqreturn_t action_ret)
static inline int try_misrouted_irq(unsigned int irq, struct irq_desc *desc, irqreturn_t action_ret)
void note_interrupt(struct irq_desc *desc, irqreturn_t action_ret)
int noirqdebug_setup(char *str)
static int __init irqfixup_setup(char *str)
static int __init irqpoll_setup(char *str)
\n
      6 struct irq_desc *desc
      5 irqreturn_t action_ret
      3 char *str
      1 unsigned int irq
      1 struct timer_list *unused
      1 int irq
      1 bool force
