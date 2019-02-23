
EXPORT_SYMBOL_GPL(find_extend_vma);
\n
static inline pgprot_t arch_filter_pgprot(pgprot_t prot)
pgprot_t vm_get_page_prot(unsigned long vm_flags)
static pgprot_t vm_pgprot_modify(pgprot_t oldprot, unsigned long vm_flags)
void vma_set_page_prot(struct vm_area_struct *vma)
static void __remove_shared_vm_struct(struct vm_area_struct *vma, struct file *file, struct address_space *mapping)
void unlink_file_vma(struct vm_area_struct *vma)
static struct vm_area_struct *remove_vma(struct vm_area_struct *vma)
static int do_brk_flags(unsigned long addr, unsigned long request, unsigned long flags, struct list_head *uf)
; SYSCALL_DEFINE1(brk, unsigned long, brk)
static long vma_compute_subtree_gap(struct vm_area_struct *vma)
static int browse_rb(struct mm_struct *mm)
static void validate_mm_rb(struct rb_root *root, struct vm_area_struct *ignore)
static void validate_mm(struct mm_struct *mm)
static void vma_gap_update(struct vm_area_struct *vma)
static inline void vma_rb_insert(struct vm_area_struct *vma, struct rb_root *root)
static void __vma_rb_erase(struct vm_area_struct *vma, struct rb_root *root)
static __always_inline void vma_rb_erase_ignore(struct vm_area_struct *vma, struct rb_root *root, struct vm_area_struct *ignore)
static __always_inline void vma_rb_erase(struct vm_area_struct *vma, struct rb_root *root)
static inline void anon_vma_interval_tree_pre_update_vma(struct vm_area_struct *vma)
static inline void anon_vma_interval_tree_post_update_vma(struct vm_area_struct *vma)
static int find_vma_links(struct mm_struct *mm, unsigned long addr, unsigned long end, struct vm_area_struct **pprev, struct rb_node ***rb_link, struct rb_node **rb_parent)
static unsigned long count_vma_pages_range(struct mm_struct *mm, unsigned long addr, unsigned long end)
void __vma_link_rb(struct mm_struct *mm, struct vm_area_struct *vma, struct rb_node **rb_link, struct rb_node *rb_parent)
static void __vma_link_file(struct vm_area_struct *vma)
static void __vma_link(struct mm_struct *mm, struct vm_area_struct *vma, struct vm_area_struct *prev, struct rb_node **rb_link, struct rb_node *rb_parent)
static void vma_link(struct mm_struct *mm, struct vm_area_struct *vma, struct vm_area_struct *prev, struct rb_node **rb_link, struct rb_node *rb_parent)
static void __insert_vm_struct(struct mm_struct *mm, struct vm_area_struct *vma)
static __always_inline void __vma_unlink_common(struct mm_struct *mm, struct vm_area_struct *vma, struct vm_area_struct *prev, bool has_prev, struct vm_area_struct *ignore)
static inline void __vma_unlink_prev(struct mm_struct *mm, struct vm_area_struct *vma, struct vm_area_struct *prev)
int __vma_adjust(struct vm_area_struct *vma, unsigned long start, unsigned long end, pgoff_t pgoff, struct vm_area_struct *insert, struct vm_area_struct *expand)
static inline int is_mergeable_vma(struct vm_area_struct *vma, struct file *file, unsigned long vm_flags, struct vm_userfaultfd_ctx vm_userfaultfd_ctx)
static inline int is_mergeable_anon_vma(struct anon_vma *anon_vma1, struct anon_vma *anon_vma2, struct vm_area_struct *vma)
static int can_vma_merge_before(struct vm_area_struct *vma, unsigned long vm_flags, struct anon_vma *anon_vma, struct file *file, pgoff_t vm_pgoff, struct vm_userfaultfd_ctx vm_userfaultfd_ctx)
static int can_vma_merge_after(struct vm_area_struct *vma, unsigned long vm_flags, struct anon_vma *anon_vma, struct file *file, pgoff_t vm_pgoff, struct vm_userfaultfd_ctx vm_userfaultfd_ctx)
struct vm_area_struct *vma_merge(struct mm_struct *mm, struct vm_area_struct *prev, unsigned long addr, unsigned long end, unsigned long vm_flags, struct anon_vma *anon_vma, struct file *file, pgoff_t pgoff, struct mempolicy *policy, struct vm_userfaultfd_ctx vm_userfaultfd_ctx)
static int anon_vma_compatible(struct vm_area_struct *a, struct vm_area_struct *b)
static struct anon_vma *reusable_anon_vma(struct vm_area_struct *old, struct vm_area_struct *a, struct vm_area_struct *b)
struct anon_vma *find_mergeable_anon_vma(struct vm_area_struct *vma)
static inline unsigned long round_hint_to_min(unsigned long hint)
static inline int mlock_future_check(struct mm_struct *mm, unsigned long flags, unsigned long len)
static inline u64 file_mmap_size_max(struct file *file, struct inode *inode)
static inline bool file_mmap_ok(struct file *file, struct inode *inode, unsigned long pgoff, unsigned long len)
unsigned long do_mmap(struct file *file, unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, vm_flags_t vm_flags, unsigned long pgoff, unsigned long *populate, struct list_head *uf)
unsigned long ksys_mmap_pgoff(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long pgoff)
SYSCALL_DEFINE6(mmap_pgoff, unsigned long, addr, unsigned long, len, unsigned long, prot, unsigned long, flags, unsigned long, fd, unsigned long, pgoff)
SYSCALL_DEFINE1(old_mmap, struct mmap_arg_struct __user *, arg)
int vma_wants_writenotify(struct vm_area_struct *vma, pgprot_t vm_page_prot)
static inline int accountable_mapping(struct file *file, vm_flags_t vm_flags)
unsigned long mmap_region(struct file *file, unsigned long addr, unsigned long len, vm_flags_t vm_flags, unsigned long pgoff, struct list_head *uf)
unsigned long unmapped_area(struct vm_unmapped_area_info *info)
unsigned long unmapped_area_topdown(struct vm_unmapped_area_info *info)
unsigned long arch_get_unmapped_area(struct file *filp, unsigned long addr, unsigned long len, unsigned long pgoff, unsigned long flags)
unsigned long arch_get_unmapped_area_topdown(struct file *filp, const unsigned long addr0, const unsigned long len, const unsigned long pgoff, const unsigned long flags)
unsigned long get_unmapped_area(struct file *file, unsigned long addr, unsigned long len, unsigned long pgoff, unsigned long flags)
struct vm_area_struct *find_vma(struct mm_struct *mm, unsigned long addr)
struct vm_area_struct * find_vma_prev(struct mm_struct *mm, unsigned long addr, struct vm_area_struct **pprev)
static int acct_stack_growth(struct vm_area_struct *vma, unsigned long size, unsigned long grow)
int expand_upwards(struct vm_area_struct *vma, unsigned long address)
int expand_downwards(struct vm_area_struct *vma, unsigned long address)
static int __init cmdline_parse_stack_guard_gap(char *p)
int expand_stack(struct vm_area_struct *vma, unsigned long address)
struct vm_area_struct * find_extend_vma(struct mm_struct *mm, unsigned long addr)
addr &= PAGE_MASK;vma = find_vma_prev(mm, addr, &prev)
;if (vma && (vma->vm_start <= addr)
)
return vma;if (!prev || expand_stack(prev, addr)
)
return NULL;if (prev->vm_flags & VM_LOCKED)
populate_vma_page_range(prev, addr, prev->vm_end, NULL)
;return prev; } int expand_stack(struct vm_area_struct *vma, unsigned long address)
struct vm_area_struct * find_extend_vma(struct mm_struct *mm, unsigned long addr)
static void remove_vma_list(struct mm_struct *mm, struct vm_area_struct *vma)
static void unmap_region(struct mm_struct *mm, struct vm_area_struct *vma, struct vm_area_struct *prev, unsigned long start, unsigned long end)
static void detach_vmas_to_be_unmapped(struct mm_struct *mm, struct vm_area_struct *vma, struct vm_area_struct *prev, unsigned long end)
int __split_vma(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long addr, int new_below)
int split_vma(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long addr, int new_below)
int __do_munmap(struct mm_struct *mm, unsigned long start, size_t len, struct list_head *uf, bool downgrade)
int do_munmap(struct mm_struct *mm, unsigned long start, size_t len, struct list_head *uf)
static int __vm_munmap(unsigned long start, size_t len, bool downgrade)
int vm_munmap(unsigned long start, size_t len)
SYSCALL_DEFINE2(munmap, unsigned long, addr, size_t, len)
SYSCALL_DEFINE5(remap_file_pages, unsigned long, start, unsigned long, size, unsigned long, prot, unsigned long, pgoff, unsigned long, flags)
static int do_brk_flags(unsigned long addr, unsigned long len, unsigned long flags, struct list_head *uf)
int vm_brk_flags(unsigned long addr, unsigned long request, unsigned long flags)
int vm_brk(unsigned long addr, unsigned long len)
void exit_mmap(struct mm_struct *mm)
int insert_vm_struct(struct mm_struct *mm, struct vm_area_struct *vma)
struct vm_area_struct *copy_vma(struct vm_area_struct **vmap, unsigned long addr, unsigned long len, pgoff_t pgoff, bool *need_rmap_locks)
bool may_expand_vm(struct mm_struct *mm, vm_flags_t flags, unsigned long npages)
void vm_stat_account(struct mm_struct *mm, vm_flags_t flags, long npages)
static void special_mapping_close(struct vm_area_struct *vma)
static const char *special_mapping_name(struct vm_area_struct *vma)
static int special_mapping_mremap(struct vm_area_struct *new_vma)
static vm_fault_t special_mapping_fault(struct vm_fault *vmf)
static struct vm_area_struct *__install_special_mapping(struct mm_struct *mm, unsigned long addr, unsigned long len, unsigned long vm_flags, void *priv, const struct vm_operations_struct *ops)
bool vma_is_special_mapping(const struct vm_area_struct *vma, const struct vm_special_mapping *sm)
struct vm_area_struct *_install_special_mapping(struct mm_struct *mm, unsigned long addr, unsigned long len, unsigned long vm_flags, const struct vm_special_mapping *spec)
int install_special_mapping(struct mm_struct *mm, unsigned long addr, unsigned long len, unsigned long vm_flags, struct page **pages)
static void vm_lock_anon_vma(struct mm_struct *mm, struct anon_vma *anon_vma)
static void vm_lock_mapping(struct mm_struct *mm, struct address_space *mapping)
int mm_take_all_locks(struct mm_struct *mm)
static void vm_unlock_anon_vma(struct anon_vma *anon_vma)
static void vm_unlock_mapping(struct address_space *mapping)
void mm_drop_all_locks(struct mm_struct *mm)
void __init mmap_init(void)
static int init_user_reserve(void)
static int init_admin_reserve(void)
static int reserve_mem_notifier(struct notifier_block *nb, unsigned long action, void *data)
static int __meminit init_reserve_notifier(void)
\n
     39 struct vm_area_struct *vma
     34 struct mm_struct *mm
     22 unsigned long addr
     13 unsigned long len
     13 unsigned long
     11 struct file *file
      9 unsigned long vm_flags
      8 unsigned long flags
      7 struct vm_area_struct *prev
      6 unsigned long start
      6 unsigned long pgoff
      6 unsigned long end
      6 struct list_head *uf
      5 struct rb_root *root
      5 struct anon_vma *anon_vma
      5 addr
      4 void
      4 unsigned long address
      4 struct vm_userfaultfd_ctx vm_userfaultfd_ctx
      4 size_t len
      3 vm_flags_t vm_flags
      3 struct vm_area_struct *ignore
      3 struct rb_node *rb_parent
      3 struct rb_node **rb_link
      3 struct address_space *mapping
      3 pgoff_t pgoff
      2 vm_flags_t flags
      2 unsigned long request
      2 unsigned long prot
      2 struct vm_unmapped_area_info *info
      2 struct vm_area_struct **pprev
      2 struct vm_area_struct *b
      2 struct vm_area_struct *a
      2 struct inode *inode
      2 struct file *filp
      2 prot
      2 pgoff_t vm_pgoff
      2 pgoff
      2 len
      2 int new_below
      2 flags
      2 brk
      2 bool downgrade
      1 void *priv
      1 void *data
      1 vma && vma->vm_start <= addr
      1 unsigned long size
      1 unsigned long *populate
      1 unsigned long npages
      1 unsigned long hint
      1 unsigned long grow
      1 unsigned long fd
      1 unsigned long action
      1 struct vm_fault *vmf
      1 struct vm_area_struct **vmap
      1 struct vm_area_struct *old
      1 struct vm_area_struct *new_vma
      1 struct vm_area_struct *insert
      1 struct vm_area_struct *expand
      1 struct rb_node **rb_parent
      1 struct rb_node ***rb_link
      1 struct page **pages
      1 struct notifier_block *nb
      1 struct mmap_arg_struct __user *
      1 struct mempolicy *policy
      1 struct anon_vma *anon_vma2
      1 struct anon_vma *anon_vma1
      1 start
      1 size_t
      1 size
      1 remap_file_pages
      1 prev->vm_flags & VM_LOCKED
      1 prev->vm_end
      1 !prev || expand_stackprev
      1 &prev
      1 prev
      1 pgprot_t vm_page_prot
      1 pgprot_t prot
      1 pgprot_t oldprot
      1 old_mmap
      1 NULL
      1 munmap
      1 mmap_pgoff
      1 mm
      1 long npages
      1 find_extend_vma
      1 fd
      1 const unsigned long pgoff
      1 const unsigned long len
      1 const unsigned long flags
      1 const unsigned long addr0
      1 const struct vm_special_mapping *spec
      1 const struct vm_special_mapping *sm
      1 const struct vm_operations_struct *ops
      1 const struct vm_area_struct *vma
      1 char *p
      1 bool *need_rmap_locks
      1 bool has_prev
      1 arg
