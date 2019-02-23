
\n
static struct vgic_irq *vgic_get_lpi(struct kvm *kvm, u32 intid)
struct vgic_irq *vgic_get_irq(struct kvm *kvm, struct kvm_vcpu *vcpu, u32 intid)
static void vgic_irq_release(struct kref *ref)
void vgic_put_irq(struct kvm *kvm, struct vgic_irq *irq)
void vgic_irq_set_phys_pending(struct vgic_irq *irq, bool pending)
bool vgic_get_phys_line_level(struct vgic_irq *irq)
void vgic_irq_set_phys_active(struct vgic_irq *irq, bool active)
static struct kvm_vcpu *vgic_target_oracle(struct vgic_irq *irq)
static int vgic_irq_cmp(void *priv, struct list_head *a, struct list_head *b)
static void vgic_sort_ap_list(struct kvm_vcpu *vcpu)
static bool vgic_validate_injection(struct vgic_irq *irq, bool level, void *owner)
bool vgic_queue_irq_unlock(struct kvm *kvm, struct vgic_irq *irq, unsigned long flags)
int kvm_vgic_inject_irq(struct kvm *kvm, int cpuid, unsigned int intid, bool level, void *owner)
static int kvm_vgic_map_irq(struct kvm_vcpu *vcpu, struct vgic_irq *irq, unsigned int host_irq, bool (*get_input_level)
(int vindid)
)
static inline void kvm_vgic_unmap_irq(struct vgic_irq *irq)
int kvm_vgic_map_phys_irq(struct kvm_vcpu *vcpu, unsigned int host_irq, u32 vintid, bool (*get_input_level)
(int vindid)
)
void kvm_vgic_reset_mapped_irq(struct kvm_vcpu *vcpu, u32 vintid)
int kvm_vgic_unmap_phys_irq(struct kvm_vcpu *vcpu, unsigned int vintid)
int kvm_vgic_set_owner(struct kvm_vcpu *vcpu, unsigned int intid, void *owner)
static void vgic_prune_ap_list(struct kvm_vcpu *vcpu)
static inline void vgic_fold_lr_state(struct kvm_vcpu *vcpu)
static inline void vgic_populate_lr(struct kvm_vcpu *vcpu, struct vgic_irq *irq, int lr)
static inline void vgic_clear_lr(struct kvm_vcpu *vcpu, int lr)
static inline void vgic_set_underflow(struct kvm_vcpu *vcpu)
static int compute_ap_list_depth(struct kvm_vcpu *vcpu, bool *multi_sgi)
static void vgic_flush_lr_state(struct kvm_vcpu *vcpu)
static inline bool can_access_vgic_from_kernel(void)
static inline void vgic_save_state(struct kvm_vcpu *vcpu)
void kvm_vgic_sync_hwstate(struct kvm_vcpu *vcpu)
static inline void vgic_restore_state(struct kvm_vcpu *vcpu)
void kvm_vgic_flush_hwstate(struct kvm_vcpu *vcpu)
void kvm_vgic_load(struct kvm_vcpu *vcpu)
void kvm_vgic_put(struct kvm_vcpu *vcpu)
int kvm_vgic_vcpu_pending_irq(struct kvm_vcpu *vcpu)
void vgic_kick_vcpus(struct kvm *kvm)
bool kvm_vgic_map_is_active(struct kvm_vcpu *vcpu, unsigned int vintid)
\n
     22 struct kvm_vcpu *vcpu
     10 struct vgic_irq *irq
      6 struct kvm *kvm
      3 void *owner
      2 unsigned int vintid
      2 unsigned int intid
      2 unsigned int host_irq
      2 u32 vintid
      2 u32 intid
      2 int vindid
      2 int lr
      2 bool level
      2 bool *get_input_level
      1 void *priv
      1 void
      1 unsigned long flags
      1 struct list_head *b
      1 struct list_head *a
      1 struct kref *ref
      1 int cpuid
      1 bool pending
      1 bool *multi_sgi
      1 bool active
