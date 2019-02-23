
\n
static void GLUE(X_PFX, ack_pending)
(struct kvmppc_xive_vcpu *xc)
static u8 GLUE(X_PFX, esb_load)
(struct xive_irq_data *xd, u32 offset)
static void GLUE(X_PFX, source_eoi)
(u32 hw_irq, struct xive_irq_data *xd)
static u32 GLUE(X_PFX, scan_interrupts)
(struct kvmppc_xive_vcpu *xc, u8 pending, int scan_type)
X_STATIC unsigned long GLUE(X_PFX, h_xirr)
(struct kvm_vcpu *vcpu)
X_STATIC unsigned long GLUE(X_PFX, h_ipoll)
(struct kvm_vcpu *vcpu, unsigned long server)
static void GLUE(X_PFX, push_pending_to_hw)
(struct kvmppc_xive_vcpu *xc)
static void GLUE(X_PFX, scan_for_rerouted_irqs)
(struct kvmppc_xive *xive, struct kvmppc_xive_vcpu *xc)
X_STATIC int GLUE(X_PFX, h_cppr)
(struct kvm_vcpu *vcpu, unsigned long cppr)
X_STATIC int GLUE(X_PFX, h_eoi)
(struct kvm_vcpu *vcpu, unsigned long xirr)
X_STATIC int GLUE(X_PFX, h_ipi)
(struct kvm_vcpu *vcpu, unsigned long server, unsigned long mfrr)
\n
     11 X_PFX
      5 struct kvm_vcpu *vcpu
      4 struct kvmppc_xive_vcpu *xc
      2 unsigned long server
      2 struct xive_irq_data *xd
      1 unsigned long xirr
      1 unsigned long mfrr
      1 unsigned long cppr
      1 u8 pending
      1 u32 offset
      1 u32 hw_irq
      1 struct kvmppc_xive *xive
      1 source_eoi
      1 scan_interrupts
      1 scan_for_rerouted_irqs
      1 push_pending_to_hw
      1 int scan_type
      1 h_xirr
      1 h_ipoll
      1 h_ipi
      1 h_eoi
      1 h_cppr
      1 esb_load
      1 ack_pending
