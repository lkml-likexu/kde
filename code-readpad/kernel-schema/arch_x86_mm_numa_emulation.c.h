
\n
void __init numa_emu_cmdline(char *str)
static int __init emu_find_memblk_by_nid(int nid, const struct numa_meminfo *mi)
static u64 __init mem_hole_size(u64 start, u64 end)
static int __init emu_setup_memblk(struct numa_meminfo *ei, struct numa_meminfo *pi, int nid, int phys_blk, u64 size)
static int __init split_nodes_interleave(struct numa_meminfo *ei, struct numa_meminfo *pi, u64 addr, u64 max_addr, int nr_nodes)
static u64 __init find_end_of_node(u64 start, u64 max_addr, u64 size)
static u64 uniform_size(u64 max_addr, u64 base, u64 hole, int nr_nodes)
static int __init split_nodes_size_interleave_uniform(struct numa_meminfo *ei, struct numa_meminfo *pi, u64 addr, u64 max_addr, u64 size, int nr_nodes, struct numa_memblk *pblk, int nid)
static int __init split_nodes_size_interleave(struct numa_meminfo *ei, struct numa_meminfo *pi, u64 addr, u64 max_addr, u64 size)
int __init setup_emu2phys_nid(int *dfl_phys_nid)
void __init numa_emulation(struct numa_meminfo *numa_meminfo, int numa_dist_cnt)
void numa_add_cpu(int cpu)
void numa_remove_cpu(int cpu)
for_each_online_node(i)
cpumask_clear_cpu(cpu, node_to_cpumask_map[i])
; } static void numa_set_cpumask(int cpu, bool enable)
void numa_add_cpu(int cpu)
void numa_remove_cpu(int cpu)
\n
      5 u64 max_addr
      5 int cpu
      4 u64 size
      4 struct numa_meminfo *pi
      4 struct numa_meminfo *ei
      3 u64 addr
      3 int nr_nodes
      3 int nid
      2 u64 start
      1 u64 hole
      1 u64 end
      1 u64 base
      1 struct numa_meminfo *numa_meminfo
      1 struct numa_memblk *pblk
      1 node_to_cpumask_map[i]
      1 int phys_blk
      1 int numa_dist_cnt
      1 int *dfl_phys_nid
      1 i
      1 cpu
      1 const struct numa_meminfo *mi
      1 char *str
      1 bool enable
