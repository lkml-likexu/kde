
\n
static int vfio_ccw_mdev_reset(struct mdev_device *mdev)
static int vfio_ccw_mdev_notifier(struct notifier_block *nb, unsigned long action, void *data)
static ssize_t name_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t device_api_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t available_instances_show(struct kobject *kobj, struct device *dev, char *buf)
static int vfio_ccw_mdev_create(struct kobject *kobj, struct mdev_device *mdev)
static int vfio_ccw_mdev_remove(struct mdev_device *mdev)
static int vfio_ccw_mdev_open(struct mdev_device *mdev)
static void vfio_ccw_mdev_release(struct mdev_device *mdev)
static ssize_t vfio_ccw_mdev_read(struct mdev_device *mdev, char __user *buf, size_t count, loff_t *ppos)
static ssize_t vfio_ccw_mdev_write(struct mdev_device *mdev, const char __user *buf, size_t count, loff_t *ppos)
static int vfio_ccw_mdev_get_device_info(struct vfio_device_info *info)
static int vfio_ccw_mdev_get_region_info(struct vfio_region_info *info, u16 *cap_type_id, void **cap_type)
static int vfio_ccw_mdev_get_irq_info(struct vfio_irq_info *info)
static int vfio_ccw_mdev_set_irqs(struct mdev_device *mdev, uint32_t flags, void __user *data)
static ssize_t vfio_ccw_mdev_ioctl(struct mdev_device *mdev, unsigned int cmd, unsigned long arg)
int vfio_ccw_mdev_reg(struct subchannel *sch)
void vfio_ccw_mdev_unreg(struct subchannel *sch)
\n
      9 struct mdev_device *mdev
      4 struct kobject *kobj
      3 struct device *dev
      3 char *buf
      2 struct subchannel *sch
      2 size_t count
      2 loff_t *ppos
      1 void __user *data
      1 void *data
      1 void **cap_type
      1 unsigned long arg
      1 unsigned long action
      1 unsigned int cmd
      1 uint32_t flags
      1 u16 *cap_type_id
      1 struct vfio_region_info *info
      1 struct vfio_irq_info *info
      1 struct vfio_device_info *info
      1 struct notifier_block *nb
      1 const char __user *buf
      1 char __user *buf
