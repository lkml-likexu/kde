
EXPORT_SYMBOL_GPL(xen_privcmd_fops);
\n
static long privcmd_ioctl_hypercall(struct file *file, void __user *udata)
static void free_page_list(struct list_head *pages)
static int gather_array(struct list_head *pagelist, unsigned nelem, size_t size, const void __user *data)
static int traverse_pages(unsigned nelem, size_t size, struct list_head *pos, int (*fn)
(void *data, void *state)
, void *state)
static int traverse_pages_block(unsigned nelem, size_t size, struct list_head *pos, int (*fn)
(void *data, int nr, void *state)
, void *state)
static int mmap_gfn_range(void *data, void *state)
static long privcmd_ioctl_mmap(struct file *file, void __user *udata)
static int mmap_batch_fn(void *data, int nr, void *state)
static int mmap_return_error(int err, struct mmap_batch_state *st)
static int mmap_return_errors(void *data, int nr, void *state)
static int alloc_empty_pages(struct vm_area_struct *vma, int numpgs)
static long privcmd_ioctl_mmap_batch(struct file *file, void __user *udata, int version)
static int lock_pages(struct privcmd_dm_op_buf kbufs[], unsigned int num, struct page *pages[], unsigned int nr_pages)
static void unlock_pages(struct page *pages[], unsigned int nr_pages)
static long privcmd_ioctl_dm_op(struct file *file, void __user *udata)
static long privcmd_ioctl_restrict(struct file *file, void __user *udata)
static int remap_pfn_fn(pte_t *ptep, pgtable_t token, unsigned long addr, void *data)
static long privcmd_ioctl_mmap_resource(struct file *file, void __user *udata)
static long privcmd_ioctl(struct file *file, unsigned int cmd, unsigned long data)
static int privcmd_open(struct inode *ino, struct file *file)
static int privcmd_release(struct inode *ino, struct file *file)
static void privcmd_close(struct vm_area_struct *vma)
static vm_fault_t privcmd_fault(struct vm_fault *vmf)
static int privcmd_mmap(struct file *file, struct vm_area_struct *vma)
static int is_mapped_fn(pte_t *pte, struct page *pmd_page, unsigned long addr, void *data)
static int privcmd_vma_range_is_mapped( struct vm_area_struct *vma, unsigned long addr, unsigned long nr_pages)
static int __init privcmd_init(void)
static void __exit privcmd_exit(void)
\n
     10 struct file *file
      7 void *data
      6 void __user *udata
      5 void *state
      4 struct vm_area_struct *vma
      3 unsigned nelem
      3 unsigned long addr
      3 size_t size
      3 int nr
      2 void
      2 unsigned int nr_pages
      2 struct page *pages[]
      2 struct list_head *pos
      2 struct inode *ino
      2 int *fn
      1 xen_privcmd_fops
      1 unsigned long nr_pages
      1 unsigned long data
      1 unsigned int num
      1 unsigned int cmd
      1 struct vm_fault *vmf
      1 struct privcmd_dm_op_buf kbufs[]
      1 struct page *pmd_page
      1 struct mmap_batch_state *st
      1 struct list_head *pages
      1 struct list_head *pagelist
      1 pte_t *ptep
      1 pte_t *pte
      1 pgtable_t token
      1 int version
      1 int numpgs
      1 int err
      1 const void __user *data
