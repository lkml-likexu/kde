
EXPORT_SYMBOL_GPL(kernfs_notify);
static struct kernfs_open_file *kernfs_of(struct file *file)
static const struct kernfs_ops *kernfs_ops(struct kernfs_node *kn)
static void kernfs_seq_stop_active(struct seq_file *sf, void *v)
static void *kernfs_seq_start(struct seq_file *sf, loff_t *ppos)
static void *kernfs_seq_next(struct seq_file *sf, void *v, loff_t *ppos)
static void kernfs_seq_stop(struct seq_file *sf, void *v)
static int kernfs_seq_show(struct seq_file *sf, void *v)
static ssize_t kernfs_file_direct_read(struct kernfs_open_file *of, char __user *user_buf, size_t count, loff_t *ppos)
static ssize_t kernfs_fop_read(struct file *file, char __user *user_buf, size_t count, loff_t *ppos)
static ssize_t kernfs_fop_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
static void kernfs_vma_open(struct vm_area_struct *vma)
static vm_fault_t kernfs_vma_fault(struct vm_fault *vmf)
static vm_fault_t kernfs_vma_page_mkwrite(struct vm_fault *vmf)
static int kernfs_vma_access(struct vm_area_struct *vma, unsigned long addr, void *buf, int len, int write)
static int kernfs_vma_set_policy(struct vm_area_struct *vma, struct mempolicy *new)
static struct mempolicy *kernfs_vma_get_policy(struct vm_area_struct *vma, unsigned long addr)
static int kernfs_fop_mmap(struct file *file, struct vm_area_struct *vma)
static int kernfs_get_open_node(struct kernfs_node *kn, struct kernfs_open_file *of)
static void kernfs_put_open_node(struct kernfs_node *kn, struct kernfs_open_file *of)
static int kernfs_fop_open(struct inode *inode, struct file *file)
static void kernfs_release_file(struct kernfs_node *kn, struct kernfs_open_file *of)
static int kernfs_fop_release(struct inode *inode, struct file *filp)
void kernfs_drain_open_files(struct kernfs_node *kn)
static __poll_t kernfs_fop_poll(struct file *filp, poll_table *wait)
static void kernfs_notify_workfn(struct work_struct *work)
void kernfs_notify(struct kernfs_node *kn)
struct kernfs_node *__kernfs_create_file(struct kernfs_node *parent, const char *name, umode_t mode, kuid_t uid, kgid_t gid, loff_t size, const struct kernfs_ops *ops, void *priv, const void *ns, struct lock_class_key *key)
   6 struct kernfs_node *kn
   5 struct vm_area_struct *vma
   5 struct seq_file *sf
   5 struct file *file
   5 loff_t *ppos
   4 void *v
   4 struct kernfs_open_file *of
   3 size_t count
   2 unsigned long addr
   2 struct vm_fault *vmf
   2 struct inode *inode
   2 struct file *filp
   2 char __user *user_buf
   1 void *priv
   1 void *buf
   1 umode_t mode
   1 struct work_struct *work
   1 struct mempolicy *new
   1 struct lock_class_key *key
   1 struct kernfs_node *parent
   1 poll_table *wait
   1 loff_t size
   1 kuid_t uid
   1 kgid_t gid
   1 kernfs_notify
   1 int write
   1 int len
   1 const void *ns
   1 const struct kernfs_ops *ops
   1 const char __user *user_buf
   1 const char *name
