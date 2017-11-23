
static void *int_seq_start(struct seq_file *f, loff_t *pos)
static void *int_seq_next(struct seq_file *f, void *v, loff_t *pos)
static void int_seq_stop(struct seq_file *f, void *v)
static int __init proc_interrupts_init(void)
   3 struct seq_file *f
   2 void *v
   2 loff_t *pos
   1 void
