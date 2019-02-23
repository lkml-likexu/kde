
\n
void acpi_table_print_madt_entry(struct acpi_subtable_header *header)
static int __init acpi_parse_entries_array(char *id, unsigned long table_size, struct acpi_table_header *table_header, struct acpi_subtable_proc *proc, int proc_num, unsigned int max_entries)
int __init acpi_table_parse_entries_array(char *id, unsigned long table_size, struct acpi_subtable_proc *proc, int proc_num, unsigned int max_entries)
int __init acpi_table_parse_entries(char *id, unsigned long table_size, int entry_id, acpi_tbl_entry_handler handler, unsigned int max_entries)
int __init acpi_table_parse_madt(enum acpi_madt_type id, acpi_tbl_entry_handler handler, unsigned int max_entries)
int __init acpi_table_parse(char *id, acpi_tbl_table_handler handler)
static void __init check_multiple_madt(void)
static void acpi_table_taint(struct acpi_table_header *table)
static u8 __init acpi_table_checksum(u8 *buffer, u32 length)
void __init acpi_table_upgrade(void)
static acpi_status acpi_table_initrd_override(struct acpi_table_header *existing_table, acpi_physical_address *address, u32 *length)
static void __init acpi_table_initrd_scan(void)
pr_info("Table Upgrade: install [%4.4s-%6.6s-%8.8s]\n", table->signature, table->oem_id, table->oem_table_id)
; acpi_os_unmap_memory(table, ACPI_HEADER_SIZE)
; acpi_install_table(acpi_tables_addr + table_offset, TRUE)
; next_table: table_offset += table_length; table_index++;} } static acpi_status acpi_table_initrd_override(struct acpi_table_header *existing_table, acpi_physical_address *address, u32 *table_length)
static void __init acpi_table_initrd_scan(void)
acpi_status acpi_os_physical_table_override(struct acpi_table_header *existing_table, acpi_physical_address *address, u32 *table_length)
acpi_status acpi_os_table_override(struct acpi_table_header *existing_table, struct acpi_table_header **new_table)
int __init acpi_table_init(void)
static int __init acpi_parse_apic_instance(char *str)
static int __init acpi_force_table_verification_setup(char *s)
static int __init acpi_force_32bit_fadt_addr(char *s)
\n
      5 void
      4 unsigned int max_entries
      4 struct acpi_table_header *existing_table
      4 char *id
      3 unsigned long table_size
      3 acpi_physical_address *address
      2 u32 *table_length
      2 struct acpi_subtable_proc *proc
      2 int proc_num
      2 char *s
      2 acpi_tbl_entry_handler handler
      1 u8 *buffer
      1 u32 *length
      1 u32 length
      1 TRUE
      1 "Table Upgrade: install [%4.4s-%6.6s-%8.8s]\n"
      1 table->signature
      1 table->oem_table_id
      1 table->oem_id
      1 table
      1 struct acpi_table_header *table_header
      1 struct acpi_table_header *table
      1 struct acpi_table_header **new_table
      1 struct acpi_subtable_header *header
      1 int entry_id
      1 enum acpi_madt_type id
      1 char *str
      1 acpi_tbl_table_handler handler
      1 acpi_tables_addr + table_offset
      1 ACPI_HEADER_SIZE
