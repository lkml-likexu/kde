
static void vfio_send_intx_eventfd(void *opaque, void *unused)
void vfio_pci_intx_mask(struct vfio_pci_device *vdev)
static int vfio_pci_intx_unmask_handler(void *opaque, void *unused)
void vfio_pci_intx_unmask(struct vfio_pci_device *vdev)
static irqreturn_t vfio_intx_handler(int irq, void *dev_id)
static int vfio_intx_enable(struct vfio_pci_device *vdev)
static int vfio_intx_set_signal(struct vfio_pci_device *vdev, int fd)
static void vfio_intx_disable(struct vfio_pci_device *vdev)
static irqreturn_t vfio_msihandler(int irq, void *arg)
static int vfio_msi_enable(struct vfio_pci_device *vdev, int nvec, bool msix)
static int vfio_msi_set_vector_signal(struct vfio_pci_device *vdev, int vector, int fd, bool msix)
static int vfio_msi_set_block(struct vfio_pci_device *vdev, unsigned start, unsigned count, int32_t *fds, bool msix)
static void vfio_msi_disable(struct vfio_pci_device *vdev, bool msix)
static int vfio_pci_set_intx_unmask(struct vfio_pci_device *vdev, unsigned index, unsigned start, unsigned count, uint32_t flags, void *data)
static int vfio_pci_set_intx_mask(struct vfio_pci_device *vdev, unsigned index, unsigned start, unsigned count, uint32_t flags, void *data)
static int vfio_pci_set_intx_trigger(struct vfio_pci_device *vdev, unsigned index, unsigned start, unsigned count, uint32_t flags, void *data)
static int vfio_pci_set_msi_trigger(struct vfio_pci_device *vdev, unsigned index, unsigned start, unsigned count, uint32_t flags, void *data)
static int vfio_pci_set_ctx_trigger_single(struct eventfd_ctx **ctx, unsigned int count, uint32_t flags, void *data)
static int vfio_pci_set_err_trigger(struct vfio_pci_device *vdev, unsigned index, unsigned start, unsigned count, uint32_t flags, void *data)
static int vfio_pci_set_req_trigger(struct vfio_pci_device *vdev, unsigned index, unsigned start, unsigned count, uint32_t flags, void *data)
int vfio_pci_set_irqs_ioctl(struct vfio_pci_device *vdev, uint32_t flags, unsigned index, unsigned start, unsigned count, void *data)
  16 struct vfio_pci_device *vdev
   8 void *data
   8 unsigned start
   8 unsigned count
   8 uint32_t flags
   7 unsigned index
   4 bool msix
   2 void *unused
   2 void *opaque
   2 int irq
   2 int fd
   1 void *dev_id
   1 void *arg
   1 unsigned int count
   1 struct eventfd_ctx **ctx
   1 int32_t *fds
   1 int vector
   1 int nvec
