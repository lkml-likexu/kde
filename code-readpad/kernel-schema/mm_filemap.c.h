
EXPORT_SYMBOL_GPL(replace_page_cache_page);
EXPORT_SYMBOL_GPL(add_to_page_cache_lru);
EXPORT_SYMBOL_GPL(add_page_wait_queue);
EXPORT_SYMBOL_GPL(page_endio);
EXPORT_SYMBOL_GPL(__lock_page_killable);
static void page_cache_delete(struct address_space *mapping, struct page *page, void *shadow)
static void unaccount_page_cache_page(struct address_space *mapping, struct page *page)
void __delete_from_page_cache(struct page *page, void *shadow)
static void page_cache_free_page(struct address_space *mapping, struct page *page)
void delete_from_page_cache(struct page *page)
static void page_cache_delete_batch(struct address_space *mapping, struct pagevec *pvec)
void delete_from_page_cache_batch(struct address_space *mapping, struct pagevec *pvec)
int filemap_check_errors(struct address_space *mapping)
static int filemap_check_and_keep_errors(struct address_space *mapping)
int __filemap_fdatawrite_range(struct address_space *mapping, loff_t start, loff_t end, int sync_mode)
static inline int __filemap_fdatawrite(struct address_space *mapping, int sync_mode)
int filemap_fdatawrite(struct address_space *mapping)
int filemap_fdatawrite_range(struct address_space *mapping, loff_t start, loff_t end)
int filemap_flush(struct address_space *mapping)
bool filemap_range_has_page(struct address_space *mapping, loff_t start_byte, loff_t end_byte)
static void __filemap_fdatawait_range(struct address_space *mapping, loff_t start_byte, loff_t end_byte)
int filemap_fdatawait_range(struct address_space *mapping, loff_t start_byte, loff_t end_byte)
int file_fdatawait_range(struct file *file, loff_t start_byte, loff_t end_byte)
int filemap_fdatawait_keep_errors(struct address_space *mapping)
static bool mapping_needs_writeback(struct address_space *mapping)
int filemap_write_and_wait(struct address_space *mapping)
int filemap_write_and_wait_range(struct address_space *mapping, loff_t lstart, loff_t lend)
void __filemap_set_wb_err(struct address_space *mapping, int err)
int file_check_and_advance_wb_err(struct file *file)
int file_write_and_wait_range(struct file *file, loff_t lstart, loff_t lend)
int replace_page_cache_page(struct page *old, struct page *new, gfp_t gfp_mask)
static int __add_to_page_cache_locked(struct page *page, struct address_space *mapping, pgoff_t offset, gfp_t gfp_mask, void **shadowp)
int add_to_page_cache_locked(struct page *page, struct address_space *mapping, pgoff_t offset, gfp_t gfp_mask)
int add_to_page_cache_lru(struct page *page, struct address_space *mapping, pgoff_t offset, gfp_t gfp_mask)
struct page *__page_cache_alloc(gfp_t gfp)
static wait_queue_head_t *page_waitqueue(struct page *page)
void __init pagecache_init(void)
static int wake_page_function(wait_queue_entry_t *wait, unsigned mode, int sync, void *arg)
static void wake_up_page_bit(struct page *page, int bit_nr)
static void wake_up_page(struct page *page, int bit)
static inline int wait_on_page_bit_common(wait_queue_head_t *q, struct page *page, int bit_nr, int state, bool lock)
void wait_on_page_bit(struct page *page, int bit_nr)
int wait_on_page_bit_killable(struct page *page, int bit_nr)
void add_page_wait_queue(struct page *page, wait_queue_entry_t *waiter)
static inline bool clear_bit_unlock_is_negative_byte(long nr, volatile void *mem)
void unlock_page(struct page *page)
void end_page_writeback(struct page *page)
void page_endio(struct page *page, bool is_write, int err)
void __lock_page(struct page *__page)
int __lock_page_killable(struct page *__page)
int __lock_page_or_retry(struct page *page, struct mm_struct *mm, unsigned int flags)
pgoff_t page_cache_next_miss(struct address_space *mapping, pgoff_t index, unsigned long max_scan)
pgoff_t page_cache_prev_miss(struct address_space *mapping, pgoff_t index, unsigned long max_scan)
struct page *find_get_entry(struct address_space *mapping, pgoff_t offset)
struct page *find_lock_entry(struct address_space *mapping, pgoff_t offset)
struct page *pagecache_get_page(struct address_space *mapping, pgoff_t offset, int fgp_flags, gfp_t gfp_mask)
unsigned find_get_entries(struct address_space *mapping, pgoff_t start, unsigned int nr_entries, struct page **entries, pgoff_t *indices)
unsigned find_get_pages_range(struct address_space *mapping, pgoff_t *start, pgoff_t end, unsigned int nr_pages, struct page **pages)
unsigned find_get_pages_contig(struct address_space *mapping, pgoff_t index, unsigned int nr_pages, struct page **pages)
unsigned find_get_pages_range_tag(struct address_space *mapping, pgoff_t *index, pgoff_t end, xa_mark_t tag, unsigned int nr_pages, struct page **pages)
unsigned find_get_entries_tag(struct address_space *mapping, pgoff_t start, xa_mark_t tag, unsigned int nr_entries, struct page **entries, pgoff_t *indices)
static void shrink_readahead_size_eio(struct file *filp, struct file_ra_state *ra)
static ssize_t generic_file_buffered_read(struct kiocb *iocb, struct iov_iter *iter, ssize_t written)
ssize_t generic_file_read_iter(struct kiocb *iocb, struct iov_iter *iter)
static int page_cache_read(struct file *file, pgoff_t offset, gfp_t gfp_mask)
static void do_sync_mmap_readahead(struct vm_area_struct *vma, struct file_ra_state *ra, struct file *file, pgoff_t offset)
static void do_async_mmap_readahead(struct vm_area_struct *vma, struct file_ra_state *ra, struct file *file, struct page *page, pgoff_t offset)
vm_fault_t filemap_fault(struct vm_fault *vmf)
void filemap_map_pages(struct vm_fault *vmf, pgoff_t start_pgoff, pgoff_t end_pgoff)
vm_fault_t filemap_page_mkwrite(struct vm_fault *vmf)
int generic_file_mmap(struct file * file, struct vm_area_struct * vma)
int generic_file_readonly_mmap(struct file *file, struct vm_area_struct *vma)
int generic_file_readonly_mmap(struct file *file, struct vm_area_struct *vma)
if ((vma->vm_flags & VM_SHARED)
&& (vma->vm_flags & VM_MAYWRITE)
)
return -EINVAL;return generic_file_mmap(file, vma)
; } vm_fault_t filemap_page_mkwrite(struct vm_fault *vmf)
int generic_file_readonly_mmap(struct file *file, struct vm_area_struct *vma)
if ((vma->vm_flags & VM_SHARED)
&& (vma->vm_flags & VM_MAYWRITE)
)
return -EINVAL;return generic_file_mmap(file, vma)
; } vm_fault_t filemap_page_mkwrite(struct vm_fault *vmf)
return VM_FAULT_SIGBUS; } int generic_file_mmap(struct file * file, struct vm_area_struct * vma)
int generic_file_readonly_mmap(struct file *file, struct vm_area_struct *vma)
if ((vma->vm_flags & VM_SHARED)
&& (vma->vm_flags & VM_MAYWRITE)
)
return -EINVAL;return generic_file_mmap(file, vma)
; } vm_fault_t filemap_page_mkwrite(struct vm_fault *vmf)
return VM_FAULT_SIGBUS; } int generic_file_mmap(struct file * file, struct vm_area_struct * vma)
return -ENOSYS; } int generic_file_readonly_mmap(struct file * file, struct vm_area_struct * vma)
static struct page *wait_on_page_read(struct page *page)
static struct page *do_read_cache_page(struct address_space *mapping, pgoff_t index, int (*filler)
(void *, struct page *)
, void *data, gfp_t gfp)
struct page *read_cache_page(struct address_space *mapping, pgoff_t index, int (*filler)
(void *, struct page *)
, void *data)
struct page *read_cache_page_gfp(struct address_space *mapping, pgoff_t index, gfp_t gfp)
inline ssize_t generic_write_checks(struct kiocb *iocb, struct iov_iter *from)
int pagecache_write_begin(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned flags, struct page **pagep, void **fsdata)
int pagecache_write_end(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned copied, struct page *page, void *fsdata)
ssize_t generic_file_direct_write(struct kiocb *iocb, struct iov_iter *from)
struct page *grab_cache_page_write_begin(struct address_space *mapping, pgoff_t index, unsigned flags)
ssize_t generic_perform_write(struct file *file, struct iov_iter *i, loff_t pos)
ssize_t __generic_file_write_iter(struct kiocb *iocb, struct iov_iter *from)
ssize_t generic_file_write_iter(struct kiocb *iocb, struct iov_iter *from)
int try_to_release_page(struct page *page, gfp_t gfp_mask)
  39 struct address_space *mapping
  23 struct page *page
  13 struct file *file
   9 pgoff_t offset
   7 pgoff_t index
   7 gfp_t gfp_mask
   6 struct vm_fault *vmf
   6 struct vm_area_struct *vma
   6 struct kiocb *iocb
   4 struct vm_area_struct * vma
   4 struct iov_iter *from
   4 struct file * file
   4 loff_t start_byte
   4 loff_t end_byte
   4 int bit_nr
   3 vma->vm_flags & VM_SHARED
   3 vma->vm_flags & VM_MAYWRITE
   3 vma
   3 unsigned int nr_pages
   3 struct page **pages
   3 struct file_ra_state *ra
   3 loff_t pos
   3 file
   2 xa_mark_t tag
   2 void *shadow
   2 void *
   2 unsigned long max_scan
   2 unsigned len
   2 unsigned int nr_entries
   2 unsigned flags
   2 struct pagevec *pvec
   2 struct page *__page
   2 struct page **entries
   2 struct page *
   2 struct iov_iter *iter
   2 pgoff_t start
   2 pgoff_t end
   2 pgoff_t *indices
   2 loff_t start
   2 loff_t lstart
   2 loff_t lend
   2 loff_t end
   2 int sync_mode
   2 int err
   2 int *filler
   2 gfp_t gfp
   1 wait_queue_head_t *q
   1 wait_queue_entry_t *waiter
   1 wait_queue_entry_t *wait
   1 volatile void *mem
   1 void *fsdata
   1 void *arg
   1 void **shadowp
   1 void **fsdata
   1 void
   1 unsigned mode
   1 unsigned int flags
   1 unsigned copied
   1 struct page *old
   1 struct page *new
   1 struct page **pagep
   1 struct mm_struct *mm
   1 struct iov_iter *i
   1 struct file *filp
   1 ssize_t written
   1 replace_page_cache_page
   1 pgoff_t start_pgoff
   1 pgoff_t end_pgoff
   1 pgoff_t *start
   1 pgoff_t *index
   1 page_endio
   1 long nr
   1 int sync
   1 int state
   1 int fgp_flags
   1 int bit
   1 bool lock
   1 bool is_write
   1 add_to_page_cache_lru
   1 add_page_wait_queue
   1 __lock_page_killable
