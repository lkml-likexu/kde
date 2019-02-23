
\n
static inline void pp_enable_irq(struct pp_struct *pp)
static ssize_t pp_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t pp_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static void pp_irq(void *private)
static int register_device(int minor, struct pp_struct *pp)
static enum ieee1284_phase init_phase(int mode)
static int pp_set_timeout(struct pardevice *pdev, long tv_sec, int tv_usec)
static int pp_do_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long pp_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long pp_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static int pp_open(struct inode *inode, struct file *file)
static int pp_release(struct inode *inode, struct file *file)
static __poll_t pp_poll(struct file *file, poll_table *wait)
static void pp_attach(struct parport *port)
static void pp_detach(struct parport *port)
static int pp_probe(struct pardevice *par_dev)
static int __init ppdev_init(void)
static void __exit ppdev_cleanup(void)
\n
      8 struct file *file
      3 unsigned long arg
      3 unsigned int cmd
      2 void
      2 struct pp_struct *pp
      2 struct parport *port
      2 struct inode *inode
      2 size_t count
      2 loff_t *ppos
      1 void *private
      1 struct pardevice *pdev
      1 struct pardevice *par_dev
      1 poll_table *wait
      1 long tv_sec
      1 int tv_usec
      1 int mode
      1 int minor
      1 const char __user *buf
      1 char __user *buf
