
EXPORT_SYMBOL_GPL(kvmppc_xive_push_vcpu);
EXPORT_SYMBOL_GPL(kvmppc_xive_set_mapped);
EXPORT_SYMBOL_GPL(kvmppc_xive_clr_mapped);
\n
void kvmppc_xive_push_vcpu(struct kvm_vcpu *vcpu)
static bool xive_irq_trigger(struct xive_irq_data *xd)
static irqreturn_t xive_esc_irq(int irq, void *data)
static int xive_attach_escalation(struct kvm_vcpu *vcpu, u8 prio)
static int xive_provision_queue(struct kvm_vcpu *vcpu, u8 prio)
static int xive_check_provisioning(struct kvm *kvm, u8 prio)
static void xive_inc_q_pending(struct kvm *kvm, u32 server, u8 prio)
static int xive_try_pick_queue(struct kvm_vcpu *vcpu, u8 prio)
static int xive_select_target(struct kvm *kvm, u32 *server, u8 prio)
static u32 xive_vp(struct kvmppc_xive *xive, u32 server)
static u8 xive_lock_and_mask(struct kvmppc_xive *xive, struct kvmppc_xive_src_block *sb, struct kvmppc_xive_irq_state *state)
static void xive_lock_for_unmask(struct kvmppc_xive_src_block *sb, struct kvmppc_xive_irq_state *state)
static void xive_finish_unmask(struct kvmppc_xive *xive, struct kvmppc_xive_src_block *sb, struct kvmppc_xive_irq_state *state, u8 prio)
static int xive_target_interrupt(struct kvm *kvm, struct kvmppc_xive_irq_state *state, u32 server, u8 prio)
int kvmppc_xive_set_xive(struct kvm *kvm, u32 irq, u32 server, u32 priority)
int kvmppc_xive_get_xive(struct kvm *kvm, u32 irq, u32 *server, u32 *priority)
int kvmppc_xive_int_on(struct kvm *kvm, u32 irq)
int kvmppc_xive_int_off(struct kvm *kvm, u32 irq)
static bool xive_restore_pending_irq(struct kvmppc_xive *xive, u32 irq)
u64 kvmppc_xive_get_icp(struct kvm_vcpu *vcpu)
int kvmppc_xive_set_icp(struct kvm_vcpu *vcpu, u64 icpval)
int kvmppc_xive_set_mapped(struct kvm *kvm, unsigned long guest_irq, struct irq_desc *host_desc)
int kvmppc_xive_clr_mapped(struct kvm *kvm, unsigned long guest_irq, struct irq_desc *host_desc)
static void kvmppc_xive_disable_vcpu_interrupts(struct kvm_vcpu *vcpu)
void kvmppc_xive_cleanup_vcpu(struct kvm_vcpu *vcpu)
int kvmppc_xive_connect_vcpu(struct kvm_device *dev, struct kvm_vcpu *vcpu, u32 cpu)
static void xive_pre_save_set_queued(struct kvmppc_xive *xive, u32 irq)
static void xive_pre_save_mask_irq(struct kvmppc_xive *xive, struct kvmppc_xive_src_block *sb, u32 irq)
static void xive_pre_save_unmask_irq(struct kvmppc_xive *xive, struct kvmppc_xive_src_block *sb, u32 irq)
static void xive_pre_save_queue(struct kvmppc_xive *xive, struct xive_q *q)
static void xive_pre_save_scan(struct kvmppc_xive *xive)
static void xive_post_save_scan(struct kvmppc_xive *xive)
static int xive_get_source(struct kvmppc_xive *xive, long irq, u64 addr)
static struct kvmppc_xive_src_block *xive_create_src_block(struct kvmppc_xive *xive, int irq)
static bool xive_check_delayed_irq(struct kvmppc_xive *xive, u32 irq)
static int xive_set_source(struct kvmppc_xive *xive, long irq, u64 addr)
int kvmppc_xive_set_irq(struct kvm *kvm, int irq_source_id, u32 irq, int level, bool line_status)
static int xive_set_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static int xive_get_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static int xive_has_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static void kvmppc_xive_cleanup_irq(u32 hw_num, struct xive_irq_data *xd)
static void kvmppc_xive_free_sources(struct kvmppc_xive_src_block *sb)
static void kvmppc_xive_free(struct kvm_device *dev)
static int kvmppc_xive_create(struct kvm_device *dev, u32 type)
static int xive_debug_show(struct seq_file *m, void *private)
static void xive_debugfs_init(struct kvmppc_xive *xive)
static void kvmppc_xive_init(struct kvm_device *dev)
void kvmppc_xive_init_module(void)
void kvmppc_xive_exit_module(void)
\n
     15 struct kvmppc_xive *xive
     11 struct kvm *kvm
     10 u32 irq
      9 struct kvm_vcpu *vcpu
      8 u8 prio
      7 struct kvm_device *dev
      6 struct kvmppc_xive_src_block *sb
      4 u32 server
      4 struct kvmppc_xive_irq_state *state
      3 struct kvm_device_attr *attr
      2 void
      2 unsigned long guest_irq
      2 u64 addr
      2 u32 *server
      2 struct xive_irq_data *xd
      2 struct irq_desc *host_desc
      2 long irq
      2 int irq
      1 void *private
      1 void *data
      1 u64 icpval
      1 u32 type
      1 u32 *priority
      1 u32 priority
      1 u32 hw_num
      1 u32 cpu
      1 struct xive_q *q
      1 struct seq_file *m
      1 kvmppc_xive_set_mapped
      1 kvmppc_xive_push_vcpu
      1 kvmppc_xive_clr_mapped
      1 int level
      1 int irq_source_id
      1 bool line_status
