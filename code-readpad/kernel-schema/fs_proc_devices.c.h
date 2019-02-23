
\n
static int devinfo_show(struct seq_file *f, void *v)
static void *devinfo_start(struct seq_file *f, loff_t *pos)
static void *devinfo_next(struct seq_file *f, void *v, loff_t *pos)
static void devinfo_stop(struct seq_file *f, void *v)
static int __init proc_devices_init(void)
\n
      4 struct seq_file *f
      3 void *v
      2 loff_t *pos
      1 void
