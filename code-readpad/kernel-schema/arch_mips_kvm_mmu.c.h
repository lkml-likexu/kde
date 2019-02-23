
\n
static int mmu_topup_memory_cache(struct kvm_mmu_memory_cache *cache, int min, int max)
static void mmu_free_memory_cache(struct kvm_mmu_memory_cache *mc)
static void *mmu_memory_cache_alloc(struct kvm_mmu_memory_cache *mc)
void kvm_mmu_free_memory_caches(struct kvm_vcpu *vcpu)
static void kvm_pgd_init(void *page)
pgd_t *kvm_pgd_alloc(void)
static pte_t *kvm_mips_walk_pgd(pgd_t *pgd, struct kvm_mmu_memory_cache *cache, unsigned long addr)
static pte_t *kvm_mips_pte_for_gpa(struct kvm *kvm, struct kvm_mmu_memory_cache *cache, unsigned long addr)
static bool kvm_mips_flush_gpa_pte(pte_t *pte, unsigned long start_gpa, unsigned long end_gpa)
static bool kvm_mips_flush_gpa_pmd(pmd_t *pmd, unsigned long start_gpa, unsigned long end_gpa)
static bool kvm_mips_flush_gpa_pud(pud_t *pud, unsigned long start_gpa, unsigned long end_gpa)
static bool kvm_mips_flush_gpa_pgd(pgd_t *pgd, unsigned long start_gpa, unsigned long end_gpa)
bool kvm_mips_flush_gpa_pt(struct kvm *kvm, gfn_t start_gfn, gfn_t end_gfn)
define BUILD_PTE_RANGE_OP(name, op)
\ static int kvm_mips_name_pte(pte_t *pte, unsigned long start, \unsigned long end)
\define BUILD_PTE_RANGE_OP(name, op)
\ static int kvm_mips_name_pte(pte_t *pte, unsigned long start, \unsigned long end)
\int ret = 0; \int i_min = __pte_offset(start)
;\int i_max = __pte_offset(end)
; \int i;\pte_t old, new; \\ if (!pte_present(pte[i])
)
\continue; \\ old = pte[i];\ new = op(old)
;\ if (pte_val(new)
== pte_val(old)
)
\continue; \ set_pte(pte + i, new)
; \ ret = 1;\}\return ret; \ } \\\ static int kvm_mips_name_pmd(pmd_t *pmd, unsigned long start, \unsigned long end)
\define BUILD_PTE_RANGE_OP(name, op)
\ static int kvm_mips_name_pte(pte_t *pte, unsigned long start, \unsigned long end)
\int ret = 0; \int i_min = __pte_offset(start)
;\int i_max = __pte_offset(end)
; \int i;\pte_t old, new; \\ if (!pte_present(pte[i])
)
\continue; \\ old = pte[i];\ new = op(old)
;\ if (pte_val(new)
== pte_val(old)
)
\continue; \ set_pte(pte + i, new)
; \ ret = 1;\}\return ret; \ } \\\ static int kvm_mips_name_pmd(pmd_t *pmd, unsigned long start, \unsigned long end)
\int ret = 0; \pte_t *pte; \unsigned long cur_end = ~0ul; \int i_min = __pmd_offset(start)
;\int i_max = __pmd_offset(end)
; \int i;\\ if (!pmd_present(pmd[i])
)
\continue; \\ pte = pte_offset(pmd + i, 0)
;\ if (i == i_max)
\cur_end = end; \\ ret |= kvm_mips_name_pte(pte, start, cur_end)
; \}\return ret; \ } \\ static int kvm_mips_name_pud(pud_t *pud, unsigned long start, \unsigned long end)
\define BUILD_PTE_RANGE_OP(name, op)
\ static int kvm_mips_name_pte(pte_t *pte, unsigned long start, \unsigned long end)
\int ret = 0; \int i_min = __pte_offset(start)
;\int i_max = __pte_offset(end)
; \int i;\pte_t old, new; \\ if (!pte_present(pte[i])
)
\continue; \\ old = pte[i];\ new = op(old)
;\ if (pte_val(new)
== pte_val(old)
)
\continue; \ set_pte(pte + i, new)
; \ ret = 1;\}\return ret; \ } \\\ static int kvm_mips_name_pmd(pmd_t *pmd, unsigned long start, \unsigned long end)
\int ret = 0; \pte_t *pte; \unsigned long cur_end = ~0ul; \int i_min = __pmd_offset(start)
;\int i_max = __pmd_offset(end)
; \int i;\\ if (!pmd_present(pmd[i])
)
\continue; \\ pte = pte_offset(pmd + i, 0)
;\ if (i == i_max)
\cur_end = end; \\ ret |= kvm_mips_name_pte(pte, start, cur_end)
; \}\return ret; \ } \\ static int kvm_mips_name_pud(pud_t *pud, unsigned long start, \unsigned long end)
\int ret = 0; \pmd_t *pmd; \unsigned long cur_end = ~0ul; \int i_min = __pud_offset(start)
;\int i_max = __pud_offset(end)
; \int i;\\ if (!pud_present(pud[i])
)
\continue; \\ pmd = pmd_offset(pud + i, 0)
;\ if (i == i_max)
\cur_end = end; \\ ret |= kvm_mips_name_pmd(pmd, start, cur_end)
; \}\return ret; \ } \\ static int kvm_mips_name_pgd(pgd_t *pgd, unsigned long start, \unsigned long end)
\int kvm_mips_mkclean_gpa_pt(struct kvm *kvm, gfn_t start_gfn, gfn_t end_gfn)
void kvm_arch_mmu_enable_log_dirty_pt_masked(struct kvm *kvm, struct kvm_memory_slot *slot, gfn_t gfn_offset, unsigned long mask)
static int kvm_mips_mkold_gpa_pt(struct kvm *kvm, gfn_t start_gfn, gfn_t end_gfn)
static int handle_hva_to_gpa(struct kvm *kvm, unsigned long start, unsigned long end, int (*handler)
(struct kvm *kvm, gfn_t gfn, gpa_t gfn_end, struct kvm_memory_slot *memslot, void *data)
, void *data)
static int kvm_unmap_hva_handler(struct kvm *kvm, gfn_t gfn, gfn_t gfn_end, struct kvm_memory_slot *memslot, void *data)
int kvm_unmap_hva_range(struct kvm *kvm, unsigned long start, unsigned long end)
static int kvm_set_spte_handler(struct kvm *kvm, gfn_t gfn, gfn_t gfn_end, struct kvm_memory_slot *memslot, void *data)
int kvm_set_spte_hva(struct kvm *kvm, unsigned long hva, pte_t pte)
static int kvm_age_hva_handler(struct kvm *kvm, gfn_t gfn, gfn_t gfn_end, struct kvm_memory_slot *memslot, void *data)
static int kvm_test_age_hva_handler(struct kvm *kvm, gfn_t gfn, gfn_t gfn_end, struct kvm_memory_slot *memslot, void *data)
int kvm_age_hva(struct kvm *kvm, unsigned long start, unsigned long end)
int kvm_test_age_hva(struct kvm *kvm, unsigned long hva)
static int _kvm_mips_map_page_fast(struct kvm_vcpu *vcpu, unsigned long gpa, bool write_fault, pte_t *out_entry, pte_t *out_buddy)
static int kvm_mips_map_page(struct kvm_vcpu *vcpu, unsigned long gpa, bool write_fault, pte_t *out_entry, pte_t *out_buddy)
static pte_t *kvm_trap_emul_pte_for_gva(struct kvm_vcpu *vcpu, unsigned long addr)
void kvm_trap_emul_invalidate_gva(struct kvm_vcpu *vcpu, unsigned long addr, bool user)
static bool kvm_mips_flush_gva_pte(pte_t *pte, unsigned long start_gva, unsigned long end_gva)
static bool kvm_mips_flush_gva_pmd(pmd_t *pmd, unsigned long start_gva, unsigned long end_gva)
static bool kvm_mips_flush_gva_pud(pud_t *pud, unsigned long start_gva, unsigned long end_gva)
static bool kvm_mips_flush_gva_pgd(pgd_t *pgd, unsigned long start_gva, unsigned long end_gva)
void kvm_mips_flush_gva_pt(pgd_t *pgd, enum kvm_mips_flush flags)
static pte_t kvm_mips_gpa_pte_to_gva_unmapped(pte_t pte)
static pte_t kvm_mips_gpa_pte_to_gva_mapped(pte_t pte, long entrylo)
int kvm_mips_handle_vz_root_tlb_fault(unsigned long badvaddr, struct kvm_vcpu *vcpu, bool write_fault)
int kvm_mips_handle_kseg0_tlb_fault(unsigned long badvaddr, struct kvm_vcpu *vcpu, bool write_fault)
int kvm_mips_handle_mapped_seg_tlb_fault(struct kvm_vcpu *vcpu, struct kvm_mips_tlb *tlb, unsigned long gva, bool write_fault)
int kvm_mips_handle_commpage_tlb_fault(unsigned long badvaddr, struct kvm_vcpu *vcpu)
static void kvm_mips_migrate_count(struct kvm_vcpu *vcpu)
void kvm_arch_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
enum kvm_mips_fault_result kvm_trap_emul_gva_fault(struct kvm_vcpu *vcpu, unsigned long gva, bool write)
int kvm_get_inst(u32 *opc, struct kvm_vcpu *vcpu, u32 *out)
\n
     15 struct kvm *kvm
     14 struct kvm_vcpu *vcpu
     13 unsigned long start
     10 \unsigned long end
      9 start
      6 pte_t *pte
      6 old
      6 end
      5 void *data
      5 struct kvm_memory_slot *memslot
      5 pmd_t *pmd
      5 pgd_t *pgd
      5 gfn_t gfn
      5 bool write_fault
      4 unsigned long start_gva
      4 unsigned long start_gpa
      4 unsigned long end_gva
      4 unsigned long end_gpa
      4 unsigned long addr
      4 pud_t *pud
      4 op
      4 name
      4 gfn_t gfn_end
      3 unsigned long end
      3 unsigned long badvaddr
      3 struct kvm_mmu_memory_cache *cache
      3 pte_valnew
      3 pte_t pte
      3 !pte_presentpte[i]
      3 pte + i
      3 new
      3 i == i_max
      3 gfn_t start_gfn
      3 gfn_t end_gfn
      3 cur_end
      3 0
      2 unsigned long hva
      2 unsigned long gva
      2 unsigned long gpa
      2 struct kvm_mmu_memory_cache *mc
      2 pte_t *out_entry
      2 pte_t *out_buddy
      2 pte
      2 !pmd_presentpmd[i]
      2 pmd + i
      1 void *page
      1 void
      1 unsigned long mask
      1 u32 *out
      1 u32 *opc
      1 struct kvm_mips_tlb *tlb
      1 struct kvm_memory_slot *slot
      1 !pud_presentpud[i]
      1 pud + i
      1 pmd
      1 long entrylo
      1 int min
      1 int max
      1 int *handler
      1 int cpu
      1 gpa_t gfn_end
      1 gfn_t gfn_offset
      1 enum kvm_mips_flush flags
      1 bool write
      1 bool user
