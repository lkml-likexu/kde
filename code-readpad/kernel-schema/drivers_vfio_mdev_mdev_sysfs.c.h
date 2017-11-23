
static ssize_t mdev_type_attr_show(struct kobject *kobj, struct attribute *__attr, char *buf)
static ssize_t mdev_type_attr_store(struct kobject *kobj, struct attribute *__attr, const char *buf, size_t count)
static ssize_t create_store(struct kobject *kobj, struct device *dev, const char *buf, size_t count)
static void mdev_type_release(struct kobject *kobj)
struct mdev_type *add_mdev_supported_type(struct mdev_parent *parent, struct attribute_group *group)
static void remove_mdev_supported_type(struct mdev_type *type)
static int add_mdev_supported_type_groups(struct mdev_parent *parent)
void parent_remove_sysfs_files(struct mdev_parent *parent)
int parent_create_sysfs_files(struct mdev_parent *parent)
static ssize_t remove_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
intmdev_create_sysfs_files(struct device *dev, struct mdev_type *type)
void mdev_remove_sysfs_files(struct device *dev, struct mdev_type *type)
   4 struct mdev_parent *parent
   4 struct kobject *kobj
   4 struct device *dev
   3 struct mdev_type *type
   3 size_t count
   3 const char *buf
   2 struct attribute *__attr
   1 struct device_attribute *attr
   1 struct attribute_group *group
   1 char *buf
