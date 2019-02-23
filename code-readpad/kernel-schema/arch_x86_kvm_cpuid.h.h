
\n
static inline int cpuid_maxphyaddr(struct kvm_vcpu *vcpu)
static __always_inline struct cpuid_reg x86_feature_cpuid(unsigned x86_feature)
static __always_inline int *guest_cpuid_get_register(struct kvm_vcpu *vcpu, unsigned x86_feature)
static __always_inline bool guest_cpuid_has(struct kvm_vcpu *vcpu, unsigned x86_feature)
static __always_inline void guest_cpuid_clear(struct kvm_vcpu *vcpu, unsigned x86_feature)
static inline bool guest_cpuid_is_amd(struct kvm_vcpu *vcpu)
static inline int guest_cpuid_family(struct kvm_vcpu *vcpu)
static inline int guest_cpuid_model(struct kvm_vcpu *vcpu)
static inline int guest_cpuid_stepping(struct kvm_vcpu *vcpu)
static inline bool supports_cpuid_fault(struct kvm_vcpu *vcpu)
static inline bool cpuid_fault_enabled(struct kvm_vcpu *vcpu)
\n
     10 struct kvm_vcpu *vcpu
      4 unsigned x86_feature
