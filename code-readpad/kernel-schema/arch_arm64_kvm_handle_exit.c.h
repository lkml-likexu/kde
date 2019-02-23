
\n
static void kvm_handle_guest_serror(struct kvm_vcpu *vcpu, u32 esr)
static int handle_hvc(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int handle_smc(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int handle_no_fpsimd(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int kvm_handle_wfx(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int kvm_handle_guest_debug(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int kvm_handle_unknown_ec(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int handle_sve(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int kvm_handle_ptrauth(struct kvm_vcpu *vcpu, struct kvm_run *run)
static exit_handle_fn kvm_get_exit_handler(struct kvm_vcpu *vcpu)
static int handle_trap_exceptions(struct kvm_vcpu *vcpu, struct kvm_run *run)
int handle_exit(struct kvm_vcpu *vcpu, struct kvm_run *run, int exception_index)
void handle_exit_early(struct kvm_vcpu *vcpu, struct kvm_run *run, int exception_index)
\n
     13 struct kvm_vcpu *vcpu
     11 struct kvm_run *run
      2 int exception_index
      1 u32 esr
