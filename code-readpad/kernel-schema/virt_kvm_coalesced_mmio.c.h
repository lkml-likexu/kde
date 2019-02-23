
\n
static inline struct kvm_coalesced_mmio_dev *to_mmio(struct kvm_io_device *dev)
static int coalesced_mmio_in_range(struct kvm_coalesced_mmio_dev *dev, gpa_t addr, int len)
static int coalesced_mmio_has_room(struct kvm_coalesced_mmio_dev *dev)
static int coalesced_mmio_write(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t addr, int len, const void *val)
static void coalesced_mmio_destructor(struct kvm_io_device *this)
int kvm_coalesced_mmio_init(struct kvm *kvm)
void kvm_coalesced_mmio_free(struct kvm *kvm)
int kvm_vm_ioctl_register_coalesced_mmio(struct kvm *kvm, struct kvm_coalesced_mmio_zone *zone)
int kvm_vm_ioctl_unregister_coalesced_mmio(struct kvm *kvm, struct kvm_coalesced_mmio_zone *zone)
\n
      4 struct kvm *kvm
      2 struct kvm_io_device *this
      2 struct kvm_coalesced_mmio_zone *zone
      2 struct kvm_coalesced_mmio_dev *dev
      2 int len
      2 gpa_t addr
      1 struct kvm_vcpu *vcpu
      1 struct kvm_io_device *dev
      1 const void *val
