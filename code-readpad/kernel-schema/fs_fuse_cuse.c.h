
\n
static struct cuse_conn *fc_to_cc(struct fuse_conn *fc)
static struct list_head *cuse_conntbl_head(dev_t devt)
static ssize_t cuse_read_iter(struct kiocb *kiocb, struct iov_iter *to)
static ssize_t cuse_write_iter(struct kiocb *kiocb, struct iov_iter *from)
static int cuse_open(struct inode *inode, struct file *file)
static int cuse_release(struct inode *inode, struct file *file)
static long cuse_file_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long cuse_file_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static int cuse_parse_one(char **pp, char *end, char **keyp, char **valp)
static int cuse_parse_devinfo(char *p, size_t len, struct cuse_devinfo *devinfo)
static void cuse_gendev_release(struct device *dev)
static void cuse_process_init_reply(struct fuse_conn *fc, struct fuse_req *req)
static int cuse_send_init(struct cuse_conn *cc)
static void cuse_fc_release(struct fuse_conn *fc)
static int cuse_channel_open(struct inode *inode, struct file *file)
static int cuse_channel_release(struct inode *inode, struct file *file)
static ssize_t cuse_class_waiting_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t cuse_class_abort_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static int __init cuse_init(void)
static void __exit cuse_exit(void)
\n
      6 struct file *file
      4 struct inode *inode
      3 struct fuse_conn *fc
      3 struct device *dev
      2 void
      2 unsigned long arg
      2 unsigned int cmd
      2 struct kiocb *kiocb
      2 struct device_attribute *attr
      1 struct iov_iter *to
      1 struct iov_iter *from
      1 struct fuse_req *req
      1 struct cuse_devinfo *devinfo
      1 struct cuse_conn *cc
      1 size_t len
      1 size_t count
      1 dev_t devt
      1 const char *buf
      1 char **valp
      1 char **pp
      1 char *p
      1 char **keyp
      1 char *end
      1 char *buf
