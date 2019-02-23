
\n
int kvm_irq_map_gsi(struct kvm *kvm, struct kvm_kernel_irq_routing_entry *entries, int gsi)
int kvm_irq_map_chip_pin(struct kvm *kvm, unsigned irqchip, unsigned pin)
int kvm_send_userspace_msi(struct kvm *kvm, struct kvm_msi *msi)
int kvm_set_irq(struct kvm *kvm, int irq_source_id, u32 irq, int level, bool line_status)
static void free_irq_routing_table(struct kvm_irq_routing_table *rt)
void kvm_free_irq_routing(struct kvm *kvm)
static int setup_routing_entry(struct kvm *kvm, struct kvm_irq_routing_table *rt, struct kvm_kernel_irq_routing_entry *e, const struct kvm_irq_routing_entry *ue)
void __attribute__((weak)
)
kvm_arch_irq_routing_update(struct kvm *kvm)
bool __weak kvm_arch_can_set_irq_routing(struct kvm *kvm)
int kvm_set_irq_routing(struct kvm *kvm, const struct kvm_irq_routing_entry *ue, unsigned nr, unsigned flags)
\n
      9 struct kvm *kvm
      2 struct kvm_irq_routing_table *rt
      2 const struct kvm_irq_routing_entry *ue
      1 weak
      1 unsigned pin
      1 unsigned nr
      1 unsigned irqchip
      1 unsigned flags
      1 u32 irq
      1 struct kvm_msi *msi
      1 struct kvm_kernel_irq_routing_entry *entries
      1 struct kvm_kernel_irq_routing_entry *e
      1 int level
      1 int irq_source_id
      1 int gsi
      1 bool line_status
