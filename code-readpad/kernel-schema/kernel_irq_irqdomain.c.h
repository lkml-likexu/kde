
EXPORT_SYMBOL_GPL(irqchip_fwnode_ops);
EXPORT_SYMBOL_GPL(__irq_domain_alloc_fwnode);
EXPORT_SYMBOL_GPL(irq_domain_free_fwnode);
EXPORT_SYMBOL_GPL(__irq_domain_add);
EXPORT_SYMBOL_GPL(irq_domain_remove);
EXPORT_SYMBOL_GPL(irq_domain_add_simple);
EXPORT_SYMBOL_GPL(irq_domain_add_legacy);
EXPORT_SYMBOL_GPL(irq_find_matching_fwspec);
EXPORT_SYMBOL_GPL(irq_domain_check_msi_remap);
EXPORT_SYMBOL_GPL(irq_set_default_host);
EXPORT_SYMBOL_GPL(irq_domain_associate);
EXPORT_SYMBOL_GPL(irq_domain_associate_many);
EXPORT_SYMBOL_GPL(irq_create_direct_mapping);
EXPORT_SYMBOL_GPL(irq_create_mapping);
EXPORT_SYMBOL_GPL(irq_create_strict_mappings);
EXPORT_SYMBOL_GPL(irq_create_fwspec_mapping);
EXPORT_SYMBOL_GPL(irq_create_of_mapping);
EXPORT_SYMBOL_GPL(irq_dispose_mapping);
EXPORT_SYMBOL_GPL(irq_find_mapping);
EXPORT_SYMBOL_GPL(irq_domain_xlate_onecell);
EXPORT_SYMBOL_GPL(irq_domain_xlate_twocell);
EXPORT_SYMBOL_GPL(irq_domain_xlate_onetwocell);
EXPORT_SYMBOL_GPL(irq_domain_simple_ops);
EXPORT_SYMBOL_GPL(irq_domain_create_hierarchy);
EXPORT_SYMBOL_GPL(irq_domain_get_irq_data);
EXPORT_SYMBOL_GPL(irq_domain_set_hwirq_and_chip);
EXPORT_SYMBOL_GPL(irq_domain_reset_irq_data);
EXPORT_SYMBOL_GPL(irq_domain_free_irqs_common);
EXPORT_SYMBOL_GPL(irq_domain_push_irq);
EXPORT_SYMBOL_GPL(irq_domain_pop_irq);
EXPORT_SYMBOL_GPL(irq_domain_alloc_irqs_parent);
EXPORT_SYMBOL_GPL(irq_domain_free_irqs_parent);
EXPORT_SYMBOL_GPL(irq_domain_get_irq_data);
struct fwnode_handle *__irq_domain_alloc_fwnode(unsigned int type, int id, const char *name, void *data)
void irq_domain_free_fwnode(struct fwnode_handle *fwnode)
struct irq_domain *__irq_domain_add(struct fwnode_handle *fwnode, int size, irq_hw_number_t hwirq_max, int direct_max, const struct irq_domain_ops *ops, void *host_data)
void irq_domain_remove(struct irq_domain *domain)
void irq_domain_update_bus_token(struct irq_domain *domain, enum irq_domain_bus_token bus_token)
struct irq_domain *irq_domain_add_simple(struct device_node *of_node, unsigned int size, unsigned int first_irq, const struct irq_domain_ops *ops, void *host_data)
struct irq_domain *irq_domain_add_legacy(struct device_node *of_node, unsigned int size, unsigned int first_irq, irq_hw_number_t first_hwirq, const struct irq_domain_ops *ops, void *host_data)
struct irq_domain *irq_find_matching_fwspec(struct irq_fwspec *fwspec, enum irq_domain_bus_token bus_token)
bool irq_domain_check_msi_remap(void)
void irq_set_default_host(struct irq_domain *domain)
static void irq_domain_clear_mapping(struct irq_domain *domain, irq_hw_number_t hwirq)
static void irq_domain_set_mapping(struct irq_domain *domain, irq_hw_number_t hwirq, struct irq_data *irq_data)
void irq_domain_disassociate(struct irq_domain *domain, unsigned int irq)
int irq_domain_associate(struct irq_domain *domain, unsigned int virq, irq_hw_number_t hwirq)
void irq_domain_associate_many(struct irq_domain *domain, unsigned int irq_base, irq_hw_number_t hwirq_base, int count)
unsigned int irq_create_direct_mapping(struct irq_domain *domain)
unsigned int irq_create_mapping(struct irq_domain *domain, irq_hw_number_t hwirq)
int irq_create_strict_mappings(struct irq_domain *domain, unsigned int irq_base, irq_hw_number_t hwirq_base, int count)
static int irq_domain_translate(struct irq_domain *d, struct irq_fwspec *fwspec, irq_hw_number_t *hwirq, unsigned int *type)
static void of_phandle_args_to_fwspec(struct of_phandle_args *irq_data, struct irq_fwspec *fwspec)
unsigned int irq_create_fwspec_mapping(struct irq_fwspec *fwspec)
unsigned int irq_create_of_mapping(struct of_phandle_args *irq_data)
void irq_dispose_mapping(unsigned int virq)
unsigned int irq_find_mapping(struct irq_domain *domain, irq_hw_number_t hwirq)
int irq_domain_xlate_onecell(struct irq_domain *d, struct device_node *ctrlr, const u32 *intspec, unsigned int intsize, unsigned long *out_hwirq, unsigned int *out_type)
int irq_domain_xlate_twocell(struct irq_domain *d, struct device_node *ctrlr, const u32 *intspec, unsigned int intsize, irq_hw_number_t *out_hwirq, unsigned int *out_type)
int irq_domain_xlate_onetwocell(struct irq_domain *d, struct device_node *ctrlr, const u32 *intspec, unsigned int intsize, unsigned long *out_hwirq, unsigned int *out_type)
int irq_domain_alloc_descs(int virq, unsigned int cnt, irq_hw_number_t hwirq, int node, const struct cpumask *affinity)
struct irq_domain *irq_domain_create_hierarchy(struct irq_domain *parent, unsigned int flags, unsigned int size, struct fwnode_handle *fwnode, const struct irq_domain_ops *ops, void *host_data)
static void irq_domain_insert_irq(int virq)
static void irq_domain_remove_irq(int virq)
static struct irq_data *irq_domain_insert_irq_data(struct irq_domain *domain, struct irq_data *child)
static void irq_domain_free_irq_data(unsigned int virq, unsigned int nr_irqs)
static int irq_domain_alloc_irq_data(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs)
struct irq_data *irq_domain_get_irq_data(struct irq_domain *domain, unsigned int virq)
int irq_domain_set_hwirq_and_chip(struct irq_domain *domain, unsigned int virq, irq_hw_number_t hwirq, struct irq_chip *chip, void *chip_data)
void irq_domain_set_info(struct irq_domain *domain, unsigned int virq, irq_hw_number_t hwirq, struct irq_chip *chip, void *chip_data, irq_flow_handler_t handler, void *handler_data, const char *handler_name)
void irq_domain_reset_irq_data(struct irq_data *irq_data)
void irq_domain_free_irqs_common(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs)
void irq_domain_free_irqs_top(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs)
static void irq_domain_free_irqs_hierarchy(struct irq_domain *domain, unsigned int irq_base, unsigned int nr_irqs)
int irq_domain_alloc_irqs_hierarchy(struct irq_domain *domain, unsigned int irq_base, unsigned int nr_irqs, void *arg)
int __irq_domain_alloc_irqs(struct irq_domain *domain, int irq_base, unsigned int nr_irqs, int node, void *arg, bool realloc, const struct cpumask *affinity)
static void irq_domain_fix_revmap(struct irq_data *d)
int irq_domain_push_irq(struct irq_domain *domain, int virq, void *arg)
int irq_domain_pop_irq(struct irq_domain *domain, int virq)
void irq_domain_free_irqs(unsigned int virq, unsigned int nr_irqs)
int irq_domain_alloc_irqs_parent(struct irq_domain *domain, unsigned int irq_base, unsigned int nr_irqs, void *arg)
void irq_domain_free_irqs_parent(struct irq_domain *domain, unsigned int irq_base, unsigned int nr_irqs)
static void __irq_domain_deactivate_irq(struct irq_data *irq_data)
static int __irq_domain_activate_irq(struct irq_data *irqd, bool reserve)
int irq_domain_activate_irq(struct irq_data *irq_data, bool reserve)
void irq_domain_deactivate_irq(struct irq_data *irq_data)
static void irq_domain_check_hierarchy(struct irq_domain *domain)
bool irq_domain_hierarchical_is_msi_remap(struct irq_domain *domain)
bool irq_domain_hierarchical_is_msi_remap(struct irq_domain *domain)
if (irq_domain_is_msi_remap(domain)
)
return true;}return false; }struct irq_data *irq_domain_get_irq_data(struct irq_domain *domain, unsigned int virq)
void irq_domain_set_info(struct irq_domain *domain, unsigned int virq, irq_hw_number_t hwirq, struct irq_chip *chip, void *chip_data, irq_flow_handler_t handler, void *handler_data, const char *handler_name)
static void irq_domain_check_hierarchy(struct irq_domain *domain)
static void irq_domain_debug_show_one(struct seq_file *m, struct irq_domain *d, int ind)
static int irq_domain_debug_show(struct seq_file *m, void *p)
static void debugfs_add_domain_dir(struct irq_domain *d)
static void debugfs_remove_domain_dir(struct irq_domain *d)
void __init irq_domain_debugfs_init(struct dentry *root)
  32 struct irq_domain *domain
  12 unsigned int virq
  10 unsigned int nr_irqs
   9 irq_hw_number_t hwirq
   7 struct irq_domain *d
   6 unsigned int irq_base
   5 struct irq_data *irq_data
   5 int virq
   4 void *host_data
   4 void *arg
   4 struct irq_fwspec *fwspec
   4 const struct irq_domain_ops *ops
   3 void *chip_data
   3 unsigned int size
   3 unsigned int intsize
   3 unsigned int *out_type
   3 struct irq_chip *chip
   3 struct fwnode_handle *fwnode
   3 struct device_node *ctrlr
   3 const u32 *intspec
   2 void *handler_data
   2 unsigned long *out_hwirq
   2 unsigned int first_irq
   2 struct seq_file *m
   2 struct of_phandle_args *irq_data
   2 struct device_node *of_node
   2 irq_hw_number_t hwirq_base
   2 irq_flow_handler_t handler
   2 irq_domain_get_irq_data
   2 int node
   2 int count
   2 enum irq_domain_bus_token bus_token
   2 const struct cpumask *affinity
   2 const char *handler_name
   2 bool reserve
   1 void *p
   1 void *data
   1 void
   1 unsigned int type
   1 unsigned int irq
   1 unsigned int flags
   1 unsigned int cnt
   1 unsigned int *type
   1 struct irq_domain *parent
   1 struct irq_data *irqd
   1 struct irq_data *d
   1 struct irq_data *child
   1 struct dentry *root
   1 irqchip_fwnode_ops
   1 irq_set_default_host
   1 irq_hw_number_t hwirq_max
   1 irq_hw_number_t first_hwirq
   1 irq_hw_number_t *out_hwirq
   1 irq_hw_number_t *hwirq
   1 irq_find_matching_fwspec
   1 irq_find_mapping
   1 irq_domain_xlate_twocell
   1 irq_domain_xlate_onetwocell
   1 irq_domain_xlate_onecell
   1 irq_domain_simple_ops
   1 irq_domain_set_hwirq_and_chip
   1 irq_domain_reset_irq_data
   1 irq_domain_remove
   1 irq_domain_push_irq
   1 irq_domain_pop_irq
   1 irq_domain_is_msi_remapdomain
   1 irq_domain_free_irqs_parent
   1 irq_domain_free_irqs_common
   1 irq_domain_free_fwnode
   1 irq_domain_create_hierarchy
   1 irq_domain_check_msi_remap
   1 irq_domain_associate_many
   1 irq_domain_associate
   1 irq_domain_alloc_irqs_parent
   1 irq_domain_add_simple
   1 irq_domain_add_legacy
   1 irq_dispose_mapping
   1 irq_create_strict_mappings
   1 irq_create_of_mapping
   1 irq_create_mapping
   1 irq_create_fwspec_mapping
   1 irq_create_direct_mapping
   1 int size
   1 int irq_base
   1 int ind
   1 int id
   1 int direct_max
   1 const char *name
   1 bool realloc
   1 __irq_domain_alloc_fwnode
   1 __irq_domain_add
