
EXPORT_SYMBOL_GPL(xen_store_evtchn);
EXPORT_SYMBOL_GPL(xen_store_interface);
EXPORT_SYMBOL_GPL(xen_store_domain_type);
EXPORT_SYMBOL_GPL(xenbus_match);
EXPORT_SYMBOL_GPL(xenbus_read_otherend_details);
EXPORT_SYMBOL_GPL(xenbus_otherend_changed);
EXPORT_SYMBOL_GPL(xenbus_dev_probe);
EXPORT_SYMBOL_GPL(xenbus_dev_remove);
EXPORT_SYMBOL_GPL(xenbus_dev_shutdown);
EXPORT_SYMBOL_GPL(xenbus_register_driver_common);
EXPORT_SYMBOL_GPL(xenbus_unregister_driver);
EXPORT_SYMBOL_GPL(xenbus_dev_groups);
EXPORT_SYMBOL_GPL(xenbus_probe_node);
EXPORT_SYMBOL_GPL(xenbus_probe_devices);
EXPORT_SYMBOL_GPL(xenbus_dev_changed);
EXPORT_SYMBOL_GPL(xenbus_dev_suspend);
EXPORT_SYMBOL_GPL(xenbus_dev_resume);
EXPORT_SYMBOL_GPL(xenbus_dev_cancel);
EXPORT_SYMBOL_GPL(register_xenstore_notifier);
EXPORT_SYMBOL_GPL(unregister_xenstore_notifier);
EXPORT_SYMBOL_GPL(xenbus_probe);
\n
static const struct xenbus_device_id * match_device(const struct xenbus_device_id *arr, struct xenbus_device *dev)
int xenbus_match(struct device *_dev, struct device_driver *_drv)
static void free_otherend_details(struct xenbus_device *dev)
static void free_otherend_watch(struct xenbus_device *dev)
static int talk_to_otherend(struct xenbus_device *dev)
static int watch_otherend(struct xenbus_device *dev)
int xenbus_read_otherend_details(struct xenbus_device *xendev, char *id_node, char *path_node)
void xenbus_otherend_changed(struct xenbus_watch *watch, const char *path, const char *token, int ignore_on_shutdown)
int xenbus_dev_probe(struct device *_dev)
int xenbus_dev_remove(struct device *_dev)
void xenbus_dev_shutdown(struct device *_dev)
int xenbus_register_driver_common(struct xenbus_driver *drv, struct xen_bus_type *bus, struct module *owner, const char *mod_name)
void xenbus_unregister_driver(struct xenbus_driver *drv)
static int cmp_dev(struct device *dev, void *data)
static struct xenbus_device *xenbus_device_find(const char *nodename, struct bus_type *bus)
static int cleanup_dev(struct device *dev, void *data)
static void xenbus_cleanup_devices(const char *path, struct bus_type *bus)
static void xenbus_dev_release(struct device *dev)
static ssize_t nodename_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t devtype_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t modalias_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t state_show(struct device *dev, struct device_attribute *attr, char *buf)
int xenbus_probe_node(struct xen_bus_type *bus, const char *type, const char *nodename)
static int xenbus_probe_device_type(struct xen_bus_type *bus, const char *type)
int xenbus_probe_devices(struct xen_bus_type *bus)
static unsigned int char_count(const char *str, char c)
static int strsep_len(const char *str, char c, unsigned int len)
void xenbus_dev_changed(const char *node, struct xen_bus_type *bus)
int xenbus_dev_suspend(struct device *dev)
int xenbus_dev_resume(struct device *dev)
int xenbus_dev_cancel(struct device *dev)
int register_xenstore_notifier(struct notifier_block *nb)
void unregister_xenstore_notifier(struct notifier_block *nb)
void xenbus_probe(struct work_struct *unused)
static int __init xenbus_probe_initcall(void)
static int __init xenstored_local_init(void)
static int xenbus_resume_cb(struct notifier_block *nb, unsigned long action, void *data)
static int __init xenbus_init(void)
\n
     10 struct device *dev
      5 struct xen_bus_type *bus
      5 struct xenbus_device *dev
      4 struct device *_dev
      4 struct device_attribute *attr
      4 char *buf
      3 void *data
      3 void
      3 struct notifier_block *nb
      2 struct xenbus_driver *drv
      2 struct bus_type *bus
      2 const char *type
      2 const char *str
      2 const char *path
      2 const char *nodename
      2 char c
      1 xen_store_interface
      1 xen_store_evtchn
      1 xen_store_domain_type
      1 xenbus_unregister_driver
      1 xenbus_register_driver_common
      1 xenbus_read_otherend_details
      1 xenbus_probe_node
      1 xenbus_probe_devices
      1 xenbus_probe
      1 xenbus_otherend_changed
      1 xenbus_match
      1 xenbus_dev_suspend
      1 xenbus_dev_shutdown
      1 xenbus_dev_resume
      1 xenbus_dev_remove
      1 xenbus_dev_probe
      1 xenbus_dev_groups
      1 xenbus_dev_changed
      1 xenbus_dev_cancel
      1 unsigned long action
      1 unsigned int len
      1 unregister_xenstore_notifier
      1 struct xenbus_watch *watch
      1 struct xenbus_device *xendev
      1 struct work_struct *unused
      1 struct module *owner
      1 struct device_driver *_drv
      1 register_xenstore_notifier
      1 int ignore_on_shutdown
      1 const struct xenbus_device_id *arr
      1 const char *token
      1 const char *node
      1 const char *mod_name
      1 char *path_node
      1 char *id_node
