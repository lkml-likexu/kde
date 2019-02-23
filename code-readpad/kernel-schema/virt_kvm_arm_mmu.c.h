
\n
static bool memslot_is_logging(struct kvm_memory_slot *memslot)
void kvm_flush_remote_tlbs(struct kvm *kvm)
static void kvm_tlb_flush_vmid_ipa(struct kvm *kvm, phys_addr_t ipa)
static void kvm_flush_dcache_pte(pte_t pte)
static void kvm_flush_dcache_pmd(pmd_t pmd)
static void kvm_flush_dcache_pud(pud_t pud)
static bool kvm_is_device_pfn(unsigned long pfn)
static void stage2_dissolve_pmd(struct kvm *kvm, phys_addr_t addr, pmd_t *pmd)
static void stage2_dissolve_pud(struct kvm *kvm, phys_addr_t addr, pud_t *pudp)
static int mmu_topup_memory_cache(struct kvm_mmu_memory_cache *cache, int min, int max)
static void mmu_free_memory_cache(struct kvm_mmu_memory_cache *mc)
static void *mmu_memory_cache_alloc(struct kvm_mmu_memory_cache *mc)
static void clear_stage2_pgd_entry(struct kvm *kvm, pgd_t *pgd, phys_addr_t addr)
static void clear_stage2_pud_entry(struct kvm *kvm, pud_t *pud, phys_addr_t addr)
static void clear_stage2_pmd_entry(struct kvm *kvm, pmd_t *pmd, phys_addr_t addr)
static inline void kvm_set_pte(pte_t *ptep, pte_t new_pte)
static inline void kvm_set_pmd(pmd_t *pmdp, pmd_t new_pmd)
static inline void kvm_pmd_populate(pmd_t *pmdp, pte_t *ptep)
static inline void kvm_pud_populate(pud_t *pudp, pmd_t *pmdp)
static inline void kvm_pgd_populate(pgd_t *pgdp, pud_t *pudp)
static void unmap_stage2_ptes(struct kvm *kvm, pmd_t *pmd, phys_addr_t addr, phys_addr_t end)
static void unmap_stage2_pmds(struct kvm *kvm, pud_t *pud, phys_addr_t addr, phys_addr_t end)
static void unmap_stage2_puds(struct kvm *kvm, pgd_t *pgd, phys_addr_t addr, phys_addr_t end)
static void unmap_stage2_range(struct kvm *kvm, phys_addr_t start, u64 size)
static void stage2_flush_ptes(struct kvm *kvm, pmd_t *pmd, phys_addr_t addr, phys_addr_t end)
static void stage2_flush_pmds(struct kvm *kvm, pud_t *pud, phys_addr_t addr, phys_addr_t end)
static void stage2_flush_puds(struct kvm *kvm, pgd_t *pgd, phys_addr_t addr, phys_addr_t end)
static void stage2_flush_memslot(struct kvm *kvm, struct kvm_memory_slot *memslot)
static void stage2_flush_vm(struct kvm *kvm)
static void clear_hyp_pgd_entry(pgd_t *pgd)
static void clear_hyp_pud_entry(pud_t *pud)
static void clear_hyp_pmd_entry(pmd_t *pmd)
static void unmap_hyp_ptes(pmd_t *pmd, phys_addr_t addr, phys_addr_t end)
static void unmap_hyp_pmds(pud_t *pud, phys_addr_t addr, phys_addr_t end)
static void unmap_hyp_puds(pgd_t *pgd, phys_addr_t addr, phys_addr_t end)
static unsigned int kvm_pgd_index(unsigned long addr, unsigned int ptrs_per_pgd)
static void __unmap_hyp_range(pgd_t *pgdp, unsigned long ptrs_per_pgd, phys_addr_t start, u64 size)
static void unmap_hyp_range(pgd_t *pgdp, phys_addr_t start, u64 size)
static void unmap_hyp_idmap_range(pgd_t *pgdp, phys_addr_t start, u64 size)
void free_hyp_pgds(void)
static void create_hyp_pte_mappings(pmd_t *pmd, unsigned long start, unsigned long end, unsigned long pfn, pgprot_t prot)
static int create_hyp_pmd_mappings(pud_t *pud, unsigned long start, unsigned long end, unsigned long pfn, pgprot_t prot)
static int create_hyp_pud_mappings(pgd_t *pgd, unsigned long start, unsigned long end, unsigned long pfn, pgprot_t prot)
static int __create_hyp_mappings(pgd_t *pgdp, unsigned long ptrs_per_pgd, unsigned long start, unsigned long end, unsigned long pfn, pgprot_t prot)
static phys_addr_t kvm_kaddr_to_phys(void *kaddr)
int create_hyp_mappings(void *from, void *to, pgprot_t prot)
static int __create_hyp_private_mapping(phys_addr_t phys_addr, size_t size, unsigned long *haddr, pgprot_t prot)
int create_hyp_io_mappings(phys_addr_t phys_addr, size_t size, void __iomem **kaddr, void __iomem **haddr)
int create_hyp_exec_mappings(phys_addr_t phys_addr, size_t size, void **haddr)
int kvm_alloc_stage2_pgd(struct kvm *kvm)
static void stage2_unmap_memslot(struct kvm *kvm, struct kvm_memory_slot *memslot)
void stage2_unmap_vm(struct kvm *kvm)
void kvm_free_stage2_pgd(struct kvm *kvm)
static pud_t *stage2_get_pud(struct kvm *kvm, struct kvm_mmu_memory_cache *cache, phys_addr_t addr)
static pmd_t *stage2_get_pmd(struct kvm *kvm, struct kvm_mmu_memory_cache *cache, phys_addr_t addr)
static int stage2_set_pmd_huge(struct kvm *kvm, struct kvm_mmu_memory_cache *cache, phys_addr_t addr, const pmd_t *new_pmd)
static int stage2_set_pud_huge(struct kvm *kvm, struct kvm_mmu_memory_cache *cache, phys_addr_t addr, const pud_t *new_pudp)
static bool stage2_get_leaf_entry(struct kvm *kvm, phys_addr_t addr, pud_t **pudpp, pmd_t **pmdpp, pte_t **ptepp)
static bool stage2_is_exec(struct kvm *kvm, phys_addr_t addr)
static int stage2_set_pte(struct kvm *kvm, struct kvm_mmu_memory_cache *cache, phys_addr_t addr, const pte_t *new_pte, unsigned long flags)
static int stage2_ptep_test_and_clear_young(pte_t *pte)
static int stage2_ptep_test_and_clear_young(pte_t *pte)
*pte = pte_mkold(*pte)
; return 1;}return 0; } static int stage2_ptep_test_and_clear_young(pte_t *pte)
static int stage2_pmdp_test_and_clear_young(pmd_t *pmd)
static int stage2_pudp_test_and_clear_young(pud_t *pud)
int kvm_phys_addr_ioremap(struct kvm *kvm, phys_addr_t guest_ipa, phys_addr_t pa, unsigned long size, bool writable)
static bool transparent_hugepage_adjust(kvm_pfn_t *pfnp, phys_addr_t *ipap)
static bool kvm_is_write_fault(struct kvm_vcpu *vcpu)
static void stage2_wp_ptes(pmd_t *pmd, phys_addr_t addr, phys_addr_t end)
static void stage2_wp_pmds(struct kvm *kvm, pud_t *pud, phys_addr_t addr, phys_addr_t end)
static voidstage2_wp_puds(struct kvm *kvm, pgd_t *pgd, phys_addr_t addr, phys_addr_t end)
static void stage2_wp_range(struct kvm *kvm, phys_addr_t addr, phys_addr_t end)
void kvm_mmu_wp_memory_region(struct kvm *kvm, int slot)
static void kvm_mmu_write_protect_pt_masked(struct kvm *kvm, struct kvm_memory_slot *slot, gfn_t gfn_offset, unsigned long mask)
void kvm_arch_mmu_enable_log_dirty_pt_masked(struct kvm *kvm, struct kvm_memory_slot *slot, gfn_t gfn_offset, unsigned long mask)
static void clean_dcache_guest_page(kvm_pfn_t pfn, unsigned long size)
static void invalidate_icache_guest_page(kvm_pfn_t pfn, unsigned long size)
static void kvm_send_hwpoison_signal(unsigned long address, struct vm_area_struct *vma)
static bool fault_supports_stage2_pmd_mappings(struct kvm_memory_slot *memslot, unsigned long hva)
static int user_mem_abort(struct kvm_vcpu *vcpu, phys_addr_t fault_ipa, struct kvm_memory_slot *memslot, unsigned long hva, unsigned long fault_status)
static void handle_access_fault(struct kvm_vcpu *vcpu, phys_addr_t fault_ipa)
int kvm_handle_guest_abort(struct kvm_vcpu *vcpu, struct kvm_run *run)
static int handle_hva_to_gpa(struct kvm *kvm, unsigned long start, unsigned long end, int (*handler)
(struct kvm *kvm, gpa_t gpa, u64 size, void *data)
, void *data)
static int kvm_unmap_hva_handler(struct kvm *kvm, gpa_t gpa, u64 size, void *data)
int kvm_unmap_hva_range(struct kvm *kvm, unsigned long start, unsigned long end)
static int kvm_set_spte_handler(struct kvm *kvm, gpa_t gpa, u64 size, void *data)
int kvm_set_spte_hva(struct kvm *kvm, unsigned long hva, pte_t pte)
static int kvm_age_hva_handler(struct kvm *kvm, gpa_t gpa, u64 size, void *data)
static int kvm_test_age_hva_handler(struct kvm *kvm, gpa_t gpa, u64 size, void *data)
int kvm_age_hva(struct kvm *kvm, unsigned long start, unsigned long end)
int kvm_test_age_hva(struct kvm *kvm, unsigned long hva)
void kvm_mmu_free_memory_caches(struct kvm_vcpu *vcpu)
phys_addr_t kvm_mmu_get_httbr(void)
phys_addr_t kvm_get_idmap_vector(void)
static int kvm_map_idmap_text(pgd_t *pgd)
int kvm_mmu_init(void)
void kvm_arch_commit_memory_region(struct kvm *kvm, const struct kvm_userspace_memory_region *mem, const struct kvm_memory_slot *old, const struct kvm_memory_slot *new, enum kvm_mr_change change)
int kvm_arch_prepare_memory_region(struct kvm *kvm, struct kvm_memory_slot *memslot, const struct kvm_userspace_memory_region *mem, enum kvm_mr_change change)
void kvm_arch_free_memslot(struct kvm *kvm, struct kvm_memory_slot *free, struct kvm_memory_slot *dont)
int kvm_arch_create_memslot(struct kvm *kvm, struct kvm_memory_slot *slot, unsigned long npages)
void kvm_arch_memslots_updated(struct kvm *kvm, struct kvm_memslots *slots)
void kvm_arch_flush_shadow_all(struct kvm *kvm)
void kvm_arch_flush_shadow_memslot(struct kvm *kvm, struct kvm_memory_slot *slot)
void kvm_set_way_flush(struct kvm_vcpu *vcpu)
void kvm_toggle_cache(struct kvm_vcpu *vcpu, bool was_enabled)
\n
     51 struct kvm *kvm
     25 phys_addr_t addr
     13 phys_addr_t end
      9 u64 size
      9 pmd_t *pmd
      8 pud_t *pud
      8 pgd_t *pgd
      7 unsigned long start
      7 unsigned long end
      7 struct kvm_vcpu *vcpu
      6 struct kvm_mmu_memory_cache *cache
      6 struct kvm_memory_slot *memslot
      6 pgprot_t prot
      5 void *data
      5 unsigned long pfn
      5 pgd_t *pgdp
      5 gpa_t gpa
      4 void
      4 unsigned long hva
      4 struct kvm_memory_slot *slot
      4 phys_addr_t start
      3 unsigned long size
      3 size_t size
      3 pud_t *pudp
      3 pte_t *pte
      3 pmd_t *pmdp
      3 phys_addr_t phys_addr
      2 unsigned long ptrs_per_pgd
      2 unsigned long mask
      2 struct kvm_mmu_memory_cache *mc
      2 pte_t *ptep
      2 pte_t pte
      2 phys_addr_t fault_ipa
      2 kvm_pfn_t pfn
      2 gfn_t gfn_offset
      2 enum kvm_mr_change change
      2 const struct kvm_userspace_memory_region *mem
      1 void *to
      1 void *kaddr
      1 void __iomem **kaddr
      1 void __iomem **haddr
      1 void **haddr
      1 void *from
      1 unsigned long npages
      1 unsigned long *haddr
      1 unsigned long flags
      1 unsigned long fault_status
      1 unsigned long address
      1 unsigned long addr
      1 unsigned int ptrs_per_pgd
      1 struct vm_area_struct *vma
      1 struct kvm_run *run
      1 struct kvm_memslots *slots
      1 struct kvm_memory_slot *free
      1 struct kvm_memory_slot *dont
      1 pud_t **pudpp
      1 pud_t pud
      1 pte_t **ptepp
      1 pte_t new_pte
      1 *pte
      1 pmd_t **pmdpp
      1 pmd_t pmd
      1 pmd_t new_pmd
      1 phys_addr_t pa
      1 phys_addr_t *ipap
      1 phys_addr_t ipa
      1 phys_addr_t guest_ipa
      1 kvm_pfn_t *pfnp
      1 int slot
      1 int min
      1 int max
      1 int *handler
      1 const struct kvm_memory_slot *old
      1 const struct kvm_memory_slot *new
      1 const pud_t *new_pudp
      1 const pte_t *new_pte
      1 const pmd_t *new_pmd
      1 bool writable
      1 bool was_enabled
