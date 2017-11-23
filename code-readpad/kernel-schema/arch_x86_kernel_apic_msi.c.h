
EXPORT_SYMBOL_GPL(pci_msi_prepare);
EXPORT_SYMBOL_GPL(pci_msi_set_desc);
static void irq_msi_compose_msg(struct irq_data *data, struct msi_msg *msg)
int native_setup_msi_irqs(struct pci_dev *dev, int nvec, int type)
void native_teardown_msi_irq(unsigned int irq)
static irq_hw_number_t pci_msi_get_hwirq(struct msi_domain_info *info, msi_alloc_info_t *arg)
int pci_msi_prepare(struct irq_domain *domain, struct device *dev, int nvec, msi_alloc_info_t *arg)
void pci_msi_set_desc(msi_alloc_info_t *arg, struct msi_desc *desc)
void __init arch_init_msi_domain(struct irq_domain *parent)
struct irq_domain *arch_create_remap_msi_irq_domain(struct irq_domain *parent, const char *name, int id)
static void dmar_msi_write_msg(struct irq_data *data, struct msi_msg *msg)
static irq_hw_number_t dmar_msi_get_hwirq(struct msi_domain_info *info, msi_alloc_info_t *arg)
static int dmar_msi_init(struct irq_domain *domain, struct msi_domain_info *info, unsigned int virq, irq_hw_number_t hwirq, msi_alloc_info_t *arg)
static struct irq_domain *dmar_get_irq_domain(void)
int dmar_alloc_hwirq(int id, int node, void *arg)
void dmar_free_hwirq(int irq)
static inline int hpet_dev_id(struct irq_domain *domain)
static void hpet_msi_write_msg(struct irq_data *data, struct msi_msg *msg)
static irq_hw_number_t hpet_msi_get_hwirq(struct msi_domain_info *info, msi_alloc_info_t *arg)
static int hpet_msi_init(struct irq_domain *domain, struct msi_domain_info *info, unsigned int virq, irq_hw_number_t hwirq, msi_alloc_info_t *arg)
static void hpet_msi_free(struct irq_domain *domain, struct msi_domain_info *info, unsigned int virq)
struct irq_domain *hpet_create_irq_domain(int hpet_id)
int hpet_assign_irq(struct irq_domain *domain, struct hpet_dev *dev, int dev_num)
   7 msi_alloc_info_t *arg
   6 struct msi_domain_info *info
   6 struct irq_domain *domain
   3 unsigned int virq
   3 struct msi_msg *msg
   3 struct irq_data *data
   2 struct irq_domain *parent
   2 irq_hw_number_t hwirq
   2 int nvec
   2 int id
   1 void *arg
   1 void
   1 unsigned int irq
   1 struct pci_dev *dev
   1 struct msi_desc *desc
   1 struct hpet_dev *dev
   1 struct device *dev
   1 pci_msi_set_desc
   1 pci_msi_prepare
   1 int type
   1 int node
   1 int irq
   1 int hpet_id
   1 int dev_num
   1 const char *name
