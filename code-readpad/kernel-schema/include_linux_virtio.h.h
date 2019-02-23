
\n
static inline void *virtqueue_get_desc(struct virtqueue *vq)
static inline void *virtqueue_get_desc(struct virtqueue *vq)
return virtqueue_get_vring(vq)
->desc; } static inline void *virtqueue_get_avail(struct virtqueue *vq)
static inline void *virtqueue_get_desc(struct virtqueue *vq)
return virtqueue_get_vring(vq)
->desc; } static inline void *virtqueue_get_avail(struct virtqueue *vq)
return virtqueue_get_vring(vq)
->avail; } static inline void *virtqueue_get_used(struct virtqueue *vq)
static inline struct virtio_device *dev_to_virtio(struct device *_dev)
static inline struct virtio_driver *drv_to_virtio(struct device_driver *drv)
\n
      6 struct virtqueue *vq
      3 vq
      1 struct device_driver *drv
      1 struct device *_dev
