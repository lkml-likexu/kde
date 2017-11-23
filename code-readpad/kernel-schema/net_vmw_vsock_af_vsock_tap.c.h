
EXPORT_SYMBOL_GPL(vsock_add_tap);
EXPORT_SYMBOL_GPL(vsock_remove_tap);
EXPORT_SYMBOL_GPL(vsock_deliver_tap);
int vsock_add_tap(struct vsock_tap *vt)
int vsock_remove_tap(struct vsock_tap *vt)
static int __vsock_deliver_tap_skb(struct sk_buff *skb, struct net_device *dev)
static void __vsock_deliver_tap(struct sk_buff *skb)
void vsock_deliver_tap(struct sk_buff *build_skb(void *opaque)
, void *opaque)
   2 struct vsock_tap *vt
   2 struct sk_buff *skb
   1 vsock_remove_tap
   1 vsock_deliver_tap
   1 vsock_add_tap
   1 struct sk_buff *build_skbvoid *opaque
   1 struct net_device *dev
