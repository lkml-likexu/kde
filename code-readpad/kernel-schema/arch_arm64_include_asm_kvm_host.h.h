
\n
static inline void __cpu_init_hyp_mode(phys_addr_t pgd_ptr, unsigned long hyp_stack_ptr, unsigned long vector_ptr)
static inline bool kvm_arch_requires_vhe(void)
static inline int kvm_arch_vcpu_run_pid_change(struct kvm_vcpu *vcpu)
static inline void kvm_arm_vhe_guest_enter(void)
static inline void kvm_arm_vhe_guest_exit(void)
static inline bool kvm_arm_harden_branch_predictor(void)
static inline int kvm_arm_have_ssbd(void)
\n
      5 void
      1 unsigned long vector_ptr
      1 unsigned long hyp_stack_ptr
      1 struct kvm_vcpu *vcpu
      1 phys_addr_t pgd_ptr
