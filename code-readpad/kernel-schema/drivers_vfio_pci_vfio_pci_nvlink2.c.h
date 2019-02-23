
\n
static size_t vfio_pci_nvgpu_rw(struct vfio_pci_device *vdev, char __user *buf, size_t count, loff_t *ppos, bool iswrite)
static void vfio_pci_nvgpu_release(struct vfio_pci_device *vdev, struct vfio_pci_region *region)
static vm_fault_t vfio_pci_nvgpu_mmap_fault(struct vm_fault *vmf)
static int vfio_pci_nvgpu_mmap(struct vfio_pci_device *vdev, struct vfio_pci_region *region, struct vm_area_struct *vma)
static int vfio_pci_nvgpu_add_capability(struct vfio_pci_device *vdev, struct vfio_pci_region *region, struct vfio_info_cap *caps)
static int vfio_pci_nvgpu_group_notifier(struct notifier_block *nb, unsigned long action, void *opaque)
int vfio_pci_nvdia_v100_nvlink2_init(struct vfio_pci_device *vdev)
static size_t vfio_pci_npu2_rw(struct vfio_pci_device *vdev, char __user *buf, size_t count, loff_t *ppos, bool iswrite)
static int vfio_pci_npu2_mmap(struct vfio_pci_device *vdev, struct vfio_pci_region *region, struct vm_area_struct *vma)
static void vfio_pci_npu2_release(struct vfio_pci_device *vdev, struct vfio_pci_region *region)
static int vfio_pci_npu2_add_capability(struct vfio_pci_device *vdev, struct vfio_pci_region *region, struct vfio_info_cap *caps)
int vfio_pci_ibm_npu2_init(struct vfio_pci_device *vdev)
\n
     10 struct vfio_pci_device *vdev
      6 struct vfio_pci_region *region
      2 struct vm_area_struct *vma
      2 struct vfio_info_cap *caps
      2 size_t count
      2 loff_t *ppos
      2 char __user *buf
      2 bool iswrite
      1 void *opaque
      1 unsigned long action
      1 struct vm_fault *vmf
      1 struct notifier_block *nb
