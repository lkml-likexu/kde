
\n
static void release_device(struct device *dev)
static int __init iommu_dev_init(void)
int iommu_device_sysfs_add(struct iommu_device *iommu, struct device *parent, const struct attribute_group **groups, const char *fmt, ...)
void iommu_device_sysfs_remove(struct iommu_device *iommu)
void iommu_device_sysfs_remove(struct iommu_device *iommu)
dev_set_drvdata(iommu->dev, NULL)
;device_unregister(iommu->dev)
;iommu->dev = NULL; }int iommu_device_link(struct iommu_device *iommu, struct device *link)
void iommu_device_unlink(struct iommu_device *iommu, struct device *link)
\n
      5 struct iommu_device *iommu
      2 struct device *link
      2 iommu->dev
      1 void
      1 struct device *parent
      1 struct device *dev
      1 NULL
      1 const struct attribute_group **groups
      1 const char *fmt
      1 ...
