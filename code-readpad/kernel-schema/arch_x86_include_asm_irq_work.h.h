
\n
static inline bool arch_irq_work_has_interrupt(void)
static inline bool arch_irq_work_has_interrupt(void)
return boot_cpu_has(X86_FEATURE_APIC)
; } extern void arch_irq_work_raise(void)
; extern __visible void smp_irq_work_interrupt(struct pt_regs *regs)
; static inline bool arch_irq_work_has_interrupt(void)
\n
      4 void
      1 X86_FEATURE_APIC
      1 struct pt_regs *regs
