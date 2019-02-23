
EXPORT_SYMBOL_GPL(acpi_has_watchdog);
\n
static bool acpi_watchdog_uses_rtc(const struct acpi_table_wdat *wdat)
return false; } static bool acpi_watchdog_uses_rtc(const struct acpi_table_wdat *wdat)
static const struct acpi_table_wdat *acpi_watchdog_get_wdat(void)
bool acpi_has_watchdog(void)
void __init acpi_watchdog_init(void)
\n
      3 void
      2 const struct acpi_table_wdat *wdat
      1 acpi_has_watchdog
