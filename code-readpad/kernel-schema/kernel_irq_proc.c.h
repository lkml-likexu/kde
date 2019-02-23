
\n
static int show_irq_affinity(int type, struct seq_file *m)
static int irq_affinity_hint_proc_show(struct seq_file *m, void *v)
int no_irq_affinity; static int irq_affinity_proc_show(struct seq_file *m, void *v)
static int irq_affinity_list_proc_show(struct seq_file *m, void *v)
static ssize_t write_irq_affinity(int type, struct file *file, const char __user *buffer, size_t count, loff_t *pos)
static ssize_t irq_affinity_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
static ssize_t irq_affinity_list_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
static int irq_affinity_proc_open(struct inode *inode, struct file *file)
static int irq_affinity_list_proc_open(struct inode *inode, struct file *file)
static int irq_effective_aff_proc_show(struct seq_file *m, void *v)
static int irq_effective_aff_list_proc_show(struct seq_file *m, void *v)
static int default_affinity_show(struct seq_file *m, void *v)
static ssize_t default_affinity_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
static int default_affinity_open(struct inode *inode, struct file *file)
static int irq_node_proc_show(struct seq_file *m, void *v)
static int irq_spurious_proc_show(struct seq_file *m, void *v)
static int name_unique(unsigned int irq, struct irqaction *new_action)
void register_handler_proc(unsigned int irq, struct irqaction *action)
void register_irq_proc(unsigned int irq, struct irq_desc *desc)
void unregister_irq_proc(unsigned int irq, struct irq_desc *desc)
void unregister_handler_proc(unsigned int irq, struct irqaction *action)
static void register_default_affinity_proc(void)
void init_irq_proc(void)
int __weak arch_show_interrupts(struct seq_file *p, int prec)
int show_interrupts(struct seq_file *p, void *v)
\n
      9 void *v
      9 struct seq_file *m
      7 struct file *file
      5 unsigned int irq
      4 size_t count
      4 const char __user *buffer
      3 struct inode *inode
      3 loff_t *pos
      2 void
      2 struct seq_file *p
      2 struct irq_desc *desc
      2 struct irqaction *action
      2 int type
      1 struct irqaction *new_action
      1 loff_t *ppos
      1 int prec
