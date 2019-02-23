
\n
static inline bool cpu_signatures_match(unsigned int s1, unsigned int p1, unsigned int s2, unsigned int p2)
static int find_matching_signature(void *mc, unsigned int csig, int cpf)
static int has_newer_microcode(void *mc, unsigned int csig, int cpf, int new_rev)
static bool microcode_matches(struct microcode_header_intel *mc_header, unsigned long sig)
static struct ucode_patch *memdup_patch(void *data, unsigned int size)
static void save_microcode_patch(void *data, unsigned int size)
static int microcode_sanity_check(void *mc, int print_err)
static struct microcode_intel * scan_microcode(void *data, size_t size, struct ucode_cpu_info *uci, bool save)
static int collect_cpu_info_early(struct ucode_cpu_info *uci)
static void show_saved_mc(void)
static void save_mc_for_early(u8 *mc, unsigned int size)
static bool load_builtin_intel_microcode(struct cpio_data *cp)
static void print_ucode_info(struct ucode_cpu_info *uci, unsigned int date)
void show_ucode_info_early(void)
static void print_ucode(struct ucode_cpu_info *uci)
static inline void print_ucode(struct ucode_cpu_info *uci)
static int apply_microcode_early(struct ucode_cpu_info *uci, bool early)
int __init save_microcode_in_initrd_intel(void)
static struct microcode_intel *__load_ucode_intel(struct ucode_cpu_info *uci)
void __init load_ucode_intel_bsp(void)
void load_ucode_intel_ap(void)
static struct microcode_intel *find_patch(struct ucode_cpu_info *uci)
void reload_ucode_intel(void)
static int collect_cpu_info(int cpu_num, struct cpu_signature *csig)
static enum ucode_state apply_microcode_intel(int cpu)
static enum ucode_state generic_load_microcode(int cpu, void *data, size_t size, int (*get_ucode_data)
(void *, const void *, size_t)
)
static int get_ucode_fw(void *to, const void *from, size_t n)
static bool is_blacklisted(unsigned int cpu)
static enum ucode_state request_microcode_fw(int cpu, struct device *device, bool refresh_fw)
static int get_ucode_user(void *to, const void *from, size_t n)
static enum ucode_state request_microcode_user(int cpu, const void __user *buf, size_t size)
static int __init calc_llc_size_per_core(struct cpuinfo_x86 *c)
struct microcode_ops * __init init_intel_microcode(void)
\n
      8 struct ucode_cpu_info *uci
      7 void
      4 void *data
      4 int cpu
      3 void *mc
      3 unsigned int size
      3 size_t size
      2 void *to
      2 unsigned int csig
      2 size_t n
      2 int cpf
      2 const void *from
      1 void *
      1 unsigned long sig
      1 unsigned int s2
      1 unsigned int s1
      1 unsigned int p2
      1 unsigned int p1
      1 unsigned int date
      1 unsigned int cpu
      1 u8 *mc
      1 struct microcode_header_intel *mc_header
      1 struct device *device
      1 struct cpu_signature *csig
      1 struct cpuinfo_x86 *c
      1 struct cpio_data *cp
      1 size_t
      1 int print_err
      1 int new_rev
      1 int *get_ucode_data
      1 int cpu_num
      1 const void __user *buf
      1 const void *
      1 bool save
      1 bool refresh_fw
      1 bool early
