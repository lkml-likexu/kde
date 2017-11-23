
static void handle_vq(struct vhost_test *n)
static void handle_vq_kick(struct vhost_work *work)
static int vhost_test_open(struct inode *inode, struct file *f)
static void *vhost_test_stop_vq(struct vhost_test *n, struct vhost_virtqueue *vq)
static void vhost_test_stop(struct vhost_test *n, void **privatep)
static void vhost_test_flush_vq(struct vhost_test *n, int index)
static void vhost_test_flush(struct vhost_test *n)
static int vhost_test_release(struct inode *inode, struct file *f)
static long vhost_test_run(struct vhost_test *n, int test)
static long vhost_test_reset_owner(struct vhost_test *n)
static int vhost_test_set_features(struct vhost_test *n, u64 features)
static long vhost_test_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
static long vhost_test_compat_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
   8 struct vhost_test *n
   4 struct file *f
   2 unsigned long arg
   2 unsigned int ioctl
   2 struct inode *inode
   1 void **privatep
   1 u64 features
   1 struct vhost_work *work
   1 struct vhost_virtqueue *vq
   1 int test
   1 int index
