
\n
static u64 vm_get_features(struct virtio_device *vdev)
static int vm_finalize_features(struct virtio_device *vdev)
static void vm_get(struct virtio_device *vdev, unsigned offset, void *buf, unsigned len)
static void vm_set(struct virtio_device *vdev, unsigned offset, const void *buf, unsigned len)
static u32 vm_generation(struct virtio_device *vdev)
static u8 vm_get_status(struct virtio_device *vdev)
static void vm_set_status(struct virtio_device *vdev, u8 status)
static void vm_reset(struct virtio_device *vdev)
static bool vm_notify(struct virtqueue *vq)
static irqreturn_t vm_interrupt(int irq, void *opaque)
static void vm_del_vq(struct virtqueue *vq)
static void vm_del_vqs(struct virtio_device *vdev)
static struct virtqueue *vm_setup_vq(struct virtio_device *vdev, unsigned index, void (*callback)
(struct virtqueue *vq)
, const char *name, bool ctx)
static int vm_find_vqs(struct virtio_device *vdev, unsigned nvqs, struct virtqueue *vqs[], vq_callback_t *callbacks[], const char * const names[], const bool *ctx, struct irq_affinity *desc)
static const char *vm_bus_name(struct virtio_device *vdev)
static void virtio_mmio_release_dev(struct device *_d)
static int virtio_mmio_probe(struct platform_device *pdev)
static int virtio_mmio_remove(struct platform_device *pdev)
static int vm_cmdline_set(const char *device, const struct kernel_param *kp)
static int vm_cmdline_get_device(struct device *dev, void *data)
static int vm_cmdline_get(char *buffer, const struct kernel_param *kp)
static int vm_unregister_cmdline_device(struct device *dev, void *data)
static void vm_unregister_cmdline_devices(void)
static void vm_unregister_cmdline_devices(void)
static int __init virtio_mmio_init(void)
static void __exit virtio_mmio_exit(void)
\n
     12 struct virtio_device *vdev
      4 void
      3 struct virtqueue *vq
      2 void *data
      2 unsigned offset
      2 unsigned len
      2 struct platform_device *pdev
      2 struct device *dev
      2 const struct kernel_param *kp
      1 vq_callback_t *callbacks[]
      1 void *opaque
      1 void *callback
      1 void *buf
      1 unsigned nvqs
      1 unsigned index
      1 u8 status
      1 struct virtqueue *vqs[]
      1 struct irq_affinity *desc
      1 struct device *_d
      1 int irq
      1 const void *buf
      1 const char *device
      1 const char * const names[]
      1 const bool *ctx
      1 char *buffer
