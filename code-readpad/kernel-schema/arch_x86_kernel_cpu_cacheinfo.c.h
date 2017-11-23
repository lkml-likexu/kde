
static const struct _cache_table cache_table[] = static void amd_cpuid4(int leaf, union _cpuid4_leaf_eax *eax, union _cpuid4_leaf_ebx *ebx, union _cpuid4_leaf_ecx *ecx)
static void amd_calc_l3_indices(struct amd_northbridge *nb)
static int amd_get_l3_disable_slot(struct amd_northbridge *nb, unsigned slot)
static ssize_t show_cache_disable(struct cacheinfo *this_leaf, char *buf, unsigned int slot)
define SHOW_CACHE_DISABLE(slot)
\ static ssize_t\ cache_disable_slot_show(struct device *dev, \struct device_attribute *attr, char *buf)
\ static void amd_l3_disable_index(struct amd_northbridge *nb, int cpu, unsigned slot, unsigned long idx)
static int amd_set_l3_disable_slot(struct amd_northbridge *nb, int cpu, unsigned slot, unsigned long index)
static ssize_t store_cache_disable(struct cacheinfo *this_leaf, const char *buf, size_t count, unsigned int slot)
define STORE_CACHE_DISABLE(slot)
\ static ssize_t\ cache_disable_slot_store(struct device *dev, \ struct device_attribute *attr, \ const char *buf, size_t count)
\ static ssize_t subcaches_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t subcaches_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static umode_t cache_private_attrs_is_visible(struct kobject *kobj, struct attribute *attr, int unused)
static void init_amd_l3_attrs(void)
const struct attribute_group * cache_get_priv_group(struct cacheinfo *this_leaf)
static void amd_init_l3_cache(struct _cpuid4_info_regs *this_leaf, int index)
static int cpuid4_cache_lookup_regs(int index, struct _cpuid4_info_regs *this_leaf)
static int find_num_cache_leaves(struct cpuinfo_x86 *c)
void cacheinfo_amd_init_llc_id(struct cpuinfo_x86 *c, int cpu, u8 node_id)
void cacheinfo_hygon_init_llc_id(struct cpuinfo_x86 *c, int cpu, u8 node_id)
void init_amd_cacheinfo(struct cpuinfo_x86 *c)
void init_hygon_cacheinfo(struct cpuinfo_x86 *c)
void init_intel_cacheinfo(struct cpuinfo_x86 *c)
static int __cache_amd_cpumap_setup(unsigned int cpu, int index, struct _cpuid4_info_regs *base)
static void __cache_cpumap_setup(unsigned int cpu, int index, struct _cpuid4_info_regs *base)
static void ci_leaf_init(struct cacheinfo *this_leaf, struct _cpuid4_info_regs *base)
static int __init_cache_level(unsigned int cpu)
static void get_cache_id(int cpu, struct _cpuid4_info_regs *id4_regs)
static int __populate_cache_leaves(unsigned int cpu)
   6 struct cpuinfo_x86 *c
   5 int cpu
   4 unsigned int cpu
   4 struct device *dev
   4 struct cacheinfo *this_leaf
   4 struct amd_northbridge *nb
   4 int index
   3 unsigned slot
   3 struct _cpuid4_info_regs *base
   3 size_t count
   3 char *buf
   2 unsigned int slot
   2 u8 node_id
   2 struct device_attribute *attr
   2 struct _cpuid4_info_regs *this_leaf
   2 slot
   2 const char *buf
   1 void
   1 unsigned long index
   1 unsigned long idx
   1 union _cpuid4_leaf_ecx *ecx
   1 union _cpuid4_leaf_ebx *ebx
   1 union _cpuid4_leaf_eax *eax
   1 struct kobject *kobj
   1 struct attribute *attr
   1 struct _cpuid4_info_regs *id4_regs
   1 int unused
   1 int leaf
   1 \struct device_attribute *attr
   1 \ struct device_attribute *attr
   1 \ const char *buf
