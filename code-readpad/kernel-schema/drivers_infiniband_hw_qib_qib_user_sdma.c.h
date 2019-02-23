
\n
static struct qib_user_sdma_rb_node * qib_user_sdma_rb_search(struct rb_root *root, pid_t pid)
static int qib_user_sdma_rb_insert(struct rb_root *root, struct qib_user_sdma_rb_node *new)
struct qib_user_sdma_queue * qib_user_sdma_queue_create(struct device *dev, int unit, int ctxt, int sctxt)
static void qib_user_sdma_init_frag(struct qib_user_sdma_pkt *pkt, int i, u16 offset, u16 len, u16 first_desc, u16 last_desc, u16 put_page, u16 dma_mapped, struct page *page, void *kvaddr, dma_addr_t dma_addr, u16 dma_length)
static void *qib_user_sdma_alloc_header(struct qib_user_sdma_queue *pq, size_t len, dma_addr_t *dma_addr)
static int qib_user_sdma_page_to_frags(const struct qib_devdata *dd, struct qib_user_sdma_queue *pq, struct qib_user_sdma_pkt *pkt, struct page *page, u16 put, u16 offset, u16 len, void *kvaddr)
static int qib_user_sdma_coalesce(const struct qib_devdata *dd, struct qib_user_sdma_queue *pq, struct qib_user_sdma_pkt *pkt, const struct iovec *iov, unsigned long niov)
static int qib_user_sdma_num_pages(const struct iovec *iov)
static void qib_user_sdma_free_pkt_frag(struct device *dev, struct qib_user_sdma_queue *pq, struct qib_user_sdma_pkt *pkt, int frag)
static int qib_user_sdma_pin_pages(const struct qib_devdata *dd, struct qib_user_sdma_queue *pq, struct qib_user_sdma_pkt *pkt, unsigned long addr, int tlen, int npages)
static int qib_user_sdma_pin_pkt(const struct qib_devdata *dd, struct qib_user_sdma_queue *pq, struct qib_user_sdma_pkt *pkt, const struct iovec *iov, unsigned long niov)
static int qib_user_sdma_init_payload(const struct qib_devdata *dd, struct qib_user_sdma_queue *pq, struct qib_user_sdma_pkt *pkt, const struct iovec *iov, unsigned long niov, int npages)
static void qib_user_sdma_free_pkt_list(struct device *dev, struct qib_user_sdma_queue *pq, struct list_head *list)
static int qib_user_sdma_queue_pkts(const struct qib_devdata *dd, struct qib_pportdata *ppd, struct qib_user_sdma_queue *pq, const struct iovec *iov, unsigned long niov, struct list_head *list, int *maxpkts, int *ndesc)
static void qib_user_sdma_set_complete_counter(struct qib_user_sdma_queue *pq, u32 c)
static int qib_user_sdma_queue_clean(struct qib_pportdata *ppd, struct qib_user_sdma_queue *pq)
void qib_user_sdma_queue_destroy(struct qib_user_sdma_queue *pq)
static int qib_user_sdma_hwqueue_clean(struct qib_pportdata *ppd)
void qib_user_sdma_queue_drain(struct qib_pportdata *ppd, struct qib_user_sdma_queue *pq)
static inline __le64 qib_sdma_make_desc0(u8 gen, u64 addr, u64 dwlen, u64 dwoffset)
static inline __le64 qib_sdma_make_first_desc0(__le64 descq)
static inline __le64 qib_sdma_make_last_desc0(__le64 descq)
static inline __le64 qib_sdma_make_desc1(u64 addr)
static void qib_user_sdma_send_frag(struct qib_pportdata *ppd, struct qib_user_sdma_pkt *pkt, int idx, unsigned ofs, u16 tail, u8 gen)
void qib_user_sdma_send_desc(struct qib_pportdata *ppd, struct list_head *pktlist)
static int qib_user_sdma_push_pkts(struct qib_pportdata *ppd, struct qib_user_sdma_queue *pq, struct list_head *pktlist, int count)
int qib_user_sdma_writev(struct qib_ctxtdata *rcd, struct qib_user_sdma_queue *pq, const struct iovec *iov, unsigned long dim)
int qib_user_sdma_make_progress(struct qib_pportdata *ppd, struct qib_user_sdma_queue *pq)
u32 qib_user_sdma_complete_counter(const struct qib_user_sdma_queue *pq)
u32 qib_user_sdma_inflight_counter(struct qib_user_sdma_queue *pq)
\n
     17 struct qib_user_sdma_queue *pq
      8 struct qib_user_sdma_pkt *pkt
      8 struct qib_pportdata *ppd
      6 const struct qib_devdata *dd
      6 const struct iovec *iov
      4 unsigned long niov
      3 struct device *dev
      2 void *kvaddr
      2 u8 gen
      2 u64 addr
      2 u16 offset
      2 u16 len
      2 struct rb_root *root
      2 struct page *page
      2 struct list_head *pktlist
      2 struct list_head *list
      2 __le64 descq
      2 int npages
      1 unsigned ofs
      1 unsigned long dim
      1 unsigned long addr
      1 u64 dwoffset
      1 u64 dwlen
      1 u32 c
      1 u16 tail
      1 u16 put_page
      1 u16 put
      1 u16 last_desc
      1 u16 first_desc
      1 u16 dma_mapped
      1 u16 dma_length
      1 struct qib_user_sdma_rb_node *new
      1 struct qib_ctxtdata *rcd
      1 size_t len
      1 pid_t pid
      1 int unit
      1 int tlen
      1 int sctxt
      1 int *ndesc
      1 int *maxpkts
      1 int idx
      1 int i
      1 int frag
      1 int ctxt
      1 int count
      1 dma_addr_t dma_addr
      1 dma_addr_t *dma_addr
      1 const struct qib_user_sdma_queue *pq
