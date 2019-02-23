
EXPORT_SYMBOL_GPL(pat_enabled);
EXPORT_SYMBOL_GPL(pat_pfn_immune_to_uc_mtrr);
EXPORT_SYMBOL_GPL(pgprot_writecombine);
EXPORT_SYMBOL_GPL(pgprot_writethrough);
\n
void pat_disable(const char *reason)
static int __init nopat(char *str)
bool pat_enabled(void)
static int __init pat_debug_setup(char *str)
static inline enum page_cache_mode get_page_memtype(struct page *pg)
static inline void set_page_memtype(struct page *pg, enum page_cache_mode memtype)
old_flags = pg->flags; new_flags = (old_flags & _PGMT_CLEAR_MASK)
| memtype_flags;} while (cmpxchg(&pg->flags, old_flags, new_flags)
!= old_flags)
; } static inline enum page_cache_mode get_page_memtype(struct page *pg)
old_flags = pg->flags; new_flags = (old_flags & _PGMT_CLEAR_MASK)
| memtype_flags;} while (cmpxchg(&pg->flags, old_flags, new_flags)
!= old_flags)
; } static inline enum page_cache_mode get_page_memtype(struct page *pg)
return -1; } static inline void set_page_memtype(struct page *pg, enum page_cache_mode memtype)
static enum page_cache_mode pat_get_cache_mode(unsigned pat_val, char *msg)
static void __init_cache_modes(u64 pat)
static void pat_bsp_init(u64 pat)
static void pat_ap_init(u64 pat)
void init_cache_modes(void)
void pat_init(void)
static unsigned long pat_x_mtrr_type(u64 start, u64 end, enum page_cache_mode req_type)
static int pagerange_is_ram_callback(unsigned long initial_pfn, unsigned long total_nr_pages, void *arg)
static int pat_pagerange_is_ram(resource_size_t start, resource_size_t end)
static int reserve_ram_pages_type(u64 start, u64 end, enum page_cache_mode req_type, enum page_cache_mode *new_type)
static int free_ram_pages_type(u64 start, u64 end)
static u64 sanitize_phys(u64 address)
int reserve_memtype(u64 start, u64 end, enum page_cache_mode req_type, enum page_cache_mode *new_type)
int free_memtype(u64 start, u64 end)
static enum page_cache_mode lookup_memtype(u64 paddr)
bool pat_pfn_immune_to_uc_mtrr(unsigned long pfn)
int io_reserve_memtype(resource_size_t start, resource_size_t end, enum page_cache_mode *type)
void io_free_memtype(resource_size_t start, resource_size_t end)
int arch_io_reserve_memtype_wc(resource_size_t start, resource_size_t size)
void arch_io_free_memtype_wc(resource_size_t start, resource_size_t size)
pgprot_t phys_mem_access_prot(struct file *file, unsigned long pfn, unsigned long size, pgprot_t vma_prot)
static inline int range_is_allowed(unsigned long pfn, unsigned long size)
static inline int range_is_allowed(unsigned long pfn, unsigned long size)
return 1; }static inline int range_is_allowed(unsigned long pfn, unsigned long size)
int phys_mem_access_prot_allowed(struct file *file, unsigned long pfn, unsigned long size, pgprot_t *vma_prot)
int kernel_map_sync_memtype(u64 base, unsigned long size, enum page_cache_mode pcm)
static int reserve_pfn_range(u64 paddr, unsigned long size, pgprot_t *vma_prot, int strict_prot)
static void free_pfn_range(u64 paddr, unsigned long size)
int track_pfn_copy(struct vm_area_struct *vma)
int track_pfn_remap(struct vm_area_struct *vma, pgprot_t *prot, unsigned long pfn, unsigned long addr, unsigned long size)
void track_pfn_insert(struct vm_area_struct *vma, pgprot_t *prot, pfn_t pfn)
void untrack_pfn(struct vm_area_struct *vma, unsigned long pfn, unsigned long size)
void untrack_pfn_moved(struct vm_area_struct *vma)
pgprot_t pgprot_writecombine(pgprot_t prot)
pgprot_t pgprot_writethrough(pgprot_t prot)
static struct memtype *memtype_get_idx(loff_t pos)
static void *memtype_seq_start(struct seq_file *seq, loff_t *pos)
static void *memtype_seq_next(struct seq_file *seq, void *v, loff_t *pos)
static void memtype_seq_stop(struct seq_file *seq, void *v)
static int memtype_seq_show(struct seq_file *seq, void *v)
static int memtype_seq_open(struct inode *inode, struct file *file)
static int __init pat_memtype_list_init(void)
\n
     10 unsigned long size
      8 unsigned long pfn
      5 u64 start
      5 u64 end
      5 struct vm_area_struct *vma
      5 struct page *pg
      5 resource_size_t start
      4 void
      4 struct seq_file *seq
      3 void *v
      3 u64 pat
      3 u64 paddr
      3 struct file *file
      3 resource_size_t end
      3 enum page_cache_mode req_type
      2 resource_size_t size
      2 pgprot_t *vma_prot
      2 pgprot_t *prot
      2 pgprot_t prot
      2 old_flags & _PGMT_CLEAR_MASK
      2 old_flags
      2 new_flags
      2 loff_t *pos
      2 enum page_cache_mode *new_type
      2 enum page_cache_mode memtype
      2 cmpxchg&pg->flags
      2 char *str
      1 void *arg
      1 unsigned pat_val
      1 unsigned long total_nr_pages
      1 unsigned long initial_pfn
      1 unsigned long addr
      1 u64 base
      1 u64 address
      1 struct inode *inode
      1 pgprot_writethrough
      1 pgprot_writecombine
      1 pgprot_t vma_prot
      1 pfn_t pfn
      1 pat_pfn_immune_to_uc_mtrr
      1 pat_enabled
      1 loff_t pos
      1 int strict_prot
      1 enum page_cache_mode *type
      1 enum page_cache_mode pcm
      1 const char *reason
      1 char *msg
