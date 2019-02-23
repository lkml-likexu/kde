
\n
static inline bool kvm_stage2_has_pud(struct kvm *kvm)
static inline bool stage2_pgd_none(struct kvm *kvm, pgd_t pgd)
static inline void stage2_pgd_clear(struct kvm *kvm, pgd_t *pgdp)
static inline bool stage2_pgd_present(struct kvm *kvm, pgd_t pgd)
static inline void stage2_pgd_populate(struct kvm *kvm, pgd_t *pgd, pud_t *pud)
static inline pud_t *stage2_pud_offset(struct kvm *kvm, pgd_t *pgd, unsigned long address)
static inline void stage2_pud_free(struct kvm *kvm, pud_t *pud)
static inline bool stage2_pud_table_empty(struct kvm *kvm, pud_t *pudp)
static inline phys_addr_t stage2_pud_addr_end(struct kvm *kvm, phys_addr_t addr, phys_addr_t end)
static inline bool kvm_stage2_has_pmd(struct kvm *kvm)
static inline bool stage2_pud_none(struct kvm *kvm, pud_t pud)
static inline void stage2_pud_clear(struct kvm *kvm, pud_t *pud)
static inline bool stage2_pud_present(struct kvm *kvm, pud_t pud)
static inline void stage2_pud_populate(struct kvm *kvm, pud_t *pud, pmd_t *pmd)
static inline pmd_t *stage2_pmd_offset(struct kvm *kvm, pud_t *pud, unsigned long address)
static inline void stage2_pmd_free(struct kvm *kvm, pmd_t *pmd)
static inline bool stage2_pud_huge(struct kvm *kvm, pud_t pud)
static inline bool stage2_pmd_table_empty(struct kvm *kvm, pmd_t *pmdp)
static inline phys_addr_t stage2_pmd_addr_end(struct kvm *kvm, phys_addr_t addr, phys_addr_t end)
static inline bool stage2_pte_table_empty(struct kvm *kvm, pte_t *ptep)
static inline unsigned long stage2_pgd_index(struct kvm *kvm, phys_addr_t addr)
static inline phys_addr_t stage2_pgd_addr_end(struct kvm *kvm, phys_addr_t addr, phys_addr_t end)
\n
     22 struct kvm *kvm
      5 pud_t *pud
      4 phys_addr_t addr
      3 pud_t pud
      3 phys_addr_t end
      2 unsigned long address
      2 pmd_t *pmd
      2 pgd_t *pgd
      2 pgd_t pgd
      1 pud_t *pudp
      1 pte_t *ptep
      1 pmd_t *pmdp
      1 pgd_t *pgdp
