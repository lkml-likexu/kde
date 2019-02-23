
EXPORT_SYMBOL_GPL(irq_gc_mask_set_bit);
EXPORT_SYMBOL_GPL(irq_gc_mask_clr_bit);
EXPORT_SYMBOL_GPL(irq_gc_ack_set_bit);
EXPORT_SYMBOL_GPL(irq_alloc_generic_chip);
EXPORT_SYMBOL_GPL(__irq_alloc_domain_generic_chips);
EXPORT_SYMBOL_GPL(irq_get_domain_generic_chip);
EXPORT_SYMBOL_GPL(irq_generic_chip_ops);
EXPORT_SYMBOL_GPL(irq_setup_generic_chip);
EXPORT_SYMBOL_GPL(irq_setup_alt_chip);
EXPORT_SYMBOL_GPL(irq_remove_generic_chip);
\n
void irq_gc_noop(struct irq_data *d)
void irq_gc_mask_disable_reg(struct irq_data *d)
void irq_gc_mask_set_bit(struct irq_data *d)
void irq_gc_mask_clr_bit(struct irq_data *d)
void irq_gc_unmask_enable_reg(struct irq_data *d)
void irq_gc_ack_set_bit(struct irq_data *d)
void irq_gc_ack_clr_bit(struct irq_data *d)
void irq_gc_mask_disable_and_ack_set(struct irq_data *d)
void irq_gc_eoi(struct irq_data *d)
int irq_gc_set_wake(struct irq_data *d, unsigned int on)
static u32 irq_readl_be(void __iomem *addr)
static void irq_writel_be(u32 val, void __iomem *addr)
void irq_init_generic_chip(struct irq_chip_generic *gc, const char *name, int num_ct, unsigned int irq_base, void __iomem *reg_base, irq_flow_handler_t handler)
struct irq_chip_generic * irq_alloc_generic_chip(const char *name, int num_ct, unsigned int irq_base, void __iomem *reg_base, irq_flow_handler_t handler)
static void irq_gc_init_mask_cache(struct irq_chip_generic *gc, enum irq_gc_flags flags)
int __irq_alloc_domain_generic_chips(struct irq_domain *d, int irqs_per_chip, int num_ct, const char *name, irq_flow_handler_t handler, unsigned int clr, unsigned int set, enum irq_gc_flags gcflags)
static struct irq_chip_generic * __irq_get_domain_generic_chip(struct irq_domain *d, unsigned int hw_irq)
struct irq_chip_generic * irq_get_domain_generic_chip(struct irq_domain *d, unsigned int hw_irq)
int irq_map_generic_chip(struct irq_domain *d, unsigned int virq, irq_hw_number_t hw_irq)
static void irq_unmap_generic_chip(struct irq_domain *d, unsigned int virq)
void irq_setup_generic_chip(struct irq_chip_generic *gc, u32 msk, enum irq_gc_flags flags, unsigned int clr, unsigned int set)
int irq_setup_alt_chip(struct irq_data *d, unsigned int type)
void irq_remove_generic_chip(struct irq_chip_generic *gc, u32 msk, unsigned int clr, unsigned int set)
static struct irq_data *irq_gc_get_irq_data(struct irq_chip_generic *gc)
static int irq_gc_suspend(void)
static void irq_gc_resume(void)
static void irq_gc_shutdown(void)
static int __init irq_gc_init_ops(void)
\n
     11 struct irq_data *d
      5 struct irq_domain *d
      5 struct irq_chip_generic *gc
      4 void
      3 unsigned int set
      3 unsigned int clr
      3 irq_flow_handler_t handler
      3 int num_ct
      3 const char *name
      2 void __iomem *reg_base
      2 void __iomem *addr
      2 unsigned int virq
      2 unsigned int irq_base
      2 unsigned int hw_irq
      2 u32 msk
      2 enum irq_gc_flags flags
      1 unsigned int type
      1 unsigned int on
      1 u32 val
      1 irq_setup_generic_chip
      1 irq_setup_alt_chip
      1 irq_remove_generic_chip
      1 irq_hw_number_t hw_irq
      1 irq_get_domain_generic_chip
      1 irq_generic_chip_ops
      1 irq_gc_mask_set_bit
      1 irq_gc_mask_clr_bit
      1 irq_gc_ack_set_bit
      1 irq_alloc_generic_chip
      1 __irq_alloc_domain_generic_chips
      1 int irqs_per_chip
      1 enum irq_gc_flags gcflags
