
EXPORT_SYMBOL_GPL(proc_mkdir_data);
EXPORT_SYMBOL_GPL(proc_get_parent_data);
void pde_free(struct proc_dir_entry *pde)
static int proc_match(const char *name, struct proc_dir_entry *de, unsigned int len)
static struct proc_dir_entry *pde_subdir_first(struct proc_dir_entry *dir)
static struct proc_dir_entry *pde_subdir_next(struct proc_dir_entry *dir)
static struct proc_dir_entry *pde_subdir_find(struct proc_dir_entry *dir, const char *name, unsigned int len)
static bool pde_subdir_insert(struct proc_dir_entry *dir, struct proc_dir_entry *de)
static int proc_notify_change(struct dentry *dentry, struct iattr *iattr)
static int proc_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
static int __xlate_proc_name(const char *name, struct proc_dir_entry **ret, const char **residual)
static int xlate_proc_name(const char *name, struct proc_dir_entry **ret, const char **residual)
int proc_alloc_inum(unsigned int *inum)
void proc_free_inum(unsigned int inum)
static int proc_misc_d_revalidate(struct dentry *dentry, unsigned int flags)
static int proc_misc_d_delete(const struct dentry *dentry)
struct dentry *proc_lookup_de(struct inode *dir, struct dentry *dentry, struct proc_dir_entry *de)
struct dentry *proc_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
int proc_readdir_de(struct file *file, struct dir_context *ctx, struct proc_dir_entry *de)
int proc_readdir(struct file *file, struct dir_context *ctx)
struct proc_dir_entry *proc_register(struct proc_dir_entry *dir, struct proc_dir_entry *dp)
static struct proc_dir_entry *__proc_create(struct proc_dir_entry **parent, const char *name, umode_t mode, nlink_t nlink)
struct proc_dir_entry *proc_symlink(const char *name, struct proc_dir_entry *parent, const char *dest)
struct proc_dir_entry *proc_mkdir_data(const char *name, umode_t mode, struct proc_dir_entry *parent, void *data)
struct proc_dir_entry *proc_mkdir_mode(const char *name, umode_t mode, struct proc_dir_entry *parent)
struct proc_dir_entry *proc_mkdir(const char *name, struct proc_dir_entry *parent)
struct proc_dir_entry *proc_create_mount_point(const char *name)
struct proc_dir_entry *proc_create_reg(const char *name, umode_t mode, struct proc_dir_entry **parent, void *data)
struct proc_dir_entry *proc_create_data(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct file_operations *proc_fops, void *data)
p = proc_create_reg(name, mode, &parent, data)
;if (!p)
return NULL;p->proc_fops = proc_fops;return proc_register(parent, p)
; } EXPORT_SYMBOL(proc_create_data)
; struct proc_dir_entry *proc_create(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct file_operations *proc_fops)
static int proc_seq_open(struct inode *inode, struct file *file)
static int proc_seq_release(struct inode *inode, struct file *file)
struct proc_dir_entry *proc_create_seq_private(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct seq_operations *ops, unsigned int state_size, void *data)
static int proc_single_open(struct inode *inode, struct file *file)
struct proc_dir_entry *proc_create_single_data(const char *name, umode_t mode, struct proc_dir_entry *parent, int (*show)
(struct seq_file *, void *)
, void *data)
void proc_set_size(struct proc_dir_entry *de, loff_t size)
void proc_set_user(struct proc_dir_entry *de, kuid_t uid, kgid_t gid)
void pde_put(struct proc_dir_entry *pde)
void remove_proc_entry(const char *name, struct proc_dir_entry *parent)
int remove_proc_subtree(const char *name, struct proc_dir_entry *parent)
void *proc_get_parent_data(const struct inode *inode)
void proc_remove(struct proc_dir_entry *de)
void *PDE_DATA(const struct inode *inode)
ssize_t proc_simple_write(struct file *f, const char __user *ubuf, size_t size, loff_t *_pos)
  17 const char *name
  10 struct proc_dir_entry *parent
   8 umode_t mode
   7 struct proc_dir_entry *de
   5 struct proc_dir_entry *dir
   5 struct file *file
   4 void *data
   4 struct dentry *dentry
   3 struct inode *inode
   2 unsigned int len
   2 unsigned int flags
   2 struct proc_dir_entry *pde
   2 struct proc_dir_entry **ret
   2 struct proc_dir_entry **parent
   2 struct inode *dir
   2 struct dir_context *ctx
   2 const struct inode *inode
   2 const struct file_operations *proc_fops
   2 const char **residual
   1 void *
   1 unsigned int state_size
   1 unsigned int query_flags
   1 unsigned int inum
   1 unsigned int *inum
   1 u32 request_mask
   1 struct seq_file *
   1 struct proc_dir_entry *dp
   1 struct kstat *stat
   1 struct iattr *iattr
   1 struct file *f
   1 size_t size
   1 proc_mkdir_data
   1 proc_get_parent_data
   1 proc_create_data
   1 parent
   1 p
   1 nlink_t nlink
   1 name
   1 mode
   1 loff_t size
   1 loff_t *_pos
   1 kuid_t uid
   1 kgid_t gid
   1 int *show
   1 data
   1 const struct seq_operations *ops
   1 const struct path *path
   1 const struct dentry *dentry
   1 const char __user *ubuf
   1 const char *dest
   1 &parent
   1 !p
