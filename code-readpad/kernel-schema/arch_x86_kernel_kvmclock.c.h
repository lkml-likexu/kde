
EXPORT_SYMBOL_GPL(kvm_clock);
static int __init parse_no_kvmclock(char *arg)
static int __init parse_no_kvmclock_vsyscall(char *arg)
static inline struct pvclock_vcpu_time_info *this_cpu_pvti(void)
static inline struct pvclock_vsyscall_time_info *this_cpu_hvclock(void)
static void kvm_get_wallclock(struct timespec64 *now)
static int kvm_set_wallclock(const struct timespec64 *now)
static u64 kvm_clock_read(void)
static u64 kvm_clock_get_cycles(struct clocksource *cs)
static u64 kvm_sched_clock_read(void)
static inline void kvm_sched_clock_init(bool stable)
static unsigned long kvm_get_tsc_khz(void)
static void __init kvm_get_preset_lpj(void)
bool kvm_check_and_clear_guest_paused(void)
static void kvm_register_clock(char *txt)
static void kvm_save_sched_clock_state(void)
static void kvm_restore_sched_clock_state(void)
static void kvm_setup_secondary_clock(void)
static void kvm_crash_shutdown(struct pt_regs *regs)
static void kvm_shutdown(void)
static void __init kvmclock_init_mem(void)
static int __init kvm_setup_vsyscall_timeinfo(void)
static int kvmclock_setup_percpu(unsigned int cpu)
void __init kvmclock_init(void)
  14 void
   2 char *arg
   1 unsigned int cpu
   1 struct timespec64 *now
   1 struct pt_regs *regs
   1 struct clocksource *cs
   1 kvm_clock
   1 const struct timespec64 *now
   1 char *txt
   1 bool stable
