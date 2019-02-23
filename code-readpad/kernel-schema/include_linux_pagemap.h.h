
\n
static inline void mapping_set_error(struct address_space *mapping, int error)
static inline void mapping_set_unevictable(struct address_space *mapping)
static inline void mapping_clear_unevictable(struct address_space *mapping)
static inline int mapping_unevictable(struct address_space *mapping)
static inline void mapping_set_exiting(struct address_space *mapping)
static inline int mapping_exiting(struct address_space *mapping)
static inline void mapping_set_no_writeback_tags(struct address_space *mapping)
static inline int mapping_use_writeback_tags(struct address_space *mapping)
static inline gfp_t mapping_gfp_mask(struct address_space * mapping)
static inline gfp_t mapping_gfp_constraint(struct address_space *mapping, gfp_t gfp_mask)
static inline void mapping_set_gfp_mask(struct address_space *m, gfp_t mask)
static inline int page_cache_get_speculative(struct page *page)
static inline int page_cache_add_speculative(struct page *page, int count)
extern struct page *__page_cache_alloc(gfp_t gfp)
; static inline struct page *__page_cache_alloc(gfp_t gfp)
static inline struct page *page_cache_alloc(struct address_space *x)
static inline gfp_t readahead_gfp_mask(struct address_space *x)
static inline struct page *find_get_page(struct address_space *mapping, pgoff_t offset)
static inline struct page *find_get_page_flags(struct address_space *mapping, pgoff_t offset, int fgp_flags)
static inline struct page *find_lock_page(struct address_space *mapping, pgoff_t offset)
static inline struct page *find_or_create_page(struct address_space *mapping, pgoff_t offset, gfp_t gfp_mask)
static inline struct page *grab_cache_page_nowait(struct address_space *mapping, pgoff_t index)
struct page *find_get_entry(struct address_space *mapping, pgoff_t offset)
; struct page *find_lock_entry(struct address_space *mapping, pgoff_t offset)
; unsigned find_get_entries(struct address_space *mapping, pgoff_t start, unsigned int nr_entries, struct page **entries, pgoff_t *indices)
; unsigned find_get_pages_range(struct address_space *mapping, pgoff_t *start, pgoff_t end, unsigned int nr_pages, struct page **pages)
; static inline unsigned find_get_pages(struct address_space *mapping, pgoff_t *start, unsigned int nr_pages, struct page **pages)
struct page *find_get_entry(struct address_space *mapping, pgoff_t offset)
; struct page *find_lock_entry(struct address_space *mapping, pgoff_t offset)
; unsigned find_get_entries(struct address_space *mapping, pgoff_t start, unsigned int nr_entries, struct page **entries, pgoff_t *indices)
; unsigned find_get_pages_range(struct address_space *mapping, pgoff_t *start, pgoff_t end, unsigned int nr_pages, struct page **pages)
; static inline unsigned find_get_pages(struct address_space *mapping, pgoff_t *start, unsigned int nr_pages, struct page **pages)
return find_get_pages_range(mapping, start, (pgoff_t)
-1, nr_pages, pages)
; } unsigned find_get_pages_contig(struct address_space *mapping, pgoff_t start, unsigned int nr_pages, struct page **pages)
; unsigned find_get_pages_range_tag(struct address_space *mapping, pgoff_t *index, pgoff_t end, xa_mark_t tag, unsigned int nr_pages, struct page **pages)
; static inline unsigned find_get_pages_tag(struct address_space *mapping, pgoff_t *index, xa_mark_t tag, unsigned int nr_pages, struct page **pages)
static inline struct page *grab_cache_page(struct address_space *mapping, pgoff_t index)
static inline struct page *read_mapping_page(struct address_space *mapping, pgoff_t index, void *data)
static inline pgoff_t page_to_index(struct page *page)
static inline pgoff_t page_to_pgoff(struct page *page)
static inline loff_t page_offset(struct page *page)
static inline loff_t page_file_offset(struct page *page)
static inline pgoff_t linear_page_index(struct vm_area_struct *vma, unsigned long address)
static inline int trylock_page(struct page *page)
static inline void lock_page(struct page *page)
static inline int lock_page_killable(struct page *page)
static inline int lock_page_or_retry(struct page *page, struct mm_struct *mm, unsigned int flags)
static inline void wait_on_page_locked(struct page *page)
static inline int wait_on_page_locked_killable(struct page *page)
static inline void wait_on_page_writeback(struct page *page)
static inline int fault_in_pages_writeable(char __user *uaddr, int size)
static inline int fault_in_pages_readable(const char __user *uaddr, int size)
static inline int add_to_page_cache(struct page *page, struct address_space *mapping, pgoff_t offset, gfp_t gfp_mask)
static inline unsigned long dir_pages(struct inode *inode)
\n
     30 struct address_space *mapping
     14 struct page *page
      9 pgoff_t offset
      7 unsigned int nr_pages
      7 struct page **pages
      4 pgoff_t *start
      3 pgoff_t start
      3 pgoff_t index
      3 pgoff_t end
      3 gfp_t gfp_mask
      2 xa_mark_t tag
      2 unsigned int nr_entries
      2 struct page **entries
      2 struct address_space *x
      2 pgoff_t *indices
      2 pgoff_t *index
      2 int size
      2 gfp_t gfp
      1 void *data
      1 unsigned long address
      1 unsigned int flags
      1 struct vm_area_struct *vma
      1 struct mm_struct *mm
      1 struct inode *inode
      1 struct address_space * mapping
      1 struct address_space *m
      1 start
      1 pgoff_t
      1 mapping
      1 int fgp_flags
      1 int error
      1 int count
      1 gfp_t mask
      1 const char __user *uaddr
      1 char __user *uaddr
