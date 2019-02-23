
\n
static int param_get_debug_layer(char *buffer, const struct kernel_param *kp)
static int param_get_debug_level(char *buffer, const struct kernel_param *kp)
static int param_set_trace_method_name(const char *val, const struct kernel_param *kp)
static int param_get_trace_method_name(char *buffer, const struct kernel_param *kp)
static int param_set_trace_state(const char *val, const struct kernel_param *kp)
static int param_get_trace_state(char *buffer, const struct kernel_param *kp)
static int param_get_acpica_version(char *buffer, const struct kernel_param *kp)
static ssize_t acpi_table_show(struct file *filp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t offset, size_t count)
static int acpi_table_attr_init(struct kobject *tables_obj, struct acpi_table_attr *table_attr, struct acpi_table_header *table_header)
acpi_status acpi_sysfs_table_handler(u32 event, void *table, void *context)
static ssize_t acpi_data_show(struct file *filp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t offset, size_t count)
static int acpi_bert_data_init(void *th, struct acpi_data_attr *data_attr)
static int acpi_table_data_init(struct acpi_table_header *th)
static int acpi_tables_sysfs_init(void)
static void delete_gpe_attr_array(void)
static void gpe_count(u32 gpe_number)
static void fixed_event_count(u32 event_number)
static void acpi_global_event_handler(u32 event_type, acpi_handle device, u32 event_number, void *context)
static int get_status(u32 index, acpi_event_status *status, acpi_handle *handle)
static ssize_t counter_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t counter_set(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t size)
static int __init acpi_gpe_set_masked_gpes(char *val)
void __init acpi_gpe_apply_masked_gpes(void)
void acpi_irq_stats_init(void)
static void __exit interrupt_stats_exit(void)
static ssize_t acpi_show_profile(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t hotplug_enabled_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t hotplug_enabled_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t size)
void acpi_sysfs_add_hotplug_profile(struct acpi_hotplug_profile *hotplug, const char *name)
static ssize_t force_remove_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t force_remove_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t size)
int __init acpi_sysfs_init(void)
\n
      8 struct kobject *kobj
      7 const struct kernel_param *kp
      6 void
      6 struct kobj_attribute *attr
      6 char *buf
      5 char *buffer
      3 size_t size
      3 const char *buf
      2 void *context
      2 u32 event_number
      2 struct file *filp
      2 struct bin_attribute *bin_attr
      2 size_t count
      2 loff_t offset
      2 const char *val
      1 void *th
      1 void *table
      1 u32 index
      1 u32 gpe_number
      1 u32 event_type
      1 u32 event
      1 struct kobject *tables_obj
      1 struct device *dev
      1 struct device_attribute *attr
      1 struct acpi_table_header *th
      1 struct acpi_table_header *table_header
      1 struct acpi_table_attr *table_attr
      1 struct acpi_hotplug_profile *hotplug
      1 struct acpi_data_attr *data_attr
      1 const char *name
      1 char *val
      1 acpi_handle *handle
      1 acpi_handle device
      1 acpi_event_status *status
