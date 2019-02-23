
EXPORT_SYMBOL_GPL(hiddev_hid_event);
\n
static struct hid_report * hiddev_lookup_report(struct hid_device *hid, struct hiddev_report_info *rinfo)
static struct hid_field * hiddev_lookup_usage(struct hid_device *hid, struct hiddev_usage_ref *uref)
static void hiddev_send_event(struct hid_device *hid, struct hiddev_usage_ref *uref)
void hiddev_hid_event(struct hid_device *hid, struct hid_field *field, struct hid_usage *usage, __s32 value)
void hiddev_report_event(struct hid_device *hid, struct hid_report *report)
static int hiddev_fasync(int fd, struct file *file, int on)
static int hiddev_release(struct inode * inode, struct file * file)
static int hiddev_open(struct inode *inode, struct file *file)
static ssize_t hiddev_write(struct file * file, const char __user * buffer, size_t count, loff_t *ppos)
static ssize_t hiddev_read(struct file * file, char __user * buffer, size_t count, loff_t *ppos)
static __poll_t hiddev_poll(struct file *file, poll_table *wait)
static noinline int hiddev_ioctl_usage(struct hiddev *hiddev, unsigned int cmd, void __user *user_arg)
static noinline int hiddev_ioctl_string(struct hiddev *hiddev, unsigned int cmd, void __user *user_arg)
static long hiddev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long hiddev_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static char *hiddev_devnode(struct device *dev, umode_t *mode)
int hiddev_connect(struct hid_device *hid, unsigned int force)
static struct usb_class_driver hiddev_class; void hiddev_disconnect(struct hid_device *hid)
\n
      7 struct hid_device *hid
      5 struct file *file
      4 unsigned int cmd
      3 struct file * file
      2 void __user *user_arg
      2 unsigned long arg
      2 struct hiddev_usage_ref *uref
      2 struct hiddev *hiddev
      2 size_t count
      2 loff_t *ppos
      1 unsigned int force
      1 umode_t *mode
      1 struct inode * inode
      1 struct inode *inode
      1 struct hid_usage *usage
      1 struct hid_report *report
      1 struct hid_field *field
      1 struct hiddev_report_info *rinfo
      1 struct device *dev
      1 __s32 value
      1 poll_table *wait
      1 int on
      1 int fd
      1 hiddev_hid_event
      1 const char __user * buffer
      1 char __user * buffer
