
\n
static void proc_evict_inode(struct inode *inode)
static struct inode *proc_alloc_inode(struct super_block *sb)
static void proc_i_callback(struct rcu_head *head)
static void proc_destroy_inode(struct inode *inode)
static void init_once(void *foo)
void __init proc_init_kmemcache(void)
static int proc_show_options(struct seq_file *seq, struct dentry *root)
static inline int use_pde(struct proc_dir_entry *pde)
static void unuse_pde(struct proc_dir_entry *pde)
static void close_pdeo(struct proc_dir_entry *pde, struct pde_opener *pdeo)
void proc_entry_rundown(struct proc_dir_entry *de)
static loff_t proc_reg_llseek(struct file *file, loff_t offset, int whence)
static ssize_t proc_reg_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t proc_reg_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static __poll_t proc_reg_poll(struct file *file, struct poll_table_struct *pts)
static long proc_reg_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long proc_reg_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static int proc_reg_mmap(struct file *file, struct vm_area_struct *vma)
static unsigned long proc_reg_get_unmapped_area(struct file *file, unsigned long orig_addr, unsigned long len, unsigned long pgoff, unsigned long flags)
static int proc_reg_open(struct inode *inode, struct file *file)
static int proc_reg_release(struct inode *inode, struct file *file)
static void proc_put_link(void *p)
static const char *proc_get_link(struct dentry *dentry, struct inode *inode, struct delayed_call *done)
struct inode *proc_get_inode(struct super_block *sb, struct proc_dir_entry *de)
int proc_fill_super(struct super_block *s, void *data, int silent)
\n
     10 struct file *file
      5 struct inode *inode
      3 struct proc_dir_entry *pde
      2 unsigned long arg
      2 unsigned int cmd
      2 struct super_block *sb
      2 struct proc_dir_entry *de
      2 size_t count
      2 loff_t *ppos
      1 void *p
      1 void *foo
      1 void *data
      1 void
      1 unsigned long pgoff
      1 unsigned long orig_addr
      1 unsigned long len
      1 unsigned long flags
      1 struct vm_area_struct *vma
      1 struct super_block *s
      1 struct seq_file *seq
      1 struct rcu_head *head
      1 struct poll_table_struct *pts
      1 struct pde_opener *pdeo
      1 struct dentry *root
      1 struct dentry *dentry
      1 struct delayed_call *done
      1 loff_t offset
      1 int whence
      1 int silent
      1 const char __user *buf
      1 char __user *buf
