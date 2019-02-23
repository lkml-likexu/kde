
EXPORT_SYMBOL_GPL(acpi_target_system_state);
\n
static void acpi_sleep_tts_switch(u32 acpi_state)
static int tts_notify_reboot(struct notifier_block *this, unsigned long code, void *x)
static int acpi_sleep_prepare(u32 acpi_state)
static bool acpi_sleep_state_supported(u8 sleep_state)
u32 acpi_target_system_state(void)
void __init acpi_nvs_nosave(void)
void __init acpi_nvs_nosave_s3(void)
static int __init init_nvs_save_s3(const struct dmi_system_id *d)
void __init acpi_old_suspend_ordering(void)
static int __init init_old_suspend_ordering(const struct dmi_system_id *d)
static int __init init_nvs_nosave(const struct dmi_system_id *d)
static int __init init_no_lps0(const struct dmi_system_id *d)
void __init acpi_sleep_no_blacklist(void)
static void __init acpi_sleep_dmi_check(void)
static int acpi_pm_freeze(void)
static int acpi_pm_pre_suspend(void)
static int __acpi_pm_prepare(void)
static int acpi_pm_prepare(void)
static int find_powerf_dev(struct device *dev, void *data)
static void acpi_pm_finish(void)
static void acpi_pm_start(u32 acpi_state)
static void acpi_pm_end(void)
static int acpi_suspend_begin(suspend_state_t pm_state)
static int acpi_suspend_enter(suspend_state_t pm_state)
static int acpi_suspend_state_valid(suspend_state_t pm_state)
static int acpi_suspend_begin_old(suspend_state_t pm_state)
static void lpi_device_get_constraints(void)
static void lpi_check_constraints(void)
static void acpi_sleep_run_lps0_dsm(unsigned int func)
static int lps0_device_attach(struct acpi_device *adev, const struct acpi_device_id *not_used)
static int acpi_s2idle_begin(void)
static int acpi_s2idle_prepare(void)
static void acpi_s2idle_wake(void)
static void acpi_s2idle_sync(void)
static void acpi_s2idle_restore(void)
static void acpi_s2idle_end(void)
static void acpi_sleep_suspend_setup(void)
bool acpi_s2idle_wakeup(void)
bool acpi_sleep_no_ec_events(void)
static intacpi_save_bm_rld(void)
static voidacpi_restore_bm_rld(void)
static void acpi_sleep_syscore_init(void)
void __init acpi_no_s4_hw_signature(void)
static int acpi_hibernation_begin(void)
static int acpi_hibernation_enter(void)
static void acpi_hibernation_leave(void)
static void acpi_pm_thaw(void)
static int acpi_hibernation_begin_old(void)
static void acpi_sleep_hibernate_setup(void)
static void acpi_power_off_prepare(void)
static void acpi_power_off(void)
int __init acpi_sleep_init(void)
\n
     36 void
      4 suspend_state_t pm_state
      4 const struct dmi_system_id *d
      3 u32 acpi_state
      1 void *x
      1 void *data
      1 unsigned long code
      1 unsigned int func
      1 u8 sleep_state
      1 struct notifier_block *this
      1 struct device *dev
      1 struct acpi_device *adev
      1 const struct acpi_device_id *not_used
      1 acpi_target_system_state
