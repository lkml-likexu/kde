
EXPORT_SYMBOL_GPL(kvmppc_xics_rm_complete);
EXPORT_SYMBOL_GPL(kvmppc_xics_hcall);
EXPORT_SYMBOL_GPL(kvmppc_xics_set_mapped);
EXPORT_SYMBOL_GPL(kvmppc_xics_clr_mapped);
\n
static int ics_deliver_irq(struct kvmppc_xics *xics, u32 irq, u32 level)
static void ics_check_resend(struct kvmppc_xics *xics, struct kvmppc_ics *ics, struct kvmppc_icp *icp)
static bool write_xive(struct kvmppc_xics *xics, struct kvmppc_ics *ics, struct ics_irq_state *state, u32 server, u32 priority, u32 saved_priority)
int kvmppc_xics_set_xive(struct kvm *kvm, u32 irq, u32 server, u32 priority)
int kvmppc_xics_get_xive(struct kvm *kvm, u32 irq, u32 *server, u32 *priority)
int kvmppc_xics_int_on(struct kvm *kvm, u32 irq)
int kvmppc_xics_int_off(struct kvm *kvm, u32 irq)
static inline bool icp_try_update(struct kvmppc_icp *icp, union kvmppc_icp_state old, union kvmppc_icp_state new, bool change_self)
static void icp_check_resend(struct kvmppc_xics *xics, struct kvmppc_icp *icp)
static bool icp_try_to_deliver(struct kvmppc_icp *icp, u32 irq, u8 priority, u32 *reject)
static void icp_deliver_irq(struct kvmppc_xics *xics, struct kvmppc_icp *icp, u32 new_irq, bool check_resend)
static void icp_down_cppr(struct kvmppc_xics *xics, struct kvmppc_icp *icp, u8 new_cppr)
static noinline unsigned long kvmppc_h_xirr(struct kvm_vcpu *vcpu)
static noinline int kvmppc_h_ipi(struct kvm_vcpu *vcpu, unsigned long server, unsigned long mfrr)
static int kvmppc_h_ipoll(struct kvm_vcpu *vcpu, unsigned long server)
static noinline void kvmppc_h_cppr(struct kvm_vcpu *vcpu, unsigned long cppr)
static int ics_eoi(struct kvm_vcpu *vcpu, u32 irq)
static noinline int kvmppc_h_eoi(struct kvm_vcpu *vcpu, unsigned long xirr)
int kvmppc_xics_rm_complete(struct kvm_vcpu *vcpu, u32 hcall)
int kvmppc_xics_hcall(struct kvm_vcpu *vcpu, u32 req)
static void xics_debugfs_irqmap(struct seq_file *m, struct kvmppc_passthru_irqmap *pimap)
static int xics_debug_show(struct seq_file *m, void *private)
static void xics_debugfs_init(struct kvmppc_xics *xics)
static struct kvmppc_ics *kvmppc_xics_create_ics(struct kvm *kvm, struct kvmppc_xics *xics, int irq)
static int kvmppc_xics_create_icp(struct kvm_vcpu *vcpu, unsigned long server_num)
u64 kvmppc_xics_get_icp(struct kvm_vcpu *vcpu)
int kvmppc_xics_set_icp(struct kvm_vcpu *vcpu, u64 icpval)
static int xics_get_source(struct kvmppc_xics *xics, long irq, u64 addr)
static int xics_set_source(struct kvmppc_xics *xics, long irq, u64 addr)
int kvmppc_xics_set_irq(struct kvm *kvm, int irq_source_id, u32 irq, int level, bool line_status)
static int xics_set_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static int xics_get_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static int xics_has_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
static void kvmppc_xics_free(struct kvm_device *dev)
static int kvmppc_xics_create(struct kvm_device *dev, u32 type)
static void kvmppc_xics_init(struct kvm_device *dev)
int kvmppc_xics_connect_vcpu(struct kvm_device *dev, struct kvm_vcpu *vcpu, u32 xcpu)
void kvmppc_xics_free_icp(struct kvm_vcpu *vcpu)
void kvmppc_xics_set_mapped(struct kvm *kvm, unsigned long irq, unsigned long host_irq)
void kvmppc_xics_clr_mapped(struct kvm *kvm, unsigned long irq, unsigned long host_irq)
\n
     13 struct kvm_vcpu *vcpu
     10 struct kvmppc_xics *xics
      8 u32 irq
      8 struct kvm *kvm
      7 struct kvm_device *dev
      6 struct kvmppc_icp *icp
      3 struct kvm_device_attr *attr
      2 unsigned long server
      2 unsigned long irq
      2 unsigned long host_irq
      2 u64 addr
      2 u32 server
      2 u32 priority
      2 struct seq_file *m
      2 struct kvmppc_ics *ics
      2 long irq
      1 void *private
      1 unsigned long xirr
      1 unsigned long server_num
      1 unsigned long mfrr
      1 unsigned long cppr
      1 union kvmppc_icp_state old
      1 union kvmppc_icp_state new
      1 u8 priority
      1 u8 new_cppr
      1 u64 icpval
      1 u32 xcpu
      1 u32 type
      1 u32 *server
      1 u32 saved_priority
      1 u32 req
      1 u32 *reject
      1 u32 *priority
      1 u32 new_irq
      1 u32 level
      1 u32 hcall
      1 struct kvmppc_passthru_irqmap *pimap
      1 struct ics_irq_state *state
      1 kvmppc_xics_set_mapped
      1 kvmppc_xics_rm_complete
      1 kvmppc_xics_hcall
      1 kvmppc_xics_clr_mapped
      1 int level
      1 int irq_source_id
      1 int irq
      1 bool line_status
      1 bool check_resend
      1 bool change_self
