
static void vfio_platform_mask(struct vfio_platform_irq *irq_ctx)
static int vfio_platform_mask_handler(void *opaque, void *unused)
static int vfio_platform_set_irq_mask(struct vfio_platform_device *vdev, unsigned index, unsigned start, unsigned count, uint32_t flags, void *data)
static void vfio_platform_unmask(struct vfio_platform_irq *irq_ctx)
static int vfio_platform_unmask_handler(void *opaque, void *unused)
static int vfio_platform_set_irq_unmask(struct vfio_platform_device *vdev, unsigned index, unsigned start, unsigned count, uint32_t flags, void *data)
static irqreturn_t vfio_automasked_irq_handler(int irq, void *dev_id)
static irqreturn_t vfio_irq_handler(int irq, void *dev_id)
static int vfio_set_trigger(struct vfio_platform_device *vdev, int index, int fd, irq_handler_t handler)
static int vfio_platform_set_irq_trigger(struct vfio_platform_device *vdev, unsigned index, unsigned start, unsigned count, uint32_t flags, void *data)
int vfio_platform_set_irqs_ioctl(struct vfio_platform_device *vdev, uint32_t flags, unsigned index, unsigned start, unsigned count, void *data)
int vfio_platform_irq_init(struct vfio_platform_device *vdev)
void vfio_platform_irq_cleanup(struct vfio_platform_device *vdev)
   7 struct vfio_platform_device *vdev
   4 void *data
   4 unsigned start
   4 unsigned index
   4 unsigned count
   4 uint32_t flags
   2 void *unused
   2 void *opaque
   2 void *dev_id
   2 struct vfio_platform_irq *irq_ctx
   2 int irq
   1 irq_handler_t handler
   1 int index
   1 int fd
