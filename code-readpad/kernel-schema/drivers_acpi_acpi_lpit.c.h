
EXPORT_SYMBOL_GPL(lpit_read_residency_count_address);
\n
static int lpit_read_residency_counter_us(u64 *counter, bool io_mem)
static ssize_t low_power_idle_system_residency_us_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t low_power_idle_cpu_residency_us_show(struct device *dev, struct device_attribute *attr, char *buf)
int lpit_read_residency_count_address(u64 *address)
static void lpit_update_residency(struct lpit_residency_info *info, struct acpi_lpit_native *lpit_native)
static void lpit_process(u64 begin, u64 end)
void acpi_init_lpit(void)
\n
      2 struct device *dev
      2 struct device_attribute *attr
      2 char *buf
      1 void
      1 u64 end
      1 u64 *counter
      1 u64 begin
      1 u64 *address
      1 struct lpit_residency_info *info
      1 struct acpi_lpit_native *lpit_native
      1 lpit_read_residency_count_address
      1 bool io_mem
