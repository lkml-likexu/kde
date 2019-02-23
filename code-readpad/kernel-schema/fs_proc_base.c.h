
\n
static unsigned int __init pid_entry_nlink(const struct pid_entry *entries, unsigned int n)
static int get_task_root(struct task_struct *task, struct path *root)
static int proc_cwd_link(struct dentry *dentry, struct path *path)
static int proc_root_link(struct dentry *dentry, struct path *path)
static ssize_t get_mm_cmdline(struct mm_struct *mm, char __user *buf, size_t count, loff_t *ppos)
static ssize_t get_task_cmdline(struct task_struct *tsk, char __user *buf, size_t count, loff_t *pos)
static ssize_t proc_pid_cmdline_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
static int proc_pid_wchan(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int lock_trace(struct task_struct *task)
static void unlock_trace(struct task_struct *task)
static int proc_pid_stack(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int proc_pid_schedstat(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int lstats_show_proc(struct seq_file *m, void *v)
static int lstats_open(struct inode *inode, struct file *file)
static ssize_t lstats_write(struct file *file, const char __user *buf, size_t count, loff_t *offs)
static int proc_oom_score(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int proc_pid_limits(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int proc_pid_syscall(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int proc_fd_access_allowed(struct inode *inode)
int proc_setattr(struct dentry *dentry, struct iattr *attr)
static bool has_pid_permissions(struct pid_namespace *pid, struct task_struct *task, int hide_pid_min)
static int proc_pid_permission(struct inode *inode, int mask)
static int proc_single_show(struct seq_file *m, void *v)
static int proc_single_open(struct inode *inode, struct file *filp)
struct mm_struct *proc_mem_open(struct inode *inode, unsigned int mode)
static int __mem_open(struct inode *inode, struct file *file, unsigned int mode)
static int mem_open(struct inode *inode, struct file *file)
static ssize_t mem_rw(struct file *file, char __user *buf, size_t count, loff_t *ppos, int write)
static ssize_t mem_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t mem_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
loff_t mem_lseek(struct file *file, loff_t offset, int orig)
static int mem_release(struct inode *inode, struct file *file)
static int environ_open(struct inode *inode, struct file *file)
static ssize_t environ_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static int auxv_open(struct inode *inode, struct file *file)
static ssize_t auxv_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t oom_adj_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static int __set_oom_adj(struct file *file, int oom_adj, bool legacy)
static ssize_t oom_adj_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static ssize_t oom_score_adj_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t oom_score_adj_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
define TMPBUFLEN 11 static ssize_t proc_loginuid_read(struct file * file, char __user * buf, size_t count, loff_t *ppos)
static ssize_t proc_loginuid_write(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
static ssize_t proc_sessionid_read(struct file * file, char __user * buf, size_t count, loff_t *ppos)
static ssize_t proc_fault_inject_read(struct file * file, char __user * buf, size_t count, loff_t *ppos)
static ssize_t proc_fault_inject_write(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
static ssize_t proc_fail_nth_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static ssize_t proc_fail_nth_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static int sched_show(struct seq_file *m, void *v)
static ssize_t sched_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
static int sched_open(struct inode *inode, struct file *filp)
static int sched_autogroup_show(struct seq_file *m, void *v)
static ssize_t sched_autogroup_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
static int sched_autogroup_open(struct inode *inode, struct file *filp)
static ssize_t comm_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
static int comm_show(struct seq_file *m, void *v)
static int comm_open(struct inode *inode, struct file *filp)
static int proc_exe_link(struct dentry *dentry, struct path *exe_path)
static const char *proc_pid_get_link(struct dentry *dentry, struct inode *inode, struct delayed_call *done)
static int do_proc_readlink(struct path *path, char __user *buffer, int buflen)
static int proc_pid_readlink(struct dentry * dentry, char __user * buffer, int buflen)
void task_dump_owner(struct task_struct *task, umode_t mode, kuid_t *ruid, kgid_t *rgid)
struct inode *proc_pid_make_inode(struct super_block * sb, struct task_struct *task, umode_t mode)
int pid_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
void pid_update_inode(struct task_struct *task, struct inode *inode)
static int pid_revalidate(struct dentry *dentry, unsigned int flags)
static inline bool proc_inode_is_dead(struct inode *inode)
int pid_delete_dentry(const struct dentry *dentry)
const struct dentry_operations pid_dentry_operations =bool proc_fill_cache(struct file *file, struct dir_context *ctx, const char *name, unsigned int len, instantiate_t instantiate, struct task_struct *task, const void *ptr)
static int dname_to_vma_addr(struct dentry *dentry, unsigned long *start, unsigned long *end)
static int map_files_d_revalidate(struct dentry *dentry, unsigned int flags)
static int map_files_get_link(struct dentry *dentry, struct path *path)
static const char * proc_map_files_get_link(struct dentry *dentry, struct inode *inode, struct delayed_call *done)
static struct dentry * proc_map_files_instantiate(struct dentry *dentry, struct task_struct *task, const void *ptr)
static struct dentry *proc_map_files_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
static int proc_map_files_readdir(struct file *file, struct dir_context *ctx)
static void *timers_start(struct seq_file *m, loff_t *pos)
static void *timers_next(struct seq_file *m, void *v, loff_t *pos)
static void timers_stop(struct seq_file *m, void *v)
static int show_timer(struct seq_file *m, void *v)
static int proc_timers_open(struct inode *inode, struct file *file)
static ssize_t timerslack_ns_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
static int timerslack_ns_show(struct seq_file *m, void *v)
static int timerslack_ns_open(struct inode *inode, struct file *filp)
static struct dentry *proc_pident_instantiate(struct dentry *dentry, struct task_struct *task, const void *ptr)
static struct dentry *proc_pident_lookup(struct inode *dir, struct dentry *dentry, const struct pid_entry *ents, unsigned int nents)
static int proc_pident_readdir(struct file *file, struct dir_context *ctx, const struct pid_entry *ents, unsigned int nents)
static ssize_t proc_pid_attr_read(struct file * file, char __user * buf, size_t count, loff_t *ppos)
static ssize_t proc_pid_attr_write(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
static int proc_attr_dir_readdir(struct file *file, struct dir_context *ctx)
static struct dentry *proc_attr_dir_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
static ssize_t proc_coredump_filter_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t proc_coredump_filter_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static int do_io_accounting(struct task_struct *task, struct seq_file *m, int whole)
static int proc_tid_io_accounting(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int proc_tgid_io_accounting(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int proc_id_map_open(struct inode *inode, struct file *file, const struct seq_operations *seq_ops)
static int proc_id_map_release(struct inode *inode, struct file *file)
static int proc_uid_map_open(struct inode *inode, struct file *file)
static int proc_gid_map_open(struct inode *inode, struct file *file)
static int proc_projid_map_open(struct inode *inode, struct file *file)
static int proc_setgroups_open(struct inode *inode, struct file *file)
static int proc_setgroups_release(struct inode *inode, struct file *file)
static int proc_pid_personality(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int proc_pid_patch_state(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int proc_stack_depth(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int proc_tgid_base_readdir(struct file *file, struct dir_context *ctx)
static struct dentry *proc_tgid_base_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
static void proc_flush_task_mnt(struct vfsmount *mnt, pid_t pid, pid_t tgid)
void proc_flush_task(struct task_struct *task)
static struct dentry *proc_pid_instantiate(struct dentry * dentry, struct task_struct *task, const void *ptr)
struct dentry *proc_pid_lookup(struct inode *dir, struct dentry * dentry, unsigned int flags)
unsigned int tgid;struct task_struct *task; }; static struct tgid_iter next_tgid(struct pid_namespace *ns, struct tgid_iter iter)
int proc_pid_readdir(struct file *file, struct dir_context *ctx)
static int proc_tid_comm_permission(struct inode *inode, int mask)
static int proc_tid_base_readdir(struct file *file, struct dir_context *ctx)
static struct dentry *proc_tid_base_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
static struct dentry *proc_task_instantiate(struct dentry *dentry, struct task_struct *task, const void *ptr)
static struct dentry *proc_task_lookup(struct inode *dir, struct dentry * dentry, unsigned int flags)
static struct task_struct *first_tid(struct pid *pid, int tid, loff_t f_pos, struct pid_namespace *ns)
static struct task_struct *next_tid(struct task_struct *start)
static int proc_task_readdir(struct file *file, struct dir_context *ctx)
static int proc_task_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
void __init set_proc_pid_nlink(void)
\n
     43 struct file *file
     28 size_t count
     27 struct inode *inode
     25 struct task_struct *task
     22 struct seq_file *m
     21 loff_t *ppos
     18 struct dentry *dentry
     13 struct pid_namespace *ns
     12 struct pid *pid
     11 char __user *buf
     10 const char __user *buf
      9 void *v
      8 unsigned int flags
      8 struct dir_context *ctx
      7 struct inode *dir
      7 struct file * file
      5 struct file *filp
      5 const void *ptr
      4 struct path *path
      4 struct dentry * dentry
      4 loff_t *pos
      4 loff_t *offset
      4 char __user * buf
      3 const char __user * buf
      2 unsigned int query_flags
      2 unsigned int nents
      2 unsigned int mode
      2 umode_t mode
      2 u32 request_mask
      2 struct kstat *stat
      2 struct delayed_call *done
      2 int mask
      2 int buflen
      2 const struct pid_entry *ents
      2 const struct path *path
      1 void
      1 unsigned long *start
      1 unsigned long *end
      1 unsigned int n
      1 unsigned int len
      1 struct vfsmount *mnt
      1 struct tgid_iter iter
      1 struct task_struct *tsk
      1 struct task_struct *start
      1 struct super_block * sb
      1 struct pid_namespace *pid
      1 struct path *root
      1 struct path *exe_path
      1 struct mm_struct *mm
      1 struct iattr *attr
      1 pid_t tgid
      1 pid_t pid
      1 loff_t offset
      1 loff_t *offs
      1 loff_t f_pos
      1 kuid_t *ruid
      1 kgid_t *rgid
      1 int write
      1 int whole
      1 int tid
      1 int orig
      1 int oom_adj
      1 int hide_pid_min
      1 instantiate_t instantiate
      1 const struct seq_operations *seq_ops
      1 const struct pid_entry *entries
      1 const struct dentry *dentry
      1 const char *name
      1 char __user * buffer
      1 char __user *buffer
      1 bool legacy
