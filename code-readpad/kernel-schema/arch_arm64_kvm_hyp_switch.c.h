
\n
static bool __hyp_text update_fp_enabled(struct kvm_vcpu *vcpu)
static void __hyp_text __fpsimd_save_fpexc32(struct kvm_vcpu *vcpu)
static void __hyp_text __activate_traps_fpsimd32(struct kvm_vcpu *vcpu)
static void __hyp_text __activate_traps_common(struct kvm_vcpu *vcpu)
static void __hyp_text __deactivate_traps_common(void)
static void activate_traps_vhe(struct kvm_vcpu *vcpu)
static void __hyp_text __activate_traps_nvhe(struct kvm_vcpu *vcpu)
static void __hyp_text __activate_traps(struct kvm_vcpu *vcpu)
static void deactivate_traps_vhe(void)
static void __hyp_text __deactivate_traps_nvhe(void)
static void __hyp_text __deactivate_traps(struct kvm_vcpu *vcpu)
void activate_traps_vhe_load(struct kvm_vcpu *vcpu)
void deactivate_traps_vhe_put(void)
static void __hyp_text __activate_vm(struct kvm *kvm)
static void __hyp_text __deactivate_vm(struct kvm_vcpu *vcpu)
static void __hyp_text __hyp_vgic_save_state(struct kvm_vcpu *vcpu)
static void __hyp_text __hyp_vgic_restore_state(struct kvm_vcpu *vcpu)
static bool __hyp_text __true_value(void)
static bool __hyp_text __false_value(void)
static bool __hyp_text __translate_far_to_hpfar(u64 far, u64 *hpfar)
static bool __hyp_text __populate_fault_info(struct kvm_vcpu *vcpu)
static bool __hyp_text __hyp_switch_fpsimd(struct kvm_vcpu *vcpu)
static bool __hyp_text fixup_guest_exit(struct kvm_vcpu *vcpu, u64 *exit_code)
static inline bool __hyp_text __needs_ssbd_off(struct kvm_vcpu *vcpu)
static void __hyp_text __set_guest_arch_workaround_state(struct kvm_vcpu *vcpu)
static void __hyp_text __set_host_arch_workaround_state(struct kvm_vcpu *vcpu)
int kvm_vcpu_run_vhe(struct kvm_vcpu *vcpu)
int __hyp_text __kvm_vcpu_run_nvhe(struct kvm_vcpu *vcpu)
static void __hyp_text __hyp_call_panic_nvhe(u64 spsr, u64 elr, u64 par, struct kvm_cpu_context *__host_ctxt)
static void __hyp_call_panic_vhe(u64 spsr, u64 elr, u64 par, struct kvm_cpu_context *host_ctxt)
void __hyp_text __noreturn hyp_panic(struct kvm_cpu_context *host_ctxt)
\n
     20 struct kvm_vcpu *vcpu
      6 void
      2 u64 spsr
      2 u64 par
      2 u64 elr
      2 struct kvm_cpu_context *host_ctxt
      1 u64 *hpfar
      1 u64 far
      1 u64 *exit_code
      1 struct kvm *kvm
      1 struct kvm_cpu_context *__host_ctxt
