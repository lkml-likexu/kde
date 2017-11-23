
static int sk_diag_fill(struct sock *sk, struct sk_buff *skb, u32 portid, u32 seq, u32 flags)
static int vsock_diag_dump(struct sk_buff *skb, struct netlink_callback *cb)
static int vsock_diag_handler_dump(struct sk_buff *skb, struct nlmsghdr *h)
static int __init vsock_diag_init(void)
static void __exit vsock_diag_exit(void)
   3 struct sk_buff *skb
   2 void
   1 u32 seq
   1 u32 portid
   1 u32 flags
   1 struct sock *sk
   1 struct nlmsghdr *h
   1 struct netlink_callback *cb
