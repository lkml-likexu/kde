
static struct resource *get_platform_resource(struct vfio_platform_device *vdev, int num)
static int get_platform_irq(struct vfio_platform_device *vdev, int i)
static int vfio_platform_probe(struct platform_device *pdev)
static int vfio_platform_remove(struct platform_device *pdev)
   2 struct vfio_platform_device *vdev
   2 struct platform_device *pdev
   1 int num
   1 int i
