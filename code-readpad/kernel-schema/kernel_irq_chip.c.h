
EXPORT_SYMBOL_GPL(irq_get_irq_data);
EXPORT_SYMBOL_GPL(handle_nested_irq);
EXPORT_SYMBOL_GPL(handle_simple_irq);
EXPORT_SYMBOL_GPL(handle_untracked_irq);
EXPORT_SYMBOL_GPL(handle_level_irq);
EXPORT_SYMBOL_GPL(handle_fasteoi_irq);
EXPORT_SYMBOL_GPL(__irq_set_handler);
EXPORT_SYMBOL_GPL(irq_set_chained_handler_and_data);
EXPORT_SYMBOL_GPL(irq_set_chip_and_handler_name);
EXPORT_SYMBOL_GPL(irq_modify_status);
EXPORT_SYMBOL_GPL(handle_fasteoi_ack_irq);
EXPORT_SYMBOL_GPL(handle_fasteoi_mask_irq);
EXPORT_SYMBOL_GPL(irq_chip_enable_parent);
EXPORT_SYMBOL_GPL(irq_chip_disable_parent);
EXPORT_SYMBOL_GPL(irq_chip_ack_parent);
EXPORT_SYMBOL_GPL(irq_chip_mask_parent);
EXPORT_SYMBOL_GPL(irq_chip_unmask_parent);
EXPORT_SYMBOL_GPL(irq_chip_eoi_parent);
EXPORT_SYMBOL_GPL(irq_chip_set_affinity_parent);
EXPORT_SYMBOL_GPL(irq_chip_set_type_parent);
\n
static irqreturn_t bad_chained_irq(int irq, void *dev_id)
int irq_set_chip(unsigned int irq, struct irq_chip *chip)
int irq_set_irq_type(unsigned int irq, unsigned int type)
int irq_set_handler_data(unsigned int irq, void *data)
int irq_set_msi_desc_off(unsigned int irq_base, unsigned int irq_offset, struct msi_desc *entry)
int irq_set_msi_desc(unsigned int irq, struct msi_desc *entry)
int irq_set_chip_data(unsigned int irq, void *data)
struct irq_data *irq_get_irq_data(unsigned int irq)
static void irq_state_clr_disabled(struct irq_desc *desc)
static void irq_state_clr_masked(struct irq_desc *desc)
static void irq_state_clr_started(struct irq_desc *desc)
static void irq_state_set_started(struct irq_desc *desc)
static int __irq_startup_managed(struct irq_desc *desc, struct cpumask *aff, bool force)
if (WARN_ON_ONCE(force)
)
return IRQ_STARTUP_ABORT;return IRQ_STARTUP_ABORT;}if (WARN_ON(irq_domain_activate_irq(d, false)
)
)
return IRQ_STARTUP_ABORT;return IRQ_STARTUP_MANAGED; } static __always_inline int __irq_startup_managed(struct irq_desc *desc, struct cpumask *aff, bool force)
static int __irq_startup(struct irq_desc *desc)
int irq_startup(struct irq_desc *desc, bool resend, bool force)
int irq_activate(struct irq_desc *desc)
int irq_activate_and_startup(struct irq_desc *desc, bool resend)
void irq_shutdown(struct irq_desc *desc)
void irq_enable(struct irq_desc *desc)
static void __irq_disable(struct irq_desc *desc, bool mask)
void irq_disable(struct irq_desc *desc)
void irq_percpu_enable(struct irq_desc *desc, unsigned int cpu)
void irq_percpu_disable(struct irq_desc *desc, unsigned int cpu)
static inline void mask_ack_irq(struct irq_desc *desc)
void mask_irq(struct irq_desc *desc)
void unmask_irq(struct irq_desc *desc)
void unmask_threaded_irq(struct irq_desc *desc)
void handle_nested_irq(unsigned int irq)
static bool irq_check_poll(struct irq_desc *desc)
static bool irq_may_run(struct irq_desc *desc)
void handle_simple_irq(struct irq_desc *desc)
void handle_untracked_irq(struct irq_desc *desc)
static void cond_unmask_irq(struct irq_desc *desc)
void handle_level_irq(struct irq_desc *desc)
static inline void preflow_handler(struct irq_desc *desc)
static void cond_unmask_eoi_irq(struct irq_desc *desc, struct irq_chip *chip)
void handle_fasteoi_irq(struct irq_desc *desc)
void handle_edge_irq(struct irq_desc *desc)
void handle_edge_eoi_irq(struct irq_desc *desc)
void handle_percpu_irq(struct irq_desc *desc)
void handle_percpu_devid_irq(struct irq_desc *desc)
static void __irq_do_set_handler(struct irq_desc *desc, irq_flow_handler_t handle, int is_chained, const char *name)
void __irq_set_handler(unsigned int irq, irq_flow_handler_t handle, int is_chained, const char *name)
void irq_set_chained_handler_and_data(unsigned int irq, irq_flow_handler_t handle, void *data)
void irq_set_chip_and_handler_name(unsigned int irq, struct irq_chip *chip, irq_flow_handler_t handle, const char *name)
void irq_modify_status(unsigned int irq, unsigned long clr, unsigned long set)
void irq_cpu_online(void)
void irq_cpu_offline(void)
void handle_fasteoi_ack_irq(struct irq_desc *desc)
void handle_fasteoi_mask_irq(struct irq_desc *desc)
void irq_chip_enable_parent(struct irq_data *data)
void irq_chip_disable_parent(struct irq_data *data)
void irq_chip_ack_parent(struct irq_data *data)
void irq_chip_mask_parent(struct irq_data *data)
void irq_chip_unmask_parent(struct irq_data *data)
void irq_chip_eoi_parent(struct irq_data *data)
int irq_chip_set_affinity_parent(struct irq_data *data, const struct cpumask *dest, bool force)
int irq_chip_set_type_parent(struct irq_data *data, unsigned int type)
int irq_chip_retrigger_hierarchy(struct irq_data *data)
int irq_chip_set_vcpu_affinity_parent(struct irq_data *data, void *vcpu_info)
int irq_chip_set_wake_parent(struct irq_data *data, unsigned int on)
int irq_chip_compose_msi_msg(struct irq_data *data, struct msi_msg *msg)
int irq_chip_pm_get(struct irq_data *data)
int irq_chip_pm_put(struct irq_data *data)
\n
     36 struct irq_desc *desc
     14 struct irq_data *data
     11 unsigned int irq
      4 irq_flow_handler_t handle
      4 bool force
      3 void *data
      3 struct irq_chip *chip
      3 const char *name
      2 void
      2 unsigned int type
      2 unsigned int cpu
      2 struct msi_desc *entry
      2 struct cpumask *aff
      2 int is_chained
      2 bool resend
      1 WARN_ON_ONCEforce
      1 WARN_ONirq_domain_activate_irqd
      1 void *vcpu_info
      1 void *dev_id
      1 unsigned long set
      1 unsigned long clr
      1 unsigned int on
      1 unsigned int irq_offset
      1 unsigned int irq_base
      1 struct msi_msg *msg
      1 __irq_set_handler
      1 irq_set_chip_and_handler_name
      1 irq_set_chained_handler_and_data
      1 irq_modify_status
      1 irq_get_irq_data
      1 irq_chip_unmask_parent
      1 irq_chip_set_type_parent
      1 irq_chip_set_affinity_parent
      1 irq_chip_mask_parent
      1 irq_chip_eoi_parent
      1 irq_chip_enable_parent
      1 irq_chip_disable_parent
      1 irq_chip_ack_parent
      1 int irq
      1 handle_untracked_irq
      1 handle_simple_irq
      1 handle_nested_irq
      1 handle_level_irq
      1 handle_fasteoi_mask_irq
      1 handle_fasteoi_irq
      1 handle_fasteoi_ack_irq
      1 false
      1 const struct cpumask *dest
      1 bool mask
