
EXPORT_SYMBOL_GPL(hest_disable);
EXPORT_SYMBOL_GPL(apei_hest_parse);
static int hest_esrc_len(struct acpi_hest_header *hest_hdr)
int apei_hest_parse(apei_hest_func_t func, void *data)
static int __init hest_parse_cmc(struct acpi_hest_header *hest_hdr, void *data)
static int __init hest_parse_ghes_count(struct acpi_hest_header *hest_hdr, void *data)
static int __init hest_parse_ghes(struct acpi_hest_header *hest_hdr, void *data)
static int __init hest_ghes_dev_register(unsigned int ghes_count)
static int __init setup_hest_disable(char *str)
void __init acpi_hest_init(void)
   4 void *data
   4 struct acpi_hest_header *hest_hdr
   1 void
   1 unsigned int ghes_count
   1 hest_disable
   1 char *str
   1 apei_hest_parse
   1 apei_hest_func_t func
