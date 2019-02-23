
\n
static inline bool kvm_hv_vapic_assist_page_enabled(struct kvm_vcpu *vcpu)
static inline void kvm_lapic_set_vector(int vec, void *bitmap)
static inline void kvm_lapic_set_irr(int vec, struct kvm_lapic *apic)
static inline u32 kvm_lapic_get_reg(struct kvm_lapic *apic, int reg_off)
static inline void kvm_lapic_set_reg(struct kvm_lapic *apic, int reg_off, u32 val)
static inline bool lapic_in_kernel(struct kvm_vcpu *vcpu)
static inline int kvm_apic_hw_enabled(struct kvm_lapic *apic)
static inline bool kvm_apic_sw_enabled(struct kvm_lapic *apic)
static inline bool kvm_apic_present(struct kvm_vcpu *vcpu)
static inline int kvm_lapic_enabled(struct kvm_vcpu *vcpu)
static inline int apic_x2apic_mode(struct kvm_lapic *apic)
static inline bool kvm_vcpu_apicv_active(struct kvm_vcpu *vcpu)
static inline bool kvm_apic_has_events(struct kvm_vcpu *vcpu)
static inline bool kvm_lowest_prio_delivery(struct kvm_lapic_irq *irq)
static inline int kvm_lapic_latched_init(struct kvm_vcpu *vcpu)
static inline enum lapic_mode kvm_apic_mode(u64 apic_base)
\n
      7 struct kvm_vcpu *vcpu
      6 struct kvm_lapic *apic
      2 int vec
      2 int reg_off
      1 void *bitmap
      1 u64 apic_base
      1 u32 val
      1 struct kvm_lapic_irq *irq
