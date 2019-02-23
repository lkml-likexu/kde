
\n
static inline bool nesting_enabled(struct kvm *kvm)
static inline struct kvm_vcpu *next_runnable_thread(struct kvmppc_vcore *vc, int *ip)
static bool kvmppc_ipi_thread(int cpu)
static void kvmppc_fast_vcpu_kick_hv(struct kvm_vcpu *vcpu)
static void kvmppc_core_start_stolen(struct kvmppc_vcore *vc)
static void kvmppc_core_end_stolen(struct kvmppc_vcore *vc)
static void kvmppc_core_vcpu_load_hv(struct kvm_vcpu *vcpu, int cpu)
static void kvmppc_core_vcpu_put_hv(struct kvm_vcpu *vcpu)
static void kvmppc_set_msr_hv(struct kvm_vcpu *vcpu, u64 msr)
static void kvmppc_set_pvr_hv(struct kvm_vcpu *vcpu, u32 pvr)
static int kvmppc_set_arch_compat(struct kvm_vcpu *vcpu, u32 arch_compat)
static void kvmppc_dump_regs(struct kvm_vcpu *vcpu)
static struct kvm_vcpu *kvmppc_find_vcpu(struct kvm *kvm, int id)
static void init_vpa(struct kvm_vcpu *vcpu, struct lppaca *vpa)
static int set_vpa(struct kvm_vcpu *vcpu, struct kvmppc_vpa *v, unsigned long addr, unsigned long len)
static int vpa_is_registered(struct kvmppc_vpa *vpap)
static unsigned long do_h_register_vpa(struct kvm_vcpu *vcpu, unsigned long flags, unsigned long vcpuid, unsigned long vpa)
static void kvmppc_update_vpa(struct kvm_vcpu *vcpu, struct kvmppc_vpa *vpap)
static void kvmppc_update_vpas(struct kvm_vcpu *vcpu)
static u64 vcore_stolen_time(struct kvmppc_vcore *vc, u64 now)
static void kvmppc_create_dtl_entry(struct kvm_vcpu *vcpu, struct kvmppc_vcore *vc)
static bool kvmppc_doorbell_pending(struct kvm_vcpu *vcpu)
static bool kvmppc_power8_compatible(struct kvm_vcpu *vcpu)
static int kvmppc_h_set_mode(struct kvm_vcpu *vcpu, unsigned long mflags, unsigned long resource, unsigned long value1, unsigned long value2)
static int kvm_arch_vcpu_yield_to(struct kvm_vcpu *target)
static int kvmppc_get_yield_count(struct kvm_vcpu *vcpu)
int kvmppc_pseries_do_hcall(struct kvm_vcpu *vcpu)
static void kvmppc_nested_cede(struct kvm_vcpu *vcpu)
static int kvmppc_hcall_impl_hv(unsigned long cmd)
static int kvmppc_emulate_debug_inst(struct kvm_run *run, struct kvm_vcpu *vcpu)
static void do_nothing(void *x)
static unsigned long kvmppc_read_dpdes(struct kvm_vcpu *vcpu)
static int kvmppc_emulate_doorbell_instr(struct kvm_vcpu *vcpu)
static int kvmppc_handle_exit_hv(struct kvm_run *run, struct kvm_vcpu *vcpu, struct task_struct *tsk)
static int kvmppc_handle_nested_exit(struct kvm_run *run, struct kvm_vcpu *vcpu)
static int kvm_arch_vcpu_ioctl_get_sregs_hv(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
static int kvm_arch_vcpu_ioctl_set_sregs_hv(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
static void kvmppc_set_lpcr(struct kvm_vcpu *vcpu, u64 new_lpcr, bool preserve_top32)
static int kvmppc_get_one_reg_hv(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
static int kvmppc_set_one_reg_hv(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
static int threads_per_vcore(struct kvm *kvm)
static struct kvmppc_vcore *kvmppc_vcore_create(struct kvm *kvm, int id)
static int debugfs_timings_open(struct inode *inode, struct file *file)
static int debugfs_timings_release(struct inode *inode, struct file *file)
static ssize_t debugfs_timings_read(struct file *file, char __user *buf, size_t len, loff_t *ppos)
static ssize_t debugfs_timings_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
static void debugfs_vcpu_init(struct kvm_vcpu *vcpu, unsigned int id)
static void debugfs_vcpu_init(struct kvm_vcpu *vcpu, unsigned int id)
static struct kvm_vcpu *kvmppc_core_vcpu_create_hv(struct kvm *kvm, unsigned int id)
static int kvmhv_set_smt_mode(struct kvm *kvm, unsigned long smt_mode, unsigned long flags)
static void unpin_vpa(struct kvm *kvm, struct kvmppc_vpa *vpa)
static void kvmppc_core_vcpu_free_hv(struct kvm_vcpu *vcpu)
static int kvmppc_core_check_requests_hv(struct kvm_vcpu *vcpu)
static void kvmppc_set_timer(struct kvm_vcpu *vcpu)
static void kvmppc_end_cede(struct kvm_vcpu *vcpu)
static void kvmppc_remove_runnable(struct kvmppc_vcore *vc, struct kvm_vcpu *vcpu)
static int kvmppc_grab_hwthread(int cpu)
static void kvmppc_release_hwthread(int cpu)
static void radix_flush_cpu(struct kvm *kvm, int cpu, struct kvm_vcpu *vcpu)
static void kvmppc_prepare_radix_vcpu(struct kvm_vcpu *vcpu, int pcpu)
static void kvmppc_radix_check_need_tlb_flush(struct kvm *kvm, int pcpu, struct kvm_nested_guest *nested)
static void kvmppc_start_thread(struct kvm_vcpu *vcpu, struct kvmppc_vcore *vc)
static void kvmppc_wait_for_nap(int n_threads)
static int on_primary_thread(void)
static void init_vcore_lists(void)
static void kvmppc_vcore_preempt(struct kvmppc_vcore *vc)
static void kvmppc_vcore_end_preempt(struct kvmppc_vcore *vc)
static void init_core_info(struct core_info *cip, struct kvmppc_vcore *vc)
static bool subcore_config_ok(int n_subcores, int n_threads)
static void init_vcore_to_run(struct kvmppc_vcore *vc)
static bool can_dynamic_split(struct kvmppc_vcore *vc, struct core_info *cip)
static bool can_piggyback(struct kvmppc_vcore *pvc, struct core_info *cip, int target_threads)
static void prepare_threads(struct kvmppc_vcore *vc)
static void collect_piggybacks(struct core_info *cip, int target_threads)
static bool recheck_signals(struct core_info *cip)
static void post_guest_process(struct kvmppc_vcore *vc, bool is_master)
static inline int kvmppc_clear_host_core(unsigned int cpu)
static inline int kvmppc_set_host_core(unsigned int cpu)
static void set_irq_happened(int trap)
static noinline void kvmppc_run_core(struct kvmppc_vcore *vc)
static int kvmhv_load_hv_regs_and_go(struct kvm_vcpu *vcpu, u64 time_limit, unsigned long lpcr)
int kvmhv_p9_guest_entry(struct kvm_vcpu *vcpu, u64 time_limit, unsigned long lpcr)
static void kvmppc_wait_for_exec(struct kvmppc_vcore *vc, struct kvm_vcpu *vcpu, int wait_state)
static void grow_halt_poll_ns(struct kvmppc_vcore *vc)
static void shrink_halt_poll_ns(struct kvmppc_vcore *vc)
static inline bool xive_interrupt_pending(struct kvm_vcpu *vcpu)
static inline bool xive_interrupt_pending(struct kvm_vcpu *vcpu)
if (!xive_enabled()
)
return false;return vcpu->arch.irq_pending || vcpu->arch.xive_saved_state.pipr < vcpu->arch.xive_saved_state.cppr; } static inline bool xive_interrupt_pending(struct kvm_vcpu *vcpu)
static bool kvmppc_vcpu_woken(struct kvm_vcpu *vcpu)
static int kvmppc_vcore_check_block(struct kvmppc_vcore *vc)
static void kvmppc_vcore_blocked(struct kvmppc_vcore *vc)
static int kvmhv_setup_mmu(struct kvm_vcpu *vcpu)
static int kvmppc_run_vcpu(struct kvm_run *kvm_run, struct kvm_vcpu *vcpu)
int kvmhv_run_single_vcpu(struct kvm_run *kvm_run, struct kvm_vcpu *vcpu, u64 time_limit, unsigned long lpcr)
static int kvmppc_vcpu_run_hv(struct kvm_run *run, struct kvm_vcpu *vcpu)
static void kvmppc_add_seg_page_size(struct kvm_ppc_one_seg_page_size **sps, int shift, int sllp)
static int kvm_vm_ioctl_get_smmu_info_hv(struct kvm *kvm, struct kvm_ppc_smmu_info *info)
static int kvm_vm_ioctl_get_dirty_log_hv(struct kvm *kvm, struct kvm_dirty_log *log)
static void kvmppc_core_free_memslot_hv(struct kvm_memory_slot *free, struct kvm_memory_slot *dont)
static int kvmppc_core_create_memslot_hv(struct kvm_memory_slot *slot, unsigned long npages)
static int kvmppc_core_prepare_memory_region_hv(struct kvm *kvm, struct kvm_memory_slot *memslot, const struct kvm_userspace_memory_region *mem)
static void kvmppc_core_commit_memory_region_hv(struct kvm *kvm, const struct kvm_userspace_memory_region *mem, const struct kvm_memory_slot *old, const struct kvm_memory_slot *new, enum kvm_mr_change change)
void kvmppc_update_lpcr(struct kvm *kvm, unsigned long lpcr, unsigned long mask)
static void kvmppc_mmu_destroy_hv(struct kvm_vcpu *vcpu)
void kvmppc_setup_partition_table(struct kvm *kvm)
static int kvmppc_hv_setup_htab_rma(struct kvm_vcpu *vcpu)
int kvmppc_switch_mmu_to_hpt(struct kvm *kvm)
int kvmppc_switch_mmu_to_radix(struct kvm *kvm)
void kvmppc_alloc_host_rm_ops(void)
void kvmppc_free_host_rm_ops(void)
static int kvmppc_core_init_vm_hv(struct kvm *kvm)
static void kvmppc_free_vcores(struct kvm *kvm)
static void kvmppc_core_destroy_vm_hv(struct kvm *kvm)
static int kvmppc_core_emulate_op_hv(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int inst, int *advance)
static int kvmppc_core_emulate_mtspr_hv(struct kvm_vcpu *vcpu, int sprn, ulong spr_val)
static int kvmppc_core_emulate_mfspr_hv(struct kvm_vcpu *vcpu, int sprn, ulong *spr_val)
static int kvmppc_core_check_processor_compat_hv(void)
void kvmppc_free_pimap(struct kvm *kvm)
static struct kvmppc_passthru_irqmap *kvmppc_alloc_pimap(void)
static int kvmppc_set_passthru_irq(struct kvm *kvm, int host_irq, int guest_gsi)
static int kvmppc_clr_passthru_irq(struct kvm *kvm, int host_irq, int guest_gsi)
static int kvmppc_irq_bypass_add_producer_hv(struct irq_bypass_consumer *cons, struct irq_bypass_producer *prod)
static void kvmppc_irq_bypass_del_producer_hv(struct irq_bypass_consumer *cons, struct irq_bypass_producer *prod)
static long kvm_arch_vm_ioctl_hv(struct file *filp, unsigned int ioctl, unsigned long arg)
static void init_default_hcalls(void)
static int kvmhv_configure_mmu(struct kvm *kvm, struct kvm_ppc_mmuv3_cfg *cfg)
static int kvmhv_enable_nested(struct kvm *kvm)
static int kvmhv_load_from_eaddr(struct kvm_vcpu *vcpu, ulong *eaddr, void *ptr, int size)
static int kvmhv_store_to_eaddr(struct kvm_vcpu *vcpu, ulong *eaddr, void *ptr, int size)
static int kvm_init_subcore_bitmap(void)
static int kvmppc_radix_possible(void)
static int kvmppc_book3s_init_hv(void)
static void kvmppc_book3s_exit_hv(void)
\n
     57 struct kvm_vcpu *vcpu
     25 struct kvm *kvm
     20 struct kvmppc_vcore *vc
     11 void
      5 struct kvm_run *run
      5 struct core_info *cip
      5 int cpu
      4 unsigned long lpcr
      4 struct file *file
      3 unsigned int id
      3 u64 time_limit
      2 void *ptr
      2 unsigned long flags
      2 unsigned int cpu
      2 union kvmppc_one_reg *val
      2 ulong *eaddr
      2 u64 id
      2 struct kvm_sregs *sregs
      2 struct kvm_run *kvm_run
      2 struct kvmppc_vpa *vpap
      2 struct irq_bypass_producer *prod
      2 struct irq_bypass_consumer *cons
      2 struct inode *inode
      2 size_t len
      2 loff_t *ppos
      2 int target_threads
      2 int sprn
      2 int size
      2 int pcpu
      2 int n_threads
      2 int id
      2 int host_irq
      2 int guest_gsi
      2 const struct kvm_userspace_memory_region *mem
      1 !xive_enabled
      1 void *x
      1 unsigned long vpa
      1 unsigned long vcpuid
      1 unsigned long value2
      1 unsigned long value1
      1 unsigned long smt_mode
      1 unsigned long resource
      1 unsigned long npages
      1 unsigned long mflags
      1 unsigned long mask
      1 unsigned long len
      1 unsigned long cmd
      1 unsigned long arg
      1 unsigned long addr
      1 unsigned int ioctl
      1 unsigned int inst
      1 ulong spr_val
      1 ulong *spr_val
      1 u64 now
      1 u64 new_lpcr
      1 u64 msr
      1 u32 pvr
      1 u32 arch_compat
      1 struct task_struct *tsk
      1 struct lppaca *vpa
      1 struct kvm_vcpu *target
      1 struct kvmppc_vpa *vpa
      1 struct kvmppc_vpa *v
      1 struct kvmppc_vcore *pvc
      1 struct kvm_ppc_smmu_info *info
      1 struct kvm_ppc_one_seg_page_size **sps
      1 struct kvm_ppc_mmuv3_cfg *cfg
      1 struct kvm_nested_guest *nested
      1 struct kvm_memory_slot *slot
      1 struct kvm_memory_slot *memslot
      1 struct kvm_memory_slot *free
      1 struct kvm_memory_slot *dont
      1 struct kvm_dirty_log *log
      1 struct file *filp
      1 int wait_state
      1 int trap
      1 int sllp
      1 int shift
      1 int n_subcores
      1 int *ip
      1 int *advance
      1 enum kvm_mr_change change
      1 const struct kvm_memory_slot *old
      1 const struct kvm_memory_slot *new
      1 const char __user *buf
      1 char __user *buf
      1 bool preserve_top32
      1 bool is_master
