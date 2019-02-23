
\n
static int get_exclusive(struct ubi_volume_desc *desc)
static void revoke_exclusive(struct ubi_volume_desc *desc, int mode)
static int vol_cdev_open(struct inode *inode, struct file *file)
static int vol_cdev_release(struct inode *inode, struct file *file)
static loff_t vol_cdev_llseek(struct file *file, loff_t offset, int origin)
static int vol_cdev_fsync(struct file *file, loff_t start, loff_t end, int datasync)
static ssize_t vol_cdev_read(struct file *file, __user char *buf, size_t count, loff_t *offp)
static ssize_t vol_cdev_direct_write(struct file *file, const char __user *buf, size_t count, loff_t *offp)
static ssize_t vol_cdev_write(struct file *file, const char __user *buf, size_t count, loff_t *offp)
static long vol_cdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static int verify_mkvol_req(const struct ubi_device *ubi, const struct ubi_mkvol_req *req)
static int verify_rsvol_req(const struct ubi_device *ubi, const struct ubi_rsvol_req *req)
static int rename_volumes(struct ubi_device *ubi, struct ubi_rnvol_req *req)
static long ubi_cdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long ctrl_cdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long vol_cdev_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long ubi_cdev_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long ctrl_cdev_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
\n
     13 struct file *file
      6 unsigned long arg
      6 unsigned int cmd
      3 size_t count
      3 loff_t *offp
      2 struct ubi_volume_desc *desc
      2 struct inode *inode
      2 const struct ubi_device *ubi
      2 const char __user *buf
      1 __user char *buf
      1 struct ubi_rnvol_req *req
      1 struct ubi_device *ubi
      1 loff_t start
      1 loff_t offset
      1 loff_t end
      1 int origin
      1 int mode
      1 int datasync
      1 const struct ubi_rsvol_req *req
      1 const struct ubi_mkvol_req *req
