
int proc_parse_options(char *options, struct pid_namespace *pid)
int proc_remount(struct super_block *sb, int *flags, char *data)
static struct dentry *proc_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
static void proc_kill_sb(struct super_block *sb)
void __init proc_root_init(void)
static int proc_root_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
static struct dentry *proc_root_lookup(struct inode * dir, struct dentry * dentry, unsigned int flags)
static int proc_root_readdir(struct file *file, struct dir_context *ctx)
int pid_ns_prepare_proc(struct pid_namespace *ns)
void pid_ns_release_proc(struct pid_namespace *ns)
   2 struct super_block *sb
   2 struct pid_namespace *ns
   1 void *data
   1 void
   1 unsigned int query_flags
   1 unsigned int flags
   1 u32 request_mask
   1 struct pid_namespace *pid
   1 struct kstat *stat
   1 struct inode * dir
   1 struct file_system_type *fs_type
   1 struct file *file
   1 struct dir_context *ctx
   1 struct dentry * dentry
   1 int flags
   1 int *flags
   1 const struct path *path
   1 const char *dev_name
   1 char *options
   1 char *data
