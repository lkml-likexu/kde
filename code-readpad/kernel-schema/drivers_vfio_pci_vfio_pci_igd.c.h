
\n
static size_t vfio_pci_igd_rw(struct vfio_pci_device *vdev, char __user *buf, size_t count, loff_t *ppos, bool iswrite)
static void vfio_pci_igd_release(struct vfio_pci_device *vdev, struct vfio_pci_region *region)
static int vfio_pci_igd_opregion_init(struct vfio_pci_device *vdev)
static size_t vfio_pci_igd_cfg_rw(struct vfio_pci_device *vdev, char __user *buf, size_t count, loff_t *ppos, bool iswrite)
static void vfio_pci_igd_cfg_release(struct vfio_pci_device *vdev, struct vfio_pci_region *region)
static int vfio_pci_igd_cfg_init(struct vfio_pci_device *vdev)
int vfio_pci_igd_init(struct vfio_pci_device *vdev)
\n
      7 struct vfio_pci_device *vdev
      2 struct vfio_pci_region *region
      2 size_t count
      2 loff_t *ppos
      2 char __user *buf
      2 bool iswrite
