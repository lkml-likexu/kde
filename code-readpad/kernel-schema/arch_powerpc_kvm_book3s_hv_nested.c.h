
\n
void kvmhv_save_hv_regs(struct kvm_vcpu *vcpu, struct hv_guest_state *hr)
static void byteswap_pt_regs(struct pt_regs *regs)
static void byteswap_hv_regs(struct hv_guest_state *hr)
static void save_hv_return_state(struct kvm_vcpu *vcpu, int trap, struct hv_guest_state *hr)
static void sanitise_hv_regs(struct kvm_vcpu *vcpu, struct hv_guest_state *hr)
static void restore_hv_regs(struct kvm_vcpu *vcpu, struct hv_guest_state *hr)
void kvmhv_restore_hv_return_state(struct kvm_vcpu *vcpu, struct hv_guest_state *hr)
static void kvmhv_nested_mmio_needed(struct kvm_vcpu *vcpu, u64 regs_ptr)
long kvmhv_enter_nested_guest(struct kvm_vcpu *vcpu)
long kvmhv_nested_init(void)
void kvmhv_nested_exit(void)
static void kvmhv_flush_lpid(unsigned int lpid)
void kvmhv_set_ptbl_entry(unsigned int lpid, u64 dw0, u64 dw1)
static void kvmhv_set_nested_ptbl(struct kvm_nested_guest *gp)
void kvmhv_vm_nested_init(struct kvm *kvm)
long kvmhv_set_partition_table(struct kvm_vcpu *vcpu)
long kvmhv_copy_tofrom_guest_nested(struct kvm_vcpu *vcpu)
static void kvmhv_update_ptbl_cache(struct kvm_nested_guest *gp)
struct kvm_nested_guest *kvmhv_alloc_nested(struct kvm *kvm, unsigned int lpid)
static void kvmhv_release_nested(struct kvm_nested_guest *gp)
static void kvmhv_remove_nested(struct kvm_nested_guest *gp)
void kvmhv_release_all_nested(struct kvm *kvm)
static void kvmhv_flush_nested(struct kvm_nested_guest *gp)
struct kvm_nested_guest *kvmhv_get_nested(struct kvm *kvm, int l1_lpid, bool create)
void kvmhv_put_nested(struct kvm_nested_guest *gp)
static struct kvm_nested_guest *kvmhv_find_nested(struct kvm *kvm, int lpid)
static inline bool kvmhv_n_rmap_is_equal(u64 rmap_1, u64 rmap_2)
void kvmhv_insert_nest_rmap(struct kvm *kvm, unsigned long *rmapp, struct rmap_nested **n_rmap)
static void kvmhv_update_nest_rmap_rc(struct kvm *kvm, u64 n_rmap, unsigned long clr, unsigned long set, unsigned long hpa, unsigned long mask)
void kvmhv_update_nest_rmap_rc_list(struct kvm *kvm, unsigned long *rmapp, unsigned long clr, unsigned long set, unsigned long hpa, unsigned long nbytes)
static void kvmhv_remove_nest_rmap(struct kvm *kvm, u64 n_rmap, unsigned long hpa, unsigned long mask)
static void kvmhv_remove_nest_rmap_list(struct kvm *kvm, unsigned long *rmapp, unsigned long hpa, unsigned long mask)
void kvmhv_remove_nest_rmap_range(struct kvm *kvm, const struct kvm_memory_slot *memslot, unsigned long gpa, unsigned long hpa, unsigned long nbytes)
static void kvmhv_free_memslot_nest_rmap(struct kvm_memory_slot *free)
static bool kvmhv_invalidate_shadow_pte(struct kvm_vcpu *vcpu, struct kvm_nested_guest *gp, long gpa, int *shift_ret)
static inline int get_ric(unsigned int instr)
static inline int get_prs(unsigned int instr)
static inline int get_r(unsigned int instr)
static inline int get_lpid(unsigned long r_val)
static inline int get_is(unsigned long r_val)
static inline int get_ap(unsigned long r_val)
static inline long get_epn(unsigned long r_val)
static int kvmhv_emulate_tlbie_tlb_addr(struct kvm_vcpu *vcpu, int lpid, int ap, long epn)
static void kvmhv_emulate_tlbie_lpid(struct kvm_vcpu *vcpu, struct kvm_nested_guest *gp, int ric)
static void kvmhv_emulate_tlbie_all_lpid(struct kvm_vcpu *vcpu, int ric)
static int kvmhv_emulate_priv_tlbie(struct kvm_vcpu *vcpu, unsigned int instr, unsigned long rsval, unsigned long rbval)
long kvmhv_do_nested_tlbie(struct kvm_vcpu *vcpu)
static int kvmhv_translate_addr_nested(struct kvm_vcpu *vcpu, struct kvm_nested_guest *gp, unsigned long n_gpa, unsigned long dsisr, struct kvmppc_pte *gpte_p)
static long kvmhv_handle_nested_set_rc(struct kvm_vcpu *vcpu, struct kvm_nested_guest *gp, unsigned long n_gpa, struct kvmppc_pte gpte, unsigned long dsisr)
static inline int kvmppc_radix_level_to_shift(int level)
static inline int kvmppc_radix_shift_to_level(int shift)
static long int __kvmhv_nested_page_fault(struct kvm_run *run, struct kvm_vcpu *vcpu, struct kvm_nested_guest *gp)
long int kvmhv_nested_page_fault(struct kvm_run *run, struct kvm_vcpu *vcpu)
int kvmhv_nested_next_lpid(struct kvm *kvm, int lpid)
\n
     19 struct kvm_vcpu *vcpu
     12 struct kvm *kvm
     11 struct kvm_nested_guest *gp
      6 struct hv_guest_state *hr
      5 unsigned long hpa
      4 unsigned long r_val
      4 unsigned int instr
      3 unsigned long *rmapp
      3 unsigned long mask
      3 unsigned int lpid
      3 int lpid
      2 void
      2 unsigned long set
      2 unsigned long n_gpa
      2 unsigned long nbytes
      2 unsigned long dsisr
      2 unsigned long clr
      2 u64 n_rmap
      2 struct kvm_run *run
      2 int ric
      1 unsigned long rsval
      1 unsigned long rbval
      1 unsigned long gpa
      1 u64 rmap_2
      1 u64 rmap_1
      1 u64 regs_ptr
      1 u64 dw1
      1 u64 dw0
      1 struct rmap_nested **n_rmap
      1 struct pt_regs *regs
      1 struct kvmppc_pte *gpte_p
      1 struct kvmppc_pte gpte
      1 struct kvm_memory_slot *free
      1 long gpa
      1 long epn
      1 int trap
      1 int *shift_ret
      1 int shift
      1 int level
      1 int l1_lpid
      1 int ap
      1 const struct kvm_memory_slot *memslot
      1 bool create
