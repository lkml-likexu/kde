
\n
static inline void __cpu_init_hyp_mode(phys_addr_t pgd_ptr, unsigned long hyp_stack_ptr, unsigned long vector_ptr)
static inline void __cpu_init_stage2(void)
static inline int kvm_arch_vm_ioctl_check_extension(struct kvm *kvm, long ext)
static inline bool kvm_arm_harden_branch_predictor(void)
static inline int kvm_arm_have_ssbd(void)
static inline int kvm_arm_setup_stage2(struct kvm *kvm, unsigned long type)
\n
      3 void
      2 struct kvm *kvm
      1 unsigned long vector_ptr
      1 unsigned long type
      1 unsigned long hyp_stack_ptr
      1 phys_addr_t pgd_ptr
      1 long ext
