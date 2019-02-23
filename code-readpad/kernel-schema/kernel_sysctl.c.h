
EXPORT_SYMBOL_GPL(proc_douintvec_minmax);
\n
static int sysrq_sysctl_handler(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int __init sysctl_init(void)
static int _proc_do_string(char *data, int maxlen, int write, char __user *buffer, size_t *lenp, loff_t *ppos)
static void warn_sysctl_write(struct ctl_table *table)
static bool proc_first_pos_non_zero_ignore(loff_t *ppos, struct ctl_table *table)
int proc_dostring(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static size_t proc_skip_spaces(char **buf)
static void proc_skip_char(char **buf, size_t *size, const char v)
define TMPBUFLEN 22static int proc_get_long(char **buf, size_t *size, unsigned long *val, bool *neg, const char *perm_tr, unsigned perm_tr_len, char *tr)
static int proc_put_long(void __user **buf, size_t *size, unsigned long val, bool neg)
static int proc_put_char(void __user **buf, size_t *size, char c)
static int do_proc_dointvec_conv(bool *negp, unsigned long *lvalp, int *valp, int write, void *data)
static int do_proc_douintvec_conv(unsigned long *lvalp, unsigned int *valp, int write, void *data)
static int __do_proc_dointvec(void *tbl_data, struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos, int (*conv)
(bool *negp, unsigned long *lvalp, int *valp, int write, void *data)
, void *data)
static int do_proc_dointvec(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos, int (*conv)
(bool *negp, unsigned long *lvalp, int *valp, int write, void *data)
, void *data)
static int do_proc_douintvec_w(unsigned int *tbl_data, struct ctl_table *table, void __user *buffer, size_t *lenp, loff_t *ppos, int (*conv)
(unsigned long *lvalp, unsigned int *valp, int write, void *data)
, void *data)
static int do_proc_douintvec_r(unsigned int *tbl_data, void __user *buffer, size_t *lenp, loff_t *ppos, int (*conv)
(unsigned long *lvalp, unsigned int *valp, int write, void *data)
, void *data)
static int __do_proc_douintvec(void *tbl_data, struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos, int (*conv)
(unsigned long *lvalp, unsigned int *valp, int write, void *data)
, void *data)
static int do_proc_douintvec(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos, int (*conv)
(unsigned long *lvalp, unsigned int *valp, int write, void *data)
, void *data)
int proc_dointvec(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_douintvec(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int proc_taint(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int proc_dointvec_minmax_sysadmin(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int do_proc_dointvec_minmax_conv(bool *negp, unsigned long *lvalp, int *valp, int write, void *data)
int proc_dointvec_minmax(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int do_proc_douintvec_minmax_conv(unsigned long *lvalp, unsigned int *valp, int write, void *data)
int proc_douintvec_minmax(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int do_proc_dopipe_max_size_conv(unsigned long *lvalp, unsigned int *valp, int write, void *data)
static int proc_dopipe_max_size(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static void validate_coredump_safety(void)
static int proc_dointvec_minmax_coredump(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int proc_dostring_coredump(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int __do_proc_doulongvec_minmax(void *data, struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos, unsigned long convmul, unsigned long convdiv)
static int do_proc_doulongvec_minmax(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos, unsigned long convmul, unsigned long convdiv)
int proc_doulongvec_minmax(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_doulongvec_ms_jiffies_minmax(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int do_proc_dointvec_jiffies_conv(bool *negp, unsigned long *lvalp, int *valp, int write, void *data)
static int do_proc_dointvec_userhz_jiffies_conv(bool *negp, unsigned long *lvalp, int *valp, int write, void *data)
static int do_proc_dointvec_ms_jiffies_conv(bool *negp, unsigned long *lvalp, int *valp, int write, void *data)
int proc_dointvec_jiffies(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_dointvec_userhz_jiffies(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_dointvec_ms_jiffies(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int proc_do_cad_pid(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_do_large_bitmap(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_dostring(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_dointvec(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_douintvec(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_dointvec_minmax(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_douintvec_minmax(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_dointvec_jiffies(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_dointvec_userhz_jiffies(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_dointvec_ms_jiffies(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_doulongvec_minmax(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
int proc_doulongvec_ms_jiffies_minmax(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
\n
     49 int write
     38 loff_t *ppos
     37 struct ctl_table *table
     37 size_t *lenp
     36 void __user *buffer
     15 void *data
     14 unsigned long *lvalp
      7 unsigned int *valp
      7 int *valp
      7 bool *negp
      6 int *conv
      4 size_t *size
      3 char **buf
      2 void __user **buf
      2 void *tbl_data
      2 void
      2 unsigned long convmul
      2 unsigned long convdiv
      2 unsigned int *tbl_data
      1 unsigned perm_tr_len
      1 unsigned long *val
      1 unsigned long val
      1 proc_douintvec_minmax
      1 int maxlen
      1 const char v
      1 const char *perm_tr
      1 char __user *buffer
      1 char *tr
      1 char *data
      1 char c
      1 bool *neg
      1 bool neg
