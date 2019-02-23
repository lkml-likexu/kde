
\n
static inline unsigned long __kern_hyp_va(unsigned long v)
static inline bool kvm_page_empty(void *ptr)
static inline pte_t kvm_s2pte_mkwrite(pte_t pte)
static inline pmd_t kvm_s2pmd_mkwrite(pmd_t pmd)
static inline pud_t kvm_s2pud_mkwrite(pud_t pud)
static inline pte_t kvm_s2pte_mkexec(pte_t pte)
static inline pmd_t kvm_s2pmd_mkexec(pmd_t pmd)
static inline pud_t kvm_s2pud_mkexec(pud_t pud)
static inline void kvm_set_s2pte_readonly(pte_t *ptep)
static inline bool kvm_s2pte_readonly(pte_t *ptep)
static inline bool kvm_s2pte_exec(pte_t *ptep)
static inline void kvm_set_s2pmd_readonly(pmd_t *pmdp)
static inline bool kvm_s2pmd_readonly(pmd_t *pmdp)
static inline bool kvm_s2pmd_exec(pmd_t *pmdp)
static inline void kvm_set_s2pud_readonly(pud_t *pudp)
static inline bool kvm_s2pud_readonly(pud_t *pudp)
static inline bool kvm_s2pud_exec(pud_t *pudp)
static inline pud_t kvm_s2pud_mkyoung(pud_t pud)
static inline bool kvm_s2pud_young(pud_t pud)
static inline bool vcpu_has_cache_enabled(struct kvm_vcpu *vcpu)
static inline void __clean_dcache_guest_page(kvm_pfn_t pfn, unsigned long size)
static inline void __invalidate_icache_guest_page(kvm_pfn_t pfn, unsigned long size)
static inline void __kvm_flush_dcache_pte(pte_t pte)
static inline void __kvm_flush_dcache_pmd(pmd_t pmd)
static inline void __kvm_flush_dcache_pud(pud_t pud)
static inline bool __kvm_cpu_uses_extended_idmap(void)
static inline unsigned long __kvm_idmap_ptrs_per_pgd(void)
static inline void __kvm_extend_hypmap(pgd_t *boot_hyp_pgd, pgd_t *hyp_pgd, pgd_t *merged_hyp_pgd, unsigned long hyp_idmap_start)
static inline unsigned int kvm_get_vmid_bits(void)
static inline int kvm_read_guest_lock(struct kvm *kvm, gpa_t gpa, void *data, unsigned long len)
static inline void *kvm_get_hyp_vector(void)
static inline int kvm_map_vectors(void)
return 0; } static inline void *kvm_get_hyp_vector(void)
static inline int kvm_map_vectors(void)
static inline int hyp_map_aux_data(void)
ptr = per_cpu_ptr(&arm64_ssbd_callback_required, cpu)
; err = create_hyp_mappings(ptr, ptr + 1, PAGE_HYP)
; if (err)
return err;}return 0; } static inline int hyp_map_aux_data(void)
static inline int arm64_vttbr_x(u32 ipa_shift, u32 levels)
static inline u64 vttbr_baddr_mask(u32 ipa_shift, u32 levels)
static inline u64 kvm_vttbr_baddr_mask(struct kvm *kvm)
static inline bool kvm_cpu_has_cnp(void)
\n
     10 void
      5 pud_t pud
      3 pud_t *pudp
      3 pte_t *ptep
      3 pte_t pte
      3 pmd_t *pmdp
      3 pmd_t pmd
      2 unsigned long size
      2 u32 levels
      2 u32 ipa_shift
      2 struct kvm *kvm
      2 kvm_pfn_t pfn
      1 void *ptr
      1 void *data
      1 unsigned long v
      1 unsigned long len
      1 unsigned long hyp_idmap_start
      1 struct kvm_vcpu *vcpu
      1 ptr + 1
      1 ptr
      1 pgd_t *merged_hyp_pgd
      1 pgd_t *hyp_pgd
      1 pgd_t *boot_hyp_pgd
      1 PAGE_HYP
      1 gpa_t gpa
      1 err
      1 cpu
      1 &arm64_ssbd_callback_required
