
\n
static void power_saving_mwait_init(void)
static unsigned long cpu_weight[NR_CPUS]; static DECLARE_BITMAP(pad_busy_cpus_bits, NR_CPUS)
; static void round_robin_cpu(unsigned int tsk_index)
static void exit_round_robin(unsigned int tsk_index)
static unsigned int idle_pct = 5;static unsigned int round_robin_time = 1;static int power_saving_thread(void *data)
static struct task_struct *ps_tsks[NR_CPUS]; static unsigned int ps_tsk_num; static int create_power_saving_task(void)
static void destroy_power_saving_task(void)
static void set_power_saving_task_num(unsigned int num)
static void acpi_pad_idle_cpus(unsigned int num_cpus)
static uint32_t acpi_pad_idle_cpus_num(void)
static ssize_t acpi_pad_rrtime_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t acpi_pad_rrtime_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t acpi_pad_idlepct_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t acpi_pad_idlepct_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t acpi_pad_idlecpus_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t acpi_pad_idlecpus_show(struct device *dev, struct device_attribute *attr, char *buf)
static int acpi_pad_add_sysfs(struct acpi_device *device)
static void acpi_pad_remove_sysfs(struct acpi_device *device)
static int acpi_pad_pur(acpi_handle handle)
static void acpi_pad_handle_notify(acpi_handle handle)
static void acpi_pad_notify(acpi_handle handle, u32 event, void *data)
static int acpi_pad_add(struct acpi_device *device)
static int acpi_pad_remove(struct acpi_device *device)
static int __init acpi_pad_init(void)
static void __exit acpi_pad_exit(void)
\n
      6 void
      6 struct device *dev
      6 struct device_attribute *attr
      4 struct acpi_device *device
      3 size_t count
      3 const char *buf
      3 char *buf
      3 acpi_handle handle
      2 void *data
      2 unsigned int tsk_index
      1 unsigned int num_cpus
      1 unsigned int num
      1 u32 event
      1 pad_busy_cpus_bits
      1 NR_CPUS
