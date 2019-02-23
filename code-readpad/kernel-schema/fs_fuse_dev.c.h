
EXPORT_SYMBOL_GPL(fuse_request_alloc);
EXPORT_SYMBOL_GPL(fuse_get_req);
EXPORT_SYMBOL_GPL(fuse_get_req_for_background);
EXPORT_SYMBOL_GPL(fuse_put_request);
EXPORT_SYMBOL_GPL(fuse_request_send);
EXPORT_SYMBOL_GPL(fuse_request_send_background);
EXPORT_SYMBOL_GPL(fuse_abort_conn);
EXPORT_SYMBOL_GPL(fuse_dev_release);
EXPORT_SYMBOL_GPL(fuse_dev_operations);
\n
static struct fuse_dev *fuse_get_dev(struct file *file)
static void fuse_request_init(struct fuse_req *req, struct page **pages, struct fuse_page_desc *page_descs, unsigned npages)
static struct page **fuse_req_pages_alloc(unsigned int npages, gfp_t flags, struct fuse_page_desc **desc)
static struct fuse_req *__fuse_request_alloc(unsigned npages, gfp_t flags)
struct fuse_req *fuse_request_alloc(unsigned npages)
struct fuse_req *fuse_request_alloc_nofs(unsigned npages)
static void fuse_req_pages_free(struct fuse_req *req)
bool fuse_req_realloc_pages(struct fuse_conn *fc, struct fuse_req *req, gfp_t flags)
void fuse_request_free(struct fuse_req *req)
void __fuse_get_request(struct fuse_req *req)
static void __fuse_put_request(struct fuse_req *req)
void fuse_set_initialized(struct fuse_conn *fc)
static bool fuse_block_alloc(struct fuse_conn *fc, bool for_background)
static void fuse_drop_waiting(struct fuse_conn *fc)
static struct fuse_req *__fuse_get_req(struct fuse_conn *fc, unsigned npages, bool for_background)
struct fuse_req *fuse_get_req(struct fuse_conn *fc, unsigned npages)
struct fuse_req *fuse_get_req_for_background(struct fuse_conn *fc, unsigned npages)
static struct fuse_req *get_reserved_req(struct fuse_conn *fc, struct file *file)
static void put_reserved_req(struct fuse_conn *fc, struct fuse_req *req)
struct fuse_req *fuse_get_req_nofail_nopages(struct fuse_conn *fc, struct file *file)
void fuse_put_request(struct fuse_conn *fc, struct fuse_req *req)
static unsigned len_args(unsigned numargs, struct fuse_arg *args)
static u64 fuse_get_unique(struct fuse_iqueue *fiq)
static unsigned int fuse_req_hash(u64 unique)
static void queue_request(struct fuse_iqueue *fiq, struct fuse_req *req)
void fuse_queue_forget(struct fuse_conn *fc, struct fuse_forget_link *forget, u64 nodeid, u64 nlookup)
static void flush_bg_queue(struct fuse_conn *fc)
static void request_end(struct fuse_conn *fc, struct fuse_req *req)
static void queue_interrupt(struct fuse_iqueue *fiq, struct fuse_req *req)
static void request_wait_answer(struct fuse_conn *fc, struct fuse_req *req)
static void __fuse_request_send(struct fuse_conn *fc, struct fuse_req *req)
void fuse_request_send(struct fuse_conn *fc, struct fuse_req *req)
static void fuse_adjust_compat(struct fuse_conn *fc, struct fuse_args *args)
ssize_t fuse_simple_request(struct fuse_conn *fc, struct fuse_args *args)
bool fuse_request_queue_background(struct fuse_conn *fc, struct fuse_req *req)
void fuse_request_send_background(struct fuse_conn *fc, struct fuse_req *req)
static int fuse_request_send_notify_reply(struct fuse_conn *fc, struct fuse_req *req, u64 unique)
void fuse_force_forget(struct file *file, u64 nodeid)
static int lock_request(struct fuse_req *req)
static int unlock_request(struct fuse_req *req)
static void fuse_copy_init(struct fuse_copy_state *cs, int write, struct iov_iter *iter)
static void fuse_copy_finish(struct fuse_copy_state *cs)
static int fuse_copy_fill(struct fuse_copy_state *cs)
static int fuse_copy_do(struct fuse_copy_state *cs, void **val, unsigned *size)
static int fuse_check_page(struct page *page)
static int fuse_try_move_page(struct fuse_copy_state *cs, struct page **pagep)
static int fuse_ref_page(struct fuse_copy_state *cs, struct page *page, unsigned offset, unsigned count)
static int fuse_copy_page(struct fuse_copy_state *cs, struct page **pagep, unsigned offset, unsigned count, int zeroing)
static int fuse_copy_pages(struct fuse_copy_state *cs, unsigned nbytes, int zeroing)
static int fuse_copy_one(struct fuse_copy_state *cs, void *val, unsigned size)
static int fuse_copy_args(struct fuse_copy_state *cs, unsigned numargs, unsigned argpages, struct fuse_arg *args, int zeroing)
static int forget_pending(struct fuse_iqueue *fiq)
static int request_pending(struct fuse_iqueue *fiq)
static int fuse_read_interrupt(struct fuse_iqueue *fiq, struct fuse_copy_state *cs, size_t nbytes, struct fuse_req *req)
__releases(fiq->waitq.lock)
static struct fuse_forget_link *dequeue_forget(struct fuse_iqueue *fiq, unsigned max, unsigned *countp)
static int fuse_read_single_forget(struct fuse_iqueue *fiq, struct fuse_copy_state *cs, size_t nbytes)
__releases(fiq->waitq.lock)
static int fuse_read_batch_forget(struct fuse_iqueue *fiq, struct fuse_copy_state *cs, size_t nbytes)
__releases(fiq->waitq.lock)
static int fuse_read_forget(struct fuse_conn *fc, struct fuse_iqueue *fiq, struct fuse_copy_state *cs, size_t nbytes)
__releases(fiq->waitq.lock)
static ssize_t fuse_dev_do_read(struct fuse_dev *fud, struct file *file, struct fuse_copy_state *cs, size_t nbytes)
static int fuse_dev_open(struct inode *inode, struct file *file)
static ssize_t fuse_dev_read(struct kiocb *iocb, struct iov_iter *to)
static ssize_t fuse_dev_splice_read(struct file *in, loff_t *ppos, struct pipe_inode_info *pipe, size_t len, unsigned int flags)
static int fuse_notify_poll(struct fuse_conn *fc, unsigned int size, struct fuse_copy_state *cs)
static int fuse_notify_inval_inode(struct fuse_conn *fc, unsigned int size, struct fuse_copy_state *cs)
static int fuse_notify_inval_entry(struct fuse_conn *fc, unsigned int size, struct fuse_copy_state *cs)
static int fuse_notify_delete(struct fuse_conn *fc, unsigned int size, struct fuse_copy_state *cs)
static int fuse_notify_store(struct fuse_conn *fc, unsigned int size, struct fuse_copy_state *cs)
static void fuse_retrieve_end(struct fuse_conn *fc, struct fuse_req *req)
static int fuse_retrieve(struct fuse_conn *fc, struct inode *inode, struct fuse_notify_retrieve_out *outarg)
static int fuse_notify_retrieve(struct fuse_conn *fc, unsigned int size, struct fuse_copy_state *cs)
static int fuse_notify(struct fuse_conn *fc, enum fuse_notify_code code, unsigned int size, struct fuse_copy_state *cs)
static struct fuse_req *request_find(struct fuse_pqueue *fpq, u64 unique)
static int copy_out_args(struct fuse_copy_state *cs, struct fuse_out *out, unsigned nbytes)
static ssize_t fuse_dev_do_write(struct fuse_dev *fud, struct fuse_copy_state *cs, size_t nbytes)
static ssize_t fuse_dev_write(struct kiocb *iocb, struct iov_iter *from)
static ssize_t fuse_dev_splice_write(struct pipe_inode_info *pipe, struct file *out, loff_t *ppos, size_t len, unsigned int flags)
static __poll_t fuse_dev_poll(struct file *file, poll_table *wait)
static void end_requests(struct fuse_conn *fc, struct list_head *head)
static void end_polls(struct fuse_conn *fc)
void fuse_abort_conn(struct fuse_conn *fc, bool is_abort)
void fuse_wait_aborted(struct fuse_conn *fc)
int fuse_dev_release(struct inode *inode, struct file *file)
static int fuse_dev_fasync(int fd, struct file *file, int on)
static int fuse_device_clone(struct fuse_conn *fc, struct file *new)
static long fuse_dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
int __init fuse_dev_init(void)
void fuse_dev_cleanup(void)
\n
     37 struct fuse_conn *fc
     24 struct fuse_copy_state *cs
     21 struct fuse_req *req
     10 struct fuse_iqueue *fiq
     10 struct file *file
      7 unsigned npages
      7 unsigned int size
      6 size_t nbytes
      4 fiq->waitq.lock
      3 u64 unique
      3 struct inode *inode
      3 int zeroing
      3 gfp_t flags
      2 void
      2 unsigned offset
      2 unsigned numargs
      2 unsigned nbytes
      2 unsigned int flags
      2 unsigned count
      2 u64 nodeid
      2 struct pipe_inode_info *pipe
      2 struct page **pagep
      2 struct page *page
      2 struct kiocb *iocb
      2 struct fuse_dev *fud
      2 struct fuse_args *args
      2 struct fuse_arg *args
      2 size_t len
      2 loff_t *ppos
      2 bool for_background
      1 void **val
      1 void *val
      1 unsigned *size
      1 unsigned size
      1 unsigned max
      1 unsigned long arg
      1 unsigned int npages
      1 unsigned int cmd
      1 unsigned *countp
      1 unsigned argpages
      1 u64 nlookup
      1 struct page **pages
      1 struct list_head *head
      1 struct iov_iter *to
      1 struct iov_iter *iter
      1 struct iov_iter *from
      1 struct fuse_pqueue *fpq
      1 struct fuse_page_desc *page_descs
      1 struct fuse_page_desc **desc
      1 struct fuse_out *out
      1 struct fuse_notify_retrieve_out *outarg
      1 struct fuse_forget_link *forget
      1 struct file *out
      1 struct file *new
      1 struct file *in
      1 poll_table *wait
      1 int write
      1 int on
      1 int fd
      1 fuse_request_send_background
      1 fuse_request_send
      1 fuse_request_alloc
      1 fuse_put_request
      1 fuse_get_req_for_background
      1 fuse_get_req
      1 fuse_dev_release
      1 fuse_dev_operations
      1 fuse_abort_conn
      1 enum fuse_notify_code code
      1 bool is_abort
