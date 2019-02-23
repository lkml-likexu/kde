
\n
static ssize_t msr_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t msr_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static long msr_ioctl(struct file *file, unsigned int ioc, unsigned long arg)
static int msr_open(struct inode *inode, struct file *file)
static int msr_device_create(unsigned int cpu)
static int msr_device_destroy(unsigned int cpu)
static char *msr_devnode(struct device *dev, umode_t *mode)
static int __init msr_init(void)
static void __exit msr_exit(void)
\n
      4 struct file *file
      2 void
      2 unsigned int cpu
      2 size_t count
      2 loff_t *ppos
      1 unsigned long arg
      1 unsigned int ioc
      1 umode_t *mode
      1 struct inode *inode
      1 struct device *dev
      1 const char __user *buf
      1 char __user *buf
