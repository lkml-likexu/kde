
\n
static inline int early_cpu_to_node(int cpu)
extern const struct cpumask *cpumask_of_node(int node)
;static inline const struct cpumask *cpumask_of_node(int node)
static inline int numa_node_id(void)
static inline int early_cpu_to_node(int cpu)
static inline int topology_max_smt_threads(void)
static inline void arch_fix_phys_package_id(int num, u32 slot)
define sysctl_sched_itmt_enabled 0 static inline void sched_set_itmt_core_prio(int prio, int core_cpu)
define sysctl_sched_itmt_enabled 0 static inline void sched_set_itmt_core_prio(int prio, int core_cpu)
} static inline int sched_set_itmt_support(void)
define sysctl_sched_itmt_enabled 0 static inline void sched_set_itmt_core_prio(int prio, int core_cpu)
} static inline int sched_set_itmt_support(void)
return 0; } static inline void sched_clear_itmt_support(void)
\n
      5 void
      3 int prio
      3 int core_cpu
      2 int node
      2 int cpu
      1 u32 slot
      1 int num
