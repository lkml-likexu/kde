
\n
static inline acpi_handle acpi_device_handle(struct acpi_device *adev)
static inline struct fwnode_handle *acpi_alloc_fwnode_static(void)
static inline void acpi_free_fwnode_static(struct fwnode_handle *fwnode)
static inline bool has_acpi_companion(struct device *dev)
static inline void acpi_preset_companion(struct device *dev, struct acpi_device *parent, u64 addr)
static inline const char *acpi_dev_name(struct acpi_device *adev)
int __init acpi_debugger_init(void)
; int acpi_register_debugger(struct module *owner, const struct acpi_debugger_ops *ops)
; void acpi_unregister_debugger(const struct acpi_debugger_ops *ops)
; int acpi_debugger_create_thread(acpi_osd_exec_callback function, void *context)
; ssize_t acpi_debugger_write_log(const char *msg)
; ssize_t acpi_debugger_read_cmd(char *buffer, size_t buffer_length)
; int acpi_debugger_wait_command_ready(void)
; int acpi_debugger_notify_command_complete(void)
; static inline int acpi_debugger_init(void)
static inline int acpi_register_debugger(struct module *owner, const struct acpi_debugger_ops *ops)
static inline void acpi_unregister_debugger(const struct acpi_debugger_ops *ops)
static inline int acpi_debugger_create_thread(acpi_osd_exec_callback function, void *context)
static inline int acpi_debugger_write_log(const char *msg)
static inline int acpi_debugger_read_cmd(char *buffer, u32 buffer_length)
static inline int acpi_debugger_wait_command_ready(void)
static inline int acpi_debugger_notify_command_complete(void)
static inline bool invalid_logical_cpuid(u32 cpuid)
static inline bool invalid_phys_cpuid(phys_cpuid_t phys_id)
int acpi_register_ioapic(acpi_handle handle, u64 phys_addr, u32 gsi_base)
; int acpi_unregister_ioapic(acpi_handle handle, u32 gsi_base)
; int acpi_ioapic_registered(acpi_handle handle, u32 gsi_base)
; void acpi_irq_stats_init(void)
; extern u32 acpi_irq_handled; extern u32 acpi_irq_not_handled; extern unsigned int acpi_sci_irq; extern bool acpi_no_s5;define INVALID_ACPI_IRQ ((unsigned)
-1)
static inline bool acpi_sci_irq_valid(void)
int acpi_pci_irq_enable (struct pci_dev *dev)
; void acpi_penalize_isa_irq(int irq, int active)
; bool acpi_isa_irq_available(int irq)
; void acpi_penalize_sci_irq(int irq, int trigger, int polarity)
; static inline void acpi_penalize_sci_irq(int irq, int trigger, int polarity)
int acpi_map_pxm_to_online_node(int pxm)
; int acpi_get_node(acpi_handle handle)
; static inline int acpi_map_pxm_to_online_node(int pxm)
int acpi_map_pxm_to_online_node(int pxm)
; int acpi_get_node(acpi_handle handle)
; static inline int acpi_map_pxm_to_online_node(int pxm)
return 0; } static inline int acpi_get_node(acpi_handle handle)
static inline int acpi_dev_filter_resource_type_cb(struct acpi_resource *ares, void *arg)
static inline void acpi_device_set_enumerated(struct acpi_device *adev)
static inline void acpi_device_clear_enumerated(struct acpi_device *adev)
static inline u64 acpi_arch_get_root_pointer(void)
static inline bool acpi_dev_found(const char *hid)
static inline bool acpi_dev_present(const char *hid, const char *uid, s64 hrv)
static inline const char * acpi_dev_get_first_match_name(const char *hid, const char *uid, s64 hrv)
static inline bool is_acpi_node(struct fwnode_handle *fwnode)
static inline bool is_acpi_device_node(struct fwnode_handle *fwnode)
static inline struct acpi_device *to_acpi_device_node(struct fwnode_handle *fwnode)
static inline bool is_acpi_data_node(struct fwnode_handle *fwnode)
static inline struct acpi_data_node *to_acpi_data_node(struct fwnode_handle *fwnode)
static inline bool acpi_data_node_match(struct fwnode_handle *fwnode, const char *name)
static inline struct fwnode_handle *acpi_fwnode_handle(struct acpi_device *adev)
static inline bool has_acpi_companion(struct device *dev)
static inline void acpi_preset_companion(struct device *dev, struct acpi_device *parent, u64 addr)
static inline const char *acpi_dev_name(struct acpi_device *adev)
static inline struct device *acpi_get_first_physical_node(struct acpi_device *adev)
static inline int early_acpi_boot_init(void)
static inline int early_acpi_boot_init(void)
return 0; } static inline int acpi_boot_init(void)
static inline void acpi_boot_table_init(void)
static inline int acpi_mps_check(void)
static inline int acpi_check_resource_conflict(struct resource *res)
static inline int acpi_check_region(resource_size_t start, resource_size_t n, const char *name)
struct acpi_table_header; static inline int acpi_table_parse(char *id, int (*handler)
(struct acpi_table_header *)
)
static inline int acpi_nvs_register(__u64 start, __u64 size)
static inline int acpi_nvs_for_each_region(int (*func)
(__u64, __u64, void *)
, void *data)
static inline const struct acpi_device_id *acpi_match_device(const struct acpi_device_id *ids, const struct device *dev)
static inline const void *acpi_device_get_match_data(const struct device *dev)
static inline bool acpi_driver_match_device(struct device *dev, const struct device_driver *drv)
static inline union acpi_object *acpi_evaluate_dsm(acpi_handle handle, const guid_t *guid, int rev, int func, union acpi_object *argv4)
static inline int acpi_device_uevent_modalias(struct device *dev, struct kobj_uevent_env *env)
static inline int acpi_device_modalias(struct device *dev, char *buf, int size)
static inline bool acpi_dma_supported(struct acpi_device *adev)
static inline enum dev_dma_attr acpi_get_dma_attr(struct acpi_device *adev)
static inline int acpi_dma_get_range(struct device *dev, u64 *dma_addr, u64 *offset, u64 *size)
static inline int acpi_dma_configure(struct device *dev, enum dev_dma_attr attr)
static inline void acpi_device_set_enumerated(struct acpi_device *adev)
static inline void acpi_device_clear_enumerated(struct acpi_device *adev)
static inline int acpi_reconfig_notifier_register(struct notifier_block *nb)
static inline int acpi_reconfig_notifier_unregister(struct notifier_block *nb)
static inline struct acpi_device *acpi_resource_consumer(struct resource *res)
void arch_reserve_mem_area(acpi_physical_address addr, size_t size)
; static inline void arch_reserve_mem_area(acpi_physical_address addr, size_t size)
int acpi_dev_suspend(struct device *dev, bool wakeup)
; int acpi_dev_resume(struct device *dev)
; int acpi_subsys_runtime_suspend(struct device *dev)
; int acpi_subsys_runtime_resume(struct device *dev)
; int acpi_dev_pm_attach(struct device *dev, bool power_on)
; static inline int acpi_dev_pm_attach(struct device *dev, bool power_on)
static inline void acpi_dev_remove_driver_gpios(struct acpi_device *adev)
bool acpi_gpio_get_irq_resource(struct acpi_resource *ares, struct acpi_resource_gpio **agpio)
; int acpi_dev_gpio_irq_get(struct acpi_device *adev, int index)
; static inline int acpi_dev_add_driver_gpios(struct acpi_device *adev, const struct acpi_gpio_mapping *gpios)
static inline int devm_acpi_dev_add_driver_gpios(struct device *dev, const struct acpi_gpio_mapping *gpios)
static inline bool acpi_gpio_get_irq_resource(struct acpi_resource *ares, struct acpi_resource_gpio **agpio)
static inline bool acpi_gpio_get_irq_resource(struct acpi_resource *ares, struct acpi_resource_gpio **agpio)
return false; } static inline int acpi_dev_gpio_irq_get(struct acpi_device *adev, int index)
bool i2c_acpi_get_i2c_resource(struct acpi_resource *ares, struct acpi_resource_i2c_serialbus **i2c)
; static inline bool i2c_acpi_get_i2c_resource(struct acpi_resource *ares, struct acpi_resource_i2c_serialbus **i2c)
static inline int acpi_node_get_property_reference( const struct fwnode_handle *fwnode, const char *name, size_t index, struct fwnode_reference_args *args)
static inline bool acpi_dev_has_props(const struct acpi_device *adev)
define acpi_probe_device_table(t)
\ extern struct acpi_probe_entry ACPI_PROBE_TABLE(t)
, \ ACPI_PROBE_TABLE_END(t)
; \ __acpi_probe_device_table(&ACPI_PROBE_TABLE(t)
, \(&ACPI_PROBE_TABLE_END(t)
- \ &ACPI_PROBE_TABLE(t)
)
)
; \})
static inline int acpi_dev_get_property(struct acpi_device *adev, const char *name, acpi_object_type type, const union acpi_object **obj)
static inline int __acpi_node_get_property_reference(const struct fwnode_handle *fwnode, const char *name, size_t index, size_t num_args, struct fwnode_reference_args *args)
static inline int acpi_node_get_property_reference(const struct fwnode_handle *fwnode, const char *name, size_t index, struct fwnode_reference_args *args)
static inline int acpi_node_prop_get(const struct fwnode_handle *fwnode, const char *propname, void **valptr)
static inline int acpi_dev_prop_get(const struct acpi_device *adev, const char *propname, void **valptr)
static inline int acpi_dev_prop_read_single(const struct acpi_device *adev, const char *propname, enum dev_prop_type proptype, void *val)
static inline int acpi_node_prop_read(const struct fwnode_handle *fwnode, const char *propname, enum dev_prop_type proptype, void *val, size_t nval)
static inline int acpi_dev_prop_read(const struct acpi_device *adev, const char *propname, enum dev_prop_type proptype, void *val, size_t nval)
static inline struct fwnode_handle * acpi_get_next_subnode(const struct fwnode_handle *fwnode, struct fwnode_handle *child)
static inline struct fwnode_handle * acpi_node_get_parent(const struct fwnode_handle *fwnode)
static inline struct fwnode_handle * acpi_graph_get_next_endpoint(const struct fwnode_handle *fwnode, struct fwnode_handle *prev)
static inline int acpi_graph_get_remote_endpoint(const struct fwnode_handle *fwnode, struct fwnode_handle **remote, struct fwnode_handle **port, struct fwnode_handle **endpoint)
extern bool qdf2400_e44_present; int acpi_parse_spcr(bool enable_earlycon, bool enable_console)
; static inline int acpi_parse_spcr(bool enable_earlycon, bool enable_console)
int acpi_irq_get(acpi_handle handle, unsigned int index, struct resource *res)
; static inline int acpi_irq_get(acpi_handle handle, unsigned int index, struct resource *res)
int lpit_read_residency_count_address(u64 *address)
; static inline int lpit_read_residency_count_address(u64 *address)
int find_acpi_cpu_topology(unsigned int cpu, int level)
; int find_acpi_cpu_topology_package(unsigned int cpu)
; int find_acpi_cpu_cache_topology(unsigned int cpu, int level)
; static inline int find_acpi_cpu_topology(unsigned int cpu, int level)
int find_acpi_cpu_topology(unsigned int cpu, int level)
; int find_acpi_cpu_topology_package(unsigned int cpu)
; int find_acpi_cpu_cache_topology(unsigned int cpu, int level)
; static inline int find_acpi_cpu_topology(unsigned int cpu, int level)
return -EINVAL; } static inline int find_acpi_cpu_topology_package(unsigned int cpu)
int find_acpi_cpu_topology(unsigned int cpu, int level)
; int find_acpi_cpu_topology_package(unsigned int cpu)
; int find_acpi_cpu_cache_topology(unsigned int cpu, int level)
; static inline int find_acpi_cpu_topology(unsigned int cpu, int level)
return -EINVAL; } static inline int find_acpi_cpu_topology_package(unsigned int cpu)
return -EINVAL; } static inline int find_acpi_cpu_cache_topology(unsigned int cpu, int level)
extern int acpi_platform_notify(struct device *dev, enum kobject_action action)
; static inline int acpi_platform_notify(struct device *dev, enum kobject_action action)
\n
     18 struct device *dev
     16 struct acpi_device *adev
     15 void
     15 unsigned int cpu
     10 int level
      9 const struct fwnode_handle *fwnode
      9 acpi_handle handle
      7 struct fwnode_handle *fwnode
      6 struct acpi_resource *ares
      6 const char *name
      5 const char *propname
      4 t
      4 struct resource *res
      4 int pxm
      4 int irq
      4 const struct acpi_device *adev
      4 const struct acpi_debugger_ops *ops
      3 void *val
      3 u32 gsi_base
      3 struct fwnode_reference_args *args
      3 struct acpi_resource_gpio **agpio
      3 size_t index
      3 enum dev_prop_type proptype
      3 const char *hid
      2 void **valptr
      2 void *context
      2 unsigned int index
      2 u64 *address
      2 u64 addr
      2 __u64
      2 struct notifier_block *nb
      2 struct module *owner
      2 struct acpi_resource_i2c_serialbus **i2c
      2 struct acpi_device *parent
      2 size_t size
      2 size_t nval
      2 s64 hrv
      2 int trigger
      2 int polarity
      2 int index
      2 enum kobject_action action
      2 const struct device *dev
      2 const struct acpi_gpio_mapping *gpios
      2 const char *uid
      2 const char *msg
      2 char *buffer
      2 bool power_on
      2 bool enable_earlycon
      2 bool enable_console
      2 acpi_physical_address addr
      2 acpi_osd_exec_callback function
      1 void *arg
      1 void *
      1 unsigned
      1 union acpi_object *argv4
      1 __u64 start
      1 u64 *size
      1 __u64 size
      1 u64 phys_addr
      1 u64 *offset
      1 u64 *dma_addr
      1 u32 cpuid
      1 u32 buffer_length
      1 struct pci_dev *dev
      1 struct kobj_uevent_env *env
      1 struct fwnode_handle **remote
      1 struct fwnode_handle *prev
      1 struct fwnode_handle **port
      1 struct fwnode_handle **endpoint
      1 struct fwnode_handle *child
      1 struct acpi_table_header *
      1 size_t num_args
      1 size_t buffer_length
      1 resource_size_t start
      1 resource_size_t n
      1 phys_cpuid_t phys_id
      1 int size
      1 int rev
      1 int *handler
      1 int *func
      1 int func
      1 int active
      1 enum dev_dma_attr attr
      1 const union acpi_object **obj
      1 const struct device_driver *drv
      1 const struct acpi_device_id *ids
      1 const guid_t *guid
      1 char *id
      1 char *buf
      1 bool wakeup
      1 &ACPI_PROBE_TABLEt
      1 &ACPI_PROBE_TABLE_ENDt
      1 acpi_object_type type
