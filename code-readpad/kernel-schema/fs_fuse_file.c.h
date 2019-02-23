
EXPORT_SYMBOL_GPL(fuse_do_open);
EXPORT_SYMBOL_GPL(fuse_sync_release);
EXPORT_SYMBOL_GPL(fuse_direct_io);
EXPORT_SYMBOL_GPL(fuse_do_ioctl);
EXPORT_SYMBOL_GPL(fuse_file_poll);
\n
static int fuse_send_open(struct fuse_conn *fc, u64 nodeid, struct file *file, int opcode, struct fuse_open_out *outargp)
struct fuse_file *fuse_file_alloc(struct fuse_conn *fc)
void fuse_file_free(struct fuse_file *ff)
static struct fuse_file *fuse_file_get(struct fuse_file *ff)
static void fuse_release_end(struct fuse_conn *fc, struct fuse_req *req)
static void fuse_file_put(struct fuse_file *ff, bool sync, bool isdir)
int fuse_do_open(struct fuse_conn *fc, u64 nodeid, struct file *file, bool isdir)
static void fuse_link_write_file(struct file *file)
void fuse_finish_open(struct inode *inode, struct file *file)
int fuse_open_common(struct inode *inode, struct file *file, bool isdir)
static void fuse_prepare_release(struct fuse_file *ff, int flags, int opcode)
void fuse_release_common(struct file *file, bool isdir)
static int fuse_open(struct inode *inode, struct file *file)
static int fuse_release(struct inode *inode, struct file *file)
void fuse_sync_release(struct fuse_file *ff, int flags)
u64 fuse_lock_owner_id(struct fuse_conn *fc, fl_owner_t id)
static bool fuse_range_is_writeback(struct inode *inode, pgoff_t idx_from, pgoff_t idx_to)
static inline bool fuse_page_is_writeback(struct inode *inode, pgoff_t index)
static int fuse_wait_on_page_writeback(struct inode *inode, pgoff_t index)
static void fuse_sync_writes(struct inode *inode)
static int fuse_flush(struct file *file, fl_owner_t id)
int fuse_fsync_common(struct file *file, loff_t start, loff_t end, int datasync, int opcode)
static int fuse_fsync(struct file *file, loff_t start, loff_t end, int datasync)
void fuse_read_fill(struct fuse_req *req, struct file *file, loff_t pos, size_t count, int opcode)
static void fuse_release_user_pages(struct fuse_req *req, bool should_dirty)
static void fuse_io_release(struct kref *kref)
static ssize_t fuse_get_res_by_io(struct fuse_io_priv *io)
static void fuse_aio_complete(struct fuse_io_priv *io, int err, ssize_t pos)
static void fuse_aio_complete_req(struct fuse_conn *fc, struct fuse_req *req)
static size_t fuse_async_req_send(struct fuse_conn *fc, struct fuse_req *req, size_t num_bytes, struct fuse_io_priv *io)
static size_t fuse_send_read(struct fuse_req *req, struct fuse_io_priv *io, loff_t pos, size_t count, fl_owner_t owner)
static void fuse_read_update_size(struct inode *inode, loff_t size, u64 attr_ver)
static void fuse_short_read(struct fuse_req *req, struct inode *inode, u64 attr_ver)
static int fuse_do_readpage(struct file *file, struct page *page)
static int fuse_readpage(struct file *file, struct page *page)
static void fuse_readpages_end(struct fuse_conn *fc, struct fuse_req *req)
static void fuse_send_readpages(struct fuse_req *req, struct file *file)
static int fuse_readpages_fill(void *_data, struct page *page)
static int fuse_readpages(struct file *file, struct address_space *mapping, struct list_head *pages, unsigned nr_pages)
static ssize_t fuse_file_read_iter(struct kiocb *iocb, struct iov_iter *to)
static void fuse_write_fill(struct fuse_req *req, struct fuse_file *ff, loff_t pos, size_t count)
static size_t fuse_send_write(struct fuse_req *req, struct fuse_io_priv *io, loff_t pos, size_t count, fl_owner_t owner)
bool fuse_write_update_size(struct inode *inode, loff_t pos)
static size_t fuse_send_write_pages(struct fuse_req *req, struct kiocb *iocb, struct inode *inode, loff_t pos, size_t count)
static ssize_t fuse_fill_write_pages(struct fuse_req *req, struct address_space *mapping, struct iov_iter *ii, loff_t pos)
static inline unsigned int fuse_wr_pages(loff_t pos, size_t len, unsigned int max_pages)
static ssize_t fuse_perform_write(struct kiocb *iocb, struct address_space *mapping, struct iov_iter *ii, loff_t pos)
static ssize_t fuse_file_write_iter(struct kiocb *iocb, struct iov_iter *from)
static inline void fuse_page_descs_length_init(struct fuse_req *req, unsigned index, unsigned nr_pages)
static inline unsigned long fuse_get_user_addr(const struct iov_iter *ii)
static inline size_t fuse_get_frag_size(const struct iov_iter *ii, size_t max_size)
static int fuse_get_user_pages(struct fuse_req *req, struct iov_iter *ii, size_t *nbytesp, int write)
ssize_t fuse_direct_io(struct fuse_io_priv *io, struct iov_iter *iter, loff_t *ppos, int flags)
static ssize_t __fuse_direct_read(struct fuse_io_priv *io, struct iov_iter *iter, loff_t *ppos)
static ssize_t fuse_direct_read_iter(struct kiocb *iocb, struct iov_iter *to)
static ssize_t fuse_direct_write_iter(struct kiocb *iocb, struct iov_iter *from)
static void fuse_writepage_free(struct fuse_conn *fc, struct fuse_req *req)
static void fuse_writepage_finish(struct fuse_conn *fc, struct fuse_req *req)
static void fuse_send_writepage(struct fuse_conn *fc, struct fuse_req *req, loff_t size)
__releases(fc->lock)
__acquires(fc->lock)
void fuse_flush_writepages(struct inode *inode)
__releases(fc->lock)
__acquires(fc->lock)
static void fuse_writepage_end(struct fuse_conn *fc, struct fuse_req *req)
static struct fuse_file *__fuse_write_file_get(struct fuse_conn *fc, struct fuse_inode *fi)
static struct fuse_file *fuse_write_file_get(struct fuse_conn *fc, struct fuse_inode *fi)
int fuse_write_inode(struct inode *inode, struct writeback_control *wbc)
static int fuse_writepage_locked(struct page *page)
static int fuse_writepage(struct page *page, struct writeback_control *wbc)
static void fuse_writepages_send(struct fuse_fill_wb_data *data)
static bool fuse_writepage_in_flight(struct fuse_req *new_req, struct page *page)
static int fuse_writepages_fill(struct page *page, struct writeback_control *wbc, void *_data)
static int fuse_writepages(struct address_space *mapping, struct writeback_control *wbc)
static int fuse_write_begin(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned flags, struct page **pagep, void **fsdata)
static int fuse_write_end(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned copied, struct page *page, void *fsdata)
static int fuse_launder_page(struct page *page)
static void fuse_vma_close(struct vm_area_struct *vma)
static vm_fault_t fuse_page_mkwrite(struct vm_fault *vmf)
static int fuse_file_mmap(struct file *file, struct vm_area_struct *vma)
static int fuse_direct_mmap(struct file *file, struct vm_area_struct *vma)
static int convert_fuse_file_lock(struct fuse_conn *fc, const struct fuse_file_lock *ffl, struct file_lock *fl)
static void fuse_lk_fill(struct fuse_args *args, struct file *file, const struct file_lock *fl, int opcode, pid_t pid, int flock, struct fuse_lk_in *inarg)
static int fuse_getlk(struct file *file, struct file_lock *fl)
static int fuse_setlk(struct file *file, struct file_lock *fl, int flock)
static int fuse_file_lock(struct file *file, int cmd, struct file_lock *fl)
static int fuse_file_flock(struct file *file, int cmd, struct file_lock *fl)
static sector_t fuse_bmap(struct address_space *mapping, sector_t block)
static loff_t fuse_lseek(struct file *file, loff_t offset, int whence)
static loff_t fuse_file_llseek(struct file *file, loff_t offset, int whence)
static int fuse_copy_ioctl_iovec_old(struct iovec *dst, void *src, size_t transferred, unsigned count, bool is_compat)
static int fuse_verify_ioctl_iov(struct fuse_conn *fc, struct iovec *iov, size_t count)
static int fuse_copy_ioctl_iovec(struct fuse_conn *fc, struct iovec *dst, void *src, size_t transferred, unsigned count, bool is_compat)
long fuse_do_ioctl(struct file *file, unsigned int cmd, unsigned long arg, unsigned int flags)
long fuse_ioctl_common(struct file *file, unsigned int cmd, unsigned long arg, unsigned int flags)
static long fuse_file_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long fuse_file_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static struct rb_node **fuse_find_polled_node(struct fuse_conn *fc, u64 kh, struct rb_node **parent_out)
static void fuse_register_polled_file(struct fuse_conn *fc, struct fuse_file *ff)
__poll_t fuse_file_poll(struct file *file, poll_table *wait)
int fuse_notify_poll_wakeup(struct fuse_conn *fc, struct fuse_notify_poll_wakeup_out *outarg)
static void fuse_do_truncate(struct file *file)
static inline loff_t fuse_round_up(struct fuse_conn *fc, loff_t off)
static ssize_t fuse_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
static long fuse_file_fallocate(struct file *file, int mode, loff_t offset, loff_t length)
static ssize_t fuse_copy_file_range(struct file *file_in, loff_t pos_in, struct file *file_out, loff_t pos_out, size_t len, unsigned int flags)
void fuse_init_file_inode(struct inode *inode)
\n
     34 struct file *file
     21 struct fuse_conn *fc
     19 struct fuse_req *req
     15 struct inode *inode
     11 loff_t pos
      9 struct page *page
      7 struct kiocb *iocb
      7 struct fuse_io_priv *io
      7 struct fuse_file *ff
      7 struct address_space *mapping
      6 size_t count
      5 struct file_lock *fl
      5 int opcode
      4 unsigned long arg
      4 unsigned int cmd
      4 struct writeback_control *wbc
      4 fc->lock
      4 bool isdir
      3 unsigned int flags
      3 struct vm_area_struct *vma
      3 struct iov_iter *iter
      3 struct iov_iter *ii
      3 loff_t offset
      3 int flags
      2 void *src
      2 void *_data
      2 unsigned nr_pages
      2 unsigned len
      2 unsigned count
      2 u64 nodeid
      2 u64 attr_ver
      2 struct iov_iter *to
      2 struct iov_iter *from
      2 struct iovec *dst
      2 struct fuse_inode *fi
      2 size_t transferred
      2 size_t len
      2 pgoff_t index
      2 loff_t start
      2 loff_t size
      2 loff_t *ppos
      2 loff_t end
      2 int whence
      2 int flock
      2 int datasync
      2 int cmd
      2 fl_owner_t owner
      2 fl_owner_t id
      2 const struct iov_iter *ii
      2 bool is_compat
      1 void **fsdata
      1 void *fsdata
      1 unsigned int max_pages
      1 unsigned index
      1 unsigned flags
      1 unsigned copied
      1 u64 kh
      1 struct vm_fault *vmf
      1 struct rb_node **parent_out
      1 struct page **pagep
      1 struct list_head *pages
      1 struct kref *kref
      1 struct iovec *iov
      1 struct fuse_req *new_req
      1 struct fuse_open_out *outargp
      1 struct fuse_notify_poll_wakeup_out *outarg
      1 struct fuse_lk_in *inarg
      1 struct fuse_fill_wb_data *data
      1 struct fuse_args *args
      1 struct file *file_out
      1 struct file *file_in
      1 ssize_t pos
      1 size_t num_bytes
      1 size_t *nbytesp
      1 size_t max_size
      1 sector_t block
      1 poll_table *wait
      1 pid_t pid
      1 pgoff_t idx_to
      1 pgoff_t idx_from
      1 loff_t pos_out
      1 loff_t pos_in
      1 loff_t off
      1 loff_t length
      1 int write
      1 int mode
      1 int err
      1 fuse_sync_release
      1 fuse_file_poll
      1 fuse_do_open
      1 fuse_do_ioctl
      1 fuse_direct_io
      1 const struct fuse_file_lock *ffl
      1 const struct file_lock *fl
      1 bool sync
      1 bool should_dirty
