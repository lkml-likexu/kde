
static void show_tty_range(struct seq_file *m, struct tty_driver *p, dev_t from, int num)
static int show_tty_driver(struct seq_file *m, void *v)
static void *t_start(struct seq_file *m, loff_t *pos)
static void *t_next(struct seq_file *m, void *v, loff_t *pos)
static void t_stop(struct seq_file *m, void *v)
void proc_tty_register_driver(struct tty_driver *driver)
void proc_tty_unregister_driver(struct tty_driver *driver)
void __init proc_tty_init(void)
   5 struct seq_file *m
   3 void *v
   2 struct tty_driver *driver
   2 loff_t *pos
   1 void
   1 struct tty_driver *p
   1 int num
   1 dev_t from
