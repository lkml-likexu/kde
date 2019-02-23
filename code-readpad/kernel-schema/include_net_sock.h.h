
\n
define SOCK_DEBUGGINGprintk(KERN_DEBUG msg)
; } while (0)
static inline __printf(2, 3)
void SOCK_DEBUG(const struct sock *sk, const char *msg, ...)
static inline int sk_peek_offset(struct sock *sk, int flags)
static inline void sk_peek_offset_bwd(struct sock *sk, int val)
static inline void sk_peek_offset_fwd(struct sock *sk, int val)
static inline struct sock *sk_entry(const struct hlist_node *node)
static inline struct sock *__sk_head(const struct hlist_head *head)
static inline struct sock *sk_head(const struct hlist_head *head)
static inline struct sock *__sk_nulls_head(const struct hlist_nulls_head *head)
static inline struct sock *sk_nulls_head(const struct hlist_nulls_head *head)
static inline struct sock *sk_next(const struct sock *sk)
static inline struct sock *sk_nulls_next(const struct sock *sk)
static inline bool sk_unhashed(const struct sock *sk)
static inline bool sk_hashed(const struct sock *sk)
static inline void sk_node_init(struct hlist_node *node)
static inline void sk_nulls_node_init(struct hlist_nulls_node *node)
static inline void __sk_del_node(struct sock *sk)
static inline bool __sk_del_node_init(struct sock *sk)
static __always_inline void sock_hold(struct sock *sk)
static __always_inline void __sock_put(struct sock *sk)
static inline bool sk_del_node_init(struct sock *sk)
static inline bool __sk_nulls_del_node_init_rcu(struct sock *sk)
static inline bool sk_nulls_del_node_init_rcu(struct sock *sk)
static inline void __sk_add_node(struct sock *sk, struct hlist_head *list)
static inline void sk_add_node(struct sock *sk, struct hlist_head *list)
static inline void sk_add_node_rcu(struct sock *sk, struct hlist_head *list)
static inline void __sk_nulls_add_node_rcu(struct sock *sk, struct hlist_nulls_head *list)
static inline void sk_nulls_add_node_rcu(struct sock *sk, struct hlist_nulls_head *list)
static inline void __sk_del_bind_node(struct sock *sk)
static inline void sk_add_bind_node(struct sock *sk, struct hlist_head *list)
static inline struct user_namespace *sk_user_ns(struct sock *sk)
static inline void sock_copy_flags(struct sock *nsk, struct sock *osk)
static inline void sock_set_flag(struct sock *sk, enum sock_flags flag)
static inline void sock_reset_flag(struct sock *sk, enum sock_flags flag)
static inline bool sock_flag(const struct sock *sk, enum sock_flags flag)
DECLARE_STATIC_KEY_FALSE(memalloc_socks_key)
; static inline int sk_memalloc_socks(void)
static inline int sk_memalloc_socks(void)
static inline gfp_t sk_gfp_mask(const struct sock *sk, gfp_t gfp_mask)
static inline void sk_acceptq_removed(struct sock *sk)
static inline void sk_acceptq_added(struct sock *sk)
static inline bool sk_acceptq_is_full(const struct sock *sk)
static inline int sk_stream_min_wspace(const struct sock *sk)
static inline int sk_stream_wspace(const struct sock *sk)
static inline void __sk_add_backlog(struct sock *sk, struct sk_buff *skb)
static inline bool sk_rcvqueues_full(const struct sock *sk, unsigned int limit)
static inline __must_check int sk_add_backlog(struct sock *sk, struct sk_buff *skb, unsigned int limit)
static inline int sk_backlog_rcv(struct sock *sk, struct sk_buff *skb)
static inline void sk_incoming_cpu_update(struct sock *sk)
static inline void sock_rps_record_flow_hash(__u32 hash)
static inline void sock_rps_record_flow(const struct sock *sk)
static inline void sock_rps_save_rxhash(struct sock *sk, const struct sk_buff *skb)
static inline void sock_rps_reset_rxhash(struct sock *sk)
static inline bool sk_flush_backlog(struct sock *sk)
static inline void sk_prot_clear_nulls(struct sock *sk, int size)
static inline void sk_refcnt_debug_inc(struct sock *sk)
static inline void sk_refcnt_debug_dec(struct sock *sk)
static inline void sk_refcnt_debug_release(const struct sock *sk)
static inline bool __sk_stream_memory_free(const struct sock *sk, int wake)
static inline bool sk_stream_memory_free(const struct sock *sk)
static inline bool __sk_stream_is_writeable(const struct sock *sk, int wake)
static inline bool sk_stream_is_writeable(const struct sock *sk)
static inline int sk_under_cgroup_hierarchy(struct sock *sk, struct cgroup *ancestor)
static inline bool sk_has_memory_pressure(const struct sock *sk)
static inline bool sk_under_memory_pressure(const struct sock *sk)
static inline long sk_memory_allocated(const struct sock *sk)
static inline long sk_memory_allocated_add(struct sock *sk, int amt)
static inline void sk_memory_allocated_sub(struct sock *sk, int amt)
static inline void sk_sockets_allocated_dec(struct sock *sk)
static inline void sk_sockets_allocated_inc(struct sock *sk)
static inline u64 sk_sockets_allocated_read_positive(struct sock *sk)
static inline int proto_sockets_allocated_sum_positive(struct proto *prot)
static inline long proto_memory_allocated(struct proto *prot)
static inline bool proto_memory_pressure(struct proto *prot)
void sock_prot_inuse_add(struct net *net, struct proto *prot, int inc)
; int sock_prot_inuse_get(struct net *net, struct proto *proto)
; int sock_inuse_get(struct net *net)
; static inline void sock_prot_inuse_add(struct net *net, struct proto *prot, int inc)
static inline int __sk_prot_rehash(struct sock *sk)
static inline struct socket *SOCKET_I(struct inode *inode)
static inline struct inode *SOCK_INODE(struct socket *socket)
static inline long sk_prot_mem_limits(const struct sock *sk, int index)
static inline int sk_mem_pages(int amt)
static inline bool sk_has_account(struct sock *sk)
static inline bool sk_wmem_schedule(struct sock *sk, int size)
static inline bool sk_rmem_schedule(struct sock *sk, struct sk_buff *skb, int size)
static inline void sk_mem_reclaim(struct sock *sk)
static inline void sk_mem_reclaim_partial(struct sock *sk)
static inline void sk_mem_charge(struct sock *sk, int size)
static inline void sk_mem_uncharge(struct sock *sk, int size)
static inline void sk_wmem_free_skb(struct sock *sk, struct sk_buff *skb)
static inline void sock_release_ownership(struct sock *sk)
static inline bool lockdep_sock_is_held(const struct sock *sk)
static inline void lock_sock(struct sock *sk)
bool lock_sock_fast(struct sock *sk)
;static inline void unlock_sock_fast(struct sock *sk, bool slow)
static inline void sock_owned_by_me(const struct sock *sk)
static inline bool sock_owned_by_user(const struct sock *sk)
static inline bool sock_owned_by_user_nocheck(const struct sock *sk)
static inline bool sock_allow_reclassification(const struct sock *csk)
static inline void sockcm_init(struct sockcm_cookie *sockc, const struct sock *sk)
static inline void sock_put(struct sock *sk)
int __sk_receive_skb(struct sock *sk, struct sk_buff *skb, const int nested, unsigned int trim_cap, bool refcounted)
; static inline int sk_receive_skb(struct sock *sk, struct sk_buff *skb, const int nested)
static inline void sk_tx_queue_set(struct sock *sk, int tx_queue)
static inline void sk_tx_queue_clear(struct sock *sk)
static inline int sk_tx_queue_get(const struct sock *sk)
static inline void sk_rx_queue_set(struct sock *sk, const struct sk_buff *skb)
static inline void sk_rx_queue_clear(struct sock *sk)
static inline int sk_rx_queue_get(const struct sock *sk)
static inline void sk_set_socket(struct sock *sk, struct socket *sock)
static inline wait_queue_head_t *sk_sleep(struct sock *sk)
static inline wait_queue_head_t *sk_sleep(struct sock *sk)
BUILD_BUG_ON(offsetof(struct socket_wq, wait)
!= 0)
;return &rcu_dereference_raw(sk->sk_wq)
->wait; }static inline void sock_orphan(struct sock *sk)
static inline void sock_graft(struct sock *sk, struct socket *parent)
static inline kuid_t sock_net_uid(const struct net *net, const struct sock *sk)
static inline u32 net_tx_rndhash(void)
static inline void sk_set_txhash(struct sock *sk)
static inline void sk_rethink_txhash(struct sock *sk)
static inline struct dst_entry * __sk_dst_get(struct sock *sk)
static inline struct dst_entry * sk_dst_get(struct sock *sk)
static inline void dst_negative_advice(struct sock *sk)
static inline void __sk_dst_set(struct sock *sk, struct dst_entry *dst)
static inline void sk_dst_set(struct sock *sk, struct dst_entry *dst)
static inline void __sk_dst_reset(struct sock *sk)
static inline void sk_dst_reset(struct sock *sk)
static inline void sk_dst_confirm(struct sock *sk)
static inline void sock_confirm_neigh(struct sk_buff *skb, struct neighbour *n)
static inline bool sk_can_gso(const struct sock *sk)
static inline void sk_nocaps_add(struct sock *sk, netdev_features_t flags)
static inline int skb_do_copy_data_nocache(struct sock *sk, struct sk_buff *skb, struct iov_iter *from, char *to, int copy, int offset)
static inline int skb_add_data_nocache(struct sock *sk, struct sk_buff *skb, struct iov_iter *from, int copy)
static inline int skb_copy_to_page_nocache(struct sock *sk, struct iov_iter *from, struct sk_buff *skb, struct page *page, int off, int copy)
static inline int sk_wmem_alloc_get(const struct sock *sk)
static inline int sk_rmem_alloc_get(const struct sock *sk)
static inline bool sk_has_allocations(const struct sock *sk)
static inline bool skwq_has_sleeper(struct socket_wq *wq)
static inline void sock_poll_wait(struct file *filp, struct socket *sock, poll_table *p)
static inline void skb_set_hash_from_sk(struct sk_buff *skb, struct sock *sk)
static inline void skb_set_owner_r(struct sk_buff *skb, struct sock *sk)
static inline int sock_error(struct sock *sk)
static inline unsigned long sock_wspace(struct sock *sk)
static inline void sk_set_bit(int nr, struct sock *sk)
static inline void sk_clear_bit(int nr, struct sock *sk)
static inline void sk_wake_async(const struct sock *sk, int how, int band)
static inline void sk_stream_moderate_sndbuf(struct sock *sk)
static inline struct page_frag *sk_page_frag(struct sock *sk)
static inline bool sock_writeable(const struct sock *sk)
static inline gfp_t gfp_any(void)
static inline long sock_rcvtimeo(const struct sock *sk, bool noblock)
static inline long sock_sndtimeo(const struct sock *sk, bool noblock)
static inline int sock_rcvlowat(const struct sock *sk, int waitall, int len)
static inline int sock_intr_errno(long timeo)
static inline void sock_skb_set_dropcount(const struct sock *sk, struct sk_buff *skb)
static inline void sk_drops_add(struct sock *sk, const struct sk_buff *skb)
static inline ktime_t sock_read_timestamp(struct sock *sk)
static inline void sock_write_timestamp(struct sock *sk, ktime_t kt)
static inline void sock_recv_timestamp(struct msghdr *msg, struct sock *sk, struct sk_buff *skb)
define SK_DEFAULT_STAMP (-1L * NSEC_PER_SEC)
static inline void sock_recv_ts_and_drops(struct msghdr *msg, struct sock *sk, struct sk_buff *skb)
static inline void _sock_tx_timestamp(struct sock *sk, __u16 tsflags, __u8 *tx_flags, __u32 *tskey)
static inline void sock_tx_timestamp(struct sock *sk, __u16 tsflags, __u8 *tx_flags)
static inline void skb_setup_tx_timestamp(struct sk_buff *skb, __u16 tsflags)
static inline void sk_eat_skb(struct sock *sk, struct sk_buff *skb)
static inline struct net *sock_net(const struct sock *sk)
static inline void sock_net_set(struct sock *sk, struct net *net)
static inline struct sock *skb_steal_sock(struct sk_buff *skb)
static inline bool sk_fullsock(const struct sock *sk)
static inline struct sk_buff *sk_validate_xmit_skb(struct sk_buff *skb, struct net_device *dev)
static inline bool sk_listener(const struct sock *sk)
static inline int sk_get_wmem0(const struct sock *sk, const struct proto *proto)
static inline int sk_get_rmem0(const struct sock *sk, const struct proto *proto)
static inline void sk_pacing_shift_update(struct sock *sk, int val)
static inline bool sk_dev_equal_l3scope(struct sock *sk, int dif)
\n
     96 struct sock *sk
     44 const struct sock *sk
     20 struct sk_buff *skb
      5 struct proto *prot
      5 struct net *net
      5 int size
      4 void
      4 struct hlist_head *list
      3 __u16 tsflags
      3 struct iov_iter *from
      3 int val
      3 int copy
      3 int amt
      3 enum sock_flags flag
      3 const struct sk_buff *skb
      2 unsigned int limit
      2 __u8 *tx_flags
      2 struct socket *sock
      2 struct msghdr *msg
      2 struct hlist_nulls_head *list
      2 struct dst_entry *dst
      2 int wake
      2 int nr
      2 int inc
      2 const struct proto *proto
      2 const struct hlist_nulls_head *head
      2 const struct hlist_head *head
      2 const int nested
      2 bool noblock
      1 wait
      1 unsigned int trim_cap
      1 __u32 *tskey
      1 __u32 hash
      1 struct sock *osk
      1 struct sock *nsk
      1 struct socket_wq *wq
      1 struct socket *socket
      1 struct socket *parent
      1 struct sockcm_cookie *sockc
      1 struct proto *proto
      1 struct page *page
      1 struct net_device *dev
      1 struct neighbour *n
      1 struct inode *inode
      1 struct hlist_nulls_node *node
      1 struct hlist_node *node
      1 struct file *filp
      1 struct cgroup *ancestor
      1 sk->sk_wq
      1 poll_table *p
      1 offsetofstruct socket_wq
      1 netdev_features_t flags
      1 memalloc_socks_key
      1 long timeo
      1 ktime_t kt
      1 KERN_DEBUG msg
      1 int waitall
      1 int tx_queue
      1 int offset
      1 int off
      1 int len
      1 int index
      1 int how
      1 int flags
      1 int dif
      1 int band
      1 gfp_t gfp_mask
      1 const struct sock *csk
      1 const struct net *net
      1 const struct hlist_node *node
      1 const char *msg
      1 char *to
      1 bool slow
      1 bool refcounted
      1 3
      1 2
      1 -1L * NSEC_PER_SEC
      1 0
      1 ...
