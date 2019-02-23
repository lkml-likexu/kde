
\n
static struct vfio_group *kvm_vfio_group_get_external_user(struct file *filep)
static bool kvm_vfio_external_group_match_file(struct vfio_group *group, struct file *filep)
static void kvm_vfio_group_put_external_user(struct vfio_group *vfio_group)
static void kvm_vfio_group_set_kvm(struct vfio_group *group, struct kvm *kvm)
static bool kvm_vfio_group_is_coherent(struct vfio_group *vfio_group)
static int kvm_vfio_external_user_iommu_id(struct vfio_group *vfio_group)
static struct iommu_group *kvm_vfio_group_get_iommu_group( struct vfio_group *group)
static void kvm_spapr_tce_release_vfio_group(struct kvm *kvm, struct vfio_group *vfio_group)
static void kvm_vfio_update_coherency(struct kvm_device *dev)
static int kvm_vfio_set_group(struct kvm_device *dev, long attr, u64 arg)
static int kvm_vfio_set_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static int kvm_vfio_has_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static void kvm_vfio_destroy(struct kvm_device *dev)
static int kvm_vfio_create(struct kvm_device *dev, u32 type)
int kvm_vfio_ops_init(void)
void kvm_vfio_ops_exit(void)
\n
      6 struct kvm_device *dev
      4 struct vfio_group *vfio_group
      3 struct vfio_group *group
      2 void
      2 struct kvm *kvm
      2 struct kvm_device_attr *attr
      2 struct file *filep
      1 u64 arg
      1 u32 type
      1 long attr
