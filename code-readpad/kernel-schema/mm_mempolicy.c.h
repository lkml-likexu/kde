
\n
struct mempolicy *get_task_policy(struct task_struct *p)
static inline int mpol_store_user_nodemask(const struct mempolicy *pol)
static void mpol_relative_nodemask(nodemask_t *ret, const nodemask_t *orig, const nodemask_t *rel)
static int mpol_new_interleave(struct mempolicy *pol, const nodemask_t *nodes)
static int mpol_new_preferred(struct mempolicy *pol, const nodemask_t *nodes)
static int mpol_new_bind(struct mempolicy *pol, const nodemask_t *nodes)
static int mpol_set_nodemask(struct mempolicy *pol, const nodemask_t *nodes, struct nodemask_scratch *nsc)
static struct mempolicy *mpol_new(unsigned short mode, unsigned short flags, nodemask_t *nodes)
void __mpol_put(struct mempolicy *p)
static void mpol_rebind_default(struct mempolicy *pol, const nodemask_t *nodes)
static void mpol_rebind_nodemask(struct mempolicy *pol, const nodemask_t *nodes)
static void mpol_rebind_preferred(struct mempolicy *pol, const nodemask_t *nodes)
static void mpol_rebind_policy(struct mempolicy *pol, const nodemask_t *newmask)
void mpol_rebind_task(struct task_struct *tsk, const nodemask_t *new)
void mpol_rebind_mm(struct mm_struct *mm, nodemask_t *new)
static inline bool queue_pages_required(struct page *page, struct queue_pages *qp)
static int queue_pages_pmd(pmd_t *pmd, spinlock_t *ptl, unsigned long addr, unsigned long end, struct mm_walk *walk)
static int queue_pages_pte_range(pmd_t *pmd, unsigned long addr, unsigned long end, struct mm_walk *walk)
static int queue_pages_hugetlb(pte_t *pte, unsigned long hmask, unsigned long addr, unsigned long end, struct mm_walk *walk)
unsigned long change_prot_numa(struct vm_area_struct *vma, unsigned long addr, unsigned long end)
return nr_updated; } static unsigned long change_prot_numa(struct vm_area_struct *vma, unsigned long addr, unsigned long end)
static int queue_pages_test_walk(unsigned long start, unsigned long end, struct mm_walk *walk)
static int queue_pages_range(struct mm_struct *mm, unsigned long start, unsigned long end, nodemask_t *nodes, unsigned long flags, struct list_head *pagelist)
static int vma_replace_policy(struct vm_area_struct *vma, struct mempolicy *pol)
static int mbind_range(struct mm_struct *mm, unsigned long start, unsigned long end, struct mempolicy *new_pol)
static long do_set_mempolicy(unsigned short mode, unsigned short flags, nodemask_t *nodes)
static void get_policy_nodemask(struct mempolicy *p, nodemask_t *nodes)
static int lookup_node(struct mm_struct *mm, unsigned long addr)
static long do_get_mempolicy(int *policy, nodemask_t *nmask, unsigned long addr, unsigned long flags)
static void migrate_page_add(struct page *page, struct list_head *pagelist, unsigned long flags)
struct page *alloc_new_node_page(struct page *page, unsigned long node)
static int migrate_to_node(struct mm_struct *mm, int source, int dest, int flags)
int do_migrate_pages(struct mm_struct *mm, const nodemask_t *from, const nodemask_t *to, int flags)
static struct page *new_page(struct page *page, unsigned long start)
static void migrate_page_add(struct page *page, struct list_head *pagelist, unsigned long flags)
int do_migrate_pages(struct mm_struct *mm, const nodemask_t *from, const nodemask_t *to, int flags)
static struct page *new_page(struct page *page, unsigned long start)
static long do_mbind(unsigned long start, unsigned long len, unsigned short mode, unsigned short mode_flags, nodemask_t *nmask, unsigned long flags)
static int get_nodes(nodemask_t *nodes, const unsigned long __user *nmask, unsigned long maxnode)
static int copy_nodes_to_user(unsigned long __user *mask, unsigned long maxnode, nodemask_t *nodes)
static long kernel_mbind(unsigned long start, unsigned long len, unsigned long mode, const unsigned long __user *nmask, unsigned long maxnode, unsigned int flags)
SYSCALL_DEFINE6(mbind, unsigned long, start, unsigned long, len, unsigned long, mode, const unsigned long __user *, nmask, unsigned long, maxnode, unsigned int, flags)
static long kernel_set_mempolicy(int mode, const unsigned long __user *nmask, unsigned long maxnode)
SYSCALL_DEFINE3(set_mempolicy, int, mode, const unsigned long __user *, nmask, unsigned long, maxnode)
static int kernel_migrate_pages(pid_t pid, unsigned long maxnode, const unsigned long __user *old_nodes, const unsigned long __user *new_nodes)
SYSCALL_DEFINE4(migrate_pages, pid_t, pid, unsigned long, maxnode, const unsigned long __user *, old_nodes, const unsigned long __user *, new_nodes)
static int kernel_get_mempolicy(int __user *policy, unsigned long __user *nmask, unsigned long maxnode, unsigned long addr, unsigned long flags)
SYSCALL_DEFINE5(get_mempolicy, int __user *, policy, unsigned long __user *, nmask, unsigned long, maxnode, unsigned long, addr, unsigned long, flags)
COMPAT_SYSCALL_DEFINE5(get_mempolicy, int __user *, policy, compat_ulong_t __user *, nmask, compat_ulong_t, maxnode, compat_ulong_t, addr, compat_ulong_t, flags)
COMPAT_SYSCALL_DEFINE3(set_mempolicy, int, mode, compat_ulong_t __user *, nmask, compat_ulong_t, maxnode)
COMPAT_SYSCALL_DEFINE6(mbind, compat_ulong_t, start, compat_ulong_t, len, compat_ulong_t, mode, compat_ulong_t __user *, nmask, compat_ulong_t, maxnode, compat_ulong_t, flags)
COMPAT_SYSCALL_DEFINE4(migrate_pages, compat_pid_t, pid, compat_ulong_t, maxnode, const compat_ulong_t __user *, old_nodes, const compat_ulong_t __user *, new_nodes)
struct mempolicy *__get_vma_policy(struct vm_area_struct *vma, unsigned long addr)
static struct mempolicy *get_vma_policy(struct vm_area_struct *vma, unsigned long addr)
bool vma_policy_mof(struct vm_area_struct *vma)
static int apply_policy_zone(struct mempolicy *policy, enum zone_type zone)
static nodemask_t *policy_nodemask(gfp_t gfp, struct mempolicy *policy)
static int policy_node(gfp_t gfp, struct mempolicy *policy, int nd)
static unsigned interleave_nodes(struct mempolicy *policy)
unsigned int mempolicy_slab_node(void)
static unsigned offset_il_node(struct mempolicy *pol, unsigned long n)
static inline unsigned interleave_nid(struct mempolicy *pol, struct vm_area_struct *vma, unsigned long addr, int shift)
int huge_node(struct vm_area_struct *vma, unsigned long addr, gfp_t gfp_flags, struct mempolicy **mpol, nodemask_t **nodemask)
bool init_nodemask_of_mempolicy(nodemask_t *mask)
bool mempolicy_nodemask_intersects(struct task_struct *tsk, const nodemask_t *mask)
static struct page *alloc_page_interleave(gfp_t gfp, unsigned order, unsigned nid)
struct page * alloc_pages_vma(gfp_t gfp, int order, struct vm_area_struct *vma, unsigned long addr, int node, bool hugepage)
struct page *alloc_pages_current(gfp_t gfp, unsigned order)
int vma_dup_policy(struct vm_area_struct *src, struct vm_area_struct *dst)
struct mempolicy *__mpol_dup(struct mempolicy *old)
bool __mpol_equal(struct mempolicy *a, struct mempolicy *b)
static struct sp_node * sp_lookup(struct shared_policy *sp, unsigned long start, unsigned long end)
static void sp_insert(struct shared_policy *sp, struct sp_node *new)
struct mempolicy * mpol_shared_policy_lookup(struct shared_policy *sp, unsigned long idx)
static void sp_free(struct sp_node *n)
int mpol_misplaced(struct page *page, struct vm_area_struct *vma, unsigned long addr)
void mpol_put_task_policy(struct task_struct *task)
static void sp_delete(struct shared_policy *sp, struct sp_node *n)
static void sp_node_init(struct sp_node *node, unsigned long start, unsigned long end, struct mempolicy *pol)
static struct sp_node *sp_alloc(unsigned long start, unsigned long end, struct mempolicy *pol)
static int shared_policy_replace(struct shared_policy *sp, unsigned long start, unsigned long end, struct sp_node *new)
void mpol_shared_policy_init(struct shared_policy *sp, struct mempolicy *mpol)
int mpol_set_shared_policy(struct shared_policy *info, struct vm_area_struct *vma, struct mempolicy *npol)
void mpol_free_shared_policy(struct shared_policy *p)
static void __init check_numabalancing_enable(void)
static int __init setup_numabalancing(char *str)
return ret; } __setup("numa_balancing=", setup_numabalancing)
; static inline void __init check_numabalancing_enable(void)
void __init numa_policy_init(void)
void numa_default_policy(void)
static const char * const policy_modes[] =int mpol_parse_str(char *str, struct mempolicy **mpol)
void mpol_to_str(char *buffer, int maxlen, struct mempolicy *pol)
\n
     14 unsigned long addr
     14 struct mempolicy *pol
     12 unsigned long end
     11 unsigned long start
     11 struct vm_area_struct *vma
     10 compat_ulong_t
      9 unsigned long
      8 maxnode
      7 struct page *page
      7 struct mm_struct *mm
      7 const nodemask_t *nodes
      6 unsigned long maxnode
      6 unsigned long flags
      6 struct shared_policy *sp
      6 nodemask_t *nodes
      6 nmask
      5 void
      5 gfp_t gfp
      4 struct mm_walk *walk
      4 struct mempolicy *policy
      4 mode
      4 flags
      4 const unsigned long __user *
      3 unsigned short mode
      3 struct list_head *pagelist
      3 int flags
      3 const unsigned long __user *nmask
      3 compat_ulong_t __user *
      2 unsigned short flags
      2 unsigned order
      2 unsigned long len
      2 struct task_struct *tsk
      2 struct sp_node *new
      2 struct sp_node *n
      2 struct mempolicy *p
      2 struct mempolicy **mpol
      2 start
      2 set_mempolicy
      2 policy
      2 pmd_t *pmd
      2 pid
      2 old_nodes
      2 nodemask_t *nmask
      2 new_nodes
      2 migrate_pages
      2 mbind
      2 len
      2 int __user *
      2 int
      2 get_mempolicy
      2 const nodemask_t *to
      2 const nodemask_t *from
      2 const compat_ulong_t __user *
      2 char *str
      2 addr
      1 unsigned short mode_flags
      1 unsigned nid
      1 unsigned long __user *nmask
      1 unsigned long __user *mask
      1 unsigned long __user *
      1 unsigned long node
      1 unsigned long n
      1 unsigned long mode
      1 unsigned long idx
      1 unsigned long hmask
      1 unsigned int flags
      1 unsigned int
      1 struct vm_area_struct *src
      1 struct vm_area_struct *dst
      1 struct task_struct *task
      1 struct task_struct *p
      1 struct sp_node *node
      1 struct shared_policy *p
      1 struct shared_policy *info
      1 struct queue_pages *qp
      1 struct nodemask_scratch *nsc
      1 struct mempolicy *old
      1 struct mempolicy *npol
      1 struct mempolicy *new_pol
      1 struct mempolicy *mpol
      1 struct mempolicy *b
      1 struct mempolicy *a
      1 spinlock_t *ptl
      1 setup_numabalancing
      1 pte_t *pte
      1 pid_t pid
      1 pid_t
      1 "numa_balancing="
      1 nodemask_t *ret
      1 nodemask_t **nodemask
      1 nodemask_t *new
      1 nodemask_t *mask
      1 int __user *policy
      1 int source
      1 int shift
      1 int *policy
      1 int order
      1 int node
      1 int nd
      1 int mode
      1 int maxlen
      1 int dest
      1 gfp_t gfp_flags
      1 enum zone_type zone
      1 const unsigned long __user *old_nodes
      1 const unsigned long __user *new_nodes
      1 const struct mempolicy *pol
      1 const nodemask_t *rel
      1 const nodemask_t *orig
      1 const nodemask_t *newmask
      1 const nodemask_t *new
      1 const nodemask_t *mask
      1 compat_pid_t
      1 char *buffer
      1 bool hugepage
