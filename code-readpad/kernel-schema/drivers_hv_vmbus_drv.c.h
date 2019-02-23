
EXPORT_SYMBOL_GPL(__vmbus_driver_register);
EXPORT_SYMBOL_GPL(vmbus_driver_unregister);
EXPORT_SYMBOL_GPL(vmbus_allocate_mmio);
EXPORT_SYMBOL_GPL(vmbus_free_mmio);
\n
static int hyperv_panic_event(struct notifier_block *nb, unsigned long val, void *args)
static int hyperv_die_event(struct notifier_block *nb, unsigned long val, void *args)
static int vmbus_exists(void)
define VMBUS_ALIAS_LEN ((sizeof((struct hv_vmbus_device_id *)
0)
->guid)
* 2)
static void print_alias_name(struct hv_device *hv_dev, char *alias_name)
static u8 channel_monitor_group(const struct vmbus_channel *channel)
static u8 channel_monitor_offset(const struct vmbus_channel *channel)
static u32 channel_pending(const struct vmbus_channel *channel, const struct hv_monitor_page *monitor_page)
static u32 channel_latency(const struct vmbus_channel *channel, const struct hv_monitor_page *monitor_page)
static u32 channel_conn_id(struct vmbus_channel *channel, struct hv_monitor_page *monitor_page)
static ssize_t id_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t state_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t monitor_id_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t class_id_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t device_id_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t modalias_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t numa_node_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t server_monitor_pending_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t client_monitor_pending_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t server_monitor_latency_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t client_monitor_latency_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t server_monitor_conn_id_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t client_monitor_conn_id_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t out_intr_mask_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t out_read_index_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t out_write_index_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t out_read_bytes_avail_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t out_write_bytes_avail_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t in_intr_mask_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t in_read_index_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t in_write_index_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t in_read_bytes_avail_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t in_write_bytes_avail_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t channel_vp_mapping_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t vendor_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t device_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t driver_override_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t driver_override_show(struct device *dev, struct device_attribute *attr, char *buf)
static int vmbus_uevent(struct device *device, struct kobj_uevent_env *env)
static inline bool is_null_guid(const uuid_le *guid)
static const struct hv_vmbus_device_id * hv_vmbus_dynid_match(struct hv_driver *drv, const uuid_le *guid)
static const struct hv_vmbus_device_id *hv_vmbus_get_id(struct hv_driver *drv, struct hv_device *dev)
static int vmbus_add_dynid(struct hv_driver *drv, uuid_le *guid)
static void vmbus_free_dynids(struct hv_driver *drv)
static ssize_t new_id_store(struct device_driver *driver, const char *buf, size_t count)
static ssize_t remove_id_store(struct device_driver *driver, const char *buf, size_t count)
static int vmbus_match(struct device *device, struct device_driver *driver)
static int vmbus_probe(struct device *child_device)
static int vmbus_remove(struct device *child_device)
static void vmbus_shutdown(struct device *child_device)
static void vmbus_device_release(struct device *device)
static void vmbus_onmessage_work(struct work_struct *work)
static void hv_process_timer_expiration(struct hv_message *msg, struct hv_per_cpu_context *hv_cpu)
void vmbus_on_msg_dpc(unsigned long data)
static void vmbus_channel_isr(struct vmbus_channel *channel)
static void vmbus_chan_sched(struct hv_per_cpu_context *hv_cpu)
static void vmbus_isr(void)
static void hv_kmsg_dump(struct kmsg_dumper *dumper, enum kmsg_dump_reason reason)
static int vmbus_bus_init(void)
int __vmbus_driver_register(struct hv_driver *hv_driver, struct module *owner, const char *mod_name)
void vmbus_driver_unregister(struct hv_driver *hv_driver)
static void vmbus_chan_release(struct kobject *kobj)
static ssize_t vmbus_chan_attr_show(struct kobject *kobj, struct attribute *attr, char *buf)
static ssize_t out_mask_show(const struct vmbus_channel *channel, char *buf)
static ssize_t in_mask_show(const struct vmbus_channel *channel, char *buf)
static ssize_t read_avail_show(const struct vmbus_channel *channel, char *buf)
static ssize_t write_avail_show(const struct vmbus_channel *channel, char *buf)
static ssize_t show_target_cpu(const struct vmbus_channel *channel, char *buf)
static ssize_t channel_pending_show(const struct vmbus_channel *channel, char *buf)
static ssize_t channel_latency_show(const struct vmbus_channel *channel, char *buf)
static ssize_t channel_interrupts_show(const struct vmbus_channel *channel, char *buf)
static ssize_t channel_events_show(const struct vmbus_channel *channel, char *buf)
static ssize_t subchannel_monitor_id_show(const struct vmbus_channel *channel, char *buf)
static ssize_t subchannel_id_show(const struct vmbus_channel *channel, char *buf)
int vmbus_add_channel_kobj(struct hv_device *dev, struct vmbus_channel *channel)
struct hv_device *vmbus_device_create(const uuid_le *type, const uuid_le *instance, struct vmbus_channel *channel)
int vmbus_device_register(struct hv_device *child_device_obj)
void vmbus_device_unregister(struct hv_device *device_obj)
define VTPM_BASE_ADDRESS 0xfed40000 static acpi_status vmbus_walk_resources(struct acpi_resource *res, void *ctx)
static int vmbus_acpi_remove(struct acpi_device *device)
static void vmbus_reserve_fb(void)
int vmbus_allocate_mmio(struct resource **new, struct hv_device *device_obj, resource_size_t min, resource_size_t max, resource_size_t size, resource_size_t align, bool fb_overlap_ok)
void vmbus_free_mmio(resource_size_t start, resource_size_t size)
static int vmbus_acpi_add(struct acpi_device *device)
static void hv_kexec_handler(void)
static void hv_crash_handler(struct pt_regs *regs)
static int __init hv_acpi_init(void)
static void __exit vmbus_exit(void)
\n
     39 char *buf
     28 struct device *dev
     25 struct device_attribute *dev_attr
     15 const struct vmbus_channel *channel
      7 void
      4 struct vmbus_channel *channel
      4 struct hv_driver *drv
      3 struct device_driver *driver
      3 struct device *device
      3 struct device *child_device
      3 struct device_attribute *attr
      3 size_t count
      3 const char *buf
      2 void *args
      2 unsigned long val
      2 struct notifier_block *nb
      2 struct kobject *kobj
      2 struct hv_per_cpu_context *hv_cpu
      2 struct hv_driver *hv_driver
      2 struct hv_device *device_obj
      2 struct hv_device *dev
      2 struct acpi_device *device
      2 resource_size_t size
      2 const uuid_le *guid
      2 const struct hv_monitor_page *monitor_page
      1 void *ctx
      1 vmbus_free_mmio
      1 vmbus_driver_unregister
      1 __vmbus_driver_register
      1 vmbus_allocate_mmio
      1 uuid_le *guid
      1 unsigned long data
      1 struct work_struct *work
      1 struct resource **new
      1 struct pt_regs *regs
      1 struct module *owner
      1 struct kobj_uevent_env *env
      1 struct kmsg_dumper *dumper
      1 struct hv_monitor_page *monitor_page
      1 struct hv_message *msg
      1 struct hv_device *hv_dev
      1 struct hv_device *child_device_obj
      1 struct attribute *attr
      1 struct acpi_resource *res
      1 sizeofstruct hv_vmbus_device_id *
      1 resource_size_t start
      1 resource_size_t min
      1 resource_size_t max
      1 resource_size_t align
      1 enum kmsg_dump_reason reason
      1 const uuid_le *type
      1 const uuid_le *instance
      1 const char *mod_name
      1 char *alias_name
      1 bool fb_overlap_ok
