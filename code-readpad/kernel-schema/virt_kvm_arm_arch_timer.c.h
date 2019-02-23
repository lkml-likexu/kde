
\n
u64 kvm_phys_timer_read(void)
static inline bool userspace_irqchip(struct kvm *kvm)
static void soft_timer_start(struct hrtimer *hrt, u64 ns)
static void soft_timer_cancel(struct hrtimer *hrt)
static irqreturn_t kvm_arch_timer_handler(int irq, void *dev_id)
static u64 kvm_timer_compute_delta(struct arch_timer_context *timer_ctx)
static bool kvm_timer_irq_can_fire(struct arch_timer_context *timer_ctx)
static u64 kvm_timer_earliest_exp(struct kvm_vcpu *vcpu)
static enum hrtimer_restart kvm_bg_timer_expire(struct hrtimer *hrt)
static enum hrtimer_restart kvm_phys_timer_expire(struct hrtimer *hrt)
static bool kvm_timer_should_fire(struct arch_timer_context *timer_ctx)
bool kvm_timer_is_pending(struct kvm_vcpu *vcpu)
void kvm_timer_update_run(struct kvm_vcpu *vcpu)
static void kvm_timer_update_irq(struct kvm_vcpu *vcpu, bool new_level, struct arch_timer_context *timer_ctx)
static void phys_timer_emulate(struct kvm_vcpu *vcpu)
static void kvm_timer_update_state(struct kvm_vcpu *vcpu)
static void vtimer_save_state(struct kvm_vcpu *vcpu)
void kvm_timer_schedule(struct kvm_vcpu *vcpu)
static void vtimer_restore_state(struct kvm_vcpu *vcpu)
void kvm_timer_unschedule(struct kvm_vcpu *vcpu)
static void set_cntvoff(u64 cntvoff)
static inline void set_vtimer_irq_phys_active(struct kvm_vcpu *vcpu, bool active)
static void kvm_timer_vcpu_load_gic(struct kvm_vcpu *vcpu)
static void kvm_timer_vcpu_load_nogic(struct kvm_vcpu *vcpu)
void kvm_timer_vcpu_load(struct kvm_vcpu *vcpu)
bool kvm_timer_should_notify_user(struct kvm_vcpu *vcpu)
void kvm_timer_vcpu_put(struct kvm_vcpu *vcpu)
static void unmask_vtimer_irq_user(struct kvm_vcpu *vcpu)
void kvm_timer_sync_hwstate(struct kvm_vcpu *vcpu)
int kvm_timer_vcpu_reset(struct kvm_vcpu *vcpu)
static void update_vtimer_cntvoff(struct kvm_vcpu *vcpu, u64 cntvoff)
void kvm_timer_vcpu_init(struct kvm_vcpu *vcpu)
static void kvm_timer_init_interrupt(void *info)
int kvm_arm_timer_set_reg(struct kvm_vcpu *vcpu, u64 regid, u64 value)
static u64 read_timer_ctl(struct arch_timer_context *timer)
u64 kvm_arm_timer_get_reg(struct kvm_vcpu *vcpu, u64 regid)
static int kvm_timer_starting_cpu(unsigned int cpu)
static int kvm_timer_dying_cpu(unsigned int cpu)
int kvm_timer_hyp_init(bool has_gic)
void kvm_timer_vcpu_terminate(struct kvm_vcpu *vcpu)
static bool timer_irqs_are_valid(struct kvm_vcpu *vcpu)
bool kvm_arch_timer_get_input_level(int vintid)
int kvm_timer_enable(struct kvm_vcpu *vcpu)
void kvm_timer_init_vhe(void)
static void set_timer_irqs(struct kvm *kvm, int vtimer_irq, int ptimer_irq)
int kvm_arm_timer_set_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
int kvm_arm_timer_get_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
int kvm_arm_timer_has_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
\n
     29 struct kvm_vcpu *vcpu
      4 struct hrtimer *hrt
      4 struct arch_timer_context *timer_ctx
      3 struct kvm_device_attr *attr
      2 void
      2 unsigned int cpu
      2 u64 regid
      2 u64 cntvoff
      2 struct kvm *kvm
      1 void *info
      1 void *dev_id
      1 u64 value
      1 u64 ns
      1 struct arch_timer_context *timer
      1 int vtimer_irq
      1 int vintid
      1 int ptimer_irq
      1 int irq
      1 bool new_level
      1 bool has_gic
      1 bool active
