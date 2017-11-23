
static struct mdev_state *find_mdev_state_by_uuid(uuid_le uuid)
void dump_buffer(char *buf, uint32_t count)
static void mtty_create_config_space(struct mdev_state *mdev_state)
static void handle_pci_cfg_write(struct mdev_state *mdev_state, u16 offset, char *buf, u32 count)
static void handle_bar_write(unsigned int index, struct mdev_state *mdev_state, u16 offset, char *buf, u32 count)
static void handle_bar_read(unsigned int index, struct mdev_state *mdev_state, u16 offset, char *buf, u32 count)
static void mdev_read_base(struct mdev_state *mdev_state)
static ssize_t mdev_access(struct mdev_device *mdev, char *buf, size_t count, loff_t pos, bool is_write)
int mtty_create(struct kobject *kobj, struct mdev_device *mdev)
int mtty_remove(struct mdev_device *mdev)
int mtty_reset(struct mdev_device *mdev)
ssize_t mtty_read(struct mdev_device *mdev, char __user *buf, size_t count, loff_t *ppos)
ssize_t mtty_write(struct mdev_device *mdev, const char __user *buf, size_t count, loff_t *ppos)
static int mtty_set_irqs(struct mdev_device *mdev, uint32_t flags, unsigned int index, unsigned int start, unsigned int count, void *data)
static int mtty_trigger_interrupt(uuid_le uuid)
int mtty_get_region_info(struct mdev_device *mdev, struct vfio_region_info *region_info, u16 *cap_type_id, void **cap_type)
int mtty_get_irq_info(struct mdev_device *mdev, struct vfio_irq_info *irq_info)
int mtty_get_device_info(struct mdev_device *mdev, struct vfio_device_info *dev_info)
static long mtty_ioctl(struct mdev_device *mdev, unsigned int cmd, unsigned long arg)
int mtty_open(struct mdev_device *mdev)
void mtty_close(struct mdev_device *mdev)
static ssize_t sample_mtty_dev_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t sample_mdev_dev_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t name_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t available_instances_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t device_api_show(struct kobject *kobj, struct device *dev, char *buf)
static void mtty_device_release(struct device *dev)
static int __init mtty_dev_init(void)
static void __exit mtty_dev_exit(void)
  13 struct mdev_device *mdev
  10 char *buf
   6 struct device *dev
   5 struct mdev_state *mdev_state
   4 struct kobject *kobj
   3 unsigned int index
   3 u32 count
   3 u16 offset
   3 size_t count
   2 void
   2 uuid_le uuid
   2 struct device_attribute *attr
   2 loff_t *ppos
   1 void *data
   1 void **cap_type
   1 unsigned long arg
   1 unsigned int start
   1 unsigned int count
   1 unsigned int cmd
   1 uint32_t flags
   1 uint32_t count
   1 u16 *cap_type_id
   1 struct vfio_region_info *region_info
   1 struct vfio_irq_info *irq_info
   1 struct vfio_device_info *dev_info
   1 loff_t pos
   1 const char __user *buf
   1 char __user *buf
   1 bool is_write
