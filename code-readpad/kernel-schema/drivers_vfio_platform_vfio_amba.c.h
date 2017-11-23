
static struct resource *get_amba_resource(struct vfio_platform_device *vdev, int i)
static int get_amba_irq(struct vfio_platform_device *vdev, int i)
static int vfio_amba_probe(struct amba_device *adev, const struct amba_id *id)
static int vfio_amba_remove(struct amba_device *adev)
   2 struct vfio_platform_device *vdev
   2 struct amba_device *adev
   2 int i
   1 const struct amba_id *id
