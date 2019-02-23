
\n
static int seq_show(struct seq_file *m, void *v)
static int seq_fdinfo_open(struct inode *inode, struct file *file)
static bool tid_fd_mode(struct task_struct *task, unsigned fd, fmode_t *mode)
static void tid_fd_update_inode(struct task_struct *task, struct inode *inode, fmode_t f_mode)
static int tid_fd_revalidate(struct dentry *dentry, unsigned int flags)
static int proc_fd_link(struct dentry *dentry, struct path *path)
static struct dentry *proc_fd_instantiate(struct dentry *dentry, struct task_struct *task, const void *ptr)
static struct dentry *proc_lookupfd_common(struct inode *dir, struct dentry *dentry, instantiate_t instantiate)
static int proc_readfd_common(struct file *file, struct dir_context *ctx, instantiate_t instantiate)
static int proc_readfd(struct file *file, struct dir_context *ctx)
static struct dentry *proc_lookupfd(struct inode *dir, struct dentry *dentry, unsigned int flags)
int proc_fd_permission(struct inode *inode, int mask)
static struct dentry *proc_fdinfo_instantiate(struct dentry *dentry, struct task_struct *task, const void *ptr)
static struct dentry * proc_lookupfdinfo(struct inode *dir, struct dentry *dentry, unsigned int flags)
static int proc_readfdinfo(struct file *file, struct dir_context *ctx)
\n
      7 struct dentry *dentry
      4 struct task_struct *task
      4 struct file *file
      3 unsigned int flags
      3 struct inode *inode
      3 struct inode *dir
      3 struct dir_context *ctx
      2 instantiate_t instantiate
      2 const void *ptr
      1 void *v
      1 unsigned fd
      1 struct seq_file *m
      1 struct path *path
      1 int mask
      1 fmode_t *mode
      1 fmode_t f_mode
