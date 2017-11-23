
EXPORT_SYMBOL_GPL(uv_min_hub_revision_id);
EXPORT_SYMBOL_GPL(uv_apicid_hibits);
EXPORT_SYMBOL_GPL(is_uv_system);
EXPORT_SYMBOL_GPL(is_uv_hubless);
EXPORT_SYMBOL_GPL(__uv_hub_info_list);
EXPORT_SYMBOL_GPL(uv_possible_blades);
unsigned long uv_undefined(char *str)
static unsigned long __init uv_early_read_mmr(unsigned long addr)
static inline bool is_GRU_range(u64 start, u64 end)
static bool uv_is_untracked_pat_range(u64 start, u64 end)
static int __init early_get_pnodeid(void)
static void __init uv_tsc_check_sync(void)
static void set_x2apic_bits(void)
static void __init early_get_apic_socketid_shift(void)
static void __init uv_set_apicid_hibit(void)
static int __init uv_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
enum uv_system_type get_uv_system_type(void)
int is_uv_system(void)
int is_uv_hubless(void)
extern int uv_hub_info_version(void)
static int __init parse_mem_block_size(char *ptr)
static __init int adj_blksize(u32 lgre)
static __init void set_block_size(void)
static __init void build_uv_gr_table(void)
static int uv_wakeup_secondary(int phys_apicid, unsigned long start_rip)
static void uv_send_IPI_one(int cpu, int vector)
static void uv_send_IPI_mask(const struct cpumask *mask, int vector)
static void uv_send_IPI_mask_allbutself(const struct cpumask *mask, int vector)
static void uv_send_IPI_allbutself(int vector)
static void uv_send_IPI_all(int vector)
static int uv_apic_id_valid(u32 apicid)
static int uv_apic_id_registered(void)
static void uv_init_apic_ldr(void)
static u32 apic_uv_calc_apicid(unsigned int cpu)
static unsigned int x2apic_get_apic_id(unsigned long x)
static u32 set_apic_id(unsigned int id)
static unsigned int uv_read_apic_id(void)
static int uv_phys_pkg_id(int initial_apicid, int index_msb)
static void uv_send_IPI_self(int vector)
static int uv_probe(void)
static void set_x2apic_extra_bits(int pnode)
static __init void get_lowmem_redirect(unsigned long *base, unsigned long *size)
static __init void map_high(char *id, unsigned long base, int pshift, int bshift, int max_pnode, enum map_type map_type)
static __init void map_gru_distributed(unsigned long c)
static __init void map_gru_high(int max_pnode)
static __init void map_mmr_high(int max_pnode)
static __init void map_mmioh_high_uv34(int index, int min_pnode, int max_pnode)
static __init void map_mmioh_high(int min_pnode, int max_pnode)
static __init void map_low_mmrs(void)
static __init void uv_rtc_init(void)
static void uv_heartbeat(struct timer_list *timer)
static int uv_heartbeat_enable(unsigned int cpu)
static int uv_heartbeat_disable(unsigned int cpu)
static __init void uv_scir_register_cpu_notifier(void)
static __init void uv_scir_register_cpu_notifier(void)
static __init int uv_init_heartbeat(void)
int uv_set_vga_state(struct pci_dev *pdev, bool decode, unsigned int command_bits, u32 flags)
void uv_cpu_init(void)
static void get_mn(struct mn *mnp)
void __init uv_init_hub_info(struct uv_hub_info_s *hi)
static void __init decode_gam_params(unsigned long ptr)
static void __init decode_gam_rng_tbl(unsigned long ptr)
static int __init decode_uv_systab(void)
static __init void boot_init_possible_blades(struct uv_hub_info_s *hub_info)
static void __init build_socket_tables(void)
static void __init uv_system_init_hub(void)
void __init uv_system_init(void)
  25 void
   6 int vector
   5 int max_pnode
   3 unsigned int cpu
   2 unsigned long ptr
   2 u64 start
   2 u64 end
   2 int min_pnode
   2 const struct cpumask *mask
   1 uv_possible_blades
   1 uv_min_hub_revision_id
   1 uv_apicid_hibits
   1 unsigned long x
   1 unsigned long start_rip
   1 unsigned long c
   1 unsigned long base
   1 unsigned long addr
   1 unsigned long *size
   1 unsigned long *base
   1 unsigned int id
   1 unsigned int command_bits
   1 u32 lgre
   1 u32 flags
   1 u32 apicid
   1 struct uv_hub_info_s *hub_info
   1 struct uv_hub_info_s *hi
   1 struct timer_list *timer
   1 struct pci_dev *pdev
   1 struct mn *mnp
   1 is_uv_system
   1 is_uv_hubless
   1 int pshift
   1 int pnode
   1 int phys_apicid
   1 int initial_apicid
   1 int index_msb
   1 int index
   1 int cpu
   1 int bshift
   1 enum map_type map_type
   1 char *str
   1 char *ptr
   1 char *oem_table_id
   1 char *oem_id
   1 char *id
   1 bool decode
   1 __uv_hub_info_list
