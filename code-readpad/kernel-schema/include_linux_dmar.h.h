
\n
static inline bool dmar_rcu_check(void)
static inline int dmar_res_noop(struct acpi_dmar_header *hdr, void *arg)
static inline int dmar_iommu_notify_scope_dev(struct dmar_pci_notify_info *info)
static inline int dmar_iommu_hotplug(struct dmar_drhd_unit *dmaru, bool insert)
extern int dmar_ir_hotplug(struct dmar_drhd_unit *dmaru, bool insert)
; static inline int dmar_ir_hotplug(struct dmar_drhd_unit *dmaru, bool insert)
static inline int dmar_device_add(void *handle)
static inline int dmar_device_remove(void *handle)
static inline bool dmar_platform_optin(void)
static inline void dmar_copy_shared_irte(struct irte *dst, struct irte *src)
\n
      3 struct dmar_drhd_unit *dmaru
      3 bool insert
      2 void *handle
      2 void
      1 void *arg
      1 struct irte *src
      1 struct irte *dst
      1 struct dmar_pci_notify_info *info
      1 struct acpi_dmar_header *hdr
