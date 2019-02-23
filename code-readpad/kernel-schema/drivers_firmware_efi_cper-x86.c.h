
\n
static enum err_types cper_get_err_type(const guid_t *err_type)
static inline void print_bool(char *str, const char *pfx, u64 check, u64 bit)
static void print_err_info_ms(const char *pfx, u16 validation_bits, u64 check)
static void print_err_info(const char *pfx, u8 err_type, u64 check)
void cper_print_proc_ia(const char *pfx, const struct cper_sec_proc_ia *proc)
\n
      4 const char *pfx
      3 u64 check
      1 u8 err_type
      1 u64 bit
      1 u16 validation_bits
      1 const struct cper_sec_proc_ia *proc
      1 const guid_t *err_type
      1 char *str
