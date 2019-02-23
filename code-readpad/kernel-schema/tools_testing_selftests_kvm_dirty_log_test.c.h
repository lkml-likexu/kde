
\n
static void guest_code(void)
static void generate_random_array(uint64_t *guest_array, uint64_t size)
static void *vcpu_worker(void *data)
static void vm_dirty_log_verify(unsigned long *bmap)
static struct kvm_vm *create_vm(enum vm_guest_mode mode, uint32_t vcpuid, uint64_t extra_mem_pages, void *guest_code, unsigned long type)
static void run_test(enum vm_guest_mode mode, unsigned long iterations, unsigned long interval, uint64_t phys_offset)
static void help(char *name)
int main(int argc, char *argv[])
\n
      2 enum vm_guest_mode mode
      1 void *guest_code
      1 void *data
      1 void
      1 unsigned long type
      1 unsigned long iterations
      1 unsigned long interval
      1 unsigned long *bmap
      1 uint64_t size
      1 uint64_t phys_offset
      1 uint64_t *guest_array
      1 uint64_t extra_mem_pages
      1 uint32_t vcpuid
      1 int argc
      1 char *name
      1 char *argv[]
