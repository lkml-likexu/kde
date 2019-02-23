
\n
static inline void ghes_edac_report_mem_error(int sev, struct cper_sec_mem_err *mem_err)
static inline int ghes_edac_register(struct ghes *ghes, struct device *dev)
static inline void ghes_edac_unregister(struct ghes *ghes)
static inline int acpi_hest_get_version(struct acpi_hest_generic_data *gdata)
static inline void *acpi_hest_get_payload(struct acpi_hest_generic_data *gdata)
static inline int acpi_hest_get_error_length(struct acpi_hest_generic_data *gdata)
static inline int acpi_hest_get_size(struct acpi_hest_generic_data *gdata)
static inline int acpi_hest_get_record_size(struct acpi_hest_generic_data *gdata)
static inline void *acpi_hest_get_next(struct acpi_hest_generic_data *gdata)
\n
      6 struct acpi_hest_generic_data *gdata
      2 struct ghes *ghes
      1 struct device *dev
      1 struct cper_sec_mem_err *mem_err
      1 int sev
