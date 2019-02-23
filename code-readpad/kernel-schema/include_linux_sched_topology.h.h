
\n
static inline int cpu_smt_flags(void)
static inline int cpu_core_flags(void)
static inline int cpu_numa_flags(void)
static inline struct cpumask *sched_domain_span(struct sched_domain *sd)
static __always_inline unsigned long arch_scale_cpu_capacity(struct sched_domain *sd, int cpu)
static inline void partition_sched_domains(int ndoms_new, cpumask_var_t doms_new[], struct sched_domain_attr *dattr_new)
static inline bool cpus_share_cache(int this_cpu, int that_cpu)
static __always_inline unsigned long arch_scale_cpu_capacity(void __always_unused *sd, int cpu)
static inline int task_node(const struct task_struct *p)
\n
      3 void
      2 struct sched_domain *sd
      2 int cpu
      1 void __always_unused *sd
      1 struct sched_domain_attr *dattr_new
      1 int this_cpu
      1 int that_cpu
      1 int ndoms_new
      1 cpumask_var_t doms_new[]
      1 const struct task_struct *p
