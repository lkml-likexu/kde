
static inline bool vfio_vga_disabled(void)
static unsigned int vfio_pci_set_vga_decode(void *opaque, bool single_vga)
static inline bool vfio_pci_is_vga(struct pci_dev *pdev)
static void vfio_pci_probe_mmaps(struct vfio_pci_device *vdev)
static bool vfio_pci_nointx(struct pci_dev *pdev)
static int vfio_pci_enable(struct vfio_pci_device *vdev)
static void vfio_pci_disable(struct vfio_pci_device *vdev)
static void vfio_pci_release(void *device_data)
static int vfio_pci_open(void *device_data)
static int vfio_pci_get_irq_count(struct vfio_pci_device *vdev, int irq_type)
static int vfio_pci_count_devs(struct pci_dev *pdev, void *data)
static int vfio_pci_fill_devs(struct pci_dev *pdev, void *data)
static int vfio_pci_validate_devs(struct pci_dev *pdev, void *data)
static bool vfio_pci_dev_below_slot(struct pci_dev *pdev, struct pci_slot *slot)
static int vfio_pci_walk_wrapper(struct pci_dev *pdev, void *data)
static int vfio_pci_for_each_slot_or_bus(struct pci_dev *pdev, int (*fn)
(struct pci_dev *, void *data)
, void *data, bool slot)
static int msix_mmappable_cap(struct vfio_pci_device *vdev, struct vfio_info_cap *caps)
int vfio_pci_register_dev_region(struct vfio_pci_device *vdev, unsigned int type, unsigned int subtype, const struct vfio_pci_regops *ops, size_t size, u32 flags, void *data)
static long vfio_pci_ioctl(void *device_data, unsigned int cmd, unsigned long arg)
static ssize_t vfio_pci_rw(void *device_data, char __user *buf, size_t count, loff_t *ppos, bool iswrite)
static ssize_t vfio_pci_read(void *device_data, char __user *buf, size_t count, loff_t *ppos)
static ssize_t vfio_pci_write(void *device_data, const char __user *buf, size_t count, loff_t *ppos)
static int vfio_pci_mmap(void *device_data, struct vm_area_struct *vma)
static void vfio_pci_request(void *device_data, unsigned int count)
static int vfio_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
static void vfio_pci_remove(struct pci_dev *pdev)
static pci_ers_result_t vfio_pci_aer_err_detected(struct pci_dev *pdev, pci_channel_state_t state)
static int vfio_pci_get_devs(struct pci_dev *pdev, void *data)
static void vfio_pci_try_bus_reset(struct vfio_pci_device *vdev)
static void __exit vfio_pci_cleanup(void)
static void __init vfio_pci_fill_ids(void)
static int __init vfio_pci_init(void)
  12 struct pci_dev *pdev
   8 void *device_data
   7 void *data
   7 struct vfio_pci_device *vdev
   4 void
   3 size_t count
   3 loff_t *ppos
   2 char __user *buf
   1 void *opaque
   1 unsigned long arg
   1 unsigned int type
   1 unsigned int subtype
   1 unsigned int count
   1 unsigned int cmd
   1 u32 flags
   1 struct vm_area_struct *vma
   1 struct vfio_info_cap *caps
   1 struct pci_slot *slot
   1 struct pci_dev *
   1 size_t size
   1 pci_channel_state_t state
   1 int irq_type
   1 int *fn
   1 const struct vfio_pci_regops *ops
   1 const struct pci_device_id *id
   1 const char __user *buf
   1 bool single_vga
   1 bool iswrite
