
\n
static void einj_exec_ctx_init(struct apei_exec_context *ctx)
static int __einj_get_available_error_type(u32 *type)
static int einj_get_available_error_type(u32 *type)
static int einj_timedout(u64 *t)
static void check_vendor_extension(u64 paddr, struct set_error_type_with_address *v5param)
static void *einj_get_parameter_address(void)
static int einj_check_trigger_header(struct acpi_einj_trigger *trigger_tab)
static struct acpi_generic_address *einj_get_trigger_parameter_region(struct acpi_einj_trigger *trigger_tab, u64 param1, u64 param2)
return NULL; }static int __einj_error_trigger(u64 trigger_paddr, u32 type, u64 param1, u64 param2)
static int __einj_error_inject(u32 type, u32 flags, u64 param1, u64 param2, u64 param3, u64 param4)
static int einj_error_inject(u32 type, u32 flags, u64 param1, u64 param2, u64 param3, u64 param4)
static int available_error_type_show(struct seq_file *m, void *v)
static int error_type_get(void *data, u64 *val)
static int error_type_set(void *data, u64 val)
static int error_inject_set(void *data, u64 val)
static int einj_check_table(struct acpi_table_einj *einj_tab)
static int __init einj_init(void)
static void __exit einj_exit(void)
\n
      4 u64 param2
      4 u64 param1
      3 void *data
      3 void
      3 u32 type
      2 u64 val
      2 u64 param4
      2 u64 param3
      2 u32 *type
      2 u32 flags
      2 struct acpi_einj_trigger *trigger_tab
      1 void *v
      1 u64 *val
      1 u64 trigger_paddr
      1 u64 *t
      1 u64 paddr
      1 struct set_error_type_with_address *v5param
      1 struct seq_file *m
      1 struct apei_exec_context *ctx
      1 struct acpi_table_einj *einj_tab
