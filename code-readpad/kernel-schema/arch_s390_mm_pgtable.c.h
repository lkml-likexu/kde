
EXPORT_SYMBOL_GPL(ptep_test_and_clear_uc);
\n
static inline void ptep_ipte_local(struct mm_struct *mm, unsigned long addr, pte_t *ptep, int nodat)
static inline void ptep_ipte_global(struct mm_struct *mm, unsigned long addr, pte_t *ptep, int nodat)
static inline pte_t ptep_flush_direct(struct mm_struct *mm, unsigned long addr, pte_t *ptep, int nodat)
static inline pte_t ptep_flush_lazy(struct mm_struct *mm, unsigned long addr, pte_t *ptep, int nodat)
static inline pgste_t pgste_get_lock(pte_t *ptep)
static inline void pgste_set_unlock(pte_t *ptep, pgste_t pgste)
static inline pgste_t pgste_get(pte_t *ptep)
static inline void pgste_set(pte_t *ptep, pgste_t pgste)
static inline pgste_t pgste_update_all(pte_t pte, pgste_t pgste, struct mm_struct *mm)
static inline void pgste_set_key(pte_t *ptep, pgste_t pgste, pte_t entry, struct mm_struct *mm)
static inline pgste_t pgste_set_pte(pte_t *ptep, pgste_t pgste, pte_t entry)
static inline pgste_t pgste_pte_notify(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pgste_t pgste)
static inline pgste_t ptep_xchg_start(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
static inline pte_t ptep_xchg_commit(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pgste_t pgste, pte_t old, pte_t new)
pte_t ptep_xchg_direct(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t new)
pte_t ptep_xchg_lazy(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t new)
pte_t ptep_modify_prot_start(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
void ptep_modify_prot_commit(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t pte)
static inline void pmdp_idte_local(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp)
static inline void pmdp_idte_global(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp)
static inline pmd_t pmdp_flush_direct(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp)
static inline pmd_t pmdp_flush_lazy(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp)
static pmd_t *pmd_alloc_map(struct mm_struct *mm, unsigned long addr)
pmd_t pmdp_xchg_direct(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp, pmd_t new)
pmd_t pmdp_xchg_lazy(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp, pmd_t new)
static inline void pudp_idte_local(struct mm_struct *mm, unsigned long addr, pud_t *pudp)
static inline void pudp_idte_global(struct mm_struct *mm, unsigned long addr, pud_t *pudp)
static inline pud_t pudp_flush_direct(struct mm_struct *mm, unsigned long addr, pud_t *pudp)
pud_t pudp_xchg_direct(struct mm_struct *mm, unsigned long addr, pud_t *pudp, pud_t new)
void pgtable_trans_huge_deposit(struct mm_struct *mm, pmd_t *pmdp, pgtable_t pgtable)
pgtable_t pgtable_trans_huge_withdraw(struct mm_struct *mm, pmd_t *pmdp)
void ptep_set_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t entry)
void ptep_set_notify(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
int ptep_force_prot(struct mm_struct *mm, unsigned long addr, pte_t *ptep, int prot, unsigned long bit)
int ptep_shadow_pte(struct mm_struct *mm, unsigned long saddr, pte_t *sptep, pte_t *tptep, pte_t pte)
void ptep_unshadow_pte(struct mm_struct *mm, unsigned long saddr, pte_t *ptep)
static void ptep_zap_swap_entry(struct mm_struct *mm, swp_entry_t entry)
void ptep_zap_unused(struct mm_struct *mm, unsigned long addr, pte_t *ptep, int reset)
void ptep_zap_key(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
bool ptep_test_and_clear_uc(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
int set_guest_storage_key(struct mm_struct *mm, unsigned long addr, unsigned char key, bool nq)
int cond_set_guest_storage_key(struct mm_struct *mm, unsigned long addr, unsigned char key, unsigned char *oldkey, bool nq, bool mr, bool mc)
int reset_guest_reference_bit(struct mm_struct *mm, unsigned long addr)
int get_guest_storage_key(struct mm_struct *mm, unsigned long addr, unsigned char *key)
int pgste_perform_essa(struct mm_struct *mm, unsigned long hva, int orc, unsigned long *oldpte, unsigned long *oldpgste)
int set_pgste_bits(struct mm_struct *mm, unsigned long hva, unsigned long bits, unsigned long value)
int get_pgste(struct mm_struct *mm, unsigned long hva, unsigned long *pgstep)
\n
     42 struct mm_struct *mm
     32 unsigned long addr
     24 pte_t *ptep
      8 pmd_t *pmdp
      7 pgste_t pgste
      4 pud_t *pudp
      4 int nodat
      3 unsigned long hva
      3 pte_t pte
      3 pte_t new
      3 pte_t entry
      2 unsigned long saddr
      2 unsigned char key
      2 pmd_t new
      2 bool nq
      1 unsigned long value
      1 unsigned long *pgstep
      1 unsigned long *oldpte
      1 unsigned long *oldpgste
      1 unsigned long bits
      1 unsigned long bit
      1 unsigned char *oldkey
      1 unsigned char *key
      1 swp_entry_t entry
      1 pud_t new
      1 pte_t *tptep
      1 pte_t *sptep
      1 pte_t old
      1 ptep_test_and_clear_uc
      1 pgtable_t pgtable
      1 int reset
      1 int prot
      1 int orc
      1 bool mr
      1 bool mc
