
\n
static inline void kvm_iodevice_init(struct kvm_io_device *dev, const struct kvm_io_device_ops *ops)
static inline int kvm_iodevice_read(struct kvm_vcpu *vcpu, struct kvm_io_device *dev, gpa_t addr, int l, void *v)
static inline int kvm_iodevice_write(struct kvm_vcpu *vcpu, struct kvm_io_device *dev, gpa_t addr, int l, const void *v)
static inline void kvm_iodevice_destructor(struct kvm_io_device *dev)
\n
      4 struct kvm_io_device *dev
      2 struct kvm_vcpu *vcpu
      2 int l
      2 gpa_t addr
      1 void *v
      1 const void *v
      1 const struct kvm_io_device_ops *ops
