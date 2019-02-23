
\n
static uint64_t page_align(struct kvm_vm *vm, uint64_t v)
static uint64_t pgd_index(struct kvm_vm *vm, vm_vaddr_t gva)
static uint64_t pud_index(struct kvm_vm *vm, vm_vaddr_t gva)
static uint64_t pmd_index(struct kvm_vm *vm, vm_vaddr_t gva)
static uint64_t pte_index(struct kvm_vm *vm, vm_vaddr_t gva)
static uint64_t pte_addr(struct kvm_vm *vm, uint64_t entry)
static uint64_t ptrs_per_pgd(struct kvm_vm *vm)
static uint64_t ptrs_per_pte(struct kvm_vm *vm)
void virt_pgd_alloc(struct kvm_vm *vm, uint32_t pgd_memslot)
void _virt_pg_map(struct kvm_vm *vm, uint64_t vaddr, uint64_t paddr, uint32_t pgd_memslot, uint64_t flags)
void virt_pg_map(struct kvm_vm *vm, uint64_t vaddr, uint64_t paddr, uint32_t pgd_memslot)
vm_paddr_t addr_gva2gpa(struct kvm_vm *vm, vm_vaddr_t gva)
static void pte_dump(FILE *stream, struct kvm_vm *vm, uint8_t indent, uint64_t page, int level)
void virt_dump(FILE *stream, struct kvm_vm *vm, uint8_t indent)
struct kvm_vm *vm_create_default(uint32_t vcpuid, uint64_t extra_mem_pages, void *guest_code)
void vm_vcpu_add_default(struct kvm_vm *vm, uint32_t vcpuid, void *guest_code)
void vcpu_setup(struct kvm_vm *vm, int vcpuid, int pgd_memslot, int gdt_memslot)
void vcpu_dump(FILE *stream, struct kvm_vm *vm, uint32_t vcpuid, uint8_t indent)
\n
     17 struct kvm_vm *vm
      5 vm_vaddr_t gva
      3 uint8_t indent
      3 uint32_t vcpuid
      3 uint32_t pgd_memslot
      3 FILE *stream
      2 void *guest_code
      2 uint64_t vaddr
      2 uint64_t paddr
      1 uint64_t v
      1 uint64_t page
      1 uint64_t flags
      1 uint64_t extra_mem_pages
      1 uint64_t entry
      1 int vcpuid
      1 int pgd_memslot
      1 int level
      1 int gdt_memslot
