
\n
static const char *proc_ns_get_link(struct dentry *dentry, struct inode *inode, struct delayed_call *done)
static int proc_ns_readlink(struct dentry *dentry, char __user *buffer, int buflen)
static struct dentry *proc_ns_instantiate(struct dentry *dentry, struct task_struct *task, const void *ptr)
static int proc_ns_dir_readdir(struct file *file, struct dir_context *ctx)
static struct dentry *proc_ns_dir_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
\n
      4 struct dentry *dentry
      1 unsigned int flags
      1 struct task_struct *task
      1 struct inode *inode
      1 struct inode *dir
      1 struct file *file
      1 struct dir_context *ctx
      1 struct delayed_call *done
      1 int buflen
      1 const void *ptr
      1 char __user *buffer
