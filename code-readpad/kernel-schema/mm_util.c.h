
EXPORT_SYMBOL_GPL(__get_user_pages_fast);
EXPORT_SYMBOL_GPL(get_user_pages_fast);
EXPORT_SYMBOL_GPL(__page_mapcount);
EXPORT_SYMBOL_GPL(vm_memory_committed);
\n
void kfree_const(const void *x)
char *kstrdup(const char *s, gfp_t gfp)
const char *kstrdup_const(const char *s, gfp_t gfp)
char *kstrndup(const char *s, size_t max, gfp_t gfp)
void *kmemdup(const void *src, size_t len, gfp_t gfp)
char *kmemdup_nul(const char *s, size_t len, gfp_t gfp)
void *memdup_user(const void __user *src, size_t len)
void *vmemdup_user(const void __user *src, size_t len)
char *strndup_user(const char __user *s, long n)
void *memdup_user_nul(const void __user *src, size_t len)
void __vma_link_list(struct mm_struct *mm, struct vm_area_struct *vma, struct vm_area_struct *prev, struct rb_node *rb_parent)
int vma_is_stack_for_current(struct vm_area_struct *vma)
void arch_pick_mmap_layout(struct mm_struct *mm, struct rlimit *rlim_stack)
int __weak __get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
int __weak get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
unsigned long vm_mmap_pgoff(struct file *file, unsigned long addr, unsigned long len, unsigned long prot, unsigned long flag, unsigned long pgoff)
unsigned long vm_mmap(struct file *file, unsigned long addr, unsigned long len, unsigned long prot, unsigned long flag, unsigned long offset)
void *kvmalloc_node(size_t size, gfp_t flags, int node)
void kvfree(const void *addr)
static inline void *__page_rmapping(struct page *page)
void *page_rmapping(struct page *page)
bool page_mapped(struct page *page)
struct anon_vma *page_anon_vma(struct page *page)
struct address_space *page_mapping(struct page *page)
struct address_space *page_mapping_file(struct page *page)
int __page_mapcount(struct page *page)
int overcommit_ratio_handler(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int overcommit_kbytes_handler(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
unsigned long vm_commit_limit(void)
unsigned long vm_memory_committed(void)
int __vm_enough_memory(struct mm_struct *mm, long pages, int cap_sys_admin)
int get_cmdline(struct task_struct *task, char *buffer, int buflen)
\n
      7 struct page *page
      5 size_t len
      5 gfp_t gfp
      4 int write
      4 const char *s
      3 struct mm_struct *mm
      3 const void __user *src
      2 void __user *buffer
      2 void
      2 unsigned long start
      2 unsigned long prot
      2 unsigned long len
      2 unsigned long flag
      2 unsigned long addr
      2 struct vm_area_struct *vma
      2 struct page **pages
      2 struct file *file
      2 struct ctl_table *table
      2 size_t *lenp
      2 loff_t *ppos
      2 int nr_pages
      1 vm_memory_committed
      1 unsigned long pgoff
      1 unsigned long offset
      1 struct vm_area_struct *prev
      1 struct task_struct *task
      1 struct rlimit *rlim_stack
      1 struct rb_node *rb_parent
      1 size_t size
      1 size_t max
      1 __page_mapcount
      1 long pages
      1 long n
      1 int node
      1 int cap_sys_admin
      1 int buflen
      1 gfp_t flags
      1 get_user_pages_fast
      1 __get_user_pages_fast
      1 const void *x
      1 const void *src
      1 const void *addr
      1 const char __user *s
      1 char *buffer
