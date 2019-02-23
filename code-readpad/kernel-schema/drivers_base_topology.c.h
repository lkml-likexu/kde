
\n
define define_id_show_func(name)
\ static ssize_t name_show(struct device *dev, \ struct device_attribute *attr, char *buf)
\define define_siblings_show_map(name, mask)
\ static ssize_t name_show(struct device *dev, \ struct device_attribute *attr, char *buf)
\define define_siblings_show_list(name, mask)
\ static ssize_t name_list_show(struct device *dev, \ struct device_attribute *attr, \ char *buf)
\static int topology_add_dev(unsigned int cpu)
static int topology_remove_dev(unsigned int cpu)
static int topology_sysfs_init(void)
\n
      3 struct device *dev
      3 \ struct device_attribute *attr
      3 name
      2 unsigned int cpu
      2 mask
      2 char *buf
      1 void
      1 \ char *buf
