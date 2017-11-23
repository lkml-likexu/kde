
static int __init mpf_checksum(unsigned char *mp, int len)
int __init default_mpc_apic_id(struct mpc_cpu *m)
static void __init MP_processor_info(struct mpc_cpu *m)
void __init default_mpc_oem_bus_info(struct mpc_bus *m, char *str)
static void __init MP_bus_info(struct mpc_bus *m)
static void __init MP_ioapic_info(struct mpc_ioapic *m)
static void __init print_mp_irq_info(struct mpc_intsrc *mp_irq)
static void __init MP_lintsrc_info(struct mpc_lintsrc *m)
static int __init smp_check_mpc(struct mpc_table *mpc, char *oem, char *str)
static void skip_entry(unsigned char **ptr, int *count, int size)
static void __init smp_dump_mptable(struct mpc_table *mpc, unsigned char *mpt)
static int __init smp_read_mpc(struct mpc_table *mpc, unsigned early)
static int __init ELCR_trigger(unsigned int irq)
static void __init construct_default_ioirq_mptable(int mpc_default_type)
static void __init construct_ioapic_table(int mpc_default_type)
static inline void __init construct_default_ISA_mptable(int mpc_default_type)
static unsigned long __init get_mpc_size(unsigned long physptr)
static int __init check_physptr(struct mpf_intel *mpf, unsigned int early)
void __init default_get_smp_config(unsigned int early)
static void __init smp_reserve_memory(struct mpf_intel *mpf)
static int __init smp_scan_config(unsigned long base, unsigned long length)
void __init default_find_smp_config(void)
static int__init get_MP_intsrc_index(struct mpc_intsrc *m)
static void __init check_irq_src(struct mpc_intsrc *m, int *nr_m_spare)
static int __init check_slot(unsigned long mpc_new_phys, unsigned long mpc_new_length, int count)
static int__init replace_intsrc_all(struct mpc_table *mpc, unsigned long mpc_new_phys, unsigned long mpc_new_length)
static int __init update_mptable_setup(char *str)
static int __initdata alloc_mptable; static int __init parse_alloc_mptable_opt(char *p)
void __init e820__memblock_alloc_reserved_mpc_new(void)
static int __init update_mp_table(void)
   4 struct mpc_table *mpc
   3 void
   3 int mpc_default_type
   3 char *str
   2 unsigned long mpc_new_phys
   2 unsigned long mpc_new_length
   2 unsigned int early
   2 struct mpf_intel *mpf
   2 struct mpc_intsrc *m
   2 struct mpc_cpu *m
   2 struct mpc_bus *m
   1 unsigned long physptr
   1 unsigned long length
   1 unsigned long base
   1 unsigned int irq
   1 unsigned early
   1 unsigned char *mpt
   1 unsigned char *mp
   1 unsigned char **ptr
   1 struct mpc_lintsrc *m
   1 struct mpc_ioapic *m
   1 struct mpc_intsrc *mp_irq
   1 int size
   1 int len
   1 int count
   1 int *nr_m_spare
   1 int *count
   1 char *p
   1 char *oem
