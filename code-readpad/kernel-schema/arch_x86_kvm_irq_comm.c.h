
EXPORT_SYMBOL_GPL(kvm_set_msi_irq);
EXPORT_SYMBOL_GPL(kvm_intr_is_single_vcpu);
\n
static int kvm_set_pic_irq(struct kvm_kernel_irq_routing_entry *e, struct kvm *kvm, int irq_source_id, int level, bool line_status)
static int kvm_set_ioapic_irq(struct kvm_kernel_irq_routing_entry *e, struct kvm *kvm, int irq_source_id, int level, bool line_status)
int kvm_irq_delivery_to_apic(struct kvm *kvm, struct kvm_lapic *src, struct kvm_lapic_irq *irq, struct dest_map *dest_map)
void kvm_set_msi_irq(struct kvm *kvm, struct kvm_kernel_irq_routing_entry *e, struct kvm_lapic_irq *irq)
static inline bool kvm_msi_route_invalid(struct kvm *kvm, struct kvm_kernel_irq_routing_entry *e)
int kvm_set_msi(struct kvm_kernel_irq_routing_entry *e, struct kvm *kvm, int irq_source_id, int level, bool line_status)
static int kvm_hv_set_sint(struct kvm_kernel_irq_routing_entry *e, struct kvm *kvm, int irq_source_id, int level, bool line_status)
int kvm_arch_set_irq_inatomic(struct kvm_kernel_irq_routing_entry *e, struct kvm *kvm, int irq_source_id, int level, bool line_status)
int kvm_request_irq_source_id(struct kvm *kvm)
void kvm_free_irq_source_id(struct kvm *kvm, int irq_source_id)
void kvm_register_irq_mask_notifier(struct kvm *kvm, int irq, struct kvm_irq_mask_notifier *kimn)
void kvm_unregister_irq_mask_notifier(struct kvm *kvm, int irq, struct kvm_irq_mask_notifier *kimn)
void kvm_fire_mask_notifiers(struct kvm *kvm, unsigned irqchip, unsigned pin, bool mask)
bool kvm_arch_can_set_irq_routing(struct kvm *kvm)
int kvm_set_routing_entry(struct kvm *kvm, struct kvm_kernel_irq_routing_entry *e, const struct kvm_irq_routing_entry *ue)
bool kvm_intr_is_single_vcpu(struct kvm *kvm, struct kvm_lapic_irq *irq, struct kvm_vcpu **dest_vcpu)
int kvm_setup_default_irq_routing(struct kvm *kvm)
int kvm_setup_empty_irq_routing(struct kvm *kvm)
void kvm_arch_post_irq_routing_update(struct kvm *kvm)
void kvm_scan_ioapic_routes(struct kvm_vcpu *vcpu, ulong *ioapic_handled_vectors)
void kvm_arch_irq_routing_update(struct kvm *kvm)
\n
     20 struct kvm *kvm
      8 struct kvm_kernel_irq_routing_entry *e
      6 int irq_source_id
      5 int level
      5 bool line_status
      3 struct kvm_lapic_irq *irq
      2 struct kvm_irq_mask_notifier *kimn
      2 int irq
      1 unsigned pin
      1 unsigned irqchip
      1 ulong *ioapic_handled_vectors
      1 struct kvm_vcpu *vcpu
      1 struct kvm_vcpu **dest_vcpu
      1 struct kvm_lapic *src
      1 struct dest_map *dest_map
      1 kvm_set_msi_irq
      1 kvm_intr_is_single_vcpu
      1 const struct kvm_irq_routing_entry *ue
      1 bool mask
