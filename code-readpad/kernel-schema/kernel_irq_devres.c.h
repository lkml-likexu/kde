
EXPORT_SYMBOL_GPL(__devm_irq_alloc_descs);
EXPORT_SYMBOL_GPL(devm_irq_alloc_generic_chip);
EXPORT_SYMBOL_GPL(devm_irq_setup_generic_chip);
static void devm_irq_release(struct device *dev, void *res)
static int devm_irq_match(struct device *dev, void *res, void *data)
int devm_request_threaded_irq(struct device *dev, unsigned int irq, irq_handler_t handler, irq_handler_t thread_fn, unsigned long irqflags, const char *devname, void *dev_id)
int devm_request_any_context_irq(struct device *dev, unsigned int irq, irq_handler_t handler, unsigned long irqflags, const char *devname, void *dev_id)
void devm_free_irq(struct device *dev, unsigned int irq, void *dev_id)
static void devm_irq_desc_release(struct device *dev, void *res)
int __devm_irq_alloc_descs(struct device *dev, int irq, unsigned int from, unsigned int cnt, int node, struct module *owner, const struct cpumask *affinity)
struct irq_chip_generic * devm_irq_alloc_generic_chip(struct device *dev, const char *name, int num_ct, unsigned int irq_base, void __iomem *reg_base, irq_flow_handler_t handler)
static void devm_irq_remove_generic_chip(struct device *dev, void *res)
int devm_irq_setup_generic_chip(struct device *dev, struct irq_chip_generic *gc, u32 msk, enum irq_gc_flags flags, unsigned int clr, unsigned int set)
  10 struct device *dev
   4 void *res
   3 void *dev_id
   3 unsigned int irq
   2 unsigned long irqflags
   2 irq_handler_t handler
   2 const char *devname
   1 void __iomem *reg_base
   1 void *data
   1 unsigned int set
   1 unsigned int irq_base
   1 unsigned int from
   1 unsigned int cnt
   1 unsigned int clr
   1 u32 msk
   1 struct module *owner
   1 struct irq_chip_generic *gc
   1 irq_handler_t thread_fn
   1 irq_flow_handler_t handler
   1 int num_ct
   1 int node
   1 int irq
   1 enum irq_gc_flags flags
   1 devm_irq_setup_generic_chip
   1 devm_irq_alloc_generic_chip
   1 const struct cpumask *affinity
   1 const char *name
   1 __devm_irq_alloc_descs
