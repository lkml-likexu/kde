
EXPORT_SYMBOL_GPL(vhost_work_init);
EXPORT_SYMBOL_GPL(vhost_poll_init);
EXPORT_SYMBOL_GPL(vhost_poll_start);
EXPORT_SYMBOL_GPL(vhost_poll_stop);
EXPORT_SYMBOL_GPL(vhost_work_flush);
EXPORT_SYMBOL_GPL(vhost_poll_flush);
EXPORT_SYMBOL_GPL(vhost_work_queue);
EXPORT_SYMBOL_GPL(vhost_has_work);
EXPORT_SYMBOL_GPL(vhost_poll_queue);
EXPORT_SYMBOL_GPL(vhost_dev_init);
EXPORT_SYMBOL_GPL(vhost_dev_check_owner);
EXPORT_SYMBOL_GPL(vhost_dev_has_owner);
EXPORT_SYMBOL_GPL(vhost_dev_set_owner);
EXPORT_SYMBOL_GPL(vhost_dev_reset_owner_prepare);
EXPORT_SYMBOL_GPL(vhost_dev_reset_owner);
EXPORT_SYMBOL_GPL(vhost_dev_stop);
EXPORT_SYMBOL_GPL(vhost_dev_cleanup);
EXPORT_SYMBOL_GPL(vhost_chr_read_iter);
EXPORT_SYMBOL_GPL(vq_iotlb_prefetch);
EXPORT_SYMBOL_GPL(vhost_log_access_ok);
EXPORT_SYMBOL_GPL(vhost_vq_access_ok);
EXPORT_SYMBOL_GPL(vhost_vring_ioctl);
EXPORT_SYMBOL_GPL(vhost_init_device_iotlb);
EXPORT_SYMBOL_GPL(vhost_dev_ioctl);
EXPORT_SYMBOL_GPL(vhost_log_write);
EXPORT_SYMBOL_GPL(vhost_vq_init_access);
EXPORT_SYMBOL_GPL(vhost_get_vq_desc);
EXPORT_SYMBOL_GPL(vhost_discard_vq_desc);
EXPORT_SYMBOL_GPL(vhost_add_used);
EXPORT_SYMBOL_GPL(vhost_add_used_n);
EXPORT_SYMBOL_GPL(vhost_signal);
EXPORT_SYMBOL_GPL(vhost_add_used_and_signal);
EXPORT_SYMBOL_GPL(vhost_add_used_and_signal_n);
EXPORT_SYMBOL_GPL(vhost_vq_avail_empty);
EXPORT_SYMBOL_GPL(vhost_enable_notify);
EXPORT_SYMBOL_GPL(vhost_disable_notify);
EXPORT_SYMBOL_GPL(vhost_new_msg);
EXPORT_SYMBOL_GPL(vhost_enqueue_msg);
EXPORT_SYMBOL_GPL(vhost_dequeue_msg);
\n
static void vhost_disable_cross_endian(struct vhost_virtqueue *vq)
static void vhost_enable_cross_endian_big(struct vhost_virtqueue *vq)
static void vhost_enable_cross_endian_little(struct vhost_virtqueue *vq)
static long vhost_set_vring_endian(struct vhost_virtqueue *vq, int __user *argp)
static long vhost_get_vring_endian(struct vhost_virtqueue *vq, u32 idx, int __user *argp)
static void vhost_init_is_le(struct vhost_virtqueue *vq)
static void vhost_init_is_le(struct vhost_virtqueue *vq)
vq->is_le = vhost_has_feature(vq, VIRTIO_F_VERSION_1)
|| !vq->user_be; } static void vhost_disable_cross_endian(struct vhost_virtqueue *vq)
static long vhost_set_vring_endian(struct vhost_virtqueue *vq, int __user *argp)
static long vhost_get_vring_endian(struct vhost_virtqueue *vq, u32 idx, int __user *argp)
static void vhost_init_is_le(struct vhost_virtqueue *vq)
static void vhost_reset_is_le(struct vhost_virtqueue *vq)
static void vhost_flush_work(struct vhost_work *work)
static void vhost_poll_func(struct file *file, wait_queue_head_t *wqh, poll_table *pt)
static int vhost_poll_wakeup(wait_queue_entry_t *wait, unsigned mode, int sync, void *key)
void vhost_work_init(struct vhost_work *work, vhost_work_fn_t fn)
void vhost_poll_init(struct vhost_poll *poll, vhost_work_fn_t fn, __poll_t mask, struct vhost_dev *dev)
int vhost_poll_start(struct vhost_poll *poll, struct file *file)
void vhost_poll_stop(struct vhost_poll *poll)
void vhost_work_flush(struct vhost_dev *dev, struct vhost_work *work)
void vhost_poll_flush(struct vhost_poll *poll)
void vhost_work_queue(struct vhost_dev *dev, struct vhost_work *work)
bool vhost_has_work(struct vhost_dev *dev)
void vhost_poll_queue(struct vhost_poll *poll)
static void __vhost_vq_meta_reset(struct vhost_virtqueue *vq)
static void vhost_vq_meta_reset(struct vhost_dev *d)
static void vhost_vq_reset(struct vhost_dev *dev, struct vhost_virtqueue *vq)
static int vhost_worker(void *data)
static void vhost_vq_free_iovecs(struct vhost_virtqueue *vq)
static long vhost_dev_alloc_iovecs(struct vhost_dev *dev)
static void vhost_dev_free_iovecs(struct vhost_dev *dev)
void vhost_dev_init(struct vhost_dev *dev, struct vhost_virtqueue **vqs, int nvqs, int iov_limit)
long vhost_dev_check_owner(struct vhost_dev *dev)
static void vhost_attach_cgroups_work(struct vhost_work *work)
static int vhost_attach_cgroups(struct vhost_dev *dev)
bool vhost_dev_has_owner(struct vhost_dev *dev)
long vhost_dev_set_owner(struct vhost_dev *dev)
struct vhost_umem *vhost_dev_reset_owner_prepare(void)
void vhost_dev_reset_owner(struct vhost_dev *dev, struct vhost_umem *umem)
void vhost_dev_stop(struct vhost_dev *dev)
static void vhost_umem_free(struct vhost_umem *umem, struct vhost_umem_node *node)
static void vhost_umem_clean(struct vhost_umem *umem)
static void vhost_clear_msg(struct vhost_dev *dev)
void vhost_dev_cleanup(struct vhost_dev *dev)
static bool log_access_ok(void __user *log_base, u64 addr, unsigned long sz)
static bool vhost_overflow(u64 uaddr, u64 size)
static bool vq_memory_access_ok(void __user *log_base, struct vhost_umem *umem, int log_all)
static inline void __user *vhost_vq_meta_fetch(struct vhost_virtqueue *vq, u64 addr, unsigned int size, int type)
static bool memory_access_ok(struct vhost_dev *d, struct vhost_umem *umem, int log_all)
static int vhost_copy_to_user(struct vhost_virtqueue *vq, void __user *to, const void *from, unsigned size)
static int vhost_copy_from_user(struct vhost_virtqueue *vq, void *to, void __user *from, unsigned size)
static void __user *__vhost_get_user_slow(struct vhost_virtqueue *vq, void __user *addr, unsigned int size, int type)
static inline void __user *__vhost_get_user(struct vhost_virtqueue *vq, void *addr, unsigned int size, int type)
static void vhost_dev_lock_vqs(struct vhost_dev *d)
static void vhost_dev_unlock_vqs(struct vhost_dev *d)
static int vhost_new_umem_range(struct vhost_umem *umem, u64 start, u64 size, u64 end, u64 userspace_addr, int perm)
static void vhost_del_umem_range(struct vhost_umem *umem, u64 start, u64 end)
static void vhost_iotlb_notify_vq(struct vhost_dev *d, struct vhost_iotlb_msg *msg)
static bool umem_access_ok(u64 uaddr, u64 size, int access)
static int vhost_process_iotlb_msg(struct vhost_dev *dev, struct vhost_iotlb_msg *msg)
return ret; } ssize_t vhost_chr_write_iter(struct vhost_dev *dev, struct iov_iter *from)
__poll_t vhost_chr_poll(struct file *file, struct vhost_dev *dev, poll_table *wait)
ssize_t vhost_chr_read_iter(struct vhost_dev *dev, struct iov_iter *to, int noblock)
static int vhost_iotlb_miss(struct vhost_virtqueue *vq, u64 iova, int access)
static void vhost_vq_meta_update(struct vhost_virtqueue *vq, const struct vhost_umem_node *node, int type)
static bool iotlb_access_ok(struct vhost_virtqueue *vq, int access, u64 addr, u64 len, int type)
int vq_iotlb_prefetch(struct vhost_virtqueue *vq)
bool vhost_log_access_ok(struct vhost_dev *dev)
static bool vq_log_access_ok(struct vhost_virtqueue *vq, void __user *log_base)
bool vhost_vq_access_ok(struct vhost_virtqueue *vq)
static struct vhost_umem *vhost_umem_alloc(void)
static long vhost_set_memory(struct vhost_dev *d, struct vhost_memory __user *m)
long vhost_vring_ioctl(struct vhost_dev *d, unsigned int ioctl, void __user *argp)
int vhost_init_device_iotlb(struct vhost_dev *d, bool enabled)
long vhost_dev_ioctl(struct vhost_dev *d, unsigned int ioctl, void __user *argp)
static int set_bit_to_user(int nr, void __user *addr)
static int log_write(void __user *log_base, u64 write_address, u64 write_length)
static int log_write_hva(struct vhost_virtqueue *vq, u64 hva, u64 len)
static int log_used(struct vhost_virtqueue *vq, u64 used_offset, u64 len)
int vhost_log_write(struct vhost_virtqueue *vq, struct vhost_log *log, unsigned int log_num, u64 len, struct iovec *iov, int count)
static int vhost_update_used_flags(struct vhost_virtqueue *vq)
static int vhost_update_avail_event(struct vhost_virtqueue *vq, u16 avail_event)
int vhost_vq_init_access(struct vhost_virtqueue *vq)
static int translate_desc(struct vhost_virtqueue *vq, u64 addr, u32 len, struct iovec iov[], int iov_size, int access)
static unsigned next_desc(struct vhost_virtqueue *vq, struct vring_desc *desc)
static int get_indirect(struct vhost_virtqueue *vq, struct iovec iov[], unsigned int iov_size, unsigned int *out_num, unsigned int *in_num, struct vhost_log *log, unsigned int *log_num, struct vring_desc *indirect)
int vhost_get_vq_desc(struct vhost_virtqueue *vq, struct iovec iov[], unsigned int iov_size, unsigned int *out_num, unsigned int *in_num, struct vhost_log *log, unsigned int *log_num)
void vhost_discard_vq_desc(struct vhost_virtqueue *vq, int n)
int vhost_add_used(struct vhost_virtqueue *vq, unsigned int head, int len)
static int __vhost_add_used_n(struct vhost_virtqueue *vq, struct vring_used_elem *heads, unsigned count)
int vhost_add_used_n(struct vhost_virtqueue *vq, struct vring_used_elem *heads, unsigned count)
static bool vhost_notify(struct vhost_dev *dev, struct vhost_virtqueue *vq)
void vhost_signal(struct vhost_dev *dev, struct vhost_virtqueue *vq)
void vhost_add_used_and_signal(struct vhost_dev *dev, struct vhost_virtqueue *vq, unsigned int head, int len)
void vhost_add_used_and_signal_n(struct vhost_dev *dev, struct vhost_virtqueue *vq, struct vring_used_elem *heads, unsigned count)
bool vhost_vq_avail_empty(struct vhost_dev *dev, struct vhost_virtqueue *vq)
bool vhost_enable_notify(struct vhost_dev *dev, struct vhost_virtqueue *vq)
void vhost_disable_notify(struct vhost_dev *dev, struct vhost_virtqueue *vq)
struct vhost_msg_node *vhost_new_msg(struct vhost_virtqueue *vq, int type)
void vhost_enqueue_msg(struct vhost_dev *dev, struct list_head *head, struct vhost_msg_node *node)
struct vhost_msg_node *vhost_dequeue_msg(struct vhost_dev *dev, struct list_head *head)
static int __init vhost_init(void)
static void __exit vhost_exit(void)
\n
     48 struct vhost_virtqueue *vq
     30 struct vhost_dev *dev
      9 struct vhost_dev *d
      7 struct vhost_umem *umem
      6 int type
      5 struct vhost_work *work
      5 struct vhost_poll *poll
      4 void __user *log_base
      4 void
      4 u64 len
      4 u64 addr
      4 int __user *argp
      4 int access
      3 unsigned int size
      3 unsigned count
      3 u64 size
      3 struct vring_used_elem *heads
      3 struct vhost_log *log
      3 struct iovec iov[]
      3 struct file *file
      2 void __user *argp
      2 void __user *addr
      2 vhost_work_fn_t fn
      2 unsigned size
      2 unsigned int *out_num
      2 unsigned int *log_num
      2 unsigned int iov_size
      2 unsigned int ioctl
      2 unsigned int *in_num
      2 unsigned int head
      2 u64 uaddr
      2 u64 start
      2 u64 end
      2 u32 idx
      2 struct vhost_iotlb_msg *msg
      2 struct list_head *head
      2 int log_all
      2 int len
      1 wait_queue_head_t *wqh
      1 wait_queue_entry_t *wait
      1 vq_iotlb_prefetch
      1 vq
      1 void __user *to
      1 void __user *from
      1 void *to
      1 void *key
      1 void *data
      1 void *addr
      1 VIRTIO_F_VERSION_1
      1 vhost_work_queue
      1 vhost_work_init
      1 vhost_work_flush
      1 vhost_vring_ioctl
      1 vhost_vq_init_access
      1 vhost_vq_avail_empty
      1 vhost_vq_access_ok
      1 vhost_signal
      1 vhost_poll_stop
      1 vhost_poll_start
      1 vhost_poll_queue
      1 vhost_poll_init
      1 vhost_poll_flush
      1 vhost_new_msg
      1 vhost_log_write
      1 vhost_log_access_ok
      1 vhost_init_device_iotlb
      1 vhost_has_work
      1 vhost_get_vq_desc
      1 vhost_enqueue_msg
      1 vhost_enable_notify
      1 vhost_discard_vq_desc
      1 vhost_disable_notify
      1 vhost_dev_stop
      1 vhost_dev_set_owner
      1 vhost_dev_reset_owner_prepare
      1 vhost_dev_reset_owner
      1 vhost_dev_ioctl
      1 vhost_dev_init
      1 vhost_dev_has_owner
      1 vhost_dev_cleanup
      1 vhost_dev_check_owner
      1 vhost_dequeue_msg
      1 vhost_chr_read_iter
      1 vhost_add_used_n
      1 vhost_add_used_and_signal_n
      1 vhost_add_used_and_signal
      1 vhost_add_used
      1 unsigned mode
      1 unsigned long sz
      1 unsigned int log_num
      1 u64 write_length
      1 u64 write_address
      1 u64 userspace_addr
      1 u64 used_offset
      1 u64 iova
      1 u64 hva
      1 u32 len
      1 u16 avail_event
      1 struct vring_desc *indirect
      1 struct vring_desc *desc
      1 struct vhost_virtqueue **vqs
      1 struct vhost_umem_node *node
      1 struct vhost_msg_node *node
      1 struct vhost_memory __user *m
      1 struct iov_iter *to
      1 struct iov_iter *from
      1 struct iovec *iov
      1 __poll_t mask
      1 poll_table *wait
      1 poll_table *pt
      1 int sync
      1 int perm
      1 int nvqs
      1 int nr
      1 int noblock
      1 int n
      1 int iov_size
      1 int iov_limit
      1 int count
      1 const void *from
      1 const struct vhost_umem_node *node
      1 bool enabled
