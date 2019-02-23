
\n
static int sca_ext_call_pending(struct kvm_vcpu *vcpu, int *src_id)
static int sca_inject_ext_call(struct kvm_vcpu *vcpu, int src_id)
static void sca_clear_ext_call(struct kvm_vcpu *vcpu)
int psw_extint_disabled(struct kvm_vcpu *vcpu)
static int psw_ioint_disabled(struct kvm_vcpu *vcpu)
static int psw_mchk_disabled(struct kvm_vcpu *vcpu)
static int psw_interrupts_disabled(struct kvm_vcpu *vcpu)
static int ckc_interrupts_enabled(struct kvm_vcpu *vcpu)
static int ckc_irq_pending(struct kvm_vcpu *vcpu)
static int cpu_timer_interrupts_enabled(struct kvm_vcpu *vcpu)
static int cpu_timer_irq_pending(struct kvm_vcpu *vcpu)
static uint64_t isc_to_isc_bits(int isc)
static inline u32 isc_to_int_word(u8 isc)
static inline u8 int_word_to_isc(u32 int_word)
static inline void kvm_s390_gisa_set_ipm_gisc(struct kvm_s390_gisa *gisa, u32 gisc)
static inline u8 kvm_s390_gisa_get_ipm(struct kvm_s390_gisa *gisa)
static inline void kvm_s390_gisa_clear_ipm_gisc(struct kvm_s390_gisa *gisa, u32 gisc)
static inline int kvm_s390_gisa_tac_ipm_gisc(struct kvm_s390_gisa *gisa, u32 gisc)
static inline unsigned long pending_irqs_no_gisa(struct kvm_vcpu *vcpu)
static inline unsigned long pending_irqs(struct kvm_vcpu *vcpu)
static inline int isc_to_irq_type(unsigned long isc)
static inline int irq_type_to_isc(unsigned long irq_type)
static unsigned long disable_iscs(struct kvm_vcpu *vcpu, unsigned long active_mask)
static unsigned long deliverable_irqs(struct kvm_vcpu *vcpu)
static void __set_cpu_idle(struct kvm_vcpu *vcpu)
static void __unset_cpu_idle(struct kvm_vcpu *vcpu)
static void __reset_intercept_indicators(struct kvm_vcpu *vcpu)
static void set_intercept_indicators_io(struct kvm_vcpu *vcpu)
static void set_intercept_indicators_ext(struct kvm_vcpu *vcpu)
static void set_intercept_indicators_mchk(struct kvm_vcpu *vcpu)
static void set_intercept_indicators_stop(struct kvm_vcpu *vcpu)
static void set_intercept_indicators(struct kvm_vcpu *vcpu)
static int __must_check __deliver_cpu_timer(struct kvm_vcpu *vcpu)
static int __must_check __deliver_ckc(struct kvm_vcpu *vcpu)
static int __must_check __deliver_pfault_init(struct kvm_vcpu *vcpu)
static int __write_machine_check(struct kvm_vcpu *vcpu, struct kvm_s390_mchk_info *mchk)
static int __must_check __deliver_machine_check(struct kvm_vcpu *vcpu)
static int __must_check __deliver_restart(struct kvm_vcpu *vcpu)
static int __must_check __deliver_set_prefix(struct kvm_vcpu *vcpu)
static int __must_check __deliver_emergency_signal(struct kvm_vcpu *vcpu)
static int __must_check __deliver_external_call(struct kvm_vcpu *vcpu)
static int __must_check __deliver_prog(struct kvm_vcpu *vcpu)
static int __must_check __deliver_service(struct kvm_vcpu *vcpu)
static int __must_check __deliver_pfault_done(struct kvm_vcpu *vcpu)
static int __must_check __deliver_virtio(struct kvm_vcpu *vcpu)
static int __do_deliver_io(struct kvm_vcpu *vcpu, struct kvm_s390_io_info *io)
static int __must_check __deliver_io(struct kvm_vcpu *vcpu, unsigned long irq_type)
int kvm_s390_ext_call_pending(struct kvm_vcpu *vcpu)
int kvm_s390_vcpu_has_irq(struct kvm_vcpu *vcpu, int exclude_stop)
int kvm_cpu_has_pending_timer(struct kvm_vcpu *vcpu)
static u64 __calculate_sltime(struct kvm_vcpu *vcpu)
int kvm_s390_handle_wait(struct kvm_vcpu *vcpu)
void kvm_s390_vcpu_wakeup(struct kvm_vcpu *vcpu)
enum hrtimer_restart kvm_s390_idle_wakeup(struct hrtimer *timer)
void kvm_s390_clear_local_irqs(struct kvm_vcpu *vcpu)
int __must_check kvm_s390_deliver_pending_interrupts(struct kvm_vcpu *vcpu)
static int __inject_prog(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
static int __inject_pfault_init(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
static int __inject_extcall(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
static int __inject_set_prefix(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
define KVM_S390_STOP_SUPP_FLAGS (KVM_S390_STOP_FLAG_STORE_STATUS)
static int __inject_sigp_stop(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
static int __inject_sigp_restart(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
static int __inject_sigp_emergency(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
static int __inject_mchk(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
static int __inject_ckc(struct kvm_vcpu *vcpu)
static int __inject_cpu_timer(struct kvm_vcpu *vcpu)
static struct kvm_s390_interrupt_info *get_io_int(struct kvm *kvm, int isc, u32 schid)
static struct kvm_s390_interrupt_info *get_top_io_int(struct kvm *kvm, u64 isc_mask, u32 schid)
static int get_top_gisa_isc(struct kvm *kvm, u64 isc_mask, u32 schid)
struct kvm_s390_interrupt_info *kvm_s390_get_io_int(struct kvm *kvm, u64 isc_mask, u32 schid)
static int __inject_service(struct kvm *kvm, struct kvm_s390_interrupt_info *inti)
static int __inject_virtio(struct kvm *kvm, struct kvm_s390_interrupt_info *inti)
static int __inject_pfault_done(struct kvm *kvm, struct kvm_s390_interrupt_info *inti)
define CR_PENDING_SUBCLASS 28 static int __inject_float_mchk(struct kvm *kvm, struct kvm_s390_interrupt_info *inti)
static int __inject_io(struct kvm *kvm, struct kvm_s390_interrupt_info *inti)
static void __floating_irq_kick(struct kvm *kvm, u64 type)
static int __inject_vm(struct kvm *kvm, struct kvm_s390_interrupt_info *inti)
int kvm_s390_inject_vm(struct kvm *kvm, struct kvm_s390_interrupt *s390int)
int kvm_s390_reinject_io_int(struct kvm *kvm, struct kvm_s390_interrupt_info *inti)
int s390int_to_s390irq(struct kvm_s390_interrupt *s390int, struct kvm_s390_irq *irq)
int kvm_s390_is_stop_irq_pending(struct kvm_vcpu *vcpu)
void kvm_s390_clear_stop_irq(struct kvm_vcpu *vcpu)
static int do_inject_vcpu(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
int kvm_s390_inject_vcpu(struct kvm_vcpu *vcpu, struct kvm_s390_irq *irq)
static inline void clear_irq_list(struct list_head *_list)
static void inti_to_irq(struct kvm_s390_interrupt_info *inti, struct kvm_s390_irq *irq)
void kvm_s390_clear_float_irqs(struct kvm *kvm)
static int get_all_floating_irqs(struct kvm *kvm, u8 __user *usrbuf, u64 len)
static int flic_ais_mode_get_all(struct kvm *kvm, struct kvm_device_attr *attr)
static int flic_get_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static inline int copy_irq_from_user(struct kvm_s390_interrupt_info *inti, u64 addr)
static int enqueue_floating_irq(struct kvm_device *dev, struct kvm_device_attr *attr)
static struct s390_io_adapter *get_io_adapter(struct kvm *kvm, unsigned int id)
static int register_io_adapter(struct kvm_device *dev, struct kvm_device_attr *attr)
int kvm_s390_mask_adapter(struct kvm *kvm, unsigned int id, bool masked)
static int kvm_s390_adapter_map(struct kvm *kvm, unsigned int id, __u64 addr)
static int kvm_s390_adapter_unmap(struct kvm *kvm, unsigned int id, __u64 addr)
void kvm_s390_destroy_adapters(struct kvm *kvm)
static int modify_io_adapter(struct kvm_device *dev, struct kvm_device_attr *attr)
static int modify_ais_mode(struct kvm *kvm, struct kvm_device_attr *attr)
static int kvm_s390_inject_airq(struct kvm *kvm, struct s390_io_adapter *adapter)
static int flic_inject_airq(struct kvm *kvm, struct kvm_device_attr *attr)
static int flic_ais_mode_set_all(struct kvm *kvm, struct kvm_device_attr *attr)
static int flic_set_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static int flic_has_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static int flic_create(struct kvm_device *dev, u32 type)
static void flic_destroy(struct kvm_device *dev)
static unsigned long get_ind_bit(__u64 addr, unsigned long bit_nr, bool swap)
static struct s390_map_info *get_map_info(struct s390_io_adapter *adapter, u64 addr)
static int adapter_indicators_set(struct kvm *kvm, struct s390_io_adapter *adapter, struct kvm_s390_adapter_int *adapter_int)
static int set_adapter_int(struct kvm_kernel_irq_routing_entry *e, struct kvm *kvm, int irq_source_id, int level, bool line_status)
void kvm_s390_reinject_machine_check(struct kvm_vcpu *vcpu, struct mcck_volatile_info *mcck_info)
int kvm_set_routing_entry(struct kvm *kvm, struct kvm_kernel_irq_routing_entry *e, const struct kvm_irq_routing_entry *ue)
int kvm_set_msi(struct kvm_kernel_irq_routing_entry *e, struct kvm *kvm, int irq_source_id, int level, bool line_status)
int kvm_s390_set_irq_state(struct kvm_vcpu *vcpu, void __user *irqstate, int len)
static void store_local_irq(struct kvm_s390_local_interrupt *li, struct kvm_s390_irq *irq, unsigned long irq_type)
int kvm_s390_get_irq_state(struct kvm_vcpu *vcpu, __u8 __user *buf, int len)
void kvm_s390_gisa_clear(struct kvm *kvm)
void kvm_s390_gisa_init(struct kvm *kvm)
void kvm_s390_gisa_destroy(struct kvm *kvm)
\n
     63 struct kvm_vcpu *vcpu
     32 struct kvm *kvm
     13 struct kvm_s390_irq *irq
     10 struct kvm_device_attr *attr
      9 struct kvm_s390_interrupt_info *inti
      8 struct kvm_device *dev
      4 unsigned int id
      4 u32 schid
      4 struct kvm_s390_gisa *gisa
      3 unsigned long irq_type
      3 u64 isc_mask
      3 __u64 addr
      3 u32 gisc
      3 struct s390_io_adapter *adapter
      3 struct kvm_kernel_irq_routing_entry *e
      2 u64 addr
      2 struct kvm_s390_interrupt *s390int
      2 int level
      2 int len
      2 int isc
      2 int irq_source_id
      2 bool line_status
      1 void __user *irqstate
      1 unsigned long isc
      1 unsigned long bit_nr
      1 unsigned long active_mask
      1 u8 __user *usrbuf
      1 __u8 __user *buf
      1 u8 isc
      1 u64 type
      1 u64 len
      1 u32 type
      1 u32 int_word
      1 struct mcck_volatile_info *mcck_info
      1 struct list_head *_list
      1 struct kvm_s390_mchk_info *mchk
      1 struct kvm_s390_local_interrupt *li
      1 struct kvm_s390_io_info *io
      1 struct kvm_s390_adapter_int *adapter_int
      1 struct hrtimer *timer
      1 KVM_S390_STOP_FLAG_STORE_STATUS
      1 int src_id
      1 int *src_id
      1 int exclude_stop
      1 const struct kvm_irq_routing_entry *ue
      1 bool swap
      1 bool masked
