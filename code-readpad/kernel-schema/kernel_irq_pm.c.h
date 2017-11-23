
EXPORT_SYMBOL_GPL(suspend_device_irqs);
EXPORT_SYMBOL_GPL(resume_device_irqs);
bool irq_pm_check_wakeup(struct irq_desc *desc)
void irq_pm_install_action(struct irq_desc *desc, struct irqaction *action)
void irq_pm_remove_action(struct irq_desc *desc, struct irqaction *action)
static bool suspend_device_irq(struct irq_desc *desc)
void suspend_device_irqs(void)
static void resume_irq(struct irq_desc *desc)
static void resume_irqs(bool want_early)
static void irq_pm_syscore_resume(void)
static int __init irq_pm_init_ops(void)
void resume_device_irqs(void)
   5 struct irq_desc *desc
   4 void
   2 struct irqaction *action
   1 suspend_device_irqs
   1 resume_device_irqs
   1 bool want_early
