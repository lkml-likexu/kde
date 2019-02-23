
\n
static bool ucall_mmio_init(struct kvm_vm *vm, vm_paddr_t gpa)
void ucall_init(struct kvm_vm *vm, ucall_type_t type, void *arg)
void ucall_uninit(struct kvm_vm *vm)
static void ucall_pio_exit(struct ucall *uc)
static void ucall_mmio_exit(struct ucall *uc)
void ucall(uint64_t cmd, int nargs, ...)
uint64_t get_ucall(struct kvm_vm *vm, uint32_t vcpu_id, struct ucall *uc)
\n
      4 struct kvm_vm *vm
      3 struct ucall *uc
      1 void *arg
      1 vm_paddr_t gpa
      1 uint64_t cmd
      1 uint32_t vcpu_id
      1 ucall_type_t type
      1 int nargs
      1 ...
