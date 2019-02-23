
EXPORT_SYMBOL_GPL(x86_vector_domain);
EXPORT_SYMBOL_GPL(irqd_cfg);
\n
void lock_vector_lock(void)
void unlock_vector_lock(void)
void init_irq_alloc_info(struct irq_alloc_info *info, const struct cpumask *mask)
void copy_irq_alloc_info(struct irq_alloc_info *dst, struct irq_alloc_info *src)
static struct apic_chip_data *apic_chip_data(struct irq_data *irqd)
struct irq_cfg *irqd_cfg(struct irq_data *irqd)
struct irq_cfg *irq_cfg(unsigned int irq)
static struct apic_chip_data *alloc_apic_chip_data(int node)
static void free_apic_chip_data(struct apic_chip_data *apicd)
static void apic_update_irq_cfg(struct irq_data *irqd, unsigned int vector, unsigned int cpu)
static void apic_update_vector(struct irq_data *irqd, unsigned int newvec, unsigned int newcpu)
static void vector_assign_managed_shutdown(struct irq_data *irqd)
static int reserve_managed_vector(struct irq_data *irqd)
static void reserve_irq_vector_locked(struct irq_data *irqd)
static int reserve_irq_vector(struct irq_data *irqd)
static int assign_vector_locked(struct irq_data *irqd, const struct cpumask *dest)
static int assign_irq_vector(struct irq_data *irqd, const struct cpumask *dest)
static int assign_irq_vector_any_locked(struct irq_data *irqd)
static int assign_irq_vector_policy(struct irq_data *irqd, struct irq_alloc_info *info)
static int assign_managed_vector(struct irq_data *irqd, const struct cpumask *dest)
static void clear_irq_vector(struct irq_data *irqd)
static void x86_vector_deactivate(struct irq_domain *dom, struct irq_data *irqd)
static int activate_reserved(struct irq_data *irqd)
static int activate_managed(struct irq_data *irqd)
static int x86_vector_activate(struct irq_domain *dom, struct irq_data *irqd, bool reserve)
static void vector_free_reserved_and_managed(struct irq_data *irqd)
static void x86_vector_free_irqs(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs)
static bool vector_configure_legacy(unsigned int virq, struct irq_data *irqd, struct apic_chip_data *apicd)
static int x86_vector_alloc_irqs(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs, void *arg)
static void x86_vector_debug_show(struct seq_file *m, struct irq_domain *d, struct irq_data *irqd, int ind)
int __init arch_probe_nr_irqs(void)
void lapic_assign_legacy_vector(unsigned int irq, bool replace)
void __init lapic_assign_system_vectors(void)
int __init arch_early_irq_init(void)
static struct irq_desc *__setup_vector_irq(int vector)
void lapic_online(void)
void lapic_offline(void)
static int apic_set_affinity(struct irq_data *irqd, const struct cpumask *dest, bool force)
static int apic_retrigger_irq(struct irq_data *irqd)
void apic_ack_irq(struct irq_data *irqd)
void apic_ack_edge(struct irq_data *irqd)
static void free_moved_vector(struct apic_chip_data *apicd)
asmlinkage __visible void __irq_entry smp_irq_move_cleanup_interrupt(void)
static void __send_cleanup_vector(struct apic_chip_data *apicd)
void send_cleanup_vector(struct irq_cfg *cfg)
static void __irq_complete_move(struct irq_cfg *cfg, unsigned vector)
void irq_complete_move(struct irq_cfg *cfg)
void irq_force_complete_move(struct irq_desc *desc)
int lapic_can_unplug_cpu(void)
static void __init print_APIC_field(int base)
static void __init print_local_APIC(void *dummy)
static void __init print_local_APICs(int maxcpu)
static void __init print_PIC(void)
static int show_lapic __initdata = 1; static __init int setup_show_lapic(char *arg)
static int __init print_ICs(void)
\n
     25 struct irq_data *irqd
     11 void
      4 struct apic_chip_data *apicd
      4 const struct cpumask *dest
      3 unsigned int virq
      3 struct irq_cfg *cfg
      2 unsigned int nr_irqs
      2 unsigned int irq
      2 struct irq_domain *domain
      2 struct irq_domain *dom
      2 struct irq_alloc_info *info
      1 x86_vector_domain
      1 void *dummy
      1 void *arg
      1 unsigned vector
      1 unsigned int vector
      1 unsigned int newvec
      1 unsigned int newcpu
      1 unsigned int cpu
      1 struct seq_file *m
      1 struct irq_domain *d
      1 struct irq_desc *desc
      1 struct irq_alloc_info *src
      1 struct irq_alloc_info *dst
      1 irqd_cfg
      1 int vector
      1 int node
      1 int maxcpu
      1 int ind
      1 int base
      1 const struct cpumask *mask
      1 char *arg
      1 bool reserve
      1 bool replace
      1 bool force
