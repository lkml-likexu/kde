
static void irq_spread_init_one(struct cpumask *irqmsk, struct cpumask *nmsk, int cpus_per_vec)
static cpumask_var_t *alloc_node_to_cpumask(void)
static void free_node_to_cpumask(cpumask_var_t *masks)
static void build_node_to_cpumask(cpumask_var_t *masks)
static int get_nodes_in_cpumask(cpumask_var_t *node_to_cpumask, const struct cpumask *mask, nodemask_t *nodemsk)
static int irq_build_affinity_masks(const struct irq_affinity *affd, int startvec, int numvecs, cpumask_var_t *node_to_cpumask, const struct cpumask *cpu_mask, struct cpumask *nmsk, struct cpumask *masks)
struct cpumask * irq_create_affinity_masks(int nvecs, const struct irq_affinity *affd)
int irq_calc_affinity_vectors(int minvec, int maxvec, const struct irq_affinity *affd)
   3 const struct irq_affinity *affd
   2 struct cpumask *nmsk
   2 cpumask_var_t *node_to_cpumask
   2 cpumask_var_t *masks
   1 void
   1 struct cpumask *masks
   1 struct cpumask *irqmsk
   1 nodemask_t *nodemsk
   1 int startvec
   1 int nvecs
   1 int numvecs
   1 int minvec
   1 int maxvec
   1 int cpus_per_vec
   1 const struct cpumask *mask
   1 const struct cpumask *cpu_mask
