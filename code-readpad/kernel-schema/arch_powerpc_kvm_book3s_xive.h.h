
\n
static inline void kvmppc_xive_select_irq(struct kvmppc_xive_irq_state *state, u32 *out_hw_irq, struct xive_irq_data **out_xd)
static inline struct kvm_vcpu *kvmppc_xive_find_server(struct kvm *kvm, u32 nr)
static inline struct kvmppc_xive_src_block *kvmppc_xive_find_source(struct kvmppc_xive *xive, u32 irq, u16 *source)
static inline u8 xive_prio_from_guest(u8 prio)
static inline u8 xive_prio_to_guest(u8 prio)
static inline u32 __xive_read_eq(__be32 *qpage, u32 msk, u32 *idx, u32 *toggle)
\n
      2 u8 prio
      1 u32 *toggle
      1 u32 *out_hw_irq
      1 u32 nr
      1 u32 msk
      1 u32 irq
      1 u32 *idx
      1 u16 *source
      1 struct xive_irq_data **out_xd
      1 struct kvmppc_xive *xive
      1 struct kvmppc_xive_irq_state *state
      1 struct kvm *kvm
      1 __be32 *qpage
