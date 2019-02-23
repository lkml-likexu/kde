
\n
static void kvmppc_mmu_book3s_64_reset_msr(struct kvm_vcpu *vcpu)
static struct kvmppc_slb *kvmppc_mmu_book3s_64_find_slbe( struct kvm_vcpu *vcpu, gva_t eaddr)
static int kvmppc_slb_sid_shift(struct kvmppc_slb *slbe)
static u64 kvmppc_slb_offset_mask(struct kvmppc_slb *slbe)
static u64 kvmppc_slb_calc_vpn(struct kvmppc_slb *slb, gva_t eaddr)
static u64 kvmppc_mmu_book3s_64_ea_to_vp(struct kvm_vcpu *vcpu, gva_t eaddr, bool data)
static int mmu_pagesize(int mmu_pg)
static int kvmppc_mmu_book3s_64_get_pagesize(struct kvmppc_slb *slbe)
static u32 kvmppc_mmu_book3s_64_get_page(struct kvmppc_slb *slbe, gva_t eaddr)
static hva_t kvmppc_mmu_book3s_64_get_pteg(struct kvm_vcpu *vcpu, struct kvmppc_slb *slbe, gva_t eaddr, bool second)
static u64 kvmppc_mmu_book3s_64_get_avpn(struct kvmppc_slb *slbe, gva_t eaddr)
static int decode_pagesize(struct kvmppc_slb *slbe, u64 r)
static int kvmppc_mmu_book3s_64_xlate(struct kvm_vcpu *vcpu, gva_t eaddr, struct kvmppc_pte *gpte, bool data, bool iswrite)
static void kvmppc_mmu_book3s_64_slbmte(struct kvm_vcpu *vcpu, u64 rs, u64 rb)
static u64 kvmppc_mmu_book3s_64_slbmfee(struct kvm_vcpu *vcpu, u64 slb_nr)
static u64 kvmppc_mmu_book3s_64_slbmfev(struct kvm_vcpu *vcpu, u64 slb_nr)
static void kvmppc_mmu_book3s_64_slbie(struct kvm_vcpu *vcpu, u64 ea)
static void kvmppc_mmu_book3s_64_slbia(struct kvm_vcpu *vcpu)
static void kvmppc_mmu_book3s_64_mtsrin(struct kvm_vcpu *vcpu, u32 srnum, ulong value)
static void kvmppc_mmu_book3s_64_tlbie(struct kvm_vcpu *vcpu, ulong va, bool large)
static int segment_contains_magic_page(struct kvm_vcpu *vcpu, ulong esid)
static int kvmppc_mmu_book3s_64_esid_to_vsid(struct kvm_vcpu *vcpu, ulong esid, u64 *vsid)
static bool kvmppc_mmu_book3s_64_is_dcbz32(struct kvm_vcpu *vcpu)
void kvmppc_mmu_book3s_64_init(struct kvm_vcpu *vcpu)
\n
     16 struct kvm_vcpu *vcpu
      7 struct kvmppc_slb *slbe
      7 gva_t eaddr
      2 ulong esid
      2 u64 slb_nr
      2 bool data
      1 ulong value
      1 ulong va
      1 u64 *vsid
      1 u64 rs
      1 u64 rb
      1 u64 r
      1 u64 ea
      1 u32 srnum
      1 struct kvmppc_slb *slb
      1 struct kvmppc_pte *gpte
      1 int mmu_pg
      1 bool second
      1 bool large
      1 bool iswrite
