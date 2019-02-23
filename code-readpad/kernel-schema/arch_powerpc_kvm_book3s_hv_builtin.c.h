
EXPORT_SYMBOL_GPL(__xive_vm_h_xirr);
EXPORT_SYMBOL_GPL(__xive_vm_h_ipoll);
EXPORT_SYMBOL_GPL(__xive_vm_h_ipi);
EXPORT_SYMBOL_GPL(__xive_vm_h_cppr);
EXPORT_SYMBOL_GPL(__xive_vm_h_eoi);
EXPORT_SYMBOL_GPL(kvm_alloc_hpt_cma);
EXPORT_SYMBOL_GPL(kvm_free_hpt_cma);
EXPORT_SYMBOL_GPL(kvm_hv_vm_activated);
EXPORT_SYMBOL_GPL(kvm_hv_vm_deactivated);
EXPORT_SYMBOL_GPL(kvmppc_hcall_impl_hv_realmode);
EXPORT_SYMBOL_GPL(kvmppc_hwrng_present);
EXPORT_SYMBOL_GPL(kvmppc_host_rm_ops_hv);
\n
static int __init early_parse_kvm_cma_resv(char *p)
struct page *kvm_alloc_hpt_cma(unsigned long nr_pages)
void kvm_free_hpt_cma(struct page *page, unsigned long nr_pages)
void __init kvm_cma_reserve(void)
long int kvmppc_rm_h_confer(struct kvm_vcpu *vcpu, int target, unsigned int yield_count)
void kvm_hv_vm_activated(void)
void kvm_hv_vm_deactivated(void)
bool kvm_hv_mode_active(void)
int kvmppc_hcall_impl_hv_realmode(unsigned long cmd)
int kvmppc_hwrng_present(void)
long kvmppc_h_random(struct kvm_vcpu *vcpu)
void kvmhv_rm_send_ipi(int cpu)
static void kvmhv_interrupt_vcore(struct kvmppc_vcore *vc, int active)
void kvmhv_commence_exit(int trap)
static struct kvmppc_irq_map *get_irqmap(struct kvmppc_passthru_irqmap *pimap, u32 xisr)
static int kvmppc_check_passthru(u32 xisr, __be32 xirr, bool *again)
static inline int kvmppc_check_passthru(u32 xisr, __be32 xirr, bool *again)
long kvmppc_read_intr(void)
static long kvmppc_read_one_intr(bool *again)
static inline bool is_rm(void)
unsigned long kvmppc_rm_h_xirr(struct kvm_vcpu *vcpu)
unsigned long kvmppc_rm_h_xirr_x(struct kvm_vcpu *vcpu)
unsigned long kvmppc_rm_h_ipoll(struct kvm_vcpu *vcpu, unsigned long server)
int kvmppc_rm_h_ipi(struct kvm_vcpu *vcpu, unsigned long server, unsigned long mfrr)
int kvmppc_rm_h_cppr(struct kvm_vcpu *vcpu, unsigned long cppr)
int kvmppc_rm_h_eoi(struct kvm_vcpu *vcpu, unsigned long xirr)
void kvmppc_bad_interrupt(struct pt_regs *regs)
static void wait_for_sync(struct kvm_split_mode *sip, int phase)
void kvmhv_p9_set_lpcr(struct kvm_split_mode *sip)
void kvmhv_p9_restore_lpcr(struct kvm_split_mode *sip)
void kvmppc_guest_entry_inject_int(struct kvm_vcpu *vcpu)
\n
      9 struct kvm_vcpu *vcpu
      7 void
      3 u32 xisr
      3 struct kvm_split_mode *sip
      3 bool *again
      2 unsigned long server
      2 unsigned long nr_pages
      2 __be32 xirr
      1 __xive_vm_h_xirr
      1 __xive_vm_h_ipoll
      1 __xive_vm_h_ipi
      1 __xive_vm_h_eoi
      1 __xive_vm_h_cppr
      1 unsigned long xirr
      1 unsigned long mfrr
      1 unsigned long cppr
      1 unsigned long cmd
      1 unsigned int yield_count
      1 struct pt_regs *regs
      1 struct page *page
      1 struct kvmppc_vcore *vc
      1 struct kvmppc_passthru_irqmap *pimap
      1 kvmppc_hwrng_present
      1 kvmppc_host_rm_ops_hv
      1 kvmppc_hcall_impl_hv_realmode
      1 kvm_hv_vm_deactivated
      1 kvm_hv_vm_activated
      1 kvm_free_hpt_cma
      1 kvm_alloc_hpt_cma
      1 int trap
      1 int target
      1 int phase
      1 int cpu
      1 int active
      1 char *p
