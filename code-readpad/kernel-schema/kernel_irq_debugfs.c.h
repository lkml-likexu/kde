
\n
static void irq_debug_show_bits(struct seq_file *m, int ind, unsigned int state, const struct irq_bit_descr *sd, int size)
static void irq_debug_show_masks(struct seq_file *m, struct irq_desc *desc)
static void irq_debug_show_chip(struct seq_file *m, struct irq_data *data, int ind)
static void irq_debug_show_data(struct seq_file *m, struct irq_data *data, int ind)
static int irq_debug_show(struct seq_file *m, void *p)
static int irq_debug_open(struct inode *inode, struct file *file)
static ssize_t irq_debug_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
void irq_debugfs_copy_devname(int irq, struct device *dev)
void irq_add_debugfs_entry(unsigned int irq, struct irq_desc *desc)
static int __init irq_debugfs_init(void)
\n
      5 struct seq_file *m
      3 int ind
      2 struct irq_desc *desc
      2 struct irq_data *data
      2 struct file *file
      1 void *p
      1 void
      1 unsigned int state
      1 unsigned int irq
      1 struct inode *inode
      1 struct device *dev
      1 size_t count
      1 loff_t *ppos
      1 int size
      1 int irq
      1 const struct irq_bit_descr *sd
      1 const char __user *user_buf
