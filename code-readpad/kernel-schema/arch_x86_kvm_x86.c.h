
EXPORT_SYMBOL_GPL(kvm_mce_cap_supported);
EXPORT_SYMBOL_GPL(kvm_x86_ops);
EXPORT_SYMBOL_GPL(kvm_has_tsc_control);
EXPORT_SYMBOL_GPL(kvm_max_guest_tsc_khz);
EXPORT_SYMBOL_GPL(kvm_tsc_scaling_ratio_frac_bits);
EXPORT_SYMBOL_GPL(kvm_max_tsc_scaling_ratio);
EXPORT_SYMBOL_GPL(kvm_default_tsc_scaling_ratio);
EXPORT_SYMBOL_GPL(lapic_timer_advance_ns);
EXPORT_SYMBOL_GPL(enable_vmware_backdoor);
EXPORT_SYMBOL_GPL(kvm_define_shared_msr);
EXPORT_SYMBOL_GPL(kvm_set_shared_msr);
EXPORT_SYMBOL_GPL(kvm_get_apic_base);
EXPORT_SYMBOL_GPL(kvm_get_apic_mode);
EXPORT_SYMBOL_GPL(kvm_set_apic_base);
EXPORT_SYMBOL_GPL(kvm_spurious_fault);
EXPORT_SYMBOL_GPL(kvm_deliver_exception_payload);
EXPORT_SYMBOL_GPL(kvm_queue_exception);
EXPORT_SYMBOL_GPL(kvm_requeue_exception);
EXPORT_SYMBOL_GPL(kvm_complete_insn_gp);
EXPORT_SYMBOL_GPL(kvm_inject_page_fault);
EXPORT_SYMBOL_GPL(kvm_inject_nmi);
EXPORT_SYMBOL_GPL(kvm_queue_exception_e);
EXPORT_SYMBOL_GPL(kvm_requeue_exception_e);
EXPORT_SYMBOL_GPL(kvm_require_cpl);
EXPORT_SYMBOL_GPL(kvm_require_dr);
EXPORT_SYMBOL_GPL(kvm_read_guest_page_mmu);
EXPORT_SYMBOL_GPL(load_pdptrs);
EXPORT_SYMBOL_GPL(pdptrs_changed);
EXPORT_SYMBOL_GPL(kvm_set_cr0);
EXPORT_SYMBOL_GPL(kvm_lmsw);
EXPORT_SYMBOL_GPL(kvm_set_xcr);
EXPORT_SYMBOL_GPL(kvm_set_cr4);
EXPORT_SYMBOL_GPL(kvm_set_cr3);
EXPORT_SYMBOL_GPL(kvm_set_cr8);
EXPORT_SYMBOL_GPL(kvm_get_cr8);
EXPORT_SYMBOL_GPL(kvm_set_dr);
EXPORT_SYMBOL_GPL(kvm_get_dr);
EXPORT_SYMBOL_GPL(kvm_rdpmc);
EXPORT_SYMBOL_GPL(kvm_get_arch_capabilities);
EXPORT_SYMBOL_GPL(kvm_valid_efer);
EXPORT_SYMBOL_GPL(kvm_enable_efer_bits);
EXPORT_SYMBOL_GPL(kvm_set_msr);
EXPORT_SYMBOL_GPL(kvm_scale_tsc);
EXPORT_SYMBOL_GPL(kvm_read_l1_tsc);
EXPORT_SYMBOL_GPL(kvm_write_tsc);
EXPORT_SYMBOL_GPL(kvm_set_msr_common);
EXPORT_SYMBOL_GPL(kvm_get_msr);
EXPORT_SYMBOL_GPL(kvm_get_msr_common);
EXPORT_SYMBOL_GPL(kvm_read_guest_virt);
EXPORT_SYMBOL_GPL(kvm_write_guest_virt_system);
EXPORT_SYMBOL_GPL(handle_ud);
EXPORT_SYMBOL_GPL(kvm_emulate_wbinvd);
EXPORT_SYMBOL_GPL(kvm_inject_realmode_interrupt);
EXPORT_SYMBOL_GPL(kvm_skip_emulated_instruction);
EXPORT_SYMBOL_GPL(kvm_emulate_instruction);
EXPORT_SYMBOL_GPL(kvm_emulate_instruction_from_buffer);
EXPORT_SYMBOL_GPL(kvm_fast_pio);
EXPORT_SYMBOL_GPL(kvm_vcpu_halt);
EXPORT_SYMBOL_GPL(kvm_emulate_halt);
EXPORT_SYMBOL_GPL(kvm_emulate_hypercall);
EXPORT_SYMBOL_GPL(kvm_vcpu_reload_apic_access_page);
EXPORT_SYMBOL_GPL(__kvm_request_immediate_exit);
EXPORT_SYMBOL_GPL(kvm_get_cs_db_l_bits);
EXPORT_SYMBOL_GPL(kvm_task_switch);
EXPORT_SYMBOL_GPL(kvm_vcpu_is_reset_bsp);
EXPORT_SYMBOL_GPL(kvm_no_apic_vcpu);
EXPORT_SYMBOL_GPL(__x86_set_memory_region);
EXPORT_SYMBOL_GPL(x86_set_memory_region);
EXPORT_SYMBOL_GPL(kvm_get_linear_rip);
EXPORT_SYMBOL_GPL(kvm_is_linear_rip);
EXPORT_SYMBOL_GPL(kvm_get_rflags);
EXPORT_SYMBOL_GPL(kvm_set_rflags);
EXPORT_SYMBOL_GPL(kvm_arch_start_assignment);
EXPORT_SYMBOL_GPL(kvm_arch_end_assignment);
EXPORT_SYMBOL_GPL(kvm_arch_has_assigned_device);
EXPORT_SYMBOL_GPL(kvm_arch_register_noncoherent_dma);
EXPORT_SYMBOL_GPL(kvm_arch_unregister_noncoherent_dma);
EXPORT_SYMBOL_GPL(kvm_arch_has_noncoherent_dma);
EXPORT_SYMBOL_GPL(kvm_vector_hashing_enabled);
static inline void kvm_async_pf_hash_reset(struct kvm_vcpu *vcpu)
static void kvm_on_user_return(struct user_return_notifier *urn)
static void shared_msr_update(unsigned slot, u32 msr)
void kvm_define_shared_msr(unsigned slot, u32 msr)
static void kvm_shared_msr_cpu_online(void)
int kvm_set_shared_msr(unsigned slot, u64 value, u64 mask)
static void drop_user_return_notifiers(void)
u64 kvm_get_apic_base(struct kvm_vcpu *vcpu)
enum lapic_mode kvm_get_apic_mode(struct kvm_vcpu *vcpu)
int kvm_set_apic_base(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
asmlinkage __visible void kvm_spurious_fault(void)
static int exception_class(int vector)
static int exception_type(int vector)
void kvm_deliver_exception_payload(struct kvm_vcpu *vcpu)
static void kvm_multiple_exception(struct kvm_vcpu *vcpu, unsigned nr, bool has_error, u32 error_code, bool has_payload, unsigned long payload, bool reinject)
void kvm_queue_exception(struct kvm_vcpu *vcpu, unsigned nr)
void kvm_requeue_exception(struct kvm_vcpu *vcpu, unsigned nr)
static void kvm_queue_exception_p(struct kvm_vcpu *vcpu, unsigned nr, unsigned long payload)
static void kvm_queue_exception_e_p(struct kvm_vcpu *vcpu, unsigned nr, u32 error_code, unsigned long payload)
int kvm_complete_insn_gp(struct kvm_vcpu *vcpu, int err)
void kvm_inject_page_fault(struct kvm_vcpu *vcpu, struct x86_exception *fault)
static bool kvm_propagate_fault(struct kvm_vcpu *vcpu, struct x86_exception *fault)
void kvm_inject_nmi(struct kvm_vcpu *vcpu)
void kvm_queue_exception_e(struct kvm_vcpu *vcpu, unsigned nr, u32 error_code)
void kvm_requeue_exception_e(struct kvm_vcpu *vcpu, unsigned nr, u32 error_code)
bool kvm_require_cpl(struct kvm_vcpu *vcpu, int required_cpl)
bool kvm_require_dr(struct kvm_vcpu *vcpu, int dr)
int kvm_read_guest_page_mmu(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, gfn_t ngfn, void *data, int offset, int len, u32 access)
static int kvm_read_nested_guest_page(struct kvm_vcpu *vcpu, gfn_t gfn, void *data, int offset, int len, u32 access)
int load_pdptrs(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, unsigned long cr3)
bool pdptrs_changed(struct kvm_vcpu *vcpu)
int kvm_set_cr0(struct kvm_vcpu *vcpu, unsigned long cr0)
void kvm_lmsw(struct kvm_vcpu *vcpu, unsigned long msw)
static void kvm_load_guest_xcr0(struct kvm_vcpu *vcpu)
static void kvm_put_guest_xcr0(struct kvm_vcpu *vcpu)
static int __kvm_set_xcr(struct kvm_vcpu *vcpu, u32 index, u64 xcr)
int kvm_set_xcr(struct kvm_vcpu *vcpu, u32 index, u64 xcr)
int kvm_set_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
int kvm_set_cr3(struct kvm_vcpu *vcpu, unsigned long cr3)
int kvm_set_cr8(struct kvm_vcpu *vcpu, unsigned long cr8)
unsigned long kvm_get_cr8(struct kvm_vcpu *vcpu)
static void kvm_update_dr0123(struct kvm_vcpu *vcpu)
static void kvm_update_dr6(struct kvm_vcpu *vcpu)
static void kvm_update_dr7(struct kvm_vcpu *vcpu)
static u64 kvm_dr6_fixed(struct kvm_vcpu *vcpu)
static int __kvm_set_dr(struct kvm_vcpu *vcpu, int dr, unsigned long val)
int kvm_set_dr(struct kvm_vcpu *vcpu, int dr, unsigned long val)
int kvm_get_dr(struct kvm_vcpu *vcpu, int dr, unsigned long *val)
bool kvm_rdpmc(struct kvm_vcpu *vcpu)
u64 kvm_get_arch_capabilities(void)
static int kvm_get_msr_feature(struct kvm_msr_entry *msr)
static int do_get_msr_feature(struct kvm_vcpu *vcpu, unsigned index, u64 *data)
bool kvm_valid_efer(struct kvm_vcpu *vcpu, u64 efer)
static int set_efer(struct kvm_vcpu *vcpu, u64 efer)
void kvm_enable_efer_bits(u64 mask)
int kvm_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr)
static int do_get_msr(struct kvm_vcpu *vcpu, unsigned index, u64 *data)
static int do_set_msr(struct kvm_vcpu *vcpu, unsigned index, u64 *data)
static void update_pvclock_gtod(struct timekeeper *tk)
void kvm_set_pending_timer(struct kvm_vcpu *vcpu)
static void kvm_write_wall_clock(struct kvm *kvm, gpa_t wall_clock)
static uint32_t div_frac(uint32_t dividend, uint32_t divisor)
static void kvm_get_time_scale(uint64_t scaled_hz, uint64_t base_hz, s8 *pshift, u32 *pmultiplier)
static u32 adjust_tsc_khz(u32 khz, s32 ppm)
static int set_tsc_khz(struct kvm_vcpu *vcpu, u32 user_tsc_khz, bool scale)
static int kvm_set_tsc_khz(struct kvm_vcpu *vcpu, u32 user_tsc_khz)
static u64 compute_guest_tsc(struct kvm_vcpu *vcpu, s64 kernel_ns)
static inline int gtod_is_based_on_tsc(int mode)
static void kvm_track_tsc_matching(struct kvm_vcpu *vcpu)
static void update_ia32_tsc_adjust_msr(struct kvm_vcpu *vcpu, s64 offset)
static inline u64 __scale_tsc(u64 ratio, u64 tsc)
u64 kvm_scale_tsc(struct kvm_vcpu *vcpu, u64 tsc)
static u64 kvm_compute_tsc_offset(struct kvm_vcpu *vcpu, u64 target_tsc)
u64 kvm_read_l1_tsc(struct kvm_vcpu *vcpu, u64 host_tsc)
static void kvm_vcpu_write_tsc_offset(struct kvm_vcpu *vcpu, u64 offset)
static inline bool kvm_check_tsc_unstable(void)
void kvm_write_tsc(struct kvm_vcpu *vcpu, struct msr_data *msr)
static inline void adjust_tsc_offset_guest(struct kvm_vcpu *vcpu, s64 adjustment)
static inline void adjust_tsc_offset_host(struct kvm_vcpu *vcpu, s64 adjustment)
static u64 read_tsc(void)
static inline u64 vgettsc(u64 *tsc_timestamp, int *mode)
static int do_monotonic_boot(s64 *t, u64 *tsc_timestamp)
static int do_realtime(struct timespec64 *ts, u64 *tsc_timestamp)
static bool kvm_get_time_and_clockread(s64 *kernel_ns, u64 *tsc_timestamp)
static bool kvm_get_walltime_and_clockread(struct timespec64 *ts, u64 *tsc_timestamp)
static void pvclock_update_vm_gtod_copy(struct kvm *kvm)
void kvm_make_mclock_inprogress_request(struct kvm *kvm)
static void kvm_gen_update_masterclock(struct kvm *kvm)
u64 get_kvmclock_ns(struct kvm *kvm)
static void kvm_setup_pvclock_page(struct kvm_vcpu *v)
static int kvm_guest_time_update(struct kvm_vcpu *v)
static void kvmclock_update_fn(struct work_struct *work)
static void kvm_gen_kvmclock_update(struct kvm_vcpu *v)
static void kvmclock_sync_fn(struct work_struct *work)
static int set_msr_mce(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
static int xen_hvm_config(struct kvm_vcpu *vcpu, u64 data)
static int kvm_pv_enable_async_pf(struct kvm_vcpu *vcpu, u64 data)
static void kvmclock_reset(struct kvm_vcpu *vcpu)
static void kvm_vcpu_flush_tlb(struct kvm_vcpu *vcpu, bool invalidate_gpa)
static void record_steal_time(struct kvm_vcpu *vcpu)
int kvm_set_msr_common(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
int kvm_get_msr(struct kvm_vcpu *vcpu, struct msr_data *msr)
static int get_msr_mce(struct kvm_vcpu *vcpu, u32 msr, u64 *pdata, bool host)
int kvm_get_msr_common(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
static int __msr_io(struct kvm_vcpu *vcpu, struct kvm_msrs *msrs, struct kvm_msr_entry *entries, int (*do_msr)
(struct kvm_vcpu *vcpu, unsigned index, u64 *data)
)
static int msr_io(struct kvm_vcpu *vcpu, struct kvm_msrs __user *user_msrs, int (*do_msr)
(struct kvm_vcpu *vcpu, unsigned index, u64 *data)
, int writeback)
static inline bool kvm_can_mwait_in_guest(void)
int kvm_vm_ioctl_check_extension(struct kvm *kvm, long ext)
long kvm_arch_dev_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
static void wbinvd_ipi(void *garbage)
static bool need_emulate_wbinvd(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
static void kvm_steal_time_set_preempted(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
static int kvm_vcpu_ioctl_get_lapic(struct kvm_vcpu *vcpu, struct kvm_lapic_state *s)
static int kvm_vcpu_ioctl_set_lapic(struct kvm_vcpu *vcpu, struct kvm_lapic_state *s)
static int kvm_cpu_accept_dm_intr(struct kvm_vcpu *vcpu)
static int kvm_vcpu_ready_for_interrupt_injection(struct kvm_vcpu *vcpu)
static int kvm_vcpu_ioctl_interrupt(struct kvm_vcpu *vcpu, struct kvm_interrupt *irq)
static int kvm_vcpu_ioctl_nmi(struct kvm_vcpu *vcpu)
static int kvm_vcpu_ioctl_smi(struct kvm_vcpu *vcpu)
static int vcpu_ioctl_tpr_access_reporting(struct kvm_vcpu *vcpu, struct kvm_tpr_access_ctl *tac)
static int kvm_vcpu_ioctl_x86_setup_mce(struct kvm_vcpu *vcpu, u64 mcg_cap)
static int kvm_vcpu_ioctl_x86_set_mce(struct kvm_vcpu *vcpu, struct kvm_x86_mce *mce)
static void kvm_vcpu_ioctl_x86_get_vcpu_events(struct kvm_vcpu *vcpu, struct kvm_vcpu_events *events)
static int kvm_vcpu_ioctl_x86_set_vcpu_events(struct kvm_vcpu *vcpu, struct kvm_vcpu_events *events)
static void kvm_vcpu_ioctl_x86_get_debugregs(struct kvm_vcpu *vcpu, struct kvm_debugregs *dbgregs)
static int kvm_vcpu_ioctl_x86_set_debugregs(struct kvm_vcpu *vcpu, struct kvm_debugregs *dbgregs)
static void fill_xsave(u8 *dest, struct kvm_vcpu *vcpu)
static void load_xsave(struct kvm_vcpu *vcpu, u8 *src)
static void kvm_vcpu_ioctl_x86_get_xsave(struct kvm_vcpu *vcpu, struct kvm_xsave *guest_xsave)
static int kvm_vcpu_ioctl_x86_set_xsave(struct kvm_vcpu *vcpu, struct kvm_xsave *guest_xsave)
static void kvm_vcpu_ioctl_x86_get_xcrs(struct kvm_vcpu *vcpu, struct kvm_xcrs *guest_xcrs)
static int kvm_vcpu_ioctl_x86_set_xcrs(struct kvm_vcpu *vcpu, struct kvm_xcrs *guest_xcrs)
static int kvm_set_guest_paused(struct kvm_vcpu *vcpu)
static int kvm_vcpu_ioctl_enable_cap(struct kvm_vcpu *vcpu, struct kvm_enable_cap *cap)
long kvm_arch_vcpu_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
vm_fault_t kvm_arch_vcpu_fault(struct kvm_vcpu *vcpu, struct vm_fault *vmf)
static int kvm_vm_ioctl_set_tss_addr(struct kvm *kvm, unsigned long addr)
static int kvm_vm_ioctl_set_identity_map_addr(struct kvm *kvm, u64 ident_addr)
static int kvm_vm_ioctl_set_nr_mmu_pages(struct kvm *kvm, u32 kvm_nr_mmu_pages)
static int kvm_vm_ioctl_get_nr_mmu_pages(struct kvm *kvm)
static int kvm_vm_ioctl_get_irqchip(struct kvm *kvm, struct kvm_irqchip *chip)
static int kvm_vm_ioctl_set_irqchip(struct kvm *kvm, struct kvm_irqchip *chip)
static int kvm_vm_ioctl_get_pit(struct kvm *kvm, struct kvm_pit_state *ps)
static int kvm_vm_ioctl_set_pit(struct kvm *kvm, struct kvm_pit_state *ps)
static int kvm_vm_ioctl_get_pit2(struct kvm *kvm, struct kvm_pit_state2 *ps)
static int kvm_vm_ioctl_set_pit2(struct kvm *kvm, struct kvm_pit_state2 *ps)
static int kvm_vm_ioctl_reinject(struct kvm *kvm, struct kvm_reinject_control *control)
int kvm_vm_ioctl_get_dirty_log(struct kvm *kvm, struct kvm_dirty_log *log)
int kvm_vm_ioctl_irq_line(struct kvm *kvm, struct kvm_irq_level *irq_event, bool line_status)
static int kvm_vm_ioctl_enable_cap(struct kvm *kvm, struct kvm_enable_cap *cap)
long kvm_arch_vm_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
static void kvm_init_msr_list(void)
static int vcpu_mmio_write(struct kvm_vcpu *vcpu, gpa_t addr, int len, const void *v)
static int vcpu_mmio_read(struct kvm_vcpu *vcpu, gpa_t addr, int len, void *v)
static void kvm_set_segment(struct kvm_vcpu *vcpu, struct kvm_segment *var, int seg)
void kvm_get_segment(struct kvm_vcpu *vcpu, struct kvm_segment *var, int seg)
gpa_t translate_nested_gpa(struct kvm_vcpu *vcpu, gpa_t gpa, u32 access, struct x86_exception *exception)
gpa_t kvm_mmu_gva_to_gpa_read(struct kvm_vcpu *vcpu, gva_t gva, struct x86_exception *exception)
gpa_t kvm_mmu_gva_to_gpa_fetch(struct kvm_vcpu *vcpu, gva_t gva, struct x86_exception *exception)
gpa_t kvm_mmu_gva_to_gpa_write(struct kvm_vcpu *vcpu, gva_t gva, struct x86_exception *exception)
gpa_t kvm_mmu_gva_to_gpa_system(struct kvm_vcpu *vcpu, gva_t gva, struct x86_exception *exception)
static int kvm_read_guest_virt_helper(gva_t addr, void *val, unsigned int bytes, struct kvm_vcpu *vcpu, u32 access, struct x86_exception *exception)
static int kvm_fetch_guest_virt(struct x86_emulate_ctxt *ctxt, gva_t addr, void *val, unsigned int bytes, struct x86_exception *exception)
int kvm_read_guest_virt(struct kvm_vcpu *vcpu, gva_t addr, void *val, unsigned int bytes, struct x86_exception *exception)
static int emulator_read_std(struct x86_emulate_ctxt *ctxt, gva_t addr, void *val, unsigned int bytes, struct x86_exception *exception, bool system)
static int kvm_read_guest_phys_system(struct x86_emulate_ctxt *ctxt, unsigned long addr, void *val, unsigned int bytes)
static int kvm_write_guest_virt_helper(gva_t addr, void *val, unsigned int bytes, struct kvm_vcpu *vcpu, u32 access, struct x86_exception *exception)
static int emulator_write_std(struct x86_emulate_ctxt *ctxt, gva_t addr, void *val, unsigned int bytes, struct x86_exception *exception, bool system)
int kvm_write_guest_virt_system(struct kvm_vcpu *vcpu, gva_t addr, void *val, unsigned int bytes, struct x86_exception *exception)
int handle_ud(struct kvm_vcpu *vcpu)
static int vcpu_is_mmio_gpa(struct kvm_vcpu *vcpu, unsigned long gva, gpa_t gpa, bool write)
static int vcpu_mmio_gva_to_gpa(struct kvm_vcpu *vcpu, unsigned long gva, gpa_t *gpa, struct x86_exception *exception, bool write)
int emulator_write_phys(struct kvm_vcpu *vcpu, gpa_t gpa, const void *val, int bytes)
static int read_prepare(struct kvm_vcpu *vcpu, void *val, int bytes)
static int read_emulate(struct kvm_vcpu *vcpu, gpa_t gpa, void *val, int bytes)
static int write_emulate(struct kvm_vcpu *vcpu, gpa_t gpa, void *val, int bytes)
static int write_mmio(struct kvm_vcpu *vcpu, gpa_t gpa, int bytes, void *val)
static int read_exit_mmio(struct kvm_vcpu *vcpu, gpa_t gpa, void *val, int bytes)
static int write_exit_mmio(struct kvm_vcpu *vcpu, gpa_t gpa, void *val, int bytes)
static int emulator_read_write_onepage(unsigned long addr, void *val, unsigned int bytes, struct x86_exception *exception, struct kvm_vcpu *vcpu, const struct read_write_emulator_ops *ops)
static int emulator_read_write(struct x86_emulate_ctxt *ctxt, unsigned long addr, void *val, unsigned int bytes, struct x86_exception *exception, const struct read_write_emulator_ops *ops)
static int emulator_read_emulated(struct x86_emulate_ctxt *ctxt, unsigned long addr, void *val, unsigned int bytes, struct x86_exception *exception)
static int emulator_write_emulated(struct x86_emulate_ctxt *ctxt, unsigned long addr, const void *val, unsigned int bytes, struct x86_exception *exception)
static int emulator_cmpxchg_emulated(struct x86_emulate_ctxt *ctxt, unsigned long addr, const void *old, const void *new, unsigned int bytes, struct x86_exception *exception)
static int kernel_pio(struct kvm_vcpu *vcpu, void *pd)
static int emulator_pio_in_out(struct kvm_vcpu *vcpu, int size, unsigned short port, void *val, unsigned int count, bool in)
static int emulator_pio_in_emulated(struct x86_emulate_ctxt *ctxt, int size, unsigned short port, void *val, unsigned int count)
static int emulator_pio_out_emulated(struct x86_emulate_ctxt *ctxt, int size, unsigned short port, const void *val, unsigned int count)
static unsigned long get_segment_base(struct kvm_vcpu *vcpu, int seg)
static void emulator_invlpg(struct x86_emulate_ctxt *ctxt, ulong address)
static int kvm_emulate_wbinvd_noskip(struct kvm_vcpu *vcpu)
int kvm_emulate_wbinvd(struct kvm_vcpu *vcpu)
static void emulator_wbinvd(struct x86_emulate_ctxt *ctxt)
static int emulator_get_dr(struct x86_emulate_ctxt *ctxt, int dr, unsigned long *dest)
static int emulator_set_dr(struct x86_emulate_ctxt *ctxt, int dr, unsigned long value)
static u64 mk_cr_64(u64 curr_cr, u32 new_val)
static unsigned long emulator_get_cr(struct x86_emulate_ctxt *ctxt, int cr)
static int emulator_set_cr(struct x86_emulate_ctxt *ctxt, int cr, ulong val)
static int emulator_get_cpl(struct x86_emulate_ctxt *ctxt)
static void emulator_get_gdt(struct x86_emulate_ctxt *ctxt, struct desc_ptr *dt)
static void emulator_get_idt(struct x86_emulate_ctxt *ctxt, struct desc_ptr *dt)
static void emulator_set_gdt(struct x86_emulate_ctxt *ctxt, struct desc_ptr *dt)
static void emulator_set_idt(struct x86_emulate_ctxt *ctxt, struct desc_ptr *dt)
static unsigned long emulator_get_cached_segment_base(struct x86_emulate_ctxt *ctxt, int seg)
static bool emulator_get_segment(struct x86_emulate_ctxt *ctxt, u16 *selector, struct desc_struct *desc, u32 *base3, int seg)
static void emulator_set_segment(struct x86_emulate_ctxt *ctxt, u16 selector, struct desc_struct *desc, u32 base3, int seg)
static int emulator_get_msr(struct x86_emulate_ctxt *ctxt, u32 msr_index, u64 *pdata)
static int emulator_set_msr(struct x86_emulate_ctxt *ctxt, u32 msr_index, u64 data)
static u64 emulator_get_smbase(struct x86_emulate_ctxt *ctxt)
static void emulator_set_smbase(struct x86_emulate_ctxt *ctxt, u64 smbase)
static int emulator_check_pmc(struct x86_emulate_ctxt *ctxt, u32 pmc)
static int emulator_read_pmc(struct x86_emulate_ctxt *ctxt, u32 pmc, u64 *pdata)
static void emulator_halt(struct x86_emulate_ctxt *ctxt)
static int emulator_intercept(struct x86_emulate_ctxt *ctxt, struct x86_instruction_info *info, enum x86_intercept_stage stage)
static bool emulator_get_cpuid(struct x86_emulate_ctxt *ctxt, u32 *eax, u32 *ebx, u32 *ecx, u32 *edx, bool check_limit)
static ulong emulator_read_gpr(struct x86_emulate_ctxt *ctxt, unsigned reg)
static void emulator_write_gpr(struct x86_emulate_ctxt *ctxt, unsigned reg, ulong val)
static void emulator_set_nmi_mask(struct x86_emulate_ctxt *ctxt, bool masked)
static unsigned emulator_get_hflags(struct x86_emulate_ctxt *ctxt)
static void emulator_set_hflags(struct x86_emulate_ctxt *ctxt, unsigned emul_flags)
static int emulator_pre_leave_smm(struct x86_emulate_ctxt *ctxt, u64 smbase)
static void toggle_interruptibility(struct kvm_vcpu *vcpu, u32 mask)
static bool inject_emulated_exception(struct kvm_vcpu *vcpu)
static void init_emulate_ctxt(struct kvm_vcpu *vcpu)
int kvm_inject_realmode_interrupt(struct kvm_vcpu *vcpu, int irq, int inc_eip)
static int handle_emulation_failure(struct kvm_vcpu *vcpu, int emulation_type)
static bool reexecute_instruction(struct kvm_vcpu *vcpu, gva_t cr2, bool write_fault_to_shadow_pgtable, int emulation_type)
static bool retry_instruction(struct x86_emulate_ctxt *ctxt, unsigned long cr2, int emulation_type)
static void kvm_smm_changed(struct kvm_vcpu *vcpu)
static void kvm_set_hflags(struct kvm_vcpu *vcpu, unsigned emul_flags)
static int kvm_vcpu_check_hw_bp(unsigned long addr, u32 type, u32 dr7, unsigned long *db)
static void kvm_vcpu_do_singlestep(struct kvm_vcpu *vcpu, int *r)
int kvm_skip_emulated_instruction(struct kvm_vcpu *vcpu)
static bool kvm_vcpu_check_breakpoint(struct kvm_vcpu *vcpu, int *r)
static bool is_vmware_backdoor_opcode(struct x86_emulate_ctxt *ctxt)
int x86_emulate_instruction(struct kvm_vcpu *vcpu, unsigned long cr2, int emulation_type, void *insn, int insn_len)
int kvm_emulate_instruction(struct kvm_vcpu *vcpu, int emulation_type)
int kvm_emulate_instruction_from_buffer(struct kvm_vcpu *vcpu, void *insn, int insn_len)
static int kvm_fast_pio_out(struct kvm_vcpu *vcpu, int size, unsigned short port)
static int complete_fast_pio_in(struct kvm_vcpu *vcpu)
static int kvm_fast_pio_in(struct kvm_vcpu *vcpu, int size, unsigned short port)
int kvm_fast_pio(struct kvm_vcpu *vcpu, int size, unsigned short port, int in)
static int kvmclock_cpu_down_prep(unsigned int cpu)
static void tsc_khz_changed(void *data)
static void kvm_hyperv_tsc_notifier(void)
static int kvmclock_cpufreq_notifier(struct notifier_block *nb, unsigned long val, void *data)
static int kvmclock_cpu_online(unsigned int cpu)
static void kvm_timer_init(void)
int kvm_is_in_guest(void)
static int kvm_is_user_mode(void)
static unsigned long kvm_get_guest_ip(void)
static void kvm_set_mmio_spte_mask(void)
static void pvclock_gtod_update_fn(struct work_struct *work)
static int pvclock_gtod_notify(struct notifier_block *nb, unsigned long unused, void *priv)
int kvm_arch_init(void *opaque)
void kvm_arch_exit(void)
int kvm_vcpu_halt(struct kvm_vcpu *vcpu)
int kvm_emulate_halt(struct kvm_vcpu *vcpu)
static int kvm_pv_clock_pairing(struct kvm_vcpu *vcpu, gpa_t paddr, unsigned long clock_type)
static void kvm_pv_kick_cpu_op(struct kvm *kvm, unsigned long flags, int apicid)
void kvm_vcpu_deactivate_apicv(struct kvm_vcpu *vcpu)
int kvm_emulate_hypercall(struct kvm_vcpu *vcpu)
static int emulator_fix_hypercall(struct x86_emulate_ctxt *ctxt)
static int dm_request_for_irq_injection(struct kvm_vcpu *vcpu)
static void post_kvm_run_save(struct kvm_vcpu *vcpu)
static void update_cr8_intercept(struct kvm_vcpu *vcpu)
static int inject_pending_event(struct kvm_vcpu *vcpu, bool req_int_win)
static void process_nmi(struct kvm_vcpu *vcpu)
static u32 enter_smm_get_segment_flags(struct kvm_segment *seg)
static void enter_smm_save_seg_32(struct kvm_vcpu *vcpu, char *buf, int n)
static void enter_smm_save_seg_64(struct kvm_vcpu *vcpu, char *buf, int n)
static void enter_smm_save_state_32(struct kvm_vcpu *vcpu, char *buf)
static void enter_smm_save_state_64(struct kvm_vcpu *vcpu, char *buf)
static void enter_smm(struct kvm_vcpu *vcpu)
static void process_smi(struct kvm_vcpu *vcpu)
void kvm_make_scan_ioapic_request(struct kvm *kvm)
static void vcpu_scan_ioapic(struct kvm_vcpu *vcpu)
static void vcpu_load_eoi_exitmap(struct kvm_vcpu *vcpu)
int kvm_arch_mmu_notifier_invalidate_range(struct kvm *kvm, unsigned long start, unsigned long end, bool blockable)
void kvm_vcpu_reload_apic_access_page(struct kvm_vcpu *vcpu)
void __kvm_request_immediate_exit(struct kvm_vcpu *vcpu)
static int vcpu_enter_guest(struct kvm_vcpu *vcpu)
static inline int vcpu_block(struct kvm *kvm, struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_running(struct kvm_vcpu *vcpu)
static int vcpu_run(struct kvm_vcpu *vcpu)
static inline int complete_emulated_io(struct kvm_vcpu *vcpu)
static int complete_emulated_pio(struct kvm_vcpu *vcpu)
static int complete_emulated_mmio(struct kvm_vcpu *vcpu)
static void kvm_load_guest_fpu(struct kvm_vcpu *vcpu)
static void kvm_put_guest_fpu(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_run(struct kvm_vcpu *vcpu, struct kvm_run *kvm_run)
static void __get_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
int kvm_arch_vcpu_ioctl_get_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
static void __set_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
int kvm_arch_vcpu_ioctl_set_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
void kvm_get_cs_db_l_bits(struct kvm_vcpu *vcpu, int *db, int *l)
static void __get_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_get_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_get_mpstate(struct kvm_vcpu *vcpu, struct kvm_mp_state *mp_state)
int kvm_arch_vcpu_ioctl_set_mpstate(struct kvm_vcpu *vcpu, struct kvm_mp_state *mp_state)
int kvm_task_switch(struct kvm_vcpu *vcpu, u16 tss_selector, int idt_index, int reason, bool has_error_code, u32 error_code)
static int kvm_valid_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
static int __set_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_set_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_set_guest_debug(struct kvm_vcpu *vcpu, struct kvm_guest_debug *dbg)
int kvm_arch_vcpu_ioctl_translate(struct kvm_vcpu *vcpu, struct kvm_translation *tr)
int kvm_arch_vcpu_ioctl_get_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
int kvm_arch_vcpu_ioctl_set_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
static void store_regs(struct kvm_vcpu *vcpu)
static int sync_regs(struct kvm_vcpu *vcpu)
static void fx_init(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_free(struct kvm_vcpu *vcpu)
struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm, unsigned int id)
int kvm_arch_vcpu_setup(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_postcreate(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_destroy(struct kvm_vcpu *vcpu)
void kvm_vcpu_reset(struct kvm_vcpu *vcpu, bool init_event)
void kvm_vcpu_deliver_sipi_vector(struct kvm_vcpu *vcpu, u8 vector)
int kvm_arch_hardware_enable(void)
void kvm_arch_hardware_disable(void)
int kvm_arch_hardware_setup(void)
void kvm_arch_hardware_unsetup(void)
void kvm_arch_check_processor_compat(void *rtn)
bool kvm_vcpu_is_reset_bsp(struct kvm_vcpu *vcpu)
bool kvm_vcpu_is_bsp(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_init(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_uninit(struct kvm_vcpu *vcpu)
void kvm_arch_sched_in(struct kvm_vcpu *vcpu, int cpu)
int kvm_arch_init_vm(struct kvm *kvm, unsigned long type)
static void kvm_unload_vcpu_mmu(struct kvm_vcpu *vcpu)
static void kvm_free_vcpus(struct kvm *kvm)
void kvm_arch_sync_events(struct kvm *kvm)
int __x86_set_memory_region(struct kvm *kvm, int id, gpa_t gpa, u32 size)
int x86_set_memory_region(struct kvm *kvm, int id, gpa_t gpa, u32 size)
void kvm_arch_destroy_vm(struct kvm *kvm)
void kvm_arch_free_memslot(struct kvm *kvm, struct kvm_memory_slot *free, struct kvm_memory_slot *dont)
int kvm_arch_create_memslot(struct kvm *kvm, struct kvm_memory_slot *slot, unsigned long npages)
void kvm_arch_memslots_updated(struct kvm *kvm, struct kvm_memslots *slots)
int kvm_arch_prepare_memory_region(struct kvm *kvm, struct kvm_memory_slot *memslot, const struct kvm_userspace_memory_region *mem, enum kvm_mr_change change)
static void kvm_mmu_slot_apply_flags(struct kvm *kvm, struct kvm_memory_slot *new)
void kvm_arch_commit_memory_region(struct kvm *kvm, const struct kvm_userspace_memory_region *mem, const struct kvm_memory_slot *old, const struct kvm_memory_slot *new, enum kvm_mr_change change)
void kvm_arch_flush_shadow_all(struct kvm *kvm)
void kvm_arch_flush_shadow_memslot(struct kvm *kvm, struct kvm_memory_slot *slot)
static inline bool kvm_guest_apic_has_interrupt(struct kvm_vcpu *vcpu)
static inline bool kvm_vcpu_has_events(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_runnable(struct kvm_vcpu *vcpu)
bool kvm_arch_vcpu_in_kernel(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_should_kick(struct kvm_vcpu *vcpu)
int kvm_arch_interrupt_allowed(struct kvm_vcpu *vcpu)
unsigned long kvm_get_linear_rip(struct kvm_vcpu *vcpu)
bool kvm_is_linear_rip(struct kvm_vcpu *vcpu, unsigned long linear_rip)
unsigned long kvm_get_rflags(struct kvm_vcpu *vcpu)
static void __kvm_set_rflags(struct kvm_vcpu *vcpu, unsigned long rflags)
void kvm_set_rflags(struct kvm_vcpu *vcpu, unsigned long rflags)
void kvm_arch_async_page_ready(struct kvm_vcpu *vcpu, struct kvm_async_pf *work)
static inline u32 kvm_async_pf_hash_fn(gfn_t gfn)
static inline u32 kvm_async_pf_next_probe(u32 key)
static void kvm_add_async_pf_gfn(struct kvm_vcpu *vcpu, gfn_t gfn)
static u32 kvm_async_pf_gfn_slot(struct kvm_vcpu *vcpu, gfn_t gfn)
bool kvm_find_async_pf_gfn(struct kvm_vcpu *vcpu, gfn_t gfn)
static void kvm_del_async_pf_gfn(struct kvm_vcpu *vcpu, gfn_t gfn)
static int apf_put_user(struct kvm_vcpu *vcpu, u32 val)
static int apf_get_user(struct kvm_vcpu *vcpu, u32 *val)
void kvm_arch_async_page_not_present(struct kvm_vcpu *vcpu, struct kvm_async_pf *work)
void kvm_arch_async_page_present(struct kvm_vcpu *vcpu, struct kvm_async_pf *work)
bool kvm_arch_can_inject_async_page_present(struct kvm_vcpu *vcpu)
void kvm_arch_start_assignment(struct kvm *kvm)
void kvm_arch_end_assignment(struct kvm *kvm)
bool kvm_arch_has_assigned_device(struct kvm *kvm)
void kvm_arch_register_noncoherent_dma(struct kvm *kvm)
void kvm_arch_unregister_noncoherent_dma(struct kvm *kvm)
bool kvm_arch_has_noncoherent_dma(struct kvm *kvm)
bool kvm_arch_has_irq_bypass(void)
int kvm_arch_irq_bypass_add_producer(struct irq_bypass_consumer *cons, struct irq_bypass_producer *prod)
void kvm_arch_irq_bypass_del_producer(struct irq_bypass_consumer *cons, struct irq_bypass_producer *prod)
int kvm_arch_update_irqfd_routing(struct kvm *kvm, unsigned int host_irq, uint32_t guest_irq, bool set)
bool kvm_vector_hashing_enabled(void)
 230 struct kvm_vcpu *vcpu
  46 struct kvm *kvm
  42 struct x86_emulate_ctxt *ctxt
  21 void
  19 void *val
  18 struct x86_exception *exception
  13 unsigned int bytes
  10 gpa_t gpa
   8 unsigned long addr
   7 unsigned nr
   7 int bytes
   7 gva_t addr
   6 unsigned short port
   6 int size
   6 int seg
   6 int dr
   6 gfn_t gfn
   5 unsigned index
   5 u64 *tsc_timestamp
   5 u64 *data
   5 u32 error_code
   5 u32 access
   5 struct kvm_sregs *sregs
   5 int emulation_type
   4 void *data
   4 struct msr_data *msr_info
   4 struct kvm_regs *regs
   4 struct desc_ptr *dt
   4 int len
   4 gva_t gva
   4 char *buf
   3 unsigned slot
   3 unsigned long val
   3 unsigned long payload
   3 unsigned long arg
   3 unsigned int ioctl
   3 unsigned int count
   3 u64 data
   3 u64 *pdata
   3 u32 msr
   3 struct work_struct *work
   3 struct msr_data *msr
   3 struct kvm_vcpu *v
   3 struct kvm_async_pf *work
   3 struct file *filp
   3 const void *val
   2 void *insn
   2 unsigned reg
   2 unsigned long rflags
   2 unsigned long gva
   2 unsigned long cr3
   2 unsigned long cr2
   2 unsigned int cpu
   2 unsigned emul_flags
   2 ulong val
   2 u64 xcr
   2 u64 tsc
   2 u64 smbase
   2 u64 mask
   2 u64 efer
   2 u32 user_tsc_khz
   2 u32 size
   2 u32 pmc
   2 u32 msr_index
   2 u32 index
   2 struct x86_exception *fault
   2 struct timespec64 *ts
   2 struct notifier_block *nb
   2 struct kvm_xsave *guest_xsave
   2 struct kvm_xcrs *guest_xcrs
   2 struct kvm_vcpu_events *events
   2 struct kvm_segment *var
   2 struct kvm_pit_state2 *ps
   2 struct kvm_pit_state *ps
   2 struct kvm_mp_state *mp_state
   2 struct kvm_mmu *mmu
   2 struct kvm_memory_slot *slot
   2 struct kvm_lapic_state *s
   2 struct kvm_irqchip *chip
   2 struct kvm_fpu *fpu
   2 struct kvm_enable_cap *cap
   2 struct kvm_debugregs *dbgregs
   2 struct irq_bypass_producer *prod
   2 struct irq_bypass_consumer *cons
   2 struct desc_struct *desc
   2 s64 adjustment
   2 int vector
   2 int offset
   2 int n
   2 int insn_len
   2 int id
   2 int cr
   2 int cpu
   2 int *r
   2 int *do_msr
   2 gpa_t addr
   2 enum kvm_mr_change change
   2 const struct read_write_emulator_ops *ops
   2 const struct kvm_userspace_memory_region *mem
   2 bool write
   2 bool system
   1 x86_set_memory_region
   1 void *v
   1 void *rtn
   1 void *priv
   1 void *pd
   1 void *opaque
   1 void *garbage
   1 unsigned long value
   1 unsigned long unused
   1 unsigned long type
   1 unsigned long start
   1 unsigned long npages
   1 unsigned long msw
   1 unsigned long linear_rip
   1 unsigned long flags
   1 unsigned long end
   1 unsigned long cr8
   1 unsigned long cr4
   1 unsigned long cr0
   1 unsigned long clock_type
   1 unsigned long *val
   1 unsigned long *dest
   1 unsigned long *db
   1 unsigned int id
   1 unsigned int host_irq
   1 ulong address
   1 uint64_t scaled_hz
   1 uint64_t base_hz
   1 uint32_t guest_irq
   1 uint32_t divisor
   1 uint32_t dividend
   1 u8 vector
   1 u8 *src
   1 u8 *dest
   1 u64 value
   1 u64 target_tsc
   1 u64 ratio
   1 u64 offset
   1 u64 mcg_cap
   1 u64 ident_addr
   1 u64 host_tsc
   1 u64 curr_cr
   1 u32 val
   1 u32 type
   1 u32 new_val
   1 u32 mask
   1 u32 kvm_nr_mmu_pages
   1 u32 khz
   1 u32 key
   1 u32 dr7
   1 u32 base3
   1 u32 *val
   1 u32 *pmultiplier
   1 u32 *edx
   1 u32 *ecx
   1 u32 *ebx
   1 u32 *eax
   1 u32 *base3
   1 u16 tss_selector
   1 u16 selector
   1 u16 *selector
   1 struct x86_instruction_info *info
   1 struct vm_fault *vmf
   1 struct user_return_notifier *urn
   1 struct timekeeper *tk
   1 struct kvm_x86_mce *mce
   1 struct kvm_translation *tr
   1 struct kvm_tpr_access_ctl *tac
   1 struct kvm_segment *seg
   1 struct kvm_run *kvm_run
   1 struct kvm_reinject_control *control
   1 struct kvm_msrs __user *user_msrs
   1 struct kvm_msrs *msrs
   1 struct kvm_msr_entry *msr
   1 struct kvm_msr_entry *entries
   1 struct kvm_memslots *slots
   1 struct kvm_memory_slot *new
   1 struct kvm_memory_slot *memslot
   1 struct kvm_memory_slot *free
   1 struct kvm_memory_slot *dont
   1 struct kvm_irq_level *irq_event
   1 struct kvm_interrupt *irq
   1 struct kvm_guest_debug *dbg
   1 struct kvm_dirty_log *log
   1 s8 *pshift
   1 s64 offset
   1 s64 kernel_ns
   1 s64 *t
   1 s64 *kernel_ns
   1 s32 ppm
   1 pdptrs_changed
   1 long ext
   1 load_pdptrs
   1 lapic_timer_advance_ns
   1 kvm_x86_ops
   1 kvm_write_tsc
   1 kvm_write_guest_virt_system
   1 kvm_vector_hashing_enabled
   1 kvm_vcpu_reload_apic_access_page
   1 kvm_vcpu_is_reset_bsp
   1 kvm_vcpu_halt
   1 kvm_valid_efer
   1 kvm_tsc_scaling_ratio_frac_bits
   1 kvm_task_switch
   1 kvm_spurious_fault
   1 kvm_skip_emulated_instruction
   1 kvm_set_xcr
   1 kvm_set_shared_msr
   1 kvm_set_rflags
   1 kvm_set_msr_common
   1 kvm_set_msr
   1 kvm_set_dr
   1 kvm_set_cr8
   1 kvm_set_cr4
   1 kvm_set_cr3
   1 kvm_set_cr0
   1 kvm_set_apic_base
   1 kvm_scale_tsc
   1 kvm_require_dr
   1 kvm_require_cpl
   1 kvm_requeue_exception_e
   1 kvm_requeue_exception
   1 kvm_read_l1_tsc
   1 kvm_read_guest_virt
   1 kvm_read_guest_page_mmu
   1 kvm_rdpmc
   1 kvm_queue_exception_e
   1 kvm_queue_exception
   1 kvm_no_apic_vcpu
   1 kvm_mce_cap_supported
   1 kvm_max_tsc_scaling_ratio
   1 kvm_max_guest_tsc_khz
   1 kvm_lmsw
   1 kvm_is_linear_rip
   1 kvm_inject_realmode_interrupt
   1 kvm_inject_page_fault
   1 kvm_inject_nmi
   1 kvm_has_tsc_control
   1 kvm_get_rflags
   1 kvm_get_msr_common
   1 kvm_get_msr
   1 kvm_get_linear_rip
   1 kvm_get_dr
   1 kvm_get_cs_db_l_bits
   1 kvm_get_cr8
   1 kvm_get_arch_capabilities
   1 kvm_get_apic_mode
   1 kvm_get_apic_base
   1 kvm_fast_pio
   1 kvm_enable_efer_bits
   1 kvm_emulate_wbinvd
   1 kvm_emulate_instruction_from_buffer
   1 kvm_emulate_instruction
   1 kvm_emulate_hypercall
   1 kvm_emulate_halt
   1 kvm_deliver_exception_payload
   1 kvm_define_shared_msr
   1 kvm_default_tsc_scaling_ratio
   1 kvm_complete_insn_gp
   1 kvm_arch_unregister_noncoherent_dma
   1 kvm_arch_start_assignment
   1 kvm_arch_register_noncoherent_dma
   1 kvm_arch_has_noncoherent_dma
   1 kvm_arch_has_assigned_device
   1 kvm_arch_end_assignment
   1 int required_cpl
   1 int reason
   1 int mode
   1 int irq
   1 int inc_eip
   1 int in
   1 int idt_index
   1 int err
   1 int apicid
   1 int *mode
   1 int *l
   1 int *db
   1 handle_ud
   1 gva_t cr2
   1 gpa_t wall_clock
   1 gpa_t paddr
   1 gpa_t *gpa
   1 gfn_t ngfn
   1 enum x86_intercept_stage stage
   1 enable_vmware_backdoor
   1 const void *v
   1 const void *old
   1 const void *new
   1 const struct kvm_memory_slot *old
   1 const struct kvm_memory_slot *new
   1 bool write_fault_to_shadow_pgtable
   1 bool set
   1 bool scale
   1 bool req_int_win
   1 bool reinject
   1 bool masked
   1 bool line_status
   1 bool invalidate_gpa
   1 bool init_event
   1 bool in
   1 bool host
   1 bool has_payload
   1 bool has_error_code
   1 bool has_error
   1 bool check_limit
   1 bool blockable
   1 __x86_set_memory_region
   1 __kvm_request_immediate_exit
