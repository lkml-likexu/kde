
EXPORT_SYMBOL_GPL(irq_remapping_cap);
static void irq_remapping_restore_boot_irq_mode(void)
static void __init irq_remapping_modify_x86_ops(void)
static __init int setup_nointremap(char *str)
static __init int setup_irqremap(char *str)
void set_irq_remapping_broken(void)
bool irq_remapping_cap(enum irq_remap_cap cap)
int __init irq_remapping_prepare(void)
int __init irq_remapping_enable(void)
void irq_remapping_disable(void)
int irq_remapping_reenable(int mode)
int __init irq_remap_enable_fault_handling(void)
void panic_if_irq_remap(const char *msg)
struct irq_domain * irq_remapping_get_ir_irq_domain(struct irq_alloc_info *info)
struct irq_domain * irq_remapping_get_irq_domain(struct irq_alloc_info *info)
   7 void
   2 struct irq_alloc_info *info
   2 char *str
   1 irq_remapping_cap
   1 int mode
   1 enum irq_remap_cap cap
   1 const char *msg
