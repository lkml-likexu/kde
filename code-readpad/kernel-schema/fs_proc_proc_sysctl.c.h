
\n
static bool is_empty_dir(struct ctl_table_header *head)
static void set_empty_dir(struct ctl_dir *dir)
void proc_sys_poll_notify(struct ctl_table_poll *poll)
static void sysctl_print_dir(struct ctl_dir *dir)
static int namecmp(const char *name1, int len1, const char *name2, int len2)
static struct ctl_table *find_entry(struct ctl_table_header **phead, struct ctl_dir *dir, const char *name, int namelen)
static int insert_entry(struct ctl_table_header *head, struct ctl_table *entry)
static void erase_entry(struct ctl_table_header *head, struct ctl_table *entry)
static void init_header(struct ctl_table_header *head, struct ctl_table_root *root, struct ctl_table_set *set, struct ctl_node *node, struct ctl_table *table)
static void erase_header(struct ctl_table_header *head)
static int insert_header(struct ctl_dir *dir, struct ctl_table_header *header)
static int use_table(struct ctl_table_header *p)
static void unuse_table(struct ctl_table_header *p)
static void proc_sys_prune_dcache(struct ctl_table_header *head)
static void start_unregistering(struct ctl_table_header *p)
static struct ctl_table_header *sysctl_head_grab(struct ctl_table_header *head)
static void sysctl_head_finish(struct ctl_table_header *head)
static struct ctl_table_set * lookup_header_set(struct ctl_table_root *root)
static struct ctl_table *lookup_entry(struct ctl_table_header **phead, struct ctl_dir *dir, const char *name, int namelen)
static struct ctl_node *first_usable_entry(struct rb_node *node)
static void first_entry(struct ctl_dir *dir, struct ctl_table_header **phead, struct ctl_table **pentry)
static void next_entry(struct ctl_table_header **phead, struct ctl_table **pentry)
static int test_perm(int mode, int op)
static int sysctl_perm(struct ctl_table_header *head, struct ctl_table *table, int op)
static struct inode *proc_sys_make_inode(struct super_block *sb, struct ctl_table_header *head, struct ctl_table *table)
void proc_sys_evict_inode(struct inode *inode, struct ctl_table_header *head)
static struct ctl_table_header *grab_header(struct inode *inode)
static struct dentry *proc_sys_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
static ssize_t proc_sys_call_handler(struct file *filp, void __user *buf, size_t count, loff_t *ppos, int write)
static ssize_t proc_sys_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
static ssize_t proc_sys_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
static int proc_sys_open(struct inode *inode, struct file *filp)
static __poll_t proc_sys_poll(struct file *filp, poll_table *wait)
static bool proc_sys_fill_cache(struct file *file, struct dir_context *ctx, struct ctl_table_header *head, struct ctl_table *table)
static bool proc_sys_link_fill_cache(struct file *file, struct dir_context *ctx, struct ctl_table_header *head, struct ctl_table *table)
static int scan(struct ctl_table_header *head, struct ctl_table *table, unsigned long *pos, struct file *file, struct dir_context *ctx)
static int proc_sys_readdir(struct file *file, struct dir_context *ctx)
static int proc_sys_permission(struct inode *inode, int mask)
static int proc_sys_setattr(struct dentry *dentry, struct iattr *attr)
static int proc_sys_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
static int proc_sys_revalidate(struct dentry *dentry, unsigned int flags)
static int proc_sys_delete(const struct dentry *dentry)
static int sysctl_is_seen(struct ctl_table_header *p)
static int proc_sys_compare(const struct dentry *dentry, unsigned int len, const char *str, const struct qstr *name)
static struct ctl_dir *find_subdir(struct ctl_dir *dir, const char *name, int namelen)
static struct ctl_dir *new_dir(struct ctl_table_set *set, const char *name, int namelen)
static struct ctl_dir *get_subdir(struct ctl_dir *dir, const char *name, int namelen)
static struct ctl_dir *xlate_dir(struct ctl_table_set *set, struct ctl_dir *dir)
static int sysctl_follow_link(struct ctl_table_header **phead, struct ctl_table **pentry)
static int sysctl_err(const char *path, struct ctl_table *table, char *fmt, ...)
static int sysctl_check_table_array(const char *path, struct ctl_table *table)
static int sysctl_check_table(const char *path, struct ctl_table *table)
static struct ctl_table_header *new_links(struct ctl_dir *dir, struct ctl_table *table, struct ctl_table_root *link_root)
static bool get_links(struct ctl_dir *dir, struct ctl_table *table, struct ctl_table_root *link_root)
static int insert_links(struct ctl_table_header *head)
struct ctl_table_header *__register_sysctl_table(struct ctl_table_set *set, const char *path, struct ctl_table *table)
struct ctl_table_header *register_sysctl(const char *path, struct ctl_table *table)
static char *append_path(const char *path, char *pos, const char *name)
static int count_subheaders(struct ctl_table *table)
static int register_leaf_sysctl_tables(const char *path, char *pos, struct ctl_table_header ***subheader, struct ctl_table_set *set, struct ctl_table *table)
struct ctl_table_header *__register_sysctl_paths(struct ctl_table_set *set, const struct ctl_path *path, struct ctl_table *table)
struct ctl_table_header *register_sysctl_paths(const struct ctl_path *path, struct ctl_table *table)
struct ctl_table_header *register_sysctl_table(struct ctl_table *table)
static void put_links(struct ctl_table_header *header)
static void drop_sysctl_table(struct ctl_table_header *header)
void unregister_sysctl_table(struct ctl_table_header * header)
void setup_sysctl_set(struct ctl_table_set *set, struct ctl_table_root *root, int (*is_seen)
(struct ctl_table_set *)
)
void retire_sysctl_set(struct ctl_table_set *set)
int __init proc_sys_init(void)
\n
     18 struct ctl_table *table
     15 struct ctl_table_header *head
     11 struct ctl_dir *dir
      8 struct ctl_table_set *set
      7 const char *path
      6 const char *name
      5 struct file *filp
      5 struct ctl_table_header **phead
      5 int namelen
      4 struct inode *inode
      4 struct file *file
      4 struct dir_context *ctx
      4 struct ctl_table_header *p
      3 struct dentry *dentry
      3 struct ctl_table_root *root
      3 struct ctl_table **pentry
      3 struct ctl_table_header *header
      3 size_t count
      3 loff_t *ppos
      2 unsigned int flags
      2 struct ctl_table_root *link_root
      2 struct ctl_table *entry
      2 int op
      2 const struct dentry *dentry
      2 const struct ctl_path *path
      2 char *pos
      1 void __user *buf
      1 void
      1 unsigned long *pos
      1 unsigned int query_flags
      1 unsigned int len
      1 u32 request_mask
      1 struct super_block *sb
      1 struct rb_node *node
      1 struct kstat *stat
      1 struct inode *dir
      1 struct iattr *attr
      1 struct ctl_table_set *
      1 struct ctl_table_poll *poll
      1 struct ctl_table_header ***subheader
      1 struct ctl_table_header * header
      1 struct ctl_node *node
      1 poll_table *wait
      1 int write
      1 int mode
      1 int mask
      1 int len2
      1 int len1
      1 int *is_seen
      1 const struct qstr *name
      1 const struct path *path
      1 const char __user *buf
      1 const char *str
      1 const char *name2
      1 const char *name1
      1 char __user *buf
      1 char *fmt
      1 ...
