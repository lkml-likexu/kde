
\n
static unsigned long ioapic_read_indirect(struct kvm_ioapic *ioapic, unsigned long addr, unsigned long length)
static void rtc_irq_eoi_tracking_reset(struct kvm_ioapic *ioapic)
static void rtc_status_pending_eoi_check_valid(struct kvm_ioapic *ioapic)
static void __rtc_irq_eoi_tracking_restore_one(struct kvm_vcpu *vcpu)
void kvm_rtc_eoi_tracking_restore_one(struct kvm_vcpu *vcpu)
static void kvm_rtc_eoi_tracking_restore_all(struct kvm_ioapic *ioapic)
static void rtc_irq_eoi(struct kvm_ioapic *ioapic, struct kvm_vcpu *vcpu)
static bool rtc_irq_check_coalesced(struct kvm_ioapic *ioapic)
static int ioapic_set_irq(struct kvm_ioapic *ioapic, unsigned int irq, int irq_level, bool line_status)
static void kvm_ioapic_inject_all(struct kvm_ioapic *ioapic, unsigned long irr)
void kvm_ioapic_scan_entry(struct kvm_vcpu *vcpu, ulong *ioapic_handled_vectors)
void kvm_arch_post_irq_ack_notifier_list_update(struct kvm *kvm)
static void ioapic_write_indirect(struct kvm_ioapic *ioapic, u32 val)
static int ioapic_service(struct kvm_ioapic *ioapic, int irq, bool line_status)
int kvm_ioapic_set_irq(struct kvm_ioapic *ioapic, int irq, int irq_source_id, int level, bool line_status)
void kvm_ioapic_clear_all(struct kvm_ioapic *ioapic, int irq_source_id)
static void kvm_ioapic_eoi_inject_work(struct work_struct *work)
static void __kvm_ioapic_update_eoi(struct kvm_vcpu *vcpu, struct kvm_ioapic *ioapic, int vector, int trigger_mode)
void kvm_ioapic_update_eoi(struct kvm_vcpu *vcpu, int vector, int trigger_mode)
static inline struct kvm_ioapic *to_ioapic(struct kvm_io_device *dev)
static inline int ioapic_in_range(struct kvm_ioapic *ioapic, gpa_t addr)
static int ioapic_mmio_read(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t addr, int len, void *val)
static int ioapic_mmio_write(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t addr, int len, const void *val)
static void kvm_ioapic_reset(struct kvm_ioapic *ioapic)
int kvm_ioapic_init(struct kvm *kvm)
void kvm_ioapic_destroy(struct kvm *kvm)
void kvm_get_ioapic(struct kvm *kvm, struct kvm_ioapic_state *state)
void kvm_set_ioapic(struct kvm *kvm, struct kvm_ioapic_state *state)
\n
     15 struct kvm_ioapic *ioapic
      8 struct kvm_vcpu *vcpu
      5 struct kvm *kvm
      3 gpa_t addr
      3 bool line_status
      2 struct kvm_io_device *this
      2 struct kvm_ioapic_state *state
      2 int vector
      2 int trigger_mode
      2 int len
      2 int irq_source_id
      2 int irq
      1 void *val
      1 unsigned long length
      1 unsigned long irr
      1 unsigned long addr
      1 unsigned int irq
      1 ulong *ioapic_handled_vectors
      1 u32 val
      1 struct work_struct *work
      1 struct kvm_io_device *dev
      1 int level
      1 int irq_level
      1 const void *val
