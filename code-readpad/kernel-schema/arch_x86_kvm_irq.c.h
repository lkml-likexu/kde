
EXPORT_SYMBOL_GPL(kvm_cpu_has_interrupt);
EXPORT_SYMBOL_GPL(kvm_cpu_get_interrupt);
EXPORT_SYMBOL_GPL(kvm_inject_pending_timer_irqs);
\n
int kvm_cpu_has_pending_timer(struct kvm_vcpu *vcpu)
static int pending_userspace_extint(struct kvm_vcpu *v)
static int kvm_cpu_has_extint(struct kvm_vcpu *v)
int kvm_cpu_has_injectable_intr(struct kvm_vcpu *v)
int kvm_cpu_has_interrupt(struct kvm_vcpu *v)
static int kvm_cpu_get_extint(struct kvm_vcpu *v)
int kvm_cpu_get_interrupt(struct kvm_vcpu *v)
void kvm_inject_pending_timer_irqs(struct kvm_vcpu *vcpu)
void __kvm_migrate_timers(struct kvm_vcpu *vcpu)
\n
      6 struct kvm_vcpu *v
      3 struct kvm_vcpu *vcpu
      1 kvm_inject_pending_timer_irqs
      1 kvm_cpu_has_interrupt
      1 kvm_cpu_get_interrupt
