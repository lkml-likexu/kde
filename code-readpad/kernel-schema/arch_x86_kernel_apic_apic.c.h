
EXPORT_SYMBOL_GPL(boot_cpu_physical_apicid);
EXPORT_SYMBOL_GPL(local_apic_timer_c2_ok);
EXPORT_SYMBOL_GPL(setup_APIC_eilvt);
\n
static inline void imcr_pic_to_apic(void)
static inline void imcr_apic_to_pic(void)
static int __init parse_lapic(char *arg)
static int apic_calibrate_pmtmr __initdata; static __init int setup_apicpmtimer(char *s)
static inline int lapic_get_version(void)
static inline int lapic_is_integrated(void)
static int modern_apic(void)
static void __init apic_disable(void)
void native_apic_wait_icr_idle(void)
u32 native_safe_apic_wait_icr_idle(void)
void native_apic_icr_write(u32 low, u32 id)
u64 native_apic_icr_read(void)
int get_physical_broadcast(void)
int lapic_get_maxlvt(void)
static void __setup_APIC_LVTT(unsigned int clocks, int oneshot, int irqen)
static inline int eilvt_entry_is_changeable(unsigned int old, unsigned int new)
static unsigned int reserve_eilvt_offset(int offset, unsigned int new)
int setup_APIC_eilvt(u8 offset, u8 vector, u8 msg_type, u8 mask)
static int lapic_next_event(unsigned long delta, struct clock_event_device *evt)
static int lapic_next_deadline(unsigned long delta, struct clock_event_device *evt)
static int lapic_timer_shutdown(struct clock_event_device *evt)
static inline int lapic_timer_set_periodic_oneshot(struct clock_event_device *evt, bool oneshot)
static int lapic_timer_set_periodic(struct clock_event_device *evt)
static int lapic_timer_set_oneshot(struct clock_event_device *evt)
static void lapic_timer_broadcast(const struct cpumask *mask)
static u32 hsx_deadline_rev(void)
static u32 bdx_deadline_rev(void)
static u32 skx_deadline_rev(void)
static void apic_check_deadline_errata(void)
static void setup_APIC_timer(void)
static void __lapic_update_tsc_freq(void *info)
void lapic_update_tsc_freq(void)
static void __init lapic_cal_handler(struct clock_event_device *dev)
static int __init calibrate_by_pmtimer(long deltapm, long *delta, long *deltatsc)
static int __init calibrate_APIC_clock(void)
void __init setup_boot_APIC_clock(void)
void setup_secondary_APIC_clock(void)
static void local_apic_timer_interrupt(void)
__visible void __irq_entry smp_apic_timer_interrupt(struct pt_regs *regs)
int setup_profiling_timer(unsigned int multiplier)
void clear_local_APIC(void)
void disable_local_APIC(void)
void lapic_shutdown(void)
void __init sync_Arb_IDs(void)
static int __init apic_intr_mode_select(void)
void __init init_bsp_APIC(void)
void __init apic_intr_mode_init(void)
static void lapic_setup_esr(void)
static void apic_pending_intr_clear(void)
static void setup_local_APIC(void)
static void end_local_APIC_setup(void)
void apic_ap_setup(void)
static void __x2apic_disable(void)
static void __x2apic_enable(void)
static int __init setup_nox2apic(char *str)
void x2apic_setup(void)
static __init void x2apic_disable(void)
static __init void x2apic_enable(void)
static __init void try_to_enable_x2apic(int remap_mode)
void __init check_x2apic(void)
void __init check_x2apic(void)
pr_info("x2apic: enabled by BIOS, switching to x2apic ops\n")
; x2apic_mode = 1; x2apic_state = X2APIC_ON; x2apic_state = X2APIC_DISABLED;} } static int __init validate_x2apic(void)
void __init enable_IR_x2apic(void)
static int __init detect_init_APIC(void)
static int __init apic_verify(void)
int __init apic_force_enable(unsigned long addr)
static int __init detect_init_APIC(void)
void __init init_apic_mappings(void)
void __init register_lapic_address(unsigned long address)
__visible void __irq_entry smp_spurious_interrupt(struct pt_regs *regs)
__visible void __irq_entry smp_error_interrupt(struct pt_regs *regs)
static void __init connect_bsp_APIC(void)
void disconnect_bsp_APIC(int virt_wire_setup)
bool apic_id_is_primary_thread(unsigned int apicid)
static int allocate_logical_cpuid(int apicid)
int generic_processor_info(int apicid, int version)
int hard_smp_processor_id(void)
void __init apic_set_eoi_write(void (*eoi_write)
(u32 reg, u32 v)
)
static void __init apic_bsp_up_setup(void)
void __init apic_bsp_setup(bool upmode)
void __init up_late_init(void)
static int lapic_suspend(void)
static void lapic_resume(void)
static void apic_pm_activate(void)
static int __init init_lapic_sysfs(void)
static int set_multi(const struct dmi_system_id *d)
static void dmi_check_multi(void)
int apic_is_clustered_box(void)
static int __init setup_disableapic(char *arg)
static int __init setup_nolapic(char *arg)
static int __init parse_lapic_timer_c2_ok(char *arg)
static int __init parse_disable_apic_timer(char *arg)
static int __init parse_nolapic_timer(char *arg)
static int __init apic_set_verbosity(char *arg)
static int __init lapic_insert_resource(void)
static int __init apic_set_disabled_cpu_apicid(char *arg)
static int __init apic_set_extnmi(char *arg)
\n
     57 void
      9 char *arg
      6 struct clock_event_device *evt
      3 struct pt_regs *regs
      2 unsigned long delta
      2 unsigned int new
      2 int apicid
      1 "x2apic: enabled by BIOS
      1 void *info
      1 void *eoi_write
      1 unsigned long address
      1 unsigned long addr
      1 unsigned int old
      1 unsigned int multiplier
      1 unsigned int clocks
      1 unsigned int apicid
      1 u8 vector
      1 u8 offset
      1 u8 msg_type
      1 u8 mask
      1 u32 v
      1 u32 reg
      1 u32 low
      1 u32 id
      1 switching to x2apic ops\n"
      1 struct clock_event_device *dev
      1 setup_APIC_eilvt
      1 long *deltatsc
      1 long deltapm
      1 long *delta
      1 local_apic_timer_c2_ok
      1 int virt_wire_setup
      1 int version
      1 int remap_mode
      1 int oneshot
      1 int offset
      1 int irqen
      1 const struct dmi_system_id *d
      1 const struct cpumask *mask
      1 char *str
      1 char *s
      1 boot_cpu_physical_apicid
      1 bool upmode
      1 bool oneshot
