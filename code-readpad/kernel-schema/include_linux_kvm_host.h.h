
\n
static inline bool is_error_pfn(kvm_pfn_t pfn)
static inline bool is_error_noslot_pfn(kvm_pfn_t pfn)
static inline bool is_noslot_pfn(kvm_pfn_t pfn)
static inline bool kvm_is_error_hva(unsigned long addr)
static inline bool is_error_page(struct page *page)
static inline int kvm_vcpu_exiting_guest_mode(struct kvm_vcpu *vcpu)
static inline unsigned long kvm_dirty_bitmap_bytes(struct kvm_memory_slot *memslot)
static inline unsigned long *kvm_second_dirty_bitmap(struct kvm_memory_slot *memslot)
static inline int kvm_arch_vcpu_memslots_id(struct kvm_vcpu *vcpu)
static inline struct kvm_io_bus *kvm_get_bus(struct kvm *kvm, enum kvm_bus idx)
static inline struct kvm_vcpu *kvm_get_vcpu(struct kvm *kvm, int i)
static inline struct kvm_vcpu *kvm_get_vcpu_by_id(struct kvm *kvm, int id)
static inline int kvm_vcpu_get_idx(struct kvm_vcpu *vcpu)
void kvm_arch_post_irq_ack_notifier_list_update(struct kvm *kvm)
; void kvm_arch_post_irq_routing_update(struct kvm *kvm)
; static inline void kvm_arch_post_irq_ack_notifier_list_update(struct kvm *kvm)
void kvm_arch_post_irq_ack_notifier_list_update(struct kvm *kvm)
; void kvm_arch_post_irq_routing_update(struct kvm *kvm)
; static inline void kvm_arch_post_irq_ack_notifier_list_update(struct kvm *kvm)
} static inline void kvm_arch_post_irq_routing_update(struct kvm *kvm)
int kvm_irqfd_init(void)
; void kvm_irqfd_exit(void)
; static inline int kvm_irqfd_init(void)
static inline void kvm_irqfd_exit(void)
static inline struct kvm_memslots *__kvm_memslots(struct kvm *kvm, int as_id)
static inline struct kvm_memslots *kvm_memslots(struct kvm *kvm)
static inline struct kvm_memslots *kvm_vcpu_memslots(struct kvm_vcpu *vcpu)
static inline struct kvm_memory_slot * id_to_memslot(struct kvm_memslots *slots, int id)
static inline struct kvm *kvm_arch_alloc_vm(void)
static inline void kvm_arch_free_vm(struct kvm *kvm)
static inline int kvm_arch_flush_remote_tlb(struct kvm *kvm)
void kvm_arch_register_noncoherent_dma(struct kvm *kvm)
; void kvm_arch_unregister_noncoherent_dma(struct kvm *kvm)
; bool kvm_arch_has_noncoherent_dma(struct kvm *kvm)
; static inline void kvm_arch_register_noncoherent_dma(struct kvm *kvm)
static inline void kvm_arch_unregister_noncoherent_dma(struct kvm *kvm)
static inline bool kvm_arch_has_noncoherent_dma(struct kvm *kvm)
static inline bool kvm_arch_has_noncoherent_dma(struct kvm *kvm)
return false; }endif void kvm_arch_start_assignment(struct kvm *kvm)
; void kvm_arch_end_assignment(struct kvm *kvm)
; bool kvm_arch_has_assigned_device(struct kvm *kvm)
; static inline void kvm_arch_start_assignment(struct kvm *kvm)
static inline void kvm_arch_end_assignment(struct kvm *kvm)
static inline bool kvm_arch_has_assigned_device(struct kvm *kvm)
static inline struct swait_queue_head *kvm_arch_vcpu_wq(struct kvm_vcpu *vcpu)
bool kvm_arch_intc_initialized(struct kvm *kvm)
; static inline bool kvm_arch_intc_initialized(struct kvm *kvm)
static inline struct kvm_memory_slot * search_memslots(struct kvm_memslots *slots, gfn_t gfn)
static inline struct kvm_memory_slot * __gfn_to_memslot(struct kvm_memslots *slots, gfn_t gfn)
static inline unsigned long __gfn_to_hva_memslot(struct kvm_memory_slot *slot, gfn_t gfn)
static inline int memslot_id(struct kvm *kvm, gfn_t gfn)
static inline gfn_t hva_to_gfn_memslot(unsigned long hva, struct kvm_memory_slot *slot)
static inline gpa_t gfn_to_gpa(gfn_t gfn)
static inline gfn_t gpa_to_gfn(gpa_t gpa)
static inline hpa_t pfn_to_hpa(kvm_pfn_t pfn)
static inline struct page *kvm_vcpu_gpa_to_page(struct kvm_vcpu *vcpu, gpa_t gpa)
static inline bool kvm_is_error_gpa(struct kvm *kvm, gpa_t gpa)
static inline int mmu_notifier_retry(struct kvm *kvm, unsigned long mmu_seq)
int kvm_irqfd(struct kvm *kvm, struct kvm_irqfd *args)
; void kvm_irqfd_release(struct kvm *kvm)
; void kvm_irq_routing_update(struct kvm *)
; static inline int kvm_irqfd(struct kvm *kvm, struct kvm_irqfd *args)
static inline int kvm_irqfd(struct kvm *kvm, struct kvm_irqfd *args)
static inline void kvm_irq_routing_update(struct kvm *kvm)
static inline int kvm_ioeventfd(struct kvm *kvm, struct kvm_ioeventfd *args)
static inline void kvm_make_request(int req, struct kvm_vcpu *vcpu)
static inline bool kvm_request_pending(struct kvm_vcpu *vcpu)
static inline bool kvm_test_request(int req, struct kvm_vcpu *vcpu)
static inline void kvm_clear_request(int req, struct kvm_vcpu *vcpu)
static inline bool kvm_check_request(int req, struct kvm_vcpu *vcpu)
static inline void kvm_vcpu_set_in_spin_loop(struct kvm_vcpu *vcpu, bool val)
static inline void kvm_vcpu_set_in_spin_loop(struct kvm_vcpu *vcpu, bool val)
vcpu->spin_loop.in_spin_loop = val; } static inline void kvm_vcpu_set_dy_eligible(struct kvm_vcpu *vcpu, bool val)
static inline void kvm_vcpu_set_in_spin_loop(struct kvm_vcpu *vcpu, bool val)
static inline void kvm_vcpu_set_dy_eligible(struct kvm_vcpu *vcpu, bool val)
static inline bool vcpu_valid_wakeup(struct kvm_vcpu *vcpu)
static inline bool vcpu_valid_wakeup(struct kvm_vcpu *vcpu)
long kvm_arch_vcpu_async_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
; static inline long kvm_arch_vcpu_async_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
int kvm_arch_vcpu_run_pid_change(struct kvm_vcpu *vcpu)
; static inline int kvm_arch_vcpu_run_pid_change(struct kvm_vcpu *vcpu)
\n
     38 struct kvm *kvm
     20 struct kvm_vcpu *vcpu
      5 void
      5 gfn_t gfn
      5 bool val
      4 kvm_pfn_t pfn
      4 int req
      3 struct kvm_memslots *slots
      3 struct kvm_irqfd *args
      3 gpa_t gpa
      2 unsigned long arg
      2 unsigned int ioctl
      2 struct kvm_memory_slot *slot
      2 struct kvm_memory_slot *memslot
      2 struct file *filp
      2 int id
      1 unsigned long mmu_seq
      1 unsigned long hva
      1 unsigned long addr
      1 struct page *page
      1 struct kvm_ioeventfd *args
      1 struct kvm *
      1 int i
      1 int as_id
      1 enum kvm_bus idx
