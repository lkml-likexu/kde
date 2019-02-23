
\n
static inline bool seq_has_overflowed(struct seq_file *m)
static inline size_t seq_get_buf(struct seq_file *m, char **bufp)
static inline void seq_commit(struct seq_file *m, int num)
static inline void seq_setwidth(struct seq_file *m, size_t size)
define DEFINE_SHOW_ATTRIBUTE(__name)
\ static int __name_open(struct inode *inode, struct file *file)
\ static inline struct user_namespace *seq_user_ns(struct seq_file *seq)
static inline void seq_show_option(struct seq_file *m, const char *name, const char *value)
\n
      5 struct seq_file *m
      1 struct seq_file *seq
      1 struct inode *inode
      1 struct file *file
      1 size_t size
      1 __name
      1 int num
      1 const char *value
      1 const char *name
      1 char **bufp
