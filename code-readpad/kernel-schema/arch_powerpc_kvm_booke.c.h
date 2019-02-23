
\n
void kvmppc_dump_vcpu(struct kvm_vcpu *vcpu)
void kvmppc_vcpu_disable_spe(struct kvm_vcpu *vcpu)
static void kvmppc_vcpu_enable_spe(struct kvm_vcpu *vcpu)
static void kvmppc_vcpu_sync_spe(struct kvm_vcpu *vcpu)
static void kvmppc_vcpu_sync_spe(struct kvm_vcpu *vcpu)
if (!(vcpu->arch.shadow_msr & MSR_SPE)
)
kvmppc_vcpu_enable_spe(vcpu)
; kvmppc_vcpu_disable_spe(vcpu)
;} } static void kvmppc_vcpu_sync_spe(struct kvm_vcpu *vcpu)
static inline void kvmppc_load_guest_fp(struct kvm_vcpu *vcpu)
static inline void kvmppc_save_guest_fp(struct kvm_vcpu *vcpu)
static void kvmppc_vcpu_sync_fpu(struct kvm_vcpu *vcpu)
static inline void kvmppc_load_guest_altivec(struct kvm_vcpu *vcpu)
static inline void kvmppc_save_guest_altivec(struct kvm_vcpu *vcpu)
static void kvmppc_vcpu_sync_debug(struct kvm_vcpu *vcpu)
void kvmppc_set_msr(struct kvm_vcpu *vcpu, u32 new_msr)
static void kvmppc_booke_queue_irqprio(struct kvm_vcpu *vcpu, unsigned int priority)
void kvmppc_core_queue_dtlb_miss(struct kvm_vcpu *vcpu, ulong dear_flags, ulong esr_flags)
void kvmppc_core_queue_data_storage(struct kvm_vcpu *vcpu, ulong dear_flags, ulong esr_flags)
void kvmppc_core_queue_itlb_miss(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_inst_storage(struct kvm_vcpu *vcpu, ulong esr_flags)
static void kvmppc_core_queue_alignment(struct kvm_vcpu *vcpu, ulong dear_flags, ulong esr_flags)
void kvmppc_core_queue_program(struct kvm_vcpu *vcpu, ulong esr_flags)
void kvmppc_core_queue_fpunavail(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_vec_unavail(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_dec(struct kvm_vcpu *vcpu)
int kvmppc_core_pending_dec(struct kvm_vcpu *vcpu)
void kvmppc_core_dequeue_dec(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_external(struct kvm_vcpu *vcpu, struct kvm_interrupt *irq)
void kvmppc_core_dequeue_external(struct kvm_vcpu *vcpu)
static void kvmppc_core_queue_watchdog(struct kvm_vcpu *vcpu)
static void kvmppc_core_dequeue_watchdog(struct kvm_vcpu *vcpu)
void kvmppc_core_queue_debug(struct kvm_vcpu *vcpu)
void kvmppc_core_dequeue_debug(struct kvm_vcpu *vcpu)
static void set_guest_srr(struct kvm_vcpu *vcpu, unsigned long srr0, u32 srr1)
static void set_guest_csrr(struct kvm_vcpu *vcpu, unsigned long srr0, u32 srr1)
static void set_guest_dsrr(struct kvm_vcpu *vcpu, unsigned long srr0, u32 srr1)
static void set_guest_mcsrr(struct kvm_vcpu *vcpu, unsigned long srr0, u32 srr1)
static int kvmppc_booke_irqprio_deliver(struct kvm_vcpu *vcpu, unsigned int priority)
static unsigned long watchdog_next_timeout(struct kvm_vcpu *vcpu)
static void arm_next_watchdog(struct kvm_vcpu *vcpu)
void kvmppc_watchdog_func(struct timer_list *t)
static void update_timer_ints(struct kvm_vcpu *vcpu)
static void kvmppc_core_check_exceptions(struct kvm_vcpu *vcpu)
int kvmppc_core_prepare_to_enter(struct kvm_vcpu *vcpu)
int kvmppc_core_check_requests(struct kvm_vcpu *vcpu)
int kvmppc_vcpu_run(struct kvm_run *kvm_run, struct kvm_vcpu *vcpu)
static int emulation_exit(struct kvm_run *run, struct kvm_vcpu *vcpu)
static int kvmppc_handle_debug(struct kvm_run *run, struct kvm_vcpu *vcpu)
static void kvmppc_fill_pt_regs(struct pt_regs *regs)
static void kvmppc_restart_interrupt(struct kvm_vcpu *vcpu, unsigned int exit_nr)
static int kvmppc_resume_inst_load(struct kvm_run *run, struct kvm_vcpu *vcpu, enum emulation_result emulated, u32 last_inst)
int kvmppc_handle_exit(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int exit_nr)
static void kvmppc_set_tsr(struct kvm_vcpu *vcpu, u32 new_tsr)
int kvm_arch_vcpu_setup(struct kvm_vcpu *vcpu)
int kvmppc_subarch_vcpu_init(struct kvm_vcpu *vcpu)
void kvmppc_subarch_vcpu_uninit(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_get_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
int kvm_arch_vcpu_ioctl_set_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
static void get_sregs_base(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
static int set_sregs_base(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
static void get_sregs_arch206(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
static int set_sregs_arch206(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvmppc_get_sregs_ivor(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvmppc_set_sregs_ivor(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_get_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_set_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvmppc_get_one_reg(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
int kvmppc_set_one_reg(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
int kvm_arch_vcpu_ioctl_get_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
int kvm_arch_vcpu_ioctl_set_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
int kvm_arch_vcpu_ioctl_translate(struct kvm_vcpu *vcpu, struct kvm_translation *tr)
int kvm_vm_ioctl_get_dirty_log(struct kvm *kvm, struct kvm_dirty_log *log)
void kvmppc_core_free_memslot(struct kvm *kvm, struct kvm_memory_slot *free, struct kvm_memory_slot *dont)
int kvmppc_core_create_memslot(struct kvm *kvm, struct kvm_memory_slot *slot, unsigned long npages)
int kvmppc_core_prepare_memory_region(struct kvm *kvm, struct kvm_memory_slot *memslot, const struct kvm_userspace_memory_region *mem)
void kvmppc_core_commit_memory_region(struct kvm *kvm, const struct kvm_userspace_memory_region *mem, const struct kvm_memory_slot *old, const struct kvm_memory_slot *new, enum kvm_mr_change change)
void kvmppc_core_flush_memslot(struct kvm *kvm, struct kvm_memory_slot *memslot)
void kvmppc_set_epcr(struct kvm_vcpu *vcpu, u32 new_epcr)
void kvmppc_set_tcr(struct kvm_vcpu *vcpu, u32 new_tcr)
void kvmppc_set_tsr_bits(struct kvm_vcpu *vcpu, u32 tsr_bits)
void kvmppc_clr_tsr_bits(struct kvm_vcpu *vcpu, u32 tsr_bits)
void kvmppc_decrementer_func(struct kvm_vcpu *vcpu)
static int kvmppc_booke_add_breakpoint(struct debug_reg *dbg_reg, uint64_t addr, int index)
static int kvmppc_booke_add_watchpoint(struct debug_reg *dbg_reg, uint64_t addr, int type, int index)
dbg_reg->dbcr0 |= DBCR0_IDM;return 0; } void kvm_guest_protect_msr(struct kvm_vcpu *vcpu, ulong prot_bitmap, bool set)
int kvmppc_xlate(struct kvm_vcpu *vcpu, ulong eaddr, enum xlate_instdata xlid, enum xlate_readwrite xlrw, struct kvmppc_pte *pte)
int kvm_arch_vcpu_ioctl_set_guest_debug(struct kvm_vcpu *vcpu, struct kvm_guest_debug *dbg)
void kvmppc_booke_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
void kvmppc_booke_vcpu_put(struct kvm_vcpu *vcpu)
void kvmppc_mmu_destroy(struct kvm_vcpu *vcpu)
int kvmppc_core_init_vm(struct kvm *kvm)
struct kvm_vcpu *kvmppc_core_vcpu_create(struct kvm *kvm, unsigned int id)
void kvmppc_core_vcpu_free(struct kvm_vcpu *vcpu)
void kvmppc_core_destroy_vm(struct kvm *kvm)
void kvmppc_core_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
void kvmppc_core_vcpu_put(struct kvm_vcpu *vcpu)
int __init kvmppc_booke_init(void)
void __exit kvmppc_booke_exit(void)
\n
     81 struct kvm_vcpu *vcpu
      9 struct kvm *kvm
      8 struct kvm_sregs *sregs
      5 ulong esr_flags
      4 unsigned long srr0
      4 u32 srr1
      4 struct kvm_run *run
      3 ulong dear_flags
      2 void
      2 vcpu
      2 unsigned int priority
      2 unsigned int exit_nr
      2 union kvmppc_one_reg *val
      2 uint64_t addr
      2 u64 id
      2 u32 tsr_bits
      2 struct kvm_regs *regs
      2 struct kvm_memory_slot *memslot
      2 struct kvm_fpu *fpu
      2 struct debug_reg *dbg_reg
      2 int index
      2 int cpu
      2 const struct kvm_userspace_memory_region *mem
      1 !vcpu->arch.shadow_msr & MSR_SPE
      1 unsigned long npages
      1 unsigned int id
      1 ulong prot_bitmap
      1 ulong eaddr
      1 u32 new_tsr
      1 u32 new_tcr
      1 u32 new_msr
      1 u32 new_epcr
      1 u32 last_inst
      1 struct timer_list *t
      1 struct pt_regs *regs
      1 struct kvm_translation *tr
      1 struct kvm_run *kvm_run
      1 struct kvmppc_pte *pte
      1 struct kvm_memory_slot *slot
      1 struct kvm_memory_slot *free
      1 struct kvm_memory_slot *dont
      1 struct kvm_interrupt *irq
      1 struct kvm_guest_debug *dbg
      1 struct kvm_dirty_log *log
      1 int type
      1 enum xlate_readwrite xlrw
      1 enum xlate_instdata xlid
      1 enum kvm_mr_change change
      1 enum emulation_result emulated
      1 const struct kvm_memory_slot *old
      1 const struct kvm_memory_slot *new
      1 bool set
