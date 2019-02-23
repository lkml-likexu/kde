
\n
static inline struct device_node *irq_domain_get_of_node(struct irq_domain *d)
static inline struct fwnode_handle *irq_domain_alloc_named_fwnode(const char *name)
static inline struct fwnode_handle *irq_domain_alloc_named_id_fwnode(const char *name, int id)
static inline struct fwnode_handle *irq_domain_alloc_fwnode(void *data)
static inline struct fwnode_handle *of_node_to_fwnode(struct device_node *node)
static inline bool is_fwnode_irqchip(struct fwnode_handle *fwnode)
static inline struct irq_domain *irq_find_matching_fwnode(struct fwnode_handle *fwnode, enum irq_domain_bus_token bus_token)
static inline struct irq_domain *irq_find_matching_host(struct device_node *node, enum irq_domain_bus_token bus_token)
static inline struct irq_domain *irq_find_host(struct device_node *node)
static inline struct irq_domain *irq_domain_add_linear(struct device_node *of_node, unsigned int size, const struct irq_domain_ops *ops, void *host_data)
static inline struct irq_domain *irq_domain_add_linear(struct device_node *of_node, unsigned int size, const struct irq_domain_ops *ops, void *host_data)
return __irq_domain_add(of_node_to_fwnode(of_node)
, size, size, 0, ops, host_data)
; } static inline struct irq_domain *irq_domain_add_nomap(struct device_node *of_node, unsigned int max_irq, const struct irq_domain_ops *ops, void *host_data)
static inline struct irq_domain *irq_domain_add_linear(struct device_node *of_node, unsigned int size, const struct irq_domain_ops *ops, void *host_data)
return __irq_domain_add(of_node_to_fwnode(of_node)
, size, size, 0, ops, host_data)
; } static inline struct irq_domain *irq_domain_add_nomap(struct device_node *of_node, unsigned int max_irq, const struct irq_domain_ops *ops, void *host_data)
return __irq_domain_add(of_node_to_fwnode(of_node)
, 0, max_irq, max_irq, ops, host_data)
; } static inline struct irq_domain *irq_domain_add_legacy_isa( struct device_node *of_node, const struct irq_domain_ops *ops, void *host_data)
static inline struct irq_domain *irq_domain_add_linear(struct device_node *of_node, unsigned int size, const struct irq_domain_ops *ops, void *host_data)
return __irq_domain_add(of_node_to_fwnode(of_node)
, size, size, 0, ops, host_data)
; } static inline struct irq_domain *irq_domain_add_nomap(struct device_node *of_node, unsigned int max_irq, const struct irq_domain_ops *ops, void *host_data)
return __irq_domain_add(of_node_to_fwnode(of_node)
, 0, max_irq, max_irq, ops, host_data)
; } static inline struct irq_domain *irq_domain_add_legacy_isa( struct device_node *of_node, const struct irq_domain_ops *ops, void *host_data)
return irq_domain_add_legacy(of_node, NUM_ISA_INTERRUPTS, 0, 0, ops, host_data)
; } static inline struct irq_domain *irq_domain_add_tree(struct device_node *of_node, const struct irq_domain_ops *ops, void *host_data)
static inline struct irq_domain *irq_domain_create_linear(struct fwnode_handle *fwnode, unsigned int size, const struct irq_domain_ops *ops, void *host_data)
static inline struct irq_domain *irq_domain_create_tree(struct fwnode_handle *fwnode, const struct irq_domain_ops *ops, void *host_data)
static inline unsigned int irq_linear_revmap(struct irq_domain *domain, irq_hw_number_t hwirq)
static inline int irq_create_identity_mapping(struct irq_domain *host, irq_hw_number_t hwirq)
static inline struct irq_domain *irq_domain_add_hierarchy(struct irq_domain *parent, unsigned int flags, unsigned int size, struct device_node *node, const struct irq_domain_ops *ops, void *host_data)
static inline int irq_domain_alloc_irqs(struct irq_domain *domain, unsigned int nr_irqs, int node, void *arg)
static inline bool irq_domain_is_hierarchy(struct irq_domain *domain)
static inline bool irq_domain_is_ipi(struct irq_domain *domain)
static inline bool irq_domain_is_ipi_per_cpu(struct irq_domain *domain)
static inline bool irq_domain_is_ipi_single(struct irq_domain *domain)
static inline bool irq_domain_is_msi(struct irq_domain *domain)
static inline bool irq_domain_is_msi_remap(struct irq_domain *domain)
static inline int irq_domain_alloc_irqs(struct irq_domain *domain, unsigned int nr_irqs, int node, void *arg)
static inline bool irq_domain_is_hierarchy(struct irq_domain *domain)
static inline bool irq_domain_is_ipi(struct irq_domain *domain)
static inline bool irq_domain_is_ipi_per_cpu(struct irq_domain *domain)
static inline bool irq_domain_is_ipi_single(struct irq_domain *domain)
static inline bool irq_domain_is_msi(struct irq_domain *domain)
static inline bool irq_domain_is_msi_remap(struct irq_domain *domain)
static inline bool irq_domain_hierarchical_is_msi_remap(struct irq_domain *domain)
static inline struct irq_domain *irq_find_matching_fwnode(struct fwnode_handle *fwnode, enum irq_domain_bus_token bus_token)
static inline struct irq_domain *irq_find_matching_fwnode(struct fwnode_handle *fwnode, enum irq_domain_bus_token bus_token)
return NULL; } static inline bool irq_domain_check_msi_remap(void)
\n
     16 struct irq_domain *domain
     13 void *host_data
     13 const struct irq_domain_ops *ops
     10 struct device_node *of_node
      6 unsigned int size
      6 struct fwnode_handle *fwnode
      5 of_node_to_fwnodeof_node
      4 struct device_node *node
      4 enum irq_domain_bus_token bus_token
      3 unsigned int max_irq
      2 void *arg
      2 unsigned int nr_irqs
      2 irq_hw_number_t hwirq
      2 int node
      2 const char *name
      2 0
      1 void *data
      1 void
      1 unsigned int flags
      1 struct irq_domain *parent
      1 struct irq_domain *host
      1 struct irq_domain *d
      1 ops
      1 of_node
      1 NUM_ISA_INTERRUPTS
      1 int id
      1 host_data
