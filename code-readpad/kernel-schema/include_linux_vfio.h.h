
\n
struct pci_dev; extern void vfio_spapr_pci_eeh_open(struct pci_dev *pdev)
; extern void vfio_spapr_pci_eeh_release(struct pci_dev *pdev)
; extern long vfio_spapr_iommu_eeh_ioctl(struct iommu_group *group, unsigned int cmd, unsigned long arg)
; static inline void vfio_spapr_pci_eeh_open(struct pci_dev *pdev)
static inline void vfio_spapr_pci_eeh_release(struct pci_dev *pdev)
static inline long vfio_spapr_iommu_eeh_ioctl(struct iommu_group *group, unsigned int cmd, unsigned long arg)
\n
      4 struct pci_dev *pdev
      2 unsigned long arg
      2 unsigned int cmd
      2 struct iommu_group *group
