
EXPORT_SYMBOL_GPL(nr_irqs);
EXPORT_SYMBOL_GPL(generic_handle_irq);
EXPORT_SYMBOL_GPL(irq_free_descs);
EXPORT_SYMBOL_GPL(__irq_alloc_descs);
EXPORT_SYMBOL_GPL(irq_alloc_hwirqs);
EXPORT_SYMBOL_GPL(irq_free_hwirqs);
EXPORT_SYMBOL_GPL(irq_get_percpu_devid_partition);
\n
static int __init irq_affinity_setup(char *str)
static void __init init_irq_default_affinity(void)
static void __init init_irq_default_affinity(void)
if (!cpumask_available(irq_default_affinity)
)
zalloc_cpumask_var(&irq_default_affinity, GFP_NOWAIT)
;if (cpumask_empty(irq_default_affinity)
)
cpumask_setall(irq_default_affinity)
; } static void __init init_irq_default_affinity(void)
static int alloc_masks(struct irq_desc *desc, int node)
static void desc_smp_init(struct irq_desc *desc, int node, const struct cpumask *affinity)
static void desc_set_defaults(unsigned int irq, struct irq_desc *desc, int node, const struct cpumask *affinity, struct module *owner)
static ssize_t per_cpu_count_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t chip_name_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t hwirq_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t type_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t wakeup_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t name_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t actions_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static void irq_sysfs_add(int irq, struct irq_desc *desc)
static int __init irq_sysfs_init(void)
static void irq_insert_desc(unsigned int irq, struct irq_desc *desc)
struct irq_desc *irq_to_desc(unsigned int irq)
static void delete_irq_desc(unsigned int irq)
static void free_masks(struct irq_desc *desc)
void irq_lock_sparse(void)
void irq_unlock_sparse(void)
static struct irq_desc *alloc_desc(int irq, int node, unsigned int flags, const struct cpumask *affinity, struct module *owner)
static void irq_kobj_release(struct kobject *kobj)
static void delayed_free_desc(struct rcu_head *rhp)
static void free_desc(unsigned int irq)
static int alloc_descs(unsigned int start, unsigned int cnt, int node, const struct irq_affinity_desc *affinity, struct module *owner)
static int irq_expand_nr_irqs(unsigned int nr)
int __init early_irq_init(void)
int __init early_irq_init(void)
struct irq_desc *irq_to_desc(unsigned int irq)
static void free_desc(unsigned int irq)
static inline int alloc_descs(unsigned int start, unsigned int cnt, int node, const struct irq_affinity_desc *affinity, struct module *owner)
static int irq_expand_nr_irqs(unsigned int nr)
void irq_mark_irq(unsigned int irq)
void irq_init_desc(unsigned int irq)
int generic_handle_irq(unsigned int irq)
int __handle_domain_irq(struct irq_domain *domain, unsigned int hwirq, bool lookup, struct pt_regs *regs)
void irq_free_descs(unsigned int from, unsigned int cnt)
int __ref __irq_alloc_descs(int irq, unsigned int from, unsigned int cnt, int node, struct module *owner, const struct irq_affinity_desc *affinity)
unsigned int irq_alloc_hwirqs(int cnt, int node)
void irq_free_hwirqs(unsigned int from, int cnt)
unsigned int irq_get_next_irq(unsigned int offset)
struct irq_desc * __irq_get_desc_lock(unsigned int irq, unsigned long *flags, bool bus, unsigned int check)
void __irq_put_desc_unlock(struct irq_desc *desc, unsigned long flags, bool bus)
int irq_set_percpu_devid_partition(unsigned int irq, const struct cpumask *affinity)
int irq_set_percpu_devid(unsigned int irq)
int irq_get_percpu_devid_partition(unsigned int irq, struct cpumask *affinity)
void kstat_incr_irq_this_cpu(unsigned int irq)
unsigned int kstat_irqs_cpu(unsigned int irq, int cpu)
unsigned int kstat_irqs(unsigned int irq)
unsigned int kstat_irqs_usr(unsigned int irq)
\n
     18 unsigned int irq
      8 void
      8 struct kobject *kobj
      8 int node
      7 struct kobj_attribute *attr
      7 struct irq_desc *desc
      7 char *buf
      5 struct module *owner
      4 unsigned int cnt
      4 const struct cpumask *affinity
      3 unsigned int from
      3 int irq
      3 const struct irq_affinity_desc *affinity
      2 unsigned int start
      2 unsigned int nr
      2 int cnt
      2 bool bus
      1 unsigned long *flags
      1 unsigned long flags
      1 unsigned int offset
      1 unsigned int hwirq
      1 unsigned int flags
      1 unsigned int check
      1 struct rcu_head *rhp
      1 struct pt_regs *regs
      1 struct irq_domain *domain
      1 struct cpumask *affinity
      1 nr_irqs
      1 irq_get_percpu_devid_partition
      1 irq_free_hwirqs
      1 irq_free_descs
      1 irq_default_affinity
      1 &irq_default_affinity
      1 irq_alloc_hwirqs
      1 __irq_alloc_descs
      1 int cpu
      1 GFP_NOWAIT
      1 generic_handle_irq
      1 cpumask_emptyirq_default_affinity
      1 !cpumask_availableirq_default_affinity
      1 char *str
      1 bool lookup
