
\n
static void ics_rm_check_resend(struct kvmppc_xics *xics, struct kvmppc_ics *ics, struct kvmppc_icp *icp)
static inline void icp_send_hcore_msg(int hcore, struct kvm_vcpu *vcpu)
static inline int grab_next_hostcore(int start, struct kvmppc_host_rm_core *rm_core, int max, int action)
static inline int find_available_hostcore(int action)
static void icp_rm_set_vcpu_irq(struct kvm_vcpu *vcpu, struct kvm_vcpu *this_vcpu)
static void icp_rm_clr_vcpu_irq(struct kvm_vcpu *vcpu)
static inline bool icp_rm_try_update(struct kvmppc_icp *icp, union kvmppc_icp_state old, union kvmppc_icp_state new)
static inline int check_too_hard(struct kvmppc_xics *xics, struct kvmppc_icp *icp)
static void icp_rm_check_resend(struct kvmppc_xics *xics, struct kvmppc_icp *icp)
static bool icp_rm_try_to_deliver(struct kvmppc_icp *icp, u32 irq, u8 priority, u32 *reject)
static void icp_rm_deliver_irq(struct kvmppc_xics *xics, struct kvmppc_icp *icp, u32 new_irq, bool check_resend)
static void icp_rm_down_cppr(struct kvmppc_xics *xics, struct kvmppc_icp *icp, u8 new_cppr)
unsigned long xics_rm_h_xirr(struct kvm_vcpu *vcpu)
int xics_rm_h_ipi(struct kvm_vcpu *vcpu, unsigned long server, unsigned long mfrr)
int xics_rm_h_cppr(struct kvm_vcpu *vcpu, unsigned long cppr)
static int ics_rm_eoi(struct kvm_vcpu *vcpu, u32 irq)
int xics_rm_h_eoi(struct kvm_vcpu *vcpu, unsigned long xirr)
static void icp_eoi(struct irq_chip *c, u32 hwirq, __be32 xirr, bool *again)
static int xics_opal_set_server(unsigned int hw_irq, int server_cpu)
static inline void this_cpu_inc_rm(unsigned int __percpu *addr)
static void kvmppc_rm_handle_irq_desc(struct irq_desc *desc)
long kvmppc_deliver_irq_passthru(struct kvm_vcpu *vcpu, __be32 xirr, struct kvmppc_irq_map *irq_map, struct kvmppc_passthru_irqmap *pimap, bool *again)
static void rm_host_ipi_action(int action, void *data)
void kvmppc_xics_ipi_action(void)
\n
      9 struct kvm_vcpu *vcpu
      7 struct kvmppc_icp *icp
      5 struct kvmppc_xics *xics
      3 int action
      2 u32 irq
      2 bool *again
      2 __be32 xirr
      1 void *data
      1 void
      1 unsigned long xirr
      1 unsigned long server
      1 unsigned long mfrr
      1 unsigned long cppr
      1 unsigned int __percpu *addr
      1 unsigned int hw_irq
      1 union kvmppc_icp_state old
      1 union kvmppc_icp_state new
      1 u8 priority
      1 u8 new_cppr
      1 u32 *reject
      1 u32 new_irq
      1 u32 hwirq
      1 struct kvm_vcpu *this_vcpu
      1 struct kvmppc_passthru_irqmap *pimap
      1 struct kvmppc_irq_map *irq_map
      1 struct kvmppc_ics *ics
      1 struct kvmppc_host_rm_core *rm_core
      1 struct irq_desc *desc
      1 struct irq_chip *c
      1 int start
      1 int server_cpu
      1 int max
      1 int hcore
      1 bool check_resend
