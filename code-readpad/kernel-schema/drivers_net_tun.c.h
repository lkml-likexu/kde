
EXPORT_SYMBOL_GPL(tun_ptr_free);
EXPORT_SYMBOL_GPL(tun_get_socket);
EXPORT_SYMBOL_GPL(tun_get_tx_ring);
\n
bool tun_is_xdp_frame(void *ptr)
void *tun_xdp_to_ptr(void *ptr)
void *tun_ptr_to_xdp(void *ptr)
static int tun_napi_receive(struct napi_struct *napi, int budget)
static int tun_napi_poll(struct napi_struct *napi, int budget)
static void tun_napi_init(struct tun_struct *tun, struct tun_file *tfile, bool napi_en, bool napi_frags)
static void tun_napi_disable(struct tun_file *tfile)
static void tun_napi_del(struct tun_file *tfile)
static bool tun_napi_frags_enabled(const struct tun_file *tfile)
static inline bool tun_legacy_is_little_endian(struct tun_struct *tun)
static long tun_get_vnet_be(struct tun_struct *tun, int __user *argp)
static long tun_set_vnet_be(struct tun_struct *tun, int __user *argp)
return 0; } static inline bool tun_legacy_is_little_endian(struct tun_struct *tun)
static long tun_get_vnet_be(struct tun_struct *tun, int __user *argp)
static long tun_set_vnet_be(struct tun_struct *tun, int __user *argp)
static inline bool tun_is_little_endian(struct tun_struct *tun)
static inline u16 tun16_to_cpu(struct tun_struct *tun, __virtio16 val)
static inline __virtio16 cpu_to_tun16(struct tun_struct *tun, u16 val)
static inline u32 tun_hashfn(u32 rxhash)
static struct tun_flow_entry *tun_flow_find(struct hlist_head *head, u32 rxhash)
static struct tun_flow_entry *tun_flow_create(struct tun_struct *tun, struct hlist_head *head, u32 rxhash, u16 queue_index)
static void tun_flow_delete(struct tun_struct *tun, struct tun_flow_entry *e)
static void tun_flow_flush(struct tun_struct *tun)
static void tun_flow_delete_by_queue(struct tun_struct *tun, u16 queue_index)
static void tun_flow_cleanup(struct timer_list *t)
static void tun_flow_update(struct tun_struct *tun, u32 rxhash, struct tun_file *tfile)
static inline void tun_flow_save_rps_rxhash(struct tun_flow_entry *e, u32 hash)
static u16 tun_automq_select_queue(struct tun_struct *tun, struct sk_buff *skb)
static u16 tun_ebpf_select_queue(struct tun_struct *tun, struct sk_buff *skb)
static u16 tun_select_queue(struct net_device *dev, struct sk_buff *skb, struct net_device *sb_dev, select_queue_fallback_t fallback)
static inline bool tun_not_capable(struct tun_struct *tun)
static void tun_set_real_num_queues(struct tun_struct *tun)
static void tun_disable_queue(struct tun_struct *tun, struct tun_file *tfile)
static struct tun_struct *tun_enable_queue(struct tun_file *tfile)
void tun_ptr_free(void *ptr)
static void tun_queue_purge(struct tun_file *tfile)
static void __tun_detach(struct tun_file *tfile, bool clean)
static void tun_detach(struct tun_file *tfile, bool clean)
static void tun_detach_all(struct net_device *dev)
static int tun_attach(struct tun_struct *tun, struct file *file, bool skip_filter, bool napi, bool napi_frags)
static struct tun_struct *tun_get(struct tun_file *tfile)
static void tun_put(struct tun_struct *tun)
static void addr_hash_set(u32 *mask, const u8 *addr)
static unsigned int addr_hash_test(const u32 *mask, const u8 *addr)
static int update_filter(struct tap_filter *filter, void __user *arg)
static int run_filter(struct tap_filter *filter, const struct sk_buff *skb)
static int check_filter(struct tap_filter *filter, const struct sk_buff *skb)
static void tun_net_uninit(struct net_device *dev)
static int tun_net_open(struct net_device *dev)
static int tun_net_close(struct net_device *dev)
static void tun_automq_xmit(struct tun_struct *tun, struct sk_buff *skb)
static unsigned int run_ebpf_filter(struct tun_struct *tun, struct sk_buff *skb, int len)
static netdev_tx_t tun_net_xmit(struct sk_buff *skb, struct net_device *dev)
static void tun_net_mclist(struct net_device *dev)
static netdev_features_t tun_net_fix_features(struct net_device *dev, netdev_features_t features)
static void tun_set_headroom(struct net_device *dev, int new_hr)
static void tun_net_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
static int tun_xdp_set(struct net_device *dev, struct bpf_prog *prog, struct netlink_ext_ack *extack)
static u32 tun_xdp_query(struct net_device *dev)
static int tun_xdp(struct net_device *dev, struct netdev_bpf *xdp)
static int tun_net_change_carrier(struct net_device *dev, bool new_carrier)
static void __tun_xdp_flush_tfile(struct tun_file *tfile)
static int tun_xdp_xmit(struct net_device *dev, int n, struct xdp_frame **frames, u32 flags)
static int tun_xdp_tx(struct net_device *dev, struct xdp_buff *xdp)
static void tun_flow_init(struct tun_struct *tun)
static void tun_flow_uninit(struct tun_struct *tun)
static void tun_net_init(struct net_device *dev)
static bool tun_sock_writeable(struct tun_struct *tun, struct tun_file *tfile)
static __poll_t tun_chr_poll(struct file *file, poll_table *wait)
static struct sk_buff *tun_napi_alloc_frags(struct tun_file *tfile, size_t len, const struct iov_iter *it)
static struct sk_buff *tun_alloc_skb(struct tun_file *tfile, size_t prepad, size_t len, size_t linear, int noblock)
static void tun_rx_batched(struct tun_struct *tun, struct tun_file *tfile, struct sk_buff *skb, int more)
static bool tun_can_build_skb(struct tun_struct *tun, struct tun_file *tfile, int len, int noblock, bool zerocopy)
static struct sk_buff *__tun_build_skb(struct page_frag *alloc_frag, char *buf, int buflen, int len, int pad)
static int tun_xdp_act(struct tun_struct *tun, struct bpf_prog *xdp_prog, struct xdp_buff *xdp, u32 act)
static struct sk_buff *tun_build_skb(struct tun_struct *tun, struct tun_file *tfile, struct iov_iter *from, struct virtio_net_hdr *hdr, int len, int *skb_xdp)
static ssize_t tun_get_user(struct tun_struct *tun, struct tun_file *tfile, void *msg_control, struct iov_iter *from, int noblock, bool more)
static ssize_t tun_chr_write_iter(struct kiocb *iocb, struct iov_iter *from)
static ssize_t tun_put_user_xdp(struct tun_struct *tun, struct tun_file *tfile, struct xdp_frame *xdp_frame, struct iov_iter *iter)
static ssize_t tun_put_user(struct tun_struct *tun, struct tun_file *tfile, struct sk_buff *skb, struct iov_iter *iter)
static void *tun_ring_recv(struct tun_file *tfile, int noblock, int *err)
static ssize_t tun_do_read(struct tun_struct *tun, struct tun_file *tfile, struct iov_iter *to, int noblock, void *ptr)
static ssize_t tun_chr_read_iter(struct kiocb *iocb, struct iov_iter *to)
static void tun_prog_free(struct rcu_head *rcu)
static int __tun_set_ebpf(struct tun_struct *tun, struct tun_prog __rcu **prog_p, struct bpf_prog *prog)
static void tun_free_netdev(struct net_device *dev)
static void tun_setup(struct net_device *dev)
static int tun_validate(struct nlattr *tb[], struct nlattr *data[], struct netlink_ext_ack *extack)
static size_t tun_get_size(const struct net_device *dev)
static int tun_fill_info(struct sk_buff *skb, const struct net_device *dev)
static void tun_sock_write_space(struct sock *sk)
static void tun_put_page(struct tun_page *tpage)
static int tun_xdp_one(struct tun_struct *tun, struct tun_file *tfile, struct xdp_buff *xdp, int *flush, struct tun_page *tpage)
static int tun_sendmsg(struct socket *sock, struct msghdr *m, size_t total_len)
static int tun_recvmsg(struct socket *sock, struct msghdr *m, size_t total_len, int flags)
static int tun_ptr_peek_len(void *ptr)
static int tun_peek_len(struct socket *sock)
static int tun_flags(struct tun_struct *tun)
static ssize_t tun_show_flags(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t tun_show_owner(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t tun_show_group(struct device *dev, struct device_attribute *attr, char *buf)
static int tun_set_iff(struct net *net, struct file *file, struct ifreq *ifr)
static void tun_get_iff(struct net *net, struct tun_struct *tun, struct ifreq *ifr)
static int set_offload(struct tun_struct *tun, unsigned long arg)
static void tun_detach_filter(struct tun_struct *tun, int n)
static int tun_attach_filter(struct tun_struct *tun)
static void tun_set_sndbuf(struct tun_struct *tun)
static int tun_set_queue(struct file *file, struct ifreq *ifr)
static int tun_set_ebpf(struct tun_struct *tun, struct tun_prog **prog_p, void __user *data)
static long __tun_chr_ioctl(struct file *file, unsigned int cmd, unsigned long arg, int ifreq_len)
static long tun_chr_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long tun_chr_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static int tun_chr_fasync(int fd, struct file *file, int on)
static int tun_chr_open(struct inode *inode, struct file * file)
static int tun_chr_close(struct inode *inode, struct file *file)
static void tun_chr_show_fdinfo(struct seq_file *m, struct file *file)
static void tun_default_link_ksettings(struct net_device *dev, struct ethtool_link_ksettings *cmd)
static int tun_get_link_ksettings(struct net_device *dev, struct ethtool_link_ksettings *cmd)
static int tun_set_link_ksettings(struct net_device *dev, const struct ethtool_link_ksettings *cmd)
static void tun_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
static u32 tun_get_msglevel(struct net_device *dev)
static void tun_set_msglevel(struct net_device *dev, u32 value)
static int tun_get_coalesce(struct net_device *dev, struct ethtool_coalesce *ec)
static int tun_set_coalesce(struct net_device *dev, struct ethtool_coalesce *ec)
static int tun_queue_resize(struct tun_struct *tun)
static int tun_device_event(struct notifier_block *unused, unsigned long event, void *ptr)
static int __init tun_init(void)
static void tun_cleanup(void)
struct socket *tun_get_socket(struct file *file)
struct ptr_ring *tun_get_tx_ring(struct file *file)
\n
     45 struct tun_struct *tun
     27 struct net_device *dev
     23 struct tun_file *tfile
     12 struct file *file
      9 struct sk_buff *skb
      7 void *ptr
      5 int noblock
      4 unsigned long arg
      4 u32 rxhash
      4 int __user *argp
      4 int len
      4 char *buf
      3 unsigned int cmd
      3 struct xdp_buff *xdp
      3 struct tap_filter *filter
      3 struct socket *sock
      3 struct iov_iter *from
      3 struct ifreq *ifr
      3 struct device *dev
      3 struct device_attribute *attr
      2 void
      2 u16 queue_index
      2 struct tun_page *tpage
      2 struct tun_flow_entry *e
      2 struct net *net
      2 struct netlink_ext_ack *extack
      2 struct napi_struct *napi
      2 struct msghdr *m
      2 struct kiocb *iocb
      2 struct iov_iter *to
      2 struct iov_iter *iter
      2 struct inode *inode
      2 struct hlist_head *head
      2 struct ethtool_link_ksettings *cmd
      2 struct ethtool_coalesce *ec
      2 struct bpf_prog *prog
      2 size_t total_len
      2 size_t len
      2 int n
      2 int budget
      2 const u8 *addr
      2 const struct sk_buff *skb
      2 const struct net_device *dev
      2 bool napi_frags
      2 bool clean
      1 void __user *data
      1 void __user *arg
      1 void *msg_control
      1 __virtio16 val
      1 unsigned long event
      1 u32 value
      1 u32 *mask
      1 u32 hash
      1 u32 flags
      1 u32 act
      1 u16 val
      1 tun_ptr_free
      1 tun_get_tx_ring
      1 tun_get_socket
      1 struct xdp_frame *xdp_frame
      1 struct xdp_frame **frames
      1 struct virtio_net_hdr *hdr
      1 struct tun_prog __rcu **prog_p
      1 struct tun_prog **prog_p
      1 struct timer_list *t
      1 struct sock *sk
      1 struct seq_file *m
      1 struct rtnl_link_stats64 *stats
      1 struct rcu_head *rcu
      1 struct page_frag *alloc_frag
      1 struct notifier_block *unused
      1 struct nlattr *tb[]
      1 struct nlattr *data[]
      1 struct net_device *sb_dev
      1 struct netdev_bpf *xdp
      1 struct file * file
      1 struct ethtool_drvinfo *info
      1 struct bpf_prog *xdp_prog
      1 size_t prepad
      1 size_t linear
      1 select_queue_fallback_t fallback
      1 poll_table *wait
      1 netdev_features_t features
      1 int *skb_xdp
      1 int pad
      1 int on
      1 int new_hr
      1 int more
      1 int ifreq_len
      1 int *flush
      1 int flags
      1 int fd
      1 int *err
      1 int buflen
      1 const u32 *mask
      1 const struct tun_file *tfile
      1 const struct iov_iter *it
      1 const struct ethtool_link_ksettings *cmd
      1 bool zerocopy
      1 bool skip_filter
      1 bool new_carrier
      1 bool napi_en
      1 bool napi
      1 bool more
