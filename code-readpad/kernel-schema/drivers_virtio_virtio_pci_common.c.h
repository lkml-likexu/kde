
\n
void vp_synchronize_vectors(struct virtio_device *vdev)
bool vp_notify(struct virtqueue *vq)
static irqreturn_t vp_config_changed(int irq, void *opaque)
static irqreturn_t vp_vring_interrupt(int irq, void *opaque)
static irqreturn_t vp_interrupt(int irq, void *opaque)
static int vp_request_msix_vectors(struct virtio_device *vdev, int nvectors, bool per_vq_vectors, struct irq_affinity *desc)
static struct virtqueue *vp_setup_vq(struct virtio_device *vdev, unsigned index, void (*callback)
(struct virtqueue *vq)
, const char *name, bool ctx, u16 msix_vec)
static void vp_del_vq(struct virtqueue *vq)
void vp_del_vqs(struct virtio_device *vdev)
static int vp_find_vqs_msix(struct virtio_device *vdev, unsigned nvqs, struct virtqueue *vqs[], vq_callback_t *callbacks[], const char * const names[], bool per_vq_vectors, const bool *ctx, struct irq_affinity *desc)
static int vp_find_vqs_intx(struct virtio_device *vdev, unsigned nvqs, struct virtqueue *vqs[], vq_callback_t *callbacks[], const char * const names[], const bool *ctx)
int vp_find_vqs(struct virtio_device *vdev, unsigned nvqs, struct virtqueue *vqs[], vq_callback_t *callbacks[], const char * const names[], const bool *ctx, struct irq_affinity *desc)
const char *vp_bus_name(struct virtio_device *vdev)
int vp_set_vq_affinity(struct virtqueue *vq, const struct cpumask *cpu_mask)
const struct cpumask *vp_get_vq_affinity(struct virtio_device *vdev, int index)
static int virtio_pci_freeze(struct device *dev)
static int virtio_pci_restore(struct device *dev)
static void virtio_pci_release_dev(struct device *_d)
static int virtio_pci_probe(struct pci_dev *pci_dev, const struct pci_device_id *id)
static void virtio_pci_remove(struct pci_dev *pci_dev)
static int virtio_pci_sriov_configure(struct pci_dev *pci_dev, int num_vfs)
\n
      9 struct virtio_device *vdev
      4 struct virtqueue *vq
      3 vq_callback_t *callbacks[]
      3 void *opaque
      3 unsigned nvqs
      3 struct virtqueue *vqs[]
      3 struct pci_dev *pci_dev
      3 struct irq_affinity *desc
      3 int irq
      3 const char * const names[]
      3 const bool *ctx
      2 struct device *dev
      2 bool per_vq_vectors
      1 void *callback
      1 unsigned index
      1 struct device *_d
      1 int nvectors
      1 int num_vfs
      1 int index
      1 const struct pci_device_id *id
      1 const struct cpumask *cpu_mask
