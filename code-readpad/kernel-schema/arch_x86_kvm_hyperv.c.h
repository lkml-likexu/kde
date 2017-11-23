
EXPORT_SYMBOL_GPL(kvm_hv_assist_page_enabled);
EXPORT_SYMBOL_GPL(kvm_hv_get_assist_page);
static inline u64 synic_read_sint(struct kvm_vcpu_hv_synic *synic, int sint)
static inline int synic_get_sint_vector(u64 sint_value)
static bool synic_has_vector_connected(struct kvm_vcpu_hv_synic *synic, int vector)
static bool synic_has_vector_auto_eoi(struct kvm_vcpu_hv_synic *synic, int vector)
static void synic_update_vector(struct kvm_vcpu_hv_synic *synic, int vector)
static int synic_set_sint(struct kvm_vcpu_hv_synic *synic, int sint, u64 data, bool host)
static struct kvm_vcpu *get_vcpu_by_vpidx(struct kvm *kvm, u32 vpidx)
static struct kvm_vcpu_hv_synic *synic_get(struct kvm *kvm, u32 vpidx)
static void synic_clear_sint_msg_pending(struct kvm_vcpu_hv_synic *synic, u32 sint)
static void kvm_hv_notify_acked_sint(struct kvm_vcpu *vcpu, u32 sint)
static void synic_exit(struct kvm_vcpu_hv_synic *synic, u32 msr)
static int synic_set_msr(struct kvm_vcpu_hv_synic *synic, u32 msr, u64 data, bool host)
static int synic_get_msr(struct kvm_vcpu_hv_synic *synic, u32 msr, u64 *pdata, bool host)
static int synic_set_irq(struct kvm_vcpu_hv_synic *synic, u32 sint)
int kvm_hv_synic_set_irq(struct kvm *kvm, u32 vpidx, u32 sint)
void kvm_hv_synic_send_eoi(struct kvm_vcpu *vcpu, int vector)
static int kvm_hv_set_sint_gsi(struct kvm *kvm, u32 vpidx, u32 sint, int gsi)
void kvm_hv_irq_routing_update(struct kvm *kvm)
static void synic_init(struct kvm_vcpu_hv_synic *synic)
static u64 get_time_ref_counter(struct kvm *kvm)
static void stimer_mark_pending(struct kvm_vcpu_hv_stimer *stimer, bool vcpu_kick)
static void stimer_cleanup(struct kvm_vcpu_hv_stimer *stimer)
static enum hrtimer_restart stimer_timer_callback(struct hrtimer *timer)
static int stimer_start(struct kvm_vcpu_hv_stimer *stimer)
static int stimer_set_config(struct kvm_vcpu_hv_stimer *stimer, u64 config, bool host)
static int stimer_set_count(struct kvm_vcpu_hv_stimer *stimer, u64 count, bool host)
static int stimer_get_config(struct kvm_vcpu_hv_stimer *stimer, u64 *pconfig)
static int stimer_get_count(struct kvm_vcpu_hv_stimer *stimer, u64 *pcount)
static int synic_deliver_msg(struct kvm_vcpu_hv_synic *synic, u32 sint, struct hv_message *src_msg)
static int stimer_send_msg(struct kvm_vcpu_hv_stimer *stimer)
static void stimer_expiration(struct kvm_vcpu_hv_stimer *stimer)
void kvm_hv_process_stimers(struct kvm_vcpu *vcpu)
void kvm_hv_vcpu_uninit(struct kvm_vcpu *vcpu)
bool kvm_hv_assist_page_enabled(struct kvm_vcpu *vcpu)
bool kvm_hv_get_assist_page(struct kvm_vcpu *vcpu, struct hv_vp_assist_page *assist_page)
static void stimer_prepare_msg(struct kvm_vcpu_hv_stimer *stimer)
static void stimer_init(struct kvm_vcpu_hv_stimer *stimer, int timer_index)
void kvm_hv_vcpu_init(struct kvm_vcpu *vcpu)
void kvm_hv_vcpu_postcreate(struct kvm_vcpu *vcpu)
int kvm_hv_activate_synic(struct kvm_vcpu *vcpu, bool dont_zero_synic_pages)
static bool kvm_hv_msr_partition_wide(u32 msr)
static int kvm_hv_msr_get_crash_data(struct kvm_vcpu *vcpu, u32 index, u64 *pdata)
static int kvm_hv_msr_get_crash_ctl(struct kvm_vcpu *vcpu, u64 *pdata)
static int kvm_hv_msr_set_crash_ctl(struct kvm_vcpu *vcpu, u64 data, bool host)
static int kvm_hv_msr_set_crash_data(struct kvm_vcpu *vcpu, u32 index, u64 data)
static bool compute_tsc_page_parameters(struct pvclock_vcpu_time_info *hv_clock, HV_REFERENCE_TSC_PAGE *tsc_ref)
void kvm_hv_setup_tsc_page(struct kvm *kvm, struct pvclock_vcpu_time_info *hv_clock)
static int kvm_hv_set_msr_pw(struct kvm_vcpu *vcpu, u32 msr, u64 data, bool host)
static u64 current_task_runtime_100ns(void)
static int kvm_hv_set_msr(struct kvm_vcpu *vcpu, u32 msr, u64 data, bool host)
static int kvm_hv_get_msr_pw(struct kvm_vcpu *vcpu, u32 msr, u64 *pdata)
static int kvm_hv_get_msr(struct kvm_vcpu *vcpu, u32 msr, u64 *pdata, bool host)
int kvm_hv_set_msr_common(struct kvm_vcpu *vcpu, u32 msr, u64 data, bool host)
int kvm_hv_get_msr_common(struct kvm_vcpu *vcpu, u32 msr, u64 *pdata, bool host)
static __always_inline unsigned long *sparse_set_to_vcpu_mask(struct kvm *kvm, u64 *sparse_banks, u64 valid_bank_mask, u64 *vp_bitmap, unsigned long *vcpu_bitmap)
static u64 kvm_hv_flush_tlb(struct kvm_vcpu *current_vcpu, u64 ingpa, u16 rep_cnt, bool ex)
static void kvm_send_ipi_to_many(struct kvm *kvm, u32 vector, unsigned long *vcpu_bitmap)
static u64 kvm_hv_send_ipi(struct kvm_vcpu *current_vcpu, u64 ingpa, u64 outgpa, bool ex, bool fast)
bool kvm_hv_hypercall_enabled(struct kvm *kvm)
static void kvm_hv_hypercall_set_result(struct kvm_vcpu *vcpu, u64 result)
static int kvm_hv_hypercall_complete(struct kvm_vcpu *vcpu, u64 result)
static int kvm_hv_hypercall_complete_userspace(struct kvm_vcpu *vcpu)
static u16 kvm_hvcall_signal_event(struct kvm_vcpu *vcpu, bool fast, u64 param)
int kvm_hv_hypercall(struct kvm_vcpu *vcpu)
void kvm_hv_init_vm(struct kvm *kvm)
void kvm_hv_destroy_vm(struct kvm *kvm)
static int kvm_hv_eventfd_assign(struct kvm *kvm, u32 conn_id, int fd)
static int kvm_hv_eventfd_deassign(struct kvm *kvm, u32 conn_id)
int kvm_vm_ioctl_hv_eventfd(struct kvm *kvm, struct kvm_hyperv_eventfd *args)
  24 struct kvm_vcpu *vcpu
  15 struct kvm *kvm
  12 struct kvm_vcpu_hv_synic *synic
  11 struct kvm_vcpu_hv_stimer *stimer
  11 bool host
  10 u32 msr
   7 u64 data
   6 u64 *pdata
   6 u32 sint
   4 u32 vpidx
   4 int vector
   2 unsigned long *vcpu_bitmap
   2 u64 result
   2 u64 ingpa
   2 u32 index
   2 u32 conn_id
   2 struct pvclock_vcpu_time_info *hv_clock
   2 struct kvm_vcpu *current_vcpu
   2 int sint
   2 bool fast
   2 bool ex
   1 void
   1 u64 valid_bank_mask
   1 u64 sint_value
   1 u64 param
   1 u64 outgpa
   1 u64 count
   1 u64 config
   1 u64 *vp_bitmap
   1 u64 *sparse_banks
   1 u64 *pcount
   1 u64 *pconfig
   1 u32 vector
   1 u16 rep_cnt
   1 struct kvm_hyperv_eventfd *args
   1 struct hv_vp_assist_page *assist_page
   1 struct hv_message *src_msg
   1 struct hrtimer *timer
   1 kvm_hv_get_assist_page
   1 kvm_hv_assist_page_enabled
   1 int timer_index
   1 int gsi
   1 int fd
   1 bool vcpu_kick
   1 bool dont_zero_synic_pages
   1 HV_REFERENCE_TSC_PAGE *tsc_ref
