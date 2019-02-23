
\n
static inline int pte_dirty(pte_t pte)
static inline u32 read_pkru(void)
static inline void write_pkru(u32 pkru)
static inline int pte_young(pte_t pte)
static inline int pmd_dirty(pmd_t pmd)
static inline int pmd_young(pmd_t pmd)
static inline int pud_dirty(pud_t pud)
static inline int pud_young(pud_t pud)
static inline int pte_write(pte_t pte)
static inline int pte_huge(pte_t pte)
static inline int pte_global(pte_t pte)
static inline int pte_exec(pte_t pte)
static inline int pte_special(pte_t pte)
static inline unsigned long pte_pfn(pte_t pte)
static inline unsigned long pmd_pfn(pmd_t pmd)
static inline unsigned long pud_pfn(pud_t pud)
static inline unsigned long p4d_pfn(p4d_t p4d)
static inline unsigned long pgd_pfn(pgd_t pgd)
static inline int p4d_large(p4d_t p4d)
static inline int pmd_large(pmd_t pte)
static inline int pmd_trans_huge(pmd_t pmd)
static inline int pud_trans_huge(pud_t pud)
define has_transparent_hugepage has_transparent_hugepage static inline int has_transparent_hugepage(void)
static inline int pmd_devmap(pmd_t pmd)
static inline int pud_devmap(pud_t pud)
static inline int pud_devmap(pud_t pud)
return !!(pud_val(pud)
& _PAGE_DEVMAP)
; } static inline int pud_devmap(pud_t pud)
static inline int pgd_devmap(pgd_t pgd)
static inline pte_t pte_set_flags(pte_t pte, pteval_t set)
static inline pte_t pte_clear_flags(pte_t pte, pteval_t clear)
static inline pte_t pte_mkclean(pte_t pte)
static inline pte_t pte_mkold(pte_t pte)
static inline pte_t pte_wrprotect(pte_t pte)
static inline pte_t pte_mkexec(pte_t pte)
static inline pte_t pte_mkdirty(pte_t pte)
static inline pte_t pte_mkyoung(pte_t pte)
static inline pte_t pte_mkwrite(pte_t pte)
static inline pte_t pte_mkhuge(pte_t pte)
static inline pte_t pte_clrhuge(pte_t pte)
static inline pte_t pte_mkglobal(pte_t pte)
static inline pte_t pte_clrglobal(pte_t pte)
static inline pte_t pte_mkspecial(pte_t pte)
static inline pte_t pte_mkdevmap(pte_t pte)
static inline pmd_t pmd_set_flags(pmd_t pmd, pmdval_t set)
static inline pmd_t pmd_clear_flags(pmd_t pmd, pmdval_t clear)
static inline pmd_t pmd_mkold(pmd_t pmd)
static inline pmd_t pmd_mkclean(pmd_t pmd)
static inline pmd_t pmd_wrprotect(pmd_t pmd)
static inline pmd_t pmd_mkdirty(pmd_t pmd)
static inline pmd_t pmd_mkdevmap(pmd_t pmd)
static inline pmd_t pmd_mkhuge(pmd_t pmd)
static inline pmd_t pmd_mkyoung(pmd_t pmd)
static inline pmd_t pmd_mkwrite(pmd_t pmd)
static inline pud_t pud_set_flags(pud_t pud, pudval_t set)
static inline pud_t pud_clear_flags(pud_t pud, pudval_t clear)
static inline pud_t pud_mkold(pud_t pud)
static inline pud_t pud_mkclean(pud_t pud)
static inline pud_t pud_wrprotect(pud_t pud)
static inline pud_t pud_mkdirty(pud_t pud)
static inline pud_t pud_mkdevmap(pud_t pud)
static inline pud_t pud_mkhuge(pud_t pud)
static inline pud_t pud_mkyoung(pud_t pud)
static inline pud_t pud_mkwrite(pud_t pud)
static inline int pte_soft_dirty(pte_t pte)
static inline int pmd_soft_dirty(pmd_t pmd)
static inline int pud_soft_dirty(pud_t pud)
static inline pte_t pte_mksoft_dirty(pte_t pte)
static inline pmd_t pmd_mksoft_dirty(pmd_t pmd)
static inline pud_t pud_mksoft_dirty(pud_t pud)
static inline pte_t pte_clear_soft_dirty(pte_t pte)
static inline pmd_t pmd_clear_soft_dirty(pmd_t pmd)
static inline pud_t pud_clear_soft_dirty(pud_t pud)
static inline pgprotval_t massage_pgprot(pgprot_t pgprot)
static inline pgprotval_t check_pgprot(pgprot_t pgprot)
static inline pte_t pfn_pte(unsigned long page_nr, pgprot_t pgprot)
static inline pmd_t pfn_pmd(unsigned long page_nr, pgprot_t pgprot)
static inline pud_t pfn_pud(unsigned long page_nr, pgprot_t pgprot)
static inline pmd_t pmd_mknotpresent(pmd_t pmd)
static inline pud_t pud_mknotpresent(pud_t pud)
static inline pte_t pte_modify(pte_t pte, pgprot_t newprot)
static inline pmd_t pmd_modify(pmd_t pmd, pgprot_t newprot)
define pgprot_modify pgprot_modify static inline pgprot_t pgprot_modify(pgprot_t oldprot, pgprot_t newprot)
static inline pgprot_t arch_filter_pgprot(pgprot_t prot)
static inline int is_new_memtype_allowed(u64 paddr, unsigned long size, enum page_cache_mode pcm, enum page_cache_mode new_pcm)
static inline pgd_t pti_set_user_pgtbl(pgd_t *pgdp, pgd_t pgd)
static inline pgd_t pti_set_user_pgtbl(pgd_t *pgdp, pgd_t pgd)
if (!static_cpu_has(X86_FEATURE_PTI)
)
return pgd;return __pti_set_user_pgtbl(pgdp, pgd)
; } static inline pgd_t pti_set_user_pgtbl(pgd_t *pgdp, pgd_t pgd)
static inline int pte_none(pte_t pte)
define __HAVE_ARCH_PTE_SAME static inline int pte_same(pte_t a, pte_t b)
static inline int pte_present(pte_t a)
static inline int pte_devmap(pte_t a)
define pte_accessible pte_accessible static inline bool pte_accessible(struct mm_struct *mm, pte_t a)
static inline int pmd_present(pmd_t pmd)
static inline int pte_protnone(pte_t pte)
static inline int pmd_protnone(pmd_t pmd)
static inline int pmd_none(pmd_t pmd)
static inline unsigned long pmd_page_vaddr(pmd_t pmd)
static inline unsigned long pmd_index(unsigned long address)
static inline unsigned long pte_index(unsigned long address)
static inline pte_t *pte_offset_kernel(pmd_t *pmd, unsigned long address)
static inline int pmd_bad(pmd_t pmd)
static inline unsigned long pages_to_mb(unsigned long npg)
static inline int pud_none(pud_t pud)
static inline int pud_present(pud_t pud)
static inline unsigned long pud_page_vaddr(pud_t pud)
static inline pmd_t *pmd_offset(pud_t *pud, unsigned long address)
static inline int pud_large(pud_t pud)
static inline int pud_bad(pud_t pud)
static inline int pud_bad(pud_t pud)
return (pud_flags(pud)
& ~(_KERNPG_TABLE | _PAGE_USER)
)
!= 0; } static inline int pud_large(pud_t pud)
static inline unsigned long pud_index(unsigned long address)
static inline int p4d_none(p4d_t p4d)
static inline int p4d_present(p4d_t p4d)
static inline unsigned long p4d_page_vaddr(p4d_t p4d)
static inline pud_t *pud_offset(p4d_t *p4d, unsigned long address)
static inline int p4d_bad(p4d_t p4d)
static inline unsigned long p4d_index(unsigned long address)
static inline int pgd_present(pgd_t pgd)
static inline unsigned long pgd_page_vaddr(pgd_t pgd)
static inline p4d_t *p4d_offset(pgd_t *pgd, unsigned long address)
static inline int pgd_bad(pgd_t pgd)
static inline int pgd_none(pgd_t pgd)
extern pgd_t trampoline_pgd_entry; static inline void __meminit init_trampoline_default(void)
static inline pte_t native_local_ptep_get_and_clear(pte_t *ptep)
static inline pmd_t native_local_pmdp_get_and_clear(pmd_t *pmdp)
static inline pud_t native_local_pudp_get_and_clear(pud_t *pudp)
static inline void native_set_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep , pte_t pte)
static inline void set_pmd_at(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp, pmd_t pmd)
static inline void set_pud_at(struct mm_struct *mm, unsigned long addr, pud_t *pudp, pud_t pud)
define __HAVE_ARCH_PTEP_GET_AND_CLEAR static inline pte_t ptep_get_and_clear(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
define __HAVE_ARCH_PTEP_GET_AND_CLEAR_FULL static inline pte_t ptep_get_and_clear_full(struct mm_struct *mm, unsigned long addr, pte_t *ptep, int full)
define __HAVE_ARCH_PTEP_SET_WRPROTECT static inline void ptep_set_wrprotect(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
define pmd_write pmd_write static inline int pmd_write(pmd_t pmd)
define __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR static inline pmd_t pmdp_huge_get_and_clear(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp)
define __HAVE_ARCH_PUDP_HUGE_GET_AND_CLEAR static inline pud_t pudp_huge_get_and_clear(struct mm_struct *mm, unsigned long addr, pud_t *pudp)
define __HAVE_ARCH_PMDP_SET_WRPROTECT static inline void pmdp_set_wrprotect(struct mm_struct *mm, unsigned long addr, pmd_t *pmdp)
define pud_write pud_write static inline int pud_write(pud_t pud)
define pmdp_establish pmdp_establish static inline pmd_t pmdp_establish(struct vm_area_struct *vma, unsigned long address, pmd_t *pmdp, pmd_t pmd)
define pmdp_establish pmdp_establish static inline pmd_t pmdp_establish(struct vm_area_struct *vma, unsigned long address, pmd_t *pmdp, pmd_t pmd)
return xchg(pmdp, pmd)
; pmd_t old = *pmdp; WRITE_ONCE(*pmdp, pmd)
; return old;} }endifstatic inline bool pgdp_maps_userspace(void *__ptr)
static inline void *ptr_set_bit(void *ptr, int bit)
__ptr |= BIT(bit)
;return (void *)
__ptr; } static inline void *ptr_clear_bit(void *ptr, int bit)
static inline pgd_t *kernel_to_user_pgdp(pgd_t *pgdp)
static inline pgd_t *user_to_kernel_pgdp(pgd_t *pgdp)
static inline p4d_t *kernel_to_user_p4dp(p4d_t *p4dp)
static inline p4d_t *user_to_kernel_p4dp(p4d_t *p4dp)
static inline void clone_pgd_range(pgd_t *dst, pgd_t *src, int count)
define PTE_SHIFT ilog2(PTRS_PER_PTE)
static inline int page_level_shift(enum pg_level level)
define PTE_SHIFT ilog2(PTRS_PER_PTE)
static inline int page_level_shift(enum pg_level level)
return (PAGE_SHIFT - PTE_SHIFT)
+ level * PTE_SHIFT; } static inline unsigned long page_level_size(enum pg_level level)
define PTE_SHIFT ilog2(PTRS_PER_PTE)
static inline int page_level_shift(enum pg_level level)
return (PAGE_SHIFT - PTE_SHIFT)
+ level * PTE_SHIFT; } static inline unsigned long page_level_size(enum pg_level level)
return 1UL << page_level_shift(level)
; } static inline unsigned long page_level_mask(enum pg_level level)
static inline void update_mmu_cache(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep)
static inline void update_mmu_cache(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep)
} static inline void update_mmu_cache_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmd)
static inline void update_mmu_cache(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep)
} static inline void update_mmu_cache_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmd)
} static inline void update_mmu_cache_pud(struct vm_area_struct *vma, unsigned long addr, pud_t *pud)
static inline pte_t pte_swp_mksoft_dirty(pte_t pte)
static inline int pte_swp_soft_dirty(pte_t pte)
static inline pte_t pte_swp_clear_soft_dirty(pte_t pte)
static inline pmd_t pmd_swp_mksoft_dirty(pmd_t pmd)
static inline int pmd_swp_soft_dirty(pmd_t pmd)
static inline pmd_t pmd_swp_clear_soft_dirty(pmd_t pmd)
static inline bool __pkru_allows_read(u32 pkru, u16 pkey)
static inline bool __pkru_allows_write(u32 pkru, u16 pkey)
static inline u16 pte_flags_pkey(unsigned long pte_flags)
static inline bool __pkru_allows_pkey(u16 pkey, bool write)
static inline bool __pte_access_permitted(unsigned long pteval, bool write)
define pte_access_permitted pte_access_permitted static inline bool pte_access_permitted(pte_t pte, bool write)
define pmd_access_permitted pmd_access_permitted static inline bool pmd_access_permitted(pmd_t pmd, bool write)
define pud_access_permitted pud_access_permitted static inline bool pud_access_permitted(pud_t pud, bool write)
static inline bool arch_has_pfn_modify_check(void)
\n
     34 pte_t pte
     33 pmd_t pmd
     31 pud_t pud
     15 unsigned long addr
     10 unsigned long address
     10 struct mm_struct *mm
      9 pgd_t pgd
      8 struct vm_area_struct *vma
      7 pte_t *ptep
      6 pmd_t *pmdp
      6 p4d_t p4d
      6 enum pg_level level
      5 pgprot_t pgprot
      5 pgd_t *pgdp
      5 bool write
      4 void
      4 pte_t a
      3 unsigned long page_nr
      3 u32 pkru
      3 u16 pkey
      3 pud_t *pudp
      3 PTRS_PER_PTE
      3 pmd_t *pmd
      3 pgprot_t newprot
      2 void *ptr
      2 pud_t *pud
      2 pmd
      2 PAGE_SHIFT - PTE_SHIFT
      2 p4d_t *p4dp
      2 int bit
      1 void *__ptr
      1 void *
      1 unsigned long size
      1 unsigned long pteval
      1 unsigned long pte_flags
      1 unsigned long npg
      1 u64 paddr
      1 !static_cpu_hasX86_FEATURE_PTI
      1 pudval_t set
      1 pudval_t clear
      1 pud_valpud
      1 pud_flagspud
      1 pteval_t set
      1 pteval_t clear
      1 pte_t *ptep 
      1 pte_t b
      1 pmdval_t set
      1 pmdval_t clear
      1 pmd_t pte
      1 *pmdp
      1 pmdp
      1 pgprot_t prot
      1 pgprot_t oldprot
      1 pgd_t *src
      1 pgd_t *pgd
      1 pgd_t *dst
      1 pgdp
      1 pgd
      1 p4d_t *p4d
      1 level
      1 _KERNPG_TABLE | _PAGE_USER
      1 int full
      1 int count
      1 enum page_cache_mode pcm
      1 enum page_cache_mode new_pcm
      1 bit
