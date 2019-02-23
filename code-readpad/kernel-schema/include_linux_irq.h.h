
\n
static inline bool irqd_is_setaffinity_pending(struct irq_data *d)
static inline bool irqd_is_per_cpu(struct irq_data *d)
static inline bool irqd_can_balance(struct irq_data *d)
static inline bool irqd_affinity_was_set(struct irq_data *d)
static inline void irqd_mark_affinity_was_set(struct irq_data *d)
static inline bool irqd_trigger_type_was_set(struct irq_data *d)
static inline u32 irqd_get_trigger_type(struct irq_data *d)
static inline void irqd_set_trigger_type(struct irq_data *d, u32 type)
static inline bool irqd_is_level_type(struct irq_data *d)
static inline void irqd_set_single_target(struct irq_data *d)
static inline bool irqd_is_single_target(struct irq_data *d)
static inline bool irqd_is_wakeup_set(struct irq_data *d)
static inline bool irqd_can_move_in_process_context(struct irq_data *d)
static inline bool irqd_irq_disabled(struct irq_data *d)
static inline bool irqd_irq_masked(struct irq_data *d)
static inline bool irqd_irq_inprogress(struct irq_data *d)
static inline bool irqd_is_wakeup_armed(struct irq_data *d)
static inline bool irqd_is_forwarded_to_vcpu(struct irq_data *d)
static inline void irqd_set_forwarded_to_vcpu(struct irq_data *d)
static inline void irqd_clr_forwarded_to_vcpu(struct irq_data *d)
static inline bool irqd_affinity_is_managed(struct irq_data *d)
static inline bool irqd_is_activated(struct irq_data *d)
static inline void irqd_set_activated(struct irq_data *d)
static inline void irqd_clr_activated(struct irq_data *d)
static inline bool irqd_is_started(struct irq_data *d)
static inline bool irqd_is_managed_and_shutdown(struct irq_data *d)
static inline void irqd_set_can_reserve(struct irq_data *d)
static inline void irqd_clr_can_reserve(struct irq_data *d)
static inline bool irqd_can_reserve(struct irq_data *d)
static inline irq_hw_number_t irqd_to_hwirq(struct irq_data *d)
void __irq_move_irq(struct irq_data *data)
; static inline void irq_move_irq(struct irq_data *data)
int irq_set_parent(int irq, int parent_irq)
; static inline int irq_set_parent(int irq, int parent_irq)
static inline void irq_set_chip_and_handler(unsigned int irq, struct irq_chip *chip, irq_flow_handler_t handle)
static inline void irq_set_handler(unsigned int irq, irq_flow_handler_t handle)
static inline void irq_set_chained_handler(unsigned int irq, irq_flow_handler_t handle)
static inline void irq_set_status_flags(unsigned int irq, unsigned long set)
static inline void irq_clear_status_flags(unsigned int irq, unsigned long clr)
static inline void irq_set_noprobe(unsigned int irq)
static inline void irq_set_probe(unsigned int irq)
static inline void irq_set_nothread(unsigned int irq)
static inline void irq_set_thread(unsigned int irq)
static inline void irq_set_nested_thread(unsigned int irq, bool nest)
static inline void irq_set_percpu_devid_flags(unsigned int irq)
static inline struct irq_chip *irq_get_chip(unsigned int irq)
static inline struct irq_chip *irq_data_get_irq_chip(struct irq_data *d)
static inline void *irq_get_chip_data(unsigned int irq)
static inline void *irq_data_get_irq_chip_data(struct irq_data *d)
static inline void *irq_get_handler_data(unsigned int irq)
static inline void *irq_data_get_irq_handler_data(struct irq_data *d)
static inline struct msi_desc *irq_get_msi_desc(unsigned int irq)
static inline struct msi_desc *irq_data_get_msi_desc(struct irq_data *d)
static inline u32 irq_get_trigger_type(unsigned int irq)
static inline int irq_common_data_get_node(struct irq_common_data *d)
static inline int irq_data_get_node(struct irq_data *d)
static inline struct cpumask *irq_get_affinity_mask(int irq)
static inline struct cpumask *irq_data_get_affinity_mask(struct irq_data *d)
static inline struct cpumask *irq_data_get_effective_affinity_mask(struct irq_data *d)
static inline struct cpumask *irq_data_get_effective_affinity_mask(struct irq_data *d)
return d->common->effective_affinity; } static inline void irq_data_update_effective_affinity(struct irq_data *d, const struct cpumask *m)
static inline struct cpumask *irq_data_get_effective_affinity_mask(struct irq_data *d)
return d->common->effective_affinity; } static inline void irq_data_update_effective_affinity(struct irq_data *d, const struct cpumask *m)
cpumask_copy(d->common->effective_affinity, m)
; } static inline void irq_data_update_effective_affinity(struct irq_data *d, const struct cpumask *m)
static inline struct cpumask *irq_data_get_effective_affinity_mask(struct irq_data *d)
return d->common->effective_affinity; } static inline void irq_data_update_effective_affinity(struct irq_data *d, const struct cpumask *m)
cpumask_copy(d->common->effective_affinity, m)
; } static inline void irq_data_update_effective_affinity(struct irq_data *d, const struct cpumask *m)
} static inline struct cpumask *irq_data_get_effective_affinity_mask(struct irq_data *d)
void irq_free_descs(unsigned int irq, unsigned int cnt)
; static inline void irq_free_desc(unsigned int irq)
unsigned int irq_alloc_hwirqs(int cnt, int node)
; static inline unsigned int irq_alloc_hwirq(int node)
unsigned int irq_alloc_hwirqs(int cnt, int node)
; static inline unsigned int irq_alloc_hwirq(int node)
return irq_alloc_hwirqs(1, node)
; } void irq_free_hwirqs(unsigned int from, int cnt)
; static inline void irq_free_hwirq(unsigned int irq)
static inline void irq_free_generic_chip(struct irq_chip_generic *gc)
static inline void irq_destroy_generic_chip(struct irq_chip_generic *gc, u32 msk, unsigned int clr, unsigned int set)
static inline struct irq_chip_type *irq_data_get_chip_type(struct irq_data *d)
static inline void irq_gc_lock(struct irq_chip_generic *gc)
static inline void irq_gc_unlock(struct irq_chip_generic *gc)
static inline void irq_reg_writel(struct irq_chip_generic *gc, u32 val, int reg_offset)
static inline u32 irq_reg_readl(struct irq_chip_generic *gc, int reg_offset)
\n
     47 struct irq_data *d
     19 unsigned int irq
      6 struct irq_chip_generic *gc
      5 const struct cpumask *m
      4 int node
      3 irq_flow_handler_t handle
      3 int irq
      3 int cnt
      2 struct irq_data *data
      2 m
      2 int reg_offset
      2 int parent_irq
      2 d->common->effective_affinity
      1 unsigned long set
      1 unsigned long clr
      1 unsigned int set
      1 unsigned int from
      1 unsigned int cnt
      1 unsigned int clr
      1 u32 val
      1 u32 type
      1 u32 msk
      1 struct irq_common_data *d
      1 struct irq_chip *chip
      1 node
      1 bool nest
      1 1
