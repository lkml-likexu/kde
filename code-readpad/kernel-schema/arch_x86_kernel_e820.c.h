
EXPORT_SYMBOL_GPL(e820__mapped_any);
\n
bool e820__mapped_any(u64 start, u64 end, enum e820_type type)
static struct e820_entry *__e820__mapped_all(u64 start, u64 end, enum e820_type type)
bool __init e820__mapped_all(u64 start, u64 end, enum e820_type type)
int e820__get_entry_type(u64 start, u64 end)
static void __init __e820__range_add(struct e820_table *table, u64 start, u64 size, enum e820_type type)
void __init e820__range_add(u64 start, u64 size, enum e820_type type)
static void __init e820_print_type(enum e820_type type)
void __init e820__print_table(char *who)
static int __init cpcompare(const void *a, const void *b)
int __init e820__update_table(struct e820_table *table)
static int __init __append_e820_table(struct boot_e820_entry *entries, u32 nr_entries)
static int __init append_e820_table(struct boot_e820_entry *entries, u32 nr_entries)
static u64 __init __e820__range_update(struct e820_table *table, u64 start, u64 size, enum e820_type old_type, enum e820_type new_type)
u64 __init e820__range_update(u64 start, u64 size, enum e820_type old_type, enum e820_type new_type)
static u64 __init e820__range_update_kexec(u64 start, u64 size, enum e820_type old_type, enum e820_typenew_type)
u64 __init e820__range_remove(u64 start, u64 size, enum e820_type old_type, bool check_type)
void __init e820__update_table_print(void)
static void __init e820__update_table_kexec(void)
static int __init e820_search_gap(unsigned long *gapstart, unsigned long *gapsize)
__init void e820__setup_pci_gap(void)
__init void e820__reallocate_tables(void)
void __init e820__memory_setup_extended(u64 phys_addr, u32 data_len)
void __init e820__register_nosave_regions(unsigned long limit_pfn)
static int __init e820__register_nvs_regions(void)
u64 __init e820__memblock_alloc_reserved(u64 size, u64 align)
static unsigned long __init e820_end_pfn(unsigned long limit_pfn, enum e820_type type)
unsigned long __init e820__end_of_ram_pfn(void)
unsigned long __init e820__end_of_low_ram_pfn(void)
static void __init early_panic(char *msg)
static int __init parse_memopt(char *p)
static int __init parse_memmap_one(char *p)
static int __init parse_memmap_opt(char *str)
void __init e820__reserve_setup_data(void)
void __init e820__finish_early_params(void)
static const char *__init e820_type_to_string(struct e820_entry *entry)
static unsigned long __init e820_type_to_iomem_type(struct e820_entry *entry)
static unsigned long __init e820_type_to_iores_desc(struct e820_entry *entry)
static bool __init do_mark_busy(enum e820_type type, struct resource *res)
void __init e820__reserve_resources(void)
static unsigned long __init ram_alignment(resource_size_t pos)
void __init e820__reserve_resources_late(void)
char *__init e820__memory_setup_default(void)
void __init e820__memory_setup(void)
void __init e820__memblock_setup(void)
\n
     14 void
     10 u64 start
      8 enum e820_type type
      7 u64 size
      4 u64 end
      4 enum e820_type old_type
      3 struct e820_table *table
      3 struct e820_entry *entry
      2 unsigned long limit_pfn
      2 u32 nr_entries
      2 struct boot_e820_entry *entries
      2 enum e820_type new_type
      2 char *p
      1 unsigned long *gapstart
      1 unsigned long *gapsize
      1 u64 phys_addr
      1 u64 align
      1 u32 data_len
      1 struct resource *res
      1 resource_size_t pos
      1 enum e820_typenew_type
      1 e820__mapped_any
      1 const void *b
      1 const void *a
      1 char *who
      1 char *str
      1 char *msg
      1 bool check_type
