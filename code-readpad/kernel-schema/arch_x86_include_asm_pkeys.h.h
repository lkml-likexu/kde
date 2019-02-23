
\n
static inline bool arch_pkeys_enabled(void)
extern int __execute_only_pkey(struct mm_struct *mm)
; static inline int execute_only_pkey(struct mm_struct *mm)
extern int __arch_override_mprotect_pkey(struct vm_area_struct *vma, int prot, int pkey)
; static inline int arch_override_mprotect_pkey(struct vm_area_struct *vma, int prot, int pkey)
static inline bool mm_pkey_is_allocated(struct mm_struct *mm, int pkey)
static inline int mm_pkey_alloc(struct mm_struct *mm)
static inline int mm_pkey_free(struct mm_struct *mm, int pkey)
static inline int vma_pkey(struct vm_area_struct *vma)
\n
      5 struct mm_struct *mm
      4 int pkey
      3 struct vm_area_struct *vma
      2 int prot
      1 void
