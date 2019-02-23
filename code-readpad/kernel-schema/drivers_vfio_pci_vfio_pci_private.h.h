
\n
extern int vfio_pci_register_dev_region(struct vfio_pci_device *vdev, unsigned int type, unsigned int subtype, const struct vfio_pci_regops *ops, size_t size, u32 flags, void *data)
; extern int vfio_pci_igd_init(struct vfio_pci_device *vdev)
; static inline int vfio_pci_igd_init(struct vfio_pci_device *vdev)
extern int vfio_pci_register_dev_region(struct vfio_pci_device *vdev, unsigned int type, unsigned int subtype, const struct vfio_pci_regops *ops, size_t size, u32 flags, void *data)
; extern int vfio_pci_igd_init(struct vfio_pci_device *vdev)
; static inline int vfio_pci_igd_init(struct vfio_pci_device *vdev)
return -ENODEV; }endif extern int vfio_pci_nvdia_v100_nvlink2_init(struct vfio_pci_device *vdev)
; extern int vfio_pci_ibm_npu2_init(struct vfio_pci_device *vdev)
; static inline int vfio_pci_nvdia_v100_nvlink2_init(struct vfio_pci_device *vdev)
static inline int vfio_pci_ibm_npu2_init(struct vfio_pci_device *vdev)
\n
     10 struct vfio_pci_device *vdev
      2 void *data
      2 unsigned int type
      2 unsigned int subtype
      2 u32 flags
      2 size_t size
      2 const struct vfio_pci_regops *ops
