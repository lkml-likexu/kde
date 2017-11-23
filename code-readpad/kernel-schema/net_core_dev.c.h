
EXPORT_SYMBOL_GPL(dev_fill_metadata_dst);
EXPORT_SYMBOL_GPL(netdev_cmd_to_name);
EXPORT_SYMBOL_GPL(net_inc_ingress_queue);
EXPORT_SYMBOL_GPL(net_dec_ingress_queue);
EXPORT_SYMBOL_GPL(net_inc_egress_queue);
EXPORT_SYMBOL_GPL(net_dec_egress_queue);
EXPORT_SYMBOL_GPL(is_skb_forwardable);
EXPORT_SYMBOL_GPL(__dev_forward_skb);
EXPORT_SYMBOL_GPL(dev_forward_skb);
EXPORT_SYMBOL_GPL(dev_nit_active);
EXPORT_SYMBOL_GPL(dev_queue_xmit_nit);
EXPORT_SYMBOL_GPL(__netif_set_xps_queue);
EXPORT_SYMBOL_GPL(validate_xmit_skb_list);
EXPORT_SYMBOL_GPL(generic_xdp_tx);
EXPORT_SYMBOL_GPL(do_xdp_generic);
EXPORT_SYMBOL_GPL(br_fdb_test_addr_hook);
EXPORT_SYMBOL_GPL(netdev_is_rx_handler_busy);
EXPORT_SYMBOL_GPL(netdev_rx_handler_register);
EXPORT_SYMBOL_GPL(netdev_rx_handler_unregister);
EXPORT_SYMBOL_GPL(napi_hash_del);
EXPORT_SYMBOL_GPL(netdev_walk_all_upper_dev_rcu);
EXPORT_SYMBOL_GPL(netdev_walk_all_lower_dev);
EXPORT_SYMBOL_GPL(netdev_walk_all_lower_dev_rcu);
EXPORT_SYMBOL_GPL(init_dummy_netdev);
EXPORT_SYMBOL_GPL(netdev_set_default_ethtool_ops);
EXPORT_SYMBOL_GPL(dev_change_net_namespace);
static inline void dev_base_seq_inc(struct net *net)
static inline struct hlist_head *dev_name_hash(struct net *net, const char *name)
static inline struct hlist_head *dev_index_hash(struct net *net, int ifindex)
static inline void rps_lock(struct softnet_data *sd)
static inline void rps_unlock(struct softnet_data *sd)
static void list_netdevice(struct net_device *dev)
static void unlist_netdevice(struct net_device *dev)
static inline unsigned short netdev_lock_pos(unsigned short dev_type)
static inline void netdev_set_xmit_lockdep_class(spinlock_t *lock, unsigned short dev_type)
static inline void netdev_set_addr_lockdep_class(struct net_device *dev)
i = netdev_lock_pos(dev->type)
;lockdep_set_class_and_name(&dev->addr_list_lock, &netdev_addr_lock_key[i], netdev_lock_name[i])
; } static inline void netdev_set_xmit_lockdep_class(spinlock_t *lock, unsigned short dev_type)
i = netdev_lock_pos(dev->type)
;lockdep_set_class_and_name(&dev->addr_list_lock, &netdev_addr_lock_key[i], netdev_lock_name[i])
; } static inline void netdev_set_xmit_lockdep_class(spinlock_t *lock, unsigned short dev_type)
} static inline void netdev_set_addr_lockdep_class(struct net_device *dev)
static inline struct list_head *ptype_head(const struct packet_type *pt)
void dev_add_pack(struct packet_type *pt)
void __dev_remove_pack(struct packet_type *pt)
void dev_remove_pack(struct packet_type *pt)
void dev_add_offload(struct packet_offload *po)
static void __dev_remove_offload(struct packet_offload *po)
void dev_remove_offload(struct packet_offload *po)
static int netdev_boot_setup_add(char *name, struct ifmap *map)
int netdev_boot_setup_check(struct net_device *dev)
unsigned long netdev_boot_base(const char *prefix, int unit)
int __init netdev_boot_setup(char *str)
int dev_get_iflink(const struct net_device *dev)
int dev_fill_metadata_dst(struct net_device *dev, struct sk_buff *skb)
struct net_device *__dev_get_by_name(struct net *net, const char *name)
struct net_device *dev_get_by_name_rcu(struct net *net, const char *name)
struct net_device *dev_get_by_name(struct net *net, const char *name)
struct net_device *__dev_get_by_index(struct net *net, int ifindex)
struct net_device *dev_get_by_index_rcu(struct net *net, int ifindex)
struct net_device *dev_get_by_index(struct net *net, int ifindex)
struct net_device *dev_get_by_napi_id(unsigned int napi_id)
int netdev_get_name(struct net *net, char *name, int ifindex)
struct net_device *dev_getbyhwaddr_rcu(struct net *net, unsigned short type, const char *ha)
struct net_device *__dev_getfirstbyhwtype(struct net *net, unsigned short type)
struct net_device *dev_getfirstbyhwtype(struct net *net, unsigned short type)
struct net_device *__dev_get_by_flags(struct net *net, unsigned short if_flags, unsigned short mask)
bool dev_valid_name(const char *name)
static int __dev_alloc_name(struct net *net, const char *name, char *buf)
static int dev_alloc_name_ns(struct net *net, struct net_device *dev, const char *name)
int dev_alloc_name(struct net_device *dev, const char *name)
int dev_get_valid_name(struct net *net, struct net_device *dev, const char *name)
int dev_change_name(struct net_device *dev, const char *newname)
int dev_set_alias(struct net_device *dev, const char *alias, size_t len)
int dev_get_alias(const struct net_device *dev, char *name, size_t len)
void netdev_features_change(struct net_device *dev)
void netdev_state_change(struct net_device *dev)
void netdev_notify_peers(struct net_device *dev)
static int __dev_open(struct net_device *dev)
int dev_open(struct net_device *dev)
static void __dev_close_many(struct list_head *head)
static void __dev_close(struct net_device *dev)
void dev_close_many(struct list_head *head, bool unlink)
void dev_close(struct net_device *dev)
void dev_disable_lro(struct net_device *dev)
static void dev_disable_gro_hw(struct net_device *dev)
const char *netdev_cmd_to_name(enum netdev_cmd cmd)
static int call_netdevice_notifier(struct notifier_block *nb, unsigned long val, struct net_device *dev)
int register_netdevice_notifier(struct notifier_block *nb)
int unregister_netdevice_notifier(struct notifier_block *nb)
static int call_netdevice_notifiers_info(unsigned long val, struct netdev_notifier_info *info)
int call_netdevice_notifiers(unsigned long val, struct net_device *dev)
static int call_netdevice_notifiers_mtu(unsigned long val, struct net_device *dev, u32 arg)
void net_inc_ingress_queue(void)
void net_dec_ingress_queue(void)
void net_inc_egress_queue(void)
void net_dec_egress_queue(void)
static DEFINE_STATIC_KEY_FALSE(netstamp_needed_key)
; static atomic_t netstamp_needed_deferred; static atomic_t netstamp_wanted; static void netstamp_clear(struct work_struct *work)
void net_enable_timestamp(void)
void net_disable_timestamp(void)
static inline void net_timestamp_set(struct sk_buff *skb)
bool is_skb_forwardable(const struct net_device *dev, const struct sk_buff *skb)
int __dev_forward_skb(struct net_device *dev, struct sk_buff *skb)
int dev_forward_skb(struct net_device *dev, struct sk_buff *skb)
static inline int deliver_skb(struct sk_buff *skb, struct packet_type *pt_prev, struct net_device *orig_dev)
static inline void deliver_ptype_list_skb(struct sk_buff *skb, struct packet_type **pt, struct net_device *orig_dev, __be16 type, struct list_head *ptype_list)
static inline bool skb_loop_sk(struct packet_type *ptype, struct sk_buff *skb)
bool dev_nit_active(struct net_device *dev)
void dev_queue_xmit_nit(struct sk_buff *skb, struct net_device *dev)
static void netif_setup_tc(struct net_device *dev, unsigned int txq)
int netdev_txq_to_tc(struct net_device *dev, unsigned int txq)
static bool remove_xps_queue(struct xps_dev_maps *dev_maps, int tci, u16 index)
static bool remove_xps_queue_cpu(struct net_device *dev, struct xps_dev_maps *dev_maps, int cpu, u16 offset, u16 count)
static void clean_xps_maps(struct net_device *dev, const unsigned long *mask, struct xps_dev_maps *dev_maps, unsigned int nr_ids, u16 offset, u16 count, bool is_rxqs_map)
static void netif_reset_xps_queues(struct net_device *dev, u16 offset, u16 count)
static void netif_reset_xps_queues_gt(struct net_device *dev, u16 index)
static struct xps_map *expand_xps_map(struct xps_map *map, int attr_index, u16 index, bool is_rxqs_map)
int __netif_set_xps_queue(struct net_device *dev, const unsigned long *mask, u16 index, bool is_rxqs_map)
int netif_set_xps_queue(struct net_device *dev, const struct cpumask *mask, u16 index)
endif static void netdev_unbind_all_sb_channels(struct net_device *dev)
void netdev_reset_tc(struct net_device *dev)
int netdev_set_tc_queue(struct net_device *dev, u8 tc, u16 count, u16 offset)
int netdev_set_num_tc(struct net_device *dev, u8 num_tc)
void netdev_unbind_sb_channel(struct net_device *dev, struct net_device *sb_dev)
int netdev_bind_sb_channel_queue(struct net_device *dev, struct net_device *sb_dev, u8 tc, u16 count, u16 offset)
int netdev_set_sb_channel(struct net_device *dev, u16 channel)
int netif_set_real_num_tx_queues(struct net_device *dev, unsigned int txq)
int netif_set_real_num_rx_queues(struct net_device *dev, unsigned int rxq)
int netif_get_num_default_rss_queues(void)
static void __netif_reschedule(struct Qdisc *q)
void __netif_schedule(struct Qdisc *q)
static struct dev_kfree_skb_cb *get_kfree_skb_cb(const struct sk_buff *skb)
void netif_schedule_queue(struct netdev_queue *txq)
void netif_tx_wake_queue(struct netdev_queue *dev_queue)
void __dev_kfree_skb_irq(struct sk_buff *skb, enum skb_free_reason reason)
void __dev_kfree_skb_any(struct sk_buff *skb, enum skb_free_reason reason)
void netif_device_detach(struct net_device *dev)
void netif_device_attach(struct net_device *dev)
static u16 skb_tx_hash(const struct net_device *dev, const struct net_device *sb_dev, struct sk_buff *skb)
static void skb_warn_bad_offload(const struct sk_buff *skb)
int skb_checksum_help(struct sk_buff *skb)
int skb_crc32c_csum_help(struct sk_buff *skb)
__be16 skb_network_protocol(struct sk_buff *skb, int *depth)
struct sk_buff *skb_mac_gso_segment(struct sk_buff *skb, netdev_features_t features)
static inline bool skb_needs_check(struct sk_buff *skb, bool tx_path)
struct sk_buff *__skb_gso_segment(struct sk_buff *skb, netdev_features_t features, bool tx_path)
void netdev_rx_csum_fault(struct net_device *dev)
static int illegal_highdma(struct net_device *dev, struct sk_buff *skb)
static netdev_features_t net_mpls_features(struct sk_buff *skb, netdev_features_t features, __be16 type)
return features; } static netdev_features_t net_mpls_features(struct sk_buff *skb, netdev_features_t features, __be16 type)
static netdev_features_t harmonize_features(struct sk_buff *skb, netdev_features_t features)
netdev_features_t passthru_features_check(struct sk_buff *skb, struct net_device *dev, netdev_features_t features)
static netdev_features_t dflt_features_check(struct sk_buff *skb, struct net_device *dev, netdev_features_t features)
static netdev_features_t gso_features_check(const struct sk_buff *skb, struct net_device *dev, netdev_features_t features)
netdev_features_t netif_skb_features(struct sk_buff *skb)
static int xmit_one(struct sk_buff *skb, struct net_device *dev, struct netdev_queue *txq, bool more)
struct sk_buff *dev_hard_start_xmit(struct sk_buff *first, struct net_device *dev, struct netdev_queue *txq, int *ret)
static struct sk_buff *validate_xmit_vlan(struct sk_buff *skb, netdev_features_t features)
int skb_csum_hwoffload_help(struct sk_buff *skb, const netdev_features_t features)
static struct sk_buff *validate_xmit_skb(struct sk_buff *skb, struct net_device *dev, bool *again)
struct sk_buff *validate_xmit_skb_list(struct sk_buff *skb, struct net_device *dev, bool *again)
static void qdisc_pkt_len_init(struct sk_buff *skb)
static inline int __dev_xmit_skb(struct sk_buff *skb, struct Qdisc *q, struct net_device *dev, struct netdev_queue *txq)
static void skb_update_prio(struct sk_buff *skb)
int dev_loopback_xmit(struct net *net, struct sock *sk, struct sk_buff *skb)
static struct sk_buff * sch_handle_egress(struct sk_buff *skb, int *ret, struct net_device *dev)
static int __get_xps_queue_idx(struct net_device *dev, struct sk_buff *skb, struct xps_dev_maps *dev_maps, unsigned int tci)
static int get_xps_queue(struct net_device *dev, struct net_device *sb_dev, struct sk_buff *skb)
u16 dev_pick_tx_zero(struct net_device *dev, struct sk_buff *skb, struct net_device *sb_dev, select_queue_fallback_t fallback)
u16 dev_pick_tx_cpu_id(struct net_device *dev, struct sk_buff *skb, struct net_device *sb_dev, select_queue_fallback_t fallback)
static u16 __netdev_pick_tx(struct net_device *dev, struct sk_buff *skb, struct net_device *sb_dev)
struct netdev_queue *netdev_pick_tx(struct net_device *dev, struct sk_buff *skb, struct net_device *sb_dev)
static int __dev_queue_xmit(struct sk_buff *skb, struct net_device *sb_dev)
int dev_queue_xmit(struct sk_buff *skb)
int dev_queue_xmit_accel(struct sk_buff *skb, struct net_device *sb_dev)
int dev_direct_xmit(struct sk_buff *skb, u16 queue_id)
static inline void ____napi_schedule(struct softnet_data *sd, struct napi_struct *napi)
static struct rps_dev_flow * set_rps_cpu(struct net_device *dev, struct sk_buff *skb, struct rps_dev_flow *rflow, u16 next_cpu)
static int get_rps_cpu(struct net_device *dev, struct sk_buff *skb, struct rps_dev_flow **rflowp)
bool rps_may_expire_flow(struct net_device *dev, u16 rxq_index, u32 flow_id, u16 filter_id)
static void rps_trigger_softirq(void *data)
static int rps_ipi_queued(struct softnet_data *sd)
static bool skb_flow_limit(struct sk_buff *skb, unsigned int qlen)
static int enqueue_to_backlog(struct sk_buff *skb, int cpu, unsigned int *qtail)
static struct netdev_rx_queue *netif_get_rxqueue(struct sk_buff *skb)
static u32 netif_receive_generic_xdp(struct sk_buff *skb, struct xdp_buff *xdp, struct bpf_prog *xdp_prog)
void generic_xdp_tx(struct sk_buff *skb, struct bpf_prog *xdp_prog)
int do_xdp_generic(struct bpf_prog *xdp_prog, struct sk_buff *skb)
static int netif_rx_internal(struct sk_buff *skb)
int netif_rx(struct sk_buff *skb)
int netif_rx_ni(struct sk_buff *skb)
static __latent_entropy void net_tx_action(struct softirq_action *h)
static inline struct sk_buff * sch_handle_ingress(struct sk_buff *skb, struct packet_type **pt_prev, int *ret, struct net_device *orig_dev)
bool netdev_is_rx_handler_busy(struct net_device *dev)
int netdev_rx_handler_register(struct net_device *dev, rx_handler_func_t *rx_handler, void *rx_handler_data)
void netdev_rx_handler_unregister(struct net_device *dev)
static bool skb_pfmemalloc_protocol(struct sk_buff *skb)
static inline int nf_ingress(struct sk_buff *skb, struct packet_type **pt_prev, int *ret, struct net_device *orig_dev)
static int __netif_receive_skb_core(struct sk_buff *skb, bool pfmemalloc, struct packet_type **ppt_prev)
static int __netif_receive_skb_one_core(struct sk_buff *skb, bool pfmemalloc)
int netif_receive_skb_core(struct sk_buff *skb)
static inline void __netif_receive_skb_list_ptype(struct list_head *head, struct packet_type *pt_prev, struct net_device *orig_dev)
static void __netif_receive_skb_list_core(struct list_head *head, bool pfmemalloc)
static int __netif_receive_skb(struct sk_buff *skb)
static void __netif_receive_skb_list(struct list_head *head)
static int generic_xdp_install(struct net_device *dev, struct netdev_bpf *xdp)
static int netif_receive_skb_internal(struct sk_buff *skb)
static void netif_receive_skb_list_internal(struct list_head *head)
int netif_receive_skb(struct sk_buff *skb)
void netif_receive_skb_list(struct list_head *head)
static void flush_backlog(struct work_struct *work)
static void flush_all_backlogs(void)
static int napi_gro_complete(struct sk_buff *skb)
static void __napi_gro_flush_chain(struct napi_struct *napi, u32 index, bool flush_old)
void napi_gro_flush(struct napi_struct *napi, bool flush_old)
static struct list_head *gro_list_prepare(struct napi_struct *napi, struct sk_buff *skb)
static void skb_gro_reset_offset(struct sk_buff *skb)
static void gro_pull_from_frag0(struct sk_buff *skb, int grow)
static void gro_flush_oldest(struct list_head *head)
static enum gro_result dev_gro_receive(struct napi_struct *napi, struct sk_buff *skb)
struct packet_offload *gro_find_receive_by_type(__be16 type)
struct packet_offload *gro_find_complete_by_type(__be16 type)
static void napi_skb_free_stolen_head(struct sk_buff *skb)
static gro_result_t napi_skb_finish(gro_result_t ret, struct sk_buff *skb)
gro_result_t napi_gro_receive(struct napi_struct *napi, struct sk_buff *skb)
static void napi_reuse_skb(struct napi_struct *napi, struct sk_buff *skb)
struct sk_buff *napi_get_frags(struct napi_struct *napi)
static gro_result_t napi_frags_finish(struct napi_struct *napi, struct sk_buff *skb, gro_result_t ret)
static struct sk_buff *napi_frags_skb(struct napi_struct *napi)
gro_result_t napi_gro_frags(struct napi_struct *napi)
__sum16 __skb_gro_checksum_complete(struct sk_buff *skb)
static void net_rps_send_ipi(struct softnet_data *remsd)
static void net_rps_action_and_irq_enable(struct softnet_data *sd)
static bool sd_has_rps_ipi_waiting(struct softnet_data *sd)
static int process_backlog(struct napi_struct *napi, int quota)
void __napi_schedule(struct napi_struct *n)
bool napi_schedule_prep(struct napi_struct *n)
void __napi_schedule_irqoff(struct napi_struct *n)
bool napi_complete_done(struct napi_struct *n, int work_done)
static struct napi_struct *napi_by_id(unsigned int napi_id)
static void busy_poll_stop(struct napi_struct *napi, void *have_poll_lock)
void napi_busy_loop(unsigned int napi_id, bool (*loop_end)
(void *, unsigned long)
, void *loop_end_arg)
static void napi_hash_add(struct napi_struct *napi)
bool napi_hash_del(struct napi_struct *napi)
static enum hrtimer_restart napi_watchdog(struct hrtimer *timer)
static void init_gro_hash(struct napi_struct *napi)
void netif_napi_add(struct net_device *dev, struct napi_struct *napi, int (*poll)
(struct napi_struct *, int)
, int weight)
void napi_disable(struct napi_struct *n)
static void flush_gro_hash(struct napi_struct *napi)
void netif_napi_del(struct napi_struct *napi)
static int napi_poll(struct napi_struct *n, struct list_head *repoll)
static __latent_entropy void net_rx_action(struct softirq_action *h)
static struct netdev_adjacent *__netdev_find_adj(struct net_device *adj_dev, struct list_head *adj_list)
static int __netdev_has_upper_dev(struct net_device *upper_dev, void *data)
bool netdev_has_upper_dev(struct net_device *dev, struct net_device *upper_dev)
bool netdev_has_upper_dev_all_rcu(struct net_device *dev, struct net_device *upper_dev)
bool netdev_has_any_upper_dev(struct net_device *dev)
struct net_device *netdev_master_upper_dev_get(struct net_device *dev)
static bool netdev_has_any_lower_dev(struct net_device *dev)
void *netdev_adjacent_get_private(struct list_head *adj_list)
struct net_device *netdev_upper_get_next_dev_rcu(struct net_device *dev, struct list_head **iter)
static struct net_device *netdev_next_upper_dev_rcu(struct net_device *dev, struct list_head **iter)
int netdev_walk_all_upper_dev_rcu(struct net_device *dev, int (*fn)
(struct net_device *dev, void *data)
, void *data)
void *netdev_lower_get_next_private(struct net_device *dev, struct list_head **iter)
void *netdev_lower_get_next_private_rcu(struct net_device *dev, struct list_head **iter)
void *netdev_lower_get_next(struct net_device *dev, struct list_head **iter)
static struct net_device *netdev_next_lower_dev(struct net_device *dev, struct list_head **iter)
int netdev_walk_all_lower_dev(struct net_device *dev, int (*fn)
(struct net_device *dev, void *data)
, void *data)
static struct net_device *netdev_next_lower_dev_rcu(struct net_device *dev, struct list_head **iter)
int netdev_walk_all_lower_dev_rcu(struct net_device *dev, int (*fn)
(struct net_device *dev, void *data)
, void *data)
void *netdev_lower_get_first_private_rcu(struct net_device *dev)
struct net_device *netdev_master_upper_dev_get_rcu(struct net_device *dev)
static int netdev_adjacent_sysfs_add(struct net_device *dev, struct net_device *adj_dev, struct list_head *dev_list)
sprintf(linkname, dev_list == &dev->adj_list.upper ? "upper_%s" : "lower_%s", adj_dev->name)
;return sysfs_create_link(&(dev->dev.kobj)
, &(adj_dev->dev.kobj)
, linkname)
; } static void netdev_adjacent_sysfs_del(struct net_device *dev, char *name, struct list_head *dev_list)
static inline bool netdev_adjacent_is_neigh_list(struct net_device *dev, struct net_device *adj_dev, struct list_head *dev_list)
static int __netdev_adjacent_dev_insert(struct net_device *dev, struct net_device *adj_dev, struct list_head *dev_list, void *private, bool master)
static void __netdev_adjacent_dev_remove(struct net_device *dev, struct net_device *adj_dev, u16 ref_nr, struct list_head *dev_list)
static int __netdev_adjacent_dev_link_lists(struct net_device *dev, struct net_device *upper_dev, struct list_head *up_list, struct list_head *down_list, void *private, bool master)
static void __netdev_adjacent_dev_unlink_lists(struct net_device *dev, struct net_device *upper_dev, u16 ref_nr, struct list_head *up_list, struct list_head *down_list)
static int __netdev_adjacent_dev_link_neighbour(struct net_device *dev, struct net_device *upper_dev, void *private, bool master)
static void __netdev_adjacent_dev_unlink_neighbour(struct net_device *dev, struct net_device *upper_dev)
static int __netdev_upper_dev_link(struct net_device *dev, struct net_device *upper_dev, bool master, void *upper_priv, void *upper_info, struct netlink_ext_ack *extack)
int netdev_upper_dev_link(struct net_device *dev, struct net_device *upper_dev, struct netlink_ext_ack *extack)
int netdev_master_upper_dev_link(struct net_device *dev, struct net_device *upper_dev, void *upper_priv, void *upper_info, struct netlink_ext_ack *extack)
void netdev_upper_dev_unlink(struct net_device *dev, struct net_device *upper_dev)
void netdev_bonding_info_change(struct net_device *dev, struct netdev_bonding_info *bonding_info)
static void netdev_adjacent_add_links(struct net_device *dev)
static void netdev_adjacent_del_links(struct net_device *dev)
void netdev_adjacent_rename_links(struct net_device *dev, char *oldname)
void *netdev_lower_dev_get_private(struct net_device *dev, struct net_device *lower_dev)
int dev_get_nest_level(struct net_device *dev)
void netdev_lower_state_changed(struct net_device *lower_dev, void *lower_state_info)
static void dev_change_rx_flags(struct net_device *dev, int flags)
static int __dev_set_promiscuity(struct net_device *dev, int inc, bool notify)
int dev_set_promiscuity(struct net_device *dev, int inc)
static int __dev_set_allmulti(struct net_device *dev, int inc, bool notify)
int dev_set_allmulti(struct net_device *dev, int inc)
void __dev_set_rx_mode(struct net_device *dev)
void dev_set_rx_mode(struct net_device *dev)
unsigned int dev_get_flags(const struct net_device *dev)
int __dev_change_flags(struct net_device *dev, unsigned int flags)
void __dev_notify_flags(struct net_device *dev, unsigned int old_flags, unsigned int gchanges)
int dev_change_flags(struct net_device *dev, unsigned int flags)
int __dev_set_mtu(struct net_device *dev, int new_mtu)
int dev_set_mtu_ext(struct net_device *dev, int new_mtu, struct netlink_ext_ack *extack)
int dev_set_mtu(struct net_device *dev, int new_mtu)
int dev_change_tx_queue_len(struct net_device *dev, unsigned long new_len)
void dev_set_group(struct net_device *dev, int new_group)
int dev_set_mac_address(struct net_device *dev, struct sockaddr *sa)
int dev_change_carrier(struct net_device *dev, bool new_carrier)
int dev_get_phys_port_id(struct net_device *dev, struct netdev_phys_item_id *ppid)
int dev_get_phys_port_name(struct net_device *dev, char *name, size_t len)
int dev_change_proto_down(struct net_device *dev, bool proto_down)
u32 __dev_xdp_query(struct net_device *dev, bpf_op_t bpf_op, enum bpf_netdev_command cmd)
static int dev_xdp_install(struct net_device *dev, bpf_op_t bpf_op, struct netlink_ext_ack *extack, u32 flags, struct bpf_prog *prog)
static void dev_xdp_uninstall(struct net_device *dev)
int dev_change_xdp_fd(struct net_device *dev, struct netlink_ext_ack *extack, int fd, u32 flags)
static int dev_new_index(struct net *net)
static void net_set_todo(struct net_device *dev)
static void rollback_registered_many(struct list_head *head)
static void rollback_registered(struct net_device *dev)
static netdev_features_t netdev_sync_upper_features(struct net_device *lower, struct net_device *upper, netdev_features_t features)
static void netdev_sync_lower_features(struct net_device *upper, struct net_device *lower, netdev_features_t features)
static netdev_features_t netdev_fix_features(struct net_device *dev, netdev_features_t features)
int __netdev_update_features(struct net_device *dev)
void netdev_update_features(struct net_device *dev)
void netdev_change_features(struct net_device *dev)
void netif_stacked_transfer_operstate(const struct net_device *rootdev, struct net_device *dev)
static int netif_alloc_rx_queues(struct net_device *dev)
static void netif_free_rx_queues(struct net_device *dev)
static void netdev_init_one_queue(struct net_device *dev, struct netdev_queue *queue, void *_unused)
static void netif_free_tx_queues(struct net_device *dev)
static int netif_alloc_netdev_queues(struct net_device *dev)
void netif_tx_stop_all_queues(struct net_device *dev)
int register_netdevice(struct net_device *dev)
int init_dummy_netdev(struct net_device *dev)
int register_netdev(struct net_device *dev)
int netdev_refcnt_read(const struct net_device *dev)
static void netdev_wait_allrefs(struct net_device *dev)
void netdev_run_todo(void)
void netdev_stats_to_stats64(struct rtnl_link_stats64 *stats64, const struct net_device_stats *netdev_stats)
struct rtnl_link_stats64 *dev_get_stats(struct net_device *dev, struct rtnl_link_stats64 *storage)
struct netdev_queue *dev_ingress_queue_create(struct net_device *dev)
void netdev_set_default_ethtool_ops(struct net_device *dev, const struct ethtool_ops *ops)
void netdev_freemem(struct net_device *dev)
struct net_device *alloc_netdev_mqs(int sizeof_priv, const char *name, unsigned char name_assign_type, void (*setup)
(struct net_device *)
, unsigned int txqs, unsigned int rxqs)
void free_netdev(struct net_device *dev)
void synchronize_net(void)
void unregister_netdevice_queue(struct net_device *dev, struct list_head *head)
void unregister_netdevice_many(struct list_head *head)
void unregister_netdev(struct net_device *dev)
int dev_change_net_namespace(struct net_device *dev, struct net *net, const char *pat)
static int dev_cpu_dead(unsigned int oldcpu)
netdev_features_t netdev_increment_features(netdev_features_t all, netdev_features_t one, netdev_features_t mask)
static struct hlist_head * __net_init netdev_create_hash(void)
static int __net_init netdev_init(struct net *net)
const char *netdev_drivername(const struct net_device *dev)
static void __netdev_printk(const char *level, const struct net_device *dev, struct va_format *vaf)
void netdev_printk(const char *level, const struct net_device *dev, const char *format, ...)
define define_netdev_printk_level(func, level)
\ void func(const struct net_device *dev, const char *fmt, ...)
\ static void __net_exit netdev_exit(struct net *net)
static void __net_exit default_device_exit(struct net *net)
static void __net_exit rtnl_lock_unregistering(struct list_head *net_list)
static void __net_exit default_device_exit_batch(struct list_head *net_list)
static int __init net_dev_init(void)
 159 struct net_device *dev
  75 struct sk_buff *skb
  23 struct net *net
  19 struct napi_struct *napi
  12 void
  12 netdev_features_t features
  11 struct net_device *upper_dev
  11 struct list_head *head
  10 const struct net_device *dev
  10 const char *name
   9 struct net_device *sb_dev
   7 struct list_head **iter
   6 struct softnet_data *sd
   6 struct netlink_ext_ack *extack
   6 struct napi_struct *n
   5 void *data
   5 u16 offset
   5 u16 index
   5 u16 count
   5 struct net_device *orig_dev
   5 struct net_device *adj_dev
   5 struct list_head *dev_list
   5 int ifindex
   5 char *name
   5 __be16 type
   4 unsigned short dev_type
   4 unsigned long val
   4 struct xps_dev_maps *dev_maps
   4 struct netdev_queue *txq
   4 int inc
   4 int *ret
   4 const struct sk_buff *skb
   4 bool master
   3 void *private
   3 unsigned short type
   3 unsigned int txq
   3 unsigned int napi_id
   3 struct packet_type *pt
   3 struct packet_offload *po
   3 struct notifier_block *nb
   3 struct bpf_prog *xdp_prog
   3 struct Qdisc *q
   3 spinlock_t *lock
   3 size_t len
   3 int new_mtu
   3 int *fn
   3 bool pfmemalloc
   3 bool is_rxqs_map
   2 void *upper_priv
   2 void *upper_info
   2 unsigned int flags
   2 u8 tc
   2 u32 flags
   2 u16 ref_nr
   2 struct work_struct *work
   2 struct softirq_action *h
   2 struct packet_type *pt_prev
   2 struct packet_type **pt_prev
   2 struct net_device *upper
   2 struct net_device *lower_dev
   2 struct net_device *lower
   2 struct list_head *up_list
   2 struct list_head *net_list
   2 struct list_head *down_list
   2 struct list_head *adj_list
   2 select_queue_fallback_t fallback
   2 netdev_lock_name[i]
   2 int cpu
   2 gro_result_t ret
   2 enum skb_free_reason reason
   2 dev->type
   2 const unsigned long *mask
   2 const char *level
   2 bpf_op_t bpf_op
   2 bool tx_path
   2 bool notify
   2 bool flush_old
   2 bool *again
   2 ...
   2 &netdev_addr_lock_key[i]
   2 &dev->addr_list_lock
   1 void *setup
   1 void *rx_handler_data
   1 void *lower_state_info
   1 void *have_poll_lock
   1 void *_unused
   1 void *
   1 validate_xmit_skb_list
   1 unsigned short mask
   1 unsigned short if_flags
   1 unsigned long new_len
   1 unsigned long
   1 unsigned int tci
   1 unsigned int rxq
   1 unsigned int qlen
   1 unsigned int oldcpu
   1 unsigned int old_flags
   1 unsigned int nr_ids
   1 unsigned int gchanges
   1 unsigned int *qtail
   1 unsigned char name_assign_type
   1 u8 num_tc
   1 u32 index
   1 u32 flow_id
   1 u32 arg
   1 u16 rxq_index
   1 u16 queue_id
   1 u16 next_cpu
   1 u16 filter_id
   1 u16 channel
   1 struct xps_map *map
   1 struct xdp_buff *xdp
   1 struct va_format *vaf
   1 struct softnet_data *remsd
   1 struct sockaddr *sa
   1 struct sock *sk
   1 struct sk_buff *first
   1 struct rtnl_link_stats64 *storage
   1 struct rtnl_link_stats64 *stats64
   1 struct rps_dev_flow *rflow
   1 struct rps_dev_flow **rflowp
   1 struct packet_type *ptype
   1 struct packet_type **pt
   1 struct packet_type **ppt_prev
   1 struct netdev_queue *queue
   1 struct netdev_queue *dev_queue
   1 struct netdev_phys_item_id *ppid
   1 struct netdev_notifier_info *info
   1 struct netdev_bpf *xdp
   1 struct netdev_bonding_info *bonding_info
   1 struct net_device *
   1 struct napi_struct *
   1 struct list_head *repoll
   1 struct list_head *ptype_list
   1 struct ifmap *map
   1 struct hrtimer *timer
   1 struct bpf_prog *prog
   1 rx_handler_func_t *rx_handler
   1 netstamp_needed_key
   1 netdev_walk_all_upper_dev_rcu
   1 netdev_walk_all_lower_dev_rcu
   1 netdev_walk_all_lower_dev
   1 netdev_set_default_ethtool_ops
   1 netdev_rx_handler_unregister
   1 netdev_rx_handler_register
   1 netdev_is_rx_handler_busy
   1 netdev_features_t one
   1 netdev_features_t mask
   1 netdev_features_t all
   1 netdev_cmd_to_name
   1 net_inc_ingress_queue
   1 net_inc_egress_queue
   1 net_dec_ingress_queue
   1 net_dec_egress_queue
   1 napi_hash_del
   1 linkname
   1 level
   1 is_skb_forwardable
   1 int work_done
   1 int unit
   1 int tci
   1 int sizeof_priv
   1 int quota
   1 int new_group
   1 int grow
   1 int flags
   1 int fd
   1 int attr_index
   1 int *poll
   1 int *depth
   1 int
   1 init_dummy_netdev
   1 generic_xdp_tx
   1 func
   1 enum netdev_cmd cmd
   1 enum bpf_netdev_command cmd
   1 do_xdp_generic
   1 dev_queue_xmit_nit
   1 dev_nit_active
   1 dev_list == &dev->adj_list.upper ? "upper_%s" : "lower_%s"
   1 dev_forward_skb
   1 dev_fill_metadata_dst
   1 dev_change_net_namespace
   1 const struct packet_type *pt
   1 const struct net_device_stats *netdev_stats
   1 const struct net_device *sb_dev
   1 const struct net_device *rootdev
   1 const struct ethtool_ops *ops
   1 const struct cpumask *mask
   1 const netdev_features_t features
   1 const char *prefix
   1 const char *pat
   1 const char *newname
   1 const char *ha
   1 const char *format
   1 const char *fmt
   1 const char *alias
   1 char *str
   1 char *oldname
   1 char *buf
   1 br_fdb_test_addr_hook
   1 bool unlink
   1 bool proto_down
   1 bool new_carrier
   1 bool more
   1 bool *loop_end
   1 adj_dev->name
   1 adj_dev->dev.kobj
   1 __netif_set_xps_queue
   1 __dev_forward_skb
   1 &dev->dev.kobj
