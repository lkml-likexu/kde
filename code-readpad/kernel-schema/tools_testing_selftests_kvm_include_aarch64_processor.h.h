
\n
static inline void get_reg(struct kvm_vm *vm, uint32_t vcpuid, uint64_t id, uint64_t *addr)
static inline void set_reg(struct kvm_vm *vm, uint32_t vcpuid, uint64_t id, uint64_t val)
\n
      2 uint64_t id
      2 uint32_t vcpuid
      2 struct kvm_vm *vm
      1 uint64_t val
      1 uint64_t *addr
