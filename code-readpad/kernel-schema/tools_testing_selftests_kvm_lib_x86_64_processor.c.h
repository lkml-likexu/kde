
\n
void regs_dump(FILE *stream, struct kvm_regs *regs, uint8_t indent)
static void segment_dump(FILE *stream, struct kvm_segment *segment, uint8_t indent)
static void dtable_dump(FILE *stream, struct kvm_dtable *dtable, uint8_t indent)
void sregs_dump(FILE *stream, struct kvm_sregs *sregs, uint8_t indent)
void virt_pgd_alloc(struct kvm_vm *vm, uint32_t pgd_memslot)
void virt_pg_map(struct kvm_vm *vm, uint64_t vaddr, uint64_t paddr, uint32_t pgd_memslot)
void virt_dump(FILE *stream, struct kvm_vm *vm, uint8_t indent)
static void kvm_seg_set_unusable(struct kvm_segment *segp)
static void kvm_seg_fill_gdt_64bit(struct kvm_vm *vm, struct kvm_segment *segp)
static void kvm_seg_set_kernel_code_64bit(struct kvm_vm *vm, uint16_t selector, struct kvm_segment *segp)
static void kvm_seg_set_kernel_data_64bit(struct kvm_vm *vm, uint16_t selector, struct kvm_segment *segp)
vm_paddr_t addr_gva2gpa(struct kvm_vm *vm, vm_vaddr_t gva)
static void kvm_setup_gdt(struct kvm_vm *vm, struct kvm_dtable *dt, int gdt_memslot, int pgd_memslot)
static void kvm_setup_tss_64bit(struct kvm_vm *vm, struct kvm_segment *segp, int selector, int gdt_memslot, int pgd_memslot)
void vcpu_setup(struct kvm_vm *vm, int vcpuid, int pgd_memslot, int gdt_memslot)
sregs.cr3 = vm->pgd;vcpu_sregs_set(vm, vcpuid, &sregs)
; }void vm_vcpu_add_default(struct kvm_vm *vm, uint32_t vcpuid, void *guest_code)
static struct kvm_cpuid2 *allocate_kvm_cpuid2(void)
struct kvm_cpuid2 *kvm_get_supported_cpuid(void)
struct kvm_cpuid_entry2 * kvm_get_supported_cpuid_index(uint32_t function, uint32_t index)
void vcpu_set_cpuid(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_cpuid2 *cpuid)
struct kvm_vm *vm_create_default(uint32_t vcpuid, uint64_t extra_mem_pages, void *guest_code)
uint64_t vcpu_get_msr(struct kvm_vm *vm, uint32_t vcpuid, uint64_t msr_index)
void vcpu_set_msr(struct kvm_vm *vm, uint32_t vcpuid, uint64_t msr_index, uint64_t msr_value)
void vcpu_args_set(struct kvm_vm *vm, uint32_t vcpuid, unsigned int num, ...)
void vcpu_dump(FILE *stream, struct kvm_vm *vm, uint32_t vcpuid, uint8_t indent)
static int kvm_get_num_msrs(struct kvm_vm *vm)
struct kvm_x86_state *vcpu_save_state(struct kvm_vm *vm, uint32_t vcpuid)
void vcpu_load_state(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_x86_state *state)
\n
     19 struct kvm_vm *vm
      9 uint32_t vcpuid
      6 uint8_t indent
      6 FILE *stream
      5 struct kvm_segment *segp
      3 int pgd_memslot
      3 int gdt_memslot
      2 void *guest_code
      2 void
      2 uint64_t msr_index
      2 uint32_t pgd_memslot
      2 uint16_t selector
      1 vm_vaddr_t gva
      1 vm
      1 vcpuid
      1 unsigned int num
      1 uint64_t vaddr
      1 uint64_t paddr
      1 uint64_t msr_value
      1 uint64_t extra_mem_pages
      1 uint32_t index
      1 uint32_t function
      1 struct kvm_x86_state *state
      1 struct kvm_sregs *sregs
      1 struct kvm_segment *segment
      1 struct kvm_regs *regs
      1 struct kvm_dtable *dtable
      1 struct kvm_dtable *dt
      1 struct kvm_cpuid2 *cpuid
      1 &sregs
      1 int vcpuid
      1 int selector
      1 ...
