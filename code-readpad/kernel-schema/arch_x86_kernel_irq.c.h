
EXPORT_SYMBOL_GPL(kvm_set_posted_intr_wakeup_handler);
\n
void ack_bad_irq(unsigned int irq)
define irq_stats(x)
(&per_cpu(irq_stat, x)
)
int arch_show_interrupts(struct seq_file *p, int prec)
u64 arch_irq_stat_cpu(unsigned int cpu)
u64 arch_irq_stat(void)
__visible unsigned int __irq_entry do_IRQ(struct pt_regs *regs)
void (*x86_platform_ipi_callback)
(void)
= NULL;__visible void __irq_entry smp_x86_platform_ipi(struct pt_regs *regs)
void kvm_set_posted_intr_wakeup_handler(void (*handler)
(void)
)
__visible void smp_kvm_posted_intr_ipi(struct pt_regs *regs)
__visible void smp_kvm_posted_intr_wakeup_ipi(struct pt_regs *regs)
__visible void smp_kvm_posted_intr_nested_ipi(struct pt_regs *regs)
void fixup_irqs(void)
\n
      5 struct pt_regs *regs
      4 void
      2 x
      1 *x86_platform_ipi_callback
      1 void *handler
      1 unsigned int irq
      1 unsigned int cpu
      1 struct seq_file *p
      1 &per_cpuirq_stat
      1 kvm_set_posted_intr_wakeup_handler
      1 int prec
