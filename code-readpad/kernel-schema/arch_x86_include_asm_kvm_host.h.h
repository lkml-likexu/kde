
\n
static inline gfn_t gfn_to_index(gfn_t gfn, gfn_t base_gfn, int level)
define __KVM_HAVE_ARCH_VM_ALLOC static inline struct kvm *kvm_arch_alloc_vm(void)
static inline void kvm_arch_free_vm(struct kvm *kvm)
define __KVM_HAVE_ARCH_FLUSH_REMOTE_TLB static inline int kvm_arch_flush_remote_tlb(struct kvm *kvm)
static inline int __kvm_irq_line_state(unsigned long *irq_state, int irq_source_id, int level)
static inline gpa_t translate_gpa(struct kvm_vcpu *vcpu, gpa_t gpa, u32 access, struct x86_exception *exception)
static inline struct kvm_mmu_page *page_header(hpa_t shadow_page)
static inline u16 kvm_read_ldt(void)
static inline void kvm_load_ldt(u16 sel)
static inline unsigned long read_msr(unsigned long msr)
static inline u32 get_rdx_init_val(void)
static inline void kvm_inject_gp(struct kvm_vcpu *vcpu, u32 error_code)
static inline void kvm_arch_vcpu_blocking(struct kvm_vcpu *vcpu)
static inline void kvm_arch_vcpu_unblocking(struct kvm_vcpu *vcpu)
static inline int kvm_cpu_get_apicid(int mps_cpu)
\n
      4 struct kvm_vcpu *vcpu
      3 void
      2 struct kvm *kvm
      2 int level
      1 unsigned long msr
      1 unsigned long *irq_state
      1 u32 error_code
      1 u32 access
      1 u16 sel
      1 struct x86_exception *exception
      1 int mps_cpu
      1 int irq_source_id
      1 hpa_t shadow_page
      1 gpa_t gpa
      1 gfn_t gfn
      1 gfn_t base_gfn
