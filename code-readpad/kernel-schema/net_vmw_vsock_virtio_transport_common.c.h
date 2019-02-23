
EXPORT_SYMBOL_GPL(virtio_transport_deliver_tap_pkt);
EXPORT_SYMBOL_GPL(virtio_transport_inc_tx_pkt);
EXPORT_SYMBOL_GPL(virtio_transport_get_credit);
EXPORT_SYMBOL_GPL(virtio_transport_put_credit);
EXPORT_SYMBOL_GPL(virtio_transport_stream_dequeue);
EXPORT_SYMBOL_GPL(virtio_transport_dgram_dequeue);
EXPORT_SYMBOL_GPL(virtio_transport_stream_has_data);
EXPORT_SYMBOL_GPL(virtio_transport_stream_has_space);
EXPORT_SYMBOL_GPL(virtio_transport_do_socket_init);
EXPORT_SYMBOL_GPL(virtio_transport_get_buffer_size);
EXPORT_SYMBOL_GPL(virtio_transport_get_min_buffer_size);
EXPORT_SYMBOL_GPL(virtio_transport_get_max_buffer_size);
EXPORT_SYMBOL_GPL(virtio_transport_set_buffer_size);
EXPORT_SYMBOL_GPL(virtio_transport_set_min_buffer_size);
EXPORT_SYMBOL_GPL(virtio_transport_set_max_buffer_size);
EXPORT_SYMBOL_GPL(virtio_transport_notify_poll_in);
EXPORT_SYMBOL_GPL(virtio_transport_notify_poll_out);
EXPORT_SYMBOL_GPL(virtio_transport_notify_recv_init);
EXPORT_SYMBOL_GPL(virtio_transport_notify_recv_pre_block);
EXPORT_SYMBOL_GPL(virtio_transport_notify_recv_pre_dequeue);
EXPORT_SYMBOL_GPL(virtio_transport_notify_recv_post_dequeue);
EXPORT_SYMBOL_GPL(virtio_transport_notify_send_init);
EXPORT_SYMBOL_GPL(virtio_transport_notify_send_pre_block);
EXPORT_SYMBOL_GPL(virtio_transport_notify_send_pre_enqueue);
EXPORT_SYMBOL_GPL(virtio_transport_notify_send_post_enqueue);
EXPORT_SYMBOL_GPL(virtio_transport_stream_rcvhiwat);
EXPORT_SYMBOL_GPL(virtio_transport_stream_is_active);
EXPORT_SYMBOL_GPL(virtio_transport_stream_allow);
EXPORT_SYMBOL_GPL(virtio_transport_dgram_bind);
EXPORT_SYMBOL_GPL(virtio_transport_dgram_allow);
EXPORT_SYMBOL_GPL(virtio_transport_connect);
EXPORT_SYMBOL_GPL(virtio_transport_shutdown);
EXPORT_SYMBOL_GPL(virtio_transport_dgram_enqueue);
EXPORT_SYMBOL_GPL(virtio_transport_stream_enqueue);
EXPORT_SYMBOL_GPL(virtio_transport_destruct);
EXPORT_SYMBOL_GPL(virtio_transport_release);
EXPORT_SYMBOL_GPL(virtio_transport_recv_pkt);
EXPORT_SYMBOL_GPL(virtio_transport_free_pkt);
\n
static const struct virtio_transport *virtio_transport_get_ops(void)
static struct virtio_vsock_pkt * virtio_transport_alloc_pkt(struct virtio_vsock_pkt_info *info, size_t len, u32 src_cid, u32 src_port, u32 dst_cid, u32 dst_port)
static struct sk_buff *virtio_transport_build_skb(void *opaque)
void virtio_transport_deliver_tap_pkt(struct virtio_vsock_pkt *pkt)
static int virtio_transport_send_pkt_info(struct vsock_sock *vsk, struct virtio_vsock_pkt_info *info)
static void virtio_transport_inc_rx_pkt(struct virtio_vsock_sock *vvs, struct virtio_vsock_pkt *pkt)
static void virtio_transport_dec_rx_pkt(struct virtio_vsock_sock *vvs, struct virtio_vsock_pkt *pkt)
void virtio_transport_inc_tx_pkt(struct virtio_vsock_sock *vvs, struct virtio_vsock_pkt *pkt)
u32 virtio_transport_get_credit(struct virtio_vsock_sock *vvs, u32 credit)
void virtio_transport_put_credit(struct virtio_vsock_sock *vvs, u32 credit)
static int virtio_transport_send_credit_update(struct vsock_sock *vsk, int type, struct virtio_vsock_hdr *hdr)
static ssize_t virtio_transport_stream_do_dequeue(struct vsock_sock *vsk, struct msghdr *msg, size_t len)
ssize_t virtio_transport_stream_dequeue(struct vsock_sock *vsk, struct msghdr *msg, size_t len, int flags)
int virtio_transport_dgram_dequeue(struct vsock_sock *vsk, struct msghdr *msg, size_t len, int flags)
s64 virtio_transport_stream_has_data(struct vsock_sock *vsk)
static s64 virtio_transport_has_space(struct vsock_sock *vsk)
s64 virtio_transport_stream_has_space(struct vsock_sock *vsk)
int virtio_transport_do_socket_init(struct vsock_sock *vsk, struct vsock_sock *psk)
u64 virtio_transport_get_buffer_size(struct vsock_sock *vsk)
u64 virtio_transport_get_min_buffer_size(struct vsock_sock *vsk)
u64 virtio_transport_get_max_buffer_size(struct vsock_sock *vsk)
void virtio_transport_set_buffer_size(struct vsock_sock *vsk, u64 val)
void virtio_transport_set_min_buffer_size(struct vsock_sock *vsk, u64 val)
void virtio_transport_set_max_buffer_size(struct vsock_sock *vsk, u64 val)
int virtio_transport_notify_poll_in(struct vsock_sock *vsk, size_t target, bool *data_ready_now)
int virtio_transport_notify_poll_out(struct vsock_sock *vsk, size_t target, bool *space_avail_now)
int virtio_transport_notify_recv_init(struct vsock_sock *vsk, size_t target, struct vsock_transport_recv_notify_data *data)
int virtio_transport_notify_recv_pre_block(struct vsock_sock *vsk, size_t target, struct vsock_transport_recv_notify_data *data)
int virtio_transport_notify_recv_pre_dequeue(struct vsock_sock *vsk, size_t target, struct vsock_transport_recv_notify_data *data)
int virtio_transport_notify_recv_post_dequeue(struct vsock_sock *vsk, size_t target, ssize_t copied, bool data_read, struct vsock_transport_recv_notify_data *data)
int virtio_transport_notify_send_init(struct vsock_sock *vsk, struct vsock_transport_send_notify_data *data)
int virtio_transport_notify_send_pre_block(struct vsock_sock *vsk, struct vsock_transport_send_notify_data *data)
int virtio_transport_notify_send_pre_enqueue(struct vsock_sock *vsk, struct vsock_transport_send_notify_data *data)
int virtio_transport_notify_send_post_enqueue(struct vsock_sock *vsk, ssize_t written, struct vsock_transport_send_notify_data *data)
u64 virtio_transport_stream_rcvhiwat(struct vsock_sock *vsk)
bool virtio_transport_stream_is_active(struct vsock_sock *vsk)
bool virtio_transport_stream_allow(u32 cid, u32 port)
int virtio_transport_dgram_bind(struct vsock_sock *vsk, struct sockaddr_vm *addr)
bool virtio_transport_dgram_allow(u32 cid, u32 port)
int virtio_transport_connect(struct vsock_sock *vsk)
int virtio_transport_shutdown(struct vsock_sock *vsk, int mode)
int virtio_transport_dgram_enqueue(struct vsock_sock *vsk, struct sockaddr_vm *remote_addr, struct msghdr *msg, size_t dgram_len)
ssize_t virtio_transport_stream_enqueue(struct vsock_sock *vsk, struct msghdr *msg, size_t len)
void virtio_transport_destruct(struct vsock_sock *vsk)
static int virtio_transport_reset(struct vsock_sock *vsk, struct virtio_vsock_pkt *pkt)
static int virtio_transport_reset_no_sock(struct virtio_vsock_pkt *pkt)
static void virtio_transport_wait_close(struct sock *sk, long timeout)
static void virtio_transport_do_close(struct vsock_sock *vsk, bool cancel_timeout)
static void virtio_transport_close_timeout(struct work_struct *work)
static bool virtio_transport_close(struct vsock_sock *vsk)
void virtio_transport_release(struct vsock_sock *vsk)
static int virtio_transport_recv_connecting(struct sock *sk, struct virtio_vsock_pkt *pkt)
static int virtio_transport_recv_connected(struct sock *sk, struct virtio_vsock_pkt *pkt)
static void virtio_transport_recv_disconnecting(struct sock *sk, struct virtio_vsock_pkt *pkt)
static int virtio_transport_send_response(struct vsock_sock *vsk, struct virtio_vsock_pkt *pkt)
static int virtio_transport_recv_listen(struct sock *sk, struct virtio_vsock_pkt *pkt)
static bool virtio_transport_space_update(struct sock *sk, struct virtio_vsock_pkt *pkt)
void virtio_transport_recv_pkt(struct virtio_vsock_pkt *pkt)
void virtio_transport_free_pkt(struct virtio_vsock_pkt *pkt)
\n
     38 struct vsock_sock *vsk
     14 struct virtio_vsock_pkt *pkt
      6 struct sock *sk
      6 size_t target
      5 struct virtio_vsock_sock *vvs
      5 struct msghdr *msg
      5 size_t len
      4 struct vsock_transport_send_notify_data *data
      4 struct vsock_transport_recv_notify_data *data
      3 u64 val
      2 u32 port
      2 u32 credit
      2 u32 cid
      2 struct virtio_vsock_pkt_info *info
      2 int flags
      1 void *opaque
      1 void
      1 virtio_transport_stream_rcvhiwat
      1 virtio_transport_stream_is_active
      1 virtio_transport_stream_has_space
      1 virtio_transport_stream_has_data
      1 virtio_transport_stream_enqueue
      1 virtio_transport_stream_dequeue
      1 virtio_transport_stream_allow
      1 virtio_transport_shutdown
      1 virtio_transport_set_min_buffer_size
      1 virtio_transport_set_max_buffer_size
      1 virtio_transport_set_buffer_size
      1 virtio_transport_release
      1 virtio_transport_recv_pkt
      1 virtio_transport_put_credit
      1 virtio_transport_notify_send_pre_enqueue
      1 virtio_transport_notify_send_pre_block
      1 virtio_transport_notify_send_post_enqueue
      1 virtio_transport_notify_send_init
      1 virtio_transport_notify_recv_pre_dequeue
      1 virtio_transport_notify_recv_pre_block
      1 virtio_transport_notify_recv_post_dequeue
      1 virtio_transport_notify_recv_init
      1 virtio_transport_notify_poll_out
      1 virtio_transport_notify_poll_in
      1 virtio_transport_inc_tx_pkt
      1 virtio_transport_get_min_buffer_size
      1 virtio_transport_get_max_buffer_size
      1 virtio_transport_get_credit
      1 virtio_transport_get_buffer_size
      1 virtio_transport_free_pkt
      1 virtio_transport_do_socket_init
      1 virtio_transport_dgram_enqueue
      1 virtio_transport_dgram_dequeue
      1 virtio_transport_dgram_bind
      1 virtio_transport_dgram_allow
      1 virtio_transport_destruct
      1 virtio_transport_deliver_tap_pkt
      1 virtio_transport_connect
      1 u32 src_port
      1 u32 src_cid
      1 u32 dst_port
      1 u32 dst_cid
      1 struct work_struct *work
      1 struct vsock_sock *psk
      1 struct virtio_vsock_hdr *hdr
      1 struct sockaddr_vm *remote_addr
      1 struct sockaddr_vm *addr
      1 ssize_t written
      1 ssize_t copied
      1 size_t dgram_len
      1 long timeout
      1 int type
      1 int mode
      1 bool *space_avail_now
      1 bool *data_ready_now
      1 bool data_read
      1 bool cancel_timeout
