
EXPORT_SYMBOL_GPL(vfio_spapr_pci_eeh_open);
EXPORT_SYMBOL_GPL(vfio_spapr_pci_eeh_release);
EXPORT_SYMBOL_GPL(vfio_spapr_iommu_eeh_ioctl);
\n
void vfio_spapr_pci_eeh_open(struct pci_dev *pdev)
void vfio_spapr_pci_eeh_release(struct pci_dev *pdev)
long vfio_spapr_iommu_eeh_ioctl(struct iommu_group *group, unsigned int cmd, unsigned long arg)
\n
      2 struct pci_dev *pdev
      1 vfio_spapr_pci_eeh_release
      1 vfio_spapr_pci_eeh_open
      1 vfio_spapr_iommu_eeh_ioctl
      1 unsigned long arg
      1 unsigned int cmd
      1 struct iommu_group *group
