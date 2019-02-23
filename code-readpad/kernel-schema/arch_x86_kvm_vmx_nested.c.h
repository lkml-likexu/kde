
\n
static void init_vmcs_shadow_fields(void)
static int nested_vmx_succeed(struct kvm_vcpu *vcpu)
static int nested_vmx_failInvalid(struct kvm_vcpu *vcpu)
static int nested_vmx_failValid(struct kvm_vcpu *vcpu, u32 vm_instruction_error)
static void nested_vmx_abort(struct kvm_vcpu *vcpu, u32 indicator)
static void vmx_disable_shadow_vmcs(struct vcpu_vmx *vmx)
static inline void nested_release_evmcs(struct kvm_vcpu *vcpu)
static void free_nested(struct kvm_vcpu *vcpu)
static void vmx_switch_vmcs(struct kvm_vcpu *vcpu, struct loaded_vmcs *vmcs)
void nested_vmx_free_vcpu(struct kvm_vcpu *vcpu)
static void nested_ept_inject_page_fault(struct kvm_vcpu *vcpu, struct x86_exception *fault)
static void nested_ept_init_mmu_context(struct kvm_vcpu *vcpu)
static void nested_ept_uninit_mmu_context(struct kvm_vcpu *vcpu)
static bool nested_vmx_is_page_fault_vmexit(struct vmcs12 *vmcs12, u16 error_code)
static int nested_vmx_check_exception(struct kvm_vcpu *vcpu, unsigned long *exit_qual)
static void vmx_inject_page_fault_nested(struct kvm_vcpu *vcpu, struct x86_exception *fault)
static bool page_address_valid(struct kvm_vcpu *vcpu, gpa_t gpa)
static int nested_vmx_check_io_bitmap_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_msr_bitmap_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_tpr_shadow_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static bool msr_write_intercepted_l01(struct kvm_vcpu *vcpu, u32 msr)
static void nested_vmx_disable_intercept_for_msr(unsigned long *msr_bitmap_l1, unsigned long *msr_bitmap_nested, u32 msr, int type)
static inline bool nested_vmx_prepare_msr_bitmap(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static void nested_cache_shadow_vmcs12(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static void nested_flush_cached_shadow_vmcs12(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static bool nested_exit_intr_ack_set(struct kvm_vcpu *vcpu)
static bool nested_exit_on_nmi(struct kvm_vcpu *vcpu)
static int nested_vmx_check_apic_access_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_apicv_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_msr_switch(struct kvm_vcpu *vcpu, u32 count, u64 addr)
static int nested_vmx_check_exit_msr_switch_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_entry_msr_switch_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_pml_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_unrestricted_guest_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_mode_based_ept_exec_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_shadow_vmcs_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_msr_check_common(struct kvm_vcpu *vcpu, struct vmx_msr_entry *e)
static int nested_vmx_load_msr_check(struct kvm_vcpu *vcpu, struct vmx_msr_entry *e)
static int nested_vmx_store_msr_check(struct kvm_vcpu *vcpu, struct vmx_msr_entry *e)
static u32 nested_vmx_load_msr(struct kvm_vcpu *vcpu, u64 gpa, u32 count)
static int nested_vmx_store_msr(struct kvm_vcpu *vcpu, u64 gpa, u32 count)
static bool nested_cr3_valid(struct kvm_vcpu *vcpu, unsigned long val)
static int nested_vmx_load_cr3(struct kvm_vcpu *vcpu, unsigned long cr3, bool nested_ept, u32 *entry_failure_code)
static bool nested_has_guest_tlb_tag(struct kvm_vcpu *vcpu)
static u16 nested_get_vpid02(struct kvm_vcpu *vcpu)
static inline bool vmx_control_verify(u32 control, u32 low, u32 high)
static inline u64 vmx_control_msr(u32 low, u32 high)
static bool is_bitwise_subset(u64 superset, u64 subset, u64 mask)
static int vmx_restore_vmx_basic(struct vcpu_vmx *vmx, u64 data)
static int vmx_restore_control_msr(struct vcpu_vmx *vmx, u32 msr_index, u64 data)
static int vmx_restore_vmx_misc(struct vcpu_vmx *vmx, u64 data)
static int vmx_restore_vmx_ept_vpid_cap(struct vcpu_vmx *vmx, u64 data)
static int vmx_restore_fixed0_msr(struct vcpu_vmx *vmx, u32 msr_index, u64 data)
int vmx_set_vmx_msr(struct kvm_vcpu *vcpu, u32 msr_index, u64 data)
int vmx_get_vmx_msr(struct nested_vmx_msrs *msrs, u32 msr_index, u64 *pdata)
static void copy_shadow_to_vmcs12(struct vcpu_vmx *vmx)
static void copy_vmcs12_to_shadow(struct vcpu_vmx *vmx)
static int copy_enlightened_to_vmcs12(struct vcpu_vmx *vmx)
static int copy_vmcs12_to_enlightened(struct vcpu_vmx *vmx)
static int nested_vmx_handle_enlightened_vmptrld(struct kvm_vcpu *vcpu, bool from_launch)
void nested_sync_from_vmcs12(struct kvm_vcpu *vcpu)
static enum hrtimer_restart vmx_preemption_timer_fn(struct hrtimer *timer)
static void vmx_start_preemption_timer(struct kvm_vcpu *vcpu)
static u64 nested_vmx_calc_efer(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
static void prepare_vmcs02_constant_state(struct vcpu_vmx *vmx)
static void prepare_vmcs02_early_full(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
static void prepare_vmcs02_early(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
static void prepare_vmcs02_full(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
static int prepare_vmcs02(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, u32 *entry_failure_code)
static int nested_vmx_check_nmi_controls(struct vmcs12 *vmcs12)
static bool valid_ept_address(struct kvm_vcpu *vcpu, u64 address)
static int nested_check_vm_execution_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_check_vm_exit_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_check_vm_entry_controls(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_check_host_control_regs(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_check_guest_non_reg_state(struct vmcs12 *vmcs12)
static int nested_vmx_check_vmentry_prereqs(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_vmcs_link_ptr(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int nested_vmx_check_vmentry_postreqs(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, u32 *exit_qual)
static int nested_vmx_check_vmentry_hw(struct kvm_vcpu *vcpu)
static void nested_get_vmcs12_pages(struct kvm_vcpu *vcpu)
static int nested_vmx_check_permission(struct kvm_vcpu *vcpu)
static u8 vmx_has_apicv_interrupt(struct kvm_vcpu *vcpu)
int nested_vmx_enter_non_root_mode(struct kvm_vcpu *vcpu, bool from_vmentry)
static int nested_vmx_run(struct kvm_vcpu *vcpu, bool launch)
static inline unsigned long vmcs12_guest_cr0(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static inline unsigned long vmcs12_guest_cr4(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static void vmcs12_save_pending_event(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static void nested_mark_vmcs12_pages_dirty(struct kvm_vcpu *vcpu)
static void vmx_complete_nested_posted_interrupt(struct kvm_vcpu *vcpu)
static void nested_vmx_inject_exception_vmexit(struct kvm_vcpu *vcpu, unsigned long exit_qual)
static int vmx_check_nested_events(struct kvm_vcpu *vcpu, bool external_intr)
static u32 vmx_get_preemption_timer_value(struct kvm_vcpu *vcpu)
static void sync_vmcs12(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static void prepare_vmcs12(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, u32 exit_reason, u32 exit_intr_info, unsigned long exit_qualification)
static void load_vmcs12_host_state(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static inline u64 nested_vmx_get_vmcs01_guest_efer(struct vcpu_vmx *vmx)
static void nested_vmx_restore_host_state(struct kvm_vcpu *vcpu)
void nested_vmx_vmexit(struct kvm_vcpu *vcpu, u32 exit_reason, u32 exit_intr_info, unsigned long exit_qualification)
int get_vmx_mem_address(struct kvm_vcpu *vcpu, unsigned long exit_qualification, u32 vmx_instruction_info, bool wr, gva_t *ret)
static int nested_vmx_get_vmptr(struct kvm_vcpu *vcpu, gpa_t *vmpointer)
static struct vmcs *alloc_shadow_vmcs(struct kvm_vcpu *vcpu)
static int enter_vmx_operation(struct kvm_vcpu *vcpu)
static int handle_vmon(struct kvm_vcpu *vcpu)
static inline void nested_release_vmcs12(struct kvm_vcpu *vcpu)
static int handle_vmoff(struct kvm_vcpu *vcpu)
static int handle_vmclear(struct kvm_vcpu *vcpu)
static int handle_vmlaunch(struct kvm_vcpu *vcpu)
static int handle_vmresume(struct kvm_vcpu *vcpu)
static int handle_vmread(struct kvm_vcpu *vcpu)
static int handle_vmwrite(struct kvm_vcpu *vcpu)
static void set_current_vmptr(struct vcpu_vmx *vmx, gpa_t vmptr)
static int handle_vmptrld(struct kvm_vcpu *vcpu)
static int handle_vmptrst(struct kvm_vcpu *vcpu)
static int handle_invept(struct kvm_vcpu *vcpu)
static int handle_invvpid(struct kvm_vcpu *vcpu)
static int nested_vmx_eptp_switching(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static int handle_vmfunc(struct kvm_vcpu *vcpu)
static bool nested_vmx_exit_handled_io(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static bool nested_vmx_exit_handled_msr(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, u32 exit_reason)
static bool nested_vmx_exit_handled_cr(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
static bool nested_vmx_exit_handled_vmcs_access(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12, gpa_t bitmap)
bool nested_vmx_exit_reflected(struct kvm_vcpu *vcpu, u32 exit_reason)
static int vmx_get_nested_state(struct kvm_vcpu *vcpu, struct kvm_nested_state __user *user_kvm_nested_state, u32 user_data_size)
void vmx_leave_nested(struct kvm_vcpu *vcpu)
static int vmx_set_nested_state(struct kvm_vcpu *vcpu, struct kvm_nested_state __user *user_kvm_nested_state, struct kvm_nested_state *kvm_state)
void nested_vmx_vcpu_setup(void)
void nested_vmx_setup_ctls_msrs(struct nested_vmx_msrs *msrs, u32 ept_caps, bool apicv)
void nested_vmx_hardware_unsetup(void)
__init int nested_vmx_hardware_setup(int (*exit_handlers[])
(struct kvm_vcpu *)
)
\n
     99 struct kvm_vcpu *vcpu
     40 struct vmcs12 *vmcs12
     17 struct vcpu_vmx *vmx
      6 u64 data
      4 u32 msr_index
      4 u32 exit_reason
      3 void
      3 unsigned long exit_qualification
      3 u32 count
      3 struct vmx_msr_entry *e
      2 u64 gpa
      2 u32 msr
      2 u32 low
      2 u32 high
      2 u32 exit_intr_info
      2 u32 *entry_failure_code
      2 struct x86_exception *fault
      2 struct nested_vmx_msrs *msrs
      2 struct kvm_nested_state __user *user_kvm_nested_state
      1 unsigned long val
      1 unsigned long *msr_bitmap_nested
      1 unsigned long *msr_bitmap_l1
      1 unsigned long exit_qual
      1 unsigned long *exit_qual
      1 unsigned long cr3
      1 u64 superset
      1 u64 subset
      1 u64 *pdata
      1 u64 mask
      1 u64 address
      1 u64 addr
      1 u32 vmx_instruction_info
      1 u32 vm_instruction_error
      1 u32 user_data_size
      1 u32 indicator
      1 u32 *exit_qual
      1 u32 ept_caps
      1 u32 control
      1 u16 error_code
      1 struct loaded_vmcs *vmcs
      1 struct kvm_vcpu *
      1 struct kvm_nested_state *kvm_state
      1 struct hrtimer *timer
      1 int type
      1 int *exit_handlers[]
      1 gva_t *ret
      1 gpa_t vmptr
      1 gpa_t *vmpointer
      1 gpa_t gpa
      1 gpa_t bitmap
      1 bool wr
      1 bool nested_ept
      1 bool launch
      1 bool from_vmentry
      1 bool from_launch
      1 bool external_intr
      1 bool apicv
