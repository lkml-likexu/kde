
static u32 vhost_transport_get_local_cid(void)
static struct vhost_vsock *__vhost_vsock_get(u32 guest_cid)
static struct vhost_vsock *vhost_vsock_get(u32 guest_cid)
static void vhost_transport_do_send_pkt(struct vhost_vsock *vsock, struct vhost_virtqueue *vq)
static void vhost_transport_send_pkt_work(struct vhost_work *work)
static int vhost_transport_send_pkt(struct virtio_vsock_pkt *pkt)
static int vhost_transport_cancel_pkt(struct vsock_sock *vsk)
static struct virtio_vsock_pkt * vhost_vsock_alloc_pkt(struct vhost_virtqueue *vq, unsigned int out, unsigned int in)
static bool vhost_vsock_more_replies(struct vhost_vsock *vsock)
static void vhost_vsock_handle_tx_kick(struct vhost_work *work)
static void vhost_vsock_handle_rx_kick(struct vhost_work *work)
static int vhost_vsock_start(struct vhost_vsock *vsock)
static int vhost_vsock_stop(struct vhost_vsock *vsock)
static void vhost_vsock_free(struct vhost_vsock *vsock)
static int vhost_vsock_dev_open(struct inode *inode, struct file *file)
static void vhost_vsock_flush(struct vhost_vsock *vsock)
static void vhost_vsock_reset_orphans(struct sock *sk)
static int vhost_vsock_dev_release(struct inode *inode, struct file *file)
static int vhost_vsock_set_cid(struct vhost_vsock *vsock, u64 guest_cid)
static int vhost_vsock_set_features(struct vhost_vsock *vsock, u64 features)
static long vhost_vsock_dev_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
static long vhost_vsock_dev_compat_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
static int __init vhost_vsock_init(void)
static void __exit vhost_vsock_exit(void)
   8 struct vhost_vsock *vsock
   3 void
   3 struct vhost_work *work
   2 unsigned long arg
   2 unsigned int ioctl
   2 u32 guest_cid
   2 struct vhost_virtqueue *vq
   2 struct inode *inode
   2 struct file *file
   2 struct file *f
   1 unsigned int out
   1 unsigned int in
   1 u64 guest_cid
   1 u64 features
   1 struct vsock_sock *vsk
   1 struct virtio_vsock_pkt *pkt
   1 struct sock *sk
