
\n
static ssize_t do_io_rw(void __iomem *io, char __user *buf, loff_t off, size_t count, size_t x_start, size_t x_end, bool iswrite)
static int vfio_pci_setup_barmap(struct vfio_pci_device *vdev, int bar)
ssize_t vfio_pci_bar_rw(struct vfio_pci_device *vdev, char __user *buf, size_t count, loff_t *ppos, bool iswrite)
ssize_t vfio_pci_vga_rw(struct vfio_pci_device *vdev, char __user *buf, size_t count, loff_t *ppos, bool iswrite)
static int vfio_pci_ioeventfd_handler(void *opaque, void *unused)
long vfio_pci_ioeventfd(struct vfio_pci_device *vdev, loff_t offset, uint64_t data, int count, int fd)
\n
      4 struct vfio_pci_device *vdev
      3 size_t count
      3 char __user *buf
      3 bool iswrite
      2 loff_t *ppos
      1 void *unused
      1 void *opaque
      1 void __iomem *io
      1 uint64_t data
      1 size_t x_start
      1 size_t x_end
      1 loff_t offset
      1 loff_t off
      1 int fd
      1 int count
      1 int bar
