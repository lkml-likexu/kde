
\n
static bool rproc_virtio_notify(struct virtqueue *vq)
irqreturn_t rproc_vq_interrupt(struct rproc *rproc, int notifyid)
static struct virtqueue *rp_find_vq(struct virtio_device *vdev, unsigned int id, void (*callback)
(struct virtqueue *vq)
, const char *name, bool ctx)
static void __rproc_virtio_del_vqs(struct virtio_device *vdev)
static void rproc_virtio_del_vqs(struct virtio_device *vdev)
static int rproc_virtio_find_vqs(struct virtio_device *vdev, unsigned int nvqs, struct virtqueue *vqs[], vq_callback_t *callbacks[], const char * const names[], const bool * ctx, struct irq_affinity *desc)
static u8 rproc_virtio_get_status(struct virtio_device *vdev)
static void rproc_virtio_set_status(struct virtio_device *vdev, u8 status)
static void rproc_virtio_reset(struct virtio_device *vdev)
static u64 rproc_virtio_get_features(struct virtio_device *vdev)
static void rproc_transport_features(struct virtio_device *vdev)
static int rproc_virtio_finalize_features(struct virtio_device *vdev)
static void rproc_virtio_get(struct virtio_device *vdev, unsigned int offset, void *buf, unsigned int len)
static void rproc_virtio_set(struct virtio_device *vdev, unsigned int offset, const void *buf, unsigned int len)
static void rproc_virtio_dev_release(struct device *dev)
int rproc_add_virtio_dev(struct rproc_vdev *rvdev, int id)
void rproc_remove_virtio_dev(struct rproc_vdev *rvdev)
\n
     12 struct virtio_device *vdev
      2 unsigned int offset
      2 unsigned int len
      2 struct virtqueue *vq
      2 struct rproc_vdev *rvdev
      1 vq_callback_t *callbacks[]
      1 void *callback
      1 void *buf
      1 unsigned int nvqs
      1 unsigned int id
      1 u8 status
      1 struct virtqueue *vqs[]
      1 struct rproc *rproc
      1 struct irq_affinity *desc
      1 struct device *dev
      1 int notifyid
      1 int id
      1 const void *buf
      1 const char * const names[]
      1 const bool * ctx
