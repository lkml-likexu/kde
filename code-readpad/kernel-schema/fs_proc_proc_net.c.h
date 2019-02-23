
EXPORT_SYMBOL_GPL(proc_create_net_data);
EXPORT_SYMBOL_GPL(proc_create_net_data_write);
EXPORT_SYMBOL_GPL(proc_create_net_single);
EXPORT_SYMBOL_GPL(proc_create_net_single_write);
\n
static inline struct net *PDE_NET(struct proc_dir_entry *pde)
static struct net *get_proc_net(const struct inode *inode)
static int proc_net_d_revalidate(struct dentry *dentry, unsigned int flags)
static void pde_force_lookup(struct proc_dir_entry *pde)
static int seq_open_net(struct inode *inode, struct file *file)
static int seq_release_net(struct inode *ino, struct file *f)
struct proc_dir_entry *proc_create_net_data(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct seq_operations *ops, unsigned int state_size, void *data)
struct proc_dir_entry *proc_create_net_data_write(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct seq_operations *ops, proc_write_t write, unsigned int state_size, void *data)
static int single_open_net(struct inode *inode, struct file *file)
static int single_release_net(struct inode *ino, struct file *f)
struct proc_dir_entry *proc_create_net_single(const char *name, umode_t mode, struct proc_dir_entry *parent, int (*show)
(struct seq_file *, void *)
, void *data)
struct proc_dir_entry *proc_create_net_single_write(const char *name, umode_t mode, struct proc_dir_entry *parent, int (*show)
(struct seq_file *, void *)
, proc_write_t write, void *data)
static struct net *get_proc_task_net(struct inode *dir)
static struct dentry *proc_tgid_net_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
static int proc_tgid_net_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
static int proc_tgid_net_readdir(struct file *file, struct dir_context *ctx)
static __net_init int proc_net_ns_init(struct net *net)
static __net_exit void proc_net_ns_exit(struct net *net)
int __init proc_net_init(void)
\n
      4 umode_t mode
      4 struct proc_dir_entry *parent
      4 const char *name
      3 struct file *file
      2 void *data
      2 void *
      2 unsigned int state_size
      2 unsigned int flags
      2 struct seq_file *
      2 struct proc_dir_entry *pde
      2 struct net *net
      2 struct inode *inode
      2 struct inode *ino
      2 struct inode *dir
      2 struct file *f
      2 struct dentry *dentry
      2 int *show
      2 const struct seq_operations *ops
      1 void
      1 unsigned int query_flags
      1 u32 request_mask
      1 struct kstat *stat
      1 struct dir_context *ctx
      1 proc_write_t write
      1 proc_create_net_single_write
      1 proc_create_net_single
      1 proc_create_net_data_write
      1 proc_create_net_data
      1 const struct path *path
      1 const struct inode *inode
