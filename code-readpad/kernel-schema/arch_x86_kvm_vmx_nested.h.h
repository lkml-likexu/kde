
\n
static inline struct vmcs12 *get_vmcs12(struct kvm_vcpu *vcpu)
static inline struct vmcs12 *get_shadow_vmcs12(struct kvm_vcpu *vcpu)
static inline int vmx_has_valid_vmcs12(struct kvm_vcpu *vcpu)
static inline unsigned long nested_ept_get_cr3(struct kvm_vcpu *vcpu)
static inline bool nested_ept_ad_enabled(struct kvm_vcpu *vcpu)
static inline int nested_vmx_reflect_vmexit(struct kvm_vcpu *vcpu, u32 exit_reason)
static inline unsigned long nested_read_cr0(struct vmcs12 *fields)
static inline unsigned long nested_read_cr0(struct vmcs12 *fields)
return (fields->guest_cr0 & ~fields->cr0_guest_host_mask)
| (fields->cr0_read_shadow & fields->cr0_guest_host_mask)
; } static inline unsigned long nested_read_cr4(struct vmcs12 *fields)
static inline unsigned nested_cpu_vmx_misc_cr3_count(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_has_vmwrite_any_field(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_has_zero_length_injection(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_supports_monitor_trap_flag(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_has_vmx_shadow_vmcs(struct kvm_vcpu *vcpu)
static inline bool nested_cpu_has(struct vmcs12 *vmcs12, u32 bit)
static inline bool nested_cpu_has2(struct vmcs12 *vmcs12, u32 bit)
static inline bool nested_cpu_has_preemption_timer(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_nmi_exiting(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_virtual_nmis(struct vmcs12 *vmcs12)
static inline int nested_cpu_has_ept(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_xsaves(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_pml(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_virt_x2apic_mode(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_vpid(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_apic_reg_virt(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_vid(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_posted_intr(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_vmfunc(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_eptp_switching(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_shadow_vmcs(struct vmcs12 *vmcs12)
static inline bool nested_cpu_has_save_preemption_timer(struct vmcs12 *vmcs12)
static inline bool nested_exit_on_intr(struct kvm_vcpu *vcpu)
static inline bool fixed_bits_valid(u64 val, u64 fixed0, u64 fixed1)
static bool nested_guest_cr0_valid(struct kvm_vcpu *vcpu, unsigned long val)
static bool nested_host_cr0_valid(struct kvm_vcpu *vcpu, unsigned long val)
static bool nested_cr4_valid(struct kvm_vcpu *vcpu, unsigned long val)
\n
     17 struct vmcs12 *vmcs12
     15 struct kvm_vcpu *vcpu
      3 unsigned long val
      3 struct vmcs12 *fields
      2 u32 bit
      1 u64 val
      1 u64 fixed1
      1 u64 fixed0
      1 u32 exit_reason
      1 fields->guest_cr0 & ~fields->cr0_guest_host_mask
      1 fields->cr0_read_shadow & fields->cr0_guest_host_mask
