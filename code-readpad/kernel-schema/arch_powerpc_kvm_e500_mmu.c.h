
\n
static inline unsigned int gtlb0_get_next_victim( struct kvmppc_vcpu_e500 *vcpu_e500)
static int tlb0_set_base(gva_t addr, int sets, int ways)
static int gtlb0_set_base(struct kvmppc_vcpu_e500 *vcpu_e500, gva_t addr)
static unsigned int get_tlb_esel(struct kvm_vcpu *vcpu, int tlbsel)
static int kvmppc_e500_tlb_index(struct kvmppc_vcpu_e500 *vcpu_e500, gva_t eaddr, int tlbsel, unsigned int pid, int as)
static inline void kvmppc_e500_deliver_tlb_miss(struct kvm_vcpu *vcpu, gva_t eaddr, int as)
static void kvmppc_recalc_tlb1map_range(struct kvmppc_vcpu_e500 *vcpu_e500)
static int kvmppc_need_recalc_tlb1map_range(struct kvmppc_vcpu_e500 *vcpu_e500, struct kvm_book3e_206_tlb_entry *gtlbe)
static void kvmppc_set_tlb1map_range(struct kvm_vcpu *vcpu, struct kvm_book3e_206_tlb_entry *gtlbe)
static inline int kvmppc_e500_gtlbe_invalidate( struct kvmppc_vcpu_e500 *vcpu_e500, int tlbsel, int esel)
int kvmppc_e500_emul_mt_mmucsr0(struct kvmppc_vcpu_e500 *vcpu_e500, ulong value)
int kvmppc_e500_emul_tlbivax(struct kvm_vcpu *vcpu, gva_t ea)
static void tlbilx_all(struct kvmppc_vcpu_e500 *vcpu_e500, int tlbsel, int pid, int type)
static void tlbilx_one(struct kvmppc_vcpu_e500 *vcpu_e500, int pid, gva_t ea)
int kvmppc_e500_emul_tlbilx(struct kvm_vcpu *vcpu, int type, gva_t ea)
int kvmppc_e500_emul_tlbre(struct kvm_vcpu *vcpu)
int kvmppc_e500_emul_tlbsx(struct kvm_vcpu *vcpu, gva_t ea)
int kvmppc_e500_emul_tlbwe(struct kvm_vcpu *vcpu)
static int kvmppc_e500_tlb_search(struct kvm_vcpu *vcpu, gva_t eaddr, unsigned int pid, int as)
int kvmppc_core_vcpu_translate(struct kvm_vcpu *vcpu, struct kvm_translation *tr)
int kvmppc_mmu_itlb_index(struct kvm_vcpu *vcpu, gva_t eaddr)
int kvmppc_mmu_dtlb_index(struct kvm_vcpu *vcpu, gva_t eaddr)
void kvmppc_mmu_itlb_miss(struct kvm_vcpu *vcpu)
void kvmppc_mmu_dtlb_miss(struct kvm_vcpu *vcpu)
gpa_t kvmppc_mmu_xlate(struct kvm_vcpu *vcpu, unsigned int index, gva_t eaddr)
void kvmppc_mmu_destroy_e500(struct kvm_vcpu *vcpu)
static void free_gtlb(struct kvmppc_vcpu_e500 *vcpu_e500)
void kvmppc_get_sregs_e500_tlb(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvmppc_set_sregs_e500_tlb(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
int kvmppc_get_one_reg_e500_tlb(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
int kvmppc_set_one_reg_e500_tlb(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
static int vcpu_mmu_geometry_update(struct kvm_vcpu *vcpu, struct kvm_book3e_206_tlb_params *params)
int kvm_vcpu_ioctl_config_tlb(struct kvm_vcpu *vcpu, struct kvm_config_tlb *cfg)
int kvm_vcpu_ioctl_dirty_tlb(struct kvm_vcpu *vcpu, struct kvm_dirty_tlb *dirty)
static int vcpu_mmu_init(struct kvm_vcpu *vcpu, struct kvmppc_e500_tlb_params *params)
int kvmppc_e500_tlb_init(struct kvmppc_vcpu_e500 *vcpu_e500)
void kvmppc_e500_tlb_uninit(struct kvmppc_vcpu_e500 *vcpu_e500)
\n
     24 struct kvm_vcpu *vcpu
     12 struct kvmppc_vcpu_e500 *vcpu_e500
      6 gva_t eaddr
      4 int tlbsel
      4 gva_t ea
      3 int as
      2 unsigned int pid
      2 union kvmppc_one_reg *val
      2 u64 id
      2 struct kvm_sregs *sregs
      2 struct kvm_book3e_206_tlb_entry *gtlbe
      2 int type
      2 int pid
      2 gva_t addr
      1 unsigned int index
      1 ulong value
      1 struct kvm_translation *tr
      1 struct kvmppc_e500_tlb_params *params
      1 struct kvm_dirty_tlb *dirty
      1 struct kvm_config_tlb *cfg
      1 struct kvm_book3e_206_tlb_params *params
      1 int ways
      1 int sets
      1 int esel
