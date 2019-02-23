
\n
int kvm_arch_vcpu_setup(struct kvm_vcpu *vcpu)
static u64 core_reg_offset_from_id(u64 id)
static int validate_core_offset(const struct kvm_one_reg *reg)
static int get_core_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
static int set_core_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
int kvm_arch_vcpu_ioctl_get_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
int kvm_arch_vcpu_ioctl_set_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
static unsigned long num_core_regs(void)
static bool is_timer_reg(u64 index)
static int copy_timer_indices(struct kvm_vcpu *vcpu, u64 __user *uindices)
static int set_timer_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
static int get_timer_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
unsigned long kvm_arm_num_regs(struct kvm_vcpu *vcpu)
int kvm_arm_copy_reg_indices(struct kvm_vcpu *vcpu, u64 __user *uindices)
int kvm_arm_get_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
int kvm_arm_set_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
int kvm_arch_vcpu_ioctl_get_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_set_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int __kvm_arm_vcpu_get_events(struct kvm_vcpu *vcpu, struct kvm_vcpu_events *events)
int __kvm_arm_vcpu_set_events(struct kvm_vcpu *vcpu, struct kvm_vcpu_events *events)
int __attribute_const__ kvm_target_cpu(void)
int kvm_vcpu_preferred_target(struct kvm_vcpu_init *init)
int kvm_arch_vcpu_ioctl_get_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
int kvm_arch_vcpu_ioctl_set_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
int kvm_arch_vcpu_ioctl_translate(struct kvm_vcpu *vcpu, struct kvm_translation *tr)
int kvm_arch_vcpu_ioctl_set_guest_debug(struct kvm_vcpu *vcpu, struct kvm_guest_debug *dbg)
int kvm_arm_vcpu_arch_set_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
int kvm_arm_vcpu_arch_get_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
int kvm_arm_vcpu_arch_has_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
\n
     23 struct kvm_vcpu *vcpu
      7 const struct kvm_one_reg *reg
      3 struct kvm_device_attr *attr
      2 void
      2 u64 __user *uindices
      2 struct kvm_vcpu_events *events
      2 struct kvm_sregs *sregs
      2 struct kvm_regs *regs
      2 struct kvm_fpu *fpu
      1 u64 index
      1 u64 id
      1 struct kvm_vcpu_init *init
      1 struct kvm_translation *tr
      1 struct kvm_guest_debug *dbg
