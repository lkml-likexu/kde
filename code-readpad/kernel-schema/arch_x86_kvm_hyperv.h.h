
\n
static inline struct kvm_vcpu_hv *vcpu_to_hv_vcpu(struct kvm_vcpu *vcpu)
static inline struct kvm_vcpu *hv_vcpu_to_vcpu(struct kvm_vcpu_hv *hv_vcpu)
static inline struct kvm_vcpu_hv_synic *vcpu_to_synic(struct kvm_vcpu *vcpu)
static inline struct kvm_vcpu *synic_to_vcpu(struct kvm_vcpu_hv_synic *synic)
static inline struct kvm_vcpu_hv_stimer *vcpu_to_stimer(struct kvm_vcpu *vcpu, int timer_index)
static inline struct kvm_vcpu *stimer_to_vcpu(struct kvm_vcpu_hv_stimer *stimer)
static inline bool kvm_hv_has_stimer_pending(struct kvm_vcpu *vcpu)
\n
      4 struct kvm_vcpu *vcpu
      1 struct kvm_vcpu_hv_synic *synic
      1 struct kvm_vcpu_hv_stimer *stimer
      1 struct kvm_vcpu_hv *hv_vcpu
      1 int timer_index
