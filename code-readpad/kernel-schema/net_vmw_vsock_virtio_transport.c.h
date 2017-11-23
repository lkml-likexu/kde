
static struct virtio_vsock *virtio_vsock_get(void)
static u32 virtio_transport_get_local_cid(void)
static void virtio_transport_loopback_work(struct work_struct *work)
static int virtio_transport_send_pkt_loopback(struct virtio_vsock *vsock, struct virtio_vsock_pkt *pkt)
static void virtio_transport_send_pkt_work(struct work_struct *work)
static int virtio_transport_send_pkt(struct virtio_vsock_pkt *pkt)
static int virtio_transport_cancel_pkt(struct vsock_sock *vsk)
static void virtio_vsock_rx_fill(struct virtio_vsock *vsock)
static void virtio_transport_tx_work(struct work_struct *work)
static bool virtio_transport_more_replies(struct virtio_vsock *vsock)
static void virtio_transport_rx_work(struct work_struct *work)
static int virtio_vsock_event_fill_one(struct virtio_vsock *vsock, struct virtio_vsock_event *event)
static void virtio_vsock_event_fill(struct virtio_vsock *vsock)
static void virtio_vsock_reset_sock(struct sock *sk)
static void virtio_vsock_update_guest_cid(struct virtio_vsock *vsock)
static void virtio_vsock_event_handle(struct virtio_vsock *vsock, struct virtio_vsock_event *event)
static void virtio_transport_event_work(struct work_struct *work)
static void virtio_vsock_event_done(struct virtqueue *vq)
static void virtio_vsock_tx_done(struct virtqueue *vq)
static void virtio_vsock_rx_done(struct virtqueue *vq)
static int virtio_vsock_probe(struct virtio_device *vdev)
static void virtio_vsock_remove(struct virtio_device *vdev)
static int __init virtio_vsock_init(void)
static void __exit virtio_vsock_exit(void)
   7 struct virtio_vsock *vsock
   5 struct work_struct *work
   4 void
   3 struct virtqueue *vq
   2 struct virtio_vsock_pkt *pkt
   2 struct virtio_vsock_event *event
   2 struct virtio_device *vdev
   1 struct vsock_sock *vsk
   1 struct sock *sk
