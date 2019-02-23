
\n
int kvm_guest_mode_change_trace_reg(void)
void kvm_guest_mode_change_trace_unreg(void)
int kvm_arch_vcpu_runnable(struct kvm_vcpu *vcpu)
bool kvm_arch_vcpu_in_kernel(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_should_kick(struct kvm_vcpu *vcpu)
int kvm_arch_hardware_enable(void)
void kvm_arch_hardware_disable(void)
int kvm_arch_hardware_setup(void)
void kvm_arch_check_processor_compat(void *rtn)
int kvm_arch_init_vm(struct kvm *kvm, unsigned long type)
bool kvm_arch_has_vcpu_debugfs(void)
int kvm_arch_create_vcpu_debugfs(struct kvm_vcpu *vcpu)
void kvm_mips_free_vcpus(struct kvm *kvm)
static void kvm_mips_free_gpa_pt(struct kvm *kvm)
void kvm_arch_destroy_vm(struct kvm *kvm)
long kvm_arch_dev_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
int kvm_arch_create_memslot(struct kvm *kvm, struct kvm_memory_slot *slot, unsigned long npages)
void kvm_arch_flush_shadow_all(struct kvm *kvm)
void kvm_arch_flush_shadow_memslot(struct kvm *kvm, struct kvm_memory_slot *slot)
int kvm_arch_prepare_memory_region(struct kvm *kvm, struct kvm_memory_slot *memslot, const struct kvm_userspace_memory_region *mem, enum kvm_mr_change change)
void kvm_arch_commit_memory_region(struct kvm *kvm, const struct kvm_userspace_memory_region *mem, const struct kvm_memory_slot *old, const struct kvm_memory_slot *new, enum kvm_mr_change change)
static inline void dump_handler(const char *symbol, void *start, void *end)
struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm, unsigned int id)
void kvm_arch_vcpu_free(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_destroy(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_set_guest_debug(struct kvm_vcpu *vcpu, struct kvm_guest_debug *dbg)
int kvm_arch_vcpu_ioctl_run(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_vcpu_ioctl_interrupt(struct kvm_vcpu *vcpu, struct kvm_mips_interrupt *irq)
int kvm_arch_vcpu_ioctl_get_mpstate(struct kvm_vcpu *vcpu, struct kvm_mp_state *mp_state)
int kvm_arch_vcpu_ioctl_set_mpstate(struct kvm_vcpu *vcpu, struct kvm_mp_state *mp_state)
static unsigned long kvm_mips_num_regs(struct kvm_vcpu *vcpu)
static int kvm_mips_copy_reg_indices(struct kvm_vcpu *vcpu, u64 __user *indices)
static int kvm_mips_get_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
static int kvm_mips_set_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
static int kvm_vcpu_ioctl_enable_cap(struct kvm_vcpu *vcpu, struct kvm_enable_cap *cap)
long kvm_arch_vcpu_async_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
long kvm_arch_vcpu_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
int kvm_vm_ioctl_get_dirty_log(struct kvm *kvm, struct kvm_dirty_log *log)
int kvm_vm_ioctl_clear_dirty_log(struct kvm *kvm, struct kvm_clear_dirty_log *log)
long kvm_arch_vm_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
int kvm_arch_init(void *opaque)
void kvm_arch_exit(void)
int kvm_arch_vcpu_ioctl_get_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvm_arch_vcpu_ioctl_set_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
void kvm_arch_vcpu_postcreate(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_get_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
int kvm_arch_vcpu_ioctl_set_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
vm_fault_t kvm_arch_vcpu_fault(struct kvm_vcpu *vcpu, struct vm_fault *vmf)
int kvm_vm_ioctl_check_extension(struct kvm *kvm, long ext)
int kvm_cpu_has_pending_timer(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_dump_regs(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_set_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
int kvm_arch_vcpu_ioctl_get_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
static void kvm_mips_comparecount_func(unsigned long data)
static enum hrtimer_restart kvm_mips_comparecount_wakeup(struct hrtimer *timer)
int kvm_arch_vcpu_init(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_uninit(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_ioctl_translate(struct kvm_vcpu *vcpu, struct kvm_translation *tr)
int kvm_arch_vcpu_setup(struct kvm_vcpu *vcpu)
static void kvm_mips_set_c0_status(void)
int kvm_mips_handle_exit(struct kvm_run *run, struct kvm_vcpu *vcpu)
void kvm_own_fpu(struct kvm_vcpu *vcpu)
void kvm_own_msa(struct kvm_vcpu *vcpu)
void kvm_drop_fpu(struct kvm_vcpu *vcpu)
void kvm_lose_fpu(struct kvm_vcpu *vcpu)
static int kvm_mips_csr_die_notify(struct notifier_block *self, unsigned long cmd, void *ptr)
static int __init kvm_mips_init(void)
static void __exit kvm_mips_exit(void)
\n
     35 struct kvm_vcpu *vcpu
     13 struct kvm *kvm
     10 void
      4 unsigned long arg
      4 unsigned int ioctl
      4 struct file *filp
      2 struct kvm_sregs *sregs
      2 struct kvm_run *run
      2 struct kvm_regs *regs
      2 struct kvm_mp_state *mp_state
      2 struct kvm_memory_slot *slot
      2 struct kvm_fpu *fpu
      2 enum kvm_mr_change change
      2 const struct kvm_userspace_memory_region *mem
      2 const struct kvm_one_reg *reg
      1 void *start
      1 void *rtn
      1 void *ptr
      1 void *opaque
      1 void *end
      1 unsigned long type
      1 unsigned long npages
      1 unsigned long data
      1 unsigned long cmd
      1 unsigned int id
      1 u64 __user *indices
      1 struct vm_fault *vmf
      1 struct notifier_block *self
      1 struct kvm_translation *tr
      1 struct kvm_mips_interrupt *irq
      1 struct kvm_memory_slot *memslot
      1 struct kvm_guest_debug *dbg
      1 struct kvm_enable_cap *cap
      1 struct kvm_dirty_log *log
      1 struct kvm_clear_dirty_log *log
      1 struct hrtimer *timer
      1 long ext
      1 const struct kvm_memory_slot *old
      1 const struct kvm_memory_slot *new
      1 const char *symbol
