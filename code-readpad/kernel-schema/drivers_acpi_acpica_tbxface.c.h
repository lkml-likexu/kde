
\n
acpi_status acpi_allocate_root_table(u32 initial_table_count)
acpi_status ACPI_INIT_FUNCTION acpi_initialize_tables(struct acpi_table_desc *initial_table_array, u32 initial_table_count, u8 allow_resize)
acpi_status ACPI_INIT_FUNCTION acpi_reallocate_root_table(void)
acpi_status acpi_get_table_header(char *signature, u32 instance, struct acpi_table_header *out_table_header)
acpi_status acpi_get_table(char *signature, u32 instance, struct acpi_table_header ** out_table)
void acpi_put_table(struct acpi_table_header *table)
acpi_status acpi_get_table_by_index(u32 table_index, struct acpi_table_header **out_table)
acpi_status acpi_install_table_handler(acpi_table_handler handler, void *context)
acpi_status acpi_remove_table_handler(acpi_table_handler handler)
\n
      2 u32 instance
      2 u32 initial_table_count
      2 char *signature
      2 acpi_table_handler handler
      1 void *context
      1 void
      1 u8 allow_resize
      1 u32 table_index
      1 struct acpi_table_header *table
      1 struct acpi_table_header *out_table_header
      1 struct acpi_table_header **out_table
      1 struct acpi_table_header ** out_table
      1 struct acpi_table_desc *initial_table_array
