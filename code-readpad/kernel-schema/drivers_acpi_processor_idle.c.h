
\n
static int disabled_by_idle_boot_param(void)
static int set_max_cstate(const struct dmi_system_id *id)
static void __cpuidle acpi_safe_halt(void)
static void lapic_timer_check_state(int state, struct acpi_processor *pr, struct acpi_processor_cx *cx)
static void __lapic_timer_propagate_broadcast(void *arg)
static void lapic_timer_propagate_broadcast(struct acpi_processor *pr)
static void lapic_timer_state_broadcast(struct acpi_processor *pr, struct acpi_processor_cx *cx, int broadcast)
static void lapic_timer_check_state(int state, struct acpi_processor *pr, static void lapic_timer_state_broadcast(struct acpi_processor *pr, struct acpi_processor_cx *cx, int broadcast)
static void tsc_check_state(int state)
static int acpi_processor_get_power_info_fadt(struct acpi_processor *pr)
static int acpi_processor_get_power_info_default(struct acpi_processor *pr)
static int acpi_processor_get_power_info_cst(struct acpi_processor *pr)
static void acpi_processor_power_verify_c3(struct acpi_processor *pr, struct acpi_processor_cx *cx)
static int acpi_processor_power_verify(struct acpi_processor *pr)
static int acpi_processor_get_cstate_info(struct acpi_processor *pr)
static int acpi_idle_bm_check(void)
static void __cpuidle acpi_idle_do_entry(struct acpi_processor_cx *cx)
static int acpi_idle_play_dead(struct cpuidle_device *dev, int index)
static bool acpi_idle_fallback_to_c1(struct acpi_processor *pr)
static void acpi_idle_enter_bm(struct acpi_processor *pr, struct acpi_processor_cx *cx, bool timer_bc)
static int acpi_idle_enter(struct cpuidle_device *dev, struct cpuidle_driver *drv, int index)
static void acpi_idle_enter_s2idle(struct cpuidle_device *dev, struct cpuidle_driver *drv, int index)
static int acpi_processor_setup_cpuidle_cx(struct acpi_processor *pr, struct cpuidle_device *dev)
static int acpi_processor_setup_cstates(struct acpi_processor *pr)
static inline void acpi_processor_cstate_first_run_checks(void)
static int acpi_processor_get_cstate_info(struct acpi_processor *pr)
static int acpi_processor_setup_cpuidle_cx(struct acpi_processor *pr, struct cpuidle_device *dev)
static int acpi_processor_setup_cstates(struct acpi_processor *pr)
static int obj_get_integer(union acpi_object *obj, u32 *value)
static int acpi_processor_evaluate_lpi(acpi_handle handle, struct acpi_lpi_states_array *info)
static bool combine_lpi_states(struct acpi_lpi_state *local, struct acpi_lpi_state *parent, struct acpi_lpi_state *result)
static void stash_composite_state(struct acpi_lpi_states_array *curr_level, struct acpi_lpi_state *t)
static int flatten_lpi_states(struct acpi_processor *pr, struct acpi_lpi_states_array *curr_level, struct acpi_lpi_states_array *prev_level)
static int acpi_processor_get_lpi_info(struct acpi_processor *pr)
int __weak acpi_processor_ffh_lpi_probe(unsigned int cpu)
int __weak acpi_processor_ffh_lpi_enter(struct acpi_lpi_state *lpi)
static int acpi_idle_lpi_enter(struct cpuidle_device *dev, struct cpuidle_driver *drv, int index)
static int acpi_processor_setup_lpi_states(struct acpi_processor *pr)
static int acpi_processor_setup_cpuidle_states(struct acpi_processor *pr)
static int acpi_processor_setup_cpuidle_dev(struct acpi_processor *pr, struct cpuidle_device *dev)
static int acpi_processor_get_power_info(struct acpi_processor *pr)
int acpi_processor_hotplug(struct acpi_processor *pr)
int acpi_processor_power_state_has_changed(struct acpi_processor *pr)
int acpi_processor_power_init(struct acpi_processor *pr)
int acpi_processor_power_exit(struct acpi_processor *pr)
\n
     27 struct acpi_processor *pr
      7 struct cpuidle_device *dev
      6 struct acpi_processor_cx *cx
      4 void
      4 int index
      3 struct cpuidle_driver *drv
      3 int state
      2 struct acpi_lpi_states_array *curr_level
      2 int broadcast
      1 void *arg
      1 unsigned int cpu
      1 union acpi_object *obj
      1 u32 *value
      1 struct acpi_lpi_state *t
      1 struct acpi_lpi_states_array *prev_level
      1 struct acpi_lpi_states_array *info
      1 struct acpi_lpi_state *result
      1 struct acpi_lpi_state *parent
      1 struct acpi_lpi_state *lpi
      1 struct acpi_lpi_state *local
      1 static void lapic_timer_state_broadcaststruct acpi_processor *pr
      1 const struct dmi_system_id *id
      1 bool timer_bc
      1 acpi_handle handle
