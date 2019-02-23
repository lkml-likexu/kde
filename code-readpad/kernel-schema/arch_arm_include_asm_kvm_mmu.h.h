
\n
static inline void kvm_set_s2pud_readonly(pud_t *pud)
static inline bool kvm_s2pud_readonly(pud_t *pud)
static inline void kvm_set_pud(pud_t *pud, pud_t new_pud)
static inline pud_t kvm_s2pud_mkwrite(pud_t pud)
static inline pud_t kvm_s2pud_mkexec(pud_t pud)
static inline bool kvm_s2pud_exec(pud_t *pud)
static inline pud_t kvm_s2pud_mkyoung(pud_t pud)
static inline bool kvm_s2pud_young(pud_t pud)
static inline pte_t kvm_s2pte_mkwrite(pte_t pte)
static inline pmd_t kvm_s2pmd_mkwrite(pmd_t pmd)
static inline pte_t kvm_s2pte_mkexec(pte_t pte)
static inline pmd_t kvm_s2pmd_mkexec(pmd_t pmd)
static inline void kvm_set_s2pte_readonly(pte_t *pte)
static inline bool kvm_s2pte_readonly(pte_t *pte)
static inline bool kvm_s2pte_exec(pte_t *pte)
static inline void kvm_set_s2pmd_readonly(pmd_t *pmd)
static inline bool kvm_s2pmd_readonly(pmd_t *pmd)
static inline bool kvm_s2pmd_exec(pmd_t *pmd)
static inline bool kvm_page_empty(void *ptr)
static inline bool vcpu_has_cache_enabled(struct kvm_vcpu *vcpu)
static inline void __clean_dcache_guest_page(kvm_pfn_t pfn, unsigned long size)
static inline void __invalidate_icache_guest_page(kvm_pfn_t pfn, unsigned long size)
static inline void __kvm_flush_dcache_pte(pte_t pte)
static inline void __kvm_flush_dcache_pmd(pmd_t pmd)
static inline void __kvm_flush_dcache_pud(pud_t pud)
static inline bool __kvm_cpu_uses_extended_idmap(void)
static inline unsigned long __kvm_idmap_ptrs_per_pgd(void)
static inline unsigned int kvm_get_vmid_bits(void)
static inline int kvm_read_guest_lock(struct kvm *kvm, gpa_t gpa, void *data, unsigned long len)
static inline void *kvm_get_hyp_vector(void)
static inline int kvm_map_vectors(void)
static inline int hyp_map_aux_data(void)
static inline bool kvm_cpu_has_cnp(void)
\n
      7 void
      5 pud_t pud
      4 pud_t *pud
      3 pte_t *pte
      3 pte_t pte
      3 pmd_t *pmd
      3 pmd_t pmd
      2 unsigned long size
      2 kvm_pfn_t pfn
      1 void *ptr
      1 void *data
      1 unsigned long len
      1 struct kvm_vcpu *vcpu
      1 struct kvm *kvm
      1 pud_t new_pud
      1 gpa_t gpa
