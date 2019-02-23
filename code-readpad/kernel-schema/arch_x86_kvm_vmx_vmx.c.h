
\n
static int vmx_setup_l1d_flush(enum vmx_l1d_flush_state l1tf)
static int vmentry_l1d_flush_parse(const char *s)
static int vmentry_l1d_flush_set(const char *s, const struct kernel_param *kp)
static int vmentry_l1d_flush_get(char *s, const struct kernel_param *kp)
static void check_ept_pointer_match(struct kvm *kvm)
static int kvm_fill_hv_flush_list_func(struct hv_guest_mapping_flush_list *flush, void *data)
static inline int __hv_remote_flush_tlb_with_range(struct kvm *kvm, struct kvm_vcpu *vcpu, struct kvm_tlb_range *range)
static int hv_remote_flush_tlb_with_range(struct kvm *kvm, struct kvm_tlb_range *range)
spin_unlock(&to_kvm_vmx(kvm)
->ept_pointer_lock)
;return ret; } static int hv_remote_flush_tlb(struct kvm *kvm)
static inline bool cpu_has_broken_vmx_preemption_timer(void)
static inline bool cpu_need_virtualize_apic_accesses(struct kvm_vcpu *vcpu)
static inline bool report_flexpriority(void)
static inline int __find_msr_index(struct vcpu_vmx *vmx, u32 msr)
struct shared_msr_entry *find_msr_entry(struct vcpu_vmx *vmx, u32 msr)
void loaded_vmcs_init(struct loaded_vmcs *loaded_vmcs)
static inline void crash_enable_local_vmclear(int cpu)
static inline void crash_disable_local_vmclear(int cpu)
static inline int crash_local_vmclear_enabled(int cpu)
static void crash_vmclear_local_loaded_vmcss(void)
static void __loaded_vmcs_clear(void *arg)
void loaded_vmcs_clear(struct loaded_vmcs *loaded_vmcs)
static bool vmx_segment_cache_test_set(struct vcpu_vmx *vmx, unsigned seg, unsigned field)
static u16 vmx_read_guest_seg_selector(struct vcpu_vmx *vmx, unsigned seg)
static ulong vmx_read_guest_seg_base(struct vcpu_vmx *vmx, unsigned seg)
static u32 vmx_read_guest_seg_limit(struct vcpu_vmx *vmx, unsigned seg)
static u32 vmx_read_guest_seg_ar(struct vcpu_vmx *vmx, unsigned seg)
void update_exception_bitmap(struct kvm_vcpu *vcpu)
static bool msr_write_intercepted(struct kvm_vcpu *vcpu, u32 msr)
static void clear_atomic_switch_msr_special(struct vcpu_vmx *vmx, unsigned long entry, unsigned long exit)
static int find_msr(struct vmx_msrs *m, unsigned int msr)
static void clear_atomic_switch_msr(struct vcpu_vmx *vmx, unsigned msr)
static void add_atomic_switch_msr_special(struct vcpu_vmx *vmx, unsigned long entry, unsigned long exit, unsigned long guest_val_vmcs, unsigned long host_val_vmcs, u64 guest_val, u64 host_val)
static void add_atomic_switch_msr(struct vcpu_vmx *vmx, unsigned msr, u64 guest_val, u64 host_val, bool entry_only)
static bool update_transition_efer(struct vcpu_vmx *vmx, int efer_offset)
static unsigned long segment_base(u16 selector)
static inline void pt_load_msr(struct pt_ctx *ctx, u32 addr_range)
static inline void pt_save_msr(struct pt_ctx *ctx, u32 addr_range)
static void pt_guest_enter(struct vcpu_vmx *vmx)
static void pt_guest_exit(struct vcpu_vmx *vmx)
void vmx_prepare_switch_to_guest(struct kvm_vcpu *vcpu)
static void vmx_prepare_switch_to_host(struct vcpu_vmx *vmx)
static u64 vmx_read_guest_kernel_gs_base(struct vcpu_vmx *vmx)
static void vmx_write_guest_kernel_gs_base(struct vcpu_vmx *vmx, u64 data)
static void vmx_vcpu_pi_load(struct kvm_vcpu *vcpu, int cpu)
void vmx_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
static void vmx_vcpu_pi_put(struct kvm_vcpu *vcpu)
void vmx_vcpu_put(struct kvm_vcpu *vcpu)
static bool emulation_required(struct kvm_vcpu *vcpu)
unsigned long vmx_get_rflags(struct kvm_vcpu *vcpu)
void vmx_set_rflags(struct kvm_vcpu *vcpu, unsigned long rflags)
u32 vmx_get_interrupt_shadow(struct kvm_vcpu *vcpu)
void vmx_set_interrupt_shadow(struct kvm_vcpu *vcpu, int mask)
static int vmx_rtit_ctl_check(struct kvm_vcpu *vcpu, u64 data)
static void skip_emulated_instruction(struct kvm_vcpu *vcpu)
static void vmx_clear_hlt(struct kvm_vcpu *vcpu)
static void vmx_queue_exception(struct kvm_vcpu *vcpu)
static bool vmx_rdtscp_supported(void)
static bool vmx_invpcid_supported(void)
static void move_msr_up(struct vcpu_vmx *vmx, int from, int to)
static void setup_msrs(struct vcpu_vmx *vmx)
static u64 vmx_read_l1_tsc_offset(struct kvm_vcpu *vcpu)
static u64 vmx_write_l1_tsc_offset(struct kvm_vcpu *vcpu, u64 offset)
bool nested_vmx_allowed(struct kvm_vcpu *vcpu)
static inline bool vmx_feature_control_msr_valid(struct kvm_vcpu *vcpu, uint64_t val)
static int vmx_get_msr_feature(struct kvm_msr_entry *msr)
static int vmx_get_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
static int vmx_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
static void vmx_cache_reg(struct kvm_vcpu *vcpu, enum kvm_reg reg)
static __init int cpu_has_kvm_support(void)
static __init int vmx_disabled_by_bios(void)
static void kvm_cpu_vmxon(u64 addr)
static int hardware_enable(void)
static void vmclear_local_loaded_vmcss(void)
static void kvm_cpu_vmxoff(void)
static void hardware_disable(void)
static __init int adjust_vmx_controls(u32 ctl_min, u32 ctl_opt, u32 msr, u32 *result)
static __init int setup_vmcs_config(struct vmcs_config *vmcs_conf, struct vmx_capability *vmx_cap)
struct vmcs *alloc_vmcs_cpu(bool shadow, int cpu)
void free_vmcs(struct vmcs *vmcs)
void free_loaded_vmcs(struct loaded_vmcs *loaded_vmcs)
int alloc_loaded_vmcs(struct loaded_vmcs *loaded_vmcs)
static void free_kvm_area(void)
static __init int alloc_kvm_area(void)
static void fix_pmode_seg(struct kvm_vcpu *vcpu, int seg, struct kvm_segment *save)
static void enter_pmode(struct kvm_vcpu *vcpu)
static void fix_rmode_seg(int seg, struct kvm_segment *save)
static void enter_rmode(struct kvm_vcpu *vcpu)
void vmx_set_efer(struct kvm_vcpu *vcpu, u64 efer)
static void enter_lmode(struct kvm_vcpu *vcpu)
static void exit_lmode(struct kvm_vcpu *vcpu)
static void vmx_flush_tlb_gva(struct kvm_vcpu *vcpu, gva_t addr)
static void vmx_decache_cr0_guest_bits(struct kvm_vcpu *vcpu)
static void vmx_decache_cr3(struct kvm_vcpu *vcpu)
static void vmx_decache_cr4_guest_bits(struct kvm_vcpu *vcpu)
static void ept_load_pdptrs(struct kvm_vcpu *vcpu)
void ept_save_pdptrs(struct kvm_vcpu *vcpu)
static void ept_update_paging_mode_cr0(unsigned long *hw_cr0, unsigned long cr0, struct kvm_vcpu *vcpu)
void vmx_set_cr0(struct kvm_vcpu *vcpu, unsigned long cr0)
static int get_ept_level(struct kvm_vcpu *vcpu)
u64 construct_eptp(struct kvm_vcpu *vcpu, unsigned long root_hpa)
void vmx_set_cr3(struct kvm_vcpu *vcpu, unsigned long cr3)
int vmx_set_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
void vmx_get_segment(struct kvm_vcpu *vcpu, struct kvm_segment *var, int seg)
static u64 vmx_get_segment_base(struct kvm_vcpu *vcpu, int seg)
int vmx_get_cpl(struct kvm_vcpu *vcpu)
static u32 vmx_segment_access_rights(struct kvm_segment *var)
void vmx_set_segment(struct kvm_vcpu *vcpu, struct kvm_segment *var, int seg)
static void vmx_get_cs_db_l_bits(struct kvm_vcpu *vcpu, int *db, int *l)
static void vmx_get_idt(struct kvm_vcpu *vcpu, struct desc_ptr *dt)
static void vmx_set_idt(struct kvm_vcpu *vcpu, struct desc_ptr *dt)
static void vmx_get_gdt(struct kvm_vcpu *vcpu, struct desc_ptr *dt)
static void vmx_set_gdt(struct kvm_vcpu *vcpu, struct desc_ptr *dt)
static bool rmode_segment_valid(struct kvm_vcpu *vcpu, int seg)
static bool code_segment_valid(struct kvm_vcpu *vcpu)
static bool stack_segment_valid(struct kvm_vcpu *vcpu)
static bool data_segment_valid(struct kvm_vcpu *vcpu, int seg)
static bool tr_valid(struct kvm_vcpu *vcpu)
static bool ldtr_valid(struct kvm_vcpu *vcpu)
static bool cs_ss_rpl_check(struct kvm_vcpu *vcpu)
static bool guest_state_valid(struct kvm_vcpu *vcpu)
static int init_rmode_tss(struct kvm *kvm)
static int init_rmode_identity_map(struct kvm *kvm)
static void seg_setup(int seg)
static int alloc_apic_access_page(struct kvm *kvm)
int allocate_vpid(void)
void free_vpid(int vpid)
static __always_inline void vmx_disable_intercept_for_msr(unsigned long *msr_bitmap, u32 msr, int type)
static __always_inline void vmx_enable_intercept_for_msr(unsigned long *msr_bitmap, u32 msr, int type)
static __always_inline void vmx_set_intercept_for_msr(unsigned long *msr_bitmap, u32 msr, int type, bool value)
static u8 vmx_msr_bitmap_mode(struct kvm_vcpu *vcpu)
static void vmx_update_msr_bitmap_x2apic(unsigned long *msr_bitmap, u8 mode)
void vmx_update_msr_bitmap(struct kvm_vcpu *vcpu)
void pt_update_intercept_for_msr(struct vcpu_vmx *vmx)
static bool vmx_get_enable_apicv(struct kvm_vcpu *vcpu)
static bool vmx_guest_apic_has_interrupt(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_trigger_posted_interrupt(struct kvm_vcpu *vcpu, bool nested)
static int vmx_deliver_nested_posted_interrupt(struct kvm_vcpu *vcpu, int vector)
if (is_guest_mode(vcpu)
&&vmx->nested.pi_pending = true; kvm_make_request(KVM_REQ_EVENT, vcpu)
;if (!kvm_vcpu_trigger_posted_interrupt(vcpu, true)
)
kvm_vcpu_kick(vcpu)
; return 0;}return -1; }static void vmx_deliver_posted_interrupt(struct kvm_vcpu *vcpu, int vector)
void vmx_set_constant_host_state(struct vcpu_vmx *vmx)
void set_cr4_guest_host_mask(struct vcpu_vmx *vmx)
static u32 vmx_pin_based_exec_ctrl(struct vcpu_vmx *vmx)
static void vmx_refresh_apicv_exec_ctrl(struct kvm_vcpu *vcpu)
u32 vmx_exec_control(struct vcpu_vmx *vmx)
static void vmx_compute_secondary_exec_control(struct vcpu_vmx *vmx)
static void ept_set_mmio_spte_mask(void)
static void vmx_vcpu_setup(struct vcpu_vmx *vmx)
static void vmx_vcpu_reset(struct kvm_vcpu *vcpu, bool init_event)
static void enable_irq_window(struct kvm_vcpu *vcpu)
static void enable_nmi_window(struct kvm_vcpu *vcpu)
static void vmx_inject_irq(struct kvm_vcpu *vcpu)
static void vmx_inject_nmi(struct kvm_vcpu *vcpu)
bool vmx_get_nmi_mask(struct kvm_vcpu *vcpu)
void vmx_set_nmi_mask(struct kvm_vcpu *vcpu, bool masked)
static int vmx_nmi_allowed(struct kvm_vcpu *vcpu)
static int vmx_interrupt_allowed(struct kvm_vcpu *vcpu)
static int vmx_set_tss_addr(struct kvm *kvm, unsigned int addr)
static int vmx_set_identity_map_addr(struct kvm *kvm, u64 ident_addr)
static bool rmode_exception(struct kvm_vcpu *vcpu, int vec)
static int handle_rmode_exception(struct kvm_vcpu *vcpu, int vec, u32 err_code)
static void kvm_machine_check(void)
static int handle_machine_check(struct kvm_vcpu *vcpu)
static int handle_exception(struct kvm_vcpu *vcpu)
static int handle_external_interrupt(struct kvm_vcpu *vcpu)
static int handle_triple_fault(struct kvm_vcpu *vcpu)
static int handle_io(struct kvm_vcpu *vcpu)
static void vmx_patch_hypercall(struct kvm_vcpu *vcpu, unsigned char *hypercall)
static int handle_set_cr0(struct kvm_vcpu *vcpu, unsigned long val)
static int handle_set_cr4(struct kvm_vcpu *vcpu, unsigned long val)
static int handle_desc(struct kvm_vcpu *vcpu)
static int handle_cr(struct kvm_vcpu *vcpu)
static int handle_dr(struct kvm_vcpu *vcpu)
static u64 vmx_get_dr6(struct kvm_vcpu *vcpu)
static void vmx_set_dr6(struct kvm_vcpu *vcpu, unsigned long val)
static void vmx_sync_dirty_debug_regs(struct kvm_vcpu *vcpu)
static void vmx_set_dr7(struct kvm_vcpu *vcpu, unsigned long val)
static int handle_cpuid(struct kvm_vcpu *vcpu)
static int handle_rdmsr(struct kvm_vcpu *vcpu)
static int handle_wrmsr(struct kvm_vcpu *vcpu)
static int handle_tpr_below_threshold(struct kvm_vcpu *vcpu)
static int handle_interrupt_window(struct kvm_vcpu *vcpu)
static int handle_halt(struct kvm_vcpu *vcpu)
static int handle_vmcall(struct kvm_vcpu *vcpu)
static int handle_invd(struct kvm_vcpu *vcpu)
static int handle_invlpg(struct kvm_vcpu *vcpu)
static int handle_rdpmc(struct kvm_vcpu *vcpu)
static int handle_wbinvd(struct kvm_vcpu *vcpu)
static int handle_xsetbv(struct kvm_vcpu *vcpu)
static int handle_xsaves(struct kvm_vcpu *vcpu)
static int handle_xrstors(struct kvm_vcpu *vcpu)
static int handle_apic_access(struct kvm_vcpu *vcpu)
static int handle_apic_eoi_induced(struct kvm_vcpu *vcpu)
static int handle_apic_write(struct kvm_vcpu *vcpu)
static int handle_task_switch(struct kvm_vcpu *vcpu)
static int handle_ept_violation(struct kvm_vcpu *vcpu)
static int handle_ept_misconfig(struct kvm_vcpu *vcpu)
static int handle_nmi_window(struct kvm_vcpu *vcpu)
static int handle_invalid_guest_state(struct kvm_vcpu *vcpu)
static void grow_ple_window(struct kvm_vcpu *vcpu)
static void shrink_ple_window(struct kvm_vcpu *vcpu)
static void wakeup_handler(void)
static void vmx_enable_tdp(void)
static int handle_pause(struct kvm_vcpu *vcpu)
static int handle_nop(struct kvm_vcpu *vcpu)
static int handle_mwait(struct kvm_vcpu *vcpu)
static int handle_invalid_op(struct kvm_vcpu *vcpu)
static int handle_monitor_trap(struct kvm_vcpu *vcpu)
static int handle_monitor(struct kvm_vcpu *vcpu)
static int handle_invpcid(struct kvm_vcpu *vcpu)
static int handle_pml_full(struct kvm_vcpu *vcpu)
static int handle_preemption_timer(struct kvm_vcpu *vcpu)
static int handle_vmx_instruction(struct kvm_vcpu *vcpu)
static int handle_encls(struct kvm_vcpu *vcpu)
static void vmx_get_exit_info(struct kvm_vcpu *vcpu, u64 *info1, u64 *info2)
static void vmx_destroy_pml_buffer(struct vcpu_vmx *vmx)
static void vmx_flush_pml_buffer(struct kvm_vcpu *vcpu)
static void kvm_flush_pml_buffers(struct kvm *kvm)
static void vmx_dump_sel(char *name, uint32_t sel)
static void vmx_dump_dtsel(char *name, uint32_t limit)
static void dump_vmcs(void)
static int vmx_handle_exit(struct kvm_vcpu *vcpu)
static void vmx_l1d_flush(struct kvm_vcpu *vcpu)
static void update_cr8_intercept(struct kvm_vcpu *vcpu, int tpr, int irr)
void vmx_set_virtual_apic_mode(struct kvm_vcpu *vcpu)
static void vmx_set_apic_access_page_addr(struct kvm_vcpu *vcpu, hpa_t hpa)
static void vmx_hwapic_isr_update(struct kvm_vcpu *vcpu, int max_isr)
static void vmx_set_rvi(int vector)
static void vmx_hwapic_irr_update(struct kvm_vcpu *vcpu, int max_irr)
static int vmx_sync_pir_to_irr(struct kvm_vcpu *vcpu)
static void vmx_load_eoi_exitmap(struct kvm_vcpu *vcpu, u64 *eoi_exit_bitmap)
static void vmx_apicv_post_state_restore(struct kvm_vcpu *vcpu)
static void vmx_complete_atomic_exit(struct vcpu_vmx *vmx)
static void vmx_handle_external_intr(struct kvm_vcpu *vcpu)
static bool vmx_has_emulated_msr(int index)
static bool vmx_pt_supported(void)
static void vmx_recover_nmi_blocking(struct vcpu_vmx *vmx)
static void __vmx_complete_interrupts(struct kvm_vcpu *vcpu, u32 idt_vectoring_info, int instr_len_field, int error_code_field)
static void vmx_complete_interrupts(struct vcpu_vmx *vmx)
static void vmx_cancel_injection(struct kvm_vcpu *vcpu)
static void atomic_switch_perf_msrs(struct vcpu_vmx *vmx)
static void vmx_arm_hv_timer(struct vcpu_vmx *vmx, u32 val)
static void vmx_update_hv_timer(struct kvm_vcpu *vcpu)
static void __vmx_vcpu_run(struct kvm_vcpu *vcpu, struct vcpu_vmx *vmx)
static void vmx_vcpu_run(struct kvm_vcpu *vcpu)
static struct kvm *vmx_vm_alloc(void)
static void vmx_vm_free(struct kvm *kvm)
static void vmx_free_vcpu(struct kvm_vcpu *vcpu)
static struct kvm_vcpu *vmx_create_vcpu(struct kvm *kvm, unsigned int id)
static int vmx_vm_init(struct kvm *kvm)
static void __init vmx_check_processor_compat(void *rtn)
static u64 vmx_get_mt_mask(struct kvm_vcpu *vcpu, gfn_t gfn, bool is_mmio)
static int vmx_get_lpage_level(void)
static void vmcs_set_secondary_exec_control(u32 new_ctl)
static void nested_vmx_cr_fixed1_bits_update(struct kvm_vcpu *vcpu)
static void nested_vmx_entry_exit_ctls_update(struct kvm_vcpu *vcpu)
static void update_intel_pt_cfg(struct kvm_vcpu *vcpu)
static void vmx_cpuid_update(struct kvm_vcpu *vcpu)
static void vmx_set_supported_cpuid(u32 func, struct kvm_cpuid_entry2 *entry)
static void vmx_request_immediate_exit(struct kvm_vcpu *vcpu)
static int vmx_check_intercept(struct kvm_vcpu *vcpu, struct x86_instruction_info *info, enum x86_intercept_stage stage)
static inline int u64_shl_div_u64(u64 a, unsigned int shift, u64 divisor, u64 *result)
static int vmx_set_hv_timer(struct kvm_vcpu *vcpu, u64 guest_deadline_tsc)
static void vmx_cancel_hv_timer(struct kvm_vcpu *vcpu)
static void vmx_sched_in(struct kvm_vcpu *vcpu, int cpu)
static void vmx_slot_enable_log_dirty(struct kvm *kvm, struct kvm_memory_slot *slot)
static void vmx_slot_disable_log_dirty(struct kvm *kvm, struct kvm_memory_slot *slot)
static void vmx_flush_log_dirty(struct kvm *kvm)
static int vmx_write_pml_buffer(struct kvm_vcpu *vcpu)
static void vmx_enable_log_dirty_pt_masked(struct kvm *kvm, struct kvm_memory_slot *memslot, gfn_t offset, unsigned long mask)
static void __pi_post_block(struct kvm_vcpu *vcpu)
static int pi_pre_block(struct kvm_vcpu *vcpu)
static int vmx_pre_block(struct kvm_vcpu *vcpu)
static void pi_post_block(struct kvm_vcpu *vcpu)
static void vmx_post_block(struct kvm_vcpu *vcpu)
static int vmx_update_pi_irte(struct kvm *kvm, unsigned int host_irq, uint32_t guest_irq, bool set)
static void vmx_setup_mce(struct kvm_vcpu *vcpu)
static int vmx_smi_allowed(struct kvm_vcpu *vcpu)
static int vmx_pre_enter_smm(struct kvm_vcpu *vcpu, char *smstate)
static int vmx_pre_leave_smm(struct kvm_vcpu *vcpu, u64 smbase)
static int enable_smi_window(struct kvm_vcpu *vcpu)
static __init int hardware_setup(void)
static __exit void hardware_unsetup(void)
static void vmx_cleanup_l1d_flush(void)
static void vmx_exit(void)
static int __init vmx_init(void)
\n
    169 struct kvm_vcpu *vcpu
     33 struct vcpu_vmx *vmx
     27 void
     18 struct kvm *kvm
      8 int seg
      7 u32 msr
      7 int cpu
      5 unsigned seg
      4 unsigned long val
      4 unsigned long *msr_bitmap
      4 struct loaded_vmcs *loaded_vmcs
      4 struct desc_ptr *dt
      3 struct kvm_segment *var
      3 int vector
      3 int type
      2 vcpu
      2 unsigned msr
      2 unsigned long exit
      2 unsigned long entry
      2 unsigned long cr0
      2 u64 host_val
      2 u64 guest_val
      2 u64 data
      2 u32 addr_range
      2 struct pt_ctx *ctx
      2 struct msr_data *msr_info
      2 struct kvm_tlb_range *range
      2 struct kvm_segment *save
      2 struct kvm_memory_slot *slot
      2 int vec
      2 const struct kernel_param *kp
      2 const char *s
      2 char *name
      1 void *rtn
      1 void *data
      1 void *arg
      1 unsigned long root_hpa
      1 unsigned long rflags
      1 unsigned long mask
      1 unsigned long *hw_cr0
      1 unsigned long host_val_vmcs
      1 unsigned long guest_val_vmcs
      1 unsigned long cr4
      1 unsigned long cr3
      1 unsigned int shift
      1 unsigned int msr
      1 unsigned int id
      1 unsigned int host_irq
      1 unsigned int addr
      1 unsigned field
      1 unsigned char *hypercall
      1 uint64_t val
      1 uint32_t sel
      1 uint32_t limit
      1 uint32_t guest_irq
      1 u8 mode
      1 u64 smbase
      1 u64 *result
      1 u64 offset
      1 u64 *info2
      1 u64 *info1
      1 u64 ident_addr
      1 u64 guest_deadline_tsc
      1 u64 *eoi_exit_bitmap
      1 u64 efer
      1 u64 divisor
      1 u64 addr
      1 u64 a
      1 u32 val
      1 u32 *result
      1 u32 new_ctl
      1 u32 idt_vectoring_info
      1 u32 func
      1 u32 err_code
      1 u32 ctl_opt
      1 u32 ctl_min
      1 u16 selector
      1 true
      1 &to_kvm_vmxkvm
      1 struct x86_instruction_info *info
      1 struct vmx_msrs *m
      1 struct vmx_capability *vmx_cap
      1 struct vmcs *vmcs
      1 struct vmcs_config *vmcs_conf
      1 struct kvm_msr_entry *msr
      1 struct kvm_memory_slot *memslot
      1 struct kvm_cpuid_entry2 *entry
      1 struct hv_guest_mapping_flush_list *flush
      1 !kvm_vcpu_trigger_posted_interruptvcpu
      1 KVM_REQ_EVENT
      1 is_guest_modevcpu
      1 int vpid
      1 int tpr
      1 int to
      1 int max_isr
      1 int max_irr
      1 int mask
      1 int *l
      1 int irr
      1 int instr_len_field
      1 int index
      1 int from
      1 int error_code_field
      1 int efer_offset
      1 int *db
      1 hpa_t hpa
      1 gva_t addr
      1 gfn_t offset
      1 gfn_t gfn
      1 enum x86_intercept_stage stage
      1 enum vmx_l1d_flush_state l1tf
      1 enum kvm_reg reg
      1 char *smstate
      1 char *s
      1 bool value
      1 bool shadow
      1 bool set
      1 bool nested
      1 bool masked
      1 bool is_mmio
      1 bool init_event
      1 bool entry_only
