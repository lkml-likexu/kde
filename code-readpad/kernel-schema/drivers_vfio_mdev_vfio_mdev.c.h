
\n
static int vfio_mdev_open(void *device_data)
static void vfio_mdev_release(void *device_data)
static long vfio_mdev_unlocked_ioctl(void *device_data, unsigned int cmd, unsigned long arg)
static ssize_t vfio_mdev_read(void *device_data, char __user *buf, size_t count, loff_t *ppos)
static ssize_t vfio_mdev_write(void *device_data, const char __user *buf, size_t count, loff_t *ppos)
static int vfio_mdev_mmap(void *device_data, struct vm_area_struct *vma)
static int vfio_mdev_probe(struct device *dev)
static void vfio_mdev_remove(struct device *dev)
static int __init vfio_mdev_init(void)
static void __exit vfio_mdev_exit(void)
\n
      6 void *device_data
      2 void
      2 struct device *dev
      2 size_t count
      2 loff_t *ppos
      1 unsigned long arg
      1 unsigned int cmd
      1 struct vm_area_struct *vma
      1 const char __user *buf
      1 char __user *buf
