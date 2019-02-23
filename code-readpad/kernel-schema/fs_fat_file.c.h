
EXPORT_SYMBOL_GPL(fat_getattr);
EXPORT_SYMBOL_GPL(fat_setattr);
\n
static int fat_ioctl_get_attributes(struct inode *inode, u32 __user *user_attr)
static int fat_ioctl_set_attributes(struct file *file, u32 __user *user_attr)
static int fat_ioctl_get_volume_id(struct inode *inode, u32 __user *user_attr)
static int fat_ioctl_fitrim(struct inode *inode, unsigned long arg)
long fat_generic_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
static int fat_file_release(struct inode *inode, struct file *filp)
int fat_file_fsync(struct file *filp, loff_t start, loff_t end, int datasync)
static int fat_cont_expand(struct inode *inode, loff_t size)
static long fat_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
static int fat_free(struct inode *inode, int skip)
void fat_truncate_blocks(struct inode *inode, loff_t offset)
int fat_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int flags)
static int fat_sanitize_mode(const struct msdos_sb_info *sbi, struct inode *inode, umode_t *mode_ptr)
static int fat_allow_set_time(struct msdos_sb_info *sbi, struct inode *inode)
int fat_setattr(struct dentry *dentry, struct iattr *attr)
\n
      9 struct inode *inode
      3 u32 __user *user_attr
      3 struct file *filp
      2 unsigned long arg
      2 struct file *file
      2 loff_t offset
      1 unsigned int flags
      1 unsigned int cmd
      1 umode_t *mode_ptr
      1 u32 request_mask
      1 struct msdos_sb_info *sbi
      1 struct kstat *stat
      1 struct iattr *attr
      1 struct dentry *dentry
      1 loff_t start
      1 loff_t size
      1 loff_t len
      1 loff_t end
      1 int skip
      1 int mode
      1 int datasync
      1 fat_setattr
      1 fat_getattr
      1 const struct path *path
      1 const struct msdos_sb_info *sbi
