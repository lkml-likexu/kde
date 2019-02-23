
EXPORT_SYMBOL_GPL(splice_to_pipe);
\n
static int page_cache_pipe_buf_steal(struct pipe_inode_info *pipe, struct pipe_buffer *buf)
static void page_cache_pipe_buf_release(struct pipe_inode_info *pipe, struct pipe_buffer *buf)
static int page_cache_pipe_buf_confirm(struct pipe_inode_info *pipe, struct pipe_buffer *buf)
static int user_page_pipe_buf_steal(struct pipe_inode_info *pipe, struct pipe_buffer *buf)
static void wakeup_pipe_readers(struct pipe_inode_info *pipe)
ssize_t splice_to_pipe(struct pipe_inode_info *pipe, struct splice_pipe_desc *spd)
ssize_t add_to_pipe(struct pipe_inode_info *pipe, struct pipe_buffer *buf)
int splice_grow_spd(const struct pipe_inode_info *pipe, struct splice_pipe_desc *spd)
void splice_shrink_spd(struct splice_pipe_desc *spd)
ssize_t generic_file_splice_read(struct file *in, loff_t *ppos, struct pipe_inode_info *pipe, size_t len, unsigned int flags)
static int generic_pipe_buf_nosteal(struct pipe_inode_info *pipe, struct pipe_buffer *buf)
static ssize_t kernel_readv(struct file *file, const struct kvec *vec, unsigned long vlen, loff_t offset)
static ssize_t default_file_splice_read(struct file *in, loff_t *ppos, struct pipe_inode_info *pipe, size_t len, unsigned int flags)
static int pipe_to_sendpage(struct pipe_inode_info *pipe, struct pipe_buffer *buf, struct splice_desc *sd)
static void wakeup_pipe_writers(struct pipe_inode_info *pipe)
static int splice_from_pipe_feed(struct pipe_inode_info *pipe, struct splice_desc *sd, splice_actor *actor)
static int splice_from_pipe_next(struct pipe_inode_info *pipe, struct splice_desc *sd)
static void splice_from_pipe_begin(struct splice_desc *sd)
static void splice_from_pipe_end(struct pipe_inode_info *pipe, struct splice_desc *sd)
ssize_t __splice_from_pipe(struct pipe_inode_info *pipe, struct splice_desc *sd, splice_actor *actor)
ssize_t splice_from_pipe(struct pipe_inode_info *pipe, struct file *out, loff_t *ppos, size_t len, unsigned int flags, splice_actor *actor)
ssize_t iter_file_splice_write(struct pipe_inode_info *pipe, struct file *out, loff_t *ppos, size_t len, unsigned int flags)
static int write_pipe_buf(struct pipe_inode_info *pipe, struct pipe_buffer *buf, struct splice_desc *sd)
static ssize_t default_file_splice_write(struct pipe_inode_info *pipe, struct file *out, loff_t *ppos, size_t len, unsigned int flags)
ssize_t generic_splice_sendpage(struct pipe_inode_info *pipe, struct file *out, loff_t *ppos, size_t len, unsigned int flags)
static long do_splice_from(struct pipe_inode_info *pipe, struct file *out, loff_t *ppos, size_t len, unsigned int flags)
static long do_splice_to(struct file *in, loff_t *ppos, struct pipe_inode_info *pipe, size_t len, unsigned int flags)
ssize_t splice_direct_to_actor(struct file *in, struct splice_desc *sd, splice_direct_actor *actor)
static int direct_splice_actor(struct pipe_inode_info *pipe, struct splice_desc *sd)
long do_splice_direct(struct file *in, loff_t *ppos, struct file *out, loff_t *opos, size_t len, unsigned int flags)
static int wait_for_space(struct pipe_inode_info *pipe, unsigned flags)
static long do_splice(struct file *in, loff_t __user *off_in, struct file *out, loff_t __user *off_out, size_t len, unsigned int flags)
static int iter_to_pipe(struct iov_iter *from, struct pipe_inode_info *pipe, unsigned flags)
static int pipe_to_user(struct pipe_inode_info *pipe, struct pipe_buffer *buf, struct splice_desc *sd)
static long vmsplice_to_user(struct file *file, struct iov_iter *iter, unsigned int flags)
static long vmsplice_to_pipe(struct file *file, struct iov_iter *iter, unsigned int flags)
static int vmsplice_type(struct fd f, int *type)
static long do_vmsplice(struct file *f, struct iov_iter *iter, unsigned int flags)
SYSCALL_DEFINE4(vmsplice, int, fd, const struct iovec __user *, uiov, unsigned long, nr_segs, unsigned int, flags)
COMPAT_SYSCALL_DEFINE4(vmsplice, int, fd, const struct compat_iovec __user *, iov32, unsigned int, nr_segs, unsigned int, flags)
SYSCALL_DEFINE6(splice, int, fd_in, loff_t __user *, off_in, int, fd_out, loff_t __user *, off_out, size_t, len, unsigned int, flags)
static int ipipe_prep(struct pipe_inode_info *pipe, unsigned int flags)
static int opipe_prep(struct pipe_inode_info *pipe, unsigned int flags)
static int splice_pipe_to_pipe(struct pipe_inode_info *ipipe, struct pipe_inode_info *opipe, size_t len, unsigned int flags)
static int link_pipe(struct pipe_inode_info *ipipe, struct pipe_inode_info *opipe, size_t len, unsigned int flags)
static long do_tee(struct file *in, struct file *out, size_t len, unsigned int flags)
SYSCALL_DEFINE4(tee, int, fdin, int, fdout, size_t, len, unsigned int, flags)
\n
     29 struct pipe_inode_info *pipe
     18 unsigned int flags
     13 size_t len
     10 struct splice_desc *sd
      9 struct pipe_buffer *buf
      9 loff_t *ppos
      8 struct file *out
      7 struct file *in
      6 int
      5 unsigned int
      4 flags
      3 struct splice_pipe_desc *spd
      3 struct iov_iter *iter
      3 struct file *file
      3 splice_actor *actor
      2 vmsplice
      2 unsigned flags
      2 struct pipe_inode_info *opipe
      2 struct pipe_inode_info *ipipe
      2 size_t
      2 nr_segs
      2 loff_t __user *
      2 len
      2 fd
      1 unsigned long vlen
      1 unsigned long
      1 uiov
      1 tee
      1 struct iov_iter *from
      1 struct file *f
      1 struct fd f
      1 splice_to_pipe
      1 splice_direct_actor *actor
      1 splice
      1 off_out
      1 off_in
      1 loff_t __user *off_out
      1 loff_t __user *off_in
      1 loff_t *opos
      1 loff_t offset
      1 iov32
      1 int *type
      1 fd_out
      1 fdout
      1 fd_in
      1 fdin
      1 const struct pipe_inode_info *pipe
      1 const struct kvec *vec
      1 const struct iovec __user *
      1 const struct compat_iovec __user *
