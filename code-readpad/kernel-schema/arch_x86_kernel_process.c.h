
int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src)
void exit_thread(struct task_struct *tsk)
void flush_thread(void)
void disable_TSC(void)
static void enable_TSC(void)
int get_tsc_mode(unsigned long adr)
int set_tsc_mode(unsigned int val)
static void set_cpuid_faulting(bool on)
static void disable_cpuid(void)
static void enable_cpuid(void)
static int get_cpuid_mode(void)
static int set_cpuid_mode(struct task_struct *task, unsigned long cpuid_enabled)
void arch_setup_new_exec(void)
static inline void switch_to_bitmap(struct tss_struct *tss, struct thread_struct *prev, struct thread_struct *next, unsigned long tifp, unsigned long tifn)
void speculative_store_bypass_ht_init(void)
static __always_inline void amd_set_core_ssb_state(unsigned long tifn)
raw_spin_lock(&st->shared_state->lock)
; st->shared_state->disable_state--; if (!st->shared_state->disable_state)
wrmsrl(MSR_AMD64_LS_CFG, msr)
; raw_spin_unlock(&st->shared_state->lock)
;} } static __always_inline void amd_set_core_ssb_state(unsigned long tifn)
static __always_inline void amd_set_ssb_virt_state(unsigned long tifn)
static __always_inline void intel_set_ssb_state(unsigned long tifn)
static __always_inline void __speculative_store_bypass_update(unsigned long tifn)
void speculative_store_bypass_update(unsigned long tif)
void __switch_to_xtra(struct task_struct *prev_p, struct task_struct *next_p, struct tss_struct *tss)
static inline void play_dead(void)
void arch_cpu_idle_enter(void)
void arch_cpu_idle_dead(void)
void arch_cpu_idle(void)
void __cpuidle default_idle(void)
bool xen_set_default_idle(void)
void stop_this_cpu(void *dummy)
static void amd_e400_idle(void)
static int prefer_mwait_c1_over_halt(const struct cpuinfo_x86 *c)
static __cpuidle void mwait_idle(void)
void select_idle_routine(const struct cpuinfo_x86 *c)
void amd_e400_c1e_apic_setup(void)
void __init arch_post_acpi_subsys_init(void)
static int __init idle_setup(char *str)
unsigned long arch_align_stack(unsigned long sp)
unsigned long arch_randomize_brk(struct mm_struct *mm)
unsigned long get_wchan(struct task_struct *p)
long do_arch_prctl_common(struct task_struct *task, int option, unsigned long cpuid_enabled)
  18 void
   6 unsigned long tifn
   2 unsigned long cpuid_enabled
   2 struct tss_struct *tss
   2 struct task_struct *task
   2 const struct cpuinfo_x86 *c
   2 &st->shared_state->lock
   1 void *dummy
   1 unsigned long tifp
   1 unsigned long tif
   1 unsigned long sp
   1 unsigned long adr
   1 unsigned int val
   1 struct thread_struct *prev
   1 struct thread_struct *next
   1 struct task_struct *tsk
   1 struct task_struct *src
   1 struct task_struct *prev_p
   1 struct task_struct *p
   1 struct task_struct *next_p
   1 struct task_struct *dst
   1 struct mm_struct *mm
   1 msr
   1 int option
   1 char *str
   1 bool on
   1 MSR_AMD64_LS_CFG
   1 !st->shared_state->disable_state
