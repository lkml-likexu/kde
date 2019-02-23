
\n
static inline unsigned int tlb1_max_shadow_size(void)
static inline u32 e500_shadow_mas3_attrib(u32 mas3, int usermode)
static inline void __write_host_tlbe(struct kvm_book3e_206_tlb_entry *stlbe, uint32_t mas0, uint32_t lpid)
static u32 get_host_mas0(unsigned long eaddr)
static inline void write_host_tlbe(struct kvmppc_vcpu_e500 *vcpu_e500, int tlbsel, int sesel, struct kvm_book3e_206_tlb_entry *stlbe)
static void write_stlbe(struct kvmppc_vcpu_e500 *vcpu_e500, struct kvm_book3e_206_tlb_entry *gtlbe, struct kvm_book3e_206_tlb_entry *stlbe, int stlbsel, int sesel)
void kvmppc_map_magic(struct kvm_vcpu *vcpu)
void inval_gtlbe_on_host(struct kvmppc_vcpu_e500 *vcpu_e500, int tlbsel, int esel)
static inline int tlbe_is_writable(struct kvm_book3e_206_tlb_entry *tlbe)
static inline void kvmppc_e500_ref_setup(struct tlbe_ref *ref, struct kvm_book3e_206_tlb_entry *gtlbe, kvm_pfn_t pfn, unsigned int wimg)
static inline void kvmppc_e500_ref_release(struct tlbe_ref *ref)
static void clear_tlb1_bitmap(struct kvmppc_vcpu_e500 *vcpu_e500)
static void clear_tlb_privs(struct kvmppc_vcpu_e500 *vcpu_e500)
void kvmppc_core_flush_tlb(struct kvm_vcpu *vcpu)
static void kvmppc_e500_setup_stlbe(struct kvm_vcpu *vcpu, struct kvm_book3e_206_tlb_entry *gtlbe, int tsize, struct tlbe_ref *ref, u64 gvaddr, struct kvm_book3e_206_tlb_entry *stlbe)
static inline int kvmppc_e500_shadow_map(struct kvmppc_vcpu_e500 *vcpu_e500, u64 gvaddr, gfn_t gfn, struct kvm_book3e_206_tlb_entry *gtlbe, int tlbsel, struct kvm_book3e_206_tlb_entry *stlbe, struct tlbe_ref *ref)
static int kvmppc_e500_tlb0_map(struct kvmppc_vcpu_e500 *vcpu_e500, int esel, struct kvm_book3e_206_tlb_entry *stlbe)
static int kvmppc_e500_tlb1_map_tlb1(struct kvmppc_vcpu_e500 *vcpu_e500, struct tlbe_ref *ref, int esel)
static int kvmppc_e500_tlb1_map(struct kvmppc_vcpu_e500 *vcpu_e500, u64 gvaddr, gfn_t gfn, struct kvm_book3e_206_tlb_entry *gtlbe, struct kvm_book3e_206_tlb_entry *stlbe, int esel)
void kvmppc_mmu_map(struct kvm_vcpu *vcpu, u64 eaddr, gpa_t gpaddr, unsigned int index)
int kvmppc_load_last_inst(struct kvm_vcpu *vcpu, enum instruction_fetch_type type, u32 *instr)
return EMULATE_DONE; } int kvmppc_load_last_inst(struct kvm_vcpu *vcpu, enum instruction_fetch_type type, u32 *instr)
static int kvm_unmap_hva(struct kvm *kvm, unsigned long hva)
int kvm_unmap_hva_range(struct kvm *kvm, unsigned long start, unsigned long end)
int kvm_age_hva(struct kvm *kvm, unsigned long start, unsigned long end)
int kvm_test_age_hva(struct kvm *kvm, unsigned long hva)
int kvm_set_spte_hva(struct kvm *kvm, unsigned long hva, pte_t pte)
int e500_mmu_host_init(struct kvmppc_vcpu_e500 *vcpu_e500)
void e500_mmu_host_uninit(struct kvmppc_vcpu_e500 *vcpu_e500)
\n
     11 struct kvmppc_vcpu_e500 *vcpu_e500
      7 struct kvm_book3e_206_tlb_entry *stlbe
      6 struct kvm_vcpu *vcpu
      5 struct tlbe_ref *ref
      5 struct kvm *kvm
      5 struct kvm_book3e_206_tlb_entry *gtlbe
      4 int esel
      3 unsigned long hva
      3 u64 gvaddr
      3 int tlbsel
      2 unsigned long start
      2 unsigned long end
      2 u32 *instr
      2 int sesel
      2 gfn_t gfn
      2 enum instruction_fetch_type type
      1 void
      1 unsigned long eaddr
      1 unsigned int wimg
      1 unsigned int index
      1 uint32_t mas0
      1 uint32_t lpid
      1 u64 eaddr
      1 u32 mas3
      1 struct kvm_book3e_206_tlb_entry *tlbe
      1 pte_t pte
      1 kvm_pfn_t pfn
      1 int usermode
      1 int tsize
      1 int stlbsel
      1 gpa_t gpaddr
