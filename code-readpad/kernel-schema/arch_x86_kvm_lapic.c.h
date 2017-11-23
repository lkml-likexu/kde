
EXPORT_SYMBOL_GPL(__kvm_apic_update_irr);
EXPORT_SYMBOL_GPL(kvm_apic_update_irr);
EXPORT_SYMBOL_GPL(kvm_lapic_find_highest_irr);
EXPORT_SYMBOL_GPL(kvm_apic_update_ppr);
EXPORT_SYMBOL_GPL(kvm_apic_match_dest);
EXPORT_SYMBOL_GPL(kvm_apic_set_eoi_accelerated);
EXPORT_SYMBOL_GPL(kvm_lapic_reg_read);
EXPORT_SYMBOL_GPL(kvm_lapic_hv_timer_in_use);
EXPORT_SYMBOL_GPL(kvm_lapic_expired_hv_timer);
EXPORT_SYMBOL_GPL(kvm_lapic_switch_to_hv_timer);
EXPORT_SYMBOL_GPL(kvm_lapic_switch_to_sw_timer);
EXPORT_SYMBOL_GPL(kvm_lapic_reg_write);
EXPORT_SYMBOL_GPL(kvm_lapic_set_eoi);
EXPORT_SYMBOL_GPL(kvm_apic_write_nodecode);
static inline int apic_test_vector(int vec, void *bitmap)
bool kvm_apic_pending_eoi(struct kvm_vcpu *vcpu, int vector)
static inline void apic_clear_vector(int vec, void *bitmap)
static inline int __apic_test_and_set_vector(int vec, void *bitmap)
static inline int __apic_test_and_clear_vector(int vec, void *bitmap)
static inline int apic_enabled(struct kvm_lapic *apic)
static inline u8 kvm_xapic_id(struct kvm_lapic *apic)
static inline u32 kvm_x2apic_id(struct kvm_lapic *apic)
static void kvm_apic_map_free(struct rcu_head *rcu)
static void recalculate_apic_map(struct kvm *kvm)
static inline void apic_set_spiv(struct kvm_lapic *apic, u32 val)
static inline void kvm_apic_set_xapic_id(struct kvm_lapic *apic, u8 id)
static inline void kvm_apic_set_ldr(struct kvm_lapic *apic, u32 id)
static inline u32 kvm_apic_calc_x2apic_ldr(u32 id)
static inline void kvm_apic_set_x2apic_id(struct kvm_lapic *apic, u32 id)
static inline int apic_lvt_enabled(struct kvm_lapic *apic, int lvt_type)
static inline int apic_lvt_vector(struct kvm_lapic *apic, int lvt_type)
static inline int apic_lvtt_oneshot(struct kvm_lapic *apic)
static inline int apic_lvtt_period(struct kvm_lapic *apic)
static inline int apic_lvtt_tscdeadline(struct kvm_lapic *apic)
static inline int apic_lvt_nmi_mode(u32 lvt_val)
void kvm_apic_set_version(struct kvm_vcpu *vcpu)
static int find_highest_vector(void *bitmap)
static u8 count_vectors(void *bitmap)
bool __kvm_apic_update_irr(u32 *pir, void *regs, int *max_irr)
bool kvm_apic_update_irr(struct kvm_vcpu *vcpu, u32 *pir, int *max_irr)
static inline int apic_search_irr(struct kvm_lapic *apic)
static inline int apic_find_highest_irr(struct kvm_lapic *apic)
static inline void apic_clear_irr(int vec, struct kvm_lapic *apic)
static inline void apic_set_isr(int vec, struct kvm_lapic *apic)
static inline int apic_find_highest_isr(struct kvm_lapic *apic)
static inline void apic_clear_isr(int vec, struct kvm_lapic *apic)
int kvm_lapic_find_highest_irr(struct kvm_vcpu *vcpu)
int kvm_apic_set_irq(struct kvm_vcpu *vcpu, struct kvm_lapic_irq *irq, struct dest_map *dest_map)
int kvm_pv_send_ipi(struct kvm *kvm, unsigned long ipi_bitmap_low, unsigned long ipi_bitmap_high, u32 min, unsigned long icr, int op_64_bit)
static int pv_eoi_put_user(struct kvm_vcpu *vcpu, u8 val)
static int pv_eoi_get_user(struct kvm_vcpu *vcpu, u8 *val)
static inline bool pv_eoi_enabled(struct kvm_vcpu *vcpu)
static bool pv_eoi_get_pending(struct kvm_vcpu *vcpu)
static void pv_eoi_set_pending(struct kvm_vcpu *vcpu)
static void pv_eoi_clr_pending(struct kvm_vcpu *vcpu)
static int apic_has_interrupt_for_ppr(struct kvm_lapic *apic, u32 ppr)
static bool __apic_update_ppr(struct kvm_lapic *apic, u32 *new_ppr)
static void apic_update_ppr(struct kvm_lapic *apic)
void kvm_apic_update_ppr(struct kvm_vcpu *vcpu)
static void apic_set_tpr(struct kvm_lapic *apic, u32 tpr)
static bool kvm_apic_broadcast(struct kvm_lapic *apic, u32 mda)
static bool kvm_apic_match_physical_addr(struct kvm_lapic *apic, u32 mda)
static bool kvm_apic_match_logical_addr(struct kvm_lapic *apic, u32 mda)
static u32 kvm_apic_mda(struct kvm_vcpu *vcpu, unsigned int dest_id, struct kvm_lapic *source, struct kvm_lapic *target)
bool kvm_apic_match_dest(struct kvm_vcpu *vcpu, struct kvm_lapic *source, int short_hand, unsigned int dest, int dest_mode)
int kvm_vector_to_index(u32 vector, u32 dest_vcpus, const unsigned long *bitmap, u32 bitmap_size)
static void kvm_apic_disabled_lapic_found(struct kvm *kvm)
static bool kvm_apic_is_broadcast_dest(struct kvm *kvm, struct kvm_lapic **src, struct kvm_lapic_irq *irq, struct kvm_apic_map *map)
static inline bool kvm_apic_map_get_dest_lapic(struct kvm *kvm, struct kvm_lapic **src, struct kvm_lapic_irq *irq, struct kvm_apic_map *map, struct kvm_lapic ***dst, unsigned long *bitmap)
bool kvm_irq_delivery_to_apic_fast(struct kvm *kvm, struct kvm_lapic *src, struct kvm_lapic_irq *irq, int *r, struct dest_map *dest_map)
bool kvm_intr_is_single_vcpu_fast(struct kvm *kvm, struct kvm_lapic_irq *irq, struct kvm_vcpu **dest_vcpu)
static int __apic_accept_irq(struct kvm_lapic *apic, int delivery_mode, int vector, int level, int trig_mode, struct dest_map *dest_map)
int kvm_apic_compare_prio(struct kvm_vcpu *vcpu1, struct kvm_vcpu *vcpu2)
static bool kvm_ioapic_handles_vector(struct kvm_lapic *apic, int vector)
static void kvm_ioapic_send_eoi(struct kvm_lapic *apic, int vector)
static int apic_set_eoi(struct kvm_lapic *apic)
void kvm_apic_set_eoi_accelerated(struct kvm_vcpu *vcpu, int vector)
static void apic_send_ipi(struct kvm_lapic *apic)
static u32 apic_get_tmcct(struct kvm_lapic *apic)
static void __report_tpr_access(struct kvm_lapic *apic, bool write)
static inline void report_tpr_access(struct kvm_lapic *apic, bool write)
static u32 __apic_read(struct kvm_lapic *apic, unsigned int offset)
static inline struct kvm_lapic *to_lapic(struct kvm_io_device *dev)
int kvm_lapic_reg_read(struct kvm_lapic *apic, u32 offset, int len, void *data)
static int apic_mmio_in_range(struct kvm_lapic *apic, gpa_t addr)
static int apic_mmio_read(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t address, int len, void *data)
static void update_divide_count(struct kvm_lapic *apic)
static void limit_periodic_timer_frequency(struct kvm_lapic *apic)
static void apic_update_lvtt(struct kvm_lapic *apic)
static void apic_timer_expired(struct kvm_lapic *apic)
static bool lapic_timer_int_injected(struct kvm_vcpu *vcpu)
void wait_lapic_expire(struct kvm_vcpu *vcpu)
static void start_sw_tscdeadline(struct kvm_lapic *apic)
static void update_target_expiration(struct kvm_lapic *apic, uint32_t old_divisor)
static bool set_target_expiration(struct kvm_lapic *apic)
static void advance_periodic_target_expiration(struct kvm_lapic *apic)
static void start_sw_period(struct kvm_lapic *apic)
bool kvm_lapic_hv_timer_in_use(struct kvm_vcpu *vcpu)
static void cancel_hv_timer(struct kvm_lapic *apic)
static bool start_hv_timer(struct kvm_lapic *apic)
static void start_sw_timer(struct kvm_lapic *apic)
static void restart_apic_timer(struct kvm_lapic *apic)
void kvm_lapic_expired_hv_timer(struct kvm_vcpu *vcpu)
void kvm_lapic_switch_to_hv_timer(struct kvm_vcpu *vcpu)
void kvm_lapic_switch_to_sw_timer(struct kvm_vcpu *vcpu)
void kvm_lapic_restart_hv_timer(struct kvm_vcpu *vcpu)
static void start_apic_timer(struct kvm_lapic *apic)
static void apic_manage_nmi_watchdog(struct kvm_lapic *apic, u32 lvt0_val)
int kvm_lapic_reg_write(struct kvm_lapic *apic, u32 reg, u32 val)
static int apic_mmio_write(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t address, int len, const void *data)
void kvm_lapic_set_eoi(struct kvm_vcpu *vcpu)
void kvm_apic_write_nodecode(struct kvm_vcpu *vcpu, u32 offset)
void kvm_free_lapic(struct kvm_vcpu *vcpu)
u64 kvm_get_lapic_tscdeadline_msr(struct kvm_vcpu *vcpu)
void kvm_set_lapic_tscdeadline_msr(struct kvm_vcpu *vcpu, u64 data)
void kvm_lapic_set_tpr(struct kvm_vcpu *vcpu, unsigned long cr8)
u64 kvm_lapic_get_cr8(struct kvm_vcpu *vcpu)
void kvm_lapic_set_base(struct kvm_vcpu *vcpu, u64 value)
void kvm_lapic_reset(struct kvm_vcpu *vcpu, bool init_event)
static bool lapic_is_periodic(struct kvm_lapic *apic)
int apic_has_pending_timer(struct kvm_vcpu *vcpu)
int kvm_apic_local_deliver(struct kvm_lapic *apic, int lvt_type)
void kvm_apic_nmi_wd_deliver(struct kvm_vcpu *vcpu)
static enum hrtimer_restart apic_timer_fn(struct hrtimer *data)
int kvm_create_lapic(struct kvm_vcpu *vcpu)
int kvm_apic_has_interrupt(struct kvm_vcpu *vcpu)
int kvm_apic_accept_pic_intr(struct kvm_vcpu *vcpu)
void kvm_inject_apic_timer_irqs(struct kvm_vcpu *vcpu)
int kvm_get_apic_interrupt(struct kvm_vcpu *vcpu)
static int kvm_apic_state_fixup(struct kvm_vcpu *vcpu, struct kvm_lapic_state *s, bool set)
int kvm_apic_get_state(struct kvm_vcpu *vcpu, struct kvm_lapic_state *s)
int kvm_apic_set_state(struct kvm_vcpu *vcpu, struct kvm_lapic_state *s)
void __kvm_migrate_apic_timer(struct kvm_vcpu *vcpu)
static void apic_sync_pv_eoi_from_guest(struct kvm_vcpu *vcpu, struct kvm_lapic *apic)
void kvm_lapic_sync_from_vapic(struct kvm_vcpu *vcpu)
static void apic_sync_pv_eoi_to_guest(struct kvm_vcpu *vcpu, struct kvm_lapic *apic)
void kvm_lapic_sync_to_vapic(struct kvm_vcpu *vcpu)
int kvm_lapic_set_vapic_addr(struct kvm_vcpu *vcpu, gpa_t vapic_addr)
int kvm_x2apic_msr_write(struct kvm_vcpu *vcpu, u32 msr, u64 data)
int kvm_x2apic_msr_read(struct kvm_vcpu *vcpu, u32 msr, u64 *data)
int kvm_hv_vapic_msr_write(struct kvm_vcpu *vcpu, u32 reg, u64 data)
int kvm_hv_vapic_msr_read(struct kvm_vcpu *vcpu, u32 reg, u64 *data)
int kvm_lapic_enable_pv_eoi(struct kvm_vcpu *vcpu, u64 data, unsigned long len)
void kvm_apic_accept_events(struct kvm_vcpu *vcpu)
void kvm_lapic_init(void)
void kvm_lapic_exit(void)
  56 struct kvm_lapic *apic
  55 struct kvm_vcpu *vcpu
   7 struct kvm *kvm
   7 int vec
   6 void *bitmap
   5 struct kvm_lapic_irq *irq
   5 int vector
   4 u64 data
   3 u32 reg
   3 u32 mda
   3 u32 id
   3 struct kvm_lapic_state *s
   3 struct dest_map *dest_map
   3 int lvt_type
   3 int len
   2 void *data
   2 void
   2 u64 *data
   2 u32 val
   2 u32 offset
   2 u32 msr
   2 u32 *pir
   2 struct kvm_lapic *source
   2 struct kvm_lapic **src
   2 struct kvm_io_device *this
   2 struct kvm_apic_map *map
   2 int *max_irr
   2 gpa_t address
   2 bool write
   1 void *regs
   1 unsigned long len
   1 unsigned long ipi_bitmap_low
   1 unsigned long ipi_bitmap_high
   1 unsigned long icr
   1 unsigned long cr8
   1 unsigned long *bitmap
   1 unsigned int offset
   1 unsigned int dest_id
   1 unsigned int dest
   1 uint32_t old_divisor
   1 u8 val
   1 u8 id
   1 u8 *val
   1 u64 value
   1 u32 vector
   1 u32 tpr
   1 u32 ppr
   1 u32 min
   1 u32 lvt_val
   1 u32 lvt0_val
   1 u32 dest_vcpus
   1 u32 bitmap_size
   1 u32 *new_ppr
   1 struct rcu_head *rcu
   1 struct kvm_vcpu *vcpu2
   1 struct kvm_vcpu *vcpu1
   1 struct kvm_vcpu **dest_vcpu
   1 struct kvm_lapic *target
   1 struct kvm_lapic *src
   1 struct kvm_lapic ***dst
   1 struct kvm_io_device *dev
   1 struct hrtimer *data
   1 kvm_lapic_switch_to_sw_timer
   1 kvm_lapic_switch_to_hv_timer
   1 kvm_lapic_set_eoi
   1 kvm_lapic_reg_write
   1 kvm_lapic_reg_read
   1 kvm_lapic_hv_timer_in_use
   1 kvm_lapic_find_highest_irr
   1 kvm_lapic_expired_hv_timer
   1 kvm_apic_write_nodecode
   1 kvm_apic_update_ppr
   1 kvm_apic_update_irr
   1 kvm_apic_set_eoi_accelerated
   1 kvm_apic_match_dest
   1 int trig_mode
   1 int short_hand
   1 int op_64_bit
   1 int level
   1 int dest_mode
   1 int delivery_mode
   1 int *r
   1 gpa_t vapic_addr
   1 gpa_t addr
   1 const void *data
   1 const unsigned long *bitmap
   1 bool set
   1 bool init_event
   1 __kvm_apic_update_irr
