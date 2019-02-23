
\n
static void *vhost_net_buf_get_ptr(struct vhost_net_buf *rxq)
static int vhost_net_buf_get_size(struct vhost_net_buf *rxq)
static int vhost_net_buf_is_empty(struct vhost_net_buf *rxq)
static void *vhost_net_buf_consume(struct vhost_net_buf *rxq)
static int vhost_net_buf_produce(struct vhost_net_virtqueue *nvq)
static void vhost_net_buf_unproduce(struct vhost_net_virtqueue *nvq)
static int vhost_net_buf_peek_len(void *ptr)
static int vhost_net_buf_peek(struct vhost_net_virtqueue *nvq)
static void vhost_net_buf_init(struct vhost_net_buf *rxq)
static void vhost_net_enable_zcopy(int vq)
static struct vhost_net_ubuf_ref * vhost_net_ubuf_alloc(struct vhost_virtqueue *vq, bool zcopy)
static int vhost_net_ubuf_put(struct vhost_net_ubuf_ref *ubufs)
static void vhost_net_ubuf_put_and_wait(struct vhost_net_ubuf_ref *ubufs)
static void vhost_net_ubuf_put_wait_and_free(struct vhost_net_ubuf_ref *ubufs)
static void vhost_net_clear_ubuf_info(struct vhost_net *n)
static int vhost_net_set_ubuf_info(struct vhost_net *n)
static void vhost_net_vq_reset(struct vhost_net *n)
static void vhost_net_tx_packet(struct vhost_net *net)
static void vhost_net_tx_err(struct vhost_net *net)
static bool vhost_net_tx_select_zcopy(struct vhost_net *net)
static bool vhost_sock_zcopy(struct socket *sock)
static bool vhost_sock_xdp(struct socket *sock)
static void vhost_zerocopy_signal_used(struct vhost_net *net, struct vhost_virtqueue *vq)
static void vhost_zerocopy_callback(struct ubuf_info *ubuf, bool success)
static inline unsigned long busy_clock(void)
static bool vhost_can_busy_poll(unsigned long endtime)
static void vhost_net_disable_vq(struct vhost_net *n, struct vhost_virtqueue *vq)
static int vhost_net_enable_vq(struct vhost_net *n, struct vhost_virtqueue *vq)
static void vhost_net_signal_used(struct vhost_net_virtqueue *nvq)
static void vhost_tx_batch(struct vhost_net *net, struct vhost_net_virtqueue *nvq, struct socket *sock, struct msghdr *msghdr)
static int sock_has_rx_data(struct socket *sock)
static void vhost_net_busy_poll_try_queue(struct vhost_net *net, struct vhost_virtqueue *vq)
static void vhost_net_busy_poll(struct vhost_net *net, struct vhost_virtqueue *rvq, struct vhost_virtqueue *tvq, bool *busyloop_intr, bool poll_rx)
static int vhost_net_tx_get_vq_desc(struct vhost_net *net, struct vhost_net_virtqueue *tnvq, unsigned int *out_num, unsigned int *in_num, struct msghdr *msghdr, bool *busyloop_intr)
static bool vhost_exceeds_maxpend(struct vhost_net *net)
static size_t init_iov_iter(struct vhost_virtqueue *vq, struct iov_iter *iter, size_t hdr_size, int out)
static bool vhost_exceeds_weight(int pkts, int total_len)
static int get_tx_bufs(struct vhost_net *net, struct vhost_net_virtqueue *nvq, struct msghdr *msg, unsigned int *out, unsigned int *in, size_t *len, bool *busyloop_intr)
static bool tx_can_batch(struct vhost_virtqueue *vq, size_t total_len)
static bool vhost_net_page_frag_refill(struct vhost_net *net, unsigned int sz, struct page_frag *pfrag, gfp_t gfp)
static int vhost_net_build_xdp(struct vhost_net_virtqueue *nvq, struct iov_iter *from)
static void handle_tx_copy(struct vhost_net *net, struct socket *sock)
static void handle_tx_zerocopy(struct vhost_net *net, struct socket *sock)
static void handle_tx(struct vhost_net *net)
static int peek_head_len(struct vhost_net_virtqueue *rvq, struct sock *sk)
static int vhost_net_rx_peek_head_len(struct vhost_net *net, struct sock *sk, bool *busyloop_intr)
static int get_rx_bufs(struct vhost_virtqueue *vq, struct vring_used_elem *heads, int datalen, unsigned *iovcount, struct vhost_log *log, unsigned *log_num, unsigned int quota)
static void handle_rx(struct vhost_net *net)
static void handle_tx_kick(struct vhost_work *work)
static void handle_rx_kick(struct vhost_work *work)
static void handle_tx_net(struct vhost_work *work)
static void handle_rx_net(struct vhost_work *work)
static int vhost_net_open(struct inode *inode, struct file *f)
static struct socket *vhost_net_stop_vq(struct vhost_net *n, struct vhost_virtqueue *vq)
static void vhost_net_stop(struct vhost_net *n, struct socket **tx_sock, struct socket **rx_sock)
static void vhost_net_flush_vq(struct vhost_net *n, int index)
static void vhost_net_flush(struct vhost_net *n)
static int vhost_net_release(struct inode *inode, struct file *f)
static struct socket *get_raw_socket(int fd)
static struct ptr_ring *get_tap_ptr_ring(int fd)
static struct socket *get_tap_socket(int fd)
static struct socket *get_socket(int fd)
static long vhost_net_set_backend(struct vhost_net *n, unsigned index, int fd)
static long vhost_net_reset_owner(struct vhost_net *n)
static int vhost_net_set_backend_features(struct vhost_net *n, u64 features)
static int vhost_net_set_features(struct vhost_net *n, u64 features)
static long vhost_net_set_owner(struct vhost_net *n)
static long vhost_net_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
static long vhost_net_compat_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
static ssize_t vhost_net_chr_read_iter(struct kiocb *iocb, struct iov_iter *to)
static ssize_t vhost_net_chr_write_iter(struct kiocb *iocb, struct iov_iter *from)
static __poll_t vhost_net_chr_poll(struct file *file, poll_table *wait)
static int vhost_net_init(void)
static void vhost_net_exit(void)
\n
     16 struct vhost_net *net
     14 struct vhost_net *n
      9 struct vhost_virtqueue *vq
      7 struct vhost_net_virtqueue *nvq
      6 struct socket *sock
      5 struct vhost_net_buf *rxq
      5 int fd
      4 struct vhost_work *work
      4 struct file *f
      4 bool *busyloop_intr
      3 void
      3 struct vhost_net_ubuf_ref *ubufs
      2 unsigned long arg
      2 unsigned int ioctl
      2 u64 features
      2 struct sock *sk
      2 struct msghdr *msghdr
      2 struct kiocb *iocb
      2 struct iov_iter *from
      2 struct inode *inode
      1 void *ptr
      1 unsigned long endtime
      1 unsigned *log_num
      1 unsigned *iovcount
      1 unsigned int sz
      1 unsigned int quota
      1 unsigned int *out_num
      1 unsigned int *out
      1 unsigned int *in_num
      1 unsigned int *in
      1 unsigned index
      1 struct vring_used_elem *heads
      1 struct vhost_virtqueue *tvq
      1 struct vhost_virtqueue *rvq
      1 struct vhost_net_virtqueue *tnvq
      1 struct vhost_net_virtqueue *rvq
      1 struct vhost_log *log
      1 struct ubuf_info *ubuf
      1 struct socket **tx_sock
      1 struct socket **rx_sock
      1 struct page_frag *pfrag
      1 struct msghdr *msg
      1 struct iov_iter *to
      1 struct iov_iter *iter
      1 struct file *file
      1 size_t total_len
      1 size_t *len
      1 size_t hdr_size
      1 poll_table *wait
      1 int vq
      1 int total_len
      1 int pkts
      1 int out
      1 int index
      1 int datalen
      1 gfp_t gfp
      1 bool zcopy
      1 bool success
      1 bool poll_rx
