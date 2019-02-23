
\n
static int xensyms_next_sym(struct xensyms *xs)
static void *xensyms_start(struct seq_file *m, loff_t *pos)
static void *xensyms_next(struct seq_file *m, void *p, loff_t *pos)
static int xensyms_show(struct seq_file *m, void *p)
static void xensyms_stop(struct seq_file *m, void *p)
static int xensyms_open(struct inode *inode, struct file *file)
static int xensyms_release(struct inode *inode, struct file *file)
\n
      4 struct seq_file *m
      3 void *p
      2 struct inode *inode
      2 struct file *file
      2 loff_t *pos
      1 struct xensyms *xs
