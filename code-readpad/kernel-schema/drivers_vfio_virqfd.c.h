
EXPORT_SYMBOL_GPL(vfio_virqfd_enable);
EXPORT_SYMBOL_GPL(vfio_virqfd_disable);
\n
static int __init vfio_virqfd_init(void)
static void __exit vfio_virqfd_exit(void)
static void virqfd_deactivate(struct virqfd *virqfd)
static int virqfd_wakeup(wait_queue_entry_t *wait, unsigned mode, int sync, void *key)
static void virqfd_ptable_queue_proc(struct file *file, wait_queue_head_t *wqh, poll_table *pt)
static void virqfd_shutdown(struct work_struct *work)
static void virqfd_inject(struct work_struct *work)
int vfio_virqfd_enable(void *opaque, int (*handler)
(void *, void *)
, void (*thread)
(void *, void *)
, void *data, struct virqfd **pvirqfd, int fd)
void vfio_virqfd_disable(struct virqfd **pvirqfd)
\n
      4 void *
      2 void
      2 struct work_struct *work
      1 wait_queue_head_t *wqh
      1 wait_queue_entry_t *wait
      1 void *opaque
      1 void *key
      1 vfio_virqfd_enable
      1 vfio_virqfd_disable
      1 unsigned mode
      1 *thread
      1 struct virqfd *virqfd
      1 struct virqfd **pvirqfd
      1 struct file *file
      1 poll_table *pt
      1 int sync
      1 int *handler
