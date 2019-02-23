
EXPORT_SYMBOL_GPL(opal_message_notifier_register);
EXPORT_SYMBOL_GPL(opal_message_notifier_unregister);
EXPORT_SYMBOL_GPL(opal_invalid_call);
EXPORT_SYMBOL_GPL(opal_xscom_read);
EXPORT_SYMBOL_GPL(opal_xscom_write);
EXPORT_SYMBOL_GPL(opal_ipmi_send);
EXPORT_SYMBOL_GPL(opal_ipmi_recv);
EXPORT_SYMBOL_GPL(opal_flash_read);
EXPORT_SYMBOL_GPL(opal_flash_write);
EXPORT_SYMBOL_GPL(opal_flash_erase);
EXPORT_SYMBOL_GPL(opal_prd_msg);
EXPORT_SYMBOL_GPL(opal_check_token);
EXPORT_SYMBOL_GPL(opal_poll_events);
EXPORT_SYMBOL_GPL(opal_rtc_read);
EXPORT_SYMBOL_GPL(opal_rtc_write);
EXPORT_SYMBOL_GPL(opal_tpo_read);
EXPORT_SYMBOL_GPL(opal_tpo_write);
EXPORT_SYMBOL_GPL(opal_i2c_request);
EXPORT_SYMBOL_GPL(opal_leds_get_ind);
EXPORT_SYMBOL_GPL(opal_leds_set_ind);
EXPORT_SYMBOL_GPL(opal_write_oppanel_async);
EXPORT_SYMBOL_GPL(opal_int_set_mfrr);
EXPORT_SYMBOL_GPL(opal_int_eoi);
EXPORT_SYMBOL_GPL(opal_error_code);
\n
void opal_configure_cores(void)
int __init early_init_dt_scan_opal(unsigned long node, const char *uname, int depth, void *data)
int __init early_init_dt_scan_recoverable_ranges(unsigned long node, const char *uname, int depth, void *data)
static int __init opal_register_exception_handlers(void)
int opal_message_notifier_register(enum opal_msg_type msg_type, struct notifier_block *nb)
int opal_message_notifier_unregister(enum opal_msg_type msg_type, struct notifier_block *nb)
static void opal_message_do_notify(uint32_t msg_type, void *msg)
static void opal_handle_message(void)
static irqreturn_t opal_message_notify(int irq, void *data)
static int __init opal_message_init(void)
int opal_get_chars(uint32_t vtermno, char *buf, int count)
static int __opal_put_chars(uint32_t vtermno, const char *data, int total_len, bool atomic)
int opal_put_chars(uint32_t vtermno, const char *data, int total_len)
int opal_put_chars_atomic(uint32_t vtermno, const char *data, int total_len)
static s64 __opal_flush_console(uint32_t vtermno)
int opal_flush_console(uint32_t vtermno)
int opal_flush_chars(uint32_t vtermno, bool wait)
static int opal_recover_mce(struct pt_regs *regs, struct machine_check_event *evt)
void __noreturn pnv_platform_error_reboot(struct pt_regs *regs, const char *msg)
int opal_machine_check(struct pt_regs *regs)
int opal_hmi_exception_early(struct pt_regs *regs)
int opal_handle_hmi_exception(struct pt_regs *regs)
static uint64_t find_recovery_address(uint64_t nip)
bool opal_mce_check_early_recovery(struct pt_regs *regs)
static int opal_sysfs_init(void)
static ssize_t symbol_map_read(struct file *fp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
static void opal_export_symmap(void)
static ssize_t export_attr_read(struct file *fp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
static void opal_export_attrs(void)
static void __init opal_dump_region_init(void)
static void opal_pdev_init(const char *compatible)
static void __init opal_imc_init_dev(void)
static int kopald(void *unused)
void opal_wake_poller(void)
static void opal_init_heartbeat(void)
static int __init opal_init(void)
void opal_shutdown(void)
struct opal_sg_list *opal_vmalloc_to_sg_list(void *vmalloc_addr, unsigned long vmalloc_size)
void opal_free_sg_list(struct opal_sg_list *sg)
int opal_error_code(int rc)
void powernv_set_nmmu_ptcr(unsigned long ptcr)
\n
     13 void
      7 uint32_t vtermno
      6 struct pt_regs *regs
      3 void *data
      3 int total_len
      3 const char *data
      3 char *buf
      2 unsigned long node
      2 struct notifier_block *nb
      2 struct kobject *kobj
      2 struct file *fp
      2 struct bin_attribute *bin_attr
      2 size_t count
      2 loff_t off
      2 int depth
      2 enum opal_msg_type msg_type
      2 const char *uname
      1 void *vmalloc_addr
      1 void *unused
      1 void *msg
      1 unsigned long vmalloc_size
      1 unsigned long ptcr
      1 uint64_t nip
      1 uint32_t msg_type
      1 struct opal_sg_list *sg
      1 struct machine_check_event *evt
      1 opal_xscom_write
      1 opal_xscom_read
      1 opal_write_oppanel_async
      1 opal_tpo_write
      1 opal_tpo_read
      1 opal_rtc_write
      1 opal_rtc_read
      1 opal_prd_msg
      1 opal_poll_events
      1 opal_message_notifier_unregister
      1 opal_message_notifier_register
      1 opal_leds_set_ind
      1 opal_leds_get_ind
      1 opal_ipmi_send
      1 opal_ipmi_recv
      1 opal_invalid_call
      1 opal_int_set_mfrr
      1 opal_int_eoi
      1 opal_i2c_request
      1 opal_flash_write
      1 opal_flash_read
      1 opal_flash_erase
      1 opal_error_code
      1 opal_check_token
      1 int rc
      1 int irq
      1 int count
      1 const char *msg
      1 const char *compatible
      1 bool wait
      1 bool atomic
