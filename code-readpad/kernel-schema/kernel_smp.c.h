
EXPORT_SYMBOL_GPL(smp_call_function_single_async);
EXPORT_SYMBOL_GPL(smp_call_function_any);
EXPORT_SYMBOL_GPL(kick_all_cpus_sync);
EXPORT_SYMBOL_GPL(wake_up_all_idle_cpus);
EXPORT_SYMBOL_GPL(smp_call_on_cpu);
\n
int smpcfd_prepare_cpu(unsigned int cpu)
int smpcfd_dead_cpu(unsigned int cpu)
int smpcfd_dying_cpu(unsigned int cpu)
void __init call_function_init(void)
static __always_inline void csd_lock_wait(call_single_data_t *csd)
static __always_inline void csd_lock(call_single_data_t *csd)
static __always_inline void csd_unlock(call_single_data_t *csd)
static int generic_exec_single(int cpu, call_single_data_t *csd, smp_call_func_t func, void *info)
void generic_smp_call_function_single_interrupt(void)
static void flush_smp_call_function_queue(bool warn_cpu_offline)
int smp_call_function_single(int cpu, smp_call_func_t func, void *info, int wait)
int smp_call_function_single_async(int cpu, call_single_data_t *csd)
int smp_call_function_any(const struct cpumask *mask, smp_call_func_t func, void *info, int wait)
void smp_call_function_many(const struct cpumask *mask, smp_call_func_t func, void *info, bool wait)
int smp_call_function(smp_call_func_t func, void *info, int wait)
static int __init nosmp(char *str)
static int __init nrcpus(char *str)
static int __init maxcpus(char *str)
void __init setup_nr_cpu_ids(void)
void __init smp_init(void)
int on_each_cpu(void (*func)
(void *info)
, void *info, int wait)
void on_each_cpu_mask(const struct cpumask *mask, smp_call_func_t func, void *info, bool wait)
void on_each_cpu_cond_mask(bool (*cond_func)
(int cpu, void *info)
, smp_call_func_t func, void *info, bool wait, gfp_t gfp_flags, const struct cpumask *mask)
void on_each_cpu_cond(bool (*cond_func)
(int cpu, void *info)
, smp_call_func_t func, void *info, bool wait, gfp_t gfp_flags)
static void do_nothing(void *unused)
void kick_all_cpus_sync(void)
void wake_up_all_idle_cpus(void)
static void smp_call_on_cpu_callback(struct work_struct *work)
int smp_call_on_cpu(unsigned int cpu, int (*func)
(void *)
, void *par, bool phys)
\n
      9 void *info
      6 void
      6 smp_call_func_t func
      5 int cpu
      5 call_single_data_t *csd
      4 unsigned int cpu
      3 int wait
      3 const struct cpumask *mask
      3 char *str
      2 bool wait
      2 bool *cond_func
      1 wake_up_all_idle_cpus
      1 void *unused
      1 void *func
      1 void *
      1 struct work_struct *work
      1 smp_call_on_cpu
      1 smp_call_function_single_async
      1 smp_call_function_any
      1 kick_all_cpus_sync
      1 int *func
      1 bool warn_cpu_offline
