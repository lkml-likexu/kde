
EXPORT_SYMBOL_GPL(acpi_bus_get_status_handle);
EXPORT_SYMBOL_GPL(acpi_bus_attach_private_data);
EXPORT_SYMBOL_GPL(acpi_bus_get_private_data);
EXPORT_SYMBOL_GPL(acpi_bus_detach_private_data);
EXPORT_SYMBOL_GPL(osc_pc_lpi_support_confirmed);
EXPORT_SYMBOL_GPL(acpi_set_modalias);
EXPORT_SYMBOL_GPL(acpi_match_device);
EXPORT_SYMBOL_GPL(acpi_device_get_match_data);
EXPORT_SYMBOL_GPL(acpi_driver_match_device);
EXPORT_SYMBOL_GPL(acpi_kobj);
\n
static inline int set_copy_dsdt(const struct dmi_system_id *id)
static inline int set_copy_dsdt(const struct dmi_system_id *id)
return 0; } static int set_copy_dsdt(const struct dmi_system_id *id)
acpi_status acpi_bus_get_status_handle(acpi_handle handle, unsigned long long *sta)
int acpi_bus_get_status(struct acpi_device *device)
void acpi_bus_private_data_handler(acpi_handle handle, void *context)
int acpi_bus_attach_private_data(acpi_handle handle, void *data)
int acpi_bus_get_private_data(acpi_handle handle, void **data)
void acpi_bus_detach_private_data(acpi_handle handle)
static void acpi_print_osc_error(acpi_handle handle, struct acpi_osc_context *context, char *error)
acpi_status acpi_run_osc(acpi_handle handle, struct acpi_osc_context *context)
static u8 sb_uuid_str[] = "0811B06E-4A27-44F9-8D60-3CBBC22E7B48"; static void acpi_bus_osc_support(void)
static void acpi_bus_notify(acpi_handle handle, u32 type, void *data)
static void acpi_device_notify(acpi_handle handle, u32 event, void *data)
static void acpi_device_notify_fixed(void *data)
static u32 acpi_device_fixed_event(void *data)
static int acpi_device_install_notify_handler(struct acpi_device *device)
static void acpi_device_remove_notify_handler(struct acpi_device *device)
static void sb_notify_work(struct work_struct *dummy)
static void acpi_sb_notify(acpi_handle handle, u32 event, void *data)
static int __init acpi_setup_sb_notify_handler(void)
struct device *acpi_get_first_physical_node(struct acpi_device *adev)
static struct acpi_device *acpi_primary_dev_companion(struct acpi_device *adev, const struct device *dev)
bool acpi_device_is_first_physical_node(struct acpi_device *adev, const struct device *dev)
struct acpi_device *acpi_companion_match(const struct device *dev)
static bool acpi_of_match_device(struct acpi_device *adev, const struct of_device_id *of_match_table, const struct of_device_id **of_id)
static bool acpi_of_modalias(struct acpi_device *adev, char *modalias, size_t len)
void acpi_set_modalias(struct acpi_device *adev, const char *default_id, char *modalias, size_t len)
static bool __acpi_match_device_cls(const struct acpi_device_id *id, struct acpi_hardware_id *hwid)
static bool __acpi_match_device(struct acpi_device *device, const struct acpi_device_id *acpi_ids, const struct of_device_id *of_ids, const struct acpi_device_id **acpi_id, const struct of_device_id **of_id)
const struct acpi_device_id *acpi_match_device(const struct acpi_device_id *ids, const struct device *dev)
const void *acpi_device_get_match_data(const struct device *dev)
int acpi_match_device_ids(struct acpi_device *device, const struct acpi_device_id *ids)
bool acpi_driver_match_device(struct device *dev, const struct device_driver *drv)
int acpi_bus_register_driver(struct acpi_driver *driver)
void acpi_bus_unregister_driver(struct acpi_driver *driver)
static int acpi_bus_match(struct device *dev, struct device_driver *drv)
static int acpi_device_uevent(struct device *dev, struct kobj_uevent_env *env)
static int acpi_device_probe(struct device *dev)
static int acpi_device_remove(struct device *dev)
static int __init acpi_bus_init_irq(void)
void __init acpi_early_init(void)
void __init acpi_subsystem_init(void)
static acpi_status acpi_bus_table_handler(u32 event, void *table, void *context)
static int __init acpi_bus_init(void)
static int __init acpi_init(void)
\n
     10 acpi_handle handle
      7 void
      6 void *data
      6 struct acpi_device *adev
      5 struct device *dev
      5 struct acpi_device *device
      5 const struct device *dev
      3 u32 event
      3 const struct dmi_system_id *id
      2 void *context
      2 struct acpi_osc_context *context
      2 struct acpi_driver *driver
      2 size_t len
      2 const struct of_device_id **of_id
      2 const struct acpi_device_id *ids
      2 char *modalias
      1 void *table
      1 void **data
      1 unsigned long long *sta
      1 u32 type
      1 struct work_struct *dummy
      1 struct kobj_uevent_env *env
      1 struct device_driver *drv
      1 struct acpi_hardware_id *hwid
      1 osc_pc_lpi_support_confirmed
      1 const struct of_device_id *of_match_table
      1 const struct of_device_id *of_ids
      1 const struct device_driver *drv
      1 const struct acpi_device_id *id
      1 const struct acpi_device_id *acpi_ids
      1 const struct acpi_device_id **acpi_id
      1 const char *default_id
      1 char *error
      1 acpi_set_modalias
      1 acpi_match_device
      1 acpi_kobj
      1 acpi_driver_match_device
      1 acpi_device_get_match_data
      1 acpi_bus_get_status_handle
      1 acpi_bus_get_private_data
      1 acpi_bus_detach_private_data
      1 acpi_bus_attach_private_data
