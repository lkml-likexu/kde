
\n
static void fuse_advise_use_readdirplus(struct inode *dir)
static inline void fuse_dentry_settime(struct dentry *entry, u64 time)
static inline u64 fuse_dentry_time(struct dentry *entry)
static u64 time_to_jiffies(u64 sec, u32 nsec)
void fuse_change_entry_timeout(struct dentry *entry, struct fuse_entry_out *o)
static u64 attr_timeout(struct fuse_attr_out *o)
u64 entry_attr_timeout(struct fuse_entry_out *o)
static void fuse_invalidate_attr_mask(struct inode *inode, u32 mask)
void fuse_invalidate_attr(struct inode *inode)
static void fuse_dir_changed(struct inode *dir)
void fuse_invalidate_atime(struct inode *inode)
void fuse_invalidate_entry_cache(struct dentry *entry)
static void fuse_invalidate_entry(struct dentry *entry)
static void fuse_lookup_init(struct fuse_conn *fc, struct fuse_args *args, u64 nodeid, const struct qstr *name, struct fuse_entry_out *outarg)
u64 fuse_get_attr_version(struct fuse_conn *fc)
static int fuse_dentry_revalidate(struct dentry *entry, unsigned int flags)
static int fuse_dentry_init(struct dentry *dentry)
return dentry->d_fsdata ? 0 : -ENOMEM; } static void fuse_dentry_release(struct dentry *dentry)
int fuse_valid_type(int m)
int fuse_lookup_name(struct super_block *sb, u64 nodeid, const struct qstr *name, struct fuse_entry_out *outarg, struct inode **inode)
static struct dentry *fuse_lookup(struct inode *dir, struct dentry *entry, unsigned int flags)
static int fuse_create_open(struct inode *dir, struct dentry *entry, struct file *file, unsigned flags, umode_t mode)
static int fuse_mknod(struct inode *, struct dentry *, umode_t, dev_t)
; static int fuse_atomic_open(struct inode *dir, struct dentry *entry, struct file *file, unsigned flags, umode_t mode)
static int create_new_entry(struct fuse_conn *fc, struct fuse_args *args, struct inode *dir, struct dentry *entry, umode_t mode)
static int fuse_mknod(struct inode *dir, struct dentry *entry, umode_t mode, dev_t rdev)
static int fuse_create(struct inode *dir, struct dentry *entry, umode_t mode, bool excl)
static int fuse_mkdir(struct inode *dir, struct dentry *entry, umode_t mode)
static int fuse_symlink(struct inode *dir, struct dentry *entry, const char *link)
void fuse_update_ctime(struct inode *inode)
static int fuse_unlink(struct inode *dir, struct dentry *entry)
static int fuse_rmdir(struct inode *dir, struct dentry *entry)
static int fuse_rename_common(struct inode *olddir, struct dentry *oldent, struct inode *newdir, struct dentry *newent, unsigned int flags, int opcode, size_t argsize)
static int fuse_rename2(struct inode *olddir, struct dentry *oldent, struct inode *newdir, struct dentry *newent, unsigned int flags)
static int fuse_link(struct dentry *entry, struct inode *newdir, struct dentry *newent)
static void fuse_fillattr(struct inode *inode, struct fuse_attr *attr, struct kstat *stat)
static int fuse_do_getattr(struct inode *inode, struct kstat *stat, struct file *file)
static int fuse_update_get_attr(struct inode *inode, struct file *file, struct kstat *stat, u32 request_mask, unsigned int flags)
int fuse_update_attributes(struct inode *inode, struct file *file)
int fuse_reverse_inval_entry(struct super_block *sb, u64 parent_nodeid, u64 child_nodeid, struct qstr *name)
int fuse_allow_current_process(struct fuse_conn *fc)
static int fuse_access(struct inode *inode, int mask)
static int fuse_perm_getattr(struct inode *inode, int mask)
static int fuse_permission(struct inode *inode, int mask)
static int fuse_readlink_page(struct inode *inode, struct page *page)
static const char *fuse_get_link(struct dentry *dentry, struct inode *inode, struct delayed_call *callback)
static int fuse_dir_open(struct inode *inode, struct file *file)
static int fuse_dir_release(struct inode *inode, struct file *file)
static int fuse_dir_fsync(struct file *file, loff_t start, loff_t end, int datasync)
static long fuse_dir_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long fuse_dir_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static bool update_mtime(unsigned ivalid, bool trust_local_mtime)
static void iattr_to_fattr(struct fuse_conn *fc, struct iattr *iattr, struct fuse_setattr_in *arg, bool trust_local_cmtime)
void fuse_set_nowrite(struct inode *inode)
static void __fuse_release_nowrite(struct inode *inode)
void fuse_release_nowrite(struct inode *inode)
static void fuse_setattr_fill(struct fuse_conn *fc, struct fuse_args *args, struct inode *inode, struct fuse_setattr_in *inarg_p, struct fuse_attr_out *outarg_p)
int fuse_flush_times(struct inode *inode, struct fuse_file *ff)
int fuse_do_setattr(struct dentry *dentry, struct iattr *attr, struct file *file)
static int fuse_setattr(struct dentry *entry, struct iattr *attr)
static int fuse_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int flags)
void fuse_init_common(struct inode *inode)
void fuse_init_dir(struct inode *inode)
static int fuse_symlink_readpage(struct file *null, struct page *page)
void fuse_init_symlink(struct inode *inode)
\n
     23 struct inode *inode
     18 struct dentry *entry
     12 struct inode *dir
     11 struct file *file
      6 unsigned int flags
      6 umode_t mode
      6 struct fuse_conn *fc
      4 struct kstat *stat
      4 struct dentry *dentry
      3 struct inode *newdir
      3 struct fuse_args *args
      3 struct dentry *newent
      3 int mask
      2 unsigned long arg
      2 unsigned int cmd
      2 unsigned flags
      2 u64 nodeid
      2 u32 request_mask
      2 struct super_block *sb
      2 struct page *page
      2 struct inode *olddir
      2 struct iattr *attr
      2 struct fuse_entry_out *outarg
      2 struct fuse_entry_out *o
      2 struct dentry *oldent
      2 const struct qstr *name
      1 unsigned ivalid
      1 umode_t
      1 u64 time
      1 u64 sec
      1 u64 parent_nodeid
      1 u64 child_nodeid
      1 u32 nsec
      1 u32 mask
      1 struct qstr *name
      1 struct inode **inode
      1 struct inode *
      1 struct iattr *iattr
      1 struct fuse_setattr_in *inarg_p
      1 struct fuse_setattr_in *arg
      1 struct fuse_file *ff
      1 struct fuse_attr_out *outarg_p
      1 struct fuse_attr_out *o
      1 struct fuse_attr *attr
      1 struct file *null
      1 struct dentry *
      1 struct delayed_call *callback
      1 size_t argsize
      1 loff_t start
      1 loff_t end
      1 int opcode
      1 int m
      1 int datasync
      1 dev_t rdev
      1 dev_t
      1 const struct path *path
      1 const char *link
      1 bool trust_local_mtime
      1 bool trust_local_cmtime
      1 bool excl
