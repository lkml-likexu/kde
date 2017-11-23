
static int vmx_setup_l1d_flush(enum vmx_l1d_flush_state l1tf)
static int vmentry_l1d_flush_parse(const char *s)
static int vmentry_l1d_flush_set(const char *s, const struct kernel_param *kp)
static int vmentry_l1d_flush_get(char *s, const struct kernel_param *kp)
static bool pi_test_and_set_on(struct pi_desc *pi_desc)
static bool pi_test_and_clear_on(struct pi_desc *pi_desc)
static int pi_test_and_set_pir(int vector, struct pi_desc *pi_desc)
static inline void pi_clear_sn(struct pi_desc *pi_desc)
static inline void pi_set_sn(struct pi_desc *pi_desc)
static inline void pi_clear_on(struct pi_desc *pi_desc)
static inline int pi_test_on(struct pi_desc *pi_desc)
static inline int pi_test_sn(struct pi_desc *pi_desc)
static inline struct kvm_vmx *to_kvm_vmx(struct kvm *kvm)
static inline struct vcpu_vmx *to_vmx(struct kvm_vcpu *vcpu)
static struct pi_desc *vcpu_to_pi_desc(struct kvm_vcpu *vcpu)
static inline short vmcs_field_to_offset(unsigned long field)
static inline struct vmcs12 *get_vmcs12(struct kvm_vcpu *vcpu)
static inline struct vmcs12 *get_shadow_vmcs12(struct kvm_vcpu *vcpu)
static inline void evmcs_write64(unsigned long field, u64 value)
static inline void evmcs_write32(unsigned long field, u32 value)
static inline void evmcs_write16(unsigned long field, u16 value)
static inline u64 evmcs_read64(unsigned long field)
static inline u32 evmcs_read32(unsigned long field)
static inline u16 evmcs_read16(unsigned long field)
static inline void evmcs_touch_msr_bitmap(void)
static void evmcs_load(u64 phys_addr)
static void evmcs_sanitize_exec_ctrls(struct vmcs_config *vmcs_conf)
static void check_ept_pointer_match(struct kvm *kvm)
static int vmx_hv_remote_flush_tlb(struct kvm *kvm)
static int nested_enable_evmcs(struct kvm_vcpu *vcpu, uint16_t *vmcs_version)
static inline bool is_exception_n(u32 intr_info, u8 vector)
static inline bool is_debug(u32 intr_info)
static inline bool is_breakpoint(u32 intr_info)
static inline bool is_page_fault(u32 intr_info)
static inline bool is_invalid_opcode(u32 intr_info)
static inline bool is_gp_fault(u32 intr_info)
static inline bool is_machine_check(u32 intr_info)
static inline bool is_icebp(u32 intr_info)
static inline bool cpu_has_vmx_msr_bitmap(void)
static inline bool cpu_has_vmx_tpr_shadow(void)
static inline bool cpu_need_tpr_shadow(struct kvm_vcpu *vcpu)
static inline bool cpu_has_secondary_exec_ctrls(void)
static inline bool cpu_has_vmx_virtualize_apic_accesses(void)
static inline bool cpu_has_vmx_virtualize_x2apic_mode(void)
static inline bool cpu_has_vmx_apic_register_virt(void)
static inline bool cpu_has_vmx_virtual_intr_delivery(void)
static inline bool cpu_has_vmx_encls_vmexit(void)
static inline bool cpu_has_broken_vmx_preemption_timer(void)
static inline bool cpu_has_vmx_preemption_timer(void)
static inline bool cpu_has_vmx_posted_intr(void)
static inline bool cpu_has_vmx_apicv(void)
static inline bool cpu_has_vmx_flexpriority(void)
static inline bool cpu_has_vmx_ept_execute_only(void)
static inline bool cpu_has_vmx_ept_2m_page(void)
static inline bool cpu_has_vmx_ept_1g_page(void)
static inline bool cpu_has_vmx_ept_4levels(void)
static inline bool cpu_has_vmx_ept_mt_wb(void)
static inline bool cpu_has_vmx_ept_5levels(void)
static inline bool cpu_has_vmx_ept_ad_bits(void)
static inline bool cpu_has_vmx_invept_context(void)
static inline bool cpu_has_vmx_invept_global(void)
static inline bool cpu_has_vmx_invvpid_individual_addr(void)
static inline bool cpu_has_vmx_invvpid_single(void)
static inline bool cpu_has_vmx_invvpid_global(void)
static inline bool cpu_has_vmx_invvpid(void)
static inline bool cpu_has_vmx_ept(void)
static inline bool cpu_has_vmx_unrestricted_guest(void)
static inline bool cpu_has_vmx_ple(void)
static inline bool cpu_has_vmx_basic_inout(void)
static inline bool cpu_need_virtualize_apic_accesses(struct kvm_vcpu *vcpu)
static inline bool cpu_has_vmx_vpid(void)
static inline bool cpu_has_vmx_rdtscp(void)
static inline bool cpu_has_vmx_invpcid(void)
static inline bool cpu_has_virtual_nmis(void)
static inline bool cpu_has_vmx_wbinvd_exit(void)
static inline bool cpu_has_vmx_shadow_vmcs(void)
static inline bool cpu_has_vmx_pml(void)
static inline bool cpu_has_vmx_tsc_scaling(void)
static inline bool cpu_has_vmx_vmfunc(void)
static bool vmx_umip_emulated(void)
static inline bool report_flexpriority(void)
static inline unsigned nested_cpu_vmx_misc_cr3_count(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_has_vmwrite_any_field(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_has_zero_length_injection(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_supports_monitor_trap_flag(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_has_vmx_shadow_vmcs(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_has(struct vmcs12 *vmcs12, u32 bit)
static inline bool nested_cpu_has2(struct vmcs12 *vmcs12, u32 bit)
static inline bool nested_cpu_has_preemption_timer(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_nmi_exiting(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_virtual_nmis(struct vmcs12 *vmcs12)
static inline int nested_cpu_has_ept(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_xsaves(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_pml(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_virt_x2apic_mode(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_vpid(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_apic_reg_virt(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_vid(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_posted_intr(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_vmfunc(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_eptp_switching(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_shadow_vmcs(struct vmcs12 *vmcs12)
static inline bool is_nmi(u32 intr_info)
static int __find_msr_index(struct vcpu_vmx *vmx, u32 msr)
static inline void __invvpid(unsigned long ext, u16 vpid, gva_t gva)
static inline void __invept(unsigned long ext, u64 eptp, gpa_t gpa)
static struct shared_msr_entry *find_msr_entry(struct vcpu_vmx *vmx, u32 msr)
static void vmcs_clear(struct vmcs *vmcs)
static inline void loaded_vmcs_init(struct loaded_vmcs *loaded_vmcs)
static void vmcs_load(struct vmcs *vmcs)
static inline void crash_enable_local_vmclear(int cpu)
static inline void crash_disable_local_vmclear(int cpu)
static inline int crash_local_vmclear_enabled(int cpu)
static void crash_vmclear_local_loaded_vmcss(void)
static void __loaded_vmcs_clear(void *arg)
static void loaded_vmcs_clear(struct loaded_vmcs *loaded_vmcs)
static inline bool vpid_sync_vcpu_addr(int vpid, gva_t addr)
static inline void vpid_sync_vcpu_single(int vpid)
static inline void vpid_sync_vcpu_global(void)
static inline void vpid_sync_context(int vpid)
static inline void ept_sync_global(void)
static inline void ept_sync_context(u64 eptp)
static __always_inline void vmcs_check16(unsigned long field)
static __always_inline void vmcs_check32(unsigned long field)
static __always_inline void vmcs_check64(unsigned long field)
static __always_inline void vmcs_checkl(unsigned long field)
static __always_inline unsigned long __vmcs_readl(unsigned long field)
static __always_inline u16 vmcs_read16(unsigned long field)
static __always_inline u32 vmcs_read32(unsigned long field)
static __always_inline u64 vmcs_read64(unsigned long field)
static __always_inline unsigned long vmcs_readl(unsigned long field)
static noinline void vmwrite_error(unsigned long field, unsigned long value)
static __always_inline void __vmcs_writel(unsigned long field, unsigned long value)
static __always_inline void vmcs_write16(unsigned long field, u16 value)
static __always_inline void vmcs_write32(unsigned long field, u32 value)
static __always_inline void vmcs_write64(unsigned long field, u64 value)
static __always_inline void vmcs_writel(unsigned long field, unsigned long value)
static __always_inline void vmcs_clear_bits(unsigned long field, u32 mask)
static __always_inline void vmcs_set_bits(unsigned long field, u32 mask)
static inline void vm_entry_controls_reset_shadow(struct vcpu_vmx *vmx)
static inline void vm_entry_controls_init(struct vcpu_vmx *vmx, u32 val)
static inline void vm_entry_controls_set(struct vcpu_vmx *vmx, u32 val)
static inline u32 vm_entry_controls_get(struct vcpu_vmx *vmx)
static inline void vm_entry_controls_setbit(struct vcpu_vmx *vmx, u32 val)
static inline void vm_entry_controls_clearbit(struct vcpu_vmx *vmx, u32 val)
static inline void vm_exit_controls_reset_shadow(struct vcpu_vmx *vmx)
static inline void vm_exit_controls_init(struct vcpu_vmx *vmx, u32 val)
static inline void vm_exit_controls_set(struct vcpu_vmx *vmx, u32 val)
static inline u32 vm_exit_controls_get(struct vcpu_vmx *vmx)
static inline void vm_exit_controls_setbit(struct vcpu_vmx *vmx, u32 val)
static inline void vm_exit_controls_clearbit(struct vcpu_vmx *vmx, u32 val)
static void vmx_segment_cache_clear(struct vcpu_vmx *vmx)
static bool vmx_segment_cache_test_set(struct vcpu_vmx *vmx, unsigned seg, unsigned field)
static u16 vmx_read_guest_seg_selector(struct vcpu_vmx *vmx, unsigned seg)
static ulong vmx_read_guest_seg_base(struct vcpu_vmx *vmx, unsigned seg)
static u32 vmx_read_guest_seg_limit(struct vcpu_vmx *vmx, unsigned seg)
static u32 vmx_read_guest_seg_ar(struct vcpu_vmx *vmx, unsigned seg)
static void update_exception_bitmap(struct kvm_vcpu *vcpu)
static bool msr_write_intercepted(struct kvm_vcpu *vcpu, u32 msr)
static bool msr_write_intercepted_l01(struct kvm_vcpu *vcpu, u32 msr)
static void clear_atomic_switch_msr_special(struct vcpu_vmx *vmx, unsigned long entry, unsigned long exit)
static int find_msr(struct vmx_msrs *m, unsigned int msr)
static void clear_atomic_switch_msr(struct vcpu_vmx *vmx, unsigned msr)
static void add_atomic_switch_msr_special(struct vcpu_vmx *vmx, unsigned long entry, unsigned long exit, unsigned long guest_val_vmcs, unsigned long host_val_vmcs, u64 guest_val, u64 host_val)
static void add_atomic_switch_msr(struct vcpu_vmx *vmx, unsigned msr, u64 guest_val, u64 host_val, bool entry_only)
static bool update_transition_efer(struct vcpu_vmx *vmx, int efer_offset)
static unsigned long segment_base(u16 selector)
static void vmx_prepare_switch_to_guest(struct kvm_vcpu *vcpu)
static void vmx_prepare_switch_to_host(struct vcpu_vmx *vmx)
static u64 vmx_read_guest_kernel_gs_base(struct vcpu_vmx *vmx)
static void vmx_write_guest_kernel_gs_base(struct vcpu_vmx *vmx, u64 data)
static void vmx_vcpu_pi_load(struct kvm_vcpu *vcpu, int cpu)
static void decache_tsc_multiplier(struct vcpu_vmx *vmx)
static void vmx_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
static void vmx_vcpu_pi_put(struct kvm_vcpu *vcpu)
static void vmx_vcpu_put(struct kvm_vcpu *vcpu)
static bool emulation_required(struct kvm_vcpu *vcpu)
static inline unsigned long nested_read_cr0(struct vmcs12 *fields)
static inline unsigned long nested_read_cr0(struct vmcs12 *fields)
return (fields->guest_cr0 & ~fields->cr0_guest_host_mask)
| (fields->cr0_read_shadow & fields->cr0_guest_host_mask)
; } static inline unsigned long nested_read_cr4(struct vmcs12 *fields)
static unsigned long vmx_get_rflags(struct kvm_vcpu *vcpu)
static void vmx_set_rflags(struct kvm_vcpu *vcpu, unsigned long rflags)
static u32 vmx_get_interrupt_shadow(struct kvm_vcpu *vcpu)
static void vmx_set_interrupt_shadow(struct kvm_vcpu *vcpu, int mask)
static void skip_emulated_instruction(struct kvm_vcpu *vcpu)
static void nested_vmx_inject_exception_vmexit(struct kvm_vcpu *vcpu, unsigned long exit_qual)
static int nested_vmx_check_exception(struct kvm_vcpu *vcpu, unsigned long *exit_qual)
static void vmx_clear_hlt(struct kvm_vcpu *vcpu)
static void vmx_queue_exception(struct kvm_vcpu *vcpu)
static bool vmx_rdtscp_supported(void)
static bool vmx_invpcid_supported(void)
static void move_msr_up(struct vcpu_vmx *vmx, int from, int to)
static void setup_msrs(struct vcpu_vmx *vmx)
static u64 vmx_read_l1_tsc_offset(struct kvm_vcpu *vcpu)
static void vmx_write_tsc_offset(struct kvm_vcpu *vcpu, u64 offset)
static inline bool nested_vmx_allowed(struct kvm_vcpu *vcpu)
static void nested_vmx_setup_ctls_msrs(struct nested_vmx_msrs *msrs, bool apicv)
static inline bool fixed_bits_valid(u64 val, u64 fixed0, u64 fixed1)
static inline bool vmx_control_verify(u32 control, u32 low, u32 high)
static inline u64 vmx_control_msr(u32 low, u32 high)
static bool is_bitwise_subset(u64 superset, u64 subset, u64 mask)
static int vmx_restore_vmx_basic(struct vcpu_vmx *vmx, u64 data)
static int vmx_restore_control_msr(struct vcpu_vmx *vmx, u32 msr_index, u64 data)
static int vmx_restore_vmx_misc(struct vcpu_vmx *vmx, u64 data)
static int vmx_restore_vmx_ept_vpid_cap(struct vcpu_vmx *vmx, u64 data)
static int vmx_restore_fixed0_msr(struct vcpu_vmx *vmx, u32 msr_index, u64 data)
static int vmx_set_vmx_msr(struct kvm_vcpu *vcpu, u32 msr_index, u64 data)
static int vmx_get_vmx_msr(struct nested_vmx_msrs *msrs, u32 msr_index, u64 *pdata)
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
static __init bool allow_1_setting(u32 msr, u32 ctl)
static __init int setup_vmcs_config(struct vmcs_config *vmcs_conf)
static struct vmcs *alloc_vmcs_cpu(bool shadow, int cpu)
static void free_vmcs(struct vmcs *vmcs)
static void free_loaded_vmcs(struct loaded_vmcs *loaded_vmcs)
static struct vmcs *alloc_vmcs(bool shadow)
static int alloc_loaded_vmcs(struct loaded_vmcs *loaded_vmcs)
static void free_kvm_area(void)
static inline int vmcs_field_width(unsigned long field)
static inline int vmcs_field_readonly(unsigned long field)
static void init_vmcs_shadow_fields(void)
static __init int alloc_kvm_area(void)
static void fix_pmode_seg(struct kvm_vcpu *vcpu, int seg, struct kvm_segment *save)
static void enter_pmode(struct kvm_vcpu *vcpu)
static void fix_rmode_seg(int seg, struct kvm_segment *save)
static void enter_rmode(struct kvm_vcpu *vcpu)
static void vmx_set_efer(struct kvm_vcpu *vcpu, u64 efer)
static void enter_lmode(struct kvm_vcpu *vcpu)
static void exit_lmode(struct kvm_vcpu *vcpu)
static inline void __vmx_flush_tlb(struct kvm_vcpu *vcpu, int vpid, bool invalidate_gpa)
static void vmx_flush_tlb(struct kvm_vcpu *vcpu, bool invalidate_gpa)
static void vmx_flush_tlb_gva(struct kvm_vcpu *vcpu, gva_t addr)
static void vmx_decache_cr0_guest_bits(struct kvm_vcpu *vcpu)
static void vmx_decache_cr3(struct kvm_vcpu *vcpu)
static void vmx_decache_cr4_guest_bits(struct kvm_vcpu *vcpu)
static void ept_load_pdptrs(struct kvm_vcpu *vcpu)
static void ept_save_pdptrs(struct kvm_vcpu *vcpu)
static bool nested_guest_cr0_valid(struct kvm_vcpu *vcpu, unsigned long val)
static bool nested_host_cr0_valid(struct kvm_vcpu *vcpu, unsigned long val)
static bool nested_cr4_valid(struct kvm_vcpu *vcpu, unsigned long val)
static void ept_update_paging_mode_cr0(unsigned long *hw_cr0, unsigned long cr0, struct kvm_vcpu *vcpu)
static void vmx_set_cr0(struct kvm_vcpu *vcpu, unsigned long cr0)
static int get_ept_level(struct kvm_vcpu *vcpu)
static u64 construct_eptp(struct kvm_vcpu *vcpu, unsigned long root_hpa)
static void vmx_set_cr3(struct kvm_vcpu *vcpu, unsigned long cr3)
static int vmx_set_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
static void vmx_get_segment(struct kvm_vcpu *vcpu, struct kvm_segment *var, int seg)
static u64 vmx_get_segment_base(struct kvm_vcpu *vcpu, int seg)
static int vmx_get_cpl(struct kvm_vcpu *vcpu)
static u32 vmx_segment_access_rights(struct kvm_segment *var)
static void vmx_set_segment(struct kvm_vcpu *vcpu, struct kvm_segment *var, int seg)
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
static bool page_address_valid(struct kvm_vcpu *vcpu, gpa_t gpa)
static int init_rmode_tss(struct kvm *kvm)
static int init_rmode_identity_map(struct kvm *kvm)
static void seg_setup(int seg)
static int alloc_apic_access_page(struct kvm *kvm)
static int allocate_vpid(void)
static void free_vpid(int vpid)
static void __always_inline vmx_disable_intercept_for_msr(unsigned long *msr_bitmap, u32 msr, int type)
static void __always_inline vmx_enable_intercept_for_msr(unsigned long *msr_bitmap, u32 msr, int type)
static void __always_inline vmx_set_intercept_for_msr(unsigned long *msr_bitmap, u32 msr, int type, bool value)
static void nested_vmx_disable_intercept_for_msr(unsigned long *msr_bitmap_l1, unsigned long *msr_bitmap_nested, u32 msr, int type)
static u8 vmx_msr_bitmap_mode(struct kvm_vcpu *vcpu)
static void vmx_update_msr_bitmap_x2apic(unsigned long *msr_bitmap, u8 mode)
static void vmx_update_msr_bitmap(struct kvm_vcpu *vcpu)
static bool vmx_get_enable_apicv(struct kvm_vcpu *vcpu)
static void nested_mark_vmcs12_pages_dirty(struct kvm_vcpu *vcpu)
static void vmx_complete_nested_posted_interrupt(struct kvm_vcpu *vcpu)
static u8 vmx_get_rvi(void)
static bool vmx_guest_apic_has_interrupt(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_trigger_posted_interrupt(struct kvm_vcpu *vcpu, bool nested)
static int vmx_deliver_nested_posted_interrupt(struct kvm_vcpu *vcpu, int vector)
if (is_guest_mode(vcpu)
&&vmx->nested.pi_pending = true; kvm_make_request(KVM_REQ_EVENT, vcpu)
;if (!kvm_vcpu_trigger_posted_interrupt(vcpu, true)
)
kvm_vcpu_kick(vcpu)
; return 0;}return -1; }static void vmx_deliver_posted_interrupt(struct kvm_vcpu *vcpu, int vector)
static void vmx_set_constant_host_state(struct vcpu_vmx *vmx)
static void set_cr4_guest_host_mask(struct vcpu_vmx *vmx)
static u32 vmx_pin_based_exec_ctrl(struct vcpu_vmx *vmx)
static void vmx_refresh_apicv_exec_ctrl(struct kvm_vcpu *vcpu)
static u32 vmx_exec_control(struct vcpu_vmx *vmx)
static bool vmx_rdrand_supported(void)
static bool vmx_rdseed_supported(void)
static void vmx_compute_secondary_exec_control(struct vcpu_vmx *vmx)
static void ept_set_mmio_spte_mask(void)
define VMX_XSS_EXIT_BITMAP 0static void vmx_vcpu_setup(struct vcpu_vmx *vmx)
static void vmx_vcpu_reset(struct kvm_vcpu *vcpu, bool init_event)
static bool nested_exit_on_intr(struct kvm_vcpu *vcpu)
static bool nested_exit_intr_ack_set(struct kvm_vcpu *vcpu)
static bool nested_exit_on_nmi(struct kvm_vcpu *vcpu)
static void enable_irq_window(struct kvm_vcpu *vcpu)
static void enable_nmi_window(struct kvm_vcpu *vcpu)
static void vmx_inject_irq(struct kvm_vcpu *vcpu)
static void vmx_inject_nmi(struct kvm_vcpu *vcpu)
static bool vmx_get_nmi_mask(struct kvm_vcpu *vcpu)
static void vmx_set_nmi_mask(struct kvm_vcpu *vcpu, bool masked)
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
static __init int hardware_setup(void)
static __exit void hardware_unsetup(void)
static int handle_pause(struct kvm_vcpu *vcpu)
static int handle_nop(struct kvm_vcpu *vcpu)
static int handle_mwait(struct kvm_vcpu *vcpu)
static int handle_invalid_op(struct kvm_vcpu *vcpu)
static int handle_monitor_trap(struct kvm_vcpu *vcpu)
static int handle_monitor(struct kvm_vcpu *vcpu)
static int nested_vmx_succeed(struct kvm_vcpu *vcpu)
static int nested_vmx_failInvalid(struct kvm_vcpu *vcpu)
static int nested_vmx_failValid(struct kvm_vcpu *vcpu, u32 vm_instruction_error)
static void nested_vmx_abort(struct kvm_vcpu *vcpu, u32 indicator)
static enum hrtimer_restart vmx_preemption_timer_fn(struct hrtimer *timer)
static int get_vmx_mem_address(struct kvm_vcpu *vcpu, unsigned long exit_qualification, u32 vmx_instruction_info, bool wr, gva_t *ret)
static int nested_vmx_get_vmptr(struct kvm_vcpu *vcpu, gpa_t *vmpointer)
static struct vmcs *alloc_shadow_vmcs(struct kvm_vcpu *vcpu)
static int enter_vmx_operation(struct kvm_vcpu *vcpu)
static int handle_vmon(struct kvm_vcpu *vcpu)
static int nested_vmx_check_permission(struct kvm_vcpu *vcpu)
static void vmx_disable_shadow_vmcs(struct vcpu_vmx *vmx)
static inline void nested_release_evmcs(struct kvm_vcpu *vcpu)
static inline void nested_release_vmcs12(struct kvm_vcpu *vcpu)
static void free_nested(struct kvm_vcpu *vcpu)
static int handle_vmoff(struct kvm_vcpu *vcpu)
static int handle_vmclear(struct kvm_vcpu *vcpu)
static int handle_vmlaunch(struct kvm_vcpu *vcpu)
static int handle_vmresume(struct kvm_vcpu *vcpu)
static inline int vmcs12_read_any(struct vmcs12 *vmcs12, unsigned long field, u64 *ret)
static int copy_enlightened_to_vmcs12(struct vcpu_vmx *vmx)
static int copy_vmcs12_to_enlightened(struct vcpu_vmx *vmx)
static void copy_shadow_to_vmcs12(struct vcpu_vmx *vmx)
static void copy_vmcs12_to_shadow(struct vcpu_vmx *vmx)
static int handle_vmread(struct kvm_vcpu *vcpu)
static int handle_vmwrite(struct kvm_vcpu *vcpu)
static void set_current_vmptr(struct vcpu_vmx *vmx, gpa_t vmptr)
static int handle_vmptrld(struct kvm_vcpu *vcpu)
static int nested_vmx_handle_enlightened_vmptrld(struct kvm_vcpu *vcpu, bool from_launch)
static int handle_vmptrst(struct kvm_vcpu *vcpu)
static int handle_invept(struct kvm_vcpu *vcpu)
static u16 nested_get_vpid02(struct kvm_vcpu *vcpu)
static int handle_invvpid(struct kvm_vcpu *vcpu)
static int handle_invpcid(struct kvm_vcpu *vcpu)
static int handle_pml_full(struct kvm_vcpu *vcpu)
static int handle_preemption_timer(struct kvm_vcpu *vcpu)
static bool valid_ept_address(struct kvm_vcpu *vcpu, u64 address)
static int nested_vmx_eptp_switching(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int handle_vmfunc(struct kvm_vcpu *vcpu)
static int handle_encls(struct kvm_vcpu *vcpu)
static bool nested_vmx_exit_handled_io(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static bool nested_vmx_exit_handled_msr(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, u32 exit_reason)
static bool nested_vmx_exit_handled_cr(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static bool nested_vmx_exit_handled_vmcs_access(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, gpa_t bitmap)
static bool nested_vmx_exit_reflected(struct kvm_vcpu *vcpu, u32 exit_reason)
static int nested_vmx_reflect_vmexit(struct kvm_vcpu *vcpu, u32 exit_reason)
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
static void vmx_set_virtual_apic_mode(struct kvm_vcpu *vcpu)
static void vmx_set_apic_access_page_addr(struct kvm_vcpu *vcpu, hpa_t hpa)
static void vmx_hwapic_isr_update(struct kvm_vcpu *vcpu, int max_isr)
static void vmx_set_rvi(int vector)
static void vmx_hwapic_irr_update(struct kvm_vcpu *vcpu, int max_irr)
static int vmx_sync_pir_to_irr(struct kvm_vcpu *vcpu)
static u8 vmx_has_apicv_interrupt(struct kvm_vcpu *vcpu)
static void vmx_load_eoi_exitmap(struct kvm_vcpu *vcpu, u64 *eoi_exit_bitmap)
static void vmx_apicv_post_state_restore(struct kvm_vcpu *vcpu)
static void vmx_complete_atomic_exit(struct vcpu_vmx *vmx)
static void vmx_handle_external_intr(struct kvm_vcpu *vcpu)
static bool vmx_has_emulated_msr(int index)
static bool vmx_mpx_supported(void)
static bool vmx_xsaves_supported(void)
static void vmx_recover_nmi_blocking(struct vcpu_vmx *vmx)
static void __vmx_complete_interrupts(struct kvm_vcpu *vcpu, u32 idt_vectoring_info, int instr_len_field, int error_code_field)
static void vmx_complete_interrupts(struct vcpu_vmx *vmx)
static void vmx_cancel_injection(struct kvm_vcpu *vcpu)
static void atomic_switch_perf_msrs(struct vcpu_vmx *vmx)
static void vmx_arm_hv_timer(struct vcpu_vmx *vmx, u32 val)
static void vmx_update_hv_timer(struct kvm_vcpu *vcpu)
static void __noclone vmx_vcpu_run(struct kvm_vcpu *vcpu)
static struct kvm *vmx_vm_alloc(void)
static void vmx_vm_free(struct kvm *kvm)
static void vmx_switch_vmcs(struct kvm_vcpu *vcpu, struct loaded_vmcs *vmcs)
static void vmx_free_vcpu_nested(struct kvm_vcpu *vcpu)
static void vmx_free_vcpu(struct kvm_vcpu *vcpu)
static struct kvm_vcpu *vmx_create_vcpu(struct kvm *kvm, unsigned int id)
static int vmx_vm_init(struct kvm *kvm)
static void __init vmx_check_processor_compat(void *rtn)
static u64 vmx_get_mt_mask(struct kvm_vcpu *vcpu, gfn_t gfn, bool is_mmio)
static int vmx_get_lpage_level(void)
static void vmcs_set_secondary_exec_control(u32 new_ctl)
static void nested_vmx_cr_fixed1_bits_update(struct kvm_vcpu *vcpu)
static void nested_vmx_entry_exit_ctls_update(struct kvm_vcpu *vcpu)
static void vmx_cpuid_update(struct kvm_vcpu *vcpu)
static void vmx_set_supported_cpuid(u32 func, struct kvm_cpuid_entry2 *entry)
static void nested_ept_inject_page_fault(struct kvm_vcpu *vcpu, struct x86_exception *fault)
static bool nested_ept_ad_enabled(struct kvm_vcpu *vcpu)
static unsigned long nested_ept_get_cr3(struct kvm_vcpu *vcpu)
static void nested_ept_init_mmu_context(struct kvm_vcpu *vcpu)
static void nested_ept_uninit_mmu_context(struct kvm_vcpu *vcpu)
static bool nested_vmx_is_page_fault_vmexit(struct vmcs12 *vmcs12, u16 error_code)
static void vmx_inject_page_fault_nested(struct kvm_vcpu *vcpu, struct x86_exception *fault)
static void nested_get_vmcs12_pages(struct kvm_vcpu *vcpu)
static void vmx_start_preemption_timer(struct kvm_vcpu *vcpu)
static int nested_vmx_check_io_bitmap_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_msr_bitmap_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_tpr_shadow_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static inline bool nested_vmx_prepare_msr_bitmap(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static void nested_cache_shadow_vmcs12(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static void nested_flush_cached_shadow_vmcs12(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_apic_access_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_apicv_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_msr_switch(struct kvm_vcpu *vcpu, unsigned long count_field, unsigned long addr_field)
static int nested_vmx_check_msr_switch_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_pml_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_shadow_vmcs_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_msr_check_common(struct kvm_vcpu *vcpu, struct vmx_msr_entry *e)
static int nested_vmx_load_msr_check(struct kvm_vcpu *vcpu, struct vmx_msr_entry *e)
static int nested_vmx_store_msr_check(struct kvm_vcpu *vcpu, struct vmx_msr_entry *e)
static u32 nested_vmx_load_msr(struct kvm_vcpu *vcpu, u64 gpa, u32 count)
static int nested_vmx_store_msr(struct kvm_vcpu *vcpu, u64 gpa, u32 count)
static bool nested_cr3_valid(struct kvm_vcpu *vcpu, unsigned long val)
static int nested_vmx_load_cr3(struct kvm_vcpu *vcpu, unsigned long cr3, bool nested_ept, u32 *entry_failure_code)
static bool nested_has_guest_tlb_tag(struct kvm_vcpu *vcpu)
static u64 nested_vmx_calc_efer(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
static void prepare_vmcs02_constant_state(struct vcpu_vmx *vmx)
static void prepare_vmcs02_early_full(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
static void prepare_vmcs02_early(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
static void prepare_vmcs02_full(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
static int prepare_vmcs02(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, u32 *entry_failure_code)
static int nested_vmx_check_nmi_controls(struct vmcs12 *vmcs12)
static int check_vmentry_prereqs(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_vmcs_link_ptr(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int check_vmentry_postreqs(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, u32 *exit_qual)
static int __noclone nested_vmx_check_vmentry_hw(struct kvm_vcpu *vcpu)
static int nested_vmx_enter_non_root_mode(struct kvm_vcpu *vcpu, bool from_vmentry)
static int nested_vmx_run(struct kvm_vcpu *vcpu, bool launch)
static inline unsigned long vmcs12_guest_cr0(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static inline unsigned long vmcs12_guest_cr4(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static void vmcs12_save_pending_event(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int vmx_check_nested_events(struct kvm_vcpu *vcpu, bool external_intr)
static void vmx_request_immediate_exit(struct kvm_vcpu *vcpu)
static u32 vmx_get_preemption_timer_value(struct kvm_vcpu *vcpu)
static void sync_vmcs12(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static void prepare_vmcs12(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, u32 exit_reason, u32 exit_intr_info, unsigned long exit_qualification)
static void load_vmcs12_host_state(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static inline u64 nested_vmx_get_vmcs01_guest_efer(struct vcpu_vmx *vmx)
static void nested_vmx_restore_host_state(struct kvm_vcpu *vcpu)
static void nested_vmx_vmexit(struct kvm_vcpu *vcpu, u32 exit_reason, u32 exit_intr_info, unsigned long exit_qualification)
static void vmx_leave_nested(struct kvm_vcpu *vcpu)
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
static inline int vmx_has_valid_vmcs12(struct kvm_vcpu *vcpu)
static int vmx_get_nested_state(struct kvm_vcpu *vcpu, struct kvm_nested_state __user *user_kvm_nested_state, u32 user_data_size)
static int vmx_set_nested_state(struct kvm_vcpu *vcpu, struct kvm_nested_state __user *user_kvm_nested_state, struct kvm_nested_state *kvm_state)
static void vmx_cleanup_l1d_flush(void)
static void vmx_exit(void)
static int __init vmx_init(void)
 276 struct kvm_vcpu *vcpu
  74 void
  60 struct vcpu_vmx *vmx
  49 struct vmcs12 *vmcs12
  27 unsigned long field
  17 struct kvm *kvm
  10 u32 msr
   9 u32 val
   9 u32 intr_info
   8 unsigned long val
   8 struct pi_desc *pi_desc
   8 int seg
   7 u64 data
   7 int cpu
   5 unsigned seg
   5 u32 exit_reason
   5 int vpid
   4 unsigned long *msr_bitmap
   4 u32 msr_index
   4 struct loaded_vmcs *loaded_vmcs
   4 struct desc_ptr *dt
   4 int vector
   4 int type
   3 unsigned long value
   3 unsigned long exit_qualification
   3 struct vmx_msr_entry *e
   3 struct vmcs12 *fields
   3 struct vmcs *vmcs
   3 struct kvm_segment *var
   2 vcpu
   2 unsigned msr
   2 unsigned long ext
   2 unsigned long exit
   2 unsigned long entry
   2 unsigned long cr3
   2 unsigned long cr0
   2 u64 value
   2 u64 host_val
   2 u64 guest_val
   2 u64 gpa
   2 u64 eptp
   2 u32 value
   2 u32 mask
   2 u32 low
   2 u32 high
   2 u32 exit_intr_info
   2 u32 count
   2 u32 bit
   2 u32 *entry_failure_code
   2 u16 value
   2 struct x86_exception *fault
   2 struct vmcs_config *vmcs_conf
   2 struct nested_vmx_msrs *msrs
   2 struct msr_data *msr_info
   2 struct kvm_segment *save
   2 struct kvm_nested_state __user *user_kvm_nested_state
   2 struct kvm_memory_slot *slot
   2 int vec
   2 gva_t addr
   2 gpa_t gpa
   2 const struct kernel_param *kp
   2 const char *s
   2 char *name
   2 bool shadow
   2 bool invalidate_gpa
   1 void *rtn
   1 void *arg
   1 unsigned long root_hpa
   1 unsigned long rflags
   1 unsigned long mask
   1 unsigned long host_val_vmcs
   1 unsigned long guest_val_vmcs
   1 unsigned long exit_qual
   1 unsigned long cr4
   1 unsigned long count_field
   1 unsigned long addr_field
   1 unsigned long *msr_bitmap_nested
   1 unsigned long *msr_bitmap_l1
   1 unsigned long *hw_cr0
   1 unsigned long *exit_qual
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
   1 uint16_t *vmcs_version
   1 u8 vector
   1 u8 mode
   1 u64 val
   1 u64 superset
   1 u64 subset
   1 u64 smbase
   1 u64 phys_addr
   1 u64 offset
   1 u64 mask
   1 u64 ident_addr
   1 u64 guest_deadline_tsc
   1 u64 fixed1
   1 u64 fixed0
   1 u64 efer
   1 u64 divisor
   1 u64 address
   1 u64 addr
   1 u64 a
   1 u64 *ret
   1 u64 *result
   1 u64 *pdata
   1 u64 *info2
   1 u64 *info1
   1 u64 *eoi_exit_bitmap
   1 u32 vmx_instruction_info
   1 u32 vm_instruction_error
   1 u32 user_data_size
   1 u32 new_ctl
   1 u32 indicator
   1 u32 idt_vectoring_info
   1 u32 func
   1 u32 err_code
   1 u32 ctl_opt
   1 u32 ctl_min
   1 u32 ctl
   1 u32 control
   1 u32 *result
   1 u32 *exit_qual
   1 u16 vpid
   1 u16 selector
   1 u16 error_code
   1 true
   1 struct x86_instruction_info *info
   1 struct vmx_msrs *m
   1 struct loaded_vmcs *vmcs
   1 struct kvm_nested_state *kvm_state
   1 struct kvm_msr_entry *msr
   1 struct kvm_memory_slot *memslot
   1 struct kvm_cpuid_entry2 *entry
   1 struct hrtimer *timer
   1 is_guest_modevcpu
   1 int tpr
   1 int to
   1 int max_isr
   1 int max_irr
   1 int mask
   1 int irr
   1 int instr_len_field
   1 int index
   1 int from
   1 int error_code_field
   1 int efer_offset
   1 int *l
   1 int *db
   1 hpa_t hpa
   1 gva_t gva
   1 gva_t *ret
   1 gpa_t vmptr
   1 gpa_t bitmap
   1 gpa_t *vmpointer
   1 gfn_t offset
   1 gfn_t gfn
   1 fields->guest_cr0 & ~fields->cr0_guest_host_mask
   1 fields->cr0_read_shadow & fields->cr0_guest_host_mask
   1 enum x86_intercept_stage stage
   1 enum vmx_l1d_flush_state l1tf
   1 enum kvm_reg reg
   1 char *smstate
   1 char *s
   1 bool wr
   1 bool value
   1 bool set
   1 bool nested_ept
   1 bool nested
   1 bool masked
   1 bool launch
   1 bool is_mmio
   1 bool init_event
   1 bool from_vmentry
   1 bool from_launch
   1 bool external_intr
   1 bool entry_only
   1 bool apicv
   1 KVM_REQ_EVENT
   1 !kvm_vcpu_trigger_posted_interruptvcpu
