
EXPORT_SYMBOL_GPL(vfio_platform_probe_common);
EXPORT_SYMBOL_GPL(vfio_platform_remove_common);
EXPORT_SYMBOL_GPL(__vfio_platform_register_reset);
EXPORT_SYMBOL_GPL(vfio_platform_unregister_reset);
\n
static vfio_platform_reset_fn_t vfio_platform_lookup_reset(const char *compat, struct module **module)
static int vfio_platform_acpi_probe(struct vfio_platform_device *vdev, struct device *dev)
static int vfio_platform_acpi_call_reset(struct vfio_platform_device *vdev, const char **extra_dbg)
static bool vfio_platform_acpi_has_reset(struct vfio_platform_device *vdev)
static bool vfio_platform_has_reset(struct vfio_platform_device *vdev)
static int vfio_platform_get_reset(struct vfio_platform_device *vdev)
static void vfio_platform_put_reset(struct vfio_platform_device *vdev)
static int vfio_platform_regions_init(struct vfio_platform_device *vdev)
static void vfio_platform_regions_cleanup(struct vfio_platform_device *vdev)
static int vfio_platform_call_reset(struct vfio_platform_device *vdev, const char **extra_dbg)
static void vfio_platform_release(void *device_data)
static int vfio_platform_open(void *device_data)
static long vfio_platform_ioctl(void *device_data, unsigned int cmd, unsigned long arg)
static ssize_t vfio_platform_read_mmio(struct vfio_platform_region *reg, char __user *buf, size_t count, loff_t off)
static ssize_t vfio_platform_read(void *device_data, char __user *buf, size_t count, loff_t *ppos)
static ssize_t vfio_platform_write_mmio(struct vfio_platform_region *reg, const char __user *buf, size_t count, loff_t off)
static ssize_t vfio_platform_write(void *device_data, const char __user *buf, size_t count, loff_t *ppos)
static int vfio_platform_mmap_mmio(struct vfio_platform_region region, struct vm_area_struct *vma)
static int vfio_platform_mmap(void *device_data, struct vm_area_struct *vma)
static int vfio_platform_of_probe(struct vfio_platform_device *vdev, struct device *dev)
int vfio_platform_probe_common(struct vfio_platform_device *vdev, struct device *dev)
struct vfio_platform_device *vfio_platform_remove_common(struct device *dev)
void __vfio_platform_register_reset(struct vfio_platform_reset_node *node)
void vfio_platform_unregister_reset(const char *compat, vfio_platform_reset_fn_t fn)
\n
     11 struct vfio_platform_device *vdev
      6 void *device_data
      4 struct device *dev
      4 size_t count
      2 struct vm_area_struct *vma
      2 struct vfio_platform_region *reg
      2 loff_t *ppos
      2 loff_t off
      2 const char __user *buf
      2 const char **extra_dbg
      2 const char *compat
      2 char __user *buf
      1 vfio_platform_unregister_reset
      1 vfio_platform_reset_fn_t fn
      1 vfio_platform_remove_common
      1 __vfio_platform_register_reset
      1 vfio_platform_probe_common
      1 unsigned long arg
      1 unsigned int cmd
      1 struct vfio_platform_reset_node *node
      1 struct vfio_platform_region region
      1 struct module **module
