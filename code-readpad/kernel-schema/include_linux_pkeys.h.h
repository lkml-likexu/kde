
\n
static inline int vma_pkey(struct vm_area_struct *vma)
static inline bool mm_pkey_is_allocated(struct mm_struct *mm, int pkey)
static inline int mm_pkey_alloc(struct mm_struct *mm)
static inline int mm_pkey_free(struct mm_struct *mm, int pkey)
static inline int arch_set_user_pkey_access(struct task_struct *tsk, int pkey, unsigned long init_val)
static inline bool arch_pkeys_enabled(void)
static inline void copy_init_pkru_to_fpregs(void)
\n
      3 struct mm_struct *mm
      3 int pkey
      2 void
      1 unsigned long init_val
      1 struct vm_area_struct *vma
      1 struct task_struct *tsk
