
\n
static int show_diag_stat(struct seq_file *m, void *v)
static void *show_diag_stat_start(struct seq_file *m, loff_t *pos)
static void *show_diag_stat_next(struct seq_file *m, void *v, loff_t *pos)
static void show_diag_stat_stop(struct seq_file *m, void *v)
static int show_diag_stat_open(struct inode *inode, struct file *file)
static int __init show_diag_stat_init(void)
void diag_stat_inc(enum diag_stat_enum nr)
void diag_stat_inc_norecursion(enum diag_stat_enum nr)
static inline int __diag14(unsigned long rx, unsigned long ry1, unsigned long subcode)
int diag14(unsigned long rx, unsigned long ry1, unsigned long subcode)
static inline int __diag204(unsigned long *subcode, unsigned long size, void *addr)
int diag204(unsigned long subcode, unsigned long size, void *addr)
int diag210(struct diag210 *addr)
int diag224(void *ptr)
static inline int __diag26c(void *req, void *resp, enum diag26c_sc subcode)
int diag26c(void *req, void *resp, enum diag26c_sc subcode)
\n
      4 struct seq_file *m
      3 void *v
      3 unsigned long subcode
      2 void *resp
      2 void *req
      2 void *addr
      2 unsigned long size
      2 unsigned long ry1
      2 unsigned long rx
      2 loff_t *pos
      2 enum diag_stat_enum nr
      2 enum diag26c_sc subcode
      1 void *ptr
      1 void
      1 unsigned long *subcode
      1 struct inode *inode
      1 struct file *file
      1 struct diag210 *addr
