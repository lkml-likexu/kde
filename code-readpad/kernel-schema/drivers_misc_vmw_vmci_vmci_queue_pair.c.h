
EXPORT_SYMBOL_GPL(vmci_qpair_alloc);
EXPORT_SYMBOL_GPL(vmci_qpair_detach);
EXPORT_SYMBOL_GPL(vmci_qpair_get_produce_indexes);
EXPORT_SYMBOL_GPL(vmci_qpair_get_consume_indexes);
EXPORT_SYMBOL_GPL(vmci_qpair_produce_free_space);
EXPORT_SYMBOL_GPL(vmci_qpair_consume_free_space);
EXPORT_SYMBOL_GPL(vmci_qpair_produce_buf_ready);
EXPORT_SYMBOL_GPL(vmci_qpair_consume_buf_ready);
EXPORT_SYMBOL_GPL(vmci_qpair_enqueue);
EXPORT_SYMBOL_GPL(vmci_qpair_dequeue);
EXPORT_SYMBOL_GPL(vmci_qpair_peek);
EXPORT_SYMBOL_GPL(vmci_qpair_enquev);
EXPORT_SYMBOL_GPL(vmci_qpair_dequev);
EXPORT_SYMBOL_GPL(vmci_qpair_peekv);
\n
static void qp_free_queue(void *q, u64 size)
static void *qp_alloc_queue(u64 size, u32 flags)
static int qp_memcpy_to_queue_iter(struct vmci_queue *queue, u64 queue_offset, struct iov_iter *from, size_t size)
static int qp_memcpy_from_queue_iter(struct iov_iter *to, const struct vmci_queue *queue, u64 queue_offset, size_t size)
static int qp_alloc_ppn_set(void *prod_q, u64 num_produce_pages, void *cons_q, u64 num_consume_pages, struct ppn_set *ppn_set)
static void qp_free_ppn_set(struct ppn_set *ppn_set)
static int qp_populate_ppn_set(u8 *call_buf, const struct ppn_set *ppn_set)
static struct vmci_queue *qp_host_alloc_queue(u64 size)
static void qp_host_free_queue(struct vmci_queue *queue, u64 queue_size)
static void qp_init_queue_mutex(struct vmci_queue *produce_q, struct vmci_queue *consume_q)
static void qp_cleanup_queue_mutex(struct vmci_queue *produce_q, struct vmci_queue *consume_q)
static void qp_acquire_queue_mutex(struct vmci_queue *queue)
static void qp_release_queue_mutex(struct vmci_queue *queue)
static void qp_release_pages(struct page **pages, u64 num_pages, bool dirty)
static int qp_host_get_user_memory(u64 produce_uva, u64 consume_uva, struct vmci_queue *produce_q, struct vmci_queue *consume_q)
static int qp_host_register_user_memory(struct vmci_qp_page_store *page_store, struct vmci_queue *produce_q, struct vmci_queue *consume_q)
static void qp_host_unregister_user_memory(struct vmci_queue *produce_q, struct vmci_queue *consume_q)
static int qp_host_map_queues(struct vmci_queue *produce_q, struct vmci_queue *consume_q)
static int qp_host_unmap_queues(u32 gid, struct vmci_queue *produce_q, struct vmci_queue *consume_q)
static struct qp_entry *qp_list_find(struct qp_list *qp_list, struct vmci_handle handle)
static struct qp_guest_endpoint * qp_guest_handle_to_entry(struct vmci_handle handle)
static struct qp_broker_entry * qp_broker_handle_to_entry(struct vmci_handle handle)
static int qp_notify_peer_local(bool attach, struct vmci_handle handle)
static struct qp_guest_endpoint * qp_guest_endpoint_create(struct vmci_handle handle, u32 peer, u32 flags, u64 produce_size, u64 consume_size, void *produce_q, void *consume_q)
static void qp_guest_endpoint_destroy(struct qp_guest_endpoint *entry)
static int qp_alloc_hypercall(const struct qp_guest_endpoint *entry)
static int qp_detatch_hypercall(struct vmci_handle handle)
static void qp_list_add_entry(struct qp_list *qp_list, struct qp_entry *entry)
static void qp_list_remove_entry(struct qp_list *qp_list, struct qp_entry *entry)
static int qp_detatch_guest_work(struct vmci_handle handle)
static int qp_alloc_guest_work(struct vmci_handle *handle, struct vmci_queue **produce_q, u64 produce_size, struct vmci_queue **consume_q, u64 consume_size, u32 peer, u32 flags, u32 priv_flags)
static int qp_broker_create(struct vmci_handle handle, u32 peer, u32 flags, u32 priv_flags, u64 produce_size, u64 consume_size, struct vmci_qp_page_store *page_store, struct vmci_ctx *context, vmci_event_release_cb wakeup_cb, void *client_data, struct qp_broker_entry **ent)
static int qp_notify_peer(bool attach, struct vmci_handle handle, u32 my_id, u32 peer_id)
static int qp_broker_attach(struct qp_broker_entry *entry, u32 peer, u32 flags, u32 priv_flags, u64 produce_size, u64 consume_size, struct vmci_qp_page_store *page_store, struct vmci_ctx *context, vmci_event_release_cb wakeup_cb, void *client_data, struct qp_broker_entry **ent)
static int qp_broker_alloc(struct vmci_handle handle, u32 peer, u32 flags, u32 priv_flags, u64 produce_size, u64 consume_size, struct vmci_qp_page_store *page_store, struct vmci_ctx *context, vmci_event_release_cb wakeup_cb, void *client_data, struct qp_broker_entry **ent, bool *swap)
static int qp_alloc_host_work(struct vmci_handle *handle, struct vmci_queue **produce_q, u64 produce_size, struct vmci_queue **consume_q, u64 consume_size, u32 peer, u32 flags, u32 priv_flags, vmci_event_release_cb wakeup_cb, void *client_data)
int vmci_qp_alloc(struct vmci_handle *handle, struct vmci_queue **produce_q, u64 produce_size, struct vmci_queue **consume_q, u64 consume_size, u32 peer, u32 flags, u32 priv_flags, bool guest_endpoint, vmci_event_release_cb wakeup_cb, void *client_data)
static int qp_detatch_host_work(struct vmci_handle handle)
static int qp_detatch(struct vmci_handle handle, bool guest_endpoint)
static struct qp_entry *qp_list_get_head(struct qp_list *qp_list)
void vmci_qp_broker_exit(void)
int vmci_qp_broker_alloc(struct vmci_handle handle, u32 peer, u32 flags, u32 priv_flags, u64 produce_size, u64 consume_size, struct vmci_qp_page_store *page_store, struct vmci_ctx *context)
int vmci_qp_broker_set_page_store(struct vmci_handle handle, u64 produce_uva, u64 consume_uva, struct vmci_ctx *context)
static void qp_reset_saved_headers(struct qp_broker_entry *entry)
int vmci_qp_broker_detach(struct vmci_handle handle, struct vmci_ctx *context)
int vmci_qp_broker_map(struct vmci_handle handle, struct vmci_ctx *context, u64 guest_mem)
static int qp_save_headers(struct qp_broker_entry *entry)
int vmci_qp_broker_unmap(struct vmci_handle handle, struct vmci_ctx *context, u32 gid)
void vmci_qp_guest_endpoints_exit(void)
static void qp_lock(const struct vmci_qp *qpair)
static void qp_unlock(const struct vmci_qp *qpair)
static int qp_map_queue_headers(struct vmci_queue *produce_q, struct vmci_queue *consume_q)
static int qp_get_queue_headers(const struct vmci_qp *qpair, struct vmci_queue_header **produce_q_header, struct vmci_queue_header **consume_q_header)
static int qp_wakeup_cb(void *client_data)
static bool qp_wait_for_ready_queue(struct vmci_qp *qpair)
static ssize_t qp_enqueue_locked(struct vmci_queue *produce_q, struct vmci_queue *consume_q, const u64 produce_q_size, struct iov_iter *from)
static ssize_t qp_dequeue_locked(struct vmci_queue *produce_q, struct vmci_queue *consume_q, const u64 consume_q_size, struct iov_iter *to, bool update_consumer)
int vmci_qpair_alloc(struct vmci_qp **qpair, struct vmci_handle *handle, u64 produce_qsize, u64 consume_qsize, u32 peer, u32 flags, u32 priv_flags)
int vmci_qpair_detach(struct vmci_qp **qpair)
int vmci_qpair_get_produce_indexes(const struct vmci_qp *qpair, u64 *producer_tail, u64 *consumer_head)
int vmci_qpair_get_consume_indexes(const struct vmci_qp *qpair, u64 *consumer_tail, u64 *producer_head)
s64 vmci_qpair_produce_free_space(const struct vmci_qp *qpair)
s64 vmci_qpair_consume_free_space(const struct vmci_qp *qpair)
s64 vmci_qpair_produce_buf_ready(const struct vmci_qp *qpair)
s64 vmci_qpair_consume_buf_ready(const struct vmci_qp *qpair)
ssize_t vmci_qpair_enqueue(struct vmci_qp *qpair, const void *buf, size_t buf_size, int buf_type)
ssize_t vmci_qpair_dequeue(struct vmci_qp *qpair, void *buf, size_t buf_size, int buf_type)
ssize_t vmci_qpair_peek(struct vmci_qp *qpair, void *buf, size_t buf_size, int buf_type)
ssize_t vmci_qpair_enquev(struct vmci_qp *qpair, struct msghdr *msg, size_t iov_size, int buf_type)
ssize_t vmci_qpair_dequev(struct vmci_qp *qpair, struct msghdr *msg, size_t iov_size, int buf_type)
ssize_t vmci_qpair_peekv(struct vmci_qp *qpair, struct msghdr *msg, size_t iov_size, int buf_type)
\n
     17 struct vmci_handle handle
     10 u32 flags
     10 struct vmci_queue *produce_q
     10 struct vmci_queue *consume_q
      9 u32 peer
      9 const struct vmci_qp *qpair
      8 u64 produce_size
      8 u64 consume_size
      8 u32 priv_flags
      8 struct vmci_ctx *context
      7 struct vmci_qp *qpair
      6 void *client_data
      6 int buf_type
      5 vmci_event_release_cb wakeup_cb
      5 struct vmci_qp_page_store *page_store
      4 struct vmci_queue *queue
      4 struct vmci_handle *handle
      4 struct qp_list *qp_list
      3 u64 size
      3 struct vmci_queue **produce_q
      3 struct vmci_queue **consume_q
      3 struct qp_broker_entry *entry
      3 struct qp_broker_entry **ent
      3 struct msghdr *msg
      3 size_t iov_size
      3 size_t buf_size
      2 void *buf
      2 void
      2 u64 queue_offset
      2 u64 produce_uva
      2 u64 consume_uva
      2 u32 gid
      2 struct vmci_qp **qpair
      2 struct qp_entry *entry
      2 struct ppn_set *ppn_set
      2 struct iov_iter *to
      2 struct iov_iter *from
      2 size_t size
      2 bool guest_endpoint
      2 bool attach
      1 void *q
      1 void *produce_q
      1 void *prod_q
      1 void *consume_q
      1 void *cons_q
      1 vmci_qpair_produce_free_space
      1 vmci_qpair_produce_buf_ready
      1 vmci_qpair_peekv
      1 vmci_qpair_peek
      1 vmci_qpair_get_produce_indexes
      1 vmci_qpair_get_consume_indexes
      1 vmci_qpair_enquev
      1 vmci_qpair_enqueue
      1 vmci_qpair_detach
      1 vmci_qpair_dequev
      1 vmci_qpair_dequeue
      1 vmci_qpair_consume_free_space
      1 vmci_qpair_consume_buf_ready
      1 vmci_qpair_alloc
      1 u8 *call_buf
      1 u64 queue_size
      1 u64 *producer_tail
      1 u64 *producer_head
      1 u64 produce_qsize
      1 u64 num_produce_pages
      1 u64 num_pages
      1 u64 num_consume_pages
      1 u64 guest_mem
      1 u64 *consumer_tail
      1 u64 *consumer_head
      1 u64 consume_qsize
      1 u32 peer_id
      1 u32 my_id
      1 struct vmci_queue_header **produce_q_header
      1 struct vmci_queue_header **consume_q_header
      1 struct qp_guest_endpoint *entry
      1 struct page **pages
      1 const void *buf
      1 const u64 produce_q_size
      1 const u64 consume_q_size
      1 const struct vmci_queue *queue
      1 const struct qp_guest_endpoint *entry
      1 const struct ppn_set *ppn_set
      1 bool update_consumer
      1 bool *swap
      1 bool dirty
