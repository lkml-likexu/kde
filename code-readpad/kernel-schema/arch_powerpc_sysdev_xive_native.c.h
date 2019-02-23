
EXPORT_SYMBOL_GPL(xive_native_populate_irq_data);
EXPORT_SYMBOL_GPL(xive_native_configure_irq);
EXPORT_SYMBOL_GPL(xive_native_configure_queue);
EXPORT_SYMBOL_GPL(xive_native_disable_queue);
EXPORT_SYMBOL_GPL(xive_native_alloc_irq);
EXPORT_SYMBOL_GPL(xive_native_free_irq);
EXPORT_SYMBOL_GPL(xive_native_sync_source);
EXPORT_SYMBOL_GPL(xive_native_default_eq_shift);
EXPORT_SYMBOL_GPL(xive_native_alloc_vp_block);
EXPORT_SYMBOL_GPL(xive_native_free_vp_block);
EXPORT_SYMBOL_GPL(xive_native_enable_vp);
EXPORT_SYMBOL_GPL(xive_native_disable_vp);
EXPORT_SYMBOL_GPL(xive_native_get_vp_info);
EXPORT_SYMBOL_GPL(xive_native_has_single_escalation);
\n
int xive_native_populate_irq_data(u32 hw_irq, struct xive_irq_data *data)
int xive_native_configure_irq(u32 hw_irq, u32 target, u8 prio, u32 sw_irq)
int xive_native_configure_queue(u32 vp_id, struct xive_q *q, u8 prio, __be32 *qpage, u32 order, bool can_escalate)
static void __xive_native_disable_queue(u32 vp_id, struct xive_q *q, u8 prio)
void xive_native_disable_queue(u32 vp_id, struct xive_q *q, u8 prio)
static int xive_native_setup_queue(unsigned int cpu, struct xive_cpu *xc, u8 prio)
static void xive_native_cleanup_queue(unsigned int cpu, struct xive_cpu *xc, u8 prio)
static bool xive_native_match(struct device_node *node)
static int xive_native_get_ipi(unsigned int cpu, struct xive_cpu *xc)
u32 xive_native_alloc_irq(void)
void xive_native_free_irq(u32 irq)
static void xive_native_put_ipi(unsigned int cpu, struct xive_cpu *xc)
static void xive_native_shutdown(void)
static void xive_native_update_pending(struct xive_cpu *xc)
static void xive_native_eoi(u32 hw_irq)
static void xive_native_setup_cpu(unsigned int cpu, struct xive_cpu *xc)
static void xive_native_teardown_cpu(unsigned int cpu, struct xive_cpu *xc)
void xive_native_sync_source(u32 hw_irq)
static bool xive_parse_provisioning(struct device_node *np)
static void xive_native_setup_pools(void)
u32 xive_native_default_eq_shift(void)
bool __init xive_native_init(void)
static bool xive_native_provision_pages(void)
u32 xive_native_alloc_vp_block(u32 max_vcpus)
void xive_native_free_vp_block(u32 vp_base)
int xive_native_enable_vp(u32 vp_id, bool single_escalation)
int xive_native_disable_vp(u32 vp_id)
int xive_native_get_vp_info(u32 vp_id, u32 *out_cam_id, u32 *out_chip_id)
bool xive_native_has_single_escalation(void)
\n
      7 void
      7 struct xive_cpu *xc
      6 unsigned int cpu
      6 u8 prio
      6 u32 vp_id
      4 u32 hw_irq
      3 struct xive_q *q
      1 xive_native_sync_source
      1 xive_native_populate_irq_data
      1 xive_native_has_single_escalation
      1 xive_native_get_vp_info
      1 xive_native_free_vp_block
      1 xive_native_free_irq
      1 xive_native_enable_vp
      1 xive_native_disable_vp
      1 xive_native_disable_queue
      1 xive_native_default_eq_shift
      1 xive_native_configure_queue
      1 xive_native_configure_irq
      1 xive_native_alloc_vp_block
      1 xive_native_alloc_irq
      1 u32 vp_base
      1 u32 target
      1 u32 sw_irq
      1 u32 *out_chip_id
      1 u32 *out_cam_id
      1 u32 order
      1 u32 max_vcpus
      1 u32 irq
      1 struct xive_irq_data *data
      1 struct device_node *np
      1 struct device_node *node
      1 bool single_escalation
      1 bool can_escalate
      1 __be32 *qpage
