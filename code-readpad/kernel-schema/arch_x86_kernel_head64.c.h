
\n
static void __head *fixup_pointer(void *ptr, unsigned long physaddr)
static unsigned long __head *fixup_long(void *ptr, unsigned long physaddr)
static unsigned int __head *fixup_int(void *ptr, unsigned long physaddr)
static bool __head check_la57_support(unsigned long physaddr)
return true; } static bool __head check_la57_support(unsigned long physaddr)
unsigned long __head __startup_64(unsigned long physaddr, struct boot_params *bp)
unsigned long __startup_secondary_64(void)
static void __init reset_early_page_tables(void)
int __init __early_make_pgtable(unsigned long address, pmdval_t pmd)
int __init early_make_pgtable(unsigned long address)
static void __init clear_bss(void)
static unsigned long get_cmd_line_ptr(void)
static void __init copy_bootdata(char *real_mode_data)
asmlinkage __visible void __init x86_64_start_kernel(char * real_mode_data)
void __init x86_64_start_reservations(char *real_mode_data)
\n
      6 unsigned long physaddr
      4 void
      3 void *ptr
      2 unsigned long address
      2 char *real_mode_data
      1 struct boot_params *bp
      1 pmdval_t pmd
      1 char * real_mode_data
