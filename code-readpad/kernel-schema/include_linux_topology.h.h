
\n
static inline int numa_node_id(void)
static inline int cpu_to_node(int cpu)
static inline void set_numa_node(int node)
static inline void set_cpu_numa_node(int cpu, int node)
static inline int numa_node_id(void)
static inline void set_numa_mem(int node)
static inline int node_to_mem_node(int node)
static inline int numa_mem_id(void)
static inline int cpu_to_mem(int cpu)
static inline void set_cpu_numa_mem(int cpu, int node)
static inline int numa_mem_id(void)
static inline int node_to_mem_node(int node)
static inline int cpu_to_mem(int cpu)
static inline const struct cpumask *cpu_smt_mask(int cpu)
static inline const struct cpumask *cpu_cpu_mask(int cpu)
\n
      7 int cpu
      6 int node
      4 void
