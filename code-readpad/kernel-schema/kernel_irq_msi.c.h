
EXPORT_SYMBOL_GPL(get_cached_msi_msg);
\n
struct msi_desc *alloc_msi_entry(struct device *dev, int nvec, const struct irq_affinity_desc *affinity)
void free_msi_entry(struct msi_desc *entry)
void __get_cached_msi_msg(struct msi_desc *entry, struct msi_msg *msg)
void get_cached_msi_msg(unsigned int irq, struct msi_msg *msg)
static inline void irq_chip_write_msi_msg(struct irq_data *data, struct msi_msg *msg)
static void msi_check_level(struct irq_domain *domain, struct msi_msg *msg)
int msi_domain_set_affinity(struct irq_data *irq_data, const struct cpumask *mask, bool force)
static int msi_domain_activate(struct irq_domain *domain, struct irq_data *irq_data, bool early)
static void msi_domain_deactivate(struct irq_domain *domain, struct irq_data *irq_data)
static int msi_domain_alloc(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs, void *arg)
static void msi_domain_free(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs)
static irq_hw_number_t msi_domain_ops_get_hwirq(struct msi_domain_info *info, msi_alloc_info_t *arg)
static int msi_domain_ops_prepare(struct irq_domain *domain, struct device *dev, int nvec, msi_alloc_info_t *arg)
static void msi_domain_ops_set_desc(msi_alloc_info_t *arg, struct msi_desc *desc)
static int msi_domain_ops_init(struct irq_domain *domain, struct msi_domain_info *info, unsigned int virq, irq_hw_number_t hwirq, msi_alloc_info_t *arg)
static int msi_domain_ops_check(struct irq_domain *domain, struct msi_domain_info *info, struct device *dev)
static void msi_domain_update_dom_ops(struct msi_domain_info *info)
static void msi_domain_update_chip_ops(struct msi_domain_info *info)
struct irq_domain *msi_create_irq_domain(struct fwnode_handle *fwnode, struct msi_domain_info *info, struct irq_domain *parent)
int msi_domain_prepare_irqs(struct irq_domain *domain, struct device *dev, int nvec, msi_alloc_info_t *arg)
int msi_domain_populate_irqs(struct irq_domain *domain, struct device *dev, int virq, int nvec, msi_alloc_info_t *arg)
static bool msi_check_reservation_mode(struct irq_domain *domain, struct msi_domain_info *info, struct device *dev)
int msi_domain_alloc_irqs(struct irq_domain *domain, struct device *dev, int nvec)
void msi_domain_free_irqs(struct irq_domain *domain, struct device *dev)
struct msi_domain_info *msi_get_domain_info(struct irq_domain *domain)
\n
     14 struct irq_domain *domain
      8 struct device *dev
      7 struct msi_domain_info *info
      6 msi_alloc_info_t *arg
      5 int nvec
      4 struct msi_msg *msg
      3 unsigned int virq
      3 struct irq_data *irq_data
      2 unsigned int nr_irqs
      2 struct msi_desc *entry
      1 void *arg
      1 unsigned int irq
      1 struct msi_desc *desc
      1 struct irq_domain *parent
      1 struct irq_data *data
      1 struct fwnode_handle *fwnode
      1 irq_hw_number_t hwirq
      1 int virq
      1 get_cached_msi_msg
      1 const struct irq_affinity_desc *affinity
      1 const struct cpumask *mask
      1 bool force
      1 bool early
