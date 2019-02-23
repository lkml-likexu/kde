
\n
static void *align(void *x, size_t size)
int kvm_check_cap(long cap)
int vm_enable_cap(struct kvm_vm *vm, struct kvm_enable_cap *cap)
static void vm_open(struct kvm_vm *vm, int perm, unsigned long type)
struct kvm_vm *_vm_create(enum vm_guest_mode mode, uint64_t phy_pages, int perm, unsigned long type)
struct kvm_vm *vm_create(enum vm_guest_mode mode, uint64_t phy_pages, int perm)
void kvm_vm_restart(struct kvm_vm *vmp, int perm)
void kvm_vm_get_dirty_log(struct kvm_vm *vm, int slot, void *log)
void kvm_vm_clear_dirty_log(struct kvm_vm *vm, int slot, void *log, uint64_t first_page, uint32_t num_pages)
static struct userspace_mem_region * userspace_mem_region_find(struct kvm_vm *vm, uint64_t start, uint64_t end)
struct kvm_userspace_memory_region * kvm_userspace_memory_region_find(struct kvm_vm *vm, uint64_t start, uint64_t end)
struct vcpu *vcpu_find(struct kvm_vm *vm, uint32_t vcpuid)
static void vm_vcpu_rm(struct kvm_vm *vm, uint32_t vcpuid)
void kvm_vm_release(struct kvm_vm *vmp)
void kvm_vm_free(struct kvm_vm *vmp)
int kvm_memcmp_hva_gva(void *hva, struct kvm_vm *vm, vm_vaddr_t gva, size_t len)
void vm_userspace_mem_region_add(struct kvm_vm *vm, enum vm_mem_backing_src_type src_type, uint64_t guest_paddr, uint32_t slot, uint64_t npages, uint32_t flags)
static struct userspace_mem_region * memslot2region(struct kvm_vm *vm, uint32_t memslot)
void vm_mem_region_set_flags(struct kvm_vm *vm, uint32_t slot, uint32_t flags)
static int vcpu_mmap_sz(void)
void vm_vcpu_add(struct kvm_vm *vm, uint32_t vcpuid, int pgd_memslot, int gdt_memslot)
static vm_vaddr_t vm_vaddr_unused_gap(struct kvm_vm *vm, size_t sz, vm_vaddr_t vaddr_min)
vm_vaddr_t vm_vaddr_alloc(struct kvm_vm *vm, size_t sz, vm_vaddr_t vaddr_min, uint32_t data_memslot, uint32_t pgd_memslot)
void virt_map(struct kvm_vm *vm, uint64_t vaddr, uint64_t paddr, size_t size, uint32_t pgd_memslot)
void *addr_gpa2hva(struct kvm_vm *vm, vm_paddr_t gpa)
vm_paddr_t addr_hva2gpa(struct kvm_vm *vm, void *hva)
void vm_create_irqchip(struct kvm_vm *vm)
struct kvm_run *vcpu_state(struct kvm_vm *vm, uint32_t vcpuid)
void vcpu_run(struct kvm_vm *vm, uint32_t vcpuid)
int _vcpu_run(struct kvm_vm *vm, uint32_t vcpuid)
void vcpu_set_mp_state(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_mp_state *mp_state)
void vcpu_regs_get(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_regs *regs)
void vcpu_regs_set(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_regs *regs)
void vcpu_events_get(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_vcpu_events *events)
void vcpu_events_set(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_vcpu_events *events)
void vcpu_sregs_get(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_sregs *sregs)
void vcpu_sregs_set(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_sregs *sregs)
int _vcpu_sregs_set(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_sregs *sregs)
void vcpu_ioctl(struct kvm_vm *vm, uint32_t vcpuid, unsigned long cmd, void *arg)
int _vcpu_ioctl(struct kvm_vm *vm, uint32_t vcpuid, unsigned long cmd, void *arg)
void vm_ioctl(struct kvm_vm *vm, unsigned long cmd, void *arg)
void vm_dump(FILE *stream, struct kvm_vm *vm, uint8_t indent)
const char *exit_reason_str(unsigned int exit_reason)
vm_paddr_t vm_phy_pages_alloc(struct kvm_vm *vm, size_t num, vm_paddr_t paddr_min, uint32_t memslot)
vm_paddr_t vm_phy_page_alloc(struct kvm_vm *vm, vm_paddr_t paddr_min, uint32_t memslot)
void *addr_gva2hva(struct kvm_vm *vm, vm_vaddr_t gva)
\n
     37 struct kvm_vm *vm
     16 uint32_t vcpuid
      4 int perm
      3 void *arg
      3 unsigned long cmd
      3 uint32_t memslot
      3 struct kvm_vm *vmp
      3 struct kvm_sregs *sregs
      2 void *log
      2 void *hva
      2 vm_vaddr_t vaddr_min
      2 vm_vaddr_t gva
      2 vm_paddr_t paddr_min
      2 unsigned long type
      2 uint64_t start
      2 uint64_t phy_pages
      2 uint64_t end
      2 uint32_t slot
      2 uint32_t pgd_memslot
      2 uint32_t flags
      2 struct kvm_vcpu_events *events
      2 struct kvm_regs *regs
      2 size_t sz
      2 size_t size
      2 int slot
      2 enum vm_guest_mode mode
      1 void *x
      1 void
      1 vm_paddr_t gpa
      1 unsigned int exit_reason
      1 uint8_t indent
      1 uint64_t vaddr
      1 uint64_t paddr
      1 uint64_t npages
      1 uint64_t guest_paddr
      1 uint64_t first_page
      1 uint32_t num_pages
      1 uint32_t data_memslot
      1 struct kvm_mp_state *mp_state
      1 struct kvm_enable_cap *cap
      1 size_t num
      1 size_t len
      1 long cap
      1 int pgd_memslot
      1 int gdt_memslot
      1 FILE *stream
      1 enum vm_mem_backing_src_type src_type
