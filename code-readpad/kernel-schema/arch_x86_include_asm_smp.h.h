
\n
static inline struct cpumask *cpu_llc_shared_mask(int cpu)
static inline void smp_send_stop(void)
static inline void stop_other_cpus(void)
static inline void smp_prepare_boot_cpu(void)
static inline void smp_prepare_cpus(unsigned int max_cpus)
static inline void smp_cpus_done(unsigned int max_cpus)
static inline int __cpu_up(unsigned int cpu, struct task_struct *tidle)
static inline int __cpu_disable(void)
static inline void __cpu_die(unsigned int cpu)
static inline void play_dead(void)
static inline void smp_send_reschedule(int cpu)
static inline void arch_send_call_function_single_ipi(int cpu)
static inline void arch_send_call_function_ipi_mask(const struct cpumask *mask)
define wbinvd_on_cpu(cpu)
wbinvd()
static inline int wbinvd_on_all_cpus(void)
\n
      6 void
      3 int cpu
      2 unsigned int max_cpus
      2 unsigned int cpu
      1 struct task_struct *tidle
      1 cpu
      1 const struct cpumask *mask
      1 
