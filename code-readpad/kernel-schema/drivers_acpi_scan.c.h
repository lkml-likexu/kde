
EXPORT_SYMBOL_GPL(acpi_scan_lock_acquire);
EXPORT_SYMBOL_GPL(acpi_scan_lock_release);
EXPORT_SYMBOL_GPL(acpi_initialize_hp_context);
EXPORT_SYMBOL_GPL(acpi_bus_get_ejd);
EXPORT_SYMBOL_GPL(acpi_dma_configure);
EXPORT_SYMBOL_GPL(acpi_walk_dep_device_list);
EXPORT_SYMBOL_GPL(acpi_bus_trim);
EXPORT_SYMBOL_GPL(acpi_bus_register_early_device);
\n
void acpi_scan_lock_acquire(void)
void acpi_scan_lock_release(void)
void acpi_lock_hp_context(void)
void acpi_unlock_hp_context(void)
void acpi_initialize_hp_context(struct acpi_device *adev, struct acpi_hotplug_context *hp, int (*notify)
(struct acpi_device *, u32)
, void (*uevent)
(struct acpi_device *, u32)
)
int acpi_scan_add_handler(struct acpi_scan_handler *handler)
int acpi_scan_add_handler_with_hotplug(struct acpi_scan_handler *handler, const char *hotplug_profile_name)
bool acpi_scan_is_offline(struct acpi_device *adev, bool uevent)
static acpi_status acpi_bus_offline(acpi_handle handle, u32 lvl, void *data, void **ret_p)
static acpi_status acpi_bus_online(acpi_handle handle, u32 lvl, void *data, void **ret_p)
static int acpi_scan_try_to_offline(struct acpi_device *device)
static int acpi_scan_hot_remove(struct acpi_device *device)
static int acpi_scan_device_not_present(struct acpi_device *adev)
static int acpi_scan_device_check(struct acpi_device *adev)
static int acpi_scan_bus_check(struct acpi_device *adev)
static int acpi_generic_hotplug_event(struct acpi_device *adev, u32 type)
void acpi_device_hotplug(struct acpi_device *adev, u32 src)
static void acpi_free_power_resources_lists(struct acpi_device *device)
static void acpi_device_release(struct device *dev)
static void acpi_device_del(struct acpi_device *device)
static void acpi_device_del_work_fn(struct work_struct *work_not_used)
static void acpi_scan_drop_device(acpi_handle handle, void *context)
static int acpi_get_device_data(acpi_handle handle, struct acpi_device **device, void (*callback)
(void *)
)
int acpi_bus_get_device(acpi_handle handle, struct acpi_device **device)
static void get_acpi_device(void *dev)
struct acpi_device *acpi_bus_get_acpi_device(acpi_handle handle)
void acpi_bus_put_acpi_device(struct acpi_device *adev)
int acpi_device_add(struct acpi_device *device, void (*release)
(struct device *)
)
static struct acpi_device *acpi_bus_get_parent(acpi_handle handle)
acpi_status acpi_bus_get_ejd(acpi_handle handle, acpi_handle *ejd)
static int acpi_bus_extract_wakeup_device_power_package(acpi_handle handle, struct acpi_device_wakeup *wakeup)
static bool acpi_wakeup_gpe_init(struct acpi_device *device)
static void acpi_bus_get_wakeup_device_flags(struct acpi_device *device)
static void acpi_bus_init_power_state(struct acpi_device *device, int state)
static void acpi_bus_get_power_flags(struct acpi_device *device)
static void acpi_bus_get_flags(struct acpi_device *device)
static void acpi_device_get_busid(struct acpi_device *device)
bool acpi_ata_match(acpi_handle handle)
bool acpi_bay_match(acpi_handle handle)
bool acpi_device_is_battery(struct acpi_device *adev)
static bool is_ejectable_bay(struct acpi_device *adev)
bool acpi_dock_match(acpi_handle handle)
static acpi_status acpi_backlight_cap_match(acpi_handle handle, u32 level, void *context, void **return_value)
long acpi_is_video_device(acpi_handle handle)
const char *acpi_device_hid(struct acpi_device *device)
static void acpi_add_id(struct acpi_device_pnp *pnp, const char *dev_id)
static bool acpi_ibm_smbus_match(acpi_handle handle)
static bool acpi_object_is_system_bus(acpi_handle handle)
static void acpi_set_pnp_ids(acpi_handle handle, struct acpi_device_pnp *pnp, int device_type)
void acpi_free_pnp_ids(struct acpi_device_pnp *pnp)
bool acpi_dma_supported(struct acpi_device *adev)
enum dev_dma_attr acpi_get_dma_attr(struct acpi_device *adev)
int acpi_dma_get_range(struct device *dev, u64 *dma_addr, u64 *offset, u64 *size)
int acpi_dma_configure(struct device *dev, enum dev_dma_attr attr)
static void acpi_init_coherency(struct acpi_device *adev)
static int acpi_check_serial_bus_slave(struct acpi_resource *ares, void *data)
static bool acpi_is_indirect_io_slave(struct acpi_device *device)
static bool acpi_device_enumeration_by_parent(struct acpi_device *device)
void acpi_init_device_object(struct acpi_device *device, acpi_handle handle, int type, unsigned long long sta)
void acpi_device_add_finalize(struct acpi_device *device)
static int acpi_add_single_object(struct acpi_device **child, acpi_handle handle, int type, unsigned long long sta)
static acpi_status acpi_get_resource_memory(struct acpi_resource *ares, void *context)
static bool acpi_device_should_be_hidden(acpi_handle handle)
static int acpi_bus_type_and_status(acpi_handle handle, int *type, unsigned long long *sta)
bool acpi_device_is_present(const struct acpi_device *adev)
static bool acpi_scan_handler_matching(struct acpi_scan_handler *handler, const char *idstr, const struct acpi_device_id **matchid)
static struct acpi_scan_handler *acpi_scan_match_handler(const char *idstr, const struct acpi_device_id **matchid)
void acpi_scan_hotplug_enabled(struct acpi_hotplug_profile *hotplug, bool val)
static void acpi_scan_init_hotplug(struct acpi_device *adev)
static void acpi_device_dep_initialize(struct acpi_device *adev)
static acpi_status acpi_bus_check_add(acpi_handle handle, u32 lvl_not_used, void *not_used, void **return_value)
static void acpi_default_enumeration(struct acpi_device *device)
static int acpi_generic_device_attach(struct acpi_device *adev, const struct acpi_device_id *not_used)
static int acpi_scan_attach_handler(struct acpi_device *device)
static void acpi_bus_attach(struct acpi_device *device)
void acpi_walk_dep_device_list(acpi_handle handle)
int acpi_bus_scan(acpi_handle handle)
void acpi_bus_trim(struct acpi_device *adev)
int acpi_bus_register_early_device(int type)
static int acpi_bus_scan_fixed(void)
static void __init acpi_get_spcr_uart_addr(void)
int __init acpi_scan_init(void)
static int __init acpi_match_madt(struct acpi_subtable_header *header, const unsigned long end)
int __init __acpi_probe_device_table(struct acpi_probe_entry *ap_head, int nr)
static void acpi_table_events_fn(struct work_struct *work)
void acpi_scan_table_handler(u32 event, void *table, void *context)
int acpi_reconfig_notifier_register(struct notifier_block *nb)
int acpi_reconfig_notifier_unregister(struct notifier_block *nb)
\n
     24 acpi_handle handle
     19 struct acpi_device *device
     17 struct acpi_device *adev
      7 void
      4 void *context
      3 void *data
      3 struct device *dev
      3 struct acpi_scan_handler *handler
      3 struct acpi_device_pnp *pnp
      3 int type
      2 void **return_value
      2 void **ret_p
      2 unsigned long long sta
      2 u32 lvl
      2 u32
      2 struct notifier_block *nb
      2 struct acpi_resource *ares
      2 struct acpi_device **device
      2 struct acpi_device *
      2 const struct acpi_device_id **matchid
      2 const char *idstr
      1 void *table
      1 void *release
      1 void *not_used
      1 void *dev
      1 void *callback
      1 void *
      1 unsigned long long *sta
      1 *uevent
      1 u64 *size
      1 u64 *offset
      1 u64 *dma_addr
      1 u32 type
      1 u32 src
      1 u32 lvl_not_used
      1 u32 level
      1 u32 event
      1 struct work_struct *work_not_used
      1 struct work_struct *work
      1 struct device *
      1 struct acpi_subtable_header *header
      1 struct acpi_probe_entry *ap_head
      1 struct acpi_hotplug_profile *hotplug
      1 struct acpi_hotplug_context *hp
      1 struct acpi_device_wakeup *wakeup
      1 struct acpi_device **child
      1 int *type
      1 int state
      1 int nr
      1 int *notify
      1 int device_type
      1 enum dev_dma_attr attr
      1 const unsigned long end
      1 const struct acpi_device_id *not_used
      1 const struct acpi_device *adev
      1 const char *hotplug_profile_name
      1 const char *dev_id
      1 bool val
      1 bool uevent
      1 acpi_walk_dep_device_list
      1 acpi_scan_lock_release
      1 acpi_scan_lock_acquire
      1 acpi_initialize_hp_context
      1 acpi_handle *ejd
      1 acpi_dma_configure
      1 acpi_bus_trim
      1 acpi_bus_register_early_device
      1 acpi_bus_get_ejd
