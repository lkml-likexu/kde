
\n
static inline int kvmppc_get_last_inst(struct kvm_vcpu *vcpu, enum instruction_fetch_type type, u32 *inst)
static inline bool is_kvmppc_hv_enabled(struct kvm *kvm)
static inline u32 kvmppc_get_field(u64 inst, int msb, int lsb)
static inline u32 kvmppc_set_field(u64 inst, int msb, int lsb, int value)
extern void kvm_cma_reserve(void)
__init; static inline void kvmppc_set_xics_phys(int cpu, unsigned long addr)
static inline void kvmppc_set_xive_tima(int cpu, unsigned long phys_addr, void __iomem *virt_addr)
static inline u32 kvmppc_get_xics_latch(void)
static inline void kvmppc_set_host_ipi(int cpu, u8 host_ipi)
static inline void kvmppc_fast_vcpu_kick(struct kvm_vcpu *vcpu)
static inline void __init kvm_cma_reserve(void)
static inline void kvmppc_set_xics_phys(int cpu, unsigned long addr)
static inline void kvmppc_set_xive_tima(int cpu, unsigned long phys_addr, void __iomem *virt_addr)
static inline u32 kvmppc_get_xics_latch(void)
static inline void kvmppc_set_host_ipi(int cpu, u8 host_ipi)
static inline void kvmppc_fast_vcpu_kick(struct kvm_vcpu *vcpu)
static inline int kvmppc_xics_enabled(struct kvm_vcpu *vcpu)
static inline struct kvmppc_passthru_irqmap *kvmppc_get_passthru_irqmap( struct kvm *kvm)
static inline unsigned long kvmppc_get_epr(struct kvm_vcpu *vcpu)
static inline void kvmppc_set_epr(struct kvm_vcpu *vcpu, u32 epr)
static inline void kvmppc_mpic_set_epr(struct kvm_vcpu *vcpu)
static inline int kvmppc_mpic_connect_vcpu(struct kvm_device *dev, struct kvm_vcpu *vcpu, u32 cpu)
static inline void kvmppc_mpic_disconnect_vcpu(struct openpic *opp, struct kvm_vcpu *vcpu)
static inline void kvmppc_mmu_flush_icache(kvm_pfn_t pfn)
static inline bool kvmppc_shared_big_endian(struct kvm_vcpu *vcpu)
define SPRNG_WRAPPER_GET(reg, bookehv_spr)
\ static inline ulong kvmppc_get_reg(struct kvm_vcpu *vcpu)
\define SPRNG_WRAPPER_SET(reg, bookehv_spr)
\ static inline void kvmppc_set_reg(struct kvm_vcpu *vcpu, ulong val)
\define SHARED_WRAPPER_GET(reg, size)
\ static inline usize kvmppc_get_reg(struct kvm_vcpu *vcpu)
\define SHARED_WRAPPER_SET(reg, size)
\ static inline void kvmppc_set_reg(struct kvm_vcpu *vcpu, usize val)
\ SHARED_WRAPPER(critical, 64)
SHARED_SPRNG_WRAPPER(sprg0, 64, SPRN_GSPRG0)
SHARED_SPRNG_WRAPPER(sprg1, 64, SPRN_GSPRG1)
SHARED_SPRNG_WRAPPER(sprg2, 64, SPRN_GSPRG2)
SHARED_SPRNG_WRAPPER(sprg3, 64, SPRN_GSPRG3)
SHARED_SPRNG_WRAPPER(srr0, 64, SPRN_GSRR0)
SHARED_SPRNG_WRAPPER(srr1, 64, SPRN_GSRR1)
SHARED_SPRNG_WRAPPER(dar, 64, SPRN_GDEAR)
SHARED_SPRNG_WRAPPER(esr, 64, SPRN_GESR)
SHARED_WRAPPER_GET(msr, 64)
static inline void kvmppc_set_msr_fast(struct kvm_vcpu *vcpu, u64 val)
static inline u32 kvmppc_get_sr(struct kvm_vcpu *vcpu, int nr)
static inline void kvmppc_set_sr(struct kvm_vcpu *vcpu, int nr, u32 val)
static inline void kvmppc_fix_ee_before_entry(void)
static inline ulong kvmppc_get_ea_indexed(struct kvm_vcpu *vcpu, int ra, int rb)
\n
     18 struct kvm_vcpu *vcpu
     10 64
      6 int cpu
      5 void
      4 reg
      2 void __iomem *virt_addr
      2 unsigned long phys_addr
      2 unsigned long addr
      2 u8 host_ipi
      2 u64 inst
      2 struct kvm *kvm
      2 size
      2 int nr
      2 int msb
      2 int lsb
      2 bookehv_spr
      1 usize val
      1 ulong val
      1 u64 val
      1 u32 val
      1 u32 *inst
      1 u32 epr
      1 u32 cpu
      1 struct openpic *opp
      1 struct kvm_device *dev
      1 srr1
      1 srr0
      1 SPRN_GSRR1
      1 SPRN_GSRR0
      1 SPRN_GSPRG3
      1 SPRN_GSPRG2
      1 SPRN_GSPRG1
      1 SPRN_GSPRG0
      1 SPRN_GESR
      1 SPRN_GDEAR
      1 sprg3
      1 sprg2
      1 sprg1
      1 sprg0
      1 msr
      1 kvm_pfn_t pfn
      1 int value
      1 int rb
      1 int ra
      1 esr
      1 enum instruction_fetch_type type
      1 dar
      1 critical
