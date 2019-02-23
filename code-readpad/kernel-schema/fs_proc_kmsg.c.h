
\n
static int kmsg_open(struct inode * inode, struct file * file)
static int kmsg_release(struct inode * inode, struct file * file)
static ssize_t kmsg_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static __poll_t kmsg_poll(struct file *file, poll_table *wait)
static int __init proc_kmsg_init(void)
\n
      2 struct inode * inode
      2 struct file * file
      2 struct file *file
      1 void
      1 size_t count
      1 poll_table *wait
      1 loff_t *ppos
      1 char __user *buf
