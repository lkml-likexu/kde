
\n
extern int isolate_lru_page(struct page *page)
;extern bool mm_iommu_preregistered(struct mm_struct *mm)
; extern long mm_iommu_new(struct mm_struct *mm, unsigned long ua, unsigned long entries, struct mm_iommu_table_group_mem_t **pmem)
; extern long mm_iommu_newdev(struct mm_struct *mm, unsigned long ua, unsigned long entries, unsigned long dev_hpa, struct mm_iommu_table_group_mem_t **pmem)
; extern long mm_iommu_put(struct mm_struct *mm, struct mm_iommu_table_group_mem_t *mem)
; extern void mm_iommu_init(struct mm_struct *mm)
; extern void mm_iommu_cleanup(struct mm_struct *mm)
; extern struct mm_iommu_table_group_mem_t *mm_iommu_lookup(struct mm_struct *mm, unsigned long ua, unsigned long size)
; extern struct mm_iommu_table_group_mem_t *mm_iommu_lookup_rm( struct mm_struct *mm, unsigned long ua, unsigned long size)
; extern struct mm_iommu_table_group_mem_t *mm_iommu_get(struct mm_struct *mm, unsigned long ua, unsigned long entries)
; extern long mm_iommu_ua_to_hpa(struct mm_iommu_table_group_mem_t *mem, unsigned long ua, unsigned int pageshift, unsigned long *hpa)
; extern long mm_iommu_ua_to_hpa_rm(struct mm_iommu_table_group_mem_t *mem, unsigned long ua, unsigned int pageshift, unsigned long *hpa)
; extern void mm_iommu_ua_mark_dirty_rm(struct mm_struct *mm, unsigned long ua)
; extern bool mm_iommu_is_devmem(struct mm_struct *mm, unsigned long hpa, unsigned int pageshift, unsigned long *size)
; extern long mm_iommu_mapped_inc(struct mm_iommu_table_group_mem_t *mem)
; extern void mm_iommu_mapped_dec(struct mm_iommu_table_group_mem_t *mem)
; static inline bool mm_iommu_is_devmem(struct mm_struct *mm, unsigned long hpa, unsigned int pageshift, unsigned long *size)
extern void radix__switch_mmu_context(struct mm_struct *prev, struct mm_struct *next)
; static inline void switch_mmu_context(struct mm_struct *prev, struct mm_struct *next, struct task_struct *tsk)
static inline int alloc_extended_context(struct mm_struct *mm, unsigned long ea)
static inline bool need_extra_context(struct mm_struct *mm, unsigned long ea)
extern void switch_mmu_context(struct mm_struct *prev, struct mm_struct *next, struct task_struct *tsk)
; extern unsigned long __init_new_context(void)
; extern void __destroy_context(unsigned long context_id)
; extern void mmu_context_init(void)
; static inline int alloc_extended_context(struct mm_struct *mm, unsigned long ea)
static inline bool need_extra_context(struct mm_struct *mm, unsigned long ea)
static inline void inc_mm_active_cpus(struct mm_struct *mm)
static inline void dec_mm_active_cpus(struct mm_struct *mm)
static inline void mm_context_add_copro(struct mm_struct *mm)
static inline void mm_context_remove_copro(struct mm_struct *mm)
static inline void switch_mm(struct mm_struct *prev, struct mm_struct *next, struct task_struct *tsk)
static inline void activate_mm(struct mm_struct *prev, struct mm_struct *next)
static inline void enter_lazy_tlb(struct mm_struct *mm, struct task_struct *tsk)
static inline void arch_exit_mmap(struct mm_struct *mm)
static inline void arch_unmap(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long start, unsigned long end)
static inline void arch_bprm_mm_init(struct mm_struct *mm, struct vm_area_struct *vma)
bool arch_vma_access_permitted(struct vm_area_struct *vma, bool write, bool execute, bool foreign)
; void arch_dup_pkeys(struct mm_struct *oldmm, struct mm_struct *mm)
; static inline bool arch_vma_access_permitted(struct vm_area_struct *vma, bool write, bool execute, bool foreign)
static inline u64 pte_to_hpte_pkey_bits(u64 pteflags)
static inline int arch_dup_mmap(struct mm_struct *oldmm, struct mm_struct *mm)
\n
     26 struct mm_struct *mm
      8 unsigned long ua
      5 struct mm_struct *prev
      5 struct mm_struct *next
      5 struct mm_iommu_table_group_mem_t *mem
      4 unsigned long ea
      4 unsigned int pageshift
      4 struct vm_area_struct *vma
      4 struct task_struct *tsk
      3 unsigned long entries
      2 void
      2 unsigned long *size
      2 unsigned long size
      2 unsigned long *hpa
      2 unsigned long hpa
      2 struct mm_struct *oldmm
      2 struct mm_iommu_table_group_mem_t **pmem
      2 bool write
      2 bool foreign
      2 bool execute
      1 unsigned long start
      1 unsigned long end
      1 unsigned long dev_hpa
      1 unsigned long context_id
      1 u64 pteflags
      1 struct page *page
