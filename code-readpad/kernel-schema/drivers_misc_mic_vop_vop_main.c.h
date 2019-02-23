
\n
static inline struct device *_vop_dev(struct _vop_vdev *vdev)
static inline unsigned _vop_desc_size(struct mic_device_desc __iomem *desc)
static inline struct mic_vqconfig __iomem * _vop_vq_config(struct mic_device_desc __iomem *desc)
static inline u8 __iomem * _vop_vq_features(struct mic_device_desc __iomem *desc)
static inline u8 __iomem * _vop_vq_configspace(struct mic_device_desc __iomem *desc)
static inline unsigned _vop_total_desc_size(struct mic_device_desc __iomem *desc)
static u64 vop_get_features(struct virtio_device *vdev)
static void vop_transport_features(struct virtio_device *vdev)
static int vop_finalize_features(struct virtio_device *vdev)
static void vop_get(struct virtio_device *vdev, unsigned int offset, void *buf, unsigned len)
static void vop_set(struct virtio_device *vdev, unsigned int offset, const void *buf, unsigned len)
static u8 vop_get_status(struct virtio_device *vdev)
static void vop_set_status(struct virtio_device *dev, u8 status)
static void vop_reset_inform_host(struct virtio_device *dev)
static void vop_reset(struct virtio_device *dev)
static bool vop_notify(struct virtqueue *vq)
static void vop_del_vq(struct virtqueue *vq, int n)
static void vop_del_vqs(struct virtio_device *dev)
static struct virtqueue *vop_new_virtqueue(unsigned int index, unsigned int num, struct virtio_device *vdev, bool context, void *pages, bool (*notify)
(struct virtqueue *vq)
, void (*callback)
(struct virtqueue *vq)
, const char *name, void *used)
static struct virtqueue *vop_find_vq(struct virtio_device *dev, unsigned index, void (*callback)
(struct virtqueue *vq)
, const char *name, bool ctx)
static int vop_find_vqs(struct virtio_device *dev, unsigned nvqs, struct virtqueue *vqs[], vq_callback_t *callbacks[], const char * const names[], const bool *ctx, struct irq_affinity *desc)
static irqreturn_t vop_virtio_intr_handler(int irq, void *data)
static void vop_virtio_release_dev(struct device *_d)
static int _vop_add_device(struct mic_device_desc __iomem *d, unsigned int offset, struct vop_device *vpdev, int dnode)
static int vop_match_desc(struct device *dev, void *data)
static void _vop_handle_config_change(struct mic_device_desc __iomem *d, unsigned int offset, struct vop_device *vpdev)
static int _vop_remove_device(struct mic_device_desc __iomem *d, unsigned int offset, struct vop_device *vpdev)
static void _vop_scan_devices(void __iomem *dp, struct vop_device *vpdev, bool remove, int dnode)
static void vop_scan_devices(struct vop_info *vi, struct vop_device *vpdev, bool remove)
static void vop_hotplug_devices(struct work_struct *work)
static irqreturn_t vop_extint_handler(int irq, void *data)
static int vop_driver_probe(struct vop_device *vpdev)
static void vop_driver_remove(struct vop_device *vpdev)
\n
      7 struct vop_device *vpdev
      7 struct virtio_device *vdev
      6 struct virtio_device *dev
      5 unsigned int offset
      5 struct virtqueue *vq
      5 struct mic_device_desc __iomem *desc
      3 void *data
      3 struct mic_device_desc __iomem *d
      2 unsigned len
      2 int irq
      2 int dnode
      2 bool remove
      1 vq_callback_t *callbacks[]
      1 void *pages
      1 void __iomem *dp
      1 void *callback
      1 void *buf
      1 unsigned nvqs
      1 unsigned int num
      1 unsigned int index
      1 unsigned index
      1 u8 status
      1 struct work_struct *work
      1 struct _vop_vdev *vdev
      1 struct vop_info *vi
      1 struct virtqueue *vqs[]
      1 struct irq_affinity *desc
      1 struct device *dev
      1 struct device *_d
      1 int n
      1 const void *buf
      1 const char * const names[]
      1 const bool *ctx
      1 *callback
      1 bool *notify
      1 bool context
