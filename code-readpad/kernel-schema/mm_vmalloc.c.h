
EXPORT_SYMBOL_GPL(register_vmap_purge_notifier);
EXPORT_SYMBOL_GPL(unregister_vmap_purge_notifier);
EXPORT_SYMBOL_GPL(vm_unmap_aliases);
EXPORT_SYMBOL_GPL(unmap_kernel_range_noflush);
EXPORT_SYMBOL_GPL(unmap_kernel_range);
EXPORT_SYMBOL_GPL(map_vm_area);
EXPORT_SYMBOL_GPL(__get_vm_area);
EXPORT_SYMBOL_GPL(alloc_vm_area);
EXPORT_SYMBOL_GPL(free_vm_area);
\n
static void free_work(struct work_struct *w)
static void vunmap_pte_range(pmd_t *pmd, unsigned long addr, unsigned long end)
static void vunmap_pmd_range(pud_t *pud, unsigned long addr, unsigned long end)
static void vunmap_pud_range(p4d_t *p4d, unsigned long addr, unsigned long end)
static void vunmap_p4d_range(pgd_t *pgd, unsigned long addr, unsigned long end)
static void vunmap_page_range(unsigned long addr, unsigned long end)
static int vmap_pte_range(pmd_t *pmd, unsigned long addr, unsigned long end, pgprot_t prot, struct page **pages, int *nr)
static int vmap_pmd_range(pud_t *pud, unsigned long addr, unsigned long end, pgprot_t prot, struct page **pages, int *nr)
static int vmap_pud_range(p4d_t *p4d, unsigned long addr, unsigned long end, pgprot_t prot, struct page **pages, int *nr)
static int vmap_p4d_range(pgd_t *pgd, unsigned long addr, unsigned long end, pgprot_t prot, struct page **pages, int *nr)
static int vmap_page_range_noflush(unsigned long start, unsigned long end, pgprot_t prot, struct page **pages)
static int vmap_page_range(unsigned long start, unsigned long end, pgprot_t prot, struct page **pages)
int is_vmalloc_or_module_addr(const void *x)
struct page *vmalloc_to_page(const void *vmalloc_addr)
unsigned long vmalloc_to_pfn(const void *vmalloc_addr)
static struct vmap_area *__find_vmap_area(unsigned long addr)
static void __insert_vmap_area(struct vmap_area *va)
static struct vmap_area *alloc_vmap_area(unsigned long size, unsigned long align, unsigned long vstart, unsigned long vend, int node, gfp_t gfp_mask)
int register_vmap_purge_notifier(struct notifier_block *nb)
int unregister_vmap_purge_notifier(struct notifier_block *nb)
static void __free_vmap_area(struct vmap_area *va)
static void free_vmap_area(struct vmap_area *va)
static void unmap_vmap_area(struct vmap_area *va)
static unsigned long lazy_max_pages(void)
void set_iounmap_nonlazy(void)
static bool __purge_vmap_area_lazy(unsigned long start, unsigned long end)
static void try_purge_vmap_area_lazy(void)
static void purge_vmap_area_lazy(void)
static void free_vmap_area_noflush(struct vmap_area *va)
static void free_unmap_vmap_area(struct vmap_area *va)
static struct vmap_area *find_vmap_area(unsigned long addr)
static unsigned long addr_to_vb_idx(unsigned long addr)
static void *vmap_block_vaddr(unsigned long va_start, unsigned long pages_off)
static void *new_vmap_block(unsigned int order, gfp_t gfp_mask)
static void free_vmap_block(struct vmap_block *vb)
static void purge_fragmented_blocks(int cpu)
static void purge_fragmented_blocks_allcpus(void)
static void *vb_alloc(unsigned long size, gfp_t gfp_mask)
static void vb_free(const void *addr, unsigned long size)
void vm_unmap_aliases(void)
void vm_unmap_ram(const void *mem, unsigned int count)
void *vm_map_ram(struct page **pages, unsigned int count, int node, pgprot_t prot)
static struct vm_struct *vmlist __initdata;void __init vm_area_add_early(struct vm_struct *vm)
void __init vm_area_register_early(struct vm_struct *vm, size_t align)
void __init vmalloc_init(void)
int map_kernel_range_noflush(unsigned long addr, unsigned long size, pgprot_t prot, struct page **pages)
void unmap_kernel_range_noflush(unsigned long addr, unsigned long size)
void unmap_kernel_range(unsigned long addr, unsigned long size)
int map_vm_area(struct vm_struct *area, pgprot_t prot, struct page **pages)
static void setup_vmalloc_vm(struct vm_struct *vm, struct vmap_area *va, unsigned long flags, const void *caller)
static void clear_vm_uninitialized_flag(struct vm_struct *vm)
static struct vm_struct *__get_vm_area_node(unsigned long size, unsigned long align, unsigned long flags, unsigned long start, unsigned long end, int node, gfp_t gfp_mask, const void *caller)
struct vm_struct *__get_vm_area(unsigned long size, unsigned long flags, unsigned long start, unsigned long end)
struct vm_struct *__get_vm_area_caller(unsigned long size, unsigned long flags, unsigned long start, unsigned long end, const void *caller)
struct vm_struct *get_vm_area(unsigned long size, unsigned long flags)
struct vm_struct *get_vm_area_caller(unsigned long size, unsigned long flags, const void *caller)
struct vm_struct *find_vm_area(const void *addr)
struct vm_struct *remove_vm_area(const void *addr)
static void __vunmap(const void *addr, int deallocate_pages)
static inline void __vfree_deferred(const void *addr)
void vfree_atomic(const void *addr)
void vfree(const void *addr)
void vunmap(const void *addr)
void *vmap(struct page **pages, unsigned int count, unsigned long flags, pgprot_t prot)
static void *__vmalloc_node(unsigned long size, unsigned long align, gfp_t gfp_mask, pgprot_t prot, int node, const void *caller)
; static void *__vmalloc_area_node(struct vm_struct *area, gfp_t gfp_mask, pgprot_t prot, int node)
void *__vmalloc_node_range(unsigned long size, unsigned long align, unsigned long start, unsigned long end, gfp_t gfp_mask, pgprot_t prot, unsigned long vm_flags, int node, const void *caller)
static void *__vmalloc_node(unsigned long size, unsigned long align, gfp_t gfp_mask, pgprot_t prot, int node, const void *caller)
void *__vmalloc(unsigned long size, gfp_t gfp_mask, pgprot_t prot)
static inline void *__vmalloc_node_flags(unsigned long size, int node, gfp_t flags)
void *__vmalloc_node_flags_caller(unsigned long size, int node, gfp_t flags, void *caller)
void *vmalloc(unsigned long size)
void *vzalloc(unsigned long size)
void *vmalloc_user(unsigned long size)
void *vmalloc_node(unsigned long size, int node)
void *vzalloc_node(unsigned long size, int node)
void *vmalloc_exec(unsigned long size)
void *vmalloc_32(unsigned long size)
void *vmalloc_32_user(unsigned long size)
static int aligned_vread(char *buf, char *addr, unsigned long count)
static int aligned_vwrite(char *buf, char *addr, unsigned long count)
long vread(char *buf, char *addr, unsigned long count)
long vwrite(char *buf, char *addr, unsigned long count)
int remap_vmalloc_range_partial(struct vm_area_struct *vma, unsigned long uaddr, void *kaddr, unsigned long size)
int remap_vmalloc_range(struct vm_area_struct *vma, void *addr, unsigned long pgoff)
void __weak vmalloc_sync_all(void)
static int f(pte_t *pte, pgtable_t table, unsigned long addr, void *data)
struct vm_struct *alloc_vm_area(size_t size, pte_t **ptes)
void free_vm_area(struct vm_struct *area)
static struct vmap_area *node_to_va(struct rb_node *n)
static bool pvm_find_next_prev(unsigned long end, struct vmap_area **pnext, struct vmap_area **pprev)
static unsigned long pvm_determine_end(struct vmap_area **pnext, struct vmap_area **pprev, unsigned long align)
struct vm_struct **pcpu_get_vm_areas(const unsigned long *offsets, const size_t *sizes, int nr_vms, size_t align)
void pcpu_free_vm_areas(struct vm_struct **vms, int nr_vms)
static void *s_start(struct seq_file *m, loff_t *pos)
__acquires(&vmap_area_lock)
static void *s_next(struct seq_file *m, void *p, loff_t *pos)
static void s_stop(struct seq_file *m, void *p)
__releases(&vmap_area_lock)
static void show_numa_info(struct seq_file *m, struct vm_struct *v)
static int s_show(struct seq_file *m, void *p)
static int __init proc_vmalloc_init(void)
\n
     26 unsigned long size
     17 unsigned long end
     16 unsigned long addr
     15 pgprot_t prot
     11 int node
     10 struct page **pages
      9 void
      9 gfp_t gfp_mask
      8 const void *addr
      7 unsigned long start
      7 unsigned long flags
      7 struct vmap_area *va
      7 const void *caller
      6 unsigned long align
      5 struct seq_file *m
      4 unsigned long count
      4 struct vm_struct *vm
      4 int *nr
      4 char *buf
      4 char *addr
      3 void *p
      3 unsigned int count
      3 struct vm_struct *area
      2 &vmap_area_lock
      2 struct vm_area_struct *vma
      2 struct vmap_area **pprev
      2 struct vmap_area **pnext
      2 struct notifier_block *nb
      2 size_t align
      2 pud_t *pud
      2 pmd_t *pmd
      2 pgd_t *pgd
      2 p4d_t *p4d
      2 loff_t *pos
      2 int nr_vms
      2 gfp_t flags
      2 const void *vmalloc_addr
      1 void *kaddr
      1 void *data
      1 void *caller
      1 void *addr
      1 vm_unmap_aliases
      1 unsigned long vstart
      1 unsigned long vm_flags
      1 unsigned long vend
      1 unsigned long va_start
      1 unsigned long uaddr
      1 unsigned long pgoff
      1 unsigned long pages_off
      1 unsigned int order
      1 unregister_vmap_purge_notifier
      1 unmap_kernel_range_noflush
      1 unmap_kernel_range
      1 struct work_struct *w
      1 struct vm_struct **vms
      1 struct vm_struct *v
      1 struct vmap_block *vb
      1 struct rb_node *n
      1 size_t size
      1 register_vmap_purge_notifier
      1 pte_t **ptes
      1 pte_t *pte
      1 pgtable_t table
      1 map_vm_area
      1 int deallocate_pages
      1 int cpu
      1 __get_vm_area
      1 free_vm_area
      1 const void *x
      1 const void *mem
      1 const unsigned long *offsets
      1 const size_t *sizes
      1 alloc_vm_area
