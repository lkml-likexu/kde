
\n
static inline int ap_using_interrupts(void)
void *ap_airq_ptr(void)
static int ap_interrupts_available(void)
static int ap_configuration_available(void)
static int ap_apft_available(void)
static inline int ap_qact_available(void)
static inline int ap_query_configuration(struct ap_config_info *info)
static void ap_init_configuration(void)
static inline int ap_test_config(unsigned int *field, unsigned int nr)
static inline int ap_test_config_card_id(unsigned int id)
static inline int ap_test_config_domain(unsigned int domain)
static int ap_query_queue(ap_qid_t qid, int *queue_depth, int *device_type, unsigned int *facilities)
void ap_wait(enum ap_wait wait)
void ap_request_timeout(struct timer_list *t)
static enum hrtimer_restart ap_poll_timeout(struct hrtimer *unused)
static void ap_interrupt_handler(struct airq_struct *airq)
static void ap_tasklet_fn(unsigned long dummy)
static int ap_pending_requests(void)
static int ap_poll_thread(void *data)
static int ap_poll_thread_start(void)
static void ap_poll_thread_stop(void)
static int ap_bus_match(struct device *dev, struct device_driver *drv)
static int ap_uevent(struct device *dev, struct kobj_uevent_env *env)
static int ap_dev_suspend(struct device *dev)
static int ap_dev_resume(struct device *dev)
static void ap_bus_suspend(void)
static int __ap_card_devices_unregister(struct device *dev, void *dummy)
static int __ap_queue_devices_unregister(struct device *dev, void *dummy)
static int __ap_queue_devices_with_id_unregister(struct device *dev, void *data)
static void ap_bus_resume(void)
static int ap_power_event(struct notifier_block *this, unsigned long event, void *ptr)
static int __ap_revise_reserved(struct device *dev, void *dummy)
static void ap_bus_revise_bindings(void)
int ap_owned_by_def_drv(int card, int queue)
int ap_apqn_in_matrix_owned_by_def_drv(unsigned long *apm, unsigned long *aqm)
static int ap_device_probe(struct device *dev)
static int ap_device_remove(struct device *dev)
int ap_driver_register(struct ap_driver *ap_drv, struct module *owner, char *name)
void ap_driver_unregister(struct ap_driver *ap_drv)
void ap_bus_force_rescan(void)
static int hex2bitmap(const char *str, unsigned long *bitmap, int bits)
static int modify_bitmap(const char *str, unsigned long *bitmap, int bits)
int ap_parse_mask_str(const char *str, unsigned long *bitmap, int bits, struct mutex *lock)
static ssize_t ap_domain_show(struct bus_type *bus, char *buf)
static ssize_t ap_domain_store(struct bus_type *bus, const char *buf, size_t count)
static ssize_t ap_control_domain_mask_show(struct bus_type *bus, char *buf)
static ssize_t ap_usage_domain_mask_show(struct bus_type *bus, char *buf)
static ssize_t ap_adapter_mask_show(struct bus_type *bus, char *buf)
static ssize_t ap_interrupts_show(struct bus_type *bus, char *buf)
static ssize_t config_time_show(struct bus_type *bus, char *buf)
static ssize_t config_time_store(struct bus_type *bus, const char *buf, size_t count)
static ssize_t poll_thread_show(struct bus_type *bus, char *buf)
static ssize_t poll_thread_store(struct bus_type *bus, const char *buf, size_t count)
static ssize_t poll_timeout_show(struct bus_type *bus, char *buf)
static ssize_t poll_timeout_store(struct bus_type *bus, const char *buf, size_t count)
static ssize_t ap_max_domain_id_show(struct bus_type *bus, char *buf)
static ssize_t apmask_show(struct bus_type *bus, char *buf)
static ssize_t apmask_store(struct bus_type *bus, const char *buf, size_t count)
static ssize_t aqmask_show(struct bus_type *bus, char *buf)
static ssize_t aqmask_store(struct bus_type *bus, const char *buf, size_t count)
static void ap_select_domain(void)
static int ap_get_compatible_type(ap_qid_t qid, int rawtype, unsigned int func)
static int __match_card_device_with_id(struct device *dev, void *data)
static int __match_queue_device_with_qid(struct device *dev, void *data)
static void _ap_scan_bus_adapter(int id)
static void ap_scan_bus(struct work_struct *unused)
static void ap_config_timeout(struct timer_list *unused)
static int __init ap_debug_init(void)
static void __init ap_perms_init(void)
static int __init ap_module_init(void)
\n
     18 void
     17 struct bus_type *bus
     12 struct device *dev
     11 char *buf
      6 size_t count
      6 const char *buf
      4 void *data
      3 void *dummy
      3 unsigned long *bitmap
      3 int bits
      3 const char *str
      2 struct ap_driver *ap_drv
      2 ap_qid_t qid
      1 void *ptr
      1 unsigned long event
      1 unsigned long dummy
      1 unsigned long *aqm
      1 unsigned long *apm
      1 unsigned int nr
      1 unsigned int id
      1 unsigned int func
      1 unsigned int *field
      1 unsigned int *facilities
      1 unsigned int domain
      1 struct work_struct *unused
      1 struct timer_list *unused
      1 struct timer_list *t
      1 struct notifier_block *this
      1 struct mutex *lock
      1 struct module *owner
      1 struct kobj_uevent_env *env
      1 struct hrtimer *unused
      1 struct device_driver *drv
      1 struct ap_config_info *info
      1 struct airq_struct *airq
      1 int rawtype
      1 int *queue_depth
      1 int queue
      1 int id
      1 int *device_type
      1 int card
      1 enum ap_wait wait
      1 char *name
