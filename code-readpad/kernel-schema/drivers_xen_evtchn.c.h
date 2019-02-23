
\n
static void evtchn_free_ring(evtchn_port_t *ring)
static unsigned int evtchn_ring_offset(struct per_user_data *u, unsigned int idx)
static evtchn_port_t *evtchn_ring_entry(struct per_user_data *u, unsigned int idx)
static int add_evtchn(struct per_user_data *u, struct user_evtchn *evtchn)
static void del_evtchn(struct per_user_data *u, struct user_evtchn *evtchn)
static struct user_evtchn *find_evtchn(struct per_user_data *u, unsigned port)
static irqreturn_t evtchn_interrupt(int irq, void *data)
static ssize_t evtchn_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t evtchn_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static int evtchn_resize_ring(struct per_user_data *u)
static int evtchn_bind_to_user(struct per_user_data *u, int port)
static void evtchn_unbind_from_user(struct per_user_data *u, struct user_evtchn *evtchn)
static void evtchn_bind_interdom_next_vcpu(int evtchn)
static long evtchn_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static __poll_t evtchn_poll(struct file *file, poll_table *wait)
static int evtchn_fasync(int fd, struct file *filp, int on)
static int evtchn_open(struct inode *inode, struct file *filp)
static int evtchn_release(struct inode *inode, struct file *filp)
.minor= MISC_DYNAMIC_MINOR, .name = "xen/evtchn", .fops = &evtchn_fops, }; static int __init evtchn_init(void)
static void __exit evtchn_cleanup(void)
\n
      8 struct per_user_data *u
      4 struct file *file
      3 struct user_evtchn *evtchn
      3 struct file *filp
      2 void
      2 unsigned int idx
      2 struct inode *inode
      2 size_t count
      2 loff_t *ppos
      1 void *data
      1 unsigned port
      1 unsigned long arg
      1 unsigned int cmd
      1 poll_table *wait
      1 int port
      1 int on
      1 int irq
      1 int fd
      1 int evtchn
      1 evtchn_port_t *ring
      1 const char __user *buf
      1 char __user *buf
