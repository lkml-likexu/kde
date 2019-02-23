
EXPORT_SYMBOL_GPL(hypercall_page);
EXPORT_SYMBOL_GPL(xen_domain_type);
EXPORT_SYMBOL_GPL(xen_start_info);
EXPORT_SYMBOL_GPL(xen_have_vector_callback);
\n
static int xen_cpu_up_online(unsigned int cpu)
int xen_cpuhp_setup(int (*cpu_up_prepare_cb)
(unsigned int)
, int (*cpu_dead_cb)
(unsigned int)
)
static int xen_vcpu_setup_restore(int cpu)
void xen_vcpu_restore(void)
void xen_vcpu_info_reset(int cpu)
int xen_vcpu_setup(int cpu)
void xen_reboot(int reason)
void xen_emergency_restart(void)
static int xen_panic_event(struct notifier_block *this, unsigned long event, void *ptr)
int xen_panic_handler_init(void)
void xen_pin_vcpu(int cpu)
void xen_arch_register_cpu(int num)
void xen_arch_unregister_cpu(int num)
\n
      4 int cpu
      3 void
      2 unsigned int
      2 int num
      1 xen_start_info
      1 xen_have_vector_callback
      1 xen_domain_type
      1 void *ptr
      1 unsigned long event
      1 unsigned int cpu
      1 struct notifier_block *this
      1 int reason
      1 int *cpu_up_prepare_cb
      1 hypercall_page
      1 *cpu_dead_cb
