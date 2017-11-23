
static inline void kvm_async_page_present_sync(struct kvm_vcpu *vcpu, struct kvm_async_pf *work)
static inline void kvm_async_page_present_sync(struct kvm_vcpu *vcpu, struct kvm_async_pf *work)
kvm_arch_async_page_present(vcpu, work)
;endif } static inline void kvm_async_page_present_async(struct kvm_vcpu *vcpu, struct kvm_async_pf *work)
int kvm_async_pf_init(void)
void kvm_async_pf_deinit(void)
void kvm_async_pf_vcpu_init(struct kvm_vcpu *vcpu)
static void async_pf_execute(struct work_struct *work)
void kvm_clear_async_pf_completion_queue(struct kvm_vcpu *vcpu)
void kvm_check_async_pf_completion(struct kvm_vcpu *vcpu)
int kvm_setup_async_pf(struct kvm_vcpu *vcpu, gva_t gva, unsigned long hva, struct kvm_arch_async_pf *arch)
int kvm_async_pf_wakeup_all(struct kvm_vcpu *vcpu)
   8 struct kvm_vcpu *vcpu
   3 struct kvm_async_pf *work
   2 void
   1 work
   1 vcpu
   1 unsigned long hva
   1 struct work_struct *work
   1 struct kvm_arch_async_pf *arch
   1 gva_t gva
