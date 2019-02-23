
EXPORT_SYMBOL_GPL(fuse_conn_init);
EXPORT_SYMBOL_GPL(fuse_conn_put);
EXPORT_SYMBOL_GPL(fuse_conn_get);
EXPORT_SYMBOL_GPL(fuse_dev_alloc);
EXPORT_SYMBOL_GPL(fuse_dev_free);
\n
struct fuse_forget_link *fuse_alloc_forget(void)
static struct inode *fuse_alloc_inode(struct super_block *sb)
static void fuse_i_callback(struct rcu_head *head)
static void fuse_destroy_inode(struct inode *inode)
static void fuse_evict_inode(struct inode *inode)
static int fuse_remount_fs(struct super_block *sb, int *flags, char *data)
static ino_t fuse_squash_ino(u64 ino64)
void fuse_change_attributes_common(struct inode *inode, struct fuse_attr *attr, u64 attr_valid)
void fuse_change_attributes(struct inode *inode, struct fuse_attr *attr, u64 attr_valid, u64 attr_version)
static void fuse_init_inode(struct inode *inode, struct fuse_attr *attr)
int fuse_inode_eq(struct inode *inode, void *_nodeidp)
static int fuse_inode_set(struct inode *inode, void *_nodeidp)
struct inode *fuse_iget(struct super_block *sb, u64 nodeid, int generation, struct fuse_attr *attr, u64 attr_valid, u64 attr_version)
int fuse_reverse_inval_inode(struct super_block *sb, u64 nodeid, loff_t offset, loff_t len)
bool fuse_lock_inode(struct inode *inode)
void fuse_unlock_inode(struct inode *inode, bool locked)
static void fuse_umount_begin(struct super_block *sb)
static void fuse_send_destroy(struct fuse_conn *fc)
static void fuse_put_super(struct super_block *sb)
static void convert_fuse_statfs(struct kstatfs *stbuf, struct fuse_kstatfs *attr)
static int fuse_statfs(struct dentry *dentry, struct kstatfs *buf)
static int fuse_match_uint(substring_t *s, unsigned int *res)
static int parse_fuse_opt(char *opt, struct fuse_mount_data *d, int is_bdev, struct user_namespace *user_ns)
static int fuse_show_options(struct seq_file *m, struct dentry *root)
static void fuse_iqueue_init(struct fuse_iqueue *fiq)
static void fuse_pqueue_init(struct fuse_pqueue *fpq)
void fuse_conn_init(struct fuse_conn *fc, struct user_namespace *user_ns)
void fuse_conn_put(struct fuse_conn *fc)
struct fuse_conn *fuse_conn_get(struct fuse_conn *fc)
static struct inode *fuse_get_root_inode(struct super_block *sb, unsigned mode)
static struct dentry *fuse_get_dentry(struct super_block *sb, struct fuse_inode_handle *handle)
static int fuse_encode_fh(struct inode *inode, u32 *fh, int *max_len, struct inode *parent)
static struct dentry *fuse_fh_to_dentry(struct super_block *sb, struct fid *fid, int fh_len, int fh_type)
static struct dentry *fuse_fh_to_parent(struct super_block *sb, struct fid *fid, int fh_len, int fh_type)
static struct dentry *fuse_get_parent(struct dentry *child)
static void sanitize_global_limit(unsigned *limit)
static int set_global_limit(const char *val, const struct kernel_param *kp)
static void process_init_limits(struct fuse_conn *fc, struct fuse_init_out *arg)
static void process_init_reply(struct fuse_conn *fc, struct fuse_req *req)
static void fuse_send_init(struct fuse_conn *fc, struct fuse_req *req)
static void fuse_free_conn(struct fuse_conn *fc)
static int fuse_bdi_init(struct fuse_conn *fc, struct super_block *sb)
struct fuse_dev *fuse_dev_alloc(struct fuse_conn *fc)
void fuse_dev_free(struct fuse_dev *fud)
static int fuse_fill_super(struct super_block *sb, void *data, int silent)
static struct dentry *fuse_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *raw_data)
static void fuse_sb_destroy(struct super_block *sb)
static void fuse_kill_sb_anon(struct super_block *sb)
static struct dentry *fuse_mount_blk(struct file_system_type *fs_type, int flags, const char *dev_name, void *raw_data)
static void fuse_kill_sb_blk(struct super_block *sb)
static inline int register_fuseblk(void)
static inline void unregister_fuseblk(void)
static inline void unregister_fuseblk(void)
unregister_filesystem(&fuseblk_fs_type)
; } static inline int register_fuseblk(void)
static inline void unregister_fuseblk(void)
static void fuse_inode_init_once(void *foo)
static int __init fuse_fs_init(void)
static void fuse_fs_cleanup(void)
static int fuse_sysfs_init(void)
static void fuse_sysfs_cleanup(void)
static int __init fuse_init(void)
static void __exit fuse_exit(void)
\n
     15 struct super_block *sb
     12 void
     10 struct inode *inode
     10 struct fuse_conn *fc
      4 struct fuse_attr *attr
      3 u64 attr_valid
      2 void *raw_data
      2 void *_nodeidp
      2 u64 nodeid
      2 u64 attr_version
      2 struct user_namespace *user_ns
      2 struct fuse_req *req
      2 struct file_system_type *fs_type
      2 struct fid *fid
      2 int flags
      2 int fh_type
      2 int fh_len
      2 const char *dev_name
      1 void *foo
      1 void *data
      1 unsigned mode
      1 unsigned *limit
      1 unsigned int *res
      1 u64 ino64
      1 u32 *fh
      1 substring_t *s
      1 struct seq_file *m
      1 struct rcu_head *head
      1 struct kstatfs *stbuf
      1 struct kstatfs *buf
      1 struct inode *parent
      1 struct fuse_pqueue *fpq
      1 struct fuse_mount_data *d
      1 struct fuse_kstatfs *attr
      1 struct fuse_iqueue *fiq
      1 struct fuse_inode_handle *handle
      1 struct fuse_init_out *arg
      1 struct fuse_dev *fud
      1 struct dentry *root
      1 struct dentry *dentry
      1 struct dentry *child
      1 loff_t offset
      1 loff_t len
      1 int silent
      1 int *max_len
      1 int is_bdev
      1 int generation
      1 int *flags
      1 fuse_dev_free
      1 fuse_dev_alloc
      1 fuse_conn_put
      1 fuse_conn_init
      1 fuse_conn_get
      1 &fuseblk_fs_type
      1 const struct kernel_param *kp
      1 const char *val
      1 char *opt
      1 char *data
      1 bool locked
