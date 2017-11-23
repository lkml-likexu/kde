
static const struct mdpy_type *mdpy_find_type(struct kobject *kobj)
static void mdpy_create_config_space(struct mdev_state *mdev_state)
static void handle_pci_cfg_write(struct mdev_state *mdev_state, u16 offset, char *buf, u32 count)
static ssize_t mdev_access(struct mdev_device *mdev, char *buf, size_t count, loff_t pos, bool is_write)
static int mdpy_reset(struct mdev_device *mdev)
static int mdpy_create(struct kobject *kobj, struct mdev_device *mdev)
static int mdpy_remove(struct mdev_device *mdev)
static ssize_t mdpy_read(struct mdev_device *mdev, char __user *buf, size_t count, loff_t *ppos)
static ssize_t mdpy_write(struct mdev_device *mdev, const char __user *buf, size_t count, loff_t *ppos)
static int mdpy_mmap(struct mdev_device *mdev, struct vm_area_struct *vma)
static int mdpy_get_region_info(struct mdev_device *mdev, struct vfio_region_info *region_info, u16 *cap_type_id, void **cap_type)
static int mdpy_get_irq_info(struct mdev_device *mdev, struct vfio_irq_info *irq_info)
static int mdpy_get_device_info(struct mdev_device *mdev, struct vfio_device_info *dev_info)
static int mdpy_query_gfx_plane(struct mdev_device *mdev, struct vfio_device_gfx_plane_info *plane)
static long mdpy_ioctl(struct mdev_device *mdev, unsigned int cmd, unsigned long arg)
static int mdpy_open(struct mdev_device *mdev)
static void mdpy_close(struct mdev_device *mdev)
static ssize_t resolution_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t name_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t description_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t available_instances_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t device_api_show(struct kobject *kobj, struct device *dev, char *buf)
static void mdpy_device_release(struct device *dev)
static int __init mdpy_dev_init(void)
static void __exit mdpy_dev_exit(void)
  14 struct mdev_device *mdev
   7 char *buf
   6 struct kobject *kobj
   6 struct device *dev
   3 size_t count
   2 void
   2 struct mdev_state *mdev_state
   2 loff_t *ppos
   1 void **cap_type
   1 unsigned long arg
   1 unsigned int cmd
   1 u32 count
   1 u16 offset
   1 u16 *cap_type_id
   1 struct vm_area_struct *vma
   1 struct vfio_region_info *region_info
   1 struct vfio_irq_info *irq_info
   1 struct vfio_device_info *dev_info
   1 struct vfio_device_gfx_plane_info *plane
   1 struct device_attribute *attr
   1 loff_t pos
   1 const char __user *buf
   1 char __user *buf
   1 bool is_write
