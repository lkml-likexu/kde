
\n
static inline bool pi_test_and_set_on(struct pi_desc *pi_desc)
static inline bool pi_test_and_clear_on(struct pi_desc *pi_desc)
static inline int pi_test_and_set_pir(int vector, struct pi_desc *pi_desc)
static inline void pi_set_sn(struct pi_desc *pi_desc)
static inline void pi_set_on(struct pi_desc *pi_desc)
static inline void pi_clear_on(struct pi_desc *pi_desc)
static inline int pi_test_on(struct pi_desc *pi_desc)
static inline int pi_test_sn(struct pi_desc *pi_desc)
static inline u8 vmx_get_rvi(void)
static inline void vm_entry_controls_reset_shadow(struct vcpu_vmx *vmx)
static inline void vm_entry_controls_init(struct vcpu_vmx *vmx, u32 val)
static inline void vm_entry_controls_set(struct vcpu_vmx *vmx, u32 val)
static inline u32 vm_entry_controls_get(struct vcpu_vmx *vmx)
static inline void vm_entry_controls_setbit(struct vcpu_vmx *vmx, u32 val)
static inline void vm_entry_controls_clearbit(struct vcpu_vmx *vmx, u32 val)
static inline void vm_exit_controls_reset_shadow(struct vcpu_vmx *vmx)
static inline void vm_exit_controls_init(struct vcpu_vmx *vmx, u32 val)
static inline void vm_exit_controls_set(struct vcpu_vmx *vmx, u32 val)
static inline u32 vm_exit_controls_get(struct vcpu_vmx *vmx)
static inline void vm_exit_controls_setbit(struct vcpu_vmx *vmx, u32 val)
static inline void vm_exit_controls_clearbit(struct vcpu_vmx *vmx, u32 val)
static inline void vmx_segment_cache_clear(struct vcpu_vmx *vmx)
static inline u32 vmx_vmentry_ctrl(void)
static inline u32 vmx_vmexit_ctrl(void)
static inline struct kvm_vmx *to_kvm_vmx(struct kvm *kvm)
static inline struct vcpu_vmx *to_vmx(struct kvm_vcpu *vcpu)
static inline struct pi_desc *vcpu_to_pi_desc(struct kvm_vcpu *vcpu)
static inline struct vmcs *alloc_vmcs(bool shadow)
static inline void __vmx_flush_tlb(struct kvm_vcpu *vcpu, int vpid, bool invalidate_gpa)
static inline void vmx_flush_tlb(struct kvm_vcpu *vcpu, bool invalidate_gpa)
static inline void decache_tsc_multiplier(struct vcpu_vmx *vmx)
\n
     14 struct vcpu_vmx *vmx
      8 u32 val
      8 struct pi_desc *pi_desc
      4 struct kvm_vcpu *vcpu
      3 void
      2 bool invalidate_gpa
      1 struct kvm *kvm
      1 int vpid
      1 int vector
      1 bool shadow
