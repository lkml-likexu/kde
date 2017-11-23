
static int show_console_dev(struct seq_file *m, void *v)
static void *c_start(struct seq_file *m, loff_t *pos)
static void *c_next(struct seq_file *m, void *v, loff_t *pos)
static void c_stop(struct seq_file *m, void *v)
static int __init proc_consoles_init(void)
   4 struct seq_file *m
   3 void *v
   2 loff_t *pos
   1 void
