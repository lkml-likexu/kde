
static void cpuid_smp_cpuid(void *cmd_block)
static ssize_t cpuid_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static int cpuid_open(struct inode *inode, struct file *file)
static int cpuid_device_create(unsigned int cpu)
static int cpuid_device_destroy(unsigned int cpu)
static char *cpuid_devnode(struct device *dev, umode_t *mode)
static int __init cpuid_init(void)
static void __exit cpuid_exit(void)
   2 void
   2 unsigned int cpu
   2 struct file *file
   1 void *cmd_block
   1 umode_t *mode
   1 struct inode *inode
   1 struct device *dev
   1 size_t count
   1 loff_t *ppos
   1 char __user *buf
