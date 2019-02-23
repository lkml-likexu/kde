
\n
static inline bool vhost_has_feature(struct vhost_virtqueue *vq, int bit)
static inline bool vhost_backend_has_feature(struct vhost_virtqueue *vq, int bit)
static inline bool vhost_is_little_endian(struct vhost_virtqueue *vq)
static inline bool vhost_is_little_endian(struct vhost_virtqueue *vq)
return vq->is_le; } static inline bool vhost_is_little_endian(struct vhost_virtqueue *vq)
static inline u16 vhost16_to_cpu(struct vhost_virtqueue *vq, __virtio16 val)
static inline __virtio16 cpu_to_vhost16(struct vhost_virtqueue *vq, u16 val)
static inline u32 vhost32_to_cpu(struct vhost_virtqueue *vq, __virtio32 val)
static inline __virtio32 cpu_to_vhost32(struct vhost_virtqueue *vq, u32 val)
static inline u64 vhost64_to_cpu(struct vhost_virtqueue *vq, __virtio64 val)
static inline __virtio64 cpu_to_vhost64(struct vhost_virtqueue *vq, u64 val)
\n
     11 struct vhost_virtqueue *vq
      2 int bit
      1 __virtio64 val
      1 __virtio32 val
      1 __virtio16 val
      1 u64 val
      1 u32 val
      1 u16 val
