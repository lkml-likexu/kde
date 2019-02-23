
\n
static inline bool irq_is_pending(struct vgic_irq *irq)
static inline bool vgic_irq_is_mapped_level(struct vgic_irq *irq)
static inline int vgic_irq_get_lr_count(struct vgic_irq *irq)
static inline bool vgic_irq_is_multi_sgi(struct vgic_irq *irq)
static inline void vgic_get_irq_kref(struct vgic_irq *irq)
static inline int vgic_v3_max_apr_idx(struct kvm_vcpu *vcpu)
static inline bool vgic_v3_redist_region_full(struct vgic_redist_region *region)
static inline size_t vgic_v3_rd_region_size(struct kvm *kvm, struct vgic_redist_region *rdreg)
static inline bool vgic_dist_overlap(struct kvm *kvm, gpa_t base, size_t size)
\n
      5 struct vgic_irq *irq
      2 struct kvm *kvm
      1 struct vgic_redist_region *region
      1 struct vgic_redist_region *rdreg
      1 struct kvm_vcpu *vcpu
      1 size_t size
      1 gpa_t base
