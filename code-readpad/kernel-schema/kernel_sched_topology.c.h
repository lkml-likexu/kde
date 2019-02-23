
\n
static int __init sched_debug_setup(char *str)
static inline bool sched_debug(void)
static int sched_domain_debug_one(struct sched_domain *sd, int cpu, int level, struct cpumask *groupmask)
static void sched_domain_debug(struct sched_domain *sd, int cpu)
define sched_debug_enabled 0 static inline bool sched_debug(void)
static int sd_degenerate(struct sched_domain *sd)
static int sd_parent_degenerate(struct sched_domain *sd, struct sched_domain *parent)
static void free_pd(struct perf_domain *pd)
static struct perf_domain *find_pd(struct perf_domain *pd, int cpu)
static struct perf_domain *pd_init(int cpu)
static void perf_domain_debug(const struct cpumask *cpu_map, struct perf_domain *pd)
static void destroy_perf_domain_rcu(struct rcu_head *rp)
static void sched_energy_set(bool has_eas)
extern struct cpufreq_governor schedutil_gov; static bool build_perf_domains(const struct cpumask *cpu_map)
static void free_rootdomain(struct rcu_head *rcu)
void rq_attach_root(struct rq *rq, struct root_domain *rd)
void sched_get_rd(struct root_domain *rd)
void sched_put_rd(struct root_domain *rd)
static int init_rootdomain(struct root_domain *rd)
void init_defrootdomain(void)
static struct root_domain *alloc_rootdomain(void)
static void free_sched_groups(struct sched_group *sg, int free_sgc)
static void destroy_sched_domain(struct sched_domain *sd)
static void destroy_sched_domains_rcu(struct rcu_head *rcu)
static void destroy_sched_domains(struct sched_domain *sd)
static void update_top_cache_domain(int cpu)
static void cpu_attach_domain(struct sched_domain *sd, struct root_domain *rd, int cpu)
int group_balance_cpu(struct sched_group *sg)
static void build_balance_mask(struct sched_domain *sd, struct sched_group *sg, struct cpumask *mask)
static struct sched_group * build_group_from_child_sched_domain(struct sched_domain *sd, int cpu)
static void init_overlap_sched_group(struct sched_domain *sd, struct sched_group *sg)
static int build_overlap_sched_groups(struct sched_domain *sd, int cpu)
static struct sched_group *get_group(int cpu, struct sd_data *sdd)
static int build_sched_groups(struct sched_domain *sd, int cpu)
static void init_sched_groups_capacity(int cpu, struct sched_domain *sd)
static int __init setup_relax_domain_level(char *str)
static void set_domain_attribute(struct sched_domain *sd, struct sched_domain_attr *attr)
static void __free_domain_allocs(struct s_data *d, enum s_alloc what, const struct cpumask *cpu_map)
static enum s_alloc __visit_domain_allocation_hell(struct s_data *d, const struct cpumask *cpu_map)
static void claim_allocations(int cpu, struct sched_domain *sd)
static struct sched_domain * sd_init(struct sched_domain_topology_level *tl, const struct cpumask *cpu_map, struct sched_domain *child, int dflags, int cpu)
void set_sched_topology(struct sched_domain_topology_level *tl)
static const struct cpumask *sd_numa_mask(int cpu)
static void sched_numa_warn(const char *str)
bool find_numa_distance(int distance)
static void init_numa_topology_type(void)
void sched_init_numa(void)
void sched_domains_numa_masks_set(unsigned int cpu)
void sched_domains_numa_masks_clear(unsigned int cpu)
static int __sdt_alloc(const struct cpumask *cpu_map)
static void __sdt_free(const struct cpumask *cpu_map)
static struct sched_domain *build_sched_domain(struct sched_domain_topology_level *tl, const struct cpumask *cpu_map, struct sched_domain_attr *attr, struct sched_domain *child, int dflags, int cpu)
static struct sched_domain_topology_level *asym_cpu_capacity_level(const struct cpumask *cpu_map)
static int build_sched_domains(const struct cpumask *cpu_map, struct sched_domain_attr *attr)
int __weak arch_update_cpu_topology(void)
cpumask_var_t *alloc_sched_domains(unsigned int ndoms)
void free_sched_domains(cpumask_var_t doms[], unsigned int ndoms)
int sched_init_domains(const struct cpumask *cpu_map)
static void detach_destroy_domains(const struct cpumask *cpu_map)
static int dattrs_equal(struct sched_domain_attr *cur, int idx_cur, struct sched_domain_attr *new, int idx_new)
void partition_sched_domains(int ndoms_new, cpumask_var_t doms_new[], struct sched_domain_attr *dattr_new)
\n
     15 struct sched_domain *sd
     15 int cpu
     12 const struct cpumask *cpu_map
      7 void
      5 struct root_domain *rd
      4 struct sched_group *sg
      3 struct sched_domain_topology_level *tl
      3 struct sched_domain_attr *attr
      3 struct perf_domain *pd
      2 unsigned int ndoms
      2 unsigned int cpu
      2 struct s_data *d
      2 struct sched_domain *child
      2 struct rcu_head *rcu
      2 int dflags
      2 char *str
      1 struct sd_data *sdd
      1 struct sched_domain *parent
      1 struct sched_domain_attr *new
      1 struct sched_domain_attr *dattr_new
      1 struct sched_domain_attr *cur
      1 struct rq *rq
      1 struct rcu_head *rp
      1 struct cpumask *mask
      1 struct cpumask *groupmask
      1 int ndoms_new
      1 int level
      1 int idx_new
      1 int idx_cur
      1 int free_sgc
      1 int distance
      1 enum s_alloc what
      1 cpumask_var_t doms_new[]
      1 cpumask_var_t doms[]
      1 const char *str
      1 bool has_eas
