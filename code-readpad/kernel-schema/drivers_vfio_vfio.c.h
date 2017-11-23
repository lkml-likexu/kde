
EXPORT_SYMBOL_GPL(vfio_iommu_group_get);
EXPORT_SYMBOL_GPL(vfio_iommu_group_put);
EXPORT_SYMBOL_GPL(vfio_register_iommu_driver);
EXPORT_SYMBOL_GPL(vfio_unregister_iommu_driver);
EXPORT_SYMBOL_GPL(vfio_device_put);
EXPORT_SYMBOL_GPL(vfio_add_group_dev);
EXPORT_SYMBOL_GPL(vfio_device_get_from_dev);
EXPORT_SYMBOL_GPL(vfio_device_data);
EXPORT_SYMBOL_GPL(vfio_del_group_dev);
EXPORT_SYMBOL_GPL(vfio_group_get_external_user);
EXPORT_SYMBOL_GPL(vfio_group_put_external_user);
EXPORT_SYMBOL_GPL(vfio_external_group_match_file);
EXPORT_SYMBOL_GPL(vfio_external_user_iommu_id);
EXPORT_SYMBOL_GPL(vfio_external_check_extension);
EXPORT_SYMBOL_GPL(vfio_info_cap_add);
EXPORT_SYMBOL_GPL(vfio_group_set_kvm);
struct iommu_group *vfio_iommu_group_get(struct device *dev)
void vfio_iommu_group_put(struct iommu_group *group, struct device *dev)
static void *vfio_noiommu_open(unsigned long arg)
static void vfio_noiommu_release(void *iommu_data)
static long vfio_noiommu_ioctl(void *iommu_data, unsigned int cmd, unsigned long arg)
static int vfio_noiommu_attach_group(void *iommu_data, struct iommu_group *iommu_group)
static void vfio_noiommu_detach_group(void *iommu_data, struct iommu_group *iommu_group)
int vfio_register_iommu_driver(const struct vfio_iommu_driver_ops *ops)
void vfio_unregister_iommu_driver(const struct vfio_iommu_driver_ops *ops)
static int vfio_alloc_group_minor(struct vfio_group *group)
static void vfio_free_group_minor(int minor)
static void vfio_container_get(struct vfio_container *container)
static void vfio_container_release(struct kref *kref)
static void vfio_container_put(struct vfio_container *container)
static void vfio_group_unlock_and_free(struct vfio_group *group)
static struct vfio_group *vfio_create_group(struct iommu_group *iommu_group)
static void vfio_group_release(struct kref *kref)
static void vfio_group_put(struct vfio_group *group)
static void vfio_group_put_bg(struct work_struct *work)
static void vfio_group_schedule_put(struct vfio_group *group)
static void vfio_group_get(struct vfio_group *group)
static struct vfio_group *vfio_group_try_get(struct vfio_group *group)
static struct vfio_group *vfio_group_get_from_iommu(struct iommu_group *iommu_group)
static struct vfio_group *vfio_group_get_from_minor(int minor)
static struct vfio_group *vfio_group_get_from_dev(struct device *dev)
static struct vfio_device *vfio_group_create_device(struct vfio_group *group, struct device *dev, const struct vfio_device_ops *ops, void *device_data)
static void vfio_device_release(struct kref *kref)
void vfio_device_put(struct vfio_device *device)
static void vfio_device_get(struct vfio_device *device)
static struct vfio_device *vfio_group_get_device(struct vfio_group *group, struct device *dev)
static bool vfio_dev_whitelisted(struct device *dev, struct device_driver *drv)
static int vfio_dev_viable(struct device *dev, void *data)
static int vfio_group_nb_add_dev(struct vfio_group *group, struct device *dev)
static int vfio_group_nb_verify(struct vfio_group *group, struct device *dev)
static int vfio_iommu_group_notifier(struct notifier_block *nb, unsigned long action, void *data)
int vfio_add_group_dev(struct device *dev, const struct vfio_device_ops *ops, void *device_data)
struct vfio_device *vfio_device_get_from_dev(struct device *dev)
static struct vfio_device *vfio_device_get_from_name(struct vfio_group *group, char *buf)
void *vfio_device_data(struct vfio_device *device)
static bool vfio_dev_present(struct vfio_group *group, struct device *dev)
void *vfio_del_group_dev(struct device *dev)
static long vfio_ioctl_check_extension(struct vfio_container *container, unsigned long arg)
static int __vfio_container_attach_groups(struct vfio_container *container, struct vfio_iommu_driver *driver, void *data)
static long vfio_ioctl_set_iommu(struct vfio_container *container, unsigned long arg)
static long vfio_fops_unl_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
static long vfio_fops_compat_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
static int vfio_fops_open(struct inode *inode, struct file *filep)
static int vfio_fops_release(struct inode *inode, struct file *filep)
static ssize_t vfio_fops_read(struct file *filep, char __user *buf, size_t count, loff_t *ppos)
static ssize_t vfio_fops_write(struct file *filep, const char __user *buf, size_t count, loff_t *ppos)
static int vfio_fops_mmap(struct file *filep, struct vm_area_struct *vma)
static void __vfio_group_unset_container(struct vfio_group *group)
static int vfio_group_unset_container(struct vfio_group *group)
static void vfio_group_try_dissolve_container(struct vfio_group *group)
static int vfio_group_set_container(struct vfio_group *group, int container_fd)
static bool vfio_group_viable(struct vfio_group *group)
static int vfio_group_add_container_user(struct vfio_group *group)
static int vfio_group_get_device_fd(struct vfio_group *group, char *buf)
static long vfio_group_fops_unl_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
static long vfio_group_fops_compat_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
static int vfio_group_fops_open(struct inode *inode, struct file *filep)
static int vfio_group_fops_release(struct inode *inode, struct file *filep)
static int vfio_device_fops_release(struct inode *inode, struct file *filep)
static long vfio_device_fops_unl_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
static ssize_t vfio_device_fops_read(struct file *filep, char __user *buf, size_t count, loff_t *ppos)
static ssize_t vfio_device_fops_write(struct file *filep, const char __user *buf, size_t count, loff_t *ppos)
static int vfio_device_fops_mmap(struct file *filep, struct vm_area_struct *vma)
static long vfio_device_fops_compat_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
struct vfio_group *vfio_group_get_external_user(struct file *filep)
void vfio_group_put_external_user(struct vfio_group *group)
bool vfio_external_group_match_file(struct vfio_group *test_group, struct file *filep)
int vfio_external_user_iommu_id(struct vfio_group *group)
long vfio_external_check_extension(struct vfio_group *group, unsigned long arg)
struct vfio_info_cap_header *vfio_info_cap_add(struct vfio_info_cap *caps, size_t size, u16 id, u16 version)
void vfio_info_cap_shift(struct vfio_info_cap *caps, size_t offset)
int vfio_info_add_capability(struct vfio_info_cap *caps, struct vfio_info_cap_header *cap, size_t size)
int vfio_set_irqs_validate_and_prepare(struct vfio_irq_set *hdr, int num_irqs, int max_irq_type, size_t *data_size)
int vfio_pin_pages(struct device *dev, unsigned long *user_pfn, int npage, int prot, unsigned long *phys_pfn)
int vfio_unpin_pages(struct device *dev, unsigned long *user_pfn, int npage)
static int vfio_register_iommu_notifier(struct vfio_group *group, unsigned long *events, struct notifier_block *nb)
static int vfio_unregister_iommu_notifier(struct vfio_group *group, struct notifier_block *nb)
void vfio_group_set_kvm(struct vfio_group *group, struct kvm *kvm)
static int vfio_register_group_notifier(struct vfio_group *group, unsigned long *events, struct notifier_block *nb)
static int vfio_unregister_group_notifier(struct vfio_group *group, struct notifier_block *nb)
int vfio_register_notifier(struct device *dev, enum vfio_notify_type type, unsigned long *events, struct notifier_block *nb)
int vfio_unregister_notifier(struct device *dev, enum vfio_notify_type type, struct notifier_block *nb)
static char *vfio_devnode(struct device *dev, umode_t *mode)
static int __init vfio_init(void)
static void __exit vfio_cleanup(void)
  27 struct vfio_group *group
  19 struct file *filep
  18 struct device *dev
  11 unsigned long arg
   7 unsigned int cmd
   7 struct notifier_block *nb
   5 struct vfio_container *container
   5 struct inode *inode
   4 void *iommu_data
   4 struct iommu_group *iommu_group
   4 size_t count
   4 loff_t *ppos
   3 void *data
   3 unsigned long *events
   3 struct vfio_info_cap *caps
   3 struct vfio_device *device
   3 struct kref *kref
   2 void *device_data
   2 void
   2 unsigned long *user_pfn
   2 struct vm_area_struct *vma
   2 size_t size
   2 int npage
   2 int minor
   2 enum vfio_notify_type type
   2 const struct vfio_iommu_driver_ops *ops
   2 const struct vfio_device_ops *ops
   2 const char __user *buf
   2 char __user *buf
   2 char *buf
   1 vfio_unregister_iommu_driver
   1 vfio_register_iommu_driver
   1 vfio_iommu_group_put
   1 vfio_iommu_group_get
   1 vfio_info_cap_add
   1 vfio_group_set_kvm
   1 vfio_group_put_external_user
   1 vfio_group_get_external_user
   1 vfio_external_user_iommu_id
   1 vfio_external_group_match_file
   1 vfio_external_check_extension
   1 vfio_device_put
   1 vfio_device_get_from_dev
   1 vfio_device_data
   1 vfio_del_group_dev
   1 vfio_add_group_dev
   1 unsigned long action
   1 unsigned long *phys_pfn
   1 umode_t *mode
   1 u16 version
   1 u16 id
   1 struct work_struct *work
   1 struct vfio_irq_set *hdr
   1 struct vfio_iommu_driver *driver
   1 struct vfio_info_cap_header *cap
   1 struct vfio_group *test_group
   1 struct kvm *kvm
   1 struct iommu_group *group
   1 struct device_driver *drv
   1 size_t offset
   1 size_t *data_size
   1 int prot
   1 int num_irqs
   1 int max_irq_type
   1 int container_fd
