
EXPORT_SYMBOL_GPL(arch_phys_wc_index);
\n
static bool mtrr_enabled(void)
void __init set_mtrr_ops(const struct mtrr_ops *ops)
static int have_wrcomb(void)
static void __init set_num_var_ranges(void)
static void __init init_table(void)
static int mtrr_rendezvous_handler(void *info)
static inline int types_compatible(mtrr_type type1, mtrr_type type2)
static void set_mtrr(unsigned int reg, unsigned long base, unsigned long size, mtrr_type type)
static void set_mtrr_cpuslocked(unsigned int reg, unsigned long base, unsigned long size, mtrr_type type)
static void set_mtrr_from_inactive_cpu(unsigned int reg, unsigned long base, unsigned long size, mtrr_type type)
int mtrr_add_page(unsigned long base, unsigned long size, unsigned int type, bool increment)
static int mtrr_check(unsigned long base, unsigned long size)
int mtrr_add(unsigned long base, unsigned long size, unsigned int type, bool increment)
int mtrr_del_page(int reg, unsigned long base, unsigned long size)
int mtrr_del(int reg, unsigned long base, unsigned long size)
int arch_phys_wc_add(unsigned long base, unsigned long size)
void arch_phys_wc_del(int handle)
int arch_phys_wc_index(int handle)
static void __init init_ifs(void)
static int mtrr_save(void)
static void mtrr_restore(void)
define SIZE_OR_MASK_BITS(n)
(~((1ULL << ((n)
- PAGE_SHIFT)
)
- 1)
)
void __init mtrr_bp_init(void)
void mtrr_ap_init(void)
void mtrr_save_state(void)
void set_mtrr_aps_delayed_init(void)
void mtrr_aps_init(void)
void mtrr_bp_restore(void)
static int __init mtrr_init_finialize(void)
\n
     14 void
      9 unsigned long size
      9 unsigned long base
      3 unsigned int reg
      3 mtrr_type type
      2 unsigned int type
      2 int reg
      2 int handle
      2 bool increment
      1 void *info
      1 n
      1 mtrr_type type2
      1 mtrr_type type1
      1 const struct mtrr_ops *ops
      1 arch_phys_wc_index
      1 ~1ULL << n
