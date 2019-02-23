
\n
void __hyp_text __kvm_tlb_flush_vmid(struct kvm *kvm)
void __hyp_text __kvm_tlb_flush_vmid_ipa(struct kvm *kvm, phys_addr_t ipa)
void __hyp_text __kvm_tlb_flush_local_vmid(struct kvm_vcpu *vcpu)
void __hyp_text __kvm_flush_vm_context(void)
\n
      2 struct kvm *kvm
      1 void
      1 struct kvm_vcpu *vcpu
      1 phys_addr_t ipa
