
EXPORT_SYMBOL_GPL(virtqueue_add_sgs);
EXPORT_SYMBOL_GPL(virtqueue_add_outbuf);
EXPORT_SYMBOL_GPL(virtqueue_add_inbuf);
EXPORT_SYMBOL_GPL(virtqueue_add_inbuf_ctx);
EXPORT_SYMBOL_GPL(virtqueue_kick_prepare);
EXPORT_SYMBOL_GPL(virtqueue_notify);
EXPORT_SYMBOL_GPL(virtqueue_kick);
EXPORT_SYMBOL_GPL(virtqueue_get_buf_ctx);
EXPORT_SYMBOL_GPL(virtqueue_get_buf);
EXPORT_SYMBOL_GPL(virtqueue_disable_cb);
EXPORT_SYMBOL_GPL(virtqueue_enable_cb_prepare);
EXPORT_SYMBOL_GPL(virtqueue_poll);
EXPORT_SYMBOL_GPL(virtqueue_enable_cb);
EXPORT_SYMBOL_GPL(virtqueue_enable_cb_delayed);
EXPORT_SYMBOL_GPL(virtqueue_detach_unused_buf);
EXPORT_SYMBOL_GPL(vring_interrupt);
EXPORT_SYMBOL_GPL(__vring_new_virtqueue);
EXPORT_SYMBOL_GPL(vring_create_virtqueue);
EXPORT_SYMBOL_GPL(vring_new_virtqueue);
EXPORT_SYMBOL_GPL(vring_del_virtqueue);
EXPORT_SYMBOL_GPL(vring_transport_features);
EXPORT_SYMBOL_GPL(virtqueue_get_vring_size);
EXPORT_SYMBOL_GPL(virtqueue_is_broken);
EXPORT_SYMBOL_GPL(virtio_break_device);
EXPORT_SYMBOL_GPL(virtqueue_get_desc_addr);
EXPORT_SYMBOL_GPL(virtqueue_get_avail_addr);
EXPORT_SYMBOL_GPL(virtqueue_get_used_addr);
EXPORT_SYMBOL_GPL(virtqueue_get_vring);
\n
static inline bool virtqueue_use_indirect(struct virtqueue *_vq, unsigned int total_sg)
static bool vring_use_dma_api(struct virtio_device *vdev)
static void *vring_alloc_queue(struct virtio_device *vdev, size_t size, dma_addr_t *dma_handle, gfp_t flag)
static void vring_free_queue(struct virtio_device *vdev, size_t size, void *queue, dma_addr_t dma_handle)
static inline struct device *vring_dma_dev(const struct vring_virtqueue *vq)
static dma_addr_t vring_map_one_sg(const struct vring_virtqueue *vq, struct scatterlist *sg, enum dma_data_direction direction)
static dma_addr_t vring_map_single(const struct vring_virtqueue *vq, void *cpu_addr, size_t size, enum dma_data_direction direction)
static int vring_mapping_error(const struct vring_virtqueue *vq, dma_addr_t addr)
static void vring_unmap_one_split(const struct vring_virtqueue *vq, struct vring_desc *desc)
static struct vring_desc *alloc_indirect_split(struct virtqueue *_vq, unsigned int total_sg, gfp_t gfp)
static inline int virtqueue_add_split(struct virtqueue *_vq, struct scatterlist *sgs[], unsigned int total_sg, unsigned int out_sgs, unsigned int in_sgs, void *data, void *ctx, gfp_t gfp)
static bool virtqueue_kick_prepare_split(struct virtqueue *_vq)
static void detach_buf_split(struct vring_virtqueue *vq, unsigned int head, void **ctx)
static inline bool more_used_split(const struct vring_virtqueue *vq)
static void *virtqueue_get_buf_ctx_split(struct virtqueue *_vq, unsigned int *len, void **ctx)
static void virtqueue_disable_cb_split(struct virtqueue *_vq)
static unsigned virtqueue_enable_cb_prepare_split(struct virtqueue *_vq)
static bool virtqueue_poll_split(struct virtqueue *_vq, unsigned last_used_idx)
static bool virtqueue_enable_cb_delayed_split(struct virtqueue *_vq)
static void *virtqueue_detach_unused_buf_split(struct virtqueue *_vq)
static struct virtqueue *vring_create_virtqueue_split(unsigned int index, unsigned int num, unsigned int vring_align, struct virtio_device *vdev, bool weak_barriers, bool may_reduce_num, bool context, bool (*notify)
(struct virtqueue *)
, void (*callback)
(struct virtqueue *)
, const char *name)
static void vring_unmap_state_packed(const struct vring_virtqueue *vq, struct vring_desc_extra_packed *state)
static void vring_unmap_desc_packed(const struct vring_virtqueue *vq, struct vring_packed_desc *desc)
static struct vring_packed_desc *alloc_indirect_packed(unsigned int total_sg, gfp_t gfp)
static int virtqueue_add_indirect_packed(struct vring_virtqueue *vq, struct scatterlist *sgs[], unsigned int total_sg, unsigned int out_sgs, unsigned int in_sgs, void *data, gfp_t gfp)
static inline int virtqueue_add_packed(struct virtqueue *_vq, struct scatterlist *sgs[], unsigned int total_sg, unsigned int out_sgs, unsigned int in_sgs, void *data, void *ctx, gfp_t gfp)
static bool virtqueue_kick_prepare_packed(struct virtqueue *_vq)
static void detach_buf_packed(struct vring_virtqueue *vq, unsigned int id, void **ctx)
static inline bool is_used_desc_packed(const struct vring_virtqueue *vq, u16 idx, bool used_wrap_counter)
static inline bool more_used_packed(const struct vring_virtqueue *vq)
static void *virtqueue_get_buf_ctx_packed(struct virtqueue *_vq, unsigned int *len, void **ctx)
static void virtqueue_disable_cb_packed(struct virtqueue *_vq)
static unsigned virtqueue_enable_cb_prepare_packed(struct virtqueue *_vq)
static bool virtqueue_poll_packed(struct virtqueue *_vq, u16 off_wrap)
static bool virtqueue_enable_cb_delayed_packed(struct virtqueue *_vq)
static void *virtqueue_detach_unused_buf_packed(struct virtqueue *_vq)
static struct virtqueue *vring_create_virtqueue_packed(unsigned int index, unsigned int num, unsigned int vring_align, struct virtio_device *vdev, bool weak_barriers, bool may_reduce_num, bool context, bool (*notify)
(struct virtqueue *)
, void (*callback)
(struct virtqueue *)
, const char *name)
static inline int virtqueue_add(struct virtqueue *_vq, struct scatterlist *sgs[], unsigned int total_sg, unsigned int out_sgs, unsigned int in_sgs, void *data, void *ctx, gfp_t gfp)
int virtqueue_add_sgs(struct virtqueue *_vq, struct scatterlist *sgs[], unsigned int out_sgs, unsigned int in_sgs, void *data, gfp_t gfp)
int virtqueue_add_outbuf(struct virtqueue *vq, struct scatterlist *sg, unsigned int num, void *data, gfp_t gfp)
int virtqueue_add_inbuf(struct virtqueue *vq, struct scatterlist *sg, unsigned int num, void *data, gfp_t gfp)
int virtqueue_add_inbuf_ctx(struct virtqueue *vq, struct scatterlist *sg, unsigned int num, void *data, void *ctx, gfp_t gfp)
bool virtqueue_kick_prepare(struct virtqueue *_vq)
bool virtqueue_notify(struct virtqueue *_vq)
bool virtqueue_kick(struct virtqueue *vq)
void *virtqueue_get_buf_ctx(struct virtqueue *_vq, unsigned int *len, void **ctx)
void *virtqueue_get_buf(struct virtqueue *_vq, unsigned int *len)
void *virtqueue_get_buf(struct virtqueue *_vq, unsigned int *len)
return virtqueue_get_buf_ctx(_vq, len, NULL)
; } EXPORT_SYMBOL_GPL(virtqueue_get_buf)
;void virtqueue_disable_cb(struct virtqueue *_vq)
unsigned virtqueue_enable_cb_prepare(struct virtqueue *_vq)
bool virtqueue_poll(struct virtqueue *_vq, unsigned last_used_idx)
bool virtqueue_enable_cb(struct virtqueue *_vq)
bool virtqueue_enable_cb_delayed(struct virtqueue *_vq)
void *virtqueue_detach_unused_buf(struct virtqueue *_vq)
static inline bool more_used(const struct vring_virtqueue *vq)
irqreturn_t vring_interrupt(int irq, void *_vq)
struct virtqueue *__vring_new_virtqueue(unsigned int index, struct vring vring, struct virtio_device *vdev, bool weak_barriers, bool context, bool (*notify)
(struct virtqueue *)
, void (*callback)
(struct virtqueue *)
, const char *name)
struct virtqueue *vring_create_virtqueue(unsigned int index, unsigned int num, unsigned int vring_align, struct virtio_device *vdev, bool weak_barriers, bool may_reduce_num, bool context, bool (*notify)
(struct virtqueue *)
, void (*callback)
(struct virtqueue *)
, const char *name)
struct virtqueue *vring_new_virtqueue(unsigned int index, unsigned int num, unsigned int vring_align, struct virtio_device *vdev, bool weak_barriers, bool context, void *pages, bool (*notify)
(struct virtqueue *vq)
, void (*callback)
(struct virtqueue *vq)
, const char *name)
void vring_del_virtqueue(struct virtqueue *_vq)
void vring_transport_features(struct virtio_device *vdev)
unsigned int virtqueue_get_vring_size(struct virtqueue *_vq)
bool virtqueue_is_broken(struct virtqueue *_vq)
void virtio_break_device(struct virtio_device *dev)
dma_addr_t virtqueue_get_desc_addr(struct virtqueue *_vq)
dma_addr_t virtqueue_get_avail_addr(struct virtqueue *_vq)
dma_addr_t virtqueue_get_used_addr(struct virtqueue *_vq)
const struct vring *virtqueue_get_vring(struct virtqueue *vq)
\n
     37 struct virtqueue *_vq
     11 const struct vring_virtqueue *vq
     10 gfp_t gfp
      9 struct virtio_device *vdev
      8 void *data
      8 struct virtqueue *
      7 unsigned int total_sg
      7 unsigned int num
      7 struct virtqueue *vq
      5 void **ctx
      5 unsigned int out_sgs
      5 unsigned int *len
      5 unsigned int in_sgs
      5 unsigned int index
      5 struct scatterlist *sgs[]
      5 *callback
      5 bool weak_barriers
      5 bool *notify
      5 bool context
      4 void *ctx
      4 unsigned int vring_align
      4 struct scatterlist *sg
      3 struct vring_virtqueue *vq
      3 size_t size
      3 bool may_reduce_num
      2 virtqueue_get_buf
      2 unsigned last_used_idx
      2 enum dma_data_direction direction
      1 vring_transport_features
      1 vring_new_virtqueue
      1 __vring_new_virtqueue
      1 vring_interrupt
      1 vring_del_virtqueue
      1 vring_create_virtqueue
      1 _vq
      1 void *_vq
      1 void *queue
      1 void *pages
      1 void *cpu_addr
      1 virtqueue_poll
      1 virtqueue_notify
      1 virtqueue_kick_prepare
      1 virtqueue_kick
      1 virtqueue_is_broken
      1 virtqueue_get_vring_size
      1 virtqueue_get_vring
      1 virtqueue_get_used_addr
      1 virtqueue_get_desc_addr
      1 virtqueue_get_buf_ctx
      1 virtqueue_get_avail_addr
      1 virtqueue_enable_cb_prepare
      1 virtqueue_enable_cb_delayed
      1 virtqueue_enable_cb
      1 virtqueue_disable_cb
      1 virtqueue_detach_unused_buf
      1 virtqueue_add_sgs
      1 virtqueue_add_outbuf
      1 virtqueue_add_inbuf_ctx
      1 virtqueue_add_inbuf
      1 virtio_break_device
      1 unsigned int id
      1 unsigned int head
      1 u16 off_wrap
      1 u16 idx
      1 struct vring vring
      1 struct vring_packed_desc *desc
      1 struct vring_desc_extra_packed *state
      1 struct vring_desc *desc
      1 struct virtio_device *dev
      1 NULL
      1 len
      1 int irq
      1 gfp_t flag
      1 dma_addr_t dma_handle
      1 dma_addr_t *dma_handle
      1 dma_addr_t addr
      1 bool used_wrap_counter
