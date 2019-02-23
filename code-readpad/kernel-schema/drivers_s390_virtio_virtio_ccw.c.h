
\n
static struct virtio_ccw_device *to_vc_device(struct virtio_device *vdev)
static void drop_airq_indicator(struct virtqueue *vq, struct airq_info *info)
static void virtio_airq_handler(struct airq_struct *airq)
static struct airq_info *new_airq_info(void)
static unsigned long get_airq_indicator(struct virtqueue *vqs[], int nvqs, u64 *first, void **airq_info)
static void virtio_ccw_drop_indicators(struct virtio_ccw_device *vcdev)
static int doing_io(struct virtio_ccw_device *vcdev, __u32 flag)
static int ccw_io_helper(struct virtio_ccw_device *vcdev, struct ccw1 *ccw, __u32 intparm)
static void virtio_ccw_drop_indicator(struct virtio_ccw_device *vcdev, struct ccw1 *ccw)
static inline long __do_kvm_notify(struct subchannel_id schid, unsigned long queue_index, long cookie)
static inline long do_kvm_notify(struct subchannel_id schid, unsigned long queue_index, long cookie)
static bool virtio_ccw_kvm_notify(struct virtqueue *vq)
static int virtio_ccw_read_vq_conf(struct virtio_ccw_device *vcdev, struct ccw1 *ccw, int index)
static void virtio_ccw_del_vq(struct virtqueue *vq, struct ccw1 *ccw)
static void virtio_ccw_del_vqs(struct virtio_device *vdev)
static struct virtqueue *virtio_ccw_setup_vq(struct virtio_device *vdev, int i, vq_callback_t *callback, const char *name, bool ctx, struct ccw1 *ccw)
static int virtio_ccw_register_adapter_ind(struct virtio_ccw_device *vcdev, struct virtqueue *vqs[], int nvqs, struct ccw1 *ccw)
static int virtio_ccw_find_vqs(struct virtio_device *vdev, unsigned nvqs, struct virtqueue *vqs[], vq_callback_t *callbacks[], const char * const names[], const bool *ctx, struct irq_affinity *desc)
static void virtio_ccw_reset(struct virtio_device *vdev)
static u64 virtio_ccw_get_features(struct virtio_device *vdev)
static void ccw_transport_features(struct virtio_device *vdev)
static int virtio_ccw_finalize_features(struct virtio_device *vdev)
static void virtio_ccw_get_config(struct virtio_device *vdev, unsigned int offset, void *buf, unsigned len)
static void virtio_ccw_set_config(struct virtio_device *vdev, unsigned int offset, const void *buf, unsigned len)
static u8 virtio_ccw_get_status(struct virtio_device *vdev)
static void virtio_ccw_set_status(struct virtio_device *vdev, u8 status)
static void virtio_ccw_release_dev(struct device *_d)
static int irb_is_error(struct irb *irb)
static struct virtqueue *virtio_ccw_vq_by_ind(struct virtio_ccw_device *vcdev, int index)
static void virtio_ccw_check_activity(struct virtio_ccw_device *vcdev, __u32 activity)
static void virtio_ccw_int_handler(struct ccw_device *cdev, unsigned long intparm, struct irb *irb)
static int virtio_ccw_check_autoonline(struct ccw_device *cdev)
static void virtio_ccw_auto_online(void *data, async_cookie_t cookie)
static int virtio_ccw_probe(struct ccw_device *cdev)
static struct virtio_ccw_device *virtio_grab_drvdata(struct ccw_device *cdev)
static void virtio_ccw_remove(struct ccw_device *cdev)
static int virtio_ccw_offline(struct ccw_device *cdev)
static int virtio_ccw_set_transport_rev(struct virtio_ccw_device *vcdev)
static int virtio_ccw_online(struct ccw_device *cdev)
static int virtio_ccw_cio_notify(struct ccw_device *cdev, int event)
static int virtio_ccw_freeze(struct ccw_device *cdev)
static int virtio_ccw_restore(struct ccw_device *cdev)
static int __init pure_hex(char **cp, unsigned int *val, int min_digit, int max_digit, int max_val)
static int __init parse_busid(char *str, unsigned int *cssid, unsigned int *ssid, unsigned int *devno)
static void __init no_auto_parse(void)
static int __init virtio_ccw_init(void)
\n
     12 struct virtio_device *vdev
     10 struct ccw_device *cdev
      9 struct virtio_ccw_device *vcdev
      6 struct ccw1 *ccw
      3 void
      3 struct virtqueue *vqs[]
      3 struct virtqueue *vq
      2 unsigned long queue_index
      2 unsigned len
      2 unsigned int offset
      2 struct subchannel_id schid
      2 struct irb *irb
      2 long cookie
      2 int nvqs
      2 int index
      1 vq_callback_t *callbacks[]
      1 vq_callback_t *callback
      1 void *data
      1 void *buf
      1 void **airq_info
      1 unsigned nvqs
      1 unsigned long intparm
      1 unsigned int *val
      1 unsigned int *ssid
      1 unsigned int *devno
      1 unsigned int *cssid
      1 u8 status
      1 u64 *first
      1 __u32 intparm
      1 __u32 flag
      1 __u32 activity
      1 struct irq_affinity *desc
      1 struct device *_d
      1 struct airq_struct *airq
      1 struct airq_info *info
      1 int min_digit
      1 int max_val
      1 int max_digit
      1 int i
      1 int event
      1 const void *buf
      1 const char *name
      1 const char * const names[]
      1 const bool *ctx
      1 char *str
      1 char **cp
      1 bool ctx
      1 async_cookie_t cookie
