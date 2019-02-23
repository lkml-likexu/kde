
\n
static ssize_t vtpm_proxy_fops_read(struct file *filp, char __user *buf, size_t count, loff_t *off)
static ssize_t vtpm_proxy_fops_write(struct file *filp, const char __user *buf, size_t count, loff_t *off)
static __poll_t vtpm_proxy_fops_poll(struct file *filp, poll_table *wait)
static void vtpm_proxy_fops_open(struct file *filp)
static void vtpm_proxy_fops_undo_open(struct proxy_dev *proxy_dev)
static int vtpm_proxy_fops_release(struct inode *inode, struct file *filp)
static int vtpm_proxy_tpm_op_recv(struct tpm_chip *chip, u8 *buf, size_t count)
static int vtpm_proxy_is_driver_command(struct tpm_chip *chip, u8 *buf, size_t count)
static int vtpm_proxy_tpm_op_send(struct tpm_chip *chip, u8 *buf, size_t count)
static void vtpm_proxy_tpm_op_cancel(struct tpm_chip *chip)
static u8 vtpm_proxy_tpm_op_status(struct tpm_chip *chip)
static bool vtpm_proxy_tpm_req_canceled(struct tpm_chip*chip, u8 status)
static int vtpm_proxy_request_locality(struct tpm_chip *chip, int locality)
static void vtpm_proxy_work(struct work_struct *work)
static void vtpm_proxy_work_stop(struct proxy_dev *proxy_dev)
static inline void vtpm_proxy_work_start(struct proxy_dev *proxy_dev)
static struct proxy_dev *vtpm_proxy_create_proxy_dev(void)
static inline void vtpm_proxy_delete_proxy_dev(struct proxy_dev *proxy_dev)
static struct file *vtpm_proxy_create_device(struct vtpm_proxy_new_dev *vtpm_new_dev)
static void vtpm_proxy_delete_device(struct proxy_dev *proxy_dev)
static long vtpmx_ioc_new_dev(struct file *file, unsigned int ioctl, unsigned long arg)
static long vtpmx_fops_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
static long vtpmx_fops_compat_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
static int vtpmx_init(void)
static void vtpmx_cleanup(void)
static int __init vtpm_module_init(void)
static void __exit vtpm_module_exit(void)
\n
      6 struct tpm_chip *chip
      5 void
      5 struct proxy_dev *proxy_dev
      5 struct file *filp
      5 size_t count
      3 unsigned long arg
      3 unsigned int ioctl
      3 u8 *buf
      2 struct file *f
      2 loff_t *off
      1 u8 status
      1 struct work_struct *work
      1 struct vtpm_proxy_new_dev *vtpm_new_dev
      1 struct tpm_chip*chip
      1 struct inode *inode
      1 struct file *file
      1 poll_table *wait
      1 int locality
      1 const char __user *buf
      1 char __user *buf
