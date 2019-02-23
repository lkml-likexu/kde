
\n
static int acpi_lpat_raw_to_temp(struct acpi_lpat_conversion_table *lpat_table, int raw)
static int acpi_lpat_temp_to_raw(struct acpi_lpat_conversion_table *lpat_table, int temp)
static struct acpi_lpat_conversion_table *acpi_lpat_get_conversion_table(acpi_handle handle)
static void acpi_lpat_free_conversion_table(struct acpi_lpat_conversion_table*lpat_table)
\n
      2 struct acpi_lpat_conversion_table *lpat_table
      1 struct acpi_lpat_conversion_table*lpat_table
      1 int temp
      1 int raw
      1 acpi_handle handle
