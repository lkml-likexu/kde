
\n
__init struct irq_matrix *irq_alloc_matrix(unsigned int matrix_bits, unsigned int alloc_start, unsigned int alloc_end)
void irq_matrix_online(struct irq_matrix *m)
void irq_matrix_offline(struct irq_matrix *m)
static unsigned int matrix_alloc_area(struct irq_matrix *m, struct cpumap *cm, unsigned int num, bool managed)
static unsigned int matrix_find_best_cpu(struct irq_matrix *m, const struct cpumask *msk)
static unsigned int matrix_find_best_cpu_managed(struct irq_matrix *m, const struct cpumask *msk)
void irq_matrix_assign_system(struct irq_matrix *m, unsigned int bit, bool replace)
int irq_matrix_reserve_managed(struct irq_matrix *m, const struct cpumask *msk)
void irq_matrix_remove_managed(struct irq_matrix *m, const struct cpumask *msk)
int irq_matrix_alloc_managed(struct irq_matrix *m, const struct cpumask *msk, unsigned int *mapped_cpu)
void irq_matrix_assign(struct irq_matrix *m, unsigned int bit)
void irq_matrix_reserve(struct irq_matrix *m)
void irq_matrix_remove_reserved(struct irq_matrix *m)
int irq_matrix_alloc(struct irq_matrix *m, const struct cpumask *msk, bool reserved, unsigned int *mapped_cpu)
void irq_matrix_free(struct irq_matrix *m, unsigned int cpu, unsigned int bit, bool managed)
unsigned int irq_matrix_available(struct irq_matrix *m, bool cpudown)
unsigned int irq_matrix_reserved(struct irq_matrix *m)
unsigned int irq_matrix_allocated(struct irq_matrix *m)
void irq_matrix_debug_show(struct seq_file *sf, struct irq_matrix *m, int ind)
\n
     18 struct irq_matrix *m
      6 const struct cpumask *msk
      3 unsigned int bit
      2 unsigned int *mapped_cpu
      2 bool managed
      1 unsigned int num
      1 unsigned int matrix_bits
      1 unsigned int cpu
      1 unsigned int alloc_start
      1 unsigned int alloc_end
      1 struct seq_file *sf
      1 struct cpumap *cm
      1 int ind
      1 bool reserved
      1 bool replace
      1 bool cpudown
