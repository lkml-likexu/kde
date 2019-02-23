
\n
static void vfio_ap_matrix_init(struct ap_config_info *info, struct ap_matrix *matrix)
static int vfio_ap_mdev_create(struct kobject *kobj, struct mdev_device *mdev)
static int vfio_ap_mdev_remove(struct mdev_device *mdev)
static ssize_t name_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t available_instances_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t device_api_show(struct kobject *kobj, struct device *dev, char *buf)
static int vfio_ap_has_queue(struct device *dev, void *data)
static int vfio_ap_verify_queue_reserved(unsigned long *apid, unsigned long *apqi)
static int vfio_ap_mdev_verify_queues_reserved_for_apid(struct ap_matrix_mdev *matrix_mdev, unsigned long apid)
static int vfio_ap_mdev_verify_no_sharing(struct ap_matrix_mdev *matrix_mdev)
static ssize_t assign_adapter_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t unassign_adapter_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static int vfio_ap_mdev_verify_queues_reserved_for_apqi(struct ap_matrix_mdev *matrix_mdev, unsigned long apqi)
static ssize_t assign_domain_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t unassign_domain_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t assign_control_domain_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t unassign_control_domain_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t control_domains_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
static ssize_t matrix_show(struct device *dev, struct device_attribute *attr, char *buf)
static int vfio_ap_mdev_set_kvm(struct ap_matrix_mdev *matrix_mdev, struct kvm *kvm)
static int vfio_ap_mdev_group_notifier(struct notifier_block *nb, unsigned long action, void *data)
static int vfio_ap_mdev_reset_queue(unsigned int apid, unsigned int apqi, unsigned int retry)
static int vfio_ap_mdev_reset_queues(struct mdev_device *mdev)
static int vfio_ap_mdev_open(struct mdev_device *mdev)
static void vfio_ap_mdev_release(struct mdev_device *mdev)
static int vfio_ap_mdev_get_device_info(unsigned long arg)
static ssize_t vfio_ap_mdev_ioctl(struct mdev_device *mdev, unsigned int cmd, unsigned long arg)
int vfio_ap_mdev_register(void)
void vfio_ap_mdev_unregister(void)
\n
     12 struct device *dev
      7 struct device_attribute *attr
      6 struct mdev_device *mdev
      6 size_t count
      6 const char *buf
      5 char *buf
      4 struct kobject *kobj
      4 struct ap_matrix_mdev *matrix_mdev
      2 void *data
      2 void
      2 unsigned long arg
      1 unsigned long *apqi
      1 unsigned long apqi
      1 unsigned long *apid
      1 unsigned long apid
      1 unsigned long action
      1 unsigned int retry
      1 unsigned int cmd
      1 unsigned int apqi
      1 unsigned int apid
      1 struct notifier_block *nb
      1 struct kvm *kvm
      1 struct device_attribute *dev_attr
      1 struct ap_matrix *matrix
      1 struct ap_config_info *info
