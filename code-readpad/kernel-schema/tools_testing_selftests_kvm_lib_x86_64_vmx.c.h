
\n
struct vmx_pages * vcpu_alloc_vmx(struct kvm_vm *vm, vm_vaddr_t *p_vmx_gva)
bool prepare_for_vmx_operation(struct vmx_pages *vmx)
bool load_vmcs(struct vmx_pages *vmx)
static inline void init_vmcs_control_fields(struct vmx_pages *vmx)
static inline void init_vmcs_host_state(void)
static inline void init_vmcs_guest_state(void *rip, void *rsp)
void prepare_vmcs(struct vmx_pages *vmx, void *guest_rip, void *guest_rsp)
\n
      4 struct vmx_pages *vmx
      1 void *rsp
      1 void *rip
      1 void *guest_rsp
      1 void *guest_rip
      1 void
      1 vm_vaddr_t *p_vmx_gva
      1 struct kvm_vm *vm
