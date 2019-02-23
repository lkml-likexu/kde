
EXPORT_SYMBOL_GPL(mdev_bus_type);
\n
static int mdev_attach_iommu(struct mdev_device *mdev)
static void mdev_detach_iommu(struct mdev_device *mdev)
static int mdev_probe(struct device *dev)
static int mdev_remove(struct device *dev)
int mdev_register_driver(struct mdev_driver *drv, struct module *owner)
void mdev_unregister_driver(struct mdev_driver *drv)
int mdev_bus_register(void)
void mdev_bus_unregister(void)
\n
      2 void
      2 struct mdev_driver *drv
      2 struct mdev_device *mdev
      2 struct device *dev
      1 struct module *owner
      1 mdev_bus_type
