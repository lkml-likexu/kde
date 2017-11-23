
static ssize_t kpagecount_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static inline u64 kpf_copy_bit(u64 kflags, int ubit, int kbit)
u64 stable_page_flags(struct page *page)
static ssize_t kpageflags_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t kpagecgroup_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static int __init proc_page_init(void)
   3 struct file *file
   3 size_t count
   3 loff_t *ppos
   3 char __user *buf
   1 void
   1 u64 kflags
   1 struct page *page
   1 int ubit
   1 int kbit
