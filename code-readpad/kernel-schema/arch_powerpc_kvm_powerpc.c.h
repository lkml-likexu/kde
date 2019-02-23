
EXPORT_SYMBOL_GPL(kvmppc_hv_ops);
EXPORT_SYMBOL_GPL(kvmppc_pr_ops);
EXPORT_SYMBOL_GPL(kvmppc_prepare_to_enter);
EXPORT_SYMBOL_GPL(kvmppc_kvm_pv);
EXPORT_SYMBOL_GPL(kvmppc_sanity_check);
EXPORT_SYMBOL_GPL(kvmppc_emulate_mmio);
EXPORT_SYMBOL_GPL(kvmppc_st);
EXPORT_SYMBOL_GPL(kvmppc_ld);
EXPORT_SYMBOL_GPL(kvmppc_handle_load);
EXPORT_SYMBOL_GPL(kvmppc_handle_store);
EXPORT_SYMBOL_GPL(kvmppc_alloc_lpid);
EXPORT_SYMBOL_GPL(kvmppc_claim_lpid);
EXPORT_SYMBOL_GPL(kvmppc_free_lpid);
EXPORT_SYMBOL_GPL(kvmppc_init_lpid);
\n
int kvm_arch_vcpu_runnable(struct kvm_vcpu *v)
bool kvm_arch_vcpu_in_kernel(struct kvm_vcpu *vcpu)
int kvm_arch_vcpu_should_kick(struct kvm_vcpu *vcpu)
int kvmppc_prepare_to_enter(struct kvm_vcpu *vcpu)
static void kvmppc_swab_shared(struct kvm_vcpu *vcpu)
int kvmppc_kvm_pv(struct kvm_vcpu *vcpu)
int kvmppc_sanity_check(struct kvm_vcpu *vcpu)
int kvmppc_emulate_mmio(struct kvm_run *run, struct kvm_vcpu *vcpu)
int kvmppc_st(struct kvm_vcpu *vcpu, ulong *eaddr, int size, void *ptr, bool data)
int kvmppc_ld(struct kvm_vcpu *vcpu, ulong *eaddr, int size, void *ptr, bool data)
int kvm_arch_hardware_enable(void)
int kvm_arch_hardware_setup(void)
void kvm_arch_check_processor_compat(void *rtn)
int kvm_arch_init_vm(struct kvm *kvm, unsigned long type)
bool kvm_arch_has_vcpu_debugfs(void)
int kvm_arch_create_vcpu_debugfs(struct kvm_vcpu *vcpu)
void kvm_arch_destroy_vm(struct kvm *kvm)
int kvm_vm_ioctl_check_extension(struct kvm *kvm, long ext)
long kvm_arch_dev_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
void kvm_arch_free_memslot(struct kvm *kvm, struct kvm_memory_slot *free, struct kvm_memory_slot *dont)
int kvm_arch_create_memslot(struct kvm *kvm, struct kvm_memory_slot *slot, unsigned long npages)
int kvm_arch_prepare_memory_region(struct kvm *kvm, struct kvm_memory_slot *memslot, const struct kvm_userspace_memory_region *mem, enum kvm_mr_change change)
void kvm_arch_commit_memory_region(struct kvm *kvm, const struct kvm_userspace_memory_region *mem, const struct kvm_memory_slot *old, const struct kvm_memory_slot *new, enum kvm_mr_change change)
void kvm_arch_flush_shadow_memslot(struct kvm *kvm, struct kvm_memory_slot *slot)
struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm, unsigned int id)
void kvm_arch_vcpu_postcreate(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_free(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_destroy(struct kvm_vcpu *vcpu)
int kvm_cpu_has_pending_timer(struct kvm_vcpu *vcpu)
static enum hrtimer_restart kvmppc_decrementer_wakeup(struct hrtimer *timer)
int kvm_arch_vcpu_init(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_uninit(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
bool kvm_arch_has_irq_bypass(void)
int kvm_arch_irq_bypass_add_producer(struct irq_bypass_consumer *cons, struct irq_bypass_producer *prod)
void kvm_arch_irq_bypass_del_producer(struct irq_bypass_consumer *cons, struct irq_bypass_producer *prod)
static inline int kvmppc_get_vsr_dword_offset(int index)
static inline int kvmppc_get_vsr_word_offset(int index)
static inline void kvmppc_set_vsr_dword(struct kvm_vcpu *vcpu, u64 gpr)
static inline void kvmppc_set_vsr_dword_dump(struct kvm_vcpu *vcpu, u64 gpr)
static inline void kvmppc_set_vsr_word_dump(struct kvm_vcpu *vcpu, u32 gpr)
static inline void kvmppc_set_vsr_word(struct kvm_vcpu *vcpu, u32 gpr32)
static inline int kvmppc_get_vmx_offset_generic(struct kvm_vcpu *vcpu, int index, int element_size)
static inline int kvmppc_get_vmx_dword_offset(struct kvm_vcpu *vcpu, int index)
static inline int kvmppc_get_vmx_word_offset(struct kvm_vcpu *vcpu, int index)
static inline int kvmppc_get_vmx_hword_offset(struct kvm_vcpu *vcpu, int index)
static inline int kvmppc_get_vmx_byte_offset(struct kvm_vcpu *vcpu, int index)
static inline void kvmppc_set_vmx_dword(struct kvm_vcpu *vcpu, u64 gpr)
static inline void kvmppc_set_vmx_word(struct kvm_vcpu *vcpu, u32 gpr32)
static inline void kvmppc_set_vmx_hword(struct kvm_vcpu *vcpu, u16 gpr16)
static inline void kvmppc_set_vmx_byte(struct kvm_vcpu *vcpu, u8 gpr8)
static inline u64 sp_to_dp(u32 fprs)
static inline u32 dp_to_sp(u64 fprd)
static void kvmppc_complete_mmio_load(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int __kvmppc_handle_load(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int rt, unsigned int bytes, int is_default_endian, int sign_extend)
int kvmppc_handle_load(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int rt, unsigned int bytes, int is_default_endian)
int kvmppc_handle_loads(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int rt, unsigned int bytes, int is_default_endian)
int kvmppc_handle_vsx_load(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int rt, unsigned int bytes, int is_default_endian, int mmio_sign_extend)
int kvmppc_handle_store(struct kvm_run *run, struct kvm_vcpu *vcpu, u64 val, unsigned int bytes, int is_default_endian)
static inline int kvmppc_get_vsr_data(struct kvm_vcpu *vcpu, int rs, u64 *val)
int kvmppc_handle_vsx_store(struct kvm_run *run, struct kvm_vcpu *vcpu, int rs, unsigned int bytes, int is_default_endian)
static int kvmppc_emulate_mmio_vsx_loadstore(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvmppc_handle_vmx_load(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int rt, unsigned int bytes, int is_default_endian)
int kvmppc_get_vmx_dword(struct kvm_vcpu *vcpu, int index, u64 *val)
int kvmppc_get_vmx_word(struct kvm_vcpu *vcpu, int index, u64 *val)
int kvmppc_get_vmx_hword(struct kvm_vcpu *vcpu, int index, u64 *val)
int kvmppc_get_vmx_byte(struct kvm_vcpu *vcpu, int index, u64 *val)
int kvmppc_handle_vmx_store(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int rs, unsigned int bytes, int is_default_endian)
static int kvmppc_emulate_mmio_vmx_loadstore(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_vcpu_ioctl_get_one_reg(struct kvm_vcpu *vcpu, struct kvm_one_reg *reg)
int kvm_vcpu_ioctl_set_one_reg(struct kvm_vcpu *vcpu, struct kvm_one_reg *reg)
int kvm_arch_vcpu_ioctl_run(struct kvm_vcpu *vcpu, struct kvm_run *run)
int kvm_vcpu_ioctl_interrupt(struct kvm_vcpu *vcpu, struct kvm_interrupt *irq)
static int kvm_vcpu_ioctl_enable_cap(struct kvm_vcpu *vcpu, struct kvm_enable_cap *cap)
bool kvm_arch_intc_initialized(struct kvm *kvm)
int kvm_arch_vcpu_ioctl_get_mpstate(struct kvm_vcpu *vcpu, struct kvm_mp_state *mp_state)
int kvm_arch_vcpu_ioctl_set_mpstate(struct kvm_vcpu *vcpu, struct kvm_mp_state *mp_state)
long kvm_arch_vcpu_async_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
long kvm_arch_vcpu_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
vm_fault_t kvm_arch_vcpu_fault(struct kvm_vcpu *vcpu, struct vm_fault *vmf)
static int kvm_vm_ioctl_get_pvinfo(struct kvm_ppc_pvinfo *pvinfo)
int kvm_vm_ioctl_irq_line(struct kvm *kvm, struct kvm_irq_level *irq_event, bool line_status)
int kvm_vm_ioctl_enable_cap(struct kvm *kvm, struct kvm_enable_cap *cap)
static int pseries_get_cpu_char(struct kvm_ppc_cpu_char *cp)
rc = plpar_get_cpu_characteristics(&c)
; cp->character = c.character; cp->behaviour = c.behaviour; cp->character_mask = KVM_PPC_CPU_CHAR_SPEC_BAR_ORI31 |KVM_PPC_CPU_CHAR_BCCTRL_SERIALISED |KVM_PPC_CPU_CHAR_L1D_FLUSH_ORI30 |KVM_PPC_CPU_CHAR_L1D_FLUSH_TRIG2 |KVM_PPC_CPU_CHAR_L1D_THREAD_PRIV |KVM_PPC_CPU_CHAR_BR_HINT_HONOURED |KVM_PPC_CPU_CHAR_MTTRIG_THR_RECONF |KVM_PPC_CPU_CHAR_COUNT_CACHE_DIS; cp->behaviour_mask = KVM_PPC_CPU_BEHAV_FAVOUR_SECURITY |KVM_PPC_CPU_BEHAV_L1D_FLUSH_PR |KVM_PPC_CPU_BEHAV_BNDS_CHK_SPEC_BAR;}return 0; } static int pseries_get_cpu_char(struct kvm_ppc_cpu_char *cp)
static inline bool have_fw_feat(struct device_node *fw_features, const char *state, const char *name)
static int kvmppc_get_cpu_char(struct kvm_ppc_cpu_char *cp)
long kvm_arch_vm_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
long kvmppc_alloc_lpid(void)
void kvmppc_claim_lpid(long lpid)
void kvmppc_free_lpid(long lpid)
void kvmppc_init_lpid(unsigned long nr_lpids_param)
int kvm_arch_init(void *opaque)
\n
     55 struct kvm_vcpu *vcpu
     13 struct kvm_run *run
     12 struct kvm *kvm
     11 int index
      8 unsigned int bytes
      8 int is_default_endian
      5 void
      5 unsigned int rt
      5 u64 *val
      4 unsigned long arg
      4 unsigned int ioctl
      4 struct file *filp
      3 u64 gpr
      3 struct kvm_ppc_cpu_char *cp
      2 void *ptr
      2 ulong *eaddr
      2 u32 gpr32
      2 struct kvm_one_reg *reg
      2 struct kvm_mp_state *mp_state
      2 struct kvm_memory_slot *slot
      2 struct kvm_enable_cap *cap
      2 struct irq_bypass_producer *prod
      2 struct irq_bypass_consumer *cons
      2 long lpid
      2 int size
      2 int rs
      2 enum kvm_mr_change change
      2 const struct kvm_userspace_memory_region *mem
      2 bool data
      1 void *rtn
      1 void *opaque
      1 unsigned long type
      1 unsigned long nr_lpids_param
      1 unsigned long npages
      1 unsigned int rs
      1 unsigned int id
      1 u8 gpr8
      1 u64 val
      1 u64 fprd
      1 u32 gpr
      1 u32 fprs
      1 u16 gpr16
      1 struct vm_fault *vmf
      1 struct kvm_vcpu *v
      1 struct kvm_ppc_pvinfo *pvinfo
      1 struct kvm_memory_slot *memslot
      1 struct kvm_memory_slot *free
      1 struct kvm_memory_slot *dont
      1 struct kvm_irq_level *irq_event
      1 struct kvm_interrupt *irq
      1 struct hrtimer *timer
      1 struct device_node *fw_features
      1 long ext
      1 kvmppc_st
      1 kvmppc_sanity_check
      1 kvmppc_pr_ops
      1 kvmppc_prepare_to_enter
      1 kvmppc_ld
      1 kvmppc_kvm_pv
      1 kvmppc_init_lpid
      1 kvmppc_hv_ops
      1 kvmppc_handle_store
      1 kvmppc_handle_load
      1 kvmppc_free_lpid
      1 kvmppc_emulate_mmio
      1 kvmppc_claim_lpid
      1 kvmppc_alloc_lpid
      1 int sign_extend
      1 int mmio_sign_extend
      1 int element_size
      1 int cpu
      1 const struct kvm_memory_slot *old
      1 const struct kvm_memory_slot *new
      1 const char *state
      1 const char *name
      1 &c
      1 bool line_status
