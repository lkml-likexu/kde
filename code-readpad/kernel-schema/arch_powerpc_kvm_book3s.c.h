
EXPORT_SYMBOL_GPL(kvmppc_unfixup_split_real);
EXPORT_SYMBOL_GPL(kvmppc_book3s_queue_irqprio);
EXPORT_SYMBOL_GPL(kvmppc_core_queue_program);
EXPORT_SYMBOL_GPL(kvmppc_core_queue_dec);
EXPORT_SYMBOL_GPL(kvmppc_core_pending_dec);
EXPORT_SYMBOL_GPL(kvmppc_core_dequeue_dec);
EXPORT_SYMBOL_GPL(kvmppc_core_queue_data_storage);
EXPORT_SYMBOL_GPL(kvmppc_core_queue_inst_storage);
EXPORT_SYMBOL_GPL(kvmppc_core_prepare_to_enter);
EXPORT_SYMBOL_GPL(kvmppc_gpa_to_pfn);
EXPORT_SYMBOL_GPL(kvmppc_load_last_inst);
EXPORT_SYMBOL_GPL(kvmppc_set_msr);
EXPORT_SYMBOL_GPL(kvmppc_h_logical_ci_load);
EXPORT_SYMBOL_GPL(kvmppc_h_logical_ci_store);
\n
void kvmppc_unfixup_split_real(struct kvm_vcpu *vcpu)
static inline unsigned long kvmppc_interrupt_offset(struct kvm_vcpu *vcpu)
static inline void kvmppc_update_int_pending(struct kvm_vcpu *vcpu, unsigned long pending_now, unsigned long old_pending)
static inline bool kvmppc_critical_section(struct kvm_vcpu *vcpu)
void kvmppc_inject_interrupt(struct kvm_vcpu *vcpu, int vec, u64 flags)
static int kvmppc_book3s_vec2irqprio(unsigned int vec)
void kvmppc_book3s_dequeue_irqprio(struct kvm_vcpu *vcpu, unsigned int vec)
void kvmppc_book3s_queue_irqprio(struct kvm_vcpu *vcpu, unsigned int vec)
void kvmppc_core_queue_program(struct kvm_vcpu *vcpu, ulong flags)
void kvmppc_core_queue_fpunavail(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_vec_unavail(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_vsx_unavail(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_dec(struct kvm_vcpu *vcpu)
int kvmppc_core_pending_dec(struct kvm_vcpu *vcpu)
void kvmppc_core_dequeue_dec(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_external(struct kvm_vcpu *vcpu, struct kvm_interrupt *irq)
void kvmppc_core_dequeue_external(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_data_storage(struct kvm_vcpu *vcpu, ulong dar, ulong flags)
void kvmppc_core_queue_inst_storage(struct kvm_vcpu *vcpu, ulong flags)
static int kvmppc_book3s_irqprio_deliver(struct kvm_vcpu *vcpu, unsigned int priority)
static bool clear_irqprio(struct kvm_vcpu *vcpu, unsigned int priority)
int kvmppc_core_prepare_to_enter(struct kvm_vcpu *vcpu)
kvm_pfn_t kvmppc_gpa_to_pfn(struct kvm_vcpu *vcpu, gpa_t gpa, bool writing, bool *writable)
int kvmppc_xlate(struct kvm_vcpu *vcpu, ulong eaddr, enum xlate_instdata xlid, enum xlate_readwrite xlrw, struct kvmppc_pte *pte)
int kvmppc_load_last_inst(struct kvm_vcpu *vcpu, enum instruction_fetch_type type, u32 *inst)
int kvm_arch_vcpu_setup(struct kvm_vcpu *vcpu)
int kvmppc_subarch_vcpu_init(struct kvm_vcpu *vcpu)
void kvmppc_subarch_vcpu_uninit(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_get_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_set_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_get_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
int kvm_arch_vcpu_ioctl_set_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
int kvm_arch_vcpu_ioctl_get_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
int kvm_arch_vcpu_ioctl_set_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
int kvmppc_get_one_reg(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
int kvmppc_set_one_reg(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
void kvmppc_core_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
void kvmppc_core_vcpu_put(struct kvm_vcpu *vcpu)
void kvmppc_set_msr(struct kvm_vcpu *vcpu, u64 msr)
int kvmppc_vcpu_run(struct kvm_run *kvm_run, struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_translate(struct kvm_vcpu *vcpu, struct kvm_translation *tr)
int kvm_arch_vcpu_ioctl_set_guest_debug(struct kvm_vcpu *vcpu, struct kvm_guest_debug *dbg)
void kvmppc_decrementer_func(struct kvm_vcpu *vcpu)
struct kvm_vcpu *kvmppc_core_vcpu_create(struct kvm *kvm, unsigned int id)
void kvmppc_core_vcpu_free(struct kvm_vcpu *vcpu)
int kvmppc_core_check_requests(struct kvm_vcpu *vcpu)
int kvm_vm_ioctl_get_dirty_log(struct kvm *kvm, struct kvm_dirty_log *log)
void kvmppc_core_free_memslot(struct kvm *kvm, struct kvm_memory_slot *free, struct kvm_memory_slot *dont)
int kvmppc_core_create_memslot(struct kvm *kvm, struct kvm_memory_slot *slot, unsigned long npages)
void kvmppc_core_flush_memslot(struct kvm *kvm, struct kvm_memory_slot *memslot)
int kvmppc_core_prepare_memory_region(struct kvm *kvm, struct kvm_memory_slot *memslot, const struct kvm_userspace_memory_region *mem)
void kvmppc_core_commit_memory_region(struct kvm *kvm, const struct kvm_userspace_memory_region *mem, const struct kvm_memory_slot *old, const struct kvm_memory_slot *new, enum kvm_mr_change change)
int kvm_unmap_hva_range(struct kvm *kvm, unsigned long start, unsigned long end)
int kvm_age_hva(struct kvm *kvm, unsigned long start, unsigned long end)
int kvm_test_age_hva(struct kvm *kvm, unsigned long hva)
int kvm_set_spte_hva(struct kvm *kvm, unsigned long hva, pte_t pte)
void kvmppc_mmu_destroy(struct kvm_vcpu *vcpu)
int kvmppc_core_init_vm(struct kvm *kvm)
void kvmppc_core_destroy_vm(struct kvm *kvm)
int kvmppc_h_logical_ci_load(struct kvm_vcpu *vcpu)
int kvmppc_h_logical_ci_store(struct kvm_vcpu *vcpu)
int kvmppc_core_check_processor_compat(void)
int kvmppc_book3s_hcall_implemented(struct kvm *kvm, unsigned long hcall)
int kvm_set_irq(struct kvm *kvm, int irq_source_id, u32 irq, int level, bool line_status)
int kvm_arch_set_irq_inatomic(struct kvm_kernel_irq_routing_entry *irq_entry, struct kvm *kvm, int irq_source_id, int level, bool line_status)
int kvm_arch_set_irq_inatomic(struct kvm_kernel_irq_routing_entry *irq_entry, struct kvm *kvm, int irq_source_id, int level, bool line_status)
return kvm_set_irq(kvm, irq_source_id, irq_entry->gsi, level, line_status)
; } static int kvmppc_book3s_set_irq(struct kvm_kernel_irq_routing_entry *e, struct kvm *kvm, int irq_source_id, int level, bool line_status)
int kvm_irq_map_gsi(struct kvm *kvm, struct kvm_kernel_irq_routing_entry *entries, int gsi)
int kvm_irq_map_chip_pin(struct kvm *kvm, unsigned irqchip, unsigned pin)
static int kvmppc_book3s_init(void)
static void kvmppc_book3s_exit(void)
\n
     47 struct kvm_vcpu *vcpu
     20 struct kvm *kvm
      4 int level
      4 int irq_source_id
      4 bool line_status
      3 void
      3 unsigned int vec
      3 ulong flags
      2 unsigned long start
      2 unsigned long hva
      2 unsigned long end
      2 unsigned int priority
      2 union kvmppc_one_reg *val
      2 u64 id
      2 struct kvm_sregs *sregs
      2 struct kvm_regs *regs
      2 struct kvm_memory_slot *memslot
      2 struct kvm_kernel_irq_routing_entry *irq_entry
      2 struct kvm_fpu *fpu
      2 const struct kvm_userspace_memory_region *mem
      1 unsigned pin
      1 unsigned long pending_now
      1 unsigned long old_pending
      1 unsigned long npages
      1 unsigned long hcall
      1 unsigned irqchip
      1 unsigned int id
      1 ulong eaddr
      1 ulong dar
      1 u64 msr
      1 u64 flags
      1 u32 irq
      1 u32 *inst
      1 struct kvm_translation *tr
      1 struct kvm_run *kvm_run
      1 struct kvmppc_pte *pte
      1 struct kvm_memory_slot *slot
      1 struct kvm_memory_slot *free
      1 struct kvm_memory_slot *dont
      1 struct kvm_kernel_irq_routing_entry *entries
      1 struct kvm_kernel_irq_routing_entry *e
      1 struct kvm_interrupt *irq
      1 struct kvm_guest_debug *dbg
      1 struct kvm_dirty_log *log
      1 pte_t pte
      1 line_status
      1 level
      1 kvmppc_unfixup_split_real
      1 kvmppc_set_msr
      1 kvmppc_load_last_inst
      1 kvmppc_h_logical_ci_store
      1 kvmppc_h_logical_ci_load
      1 kvmppc_gpa_to_pfn
      1 kvmppc_core_queue_program
      1 kvmppc_core_queue_inst_storage
      1 kvmppc_core_queue_dec
      1 kvmppc_core_queue_data_storage
      1 kvmppc_core_prepare_to_enter
      1 kvmppc_core_pending_dec
      1 kvmppc_core_dequeue_dec
      1 kvmppc_book3s_queue_irqprio
      1 kvm
      1 irq_source_id
      1 irq_entry->gsi
      1 int vec
      1 int gsi
      1 int cpu
      1 gpa_t gpa
      1 enum xlate_readwrite xlrw
      1 enum xlate_instdata xlid
      1 enum kvm_mr_change change
      1 enum instruction_fetch_type type
      1 const struct kvm_memory_slot *old
      1 const struct kvm_memory_slot *new
      1 bool writing
      1 bool *writable
