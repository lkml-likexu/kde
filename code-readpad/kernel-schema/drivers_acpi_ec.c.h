
EXPORT_SYMBOL_GPL(acpi_ec_add_query_handler);
EXPORT_SYMBOL_GPL(acpi_ec_remove_query_handler);
static bool acpi_ec_started(struct acpi_ec *ec)
static bool acpi_ec_event_enabled(struct acpi_ec *ec)
static bool acpi_ec_flushed(struct acpi_ec *ec)
static inline u8 acpi_ec_read_status(struct acpi_ec *ec)
static inline u8 acpi_ec_read_data(struct acpi_ec *ec)
static inline void acpi_ec_write_cmd(struct acpi_ec *ec, u8 command)
static inline void acpi_ec_write_data(struct acpi_ec *ec, u8 data)
static const char *acpi_ec_cmd_string(u8 cmd)
static inline bool acpi_ec_is_gpe_raised(struct acpi_ec *ec)
static inline void acpi_ec_enable_gpe(struct acpi_ec *ec, bool open)
static inline void acpi_ec_disable_gpe(struct acpi_ec *ec, bool close)
static inline void acpi_ec_clear_gpe(struct acpi_ec *ec)
static void acpi_ec_submit_request(struct acpi_ec *ec)
static void acpi_ec_complete_request(struct acpi_ec *ec)
static void acpi_ec_mask_gpe(struct acpi_ec *ec)
static void acpi_ec_unmask_gpe(struct acpi_ec *ec)
static bool acpi_ec_submit_flushable_request(struct acpi_ec *ec)
static void acpi_ec_submit_query(struct acpi_ec *ec)
static void acpi_ec_complete_query(struct acpi_ec *ec)
static inline void __acpi_ec_enable_event(struct acpi_ec *ec)
static inline void __acpi_ec_disable_event(struct acpi_ec *ec)
static void acpi_ec_enable_event(struct acpi_ec *ec)
static bool acpi_ec_query_flushed(struct acpi_ec *ec)
static void __acpi_ec_flush_event(struct acpi_ec *ec)
static void acpi_ec_disable_event(struct acpi_ec *ec)
void acpi_ec_flush_work(void)
static bool acpi_ec_guard_event(struct acpi_ec *ec)
static int ec_transaction_polled(struct acpi_ec *ec)
static int ec_transaction_completed(struct acpi_ec *ec)
static inline void ec_transaction_transition(struct acpi_ec *ec, unsigned long flag)
static void advance_transaction(struct acpi_ec *ec)
static void start_transaction(struct acpi_ec *ec)
static int ec_guard(struct acpi_ec *ec)
static int ec_poll(struct acpi_ec *ec)
static int acpi_ec_transaction_unlocked(struct acpi_ec *ec, struct transaction *t)
static int acpi_ec_transaction(struct acpi_ec *ec, struct transaction *t)
static int acpi_ec_burst_enable(struct acpi_ec *ec)
static int acpi_ec_burst_disable(struct acpi_ec *ec)
static int acpi_ec_read(struct acpi_ec *ec, u8 address, u8 *data)
static int acpi_ec_write(struct acpi_ec *ec, u8 address, u8 data)
int ec_read(u8 addr, u8 *val)
int ec_write(u8 addr, u8 val)
int ec_transaction(u8 command, const u8 *wdata, unsigned wdata_len, u8 *rdata, unsigned rdata_len)
acpi_handle ec_get_handle(void)
static void acpi_ec_start(struct acpi_ec *ec, bool resuming)
static bool acpi_ec_stopped(struct acpi_ec *ec)
static void acpi_ec_stop(struct acpi_ec *ec, bool suspending)
static void acpi_ec_enter_noirq(struct acpi_ec *ec)
static void acpi_ec_leave_noirq(struct acpi_ec *ec)
void acpi_ec_block_transactions(void)
void acpi_ec_unblock_transactions(void)
void acpi_ec_dispatch_gpe(void)
static struct acpi_ec_query_handler * acpi_ec_get_query_handler(struct acpi_ec_query_handler *handler)
static struct acpi_ec_query_handler * acpi_ec_get_query_handler_by_value(struct acpi_ec *ec, u8 value)
static void acpi_ec_query_handler_release(struct kref *kref)
static void acpi_ec_put_query_handler(struct acpi_ec_query_handler *handler)
int acpi_ec_add_query_handler(struct acpi_ec *ec, u8 query_bit, acpi_handle handle, acpi_ec_query_func func, void *data)
static void acpi_ec_remove_query_handlers(struct acpi_ec *ec, bool remove_all, u8 query_bit)
void acpi_ec_remove_query_handler(struct acpi_ec *ec, u8 query_bit)
static struct acpi_ec_query *acpi_ec_create_query(u8 *pval)
static void acpi_ec_delete_query(struct acpi_ec_query *q)
static void acpi_ec_event_processor(struct work_struct *work)
static int acpi_ec_query(struct acpi_ec *ec, u8 *data)
static void acpi_ec_check_event(struct acpi_ec *ec)
static void acpi_ec_event_handler(struct work_struct *work)
static u32 acpi_ec_gpe_handler(acpi_handle gpe_device, u32 gpe_number, void *data)
static acpi_status acpi_ec_space_handler(u32 function, acpi_physical_address address, u32 bits, u64 *value64, void *handler_context, void *region_context)
static void acpi_ec_free(struct acpi_ec *ec)
static struct acpi_ec *acpi_ec_alloc(void)
static acpi_status acpi_ec_register_query_methods(acpi_handle handle, u32 level, void *context, void **return_value)
static acpi_status ec_parse_device(acpi_handle handle, u32 Level, void *context, void **retval)
static int ec_install_handlers(struct acpi_ec *ec, bool handle_events)
static void ec_remove_handlers(struct acpi_ec *ec)
static int acpi_ec_setup(struct acpi_ec *ec, bool handle_events)
static int acpi_config_boot_ec(struct acpi_ec *ec, acpi_handle handle, bool handle_events, bool is_ecdt)
static bool acpi_ec_ecdt_get_handle(acpi_handle *phandle)
static bool acpi_is_boot_ec(struct acpi_ec *ec)
static int acpi_ec_add(struct acpi_device *device)
static int acpi_ec_remove(struct acpi_device *device)
static acpi_status ec_parse_io_ports(struct acpi_resource *resource, void *context)
int __init acpi_ec_dsdt_probe(void)
static int __init acpi_ec_ecdt_start(void)
static int ec_flag_query_handshake(const struct dmi_system_id *id)
static int ec_correct_ecdt(const struct dmi_system_id *id)
static int ec_honor_ecdt_gpe(const struct dmi_system_id *id)
int __init acpi_ec_ecdt_probe(void)
static int acpi_ec_suspend(struct device *dev)
static int acpi_ec_suspend_noirq(struct device *dev)
static int acpi_ec_resume_noirq(struct device *dev)
static int acpi_ec_resume(struct device *dev)
static int param_set_event_clearing(const char *val, const struct kernel_param *kp)
static int param_get_event_clearing(char *buffer, const struct kernel_param *kp)
static inline int acpi_ec_query_init(void)
static inline void acpi_ec_query_exit(void)
int __init acpi_ec_init(void)
static void __exit acpi_ec_exit(void)
  55 struct acpi_ec *ec
  13 void
   4 struct device *dev
   4 acpi_handle handle
   3 void *context
   3 u8 query_bit
   3 const struct dmi_system_id *id
   3 bool handle_events
   2 void *data
   2 u8 data
   2 u8 command
   2 u8 address
   2 u8 addr
   2 u8 *data
   2 struct work_struct *work
   2 struct transaction *t
   2 struct acpi_ec_query_handler *handler
   2 struct acpi_device *device
   2 const struct kernel_param *kp
   1 void *region_context
   1 void *handler_context
   1 void **retval
   1 void **return_value
   1 unsigned wdata_len
   1 unsigned rdata_len
   1 unsigned long flag
   1 u8 value
   1 u8 val
   1 u8 cmd
   1 u8 *val
   1 u8 *rdata
   1 u8 *pval
   1 u64 *value64
   1 u32 level
   1 u32 gpe_number
   1 u32 function
   1 u32 bits
   1 u32 Level
   1 struct kref *kref
   1 struct acpi_resource *resource
   1 struct acpi_ec_query *q
   1 const u8 *wdata
   1 const char *val
   1 char *buffer
   1 bool suspending
   1 bool resuming
   1 bool remove_all
   1 bool open
   1 bool is_ecdt
   1 bool close
   1 acpi_physical_address address
   1 acpi_handle gpe_device
   1 acpi_handle *phandle
   1 acpi_ec_remove_query_handler
   1 acpi_ec_query_func func
   1 acpi_ec_add_query_handler
