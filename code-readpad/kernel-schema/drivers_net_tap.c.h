
EXPORT_SYMBOL_GPL(tap_del_queues);
EXPORT_SYMBOL_GPL(tap_handle_frame);
EXPORT_SYMBOL_GPL(tap_get_minor);
EXPORT_SYMBOL_GPL(tap_free_minor);
EXPORT_SYMBOL_GPL(tap_get_socket);
EXPORT_SYMBOL_GPL(tap_get_ptr_ring);
EXPORT_SYMBOL_GPL(tap_queue_resize);
EXPORT_SYMBOL_GPL(tap_create_cdev);
EXPORT_SYMBOL_GPL(tap_destroy_cdev);
\n
static inline bool tap_legacy_is_little_endian(struct tap_queue *q)
static long tap_get_vnet_be(struct tap_queue *q, int __user *sp)
static long tap_set_vnet_be(struct tap_queue *q, int __user *sp)
return 0; } static inline bool tap_legacy_is_little_endian(struct tap_queue *q)
static long tap_get_vnet_be(struct tap_queue *q, int __user *argp)
static long tap_set_vnet_be(struct tap_queue *q, int __user *argp)
static inline bool tap_is_little_endian(struct tap_queue *q)
static inline u16 tap16_to_cpu(struct tap_queue *q, __virtio16 val)
static inline __virtio16 cpu_to_tap16(struct tap_queue *q, u16 val)
static struct tap_dev *tap_dev_get_rcu(const struct net_device *dev)
static int tap_enable_queue(struct tap_dev *tap, struct file *file, struct tap_queue *q)
static int tap_set_queue(struct tap_dev *tap, struct file *file, struct tap_queue *q)
static int tap_disable_queue(struct tap_queue *q)
static void tap_put_queue(struct tap_queue *q)
static struct tap_queue *tap_get_queue(struct tap_dev *tap, struct sk_buff *skb)
void tap_del_queues(struct tap_dev *tap)
rx_handler_result_t tap_handle_frame(struct sk_buff **pskb)
static struct major_info *tap_get_major(int major)
int tap_get_minor(dev_t major, struct tap_dev *tap)
void tap_free_minor(dev_t major, struct tap_dev *tap)
static struct tap_dev *dev_get_by_tap_file(int major, int minor)
static void tap_sock_write_space(struct sock *sk)
static void tap_sock_destruct(struct sock *sk)
static int tap_open(struct inode *inode, struct file *file)
static int tap_release(struct inode *inode, struct file *file)
static __poll_t tap_poll(struct file *file, poll_table *wait)
static inline struct sk_buff *tap_alloc_skb(struct sock *sk, size_t prepad, size_t len, size_t linear, int noblock, int *err)
static ssize_t tap_get_user(struct tap_queue *q, void *msg_control, struct iov_iter *from, int noblock)
static ssize_t tap_write_iter(struct kiocb *iocb, struct iov_iter *from)
static ssize_t tap_put_user(struct tap_queue *q, const struct sk_buff *skb, struct iov_iter *iter)
static ssize_t tap_do_read(struct tap_queue *q, struct iov_iter *to, int noblock, struct sk_buff *skb)
static ssize_t tap_read_iter(struct kiocb *iocb, struct iov_iter *to)
static struct tap_dev *tap_get_tap_dev(struct tap_queue *q)
static void tap_put_tap_dev(struct tap_dev *tap)
static int tap_ioctl_set_queue(struct file *file, unsigned int flags)
static int set_offload(struct tap_queue *q, unsigned long arg)
static long tap_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long tap_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static int tap_get_user_xdp(struct tap_queue *q, struct xdp_buff *xdp)
static int tap_sendmsg(struct socket *sock, struct msghdr *m, size_t total_len)
static int tap_recvmsg(struct socket *sock, struct msghdr *m, size_t total_len, int flags)
static int tap_peek_len(struct socket *sock)
struct socket *tap_get_socket(struct file *file)
struct ptr_ring *tap_get_ptr_ring(struct file *file)
int tap_queue_resize(struct tap_dev *tap)
static int tap_list_add(dev_t major, const char *device_name)
int tap_create_cdev(struct cdev *tap_cdev, dev_t *tap_major, const char *device_name, struct module *module)
void tap_destroy_cdev(dev_t major, struct cdev *tap_cdev)
\n
     19 struct tap_queue *q
     10 struct file *file
      8 struct tap_dev *tap
      4 dev_t major
      3 unsigned long arg
      3 struct sock *sk
      3 struct socket *sock
      3 int noblock
      2 unsigned int cmd
      2 struct sk_buff *skb
      2 struct msghdr *m
      2 struct kiocb *iocb
      2 struct iov_iter *to
      2 struct iov_iter *from
      2 struct inode *inode
      2 struct cdev *tap_cdev
      2 size_t total_len
      2 int __user *sp
      2 int __user *argp
      2 int major
      2 const char *device_name
      1 void *msg_control
      1 __virtio16 val
      1 unsigned int flags
      1 u16 val
      1 tap_queue_resize
      1 tap_handle_frame
      1 tap_get_socket
      1 tap_get_ptr_ring
      1 tap_get_minor
      1 tap_free_minor
      1 tap_destroy_cdev
      1 tap_del_queues
      1 tap_create_cdev
      1 struct xdp_buff *xdp
      1 struct sk_buff **pskb
      1 struct module *module
      1 struct iov_iter *iter
      1 size_t prepad
      1 size_t linear
      1 size_t len
      1 poll_table *wait
      1 int minor
      1 int flags
      1 int *err
      1 dev_t *tap_major
      1 const struct sk_buff *skb
      1 const struct net_device *dev
