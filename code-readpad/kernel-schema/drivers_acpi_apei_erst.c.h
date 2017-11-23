
EXPORT_SYMBOL_GPL(erst_disable);
EXPORT_SYMBOL_GPL(erst_get_record_count);
EXPORT_SYMBOL_GPL(erst_get_record_id_begin);
EXPORT_SYMBOL_GPL(erst_get_record_id_next);
EXPORT_SYMBOL_GPL(erst_get_record_id_end);
EXPORT_SYMBOL_GPL(erst_write);
EXPORT_SYMBOL_GPL(erst_read);
EXPORT_SYMBOL_GPL(erst_clear);
static inline int erst_errno(int command_status)
static int erst_timedout(u64 *t, u64 spin_unit)
static int erst_exec_load_var1(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_load_var2(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_store_var1(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_add(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_subtract(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_add_value(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_subtract_value(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_stall(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_stall_while_true(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_skip_next_instruction_if_true(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_goto(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_set_src_address_base(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_set_dst_address_base(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static int erst_exec_move_data(struct apei_exec_context *ctx, struct acpi_whea_header *entry)
static inline void erst_exec_ctx_init(struct apei_exec_context *ctx)
static int erst_get_erange(struct erst_erange *range)
static ssize_t __erst_get_record_count(void)
ssize_t erst_get_record_count(void)
static int __erst_get_next_record_id(u64 *record_id)
int erst_get_record_id_begin(int *pos)
static int __erst_record_id_cache_add_one(void)
int erst_get_record_id_next(int *pos, u64 *record_id)
static void __erst_record_id_cache_compact(void)
void erst_get_record_id_end(void)
static int __erst_write_to_storage(u64 offset)
static int __erst_read_from_storage(u64 record_id, u64 offset)
static int __erst_clear_from_storage(u64 record_id)
static void pr_unimpl_nvram(void)
static int __erst_write_to_nvram(const struct cper_record_header *record)
static int __erst_read_to_erange_from_nvram(u64 record_id, u64 *offset)
static int __erst_clear_from_nvram(u64 record_id)
int erst_write(const struct cper_record_header *record)
static int __erst_read_to_erange(u64 record_id, u64 *offset)
static ssize_t __erst_read(u64 record_id, struct cper_record_header *record, size_t buflen)
ssize_t erst_read(u64 record_id, struct cper_record_header *record, size_t buflen)
int erst_clear(u64 record_id)
static int __init setup_erst_disable(char *str)
static int erst_check_table(struct acpi_table_erst *erst_tab)
static int erst_open_pstore(struct pstore_info *psi)
static int erst_close_pstore(struct pstore_info *psi)
static ssize_t erst_reader(struct pstore_record *record)
static int erst_writer(struct pstore_record *record)
static int erst_clearer(struct pstore_record *record)
static int __init erst_init(void)
  15 struct apei_exec_context *ctx
  14 struct acpi_whea_header *entry
   8 u64 record_id
   7 void
   3 struct pstore_record *record
   2 u64 offset
   2 u64 *record_id
   2 u64 *offset
   2 struct pstore_info *psi
   2 struct cper_record_header *record
   2 size_t buflen
   2 int *pos
   2 const struct cper_record_header *record
   1 u64 spin_unit
   1 u64 *t
   1 struct erst_erange *range
   1 struct acpi_table_erst *erst_tab
   1 int command_status
   1 erst_write
   1 erst_read
   1 erst_get_record_id_next
   1 erst_get_record_id_end
   1 erst_get_record_id_begin
   1 erst_get_record_count
   1 erst_disable
   1 erst_clear
   1 char *str
