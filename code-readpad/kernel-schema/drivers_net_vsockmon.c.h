
static int vsockmon_dev_init(struct net_device *dev)
static void vsockmon_dev_uninit(struct net_device *dev)
static int vsockmon_open(struct net_device *dev)
static int vsockmon_close(struct net_device *dev)
static netdev_tx_t vsockmon_xmit(struct sk_buff *skb, struct net_device *dev)
static void vsockmon_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
static int vsockmon_is_valid_mtu(int new_mtu)
static int vsockmon_change_mtu(struct net_device *dev, int new_mtu)
static u32 always_on(struct net_device *dev)
static void vsockmon_setup(struct net_device *dev)
static __init int vsockmon_register(void)
static __exit void vsockmon_unregister(void)
   9 struct net_device *dev
   2 void
   2 int new_mtu
   1 struct sk_buff *skb
   1 struct rtnl_link_stats64 *stats
