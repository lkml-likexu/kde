
\n
static u32 smccc_get_function(struct kvm_vcpu *vcpu)
static unsigned long smccc_get_arg1(struct kvm_vcpu *vcpu)
static unsigned long smccc_get_arg2(struct kvm_vcpu *vcpu)
static unsigned long smccc_get_arg3(struct kvm_vcpu *vcpu)
static void smccc_set_retval(struct kvm_vcpu *vcpu, unsigned long a0, unsigned long a1, unsigned long a2, unsigned long a3)
static unsigned long psci_affinity_mask(unsigned long affinity_level)
static unsigned long kvm_psci_vcpu_suspend(struct kvm_vcpu *vcpu)
static void kvm_psci_vcpu_off(struct kvm_vcpu *vcpu)
static unsigned long kvm_psci_vcpu_on(struct kvm_vcpu *source_vcpu)
static unsigned long kvm_psci_vcpu_affinity_info(struct kvm_vcpu *vcpu)
static void kvm_prepare_system_event(struct kvm_vcpu *vcpu, u32 type)
static void kvm_psci_system_off(struct kvm_vcpu *vcpu)
static void kvm_psci_system_reset(struct kvm_vcpu *vcpu)
static int kvm_psci_0_2_call(struct kvm_vcpu *vcpu)
static int kvm_psci_1_0_call(struct kvm_vcpu *vcpu)
static int kvm_psci_0_1_call(struct kvm_vcpu *vcpu)
static int kvm_psci_call(struct kvm_vcpu *vcpu)
int kvm_hvc_call_handler(struct kvm_vcpu *vcpu)
int kvm_arm_get_fw_num_regs(struct kvm_vcpu *vcpu)
int kvm_arm_copy_fw_reg_indices(struct kvm_vcpu *vcpu, u64 __user *uindices)
int kvm_arm_get_fw_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
int kvm_arm_set_fw_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
\n
     20 struct kvm_vcpu *vcpu
      2 const struct kvm_one_reg *reg
      1 unsigned long affinity_level
      1 unsigned long a3
      1 unsigned long a2
      1 unsigned long a1
      1 unsigned long a0
      1 u64 __user *uindices
      1 u32 type
      1 struct kvm_vcpu *source_vcpu
