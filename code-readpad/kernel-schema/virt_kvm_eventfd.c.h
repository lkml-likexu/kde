
EXPORT_SYMBOL_GPL(kvm_irq_has_notifier);
static void irqfd_inject(struct work_struct *work)
static void irqfd_resampler_ack(struct kvm_irq_ack_notifier *kian)
static void irqfd_resampler_shutdown(struct kvm_kernel_irqfd *irqfd)
static void irqfd_shutdown(struct work_struct *work)
static bool irqfd_is_active(struct kvm_kernel_irqfd *irqfd)
static void irqfd_deactivate(struct kvm_kernel_irqfd *irqfd)
int __attribute__((weak)
)
kvm_arch_set_irq_inatomic( struct kvm_kernel_irq_routing_entry *irq, struct kvm *kvm, int irq_source_id, int level, bool line_status)
static int irqfd_wakeup(wait_queue_entry_t *wait, unsigned mode, int sync, void *key)
static void irqfd_ptable_queue_proc(struct file *file, wait_queue_head_t *wqh, poll_table *pt)
static void irqfd_update(struct kvm *kvm, struct kvm_kernel_irqfd *irqfd)
void __attribute__((weak)
)
kvm_arch_irq_bypass_stop( struct irq_bypass_consumer *cons)
void __attribute__((weak)
)
kvm_arch_irq_bypass_start( struct irq_bypass_consumer *cons)
int__attribute__((weak)
)
kvm_arch_update_irqfd_routing( struct kvm *kvm, unsigned int host_irq, uint32_t guest_irq, bool set)
static int kvm_irqfd_assign(struct kvm *kvm, struct kvm_irqfd *args)
bool kvm_irq_has_notifier(struct kvm *kvm, unsigned irqchip, unsigned pin)
void kvm_notify_acked_gsi(struct kvm *kvm, int gsi)
void kvm_notify_acked_irq(struct kvm *kvm, unsigned irqchip, unsigned pin)
void kvm_register_irq_ack_notifier(struct kvm *kvm, struct kvm_irq_ack_notifier *kian)
void kvm_unregister_irq_ack_notifier(struct kvm *kvm, struct kvm_irq_ack_notifier *kian)
void kvm_eventfd_init(struct kvm *kvm)
static int kvm_irqfd_deassign(struct kvm *kvm, struct kvm_irqfd *args)
int kvm_irqfd(struct kvm *kvm, struct kvm_irqfd *args)
void kvm_irqfd_release(struct kvm *kvm)
void kvm_irq_routing_update(struct kvm *kvm)
int kvm_irqfd_init(void)
void kvm_irqfd_exit(void)
static inline struct _ioeventfd * to_ioeventfd(struct kvm_io_device *dev)
static void ioeventfd_release(struct _ioeventfd *p)
static bool ioeventfd_in_range(struct _ioeventfd *p, gpa_t addr, int len, const void *val)
static int ioeventfd_write(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t addr, int len, const void *val)
static void ioeventfd_destructor(struct kvm_io_device *this)
static bool ioeventfd_check_collision(struct kvm *kvm, struct _ioeventfd *p)
static enum kvm_bus ioeventfd_bus_from_flags(__u32 flags)
static int kvm_assign_ioeventfd_idx(struct kvm *kvm, enum kvm_bus bus_idx, struct kvm_ioeventfd *args)
static int kvm_deassign_ioeventfd_idx(struct kvm *kvm, enum kvm_bus bus_idx, struct kvm_ioeventfd *args)
static int kvm_deassign_ioeventfd(struct kvm *kvm, struct kvm_ioeventfd *args)
static int kvm_assign_ioeventfd(struct kvm *kvm, struct kvm_ioeventfd *args)
int kvm_ioeventfd(struct kvm *kvm, struct kvm_ioeventfd *args)
  20 struct kvm *kvm
   5 struct kvm_ioeventfd *args
   4 weak
   4 struct kvm_kernel_irqfd *irqfd
   3 struct kvm_irqfd *args
   3 struct kvm_irq_ack_notifier *kian
   3 struct _ioeventfd *p
   2 void
   2 unsigned pin
   2 unsigned irqchip
   2 struct work_struct *work
   2 struct kvm_io_device *this
   2 struct irq_bypass_consumer *cons
   2 int len
   2 gpa_t addr
   2 enum kvm_bus bus_idx
   2 const void *val
   1 wait_queue_head_t *wqh
   1 wait_queue_entry_t *wait
   1 void *key
   1 unsigned mode
   1 unsigned int host_irq
   1 uint32_t guest_irq
   1 struct kvm_vcpu *vcpu
   1 struct kvm_kernel_irq_routing_entry *irq
   1 struct kvm_io_device *dev
   1 struct file *file
   1 poll_table *pt
   1 kvm_irq_has_notifier
   1 int sync
   1 int level
   1 int irq_source_id
   1 int gsi
   1 bool set
   1 bool line_status
   1 __u32 flags
