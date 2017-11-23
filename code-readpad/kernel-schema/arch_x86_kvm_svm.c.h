
static inline struct kvm_svm *to_kvm_svm(struct kvm *kvm)
static inline bool svm_sev_enabled(void)
static inline bool sev_guest(struct kvm *kvm)
static inline int sev_get_asid(struct kvm *kvm)
static inline void mark_all_dirty(struct vmcb *vmcb)
static inline void mark_all_clean(struct vmcb *vmcb)
static inline void mark_dirty(struct vmcb *vmcb, int bit)
static inline struct vcpu_svm *to_svm(struct kvm_vcpu *vcpu)
static inline void avic_update_vapic_bar(struct vcpu_svm *svm, u64 data)
static inline bool avic_vcpu_is_running(struct kvm_vcpu *vcpu)
static void recalc_intercepts(struct vcpu_svm *svm)
static inline struct vmcb *get_host_vmcb(struct vcpu_svm *svm)
static inline void set_cr_intercept(struct vcpu_svm *svm, int bit)
static inline void clr_cr_intercept(struct vcpu_svm *svm, int bit)
static inline bool is_cr_intercept(struct vcpu_svm *svm, int bit)
static inline void set_dr_intercepts(struct vcpu_svm *svm)
static inline void clr_dr_intercepts(struct vcpu_svm *svm)
static inline void set_exception_intercept(struct vcpu_svm *svm, int bit)
static inline void clr_exception_intercept(struct vcpu_svm *svm, int bit)
static inline void set_intercept(struct vcpu_svm *svm, int bit)
static inline void clr_intercept(struct vcpu_svm *svm, int bit)
static inline bool vgif_enabled(struct vcpu_svm *svm)
static inline void enable_gif(struct vcpu_svm *svm)
static inline void disable_gif(struct vcpu_svm *svm)
static inline bool gif_set(struct vcpu_svm *svm)
static u32 svm_msrpm_offset(u32 msr)
static inline void clgi(void)
static inline void stgi(void)
static inline void invlpga(unsigned long addr, u32 asid)
static int get_npt_level(struct kvm_vcpu *vcpu)
static void svm_set_efer(struct kvm_vcpu *vcpu, u64 efer)
static int is_external_interrupt(u32 info)
static u32 svm_get_interrupt_shadow(struct kvm_vcpu *vcpu)
static void svm_set_interrupt_shadow(struct kvm_vcpu *vcpu, int mask)
static void skip_emulated_instruction(struct kvm_vcpu *vcpu)
static void svm_queue_exception(struct kvm_vcpu *vcpu)
static void svm_init_erratum_383(void)
static void svm_init_osvw(struct kvm_vcpu *vcpu)
static int has_svm(void)
static void svm_hardware_disable(void)
static int svm_hardware_enable(void)
static void svm_cpu_uninit(int cpu)
static int svm_cpu_init(int cpu)
static bool valid_msr_intercept(u32 index)
static bool msr_write_intercepted(struct kvm_vcpu *vcpu, unsigned msr)
static void set_msr_interception(u32 *msrpm, unsigned msr, int read, int write)
static void svm_vcpu_init_msrpm(u32 *msrpm)
static void add_msr_offset(u32 offset)
static void init_msrpm_offsets(void)
static void svm_enable_lbrv(struct vcpu_svm *svm)
static void svm_disable_lbrv(struct vcpu_svm *svm)
static void disable_nmi_singlestep(struct vcpu_svm *svm)
static int avic_ga_log_notifier(u32 ga_tag)
static __init int sev_hardware_setup(void)
static void grow_ple_window(struct kvm_vcpu *vcpu)
static void shrink_ple_window(struct kvm_vcpu *vcpu)
static __init int svm_hardware_setup(void)
static __exit void svm_hardware_unsetup(void)
static void init_seg(struct vmcb_seg *seg)
static void init_sys_seg(struct vmcb_seg *seg, uint32_t type)
static u64 svm_read_l1_tsc_offset(struct kvm_vcpu *vcpu)
static void svm_write_tsc_offset(struct kvm_vcpu *vcpu, u64 offset)
static void avic_init_vmcb(struct vcpu_svm *svm)
static void init_vmcb(struct vcpu_svm *svm)
static u64 *avic_get_physical_id_entry(struct kvm_vcpu *vcpu, unsigned int index)
static int avic_init_access_page(struct kvm_vcpu *vcpu)
static int avic_init_backing_page(struct kvm_vcpu *vcpu)
static void __sev_asid_free(int asid)
static void sev_asid_free(struct kvm *kvm)
static void sev_unbind_asid(struct kvm *kvm, unsigned int handle)
static struct page **sev_pin_memory(struct kvm *kvm, unsigned long uaddr, unsigned long ulen, unsigned long *n, int write)
static void sev_unpin_memory(struct kvm *kvm, struct page **pages, unsigned long npages)
static void sev_clflush_pages(struct page *pages[], unsigned long npages)
static void __unregister_enc_region_locked(struct kvm *kvm, struct enc_region *region)
static struct kvm *svm_vm_alloc(void)
static void svm_vm_free(struct kvm *kvm)
static void sev_vm_destroy(struct kvm *kvm)
static void avic_vm_destroy(struct kvm *kvm)
static void svm_vm_destroy(struct kvm *kvm)
static int avic_vm_init(struct kvm *kvm)
static inline int avic_update_iommu_vcpu_affinity(struct kvm_vcpu *vcpu, int cpu, bool r)
static void avic_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
static void avic_vcpu_put(struct kvm_vcpu *vcpu)
static void avic_set_running(struct kvm_vcpu *vcpu, bool is_run)
static void svm_vcpu_reset(struct kvm_vcpu *vcpu, bool init_event)
static int avic_init_vcpu(struct vcpu_svm *svm)
static struct kvm_vcpu *svm_create_vcpu(struct kvm *kvm, unsigned int id)
static void svm_free_vcpu(struct kvm_vcpu *vcpu)
static void svm_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
static void svm_vcpu_put(struct kvm_vcpu *vcpu)
static void svm_vcpu_blocking(struct kvm_vcpu *vcpu)
static void svm_vcpu_unblocking(struct kvm_vcpu *vcpu)
static unsigned long svm_get_rflags(struct kvm_vcpu *vcpu)
static void svm_set_rflags(struct kvm_vcpu *vcpu, unsigned long rflags)
static void svm_cache_reg(struct kvm_vcpu *vcpu, enum kvm_reg reg)
static void svm_set_vintr(struct vcpu_svm *svm)
static void svm_clear_vintr(struct vcpu_svm *svm)
static struct vmcb_seg *svm_seg(struct kvm_vcpu *vcpu, int seg)
static u64 svm_get_segment_base(struct kvm_vcpu *vcpu, int seg)
static void svm_get_segment(struct kvm_vcpu *vcpu, struct kvm_segment *var, int seg)
static int svm_get_cpl(struct kvm_vcpu *vcpu)
static void svm_get_idt(struct kvm_vcpu *vcpu, struct desc_ptr *dt)
static void svm_set_idt(struct kvm_vcpu *vcpu, struct desc_ptr *dt)
static void svm_get_gdt(struct kvm_vcpu *vcpu, struct desc_ptr *dt)
static void svm_set_gdt(struct kvm_vcpu *vcpu, struct desc_ptr *dt)
static void svm_decache_cr0_guest_bits(struct kvm_vcpu *vcpu)
static void svm_decache_cr3(struct kvm_vcpu *vcpu)
static void svm_decache_cr4_guest_bits(struct kvm_vcpu *vcpu)
static void update_cr0_intercept(struct vcpu_svm *svm)
static void svm_set_cr0(struct kvm_vcpu *vcpu, unsigned long cr0)
static int svm_set_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
static void svm_set_segment(struct kvm_vcpu *vcpu, struct kvm_segment *var, int seg)
static void update_bp_intercept(struct kvm_vcpu *vcpu)
static void new_asid(struct vcpu_svm *svm, struct svm_cpu_data *sd)
static u64 svm_get_dr6(struct kvm_vcpu *vcpu)
static void svm_set_dr6(struct kvm_vcpu *vcpu, unsigned long value)
static void svm_sync_dirty_debug_regs(struct kvm_vcpu *vcpu)
static void svm_set_dr7(struct kvm_vcpu *vcpu, unsigned long value)
static int pf_interception(struct vcpu_svm *svm)
static int npf_interception(struct vcpu_svm *svm)
static int db_interception(struct vcpu_svm *svm)
static int bp_interception(struct vcpu_svm *svm)
static int ud_interception(struct vcpu_svm *svm)
static int ac_interception(struct vcpu_svm *svm)
static int gp_interception(struct vcpu_svm *svm)
static bool is_erratum_383(void)
static void svm_handle_mce(struct vcpu_svm *svm)
static int mc_interception(struct vcpu_svm *svm)
static int shutdown_interception(struct vcpu_svm *svm)
static int io_interception(struct vcpu_svm *svm)
static int nmi_interception(struct vcpu_svm *svm)
static int intr_interception(struct vcpu_svm *svm)
static int nop_on_interception(struct vcpu_svm *svm)
static int halt_interception(struct vcpu_svm *svm)
static int vmmcall_interception(struct vcpu_svm *svm)
static unsigned long nested_svm_get_tdp_cr3(struct kvm_vcpu *vcpu)
static u64 nested_svm_get_tdp_pdptr(struct kvm_vcpu *vcpu, int index)
static void nested_svm_set_tdp_cr3(struct kvm_vcpu *vcpu, unsigned long root)
static void nested_svm_inject_npf_exit(struct kvm_vcpu *vcpu, struct x86_exception *fault)
static void nested_svm_init_mmu_context(struct kvm_vcpu *vcpu)
static void nested_svm_uninit_mmu_context(struct kvm_vcpu *vcpu)
static int nested_svm_check_permissions(struct vcpu_svm *svm)
static int nested_svm_check_exception(struct vcpu_svm *svm, unsigned nr, bool has_error_code, u32 error_code)
static inline bool nested_svm_intr(struct vcpu_svm *svm)
static inline bool nested_svm_nmi(struct vcpu_svm *svm)
static void *nested_svm_map(struct vcpu_svm *svm, u64 gpa, struct page **_page)
static void nested_svm_unmap(struct page *page)
static int nested_svm_intercept_ioio(struct vcpu_svm *svm)
static int nested_svm_exit_handled_msr(struct vcpu_svm *svm)
static int nested_svm_intercept_db(struct vcpu_svm *svm)
static int nested_svm_exit_special(struct vcpu_svm *svm)
static int nested_svm_intercept(struct vcpu_svm *svm)
static int nested_svm_exit_handled(struct vcpu_svm *svm)
static inline void copy_vmcb_control_area(struct vmcb *dst_vmcb, struct vmcb *from_vmcb)
static int nested_svm_vmexit(struct vcpu_svm *svm)
static bool nested_svm_vmrun_msrpm(struct vcpu_svm *svm)
static bool nested_vmcb_checks(struct vmcb *vmcb)
static void enter_svm_guest_mode(struct vcpu_svm *svm, u64 vmcb_gpa, struct vmcb *nested_vmcb, struct page *page)
static bool nested_svm_vmrun(struct vcpu_svm *svm)
static void nested_svm_vmloadsave(struct vmcb *from_vmcb, struct vmcb *to_vmcb)
static int vmload_interception(struct vcpu_svm *svm)
static int vmsave_interception(struct vcpu_svm *svm)
static int vmrun_interception(struct vcpu_svm *svm)
static int stgi_interception(struct vcpu_svm *svm)
static int clgi_interception(struct vcpu_svm *svm)
static int invlpga_interception(struct vcpu_svm *svm)
static int skinit_interception(struct vcpu_svm *svm)
static int wbinvd_interception(struct vcpu_svm *svm)
static int xsetbv_interception(struct vcpu_svm *svm)
static int task_switch_interception(struct vcpu_svm *svm)
static int cpuid_interception(struct vcpu_svm *svm)
static int iret_interception(struct vcpu_svm *svm)
static int invlpg_interception(struct vcpu_svm *svm)
static int emulate_on_interception(struct vcpu_svm *svm)
static int rsm_interception(struct vcpu_svm *svm)
static int rdpmc_interception(struct vcpu_svm *svm)
static bool check_selective_cr0_intercepted(struct vcpu_svm *svm, unsigned long val)
static int cr_interception(struct vcpu_svm *svm)
static int dr_interception(struct vcpu_svm *svm)
static int cr8_write_interception(struct vcpu_svm *svm)
static int svm_get_msr_feature(struct kvm_msr_entry *msr)
static int svm_get_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
static int rdmsr_interception(struct vcpu_svm *svm)
static int svm_set_vm_cr(struct kvm_vcpu *vcpu, u64 data)
static int svm_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr)
static int wrmsr_interception(struct vcpu_svm *svm)
static int msr_interception(struct vcpu_svm *svm)
static int interrupt_window_interception(struct vcpu_svm *svm)
static int pause_interception(struct vcpu_svm *svm)
static int nop_interception(struct vcpu_svm *svm)
static int monitor_interception(struct vcpu_svm *svm)
static int mwait_interception(struct vcpu_svm *svm)
static int avic_incomplete_ipi_interception(struct vcpu_svm *svm)
static u32 *avic_get_logical_id_entry(struct kvm_vcpu *vcpu, u32 ldr, bool flat)
static int avic_ldr_write(struct kvm_vcpu *vcpu, u8 g_physical_id, u32 ldr, bool valid)
static int avic_handle_ldr_update(struct kvm_vcpu *vcpu)
static int avic_handle_apic_id_update(struct kvm_vcpu *vcpu)
static int avic_handle_dfr_update(struct kvm_vcpu *vcpu)
static int avic_unaccel_trap_write(struct vcpu_svm *svm)
static bool is_avic_unaccelerated_access_trap(u32 offset)
static int avic_unaccelerated_access_interception(struct vcpu_svm *svm)
static void dump_vmcb(struct kvm_vcpu *vcpu)
static void svm_get_exit_info(struct kvm_vcpu *vcpu, u64 *info1, u64 *info2)
static int handle_exit(struct kvm_vcpu *vcpu)
static void reload_tss(struct kvm_vcpu *vcpu)
static void pre_sev_run(struct vcpu_svm *svm, int cpu)
static void pre_svm_run(struct vcpu_svm *svm)
static void svm_inject_nmi(struct kvm_vcpu *vcpu)
static inline void svm_inject_irq(struct vcpu_svm *svm, int irq)
static void svm_set_irq(struct kvm_vcpu *vcpu)
static inline bool svm_nested_virtualize_tpr(struct kvm_vcpu *vcpu)
static void update_cr8_intercept(struct kvm_vcpu *vcpu, int tpr, int irr)
static void svm_set_virtual_apic_mode(struct kvm_vcpu *vcpu)
static bool svm_get_enable_apicv(struct kvm_vcpu *vcpu)
static void svm_hwapic_irr_update(struct kvm_vcpu *vcpu, int max_irr)
static void svm_hwapic_isr_update(struct kvm_vcpu *vcpu, int max_isr)
static void svm_refresh_apicv_exec_ctrl(struct kvm_vcpu *vcpu)
static void svm_load_eoi_exitmap(struct kvm_vcpu *vcpu, u64 *eoi_exit_bitmap)
static void svm_deliver_avic_intr(struct kvm_vcpu *vcpu, int vec)
static void svm_ir_list_del(struct vcpu_svm *svm, struct amd_iommu_pi_data *pi)
static int svm_ir_list_add(struct vcpu_svm *svm, struct amd_iommu_pi_data *pi)
static int get_pi_vcpu_info(struct kvm *kvm, struct kvm_kernel_irq_routing_entry *e, struct vcpu_data *vcpu_info, struct vcpu_svm **svm)
static int svm_update_pi_irte(struct kvm *kvm, unsigned int host_irq, uint32_t guest_irq, bool set)
static int svm_nmi_allowed(struct kvm_vcpu *vcpu)
static bool svm_get_nmi_mask(struct kvm_vcpu *vcpu)
static void svm_set_nmi_mask(struct kvm_vcpu *vcpu, bool masked)
static int svm_interrupt_allowed(struct kvm_vcpu *vcpu)
static void enable_irq_window(struct kvm_vcpu *vcpu)
static void enable_nmi_window(struct kvm_vcpu *vcpu)
static int svm_set_tss_addr(struct kvm *kvm, unsigned int addr)
static int svm_set_identity_map_addr(struct kvm *kvm, u64 ident_addr)
static void svm_flush_tlb(struct kvm_vcpu *vcpu, bool invalidate_gpa)
static void svm_flush_tlb_gva(struct kvm_vcpu *vcpu, gva_t gva)
static void svm_prepare_guest_switch(struct kvm_vcpu *vcpu)
static inline void sync_cr8_to_lapic(struct kvm_vcpu *vcpu)
static inline void sync_lapic_to_cr8(struct kvm_vcpu *vcpu)
static void svm_complete_interrupts(struct vcpu_svm *svm)
static void svm_cancel_injection(struct kvm_vcpu *vcpu)
static void svm_vcpu_run(struct kvm_vcpu *vcpu)
static void svm_set_cr3(struct kvm_vcpu *vcpu, unsigned long root)
static void set_tdp_cr3(struct kvm_vcpu *vcpu, unsigned long root)
static int is_disabled(void)
static void svm_patch_hypercall(struct kvm_vcpu *vcpu, unsigned char *hypercall)
static void svm_check_processor_compat(void *rtn)
static bool svm_cpu_has_accelerated_tpr(void)
static bool svm_has_emulated_msr(int index)
static u64 svm_get_mt_mask(struct kvm_vcpu *vcpu, gfn_t gfn, bool is_mmio)
static void svm_cpuid_update(struct kvm_vcpu *vcpu)
static void svm_set_supported_cpuid(u32 func, struct kvm_cpuid_entry2 *entry)
static int svm_get_lpage_level(void)
static bool svm_rdtscp_supported(void)
static bool svm_invpcid_supported(void)
static bool svm_mpx_supported(void)
static bool svm_xsaves_supported(void)
static bool svm_umip_emulated(void)
static bool svm_has_wbinvd_exit(void)
static int svm_check_intercept(struct kvm_vcpu *vcpu, struct x86_instruction_info *info, enum x86_intercept_stage stage)
static void svm_handle_external_intr(struct kvm_vcpu *vcpu)
static void svm_sched_in(struct kvm_vcpu *vcpu, int cpu)
static inline void avic_post_state_restore(struct kvm_vcpu *vcpu)
static void svm_setup_mce(struct kvm_vcpu *vcpu)
static int svm_smi_allowed(struct kvm_vcpu *vcpu)
static int svm_pre_enter_smm(struct kvm_vcpu *vcpu, char *smstate)
static int svm_pre_leave_smm(struct kvm_vcpu *vcpu, u64 smbase)
static int enable_smi_window(struct kvm_vcpu *vcpu)
static int sev_asid_new(void)
static int sev_guest_init(struct kvm *kvm, struct kvm_sev_cmd *argp)
static int sev_bind_asid(struct kvm *kvm, unsigned int handle, int *error)
static int __sev_issue_cmd(int fd, int id, void *data, int *error)
static int sev_issue_cmd(struct kvm *kvm, int id, void *data, int *error)
static int sev_launch_start(struct kvm *kvm, struct kvm_sev_cmd *argp)
static int get_num_contig_pages(int idx, struct page **inpages, unsigned long npages)
static int sev_launch_update_data(struct kvm *kvm, struct kvm_sev_cmd *argp)
static int sev_launch_measure(struct kvm *kvm, struct kvm_sev_cmd *argp)
static int sev_launch_finish(struct kvm *kvm, struct kvm_sev_cmd *argp)
static int sev_guest_status(struct kvm *kvm, struct kvm_sev_cmd *argp)
static int __sev_issue_dbg_cmd(struct kvm *kvm, unsigned long src, unsigned long dst, int size, int *error, bool enc)
static int __sev_dbg_decrypt(struct kvm *kvm, unsigned long src_paddr, unsigned long dst_paddr, int sz, int *err)
static int __sev_dbg_decrypt_user(struct kvm *kvm, unsigned long paddr, unsigned long __user dst_uaddr, unsigned long dst_paddr, int size, int *err)
static int __sev_dbg_encrypt_user(struct kvm *kvm, unsigned long paddr, unsigned long __user vaddr, unsigned long dst_paddr, unsigned long __user dst_vaddr, int size, int *error)
static int sev_dbg_crypt(struct kvm *kvm, struct kvm_sev_cmd *argp, bool dec)
static int sev_launch_secret(struct kvm *kvm, struct kvm_sev_cmd *argp)
static int svm_mem_enc_op(struct kvm *kvm, void __user *argp)
static int svm_register_enc_region(struct kvm *kvm, struct kvm_enc_region *range)
static struct enc_region * find_enc_region(struct kvm *kvm, struct kvm_enc_region *range)
static int svm_unregister_enc_region(struct kvm *kvm, struct kvm_enc_region *range)
static int nested_enable_evmcs(struct kvm_vcpu *vcpu, uint16_t *vmcs_version)
static int __init svm_init(void)
static void __exit svm_exit(void)
 106 struct kvm_vcpu *vcpu
  94 struct vcpu_svm *svm
  36 struct kvm *kvm
  25 void
   8 struct kvm_sev_cmd *argp
   8 int bit
   7 int cpu
   5 int *error
   4 struct vmcb *vmcb
   4 struct desc_ptr *dt
   4 int seg
   3 unsigned long root
   3 unsigned long npages
   3 unsigned long dst_paddr
   3 struct kvm_enc_region *range
   3 int size
   2 void *data
   2 unsigned msr
   2 unsigned long value
   2 unsigned long paddr
   2 unsigned int handle
   2 u64 data
   2 u32 offset
   2 u32 ldr
   2 u32 *msrpm
   2 struct vmcb_seg *seg
   2 struct vmcb *from_vmcb
   2 struct page *page
   2 struct kvm_segment *var
   2 struct amd_iommu_pi_data *pi
   2 int write
   2 int index
   2 int id
   2 int *err
   1 void __user *argp
   1 void *rtn
   1 unsigned nr
   1 unsigned long val
   1 unsigned long ulen
   1 unsigned long uaddr
   1 unsigned long src_paddr
   1 unsigned long src
   1 unsigned long rflags
   1 unsigned long dst
   1 unsigned long cr4
   1 unsigned long cr0
   1 unsigned long addr
   1 unsigned long __user vaddr
   1 unsigned long __user dst_vaddr
   1 unsigned long __user dst_uaddr
   1 unsigned long *n
   1 unsigned int index
   1 unsigned int id
   1 unsigned int host_irq
   1 unsigned int addr
   1 unsigned char *hypercall
   1 uint32_t type
   1 uint32_t guest_irq
   1 uint16_t *vmcs_version
   1 u8 g_physical_id
   1 u64 vmcb_gpa
   1 u64 smbase
   1 u64 offset
   1 u64 ident_addr
   1 u64 gpa
   1 u64 efer
   1 u64 *info2
   1 u64 *info1
   1 u64 *eoi_exit_bitmap
   1 u32 msr
   1 u32 info
   1 u32 index
   1 u32 ga_tag
   1 u32 func
   1 u32 error_code
   1 u32 asid
   1 struct x86_instruction_info *info
   1 struct x86_exception *fault
   1 struct vmcb *to_vmcb
   1 struct vmcb *nested_vmcb
   1 struct vmcb *dst_vmcb
   1 struct vcpu_svm **svm
   1 struct vcpu_data *vcpu_info
   1 struct svm_cpu_data *sd
   1 struct page *pages[]
   1 struct page **pages
   1 struct page **inpages
   1 struct page **_page
   1 struct msr_data *msr_info
   1 struct msr_data *msr
   1 struct kvm_msr_entry *msr
   1 struct kvm_kernel_irq_routing_entry *e
   1 struct kvm_cpuid_entry2 *entry
   1 struct enc_region *region
   1 int vec
   1 int tpr
   1 int sz
   1 int read
   1 int max_isr
   1 int max_irr
   1 int mask
   1 int irr
   1 int irq
   1 int idx
   1 int fd
   1 int asid
   1 gva_t gva
   1 gfn_t gfn
   1 enum x86_intercept_stage stage
   1 enum kvm_reg reg
   1 char *smstate
   1 bool valid
   1 bool set
   1 bool r
   1 bool masked
   1 bool is_run
   1 bool is_mmio
   1 bool invalidate_gpa
   1 bool init_event
   1 bool has_error_code
   1 bool flat
   1 bool enc
   1 bool dec
