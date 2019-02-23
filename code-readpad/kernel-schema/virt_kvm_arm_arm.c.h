
\n
static void kvm_arm_set_running_vcpu(struct kvm_vcpu *vcpu)
struct kvm_vcpu *kvm_arm_get_running_vcpu(void)
struct kvm_vcpu * __percpu *kvm_get_running_vcpus(void)
int kvm_arch_vcpu_should_kick(struct kvm_vcpu *vcpu)
int kvm_arch_hardware_setup(void)
void kvm_arch_check_processor_compat(void *rtn)
int kvm_arch_init_vm(struct kvm *kvm, unsigned long type)
bool kvm_arch_has_vcpu_debugfs(void)
int kvm_arch_create_vcpu_debugfs(struct kvm_vcpu *vcpu)
vm_fault_t kvm_arch_vcpu_fault(struct kvm_vcpu *vcpu, struct vm_fault *vmf)
void kvm_arch_destroy_vm(struct kvm *kvm)
int kvm_vm_ioctl_check_extension(struct kvm *kvm, long ext)
long kvm_arch_dev_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
struct kvm *kvm_arch_alloc_vm(void)
void kvm_arch_free_vm(struct kvm *kvm)
struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm, unsigned int id)
void kvm_arch_vcpu_postcreate(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_free(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_destroy(struct kvm_vcpu *vcpu)
int kvm_cpu_has_pending_timer(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_blocking(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_unblocking(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_init(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
static void vcpu_power_off(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_get_mpstate(struct kvm_vcpu *vcpu, struct kvm_mp_state *mp_state)
int kvm_arch_vcpu_ioctl_set_mpstate(struct kvm_vcpu *vcpu, struct kvm_mp_state *mp_state)
int kvm_arch_vcpu_runnable(struct kvm_vcpu *v)
bool kvm_arch_vcpu_in_kernel(struct kvm_vcpu *vcpu)
static void exit_vm_noop(void *info)
void force_vm_exit(const cpumask_t *mask)
static bool need_new_vmid_gen(struct kvm *kvm)
static void update_vttbr(struct kvm *kvm)
static int kvm_vcpu_first_run_init(struct kvm_vcpu *vcpu)
bool kvm_arch_intc_initialized(struct kvm *kvm)
void kvm_arm_halt_guest(struct kvm *kvm)
void kvm_arm_resume_guest(struct kvm *kvm)
static void vcpu_req_sleep(struct kvm_vcpu *vcpu)
static int kvm_vcpu_initialized(struct kvm_vcpu *vcpu)
static void check_vcpu_requests(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_run(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int vcpu_interrupt_line(struct kvm_vcpu *vcpu, int number, bool level)
int kvm_vm_ioctl_irq_line(struct kvm *kvm, struct kvm_irq_level *irq_level, bool line_status)
static int kvm_vcpu_set_target(struct kvm_vcpu *vcpu, const struct kvm_vcpu_init *init)
static int kvm_arch_vcpu_ioctl_vcpu_init(struct kvm_vcpu *vcpu, struct kvm_vcpu_init *init)
static int kvm_arm_vcpu_set_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
static int kvm_arm_vcpu_get_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
static int kvm_arm_vcpu_has_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
static int kvm_arm_vcpu_get_events(struct kvm_vcpu *vcpu, struct kvm_vcpu_events *events)
static int kvm_arm_vcpu_set_events(struct kvm_vcpu *vcpu, struct kvm_vcpu_events *events)
long kvm_arch_vcpu_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
int kvm_vm_ioctl_get_dirty_log(struct kvm *kvm, struct kvm_dirty_log *log)
int kvm_vm_ioctl_clear_dirty_log(struct kvm *kvm, struct kvm_clear_dirty_log *log)
static int kvm_vm_ioctl_set_device_addr(struct kvm *kvm, struct kvm_arm_device_addr *dev_addr)
long kvm_arch_vm_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
static void cpu_init_hyp_mode(void *dummy)
static void cpu_hyp_reset(void)
static void cpu_hyp_reinit(void)
static void _kvm_arch_hardware_enable(void *discard)
int kvm_arch_hardware_enable(void)
static void _kvm_arch_hardware_disable(void *discard)
void kvm_arch_hardware_disable(void)
static int hyp_init_cpu_pm_notifier(struct notifier_block *self, unsigned long cmd, void *v)
static void __init hyp_cpu_pm_init(void)
static void __init hyp_cpu_pm_init(void)
cpu_pm_register_notifier(&hyp_init_cpu_pm_nb)
; } static void __init hyp_cpu_pm_exit(void)
static void __init hyp_cpu_pm_init(void)
cpu_pm_register_notifier(&hyp_init_cpu_pm_nb)
; } static void __init hyp_cpu_pm_exit(void)
cpu_pm_unregister_notifier(&hyp_init_cpu_pm_nb)
; } static inline void hyp_cpu_pm_init(void)
static void __init hyp_cpu_pm_init(void)
cpu_pm_register_notifier(&hyp_init_cpu_pm_nb)
; } static void __init hyp_cpu_pm_exit(void)
cpu_pm_unregister_notifier(&hyp_init_cpu_pm_nb)
; } static inline void hyp_cpu_pm_init(void)
} static inline void hyp_cpu_pm_exit(void)
static int init_common_resources(void)
static int init_subsystems(void)
static void teardown_hyp_mode(void)
static int init_hyp_mode(void)
static void check_kvm_target_cpu(void *ret)
struct kvm_vcpu *kvm_mpidr_to_vcpu(struct kvm *kvm, unsigned long mpidr)
bool kvm_arch_has_irq_bypass(void)
int kvm_arch_irq_bypass_add_producer(struct irq_bypass_consumer *cons, struct irq_bypass_producer *prod)
return kvm_vgic_v4_set_forwarding(irqfd->kvm, prod->irq, &irqfd->irq_entry)
; } void kvm_arch_irq_bypass_del_producer(struct irq_bypass_consumer *cons, struct irq_bypass_producer *prod)
void kvm_arch_irq_bypass_stop(struct irq_bypass_consumer *cons)
void kvm_arch_irq_bypass_start(struct irq_bypass_consumer *cons)
int kvm_arch_init(void *opaque)
void kvm_arch_exit(void)
static int arm_init(void)
\n
     30 struct kvm_vcpu *vcpu
     26 void
     15 struct kvm *kvm
      5 &hyp_init_cpu_pm_nb
      4 struct irq_bypass_consumer *cons
      3 unsigned long arg
      3 unsigned int ioctl
      3 struct kvm_device_attr *attr
      3 struct file *filp
      2 void *discard
      2 struct kvm_vcpu_events *events
      2 struct kvm_mp_state *mp_state
      2 struct irq_bypass_producer *prod
      1 void *v
      1 void *rtn
      1 void *ret
      1 void *opaque
      1 void *info
      1 void *dummy
      1 unsigned long type
      1 unsigned long mpidr
      1 unsigned long cmd
      1 unsigned int id
      1 struct vm_fault *vmf
      1 struct notifier_block *self
      1 struct kvm_vcpu *v
      1 struct kvm_vcpu_init *init
      1 struct kvm_run *run
      1 struct kvm_irq_level *irq_level
      1 struct kvm_dirty_log *log
      1 struct kvm_clear_dirty_log *log
      1 struct kvm_arm_device_addr *dev_addr
      1 prod->irq
      1 long ext
      1 irqfd->kvm
      1 &irqfd->irq_entry
      1 int number
      1 int cpu
      1 const struct kvm_vcpu_init *init
      1 const cpumask_t *mask
      1 bool line_status
      1 bool level
