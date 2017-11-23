
static void pit_set_gate(struct kvm_pit *pit, int channel, u32 val)
static int pit_get_gate(struct kvm_pit *pit, int channel)
static s64 __kpit_elapsed(struct kvm_pit *pit)
static s64 kpit_elapsed(struct kvm_pit *pit, struct kvm_kpit_channel_state *c, int channel)
static int pit_get_count(struct kvm_pit *pit, int channel)
static int pit_get_out(struct kvm_pit *pit, int channel)
static void pit_latch_count(struct kvm_pit *pit, int channel)
static void pit_latch_status(struct kvm_pit *pit, int channel)
static inline struct kvm_pit *pit_state_to_pit(struct kvm_kpit_state *ps)
static void kvm_pit_ack_irq(struct kvm_irq_ack_notifier *kian)
void __kvm_migrate_pit_timer(struct kvm_vcpu *vcpu)
static void destroy_pit_timer(struct kvm_pit *pit)
static void pit_do_work(struct kthread_work *work)
static enum hrtimer_restart pit_timer_fn(struct hrtimer *data)
static inline void kvm_pit_reset_reinject(struct kvm_pit *pit)
void kvm_pit_set_reinject(struct kvm_pit *pit, bool reinject)
static void create_pit_timer(struct kvm_pit *pit, u32 val, int is_period)
static void pit_load_count(struct kvm_pit *pit, int channel, u32 val)
void kvm_pit_load_count(struct kvm_pit *pit, int channel, u32 val, int hpet_legacy_start)
static inline struct kvm_pit *dev_to_pit(struct kvm_io_device *dev)
static inline struct kvm_pit *speaker_to_pit(struct kvm_io_device *dev)
static inline int pit_in_range(gpa_t addr)
static int pit_ioport_write(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t addr, int len, const void *data)
static int pit_ioport_read(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t addr, int len, void *data)
static int speaker_ioport_write(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t addr, int len, const void *data)
static int speaker_ioport_read(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t addr, int len, void *data)
static void kvm_pit_reset(struct kvm_pit *pit)
static void pit_mask_notifer(struct kvm_irq_mask_notifier *kimn, bool mask)
struct kvm_pit *kvm_create_pit(struct kvm *kvm, u32 flags)
void kvm_free_pit(struct kvm *kvm)
  15 struct kvm_pit *pit
   9 int channel
   5 struct kvm_vcpu *vcpu
   5 gpa_t addr
   4 u32 val
   4 struct kvm_io_device *this
   4 int len
   2 void *data
   2 struct kvm_io_device *dev
   2 struct kvm *kvm
   2 const void *data
   1 u32 flags
   1 struct kvm_kpit_state *ps
   1 struct kvm_kpit_channel_state *c
   1 struct kvm_irq_mask_notifier *kimn
   1 struct kvm_irq_ack_notifier *kian
   1 struct kthread_work *work
   1 struct hrtimer *data
   1 int is_period
   1 int hpet_legacy_start
   1 bool reinject
   1 bool mask
