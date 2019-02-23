
EXPORT_SYMBOL_GPL(memory_add_physaddr_to_nid);
\n
static __init int numa_setup(char *opt)
int numa_cpu_node(int cpu)
void numa_set_node(int cpu, int node)
void numa_clear_node(int cpu)
void __init setup_node_to_cpumask_map(void)
static int __init numa_add_memblk_to(int nid, u64 start, u64 end, struct numa_meminfo *mi)
void __init numa_remove_memblk_from(int idx, struct numa_meminfo *mi)
int __init numa_add_memblk(int nid, u64 start, u64 end)
static void __init alloc_node_data(int nid)
int __init numa_cleanup_meminfo(struct numa_meminfo *mi)
static void __init numa_nodemask_from_meminfo(nodemask_t *nodemask, const struct numa_meminfo *mi)
void __init numa_reset_distance(void)
static int __init numa_alloc_distance(void)
void __init numa_set_distance(int from, int to, int distance)
int __node_distance(int from, int to)
static bool __init numa_meminfo_cover_memory(const struct numa_meminfo *mi)
static void __init numa_clear_kernel_node_hotplug(void)
static int __init numa_register_memblks(struct numa_meminfo *mi)
static void __init numa_init_array(void)
static int __init numa_init(int (*init_func)
(void)
)
static int __init dummy_numa_init(void)
void __init x86_numa_init(void)
static void __init init_memory_less_node(int nid)
void __init init_cpu_to_node(void)
ifndef CONFIG_NUMA_EMU void numa_add_cpu(int cpu)
void numa_remove_cpu(int cpu)
int __cpu_to_node(int cpu)
int early_cpu_to_node(int cpu)
void debug_cpumask_set_cpu(int cpu, int node, bool enable)
ifndef CONFIG_NUMA_EMU static void numa_set_cpumask(int cpu, bool enable)
void numa_add_cpu(int cpu)
void numa_remove_cpu(int cpu)
const struct cpumask *cpumask_of_node(int node)
int memory_add_physaddr_to_nid(u64 start)
\n
     11 int cpu
      9 void
      4 struct numa_meminfo *mi
      4 int nid
      3 u64 start
      3 int node
      2 u64 end
      2 int to
      2 int from
      2 const struct numa_meminfo *mi
      2 bool enable
      1 nodemask_t *nodemask
      1 memory_add_physaddr_to_nid
      1 int *init_func
      1 int idx
      1 int distance
      1 char *opt
