
\n
extern void __mpol_put(struct mempolicy *pol)
; static inline void mpol_put(struct mempolicy *pol)
static inline int mpol_needs_cond_ref(struct mempolicy *pol)
static inline void mpol_cond_put(struct mempolicy *pol)
extern struct mempolicy *__mpol_dup(struct mempolicy *pol)
; static inline struct mempolicy *mpol_dup(struct mempolicy *pol)
static inline void mpol_get(struct mempolicy *pol)
extern bool __mpol_equal(struct mempolicy *a, struct mempolicy *b)
; static inline bool mpol_equal(struct mempolicy *a, struct mempolicy *b)
static inline void check_highest_zone(enum zone_type k)
static inline bool vma_migratable(struct vm_area_struct *vma)
static inline bool mpol_equal(struct mempolicy *a, struct mempolicy *b)
static inline void mpol_put(struct mempolicy *p)
static inline void mpol_cond_put(struct mempolicy *pol)
static inline void mpol_get(struct mempolicy *pol)
static inline void mpol_shared_policy_init(struct shared_policy *sp, struct mempolicy *mpol)
static inline void mpol_free_shared_policy(struct shared_policy *p)
static inline struct mempolicy * mpol_shared_policy_lookup(struct shared_policy *sp, unsigned long idx)
static inline int vma_dup_policy(struct vm_area_struct *src, struct vm_area_struct *dst)
static inline void numa_policy_init(void)
static inline void numa_default_policy(void)
static inline void mpol_rebind_task(struct task_struct *tsk, const nodemask_t *new)
static inline void mpol_rebind_mm(struct mm_struct *mm, nodemask_t *new)
static inline int huge_node(struct vm_area_struct *vma, unsigned long addr, gfp_t gfp_flags, struct mempolicy **mpol, nodemask_t **nodemask)
static inline bool init_nodemask_of_mempolicy(nodemask_t *m)
static inline int do_migrate_pages(struct mm_struct *mm, const nodemask_t *from, const nodemask_t *to, int flags)
static inline void check_highest_zone(int k)
static inline int mpol_parse_str(char *str, struct mempolicy **mpol)
static inline int mpol_misplaced(struct page *page, struct vm_area_struct *vma, unsigned long address)
static inline void mpol_put_task_policy(struct task_struct *task)
\n
      9 struct mempolicy *pol
      3 struct vm_area_struct *vma
      3 struct mempolicy *b
      3 struct mempolicy *a
      2 void
      2 struct shared_policy *sp
      2 struct mm_struct *mm
      2 struct mempolicy **mpol
      1 unsigned long idx
      1 unsigned long address
      1 unsigned long addr
      1 struct vm_area_struct *src
      1 struct vm_area_struct *dst
      1 struct task_struct *tsk
      1 struct task_struct *task
      1 struct shared_policy *p
      1 struct page *page
      1 struct mempolicy *p
      1 struct mempolicy *mpol
      1 nodemask_t **nodemask
      1 nodemask_t *new
      1 nodemask_t *m
      1 int k
      1 int flags
      1 gfp_t gfp_flags
      1 enum zone_type k
      1 const nodemask_t *to
      1 const nodemask_t *new
      1 const nodemask_t *from
      1 char *str
