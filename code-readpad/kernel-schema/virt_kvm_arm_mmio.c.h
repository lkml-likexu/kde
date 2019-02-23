
\n
void kvm_mmio_write_buf(void *buf, unsigned int len, unsigned long data)
unsigned long kvm_mmio_read_buf(const void *buf, unsigned int len)
int kvm_handle_mmio_return(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int decode_hsr(struct kvm_vcpu *vcpu, bool *is_write, int *len)
int io_mem_abort(struct kvm_vcpu *vcpu, struct kvm_run *run, phys_addr_t fault_ipa)
\n
      3 struct kvm_vcpu *vcpu
      2 unsigned int len
      2 struct kvm_run *run
      1 void *buf
      1 unsigned long data
      1 phys_addr_t fault_ipa
      1 int *len
      1 const void *buf
      1 bool *is_write
