
\n
static inline int __init acpi_sfi_table_parse(char *signature, int (*handler)
(struct acpi_table_header *)
)
return sfi_acpi_table_parse(signature, NULL, NULL, handler)
; } static inline int sfi_acpi_table_parse(char *signature, char *oem_id, char *oem_table_id, int (*handler)
(struct acpi_table_header *)
)
static inline int __init acpi_sfi_table_parse(char *signature, int (*handler)
(struct acpi_table_header *)
)
\n
      3 struct acpi_table_header *
      3 int *handler
      3 char *signature
      2 NULL
      1 signature
      1 handler
      1 char *oem_table_id
      1 char *oem_id
