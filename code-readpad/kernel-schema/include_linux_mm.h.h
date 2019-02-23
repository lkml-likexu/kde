
\n
static inline void set_max_mapnr(unsigned long limit)
extern atomic_long_t _totalram_pages; static inline unsigned long totalram_pages(void)
static inline void totalram_pages_inc(void)
static inline void totalram_pages_dec(void)
static inline void totalram_pages_add(long count)
static inline void totalram_pages_set(long val)
static inline void vma_init(struct vm_area_struct *vma, struct mm_struct *mm)
static inline void vma_set_anonymous(struct vm_area_struct *vma)
static inline int pmd_devmap(pmd_t pmd)
static inline int pmd_devmap(pmd_t pmd)
return 0; } static inline int pud_devmap(pud_t pud)
static inline int pmd_devmap(pmd_t pmd)
return 0; } static inline int pud_devmap(pud_t pud)
return 0; } static inline int pgd_devmap(pgd_t pgd)
static inline int put_page_testzero(struct page *page)
static inline int get_page_unless_zero(struct page *page)
static inline bool is_vmalloc_addr(const void *x)
return addr >= VMALLOC_START && addr < VMALLOC_END;return false;endif } extern int is_vmalloc_or_module_addr(const void *x)
; static inline int is_vmalloc_or_module_addr(const void *x)
extern void *kvmalloc_node(size_t size, gfp_t flags, int node)
; static inline void *kvmalloc(size_t size, gfp_t flags)
extern void *kvmalloc_node(size_t size, gfp_t flags, int node)
; static inline void *kvmalloc(size_t size, gfp_t flags)
return kvmalloc_node(size, flags, NUMA_NO_NODE)
; } static inline void *kvzalloc_node(size_t size, gfp_t flags, int node)
extern void *kvmalloc_node(size_t size, gfp_t flags, int node)
; static inline void *kvmalloc(size_t size, gfp_t flags)
return kvmalloc_node(size, flags, NUMA_NO_NODE)
; } static inline void *kvzalloc_node(size_t size, gfp_t flags, int node)
return kvmalloc_node(size, flags | __GFP_ZERO, node)
; } static inline void *kvzalloc(size_t size, gfp_t flags)
static inline void *kvmalloc_array(size_t n, size_t size, gfp_t flags)
static inline void *kvcalloc(size_t n, size_t size, gfp_t flags)
static inline atomic_t *compound_mapcount_ptr(struct page *page)
static inline int compound_mapcount(struct page *page)
static inline void page_mapcount_reset(struct page *page)
static inline int page_mapcount(struct page *page)
int total_mapcount(struct page *page)
; int page_trans_huge_mapcount(struct page *page, int *total_mapcount)
; static inline int total_mapcount(struct page *page)
int total_mapcount(struct page *page)
; int page_trans_huge_mapcount(struct page *page, int *total_mapcount)
; static inline int total_mapcount(struct page *page)
return page_mapcount(page)
; } static inline int page_trans_huge_mapcount(struct page *page, int *total_mapcount)
static inline struct page *virt_to_head_page(const void *x)
static inline void set_compound_page_dtor(struct page *page, enum compound_dtor_id compound_dtor)
static inline compound_page_dtor *get_compound_page_dtor(struct page *page)
static inline unsigned int compound_order(struct page *page)
static inline void set_compound_order(struct page *page, unsigned int order)
static inline pte_t maybe_mkwrite(pte_t pte, struct vm_area_struct *vma)
static inline enum zone_type page_zonenum(const struct page *page)
static inline bool is_zone_device_page(const struct page *page)
static inline bool is_zone_device_page(const struct page *page)
return page_zonenum(page)
== ZONE_DEVICE; } extern void memmap_init_zone_device(struct zone *, unsigned long, unsigned long, struct dev_pagemap *)
; static inline bool is_zone_device_page(const struct page *page)
void dev_pagemap_get_ops(void)
; void dev_pagemap_put_ops(void)
; void __put_devmap_managed_page(struct page *page)
; DECLARE_STATIC_KEY_FALSE(devmap_managed_key)
; static inline bool put_devmap_managed_page(struct page *page)
static inline bool is_device_private_page(const struct page *page)
static inline bool is_device_public_page(const struct page *page)
static inline bool is_pci_p2pdma_page(const struct page *page)
static inline bool is_pci_p2pdma_page(const struct page *page)
return is_zone_device_page(page)
&& page->pgmap->type == MEMORY_DEVICE_PCI_P2PDMA; } static inline bool is_pci_p2pdma_page(const struct page *page)
static inline void dev_pagemap_get_ops(void)
static inline void dev_pagemap_put_ops(void)
static inline bool put_devmap_managed_page(struct page *page)
static inline bool is_device_private_page(const struct page *page)
static inline bool is_device_public_page(const struct page *page)
static inline bool is_pci_p2pdma_page(const struct page *page)
static inline void get_page(struct page *page)
static inline void put_page(struct page *page)
static inline int page_zone_id(struct page *page)
extern int page_to_nid(const struct page *page)
; static inline int page_to_nid(const struct page *page)
static inline int cpu_pid_to_cpupid(int cpu, int pid)
static inline int cpupid_to_pid(int cpupid)
static inline int cpupid_to_cpu(int cpupid)
static inline int cpupid_to_nid(int cpupid)
static inline bool cpupid_pid_unset(int cpupid)
static inline bool cpupid_cpu_unset(int cpupid)
static inline bool __cpupid_match_pid(pid_t task_pid, int cpupid)
define cpupid_match_pid(task, cpupid)
__cpupid_match_pid(task->pid, cpupid)
static inline int page_cpupid_xchg_last(struct page *page, int cpupid)
static inline int page_cpupid_last(struct page *page)
static inline int page_cpupid_last(struct page *page)
return page->_last_cpupid; } static inline void page_cpupid_reset_last(struct page *page)
static inline int page_cpupid_last(struct page *page)
return page->_last_cpupid; } static inline void page_cpupid_reset_last(struct page *page)
page->_last_cpupid = -1 & LAST_CPUPID_MASK; } static inline int page_cpupid_last(struct page *page)
static inline void page_cpupid_reset_last(struct page *page)
static inline void page_cpupid_reset_last(struct page *page)
page->flags |= LAST_CPUPID_MASK << LAST_CPUPID_PGSHIFT; }endifstatic inline int page_cpupid_xchg_last(struct page *page, int cpupid)
static inline int page_cpupid_last(struct page *page)
static inline int cpupid_to_nid(int cpupid)
static inline int cpupid_to_pid(int cpupid)
static inline int cpupid_to_cpu(int cpupid)
static inline int cpu_pid_to_cpupid(int nid, int pid)
static inline bool cpupid_pid_unset(int cpupid)
static inline void page_cpupid_reset_last(struct page *page)
static inline bool cpupid_match_pid(struct task_struct *task, int cpupid)
static inline u8 page_kasan_tag(const struct page *page)
static inline void page_kasan_tag_set(struct page *page, u8 tag)
static inline void page_kasan_tag_reset(struct page *page)
static inline void page_kasan_tag_reset(struct page *page)
page_kasan_tag_set(page, 0xff)
; } static inline u8 page_kasan_tag(const struct page *page)
static inline struct zone *page_zone(const struct page *page)
static inline pg_data_t *page_pgdat(const struct page *page)
static inline void set_page_section(struct page *page, unsigned long section)
static inline unsigned long page_to_section(const struct page *page)
static inline void set_page_zone(struct page *page, enum zone_type zone)
static inline void set_page_node(struct page *page, unsigned long node)
static inline void set_page_links(struct page *page, enum zone_type zone, unsigned long node, unsigned long pfn)
static inline struct mem_cgroup *page_memcg(struct page *page)
static inline struct mem_cgroup *page_memcg(struct page *page)
return page->mem_cgroup; } static inline struct mem_cgroup *page_memcg_rcu(struct page *page)
static inline struct mem_cgroup *page_memcg(struct page *page)
return page->mem_cgroup; } static inline struct mem_cgroup *page_memcg_rcu(struct page *page)
WARN_ON_ONCE(!rcu_read_lock_held()
)
;return READ_ONCE(page->mem_cgroup)
; } static inline struct mem_cgroup *page_memcg(struct page *page)
static inline struct mem_cgroup *page_memcg(struct page *page)
return page->mem_cgroup; } static inline struct mem_cgroup *page_memcg_rcu(struct page *page)
WARN_ON_ONCE(!rcu_read_lock_held()
)
;return READ_ONCE(page->mem_cgroup)
; } static inline struct mem_cgroup *page_memcg(struct page *page)
return NULL; } static inline struct mem_cgroup *page_memcg_rcu(struct page *page)
static __always_inline void *lowmem_page_address(const struct page *page)
static inline void *page_address(const struct page *page)
static inline void *page_address(const struct page *page)
return page->virtual; } static inline void set_page_address(struct page *page, void *address)
static inline struct address_space *page_file_mapping(struct page *page)
static inline pgoff_t page_index(struct page *page)
static inline bool page_is_pfmemalloc(struct page *page)
static inline void set_page_pfmemalloc(struct page *page)
static inline void clear_page_pfmemalloc(struct page *page)
extern vm_fault_t handle_mm_fault(struct vm_area_struct *vma, unsigned long address, unsigned int flags)
; extern int fixup_user_fault(struct task_struct *tsk, struct mm_struct *mm, unsigned long address, unsigned int fault_flags, bool *unlocked)
; void unmap_mapping_pages(struct address_space *mapping, pgoff_t start, pgoff_t nr, bool even_cows)
; void unmap_mapping_range(struct address_space *mapping, loff_t const holebegin, loff_t const holelen, int even_cows)
; static inline vm_fault_t handle_mm_fault(struct vm_area_struct *vma, unsigned long address, unsigned int flags)
extern vm_fault_t handle_mm_fault(struct vm_area_struct *vma, unsigned long address, unsigned int flags)
; extern int fixup_user_fault(struct task_struct *tsk, struct mm_struct *mm, unsigned long address, unsigned int fault_flags, bool *unlocked)
; void unmap_mapping_pages(struct address_space *mapping, pgoff_t start, pgoff_t nr, bool even_cows)
; void unmap_mapping_range(struct address_space *mapping, loff_t const holebegin, loff_t const holelen, int even_cows)
; static inline vm_fault_t handle_mm_fault(struct vm_area_struct *vma, unsigned long address, unsigned int flags)
BUG()
;return VM_FAULT_SIGBUS; } static inline int fixup_user_fault(struct task_struct *tsk, struct mm_struct *mm, unsigned long address, unsigned int fault_flags, bool *unlocked)
static inline void unmap_shared_mapping_range(struct address_space *mapping, loff_t const holebegin, loff_t const holelen)
long get_user_pages_remote(struct task_struct *tsk, struct mm_struct *mm, unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, struct vm_area_struct **vmas, int *locked)
; long get_user_pages(unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, struct vm_area_struct **vmas)
; long get_user_pages_locked(unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, int *locked)
; long get_user_pages_unlocked(unsigned long start, unsigned long nr_pages, struct page **pages, unsigned int gup_flags)
; long get_user_pages_longterm(unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, struct vm_area_struct **vmas)
; static inline long get_user_pages_longterm(unsigned long start, unsigned long nr_pages, unsigned int gup_flags, struct page **pages, struct vm_area_struct **vmas)
static inline unsigned int frame_vector_count(struct frame_vector *vec)
static inline struct page **frame_vector_pages(struct frame_vector *vec)
static inline unsigned long *frame_vector_pfns(struct frame_vector *vec)
void __set_page_dirty(struct page *, struct address_space *, int warn)
; int __set_page_dirty_nobuffers(struct page *page)
; int __set_page_dirty_no_writeback(struct page *page)
; int redirty_page_for_writepage(struct writeback_control *wbc, struct page *page)
; void account_page_dirtied(struct page *page, struct address_space *mapping)
; void account_page_cleaned(struct page *page, struct address_space *mapping, struct bdi_writeback *wb)
; int set_page_dirty(struct page *page)
; int set_page_dirty_lock(struct page *page)
; void __cancel_dirty_page(struct page *page)
; static inline void cancel_dirty_page(struct page *page)
static inline bool vma_is_anonymous(struct vm_area_struct *vma)
int __get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages)
;static inline unsigned long get_mm_counter(struct mm_struct *mm, int member)
static inline void add_mm_counter(struct mm_struct *mm, int member, long value)
static inline void inc_mm_counter(struct mm_struct *mm, int member)
static inline void dec_mm_counter(struct mm_struct *mm, int member)
static inline int mm_counter_file(struct page *page)
static inline int mm_counter(struct page *page)
static inline unsigned long get_mm_rss(struct mm_struct *mm)
static inline unsigned long get_mm_hiwater_rss(struct mm_struct *mm)
static inline unsigned long get_mm_hiwater_vm(struct mm_struct *mm)
static inline void update_hiwater_rss(struct mm_struct *mm)
static inline void update_hiwater_vm(struct mm_struct *mm)
static inline void reset_mm_hiwater_rss(struct mm_struct *mm)
static inline void setmax_mm_hiwater_rss(unsigned long *maxrss, struct mm_struct *mm)
void sync_mm_rss(struct mm_struct *mm)
; static inline void sync_mm_rss(struct mm_struct *mm)
static inline int pte_devmap(pte_t pte)
extern pte_t *__get_locked_pte(struct mm_struct *mm, unsigned long addr, spinlock_t **ptl)
; static inline pte_t *get_locked_pte(struct mm_struct *mm, unsigned long addr, spinlock_t **ptl)
static inline int __p4d_alloc(struct mm_struct *mm, pgd_t *pgd, unsigned long address)
static inline int __pud_alloc(struct mm_struct *mm, p4d_t *p4d, unsigned long address)
static inline void mm_inc_nr_puds(struct mm_struct *mm)
static inline void mm_dec_nr_puds(struct mm_struct *mm)
static inline int __pmd_alloc(struct mm_struct *mm, pud_t *pud, unsigned long address)
static inline void mm_inc_nr_pmds(struct mm_struct *mm)
static inline void mm_dec_nr_pmds(struct mm_struct *mm)
static inline void mm_pgtables_bytes_init(struct mm_struct *mm)
static inline unsigned long mm_pgtables_bytes(const struct mm_struct *mm)
static inline void mm_inc_nr_ptes(struct mm_struct *mm)
static inline void mm_dec_nr_ptes(struct mm_struct *mm)
static inline unsigned long mm_pgtables_bytes(const struct mm_struct *mm)
static inline p4d_t *p4d_alloc(struct mm_struct *mm, pgd_t *pgd, unsigned long address)
static inline pud_t *pud_alloc(struct mm_struct *mm, p4d_t *p4d, unsigned long address)
static inline pmd_t *pmd_alloc(struct mm_struct *mm, pud_t *pud, unsigned long address)
static inline spinlock_t *ptlock_ptr(struct page *page)
static inline spinlock_t *ptlock_ptr(struct page *page)
return page->ptl; } static inline void ptlock_cache_init(void)
static inline bool ptlock_alloc(struct page *page)
static inline void ptlock_free(struct page *page)
static inline spinlock_t *ptlock_ptr(struct page *page)
static inline spinlock_t *pte_lockptr(struct mm_struct *mm, pmd_t *pmd)
static inline bool ptlock_init(struct page *page)
static inline spinlock_t *pte_lockptr(struct mm_struct *mm, pmd_t *pmd)
static inline void pgtable_init(void)
static inline bool pgtable_page_ctor(struct page *page)
static inline void pgtable_page_dtor(struct page *page)
static struct page *pmd_to_page(pmd_t *pmd)
static inline spinlock_t *pmd_lockptr(struct mm_struct *mm, pmd_t *pmd)
static inline bool pgtable_pmd_page_ctor(struct page *page)
static inline void pgtable_pmd_page_dtor(struct page *page)
static inline spinlock_t *pmd_lockptr(struct mm_struct *mm, pmd_t *pmd)
static inline spinlock_t *pmd_lock(struct mm_struct *mm, pmd_t *pmd)
static inline spinlock_t *pud_lockptr(struct mm_struct *mm, pud_t *pud)
static inline spinlock_t *pud_lock(struct mm_struct *mm, pud_t *pud)
static inline void __free_reserved_page(struct page *page)
static inline void free_reserved_page(struct page *page)
static inline void mark_page_reserved(struct page *page)
static inline unsigned long free_initmem_default(int poison)
static inline unsigned long get_num_physpages(void)
!defined(CONFIG_HAVE_ARCH_EARLY_PFN_TO_NID)
static inline int __early_pfn_to_nid(unsigned long pfn, struct mminit_pfnnid_cache *state)
extern int __vm_enough_memory(struct mm_struct *mm, long pages, int cap_sys_admin)
; extern int __vma_adjust(struct vm_area_struct *vma, unsigned long start, unsigned long end, pgoff_t pgoff, struct vm_area_struct *insert, struct vm_area_struct *expand)
; static inline int vma_adjust(struct vm_area_struct *vma, unsigned long start, unsigned long end, pgoff_t pgoff, struct vm_area_struct *insert)
static inline int check_data_rlimit(unsigned long rlim, unsigned long new, unsigned long start, unsigned long end_data, unsigned long start_data)
static inline unsigned long do_mmap_pgoff(struct file *file, unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long pgoff, unsigned long *populate, struct list_head *uf)
extern int __mm_populate(unsigned long addr, unsigned long len, int ignore_errors)
; static inline void mm_populate(unsigned long addr, unsigned long len)
static inline unsigned long vm_unmapped_area(struct vm_unmapped_area_info *info)
static inline struct vm_area_struct * find_vma_intersection(struct mm_struct * mm, unsigned long start_addr, unsigned long end_addr)
static inline unsigned long vm_start_gap(struct vm_area_struct *vma)
static inline unsigned long vm_end_gap(struct vm_area_struct *vma)
static inline unsigned long vma_pages(struct vm_area_struct *vma)
static inline struct vm_area_struct *find_exact_vma(struct mm_struct *mm, unsigned long vm_start, unsigned long vm_end)
static inline bool range_in_vma(struct vm_area_struct *vma, unsigned long start, unsigned long end)
pgprot_t vm_get_page_prot(unsigned long vm_flags)
; void vma_set_page_prot(struct vm_area_struct *vma)
; static inline pgprot_t vm_get_page_prot(unsigned long vm_flags)
pgprot_t vm_get_page_prot(unsigned long vm_flags)
; void vma_set_page_prot(struct vm_area_struct *vma)
; static inline pgprot_t vm_get_page_prot(unsigned long vm_flags)
return __pgprot(0)
; } static inline void vma_set_page_prot(struct vm_area_struct *vma)
static inline vm_fault_t vmf_insert_page(struct vm_area_struct *vma, unsigned long addr, struct page *page)
static inline vm_fault_t vmf_error(int err)
static inline int vm_fault_to_errno(vm_fault_t vm_fault, int foll_flags)
static inline bool debug_pagealloc_enabled(void)
static inline void kernel_map_pages(struct page *page, int numpages, int enable)
__kernel_map_pages(page, numpages, enable)
; } extern bool kernel_page_present(struct page *page)
;endifstatic inline voidendifstatic inline bool debug_pagealloc_enabled(void)
extern struct vm_area_struct *get_gate_vma(struct mm_struct *mm)
; extern int in_gate_area_no_mm(unsigned long addr)
; extern int in_gate_area(struct mm_struct *mm, unsigned long addr)
; static inline struct vm_area_struct *get_gate_vma(struct mm_struct *mm)
extern struct vm_area_struct *get_gate_vma(struct mm_struct *mm)
; extern int in_gate_area_no_mm(unsigned long addr)
; extern int in_gate_area(struct mm_struct *mm, unsigned long addr)
; static inline struct vm_area_struct *get_gate_vma(struct mm_struct *mm)
return NULL; } static inline int in_gate_area(struct mm_struct *mm, unsigned long addr)
static inline unsigned int debug_guardpage_minorder(void)
static inline bool debug_guardpage_enabled(void)
static inline bool page_is_guard(struct page *page)
\n
     86 struct page *page
     49 struct mm_struct *mm
     22 const struct page *page
     18 struct vm_area_struct *vma
     14 void
     13 unsigned long address
     13 int cpupid
     11 unsigned long start
     11 unsigned long addr
     11 size_t size
     11 gfp_t flags
      7 struct page **pages
      7 struct address_space *mapping
      6 unsigned long nr_pages
      6 unsigned int gup_flags
      6 pmd_t *pmd
      5 page
      5 int node
      4 unsigned long vm_flags
      4 unsigned int flags
      4 struct vm_area_struct **vmas
      4 struct task_struct *tsk
      4 pud_t *pud
      4 int member
      4 const void *x
      3 unsigned long len
      3 unsigned long end
      3 unsigned int fault_flags
      3 struct frame_vector *vec
      3 size
      3 pmd_t pmd
      3 loff_t const holelen
      3 loff_t const holebegin
      3 int *total_mapcount
      3 bool *unlocked
      2 unsigned long pfn
      2 unsigned long node
      2 unsigned long
      2 struct vm_area_struct *insert
      2 spinlock_t **ptl
      2 size_t n
      2 !rcu_read_lock_held
      2 pud_t pud
      2 pte_t pte
      2 pgoff_t start
      2 pgoff_t pgoff
      2 pgoff_t nr
      2 pgd_t *pgd
      2 page->mem_cgroup
      2 p4d_t *p4d
      2 NUMA_NO_NODE
      2 int pid
      2 int *locked
      2 int even_cows
      2 flags
      2 enum zone_type zone
      2 cpupid
      2 const struct mm_struct *mm
      2 bool even_cows
      1 void *address
      1 vm_fault_t vm_fault
      1 unsigned long vm_start
      1 unsigned long vm_end
      1 unsigned long start_data
      1 unsigned long start_addr
      1 unsigned long section
      1 unsigned long rlim
      1 unsigned long prot
      1 unsigned long *populate
      1 unsigned long pgoff
      1 unsigned long new
      1 unsigned long *maxrss
      1 unsigned long limit
      1 unsigned long flags
      1 unsigned long end_data
      1 unsigned long end_addr
      1 unsigned int order
      1 u8 tag
      1 task->pid
      1 task
      1 struct zone *
      1 struct writeback_control *wbc
      1 struct vm_unmapped_area_info *info
      1 struct vm_area_struct *expand
      1 struct task_struct *task
      1 struct page *
      1 struct mm_struct * mm
      1 struct mminit_pfnnid_cache *state
      1 struct list_head *uf
      1 struct file *file
      1 struct dev_pagemap *
      1 struct bdi_writeback *wb
      1 struct address_space *
      1 pid_t task_pid
      1 pgd_t pgd
      1 numpages
      1 node
      1 long value
      1 long val
      1 long pages
      1 long count
      1 int write
      1 int warn
      1 int poison
      1 int numpages
      1 int nr_pages
      1 int nid
      1 int ignore_errors
      1 int foll_flags
      1 int err
      1 int enable
      1 int cpu
      1 int cap_sys_admin
      1 flags | __GFP_ZERO
      1 enum compound_dtor_id compound_dtor
      1 enable
      1 devmap_managed_key
      1 CONFIG_HAVE_ARCH_EARLY_PFN_TO_NID
      1 0xff
      1 0
      1 
