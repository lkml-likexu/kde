
\n
static long ioctl_restart(struct fsl_hv_ioctl_restart __user *p)
static long ioctl_status(struct fsl_hv_ioctl_status __user *p)
static long ioctl_start(struct fsl_hv_ioctl_start __user *p)
static long ioctl_stop(struct fsl_hv_ioctl_stop __user *p)
static long ioctl_memcpy(struct fsl_hv_ioctl_memcpy __user *p)
static long ioctl_doorbell(struct fsl_hv_ioctl_doorbell __user *p)
static long ioctl_dtprop(struct fsl_hv_ioctl_prop __user *p, int set)
static long fsl_hv_ioctl(struct file *file, unsigned int cmd, unsigned long argaddr)
static void fsl_hv_queue_doorbell(uint32_t doorbell)
static irqreturn_t fsl_hv_isr(int irq, void *data)
static irqreturn_t fsl_hv_state_change_thread(int irq, void *data)
static irqreturn_t fsl_hv_state_change_isr(int irq, void *data)
static __poll_t fsl_hv_poll(struct file *filp, struct poll_table_struct *p)
static ssize_t fsl_hv_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
static int fsl_hv_open(struct inode *inode, struct file *filp)
static int fsl_hv_close(struct inode *inode, struct file *filp)
static irqreturn_t fsl_hv_shutdown_isr(int irq, void *data)
static int get_parent_handle(struct device_node *np)
int fsl_hv_failover_register(struct notifier_block *nb)
int fsl_hv_failover_unregister(struct notifier_block *nb)
static int has_fsl_hypervisor(void)
static int __init fsl_hypervisor_init(void)
static void __exit fsl_hypervisor_exit(void)
\n
      4 void *data
      4 struct file *filp
      4 int irq
      3 void
      2 struct notifier_block *nb
      2 struct inode *inode
      1 unsigned long argaddr
      1 unsigned int cmd
      1 uint32_t doorbell
      1 struct poll_table_struct *p
      1 struct fsl_hv_ioctl_stop __user *p
      1 struct fsl_hv_ioctl_status __user *p
      1 struct fsl_hv_ioctl_start __user *p
      1 struct fsl_hv_ioctl_restart __user *p
      1 struct fsl_hv_ioctl_prop __user *p
      1 struct fsl_hv_ioctl_memcpy __user *p
      1 struct fsl_hv_ioctl_doorbell __user *p
      1 struct file *file
      1 struct device_node *np
      1 size_t len
      1 loff_t *off
      1 int set
      1 char __user *buf
