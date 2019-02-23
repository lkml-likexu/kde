
EXPORT_SYMBOL_GPL(kvm_slot_page_track_add_page);
EXPORT_SYMBOL_GPL(kvm_slot_page_track_remove_page);
EXPORT_SYMBOL_GPL(kvm_page_track_register_notifier);
EXPORT_SYMBOL_GPL(kvm_page_track_unregister_notifier);
\n
void kvm_page_track_free_memslot(struct kvm_memory_slot *free, struct kvm_memory_slot *dont)
int kvm_page_track_create_memslot(struct kvm_memory_slot *slot, unsigned long npages)
static inline bool page_track_mode_is_valid(enum kvm_page_track_mode mode)
static void update_gfn_track(struct kvm_memory_slot *slot, gfn_t gfn, enum kvm_page_track_mode mode, short count)
void kvm_slot_page_track_add_page(struct kvm *kvm, struct kvm_memory_slot *slot, gfn_t gfn, enum kvm_page_track_mode mode)
void kvm_slot_page_track_remove_page(struct kvm *kvm, struct kvm_memory_slot *slot, gfn_t gfn, enum kvm_page_track_mode mode)
bool kvm_page_track_is_active(struct kvm_vcpu *vcpu, gfn_t gfn, enum kvm_page_track_mode mode)
void kvm_page_track_cleanup(struct kvm *kvm)
void kvm_page_track_init(struct kvm *kvm)
void kvm_page_track_register_notifier(struct kvm *kvm, struct kvm_page_track_notifier_node *n)
void kvm_page_track_unregister_notifier(struct kvm *kvm, struct kvm_page_track_notifier_node *n)
void kvm_page_track_write(struct kvm_vcpu *vcpu, gpa_t gpa, const u8 *new, int bytes)
void kvm_page_track_flush_slot(struct kvm *kvm, struct kvm_memory_slot *slot)
\n
      7 struct kvm *kvm
      5 struct kvm_memory_slot *slot
      5 enum kvm_page_track_mode mode
      4 gfn_t gfn
      2 struct kvm_vcpu *vcpu
      2 struct kvm_page_track_notifier_node *n
      1 unsigned long npages
      1 struct kvm_memory_slot *free
      1 struct kvm_memory_slot *dont
      1 short count
      1 kvm_slot_page_track_remove_page
      1 kvm_slot_page_track_add_page
      1 kvm_page_track_unregister_notifier
      1 kvm_page_track_register_notifier
      1 int bytes
      1 gpa_t gpa
      1 const u8 *new
