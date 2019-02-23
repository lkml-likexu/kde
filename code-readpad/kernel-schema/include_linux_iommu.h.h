
\n
static inline void iommu_device_set_ops(struct iommu_device *iommu, const struct iommu_ops *ops)
static inline void iommu_device_set_fwnode(struct iommu_device *iommu, struct fwnode_handle *fwnode)
static inline struct iommu_device *dev_to_iommu_device(struct device *dev)
static inline void iommu_flush_tlb_all(struct iommu_domain *domain)
static inline void iommu_tlb_range_add(struct iommu_domain *domain, unsigned long iova, size_t size)
static inline void iommu_tlb_sync(struct iommu_domain *domain)
static inline struct iommu_fwspec *dev_iommu_fwspec_get(struct device *dev)
static inline void dev_iommu_fwspec_set(struct device *dev, struct iommu_fwspec *fwspec)
static inline bool iommu_present(struct bus_type *bus)
static inline bool iommu_capable(struct bus_type *bus, enum iommu_cap cap)
static inline struct iommu_domain *iommu_domain_alloc(struct bus_type *bus)
static inline struct iommu_group *iommu_group_get_by_id(int id)
static inline void iommu_domain_free(struct iommu_domain *domain)
static inline int iommu_attach_device(struct iommu_domain *domain, struct device *dev)
static inline void iommu_detach_device(struct iommu_domain *domain, struct device *dev)
static inline struct iommu_domain *iommu_get_domain_for_dev(struct device *dev)
static inline int iommu_map(struct iommu_domain *domain, unsigned long iova, phys_addr_t paddr, size_t size, int prot)
static inline size_t iommu_unmap(struct iommu_domain *domain, unsigned long iova, size_t size)
static inline size_t iommu_unmap_fast(struct iommu_domain *domain, unsigned long iova, int gfp_order)
static inline size_t iommu_map_sg(struct iommu_domain *domain, unsigned long iova, struct scatterlist *sg, unsigned int nents, int prot)
static inline void iommu_flush_tlb_all(struct iommu_domain *domain)
static inline void iommu_tlb_range_add(struct iommu_domain *domain, unsigned long iova, size_t size)
static inline void iommu_tlb_sync(struct iommu_domain *domain)
static inline int iommu_domain_window_enable(struct iommu_domain *domain, u32 wnd_nr, phys_addr_t paddr, u64 size, int prot)
static inline void iommu_domain_window_disable(struct iommu_domain *domain, u32 wnd_nr)
static inline phys_addr_t iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
static inline void iommu_set_fault_handler(struct iommu_domain *domain, iommu_fault_handler_t handler, void *token)
static inline void iommu_get_resv_regions(struct device *dev, struct list_head *list)
static inline void iommu_put_resv_regions(struct device *dev, struct list_head *list)
static inline int iommu_get_group_resv_regions(struct iommu_group *group, struct list_head *head)
static inline int iommu_request_dm_for_dev(struct device *dev)
static inline int iommu_attach_group(struct iommu_domain *domain, struct iommu_group *group)
static inline void iommu_detach_group(struct iommu_domain *domain, struct iommu_group *group)
static inline struct iommu_group *iommu_group_alloc(void)
static inline void *iommu_group_get_iommudata(struct iommu_group *group)
static inline void iommu_group_set_iommudata(struct iommu_group *group, void *iommu_data, void (*release)
(void *iommu_data)
)
static inline int iommu_group_set_name(struct iommu_group *group, const char *name)
static inline int iommu_group_add_device(struct iommu_group *group, struct device *dev)
static inline void iommu_group_remove_device(struct device *dev)
static inline int iommu_group_for_each_dev(struct iommu_group *group, void *data, int (*fn)
(struct device *, void *)
)
static inline struct iommu_group *iommu_group_get(struct device *dev)
static inline void iommu_group_put(struct iommu_group *group)
static inline int iommu_group_register_notifier(struct iommu_group *group, struct notifier_block *nb)
static inline int iommu_group_unregister_notifier(struct iommu_group *group, struct notifier_block *nb)
static inline int iommu_group_id(struct iommu_group *group)
static inline int iommu_domain_get_attr(struct iommu_domain *domain, enum iommu_attr attr, void *data)
static inline int iommu_domain_set_attr(struct iommu_domain *domain, enum iommu_attr attr, void *data)
static inline intiommu_device_register(struct iommu_device *iommu)
static inline void iommu_device_set_ops(struct iommu_device *iommu, const struct iommu_ops *ops)
static inline void iommu_device_set_fwnode(struct iommu_device *iommu, struct fwnode_handle *fwnode)
static inline struct iommu_device *dev_to_iommu_device(struct device *dev)
static inline void iommu_device_unregister(struct iommu_device *iommu)
static inline intiommu_device_sysfs_add(struct iommu_device *iommu, struct device *parent, const struct attribute_group **groups, const char *fmt, ...)
static inline void iommu_device_sysfs_remove(struct iommu_device *iommu)
static inline int iommu_device_link(struct device *dev, struct device *link)
static inline void iommu_device_unlink(struct device *dev, struct device *link)
static inline int iommu_fwspec_init(struct device *dev, struct fwnode_handle *iommu_fwnode, const struct iommu_ops *ops)
static inline void iommu_fwspec_free(struct device *dev)
static inline int iommu_fwspec_add_ids(struct device *dev, u32 *ids, int num_ids)
static inline const struct iommu_ops *iommu_ops_from_fwnode(struct fwnode_handle *fwnode)
\n
     21 struct iommu_domain *domain
     18 struct device *dev
     12 struct iommu_group *group
      8 struct iommu_device *iommu
      6 unsigned long iova
      4 size_t size
      3 void *data
      3 struct fwnode_handle *fwnode
      3 struct bus_type *bus
      3 int prot
      3 const struct iommu_ops *ops
      2 void *iommu_data
      2 u32 wnd_nr
      2 struct notifier_block *nb
      2 struct list_head *list
      2 struct device *link
      2 phys_addr_t paddr
      2 enum iommu_attr attr
      1 void *token
      1 void *release
      1 void *
      1 void
      1 unsigned int nents
      1 u64 size
      1 u32 *ids
      1 struct scatterlist *sg
      1 struct list_head *head
      1 struct iommu_fwspec *fwspec
      1 struct fwnode_handle *iommu_fwnode
      1 struct device *parent
      1 struct device *
      1 iommu_fault_handler_t handler
      1 int num_ids
      1 int id
      1 int gfp_order
      1 int *fn
      1 enum iommu_cap cap
      1 dma_addr_t iova
      1 const struct attribute_group **groups
      1 const char *name
      1 const char *fmt
      1 ...
