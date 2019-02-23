
\n
static void __hyp_text __tlb_switch_to_guest_vhe(struct kvm *kvm, struct tlb_inv_context *cxt)
static void __hyp_text __tlb_switch_to_guest_nvhe(struct kvm *kvm, struct tlb_inv_context *cxt)
static void __hyp_text __tlb_switch_to_host_vhe(struct kvm *kvm, struct tlb_inv_context *cxt)
static void __hyp_text __tlb_switch_to_host_nvhe(struct kvm *kvm, struct tlb_inv_context *cxt)
void __hyp_text __kvm_tlb_flush_vmid_ipa(struct kvm *kvm, phys_addr_t ipa)
void __hyp_text __kvm_tlb_flush_vmid(struct kvm *kvm)
void __hyp_text __kvm_tlb_flush_local_vmid(struct kvm_vcpu *vcpu)
void __hyp_text __kvm_flush_vm_context(void)
\n
      6 struct kvm *kvm
      4 struct tlb_inv_context *cxt
      1 void
      1 struct kvm_vcpu *vcpu
      1 phys_addr_t ipa
