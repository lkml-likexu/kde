
EXPORT_SYMBOL_GPL(iommu_get_group_resv_regions);
EXPORT_SYMBOL_GPL(iommu_group_alloc);
EXPORT_SYMBOL_GPL(iommu_group_get_by_id);
EXPORT_SYMBOL_GPL(iommu_group_get_iommudata);
EXPORT_SYMBOL_GPL(iommu_group_set_iommudata);
EXPORT_SYMBOL_GPL(iommu_group_set_name);
EXPORT_SYMBOL_GPL(iommu_group_add_device);
EXPORT_SYMBOL_GPL(iommu_group_remove_device);
EXPORT_SYMBOL_GPL(iommu_group_for_each_dev);
EXPORT_SYMBOL_GPL(iommu_group_get);
EXPORT_SYMBOL_GPL(iommu_group_put);
EXPORT_SYMBOL_GPL(iommu_group_register_notifier);
EXPORT_SYMBOL_GPL(iommu_group_unregister_notifier);
EXPORT_SYMBOL_GPL(iommu_group_id);
EXPORT_SYMBOL_GPL(bus_set_iommu);
EXPORT_SYMBOL_GPL(iommu_present);
EXPORT_SYMBOL_GPL(iommu_capable);
EXPORT_SYMBOL_GPL(iommu_set_fault_handler);
EXPORT_SYMBOL_GPL(iommu_domain_alloc);
EXPORT_SYMBOL_GPL(iommu_domain_free);
EXPORT_SYMBOL_GPL(iommu_attach_device);
EXPORT_SYMBOL_GPL(iommu_detach_device);
EXPORT_SYMBOL_GPL(iommu_get_domain_for_dev);
EXPORT_SYMBOL_GPL(iommu_attach_group);
EXPORT_SYMBOL_GPL(iommu_detach_group);
EXPORT_SYMBOL_GPL(iommu_iova_to_phys);
EXPORT_SYMBOL_GPL(iommu_map);
EXPORT_SYMBOL_GPL(iommu_unmap);
EXPORT_SYMBOL_GPL(iommu_unmap_fast);
EXPORT_SYMBOL_GPL(iommu_map_sg);
EXPORT_SYMBOL_GPL(iommu_domain_window_enable);
EXPORT_SYMBOL_GPL(iommu_domain_window_disable);
EXPORT_SYMBOL_GPL(report_iommu_fault);
EXPORT_SYMBOL_GPL(iommu_domain_get_attr);
EXPORT_SYMBOL_GPL(iommu_domain_set_attr);
EXPORT_SYMBOL_GPL(iommu_fwspec_init);
EXPORT_SYMBOL_GPL(iommu_fwspec_free);
EXPORT_SYMBOL_GPL(iommu_fwspec_add_ids);
int iommu_device_register(struct iommu_device *iommu)
void iommu_device_unregister(struct iommu_device *iommu)
static int __init iommu_set_def_domain_type(char *str)
static int __init iommu_dma_setup(char *str)
static ssize_t iommu_group_attr_show(struct kobject *kobj, struct attribute *__attr, char *buf)
static ssize_t iommu_group_attr_store(struct kobject *kobj, struct attribute *__attr, const char *buf, size_t count)
static int iommu_group_create_file(struct iommu_group *group, struct iommu_group_attribute *attr)
static void iommu_group_remove_file(struct iommu_group *group, struct iommu_group_attribute *attr)
static ssize_t iommu_group_show_name(struct iommu_group *group, char *buf)
static int iommu_insert_resv_region(struct iommu_resv_region *new, struct list_head *regions)
static int iommu_insert_device_resv_regions(struct list_head *dev_resv_regions, struct list_head *group_resv_regions)
int iommu_get_group_resv_regions(struct iommu_group *group, struct list_head *head)
static ssize_t iommu_group_show_resv_regions(struct iommu_group *group, char *buf)
static ssize_t iommu_group_show_type(struct iommu_group *group, char *buf)
static void iommu_group_release(struct kobject *kobj)
struct iommu_group *iommu_group_alloc(void)
struct iommu_group *iommu_group_get_by_id(int id)
void *iommu_group_get_iommudata(struct iommu_group *group)
void iommu_group_set_iommudata(struct iommu_group *group, void *iommu_data, void (*release)
(void *iommu_data)
)
int iommu_group_set_name(struct iommu_group *group, const char *name)
static int iommu_group_create_direct_mappings(struct iommu_group *group, struct device *dev)
int iommu_group_add_device(struct iommu_group *group, struct device *dev)
void iommu_group_remove_device(struct device *dev)
static int iommu_group_device_count(struct iommu_group *group)
static int __iommu_group_for_each_dev(struct iommu_group *group, void *data, int (*fn)
(struct device *, void *)
)
int iommu_group_for_each_dev(struct iommu_group *group, void *data, int (*fn)
(struct device *, void *)
)
struct iommu_group *iommu_group_get(struct device *dev)
struct iommu_group *iommu_group_ref_get(struct iommu_group *group)
void iommu_group_put(struct iommu_group *group)
int iommu_group_register_notifier(struct iommu_group *group, struct notifier_block *nb)
int iommu_group_unregister_notifier(struct iommu_group *group, struct notifier_block *nb)
int iommu_group_id(struct iommu_group *group)
static struct iommu_group *get_pci_function_alias_group(struct pci_dev *pdev, unsigned long *devfns)
static struct iommu_group *get_pci_alias_group(struct pci_dev *pdev, unsigned long *devfns)
static int get_pci_alias_or_group(struct pci_dev *pdev, u16 alias, void *opaque)
struct iommu_group *generic_device_group(struct device *dev)
struct iommu_group *pci_device_group(struct device *dev)
struct iommu_group *fsl_mc_device_group(struct device *dev)
struct iommu_group *iommu_group_get_for_dev(struct device *dev)
struct iommu_domain *iommu_group_default_domain(struct iommu_group *group)
static int add_iommu_group(struct device *dev, void *data)
static int remove_iommu_group(struct device *dev, void *data)
static int iommu_bus_notifier(struct notifier_block *nb, unsigned long action, void *data)
static int iommu_bus_init(struct bus_type *bus, const struct iommu_ops *ops)
int bus_set_iommu(struct bus_type *bus, const struct iommu_ops *ops)
bool iommu_present(struct bus_type *bus)
bool iommu_capable(struct bus_type *bus, enum iommu_cap cap)
void iommu_set_fault_handler(struct iommu_domain *domain, iommu_fault_handler_t handler, void *token)
static struct iommu_domain *__iommu_domain_alloc(struct bus_type *bus, unsigned type)
struct iommu_domain *iommu_domain_alloc(struct bus_type *bus)
void iommu_domain_free(struct iommu_domain *domain)
static int __iommu_attach_device(struct iommu_domain *domain, struct device *dev)
int iommu_attach_device(struct iommu_domain *domain, struct device *dev)
static void __iommu_detach_device(struct iommu_domain *domain, struct device *dev)
void iommu_detach_device(struct iommu_domain *domain, struct device *dev)
struct iommu_domain *iommu_get_domain_for_dev(struct device *dev)
struct iommu_domain *iommu_get_dma_domain(struct device *dev)
static int iommu_group_do_attach_device(struct device *dev, void *data)
static int __iommu_attach_group(struct iommu_domain *domain, struct iommu_group *group)
int iommu_attach_group(struct iommu_domain *domain, struct iommu_group *group)
static int iommu_group_do_detach_device(struct device *dev, void *data)
static void __iommu_detach_group(struct iommu_domain *domain, struct iommu_group *group)
void iommu_detach_group(struct iommu_domain *domain, struct iommu_group *group)
phys_addr_t iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
static size_t iommu_pgsize(struct iommu_domain *domain, unsigned long addr_merge, size_t size)
int iommu_map(struct iommu_domain *domain, unsigned long iova, phys_addr_t paddr, size_t size, int prot)
static size_t __iommu_unmap(struct iommu_domain *domain, unsigned long iova, size_t size, bool sync)
size_t iommu_unmap(struct iommu_domain *domain, unsigned long iova, size_t size)
size_t iommu_unmap_fast(struct iommu_domain *domain, unsigned long iova, size_t size)
size_t iommu_map_sg(struct iommu_domain *domain, unsigned long iova, struct scatterlist *sg, unsigned int nents, int prot)
int iommu_domain_window_enable(struct iommu_domain *domain, u32 wnd_nr, phys_addr_t paddr, u64 size, int prot)
void iommu_domain_window_disable(struct iommu_domain *domain, u32 wnd_nr)
int report_iommu_fault(struct iommu_domain *domain, struct device *dev, unsigned long iova, int flags)
static int __init iommu_init(void)
int iommu_domain_get_attr(struct iommu_domain *domain, enum iommu_attr attr, void *data)
int iommu_domain_set_attr(struct iommu_domain *domain, enum iommu_attr attr, void *data)
void iommu_get_resv_regions(struct device *dev, struct list_head *list)
void iommu_put_resv_regions(struct device *dev, struct list_head *list)
struct iommu_resv_region *iommu_alloc_resv_region(phys_addr_t start, size_t length, int prot, enum iommu_resv_type type)
int iommu_request_dm_for_dev(struct device *dev)
const struct iommu_ops *iommu_ops_from_fwnode(struct fwnode_handle *fwnode)
int iommu_fwspec_init(struct device *dev, struct fwnode_handle *iommu_fwnode, const struct iommu_ops *ops)
void iommu_fwspec_free(struct device *dev)
int iommu_fwspec_add_ids(struct device *dev, u32 *ids, int num_ids)
  25 struct device *dev
  24 struct iommu_group *group
  22 struct iommu_domain *domain
   9 void *data
   6 unsigned long iova
   6 struct bus_type *bus
   5 size_t size
   4 int prot
   4 char *buf
   3 struct pci_dev *pdev
   3 struct notifier_block *nb
   3 struct kobject *kobj
   3 const struct iommu_ops *ops
   2 void *iommu_data
   2 void *
   2 void
   2 unsigned long *devfns
   2 u32 wnd_nr
   2 struct list_head *list
   2 struct iommu_group_attribute *attr
   2 struct iommu_device *iommu
   2 struct device *
   2 struct attribute *__attr
   2 phys_addr_t paddr
   2 int *fn
   2 enum iommu_attr attr
   2 char *str
   1 void *token
   1 void *release
   1 void *opaque
   1 unsigned type
   1 unsigned long addr_merge
   1 unsigned long action
   1 unsigned int nents
   1 u64 size
   1 u32 *ids
   1 u16 alias
   1 struct scatterlist *sg
   1 struct list_head *regions
   1 struct list_head *head
   1 struct list_head *group_resv_regions
   1 struct list_head *dev_resv_regions
   1 struct iommu_resv_region *new
   1 struct fwnode_handle *iommu_fwnode
   1 struct fwnode_handle *fwnode
   1 size_t length
   1 size_t count
   1 report_iommu_fault
   1 phys_addr_t start
   1 iommu_unmap_fast
   1 iommu_unmap
   1 iommu_set_fault_handler
   1 iommu_present
   1 iommu_map_sg
   1 iommu_map
   1 iommu_iova_to_phys
   1 iommu_group_unregister_notifier
   1 iommu_group_set_name
   1 iommu_group_set_iommudata
   1 iommu_group_remove_device
   1 iommu_group_register_notifier
   1 iommu_group_put
   1 iommu_group_id
   1 iommu_group_get_iommudata
   1 iommu_group_get_by_id
   1 iommu_group_get
   1 iommu_group_for_each_dev
   1 iommu_group_alloc
   1 iommu_group_add_device
   1 iommu_get_group_resv_regions
   1 iommu_get_domain_for_dev
   1 iommu_fwspec_init
   1 iommu_fwspec_free
   1 iommu_fwspec_add_ids
   1 iommu_fault_handler_t handler
   1 iommu_domain_window_enable
   1 iommu_domain_window_disable
   1 iommu_domain_set_attr
   1 iommu_domain_get_attr
   1 iommu_domain_free
   1 iommu_domain_alloc
   1 iommu_detach_group
   1 iommu_detach_device
   1 iommu_capable
   1 iommu_attach_group
   1 iommu_attach_device
   1 int num_ids
   1 int id
   1 int flags
   1 enum iommu_resv_type type
   1 enum iommu_cap cap
   1 dma_addr_t iova
   1 const char *name
   1 const char *buf
   1 bus_set_iommu
   1 bool sync
