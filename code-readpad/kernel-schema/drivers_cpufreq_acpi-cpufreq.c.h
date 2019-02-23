
\n
static inline struct acpi_processor_performance *to_perf_data(struct acpi_cpufreq_data *data)
static bool boost_state(unsigned int cpu)
static int boost_set_msr(bool enable)
static void boost_set_msr_each(void *p_en)
static int set_boost(int val)
static ssize_t show_freqdomain_cpus(struct cpufreq_policy *policy, char *buf)
static ssize_t store_cpb(struct cpufreq_policy *policy, const char *buf, size_t count)
static ssize_t show_cpb(struct cpufreq_policy *policy, char *buf)
static int check_est_cpu(unsigned int cpuid)
static int check_amd_hwpstate_cpu(unsigned int cpuid)
static unsigned extract_io(struct cpufreq_policy *policy, u32 value)
static unsigned extract_msr(struct cpufreq_policy *policy, u32 msr)
static unsigned extract_freq(struct cpufreq_policy *policy, u32 val)
static u32 cpu_freq_read_intel(struct acpi_pct_register *not_used)
static void cpu_freq_write_intel(struct acpi_pct_register *not_used, u32 val)
static u32 cpu_freq_read_amd(struct acpi_pct_register *not_used)
static void cpu_freq_write_amd(struct acpi_pct_register *not_used, u32 val)
static u32 cpu_freq_read_io(struct acpi_pct_register *reg)
static void cpu_freq_write_io(struct acpi_pct_register *reg, u32 val)
static void do_drv_read(void *_cmd)
static u32 drv_read(struct acpi_cpufreq_data *data, const struct cpumask *mask)
static void do_drv_write(void *_cmd)
static void drv_write(struct acpi_cpufreq_data *data, const struct cpumask *mask, u32 val)
static u32 get_cur_val(const struct cpumask *mask, struct acpi_cpufreq_data *data)
static unsigned int get_cur_freq_on_cpu(unsigned int cpu)
static unsigned int check_freqs(struct cpufreq_policy *policy, const struct cpumask *mask, unsigned int freq)
static int acpi_cpufreq_target(struct cpufreq_policy *policy, unsigned int index)
static unsigned int acpi_cpufreq_fast_switch(struct cpufreq_policy *policy, unsigned int target_freq)
static unsigned long acpi_cpufreq_guess_freq(struct acpi_cpufreq_data *data, unsigned int cpu)
static void free_acpi_perf_data(void)
static int cpufreq_boost_online(unsigned int cpu)
static int cpufreq_boost_down_prep(unsigned int cpu)
static int __init acpi_cpufreq_early_init(void)
static int sw_any_bug_found(const struct dmi_system_id *d)
static int acpi_cpufreq_blacklist(struct cpuinfo_x86 *c)
static int acpi_cpufreq_cpu_init(struct cpufreq_policy *policy)
static int acpi_cpufreq_cpu_exit(struct cpufreq_policy *policy)
static void acpi_cpufreq_cpu_ready(struct cpufreq_policy *policy)
static int acpi_cpufreq_resume(struct cpufreq_policy *policy)
static void __init acpi_cpufreq_boost_init(void)
static void acpi_cpufreq_boost_exit(void)
static int __init acpi_cpufreq_init(void)
static void __exit acpi_cpufreq_exit(void)
\n
     13 struct cpufreq_policy *policy
      6 void
      5 unsigned int cpu
      5 u32 val
      5 struct acpi_cpufreq_data *data
      4 struct acpi_pct_register *not_used
      4 const struct cpumask *mask
      2 void *_cmd
      2 unsigned int cpuid
      2 struct acpi_pct_register *reg
      2 char *buf
      1 void *p_en
      1 unsigned int target_freq
      1 unsigned int index
      1 unsigned int freq
      1 u32 value
      1 u32 msr
      1 struct cpuinfo_x86 *c
      1 size_t count
      1 int val
      1 const struct dmi_system_id *d
      1 const char *buf
      1 bool enable
