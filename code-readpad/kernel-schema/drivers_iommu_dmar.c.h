
EXPORT_SYMBOL_GPL(dmar_platform_optin);
\n
static void dmar_register_drhd_unit(struct dmar_drhd_unit *drhd)
void *dmar_alloc_dev_scope(void *start, void *end, int *cnt)
void dmar_free_dev_scope(struct dmar_dev_scope **devices, int *cnt)
static struct dmar_pci_notify_info * dmar_alloc_pci_notify_info(struct pci_dev *dev, unsigned long event)
static inline void dmar_free_pci_notify_info(struct dmar_pci_notify_info *info)
static bool dmar_match_pci_path(struct dmar_pci_notify_info *info, int bus, struct acpi_dmar_pci_path *path, int count)
int dmar_insert_dev_scope(struct dmar_pci_notify_info *info, void *start, void*end, u16 segment, struct dmar_dev_scope *devices, int devices_cnt)
int dmar_remove_dev_scope(struct dmar_pci_notify_info *info, u16 segment, struct dmar_dev_scope *devices, int count)
static int dmar_pci_bus_add_dev(struct dmar_pci_notify_info *info)
static voiddmar_pci_bus_del_dev(struct dmar_pci_notify_info *info)
static int dmar_pci_bus_notifier(struct notifier_block *nb, unsigned long action, void *data)
static struct dmar_drhd_unit * dmar_find_dmaru(struct acpi_dmar_hardware_unit *drhd)
static int dmar_parse_one_drhd(struct acpi_dmar_header *header, void *arg)
static void dmar_free_drhd(struct dmar_drhd_unit *dmaru)
static int __init dmar_parse_one_andd(struct acpi_dmar_header *header, void *arg)
static int dmar_parse_one_rhsa(struct acpi_dmar_header *header, void *arg)
static void dmar_table_print_dmar_entry(struct acpi_dmar_header *header)
static int __init dmar_table_detect(void)
static int dmar_walk_remapping_entries(struct acpi_dmar_header *start, size_t len, struct dmar_res_callback *cb)
static inline int dmar_walk_dmar_table(struct acpi_table_dmar *dmar, struct dmar_res_callback *cb)
static int __init parse_dmar_table(void)
static int dmar_pci_device_match(struct dmar_dev_scope devices[], int cnt, struct pci_dev *dev)
struct dmar_drhd_unit * dmar_find_matched_drhd_unit(struct pci_dev *dev)
static void __init dmar_acpi_insert_dev_scope(u8 device_number, struct acpi_device *adev)
static int __init dmar_acpi_dev_scope_init(void)
int __init dmar_dev_scope_init(void)
void __init dmar_register_bus_notifier(void)
int __init dmar_table_init(void)
static void warn_invalid_dmar(u64 addr, const char *message)
static int __ref dmar_validate_one_drhd(struct acpi_dmar_header *entry, void *arg)
int __init detect_intel_iommu(void)
static void unmap_iommu(struct intel_iommu *iommu)
static int map_iommu(struct intel_iommu *iommu, u64 phys_addr)
static int dmar_alloc_seq_id(struct intel_iommu *iommu)
static void dmar_free_seq_id(struct intel_iommu *iommu)
static int alloc_iommu(struct dmar_drhd_unit *drhd)
static void free_iommu(struct intel_iommu *iommu)
static inline void reclaim_free_desc(struct q_inval *qi)
static int qi_check_fault(struct intel_iommu *iommu, int index)
int qi_submit_sync(struct qi_desc *desc, struct intel_iommu *iommu)
void qi_global_iec(struct intel_iommu *iommu)
void qi_flush_context(struct intel_iommu *iommu, u16 did, u16 sid, u8 fm, u64 type)
void qi_flush_iotlb(struct intel_iommu *iommu, u16 did, u64 addr, unsigned int size_order, u64 type)
void qi_flush_dev_iotlb(struct intel_iommu *iommu, u16 sid, u16 pfsid, u16 qdep, u64 addr, unsigned mask)
void dmar_disable_qi(struct intel_iommu *iommu)
static void __dmar_enable_qi(struct intel_iommu *iommu)
int dmar_enable_qi(struct intel_iommu *iommu)
static const char *dma_remap_fault_reasons[] = static const char *irq_remap_fault_reasons[] = static const char *dmar_get_fault_reason(u8 fault_reason, int *fault_type)
static inline int dmar_msi_reg(struct intel_iommu *iommu, int irq)
void dmar_msi_unmask(struct irq_data *data)
void dmar_msi_mask(struct irq_data *data)
void dmar_msi_write(int irq, struct msi_msg *msg)
void dmar_msi_read(int irq, struct msi_msg *msg)
static int dmar_fault_do_one(struct intel_iommu *iommu, int type, u8 fault_reason, u16 source_id, unsigned long long addr)
define PRIMARY_FAULT_REG_LEN (16)
irqreturn_t dmar_fault(int irq, void *dev_id)
int dmar_set_interrupt(struct intel_iommu *iommu)
int __init enable_drhd_fault_handling(void)
int dmar_reenable_qi(struct intel_iommu *iommu)
int __init dmar_ir_support(void)
static inline bool dmar_in_use(void)
static int __init dmar_free_unused_resources(void)
static inline bool dmar_detect_dsm(acpi_handle handle, int func)
static int dmar_walk_dsm_resource(acpi_handle handle, int func, dmar_res_handler_t handler, void *arg)
static int dmar_hp_add_drhd(struct acpi_dmar_header *header, void *arg)
static int dmar_hp_remove_drhd(struct acpi_dmar_header *header, void *arg)
static int dmar_hp_release_drhd(struct acpi_dmar_header *header, void *arg)
static int dmar_hotplug_insert(acpi_handle handle)
static int dmar_hotplug_remove(acpi_handle handle)
static acpi_status dmar_get_dsm_handle(acpi_handle handle, u32 lvl, void *context, void **retval)
static int dmar_device_hotplug(acpi_handle handle, bool insert)
int dmar_device_add(acpi_handle handle)
int dmar_device_remove(acpi_handle handle)
bool dmar_platform_optin(void)
\n
     18 struct intel_iommu *iommu
     12 void
      8 void *arg
      8 acpi_handle handle
      7 struct acpi_dmar_header *header
      6 struct dmar_pci_notify_info *info
      4 int irq
      3 u64 addr
      3 struct pci_dev *dev
      2 void *start
      2 u8 fault_reason
      2 u64 type
      2 u16 sid
      2 u16 segment
      2 u16 did
      2 struct msi_msg *msg
      2 struct irq_data *data
      2 struct dmar_res_callback *cb
      2 struct dmar_drhd_unit *drhd
      2 struct dmar_dev_scope *devices
      2 int func
      2 int count
      2 int *cnt
      1 void **retval
      1 void*end
      1 void *end
      1 void *dev_id
      1 void *data
      1 void *context
      1 unsigned mask
      1 unsigned long long addr
      1 unsigned long event
      1 unsigned long action
      1 unsigned int size_order
      1 u8 fm
      1 u8 device_number
      1 u64 phys_addr
      1 u32 lvl
      1 u16 source_id
      1 u16 qdep
      1 u16 pfsid
      1 struct q_inval *qi
      1 struct qi_desc *desc
      1 struct notifier_block *nb
      1 struct dmar_drhd_unit *dmaru
      1 struct dmar_dev_scope devices[]
      1 struct dmar_dev_scope **devices
      1 struct acpi_table_dmar *dmar
      1 struct acpi_dmar_pci_path *path
      1 struct acpi_dmar_header *start
      1 struct acpi_dmar_header *entry
      1 struct acpi_dmar_hardware_unit *drhd
      1 struct acpi_device *adev
      1 size_t len
      1 int type
      1 int index
      1 int *fault_type
      1 int devices_cnt
      1 int cnt
      1 int bus
      1 dmar_res_handler_t handler
      1 dmar_platform_optin
      1 const char *message
      1 bool insert
      1 16
