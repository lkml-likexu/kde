
\n
static int diag_release_pages(struct kvm_vcpu *vcpu)
static int __diag_page_ref_service(struct kvm_vcpu *vcpu)
static int __diag_time_slice_end(struct kvm_vcpu *vcpu)
static int __diag_time_slice_end_directed(struct kvm_vcpu *vcpu)
static int __diag_ipl_functions(struct kvm_vcpu *vcpu)
static int __diag_virtio_hypercall(struct kvm_vcpu *vcpu)
int kvm_s390_handle_diag(struct kvm_vcpu *vcpu)
\n
      7 struct kvm_vcpu *vcpu
