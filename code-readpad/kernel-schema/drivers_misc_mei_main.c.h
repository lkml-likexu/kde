
EXPORT_SYMBOL_GPL(mei_register);
EXPORT_SYMBOL_GPL(mei_deregister);
\n
static int mei_open(struct inode *inode, struct file *file)
static int mei_release(struct inode *inode, struct file *file)
static ssize_t mei_read(struct file *file, char __user *ubuf, size_t length, loff_t *offset)
out:cl_dbg(dev, cl, "end mei read rets = %zd\n", rets)
;mutex_unlock(&dev->device_lock)
;return rets; }static ssize_t mei_write(struct file *file, const char __user *ubuf, size_t length, loff_t *offset)
static int mei_ioctl_connect_client(struct file *file, struct mei_connect_client_data *data)
static int mei_ioctl_client_notify_request(const struct file *file, u32 request)
static int mei_ioctl_client_notify_get(const struct file *file, u32 *notify_get)
static long mei_ioctl(struct file *file, unsigned int cmd, unsigned long data)
static long mei_compat_ioctl(struct file *file, unsigned int cmd, unsigned long data)
static __poll_t mei_poll(struct file *file, poll_table *wait)
static bool mei_cl_is_write_queued(struct mei_cl *cl)
static int mei_fsync(struct file *fp, loff_t start, loff_t end, int datasync)
static int mei_fasync(int fd, struct file *file, int band)
static ssize_t fw_status_show(struct device *device, struct device_attribute *attr, char *buf)
static ssize_t hbm_ver_show(struct device *device, struct device_attribute *attr, char *buf)
static ssize_t hbm_ver_drv_show(struct device *device, struct device_attribute *attr, char *buf)
static ssize_t tx_queue_limit_show(struct device *device, struct device_attribute *attr, char *buf)
static ssize_t tx_queue_limit_store(struct device *device, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t fw_ver_show(struct device *device, struct device_attribute *attr, char *buf)
static int mei_minor_get(struct mei_device *dev)
static void mei_minor_free(struct mei_device *dev)
int mei_register(struct mei_device *dev, struct device *parent)
void mei_deregister(struct mei_device *dev)
static int __init mei_init(void)
static void __exit mei_exit(void)
\n
      9 struct file *file
      6 struct device *device
      6 struct device_attribute *attr
      5 char *buf
      4 struct mei_device *dev
      2 void
      2 unsigned long data
      2 unsigned int cmd
      2 struct inode *inode
      2 size_t length
      2 loff_t *offset
      2 const struct file *file
      1 u32 request
      1 u32 *notify_get
      1 struct mei_connect_client_data *data
      1 struct mei_cl *cl
      1 struct file *fp
      1 struct device *parent
      1 size_t count
      1 rets
      1 poll_table *wait
      1 mei_register
      1 mei_deregister
      1 loff_t start
      1 loff_t end
      1 int fd
      1 int datasync
      1 int band
      1 "end mei read rets = %zd\n"
      1 &dev->device_lock
      1 dev
      1 const char __user *ubuf
      1 const char *buf
      1 cl
      1 char __user *ubuf
