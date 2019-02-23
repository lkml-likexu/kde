
\n
void acpi_processor_power_init_bm_check(struct acpi_processor_flags *flags, unsigned int cpu)
; int acpi_processor_ffh_cstate_probe(unsigned int cpu, struct acpi_processor_cx *cx, struct acpi_power_register *reg)
; void acpi_processor_ffh_cstate_enter(struct acpi_processor_cx *cstate)
; static inline void acpi_processor_power_init_bm_check(struct acpi_processor_flags *flags, unsigned int cpu)
void acpi_processor_power_init_bm_check(struct acpi_processor_flags *flags, unsigned int cpu)
; int acpi_processor_ffh_cstate_probe(unsigned int cpu, struct acpi_processor_cx *cx, struct acpi_power_register *reg)
; void acpi_processor_ffh_cstate_enter(struct acpi_processor_cx *cstate)
; static inline void acpi_processor_power_init_bm_check(struct acpi_processor_flags *flags, unsigned int cpu)
flags->bm_check = 1;return; } static inline int acpi_processor_ffh_cstate_probe(unsigned int cpu, struct acpi_processor_cx *cx, struct acpi_power_register *reg)
void acpi_processor_power_init_bm_check(struct acpi_processor_flags *flags, unsigned int cpu)
; int acpi_processor_ffh_cstate_probe(unsigned int cpu, struct acpi_processor_cx *cx, struct acpi_power_register *reg)
; void acpi_processor_ffh_cstate_enter(struct acpi_processor_cx *cstate)
; static inline void acpi_processor_power_init_bm_check(struct acpi_processor_flags *flags, unsigned int cpu)
flags->bm_check = 1;return; } static inline int acpi_processor_ffh_cstate_probe(unsigned int cpu, struct acpi_processor_cx *cx, struct acpi_power_register *reg)
return -1; } static inline void acpi_processor_ffh_cstate_enter(struct acpi_processor_cx*cstate)
void acpi_processor_ppc_init(void)
; void acpi_processor_ppc_exit(void)
; void acpi_processor_ppc_has_changed(struct acpi_processor *pr, int event_flag)
; extern int acpi_processor_get_bios_limit(int cpu, unsigned int *limit)
; static inline void acpi_processor_ppc_init(void)
void acpi_processor_ppc_init(void)
; void acpi_processor_ppc_exit(void)
; void acpi_processor_ppc_has_changed(struct acpi_processor *pr, int event_flag)
; extern int acpi_processor_get_bios_limit(int cpu, unsigned int *limit)
; static inline void acpi_processor_ppc_init(void)
return; } static inline void acpi_processor_ppc_exit(void)
void acpi_processor_ppc_init(void)
; void acpi_processor_ppc_exit(void)
; void acpi_processor_ppc_has_changed(struct acpi_processor *pr, int event_flag)
; extern int acpi_processor_get_bios_limit(int cpu, unsigned int *limit)
; static inline void acpi_processor_ppc_init(void)
return; } static inline void acpi_processor_ppc_exit(void)
return; } static inline void acpi_processor_ppc_has_changed(struct acpi_processor *pr, int event_flag)
void acpi_processor_ppc_init(void)
; void acpi_processor_ppc_exit(void)
; void acpi_processor_ppc_has_changed(struct acpi_processor *pr, int event_flag)
; extern int acpi_processor_get_bios_limit(int cpu, unsigned int *limit)
; static inline void acpi_processor_ppc_init(void)
return; } static inline void acpi_processor_ppc_exit(void)
return; } static inline void acpi_processor_ppc_has_changed(struct acpi_processor *pr, int event_flag)
static unsigned int printout = 1; printk(KERN_WARNING"Warning: Processor Platform Limit event detected, but not handled.\n")
; printk(KERN_WARNING"Consider compiling CPUfreq support into your kernel.\n")
; printout = 0;} } static inline int acpi_processor_get_bios_limit(int cpu, unsigned int *limit)
extern int acpi_cppc_processor_probe(struct acpi_processor *pr)
; extern void acpi_cppc_processor_exit(struct acpi_processor *pr)
; static inline int acpi_cppc_processor_probe(struct acpi_processor *pr)
extern int acpi_cppc_processor_probe(struct acpi_processor *pr)
; extern void acpi_cppc_processor_exit(struct acpi_processor *pr)
; static inline int acpi_cppc_processor_probe(struct acpi_processor *pr)
return 0; } static inline void acpi_cppc_processor_exit(struct acpi_processor *pr)
int acpi_processor_tstate_has_changed(struct acpi_processor *pr)
; int acpi_processor_get_throttling_info(struct acpi_processor *pr)
; extern int acpi_processor_set_throttling(struct acpi_processor *pr, int state, bool force)
;extern void acpi_processor_reevaluate_tstate(struct acpi_processor *pr, bool is_dead)
; extern const struct file_operations acpi_processor_throttling_fops; extern void acpi_processor_throttling_init(void)
; static inline int acpi_processor_tstate_has_changed(struct acpi_processor *pr)
static inline int acpi_processor_get_throttling_info(struct acpi_processor *pr)
static inline int acpi_processor_set_throttling(struct acpi_processor *pr, int state, bool force)
extern struct cpuidle_driver acpi_idle_driver; int acpi_processor_power_init(struct acpi_processor *pr)
; int acpi_processor_power_exit(struct acpi_processor *pr)
; int acpi_processor_power_state_has_changed(struct acpi_processor *pr)
; int acpi_processor_hotplug(struct acpi_processor *pr)
; static inline int acpi_processor_power_init(struct acpi_processor *pr)
static inline int acpi_processor_power_exit(struct acpi_processor *pr)
static inline int acpi_processor_power_state_has_changed(struct acpi_processor *pr)
static inline int acpi_processor_hotplug(struct acpi_processor *pr)
int acpi_processor_get_limit_info(struct acpi_processor *pr)
; extern const struct thermal_cooling_device_ops processor_cooling_ops; void acpi_thermal_cpufreq_init(void)
; void acpi_thermal_cpufreq_exit(void)
; static inline void acpi_thermal_cpufreq_init(void)
int acpi_processor_get_limit_info(struct acpi_processor *pr)
; extern const struct thermal_cooling_device_ops processor_cooling_ops; void acpi_thermal_cpufreq_init(void)
; void acpi_thermal_cpufreq_exit(void)
; static inline void acpi_thermal_cpufreq_init(void)
return; } static inline void acpi_thermal_cpufreq_exit(void)
\n
     30 struct acpi_processor *pr
     23 void
     11 unsigned int cpu
      6 struct acpi_processor_flags *flags
      6 int event_flag
      5 unsigned int *limit
      5 struct acpi_processor_cx *cx
      5 struct acpi_power_register *reg
      5 int cpu
      3 struct acpi_processor_cx *cstate
      2 int state
      2 bool force
      1 struct acpi_processor_cx*cstate
      1 KERN_WARNING"Warning: Processor Platform Limit event detected
      1 KERN_WARNING"Consider compiling CPUfreq support into your kernel.\n"
      1 but not handled.\n"
      1 bool is_dead
