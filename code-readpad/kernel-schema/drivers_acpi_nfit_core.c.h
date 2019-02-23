
EXPORT_SYMBOL_GPL(acpi_nfit_ctl);
EXPORT_SYMBOL_GPL(nfit_get_smbios_id);
EXPORT_SYMBOL_GPL(__acpi_nvdimm_notify);
EXPORT_SYMBOL_GPL(acpi_nfit_init);
EXPORT_SYMBOL_GPL(acpi_nfit_desc_init);
EXPORT_SYMBOL_GPL(acpi_nfit_shutdown);
EXPORT_SYMBOL_GPL(__acpi_nfit_notify);
\n
const guid_t *to_nfit_uuid(enum nfit_uuids id)
static struct acpi_device *to_acpi_dev(struct acpi_nfit_desc *acpi_desc)
static int xlat_bus_status(void *buf, unsigned int cmd, u32 status)
static int xlat_nvdimm_status(struct nvdimm *nvdimm, void *buf, unsigned int cmd, u32 status)
static int xlat_status(struct nvdimm *nvdimm, void *buf, unsigned int cmd, u32 status)
static union acpi_object *pkg_to_buf(union acpi_object *pkg)
static union acpi_object *int_to_buf(union acpi_object *integer)
static union acpi_object *acpi_label_write(acpi_handle handle, u32 offset, u32 len, void *data)
static union acpi_object *acpi_label_read(acpi_handle handle, u32 offset, u32 len)
static union acpi_object *acpi_label_info(acpi_handle handle)
static u8 nfit_dsm_revid(unsigned family, unsigned func)
static bool payload_dumpable(struct nvdimm *nvdimm, unsigned int func)
static int cmd_to_func(struct nfit_mem *nfit_mem, unsigned int cmd, struct nd_cmd_pkg *call_pkg)
int acpi_nfit_ctl(struct nvdimm_bus_descriptor *nd_desc, struct nvdimm *nvdimm, unsigned int cmd, void *buf, unsigned int buf_len, int *cmd_rc)
static const char *spa_type_name(u16 type)
int nfit_spa_type(struct acpi_nfit_system_address *spa)
static bool add_spa(struct acpi_nfit_desc *acpi_desc, struct nfit_table_prev *prev, struct acpi_nfit_system_address *spa)
static bool add_memdev(struct acpi_nfit_desc *acpi_desc, struct nfit_table_prev *prev, struct acpi_nfit_memory_map *memdev)
int nfit_get_smbios_id(u32 device_handle, u16 *flags)
static size_t sizeof_dcr(struct acpi_nfit_control_region *dcr)
static bool add_dcr(struct acpi_nfit_desc *acpi_desc, struct nfit_table_prev *prev, struct acpi_nfit_control_region *dcr)
static bool add_bdw(struct acpi_nfit_desc *acpi_desc, struct nfit_table_prev *prev, struct acpi_nfit_data_region *bdw)
static size_t sizeof_idt(struct acpi_nfit_interleave *idt)
static bool add_idt(struct acpi_nfit_desc *acpi_desc, struct nfit_table_prev *prev, struct acpi_nfit_interleave *idt)
static size_t sizeof_flush(struct acpi_nfit_flush_address *flush)
static bool add_flush(struct acpi_nfit_desc *acpi_desc, struct nfit_table_prev *prev, struct acpi_nfit_flush_address *flush)
static bool add_platform_cap(struct acpi_nfit_desc *acpi_desc, struct acpi_nfit_capabilities *pcap)
static void *add_table(struct acpi_nfit_desc *acpi_desc, struct nfit_table_prev *prev, void *table, const void *end)
static void nfit_mem_find_spa_bdw(struct acpi_nfit_desc *acpi_desc, struct nfit_mem *nfit_mem)
static void nfit_mem_init_bdw(struct acpi_nfit_desc *acpi_desc, struct nfit_mem *nfit_mem, struct acpi_nfit_system_address *spa)
static int __nfit_mem_init(struct acpi_nfit_desc *acpi_desc, struct acpi_nfit_system_address *spa)
static int nfit_mem_cmp(void *priv, struct list_head *_a, struct list_head *_b)
static int nfit_mem_init(struct acpi_nfit_desc *acpi_desc)
static ssize_t bus_dsm_mask_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t revision_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t hw_error_scrub_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t hw_error_scrub_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
static ssize_t scrub_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t scrub_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
static bool ars_supported(struct nvdimm_bus *nvdimm_bus)
static umode_t nfit_visible(struct kobject *kobj, struct attribute *a, int n)
static struct acpi_nfit_memory_map *to_nfit_memdev(struct device *dev)
static struct acpi_nfit_control_region *to_nfit_dcr(struct device *dev)
static ssize_t handle_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t phys_id_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t vendor_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t rev_id_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t device_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t subsystem_vendor_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t subsystem_rev_id_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t subsystem_device_show(struct device *dev, struct device_attribute *attr, char *buf)
static int num_nvdimm_formats(struct nvdimm *nvdimm)
static ssize_t format_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t format1_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t formats_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t serial_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t family_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t dsm_mask_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t flags_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t id_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t dirty_shutdown_show(struct device *dev, struct device_attribute *attr, char *buf)
static umode_t acpi_nfit_dimm_attr_visible(struct kobject *kobj, struct attribute *a, int n)
static struct nvdimm *acpi_nfit_dimm_by_handle(struct acpi_nfit_desc *acpi_desc, u32 device_handle)
void __acpi_nvdimm_notify(struct device *dev, u32 event)
static void acpi_nvdimm_notify(acpi_handle handle, u32 event, void *data)
static bool acpi_nvdimm_has_method(struct acpi_device *adev, char *method)
__weak void nfit_intel_shutdown_status(struct nfit_mem *nfit_mem)
static void populate_shutdown_status(struct nfit_mem *nfit_mem)
static int acpi_nfit_add_dimm(struct acpi_nfit_desc *acpi_desc, struct nfit_mem *nfit_mem, u32 device_handle)
static void shutdown_dimm_notify(void *data)
static const struct nvdimm_security_ops *acpi_nfit_get_security_ops(int family)
static int acpi_nfit_register_dimms(struct acpi_nfit_desc *acpi_desc)
static void acpi_nfit_init_dsms(struct acpi_nfit_desc *acpi_desc)
static ssize_t range_index_show(struct device *dev, struct device_attribute *attr, char *buf)
static size_t sizeof_nfit_set_info(int num_mappings)
static size_t sizeof_nfit_set_info2(int num_mappings)
static int cmp_map_compat(const void *m0, const void *m1)
static int cmp_map(const void *m0, const void *m1)
static int cmp_map2(const void *m0, const void *m1)
static struct acpi_nfit_memory_map *memdev_from_spa( struct acpi_nfit_desc *acpi_desc, u16 range_index, int n)
static int acpi_nfit_init_interleave_set(struct acpi_nfit_desc *acpi_desc, struct nd_region_desc *ndr_desc, struct acpi_nfit_system_address *spa)
static u64 to_interleave_offset(u64 offset, struct nfit_blk_mmio *mmio)
static u32 read_blk_stat(struct nfit_blk *nfit_blk, unsigned int bw)
static void write_blk_ctl(struct nfit_blk *nfit_blk, unsigned int bw, resource_size_t dpa, unsigned int len, unsigned int write)
static int acpi_nfit_blk_single_io(struct nfit_blk *nfit_blk, resource_size_t dpa, void *iobuf, size_t len, int rw, unsigned int lane)
static int acpi_nfit_blk_region_do_io(struct nd_blk_region *ndbr, resource_size_t dpa, void *iobuf, u64 len, int rw)
static int nfit_blk_init_interleave(struct nfit_blk_mmio *mmio, struct acpi_nfit_interleave *idt, u16 interleave_ways)
static int acpi_nfit_blk_get_flags(struct nvdimm_bus_descriptor *nd_desc, struct nvdimm *nvdimm, struct nfit_blk *nfit_blk)
static int acpi_nfit_blk_region_enable(struct nvdimm_bus *nvdimm_bus, struct device *dev)
static int ars_get_cap(struct acpi_nfit_desc *acpi_desc, struct nd_cmd_ars_cap *cmd, struct nfit_spa *nfit_spa)
static int ars_start(struct acpi_nfit_desc *acpi_desc, struct nfit_spa *nfit_spa, enum nfit_ars_state req_type)
static int ars_continue(struct acpi_nfit_desc *acpi_desc)
static int ars_get_status(struct acpi_nfit_desc *acpi_desc)
static void ars_complete(struct acpi_nfit_desc *acpi_desc, struct nfit_spa *nfit_spa)
static int ars_status_process_records(struct acpi_nfit_desc *acpi_desc)
static void acpi_nfit_remove_resource(void *data)
static int acpi_nfit_insert_resource(struct acpi_nfit_desc *acpi_desc, struct nd_region_desc *ndr_desc)
static int acpi_nfit_init_mapping(struct acpi_nfit_desc *acpi_desc, struct nd_mapping_desc *mapping, struct nd_region_desc *ndr_desc, struct acpi_nfit_memory_map *memdev, struct nfit_spa *nfit_spa)
static bool nfit_spa_is_virtual(struct acpi_nfit_system_address *spa)
static bool nfit_spa_is_volatile(struct acpi_nfit_system_address *spa)
static int acpi_nfit_register_region(struct acpi_nfit_desc *acpi_desc, struct nfit_spa *nfit_spa)
static int ars_status_alloc(struct acpi_nfit_desc *acpi_desc)
static int acpi_nfit_query_poison(struct acpi_nfit_desc *acpi_desc)
static int ars_register(struct acpi_nfit_desc *acpi_desc, struct nfit_spa *nfit_spa)
static void ars_complete_all(struct acpi_nfit_desc *acpi_desc)
static unsigned int __acpi_nfit_scrub(struct acpi_nfit_desc *acpi_desc, int query_rc)
static void __sched_ars(struct acpi_nfit_desc *acpi_desc, unsigned int tmo)
static void sched_ars(struct acpi_nfit_desc *acpi_desc)
static void notify_ars_done(struct acpi_nfit_desc *acpi_desc)
static void acpi_nfit_scrub(struct work_struct *work)
static void acpi_nfit_init_ars(struct acpi_nfit_desc *acpi_desc, struct nfit_spa *nfit_spa)
static int acpi_nfit_register_regions(struct acpi_nfit_desc *acpi_desc)
static int acpi_nfit_check_deletions(struct acpi_nfit_desc *acpi_desc, struct nfit_table_prev *prev)
static int acpi_nfit_desc_init_scrub_attr(struct acpi_nfit_desc *acpi_desc)
static void acpi_nfit_unregister(void *data)
int acpi_nfit_init(struct acpi_nfit_desc *acpi_desc, void *data, acpi_size sz)
static int acpi_nfit_flush_probe(struct nvdimm_bus_descriptor *nd_desc)
static int __acpi_nfit_clear_to_send(struct nvdimm_bus_descriptor *nd_desc, struct nvdimm *nvdimm, unsigned int cmd)
static int acpi_nfit_clear_to_send(struct nvdimm_bus_descriptor *nd_desc, struct nvdimm *nvdimm, unsigned int cmd, void *buf)
int acpi_nfit_ars_rescan(struct acpi_nfit_desc *acpi_desc, enum nfit_ars_state req_type)
void acpi_nfit_desc_init(struct acpi_nfit_desc *acpi_desc, struct device *dev)
static void acpi_nfit_put_table(void *table)
void acpi_nfit_shutdown(void *data)
static int acpi_nfit_add(struct acpi_device *adev)
static int acpi_nfit_remove(struct acpi_device *adev)
static void acpi_nfit_update_notify(struct device *dev, acpi_handle handle)
static void acpi_nfit_uc_error_notify(struct device *dev, acpi_handle handle)
void __acpi_nfit_notify(struct device *dev, acpi_handle handle, u32 event)
static void acpi_nfit_notify(struct acpi_device *adev, u32 event)
static __init int nfit_init(void)
static __exit void nfit_exit(void)
\n
     43 struct acpi_nfit_desc *acpi_desc
     32 struct device *dev
     24 struct device_attribute *attr
     22 char *buf
      8 struct nvdimm *nvdimm
      8 struct nfit_table_prev *prev
      7 void *data
      7 unsigned int cmd
      7 struct nfit_spa *nfit_spa
      7 struct acpi_nfit_system_address *spa
      7 acpi_handle handle
      6 struct nfit_mem *nfit_mem
      5 void *buf
      5 struct nvdimm_bus_descriptor *nd_desc
      4 u32 event
      4 struct nfit_blk *nfit_blk
      4 struct acpi_device *adev
      3 u32 status
      3 u32 device_handle
      3 struct nd_region_desc *ndr_desc
      3 struct acpi_nfit_interleave *idt
      3 resource_size_t dpa
      3 int n
      3 const void *m1
      3 const void *m0
      2 void *table
      2 void *iobuf
      2 void
      2 unsigned int bw
      2 u32 offset
      2 u32 len
      2 struct nvdimm_bus *nvdimm_bus
      2 struct nfit_blk_mmio *mmio
      2 struct kobject *kobj
      2 struct attribute *a
      2 struct acpi_nfit_memory_map *memdev
      2 struct acpi_nfit_flush_address *flush
      2 struct acpi_nfit_control_region *dcr
      2 size_t size
      2 int rw
      2 int num_mappings
      2 enum nfit_ars_state req_type
      2 const char *buf
      1 void *priv
      1 unsigned int write
      1 unsigned int tmo
      1 unsigned int len
      1 unsigned int lane
      1 unsigned int func
      1 unsigned int buf_len
      1 unsigned func
      1 unsigned family
      1 union acpi_object *pkg
      1 union acpi_object *integer
      1 u64 offset
      1 u64 len
      1 u16 type
      1 u16 range_index
      1 u16 interleave_ways
      1 u16 *flags
      1 struct work_struct *work
      1 struct nd_mapping_desc *mapping
      1 struct nd_cmd_pkg *call_pkg
      1 struct nd_cmd_ars_cap *cmd
      1 struct nd_blk_region *ndbr
      1 struct list_head *_b
      1 struct list_head *_a
      1 struct acpi_nfit_data_region *bdw
      1 struct acpi_nfit_capabilities *pcap
      1 size_t len
      1 nfit_get_smbios_id
      1 int query_rc
      1 int family
      1 int *cmd_rc
      1 enum nfit_uuids id
      1 const void *end
      1 char *method
      1 acpi_size sz
      1 __acpi_nvdimm_notify
      1 acpi_nfit_shutdown
      1 __acpi_nfit_notify
      1 acpi_nfit_init
      1 acpi_nfit_desc_init
      1 acpi_nfit_ctl
