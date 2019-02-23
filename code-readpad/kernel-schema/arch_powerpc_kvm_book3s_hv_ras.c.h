
EXPORT_SYMBOL_GPL(kvmppc_subcore_enter_guest);
EXPORT_SYMBOL_GPL(kvmppc_subcore_exit_guest);
\n
static void reload_slb(struct kvm_vcpu *vcpu)
static long kvmppc_realmode_mc_power7(struct kvm_vcpu *vcpu)
long kvmppc_realmode_machine_check(struct kvm_vcpu *vcpu)
static inline int kvmppc_cur_subcore_size(void)
void kvmppc_subcore_enter_guest(void)
void kvmppc_subcore_exit_guest(void)
static bool kvmppc_tb_resync_required(void)
static void kvmppc_tb_resync_done(void)
long kvmppc_realmode_hmi_handler(void)
\n
      6 void
      3 struct kvm_vcpu *vcpu
      1 kvmppc_subcore_exit_guest
      1 kvmppc_subcore_enter_guest
