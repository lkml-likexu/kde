
EXPORT_SYMBOL_GPL(kvmppc_rtas_hcall);
\n
static void kvm_rtas_set_xive(struct kvm_vcpu *vcpu, struct rtas_args *args)
static void kvm_rtas_get_xive(struct kvm_vcpu *vcpu, struct rtas_args *args)
static void kvm_rtas_int_off(struct kvm_vcpu *vcpu, struct rtas_args *args)
static void kvm_rtas_int_on(struct kvm_vcpu *vcpu, struct rtas_args *args)
static int rtas_name_matches(char *s1, char *s2)
static int rtas_token_undefine(struct kvm *kvm, char *name)
static int rtas_token_define(struct kvm *kvm, char *name, u64 token)
int kvm_vm_ioctl_rtas_define_token(struct kvm *kvm, void __user *argp)
int kvmppc_rtas_hcall(struct kvm_vcpu *vcpu)
void kvmppc_rtas_tokens_free(struct kvm *kvm)
\n
      5 struct kvm_vcpu *vcpu
      4 struct rtas_args *args
      4 struct kvm *kvm
      2 char *name
      1 void __user *argp
      1 u64 token
      1 kvmppc_rtas_hcall
      1 char *s2
      1 char *s1
