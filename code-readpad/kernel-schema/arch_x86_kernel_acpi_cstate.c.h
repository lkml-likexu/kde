
EXPORT_SYMBOL_GPL(acpi_processor_ffh_cstate_probe);
EXPORT_SYMBOL_GPL(acpi_processor_ffh_cstate_enter);
void acpi_processor_power_init_bm_check(struct acpi_processor_flags *flags, unsigned int cpu)
static long acpi_processor_ffh_cstate_probe_cpu(void *_cx)
int acpi_processor_ffh_cstate_probe(unsigned int cpu, struct acpi_processor_cx *cx, struct acpi_power_register *reg)
void __cpuidle acpi_processor_ffh_cstate_enter(struct acpi_processor_cx *cx)
static int __init ffh_cstate_init(void)
static void __exit ffh_cstate_exit(void)
   2 void
   2 unsigned int cpu
   2 struct acpi_processor_cx *cx
   1 void *_cx
   1 struct acpi_processor_flags *flags
   1 struct acpi_power_register *reg
   1 acpi_processor_ffh_cstate_probe
   1 acpi_processor_ffh_cstate_enter
