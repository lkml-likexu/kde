
\n
void proc_task_name(struct seq_file *m, struct task_struct *p, bool escape)
static inline const char *get_task_state(struct task_struct *tsk)
static inline void task_state(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *p)
void render_sigset_t(struct seq_file *m, const char *header, sigset_t *set)
static void collect_sigign_sigcatch(struct task_struct *p, sigset_t *ign, sigset_t *catch)
static inline void task_sig(struct seq_file *m, struct task_struct *p)
static void render_cap_t(struct seq_file *m, const char *header, kernel_cap_t *a)
static inline void task_cap(struct seq_file *m, struct task_struct *p)
static inline void task_seccomp(struct seq_file *m, struct task_struct *p)
static inline void task_context_switch_counts(struct seq_file *m, struct task_struct *p)
static void task_cpus_allowed(struct seq_file *m, struct task_struct *task)
static inline void task_core_dumping(struct seq_file *m, struct mm_struct *mm)
static inline void task_thp_status(struct seq_file *m, struct mm_struct *mm)
int proc_pid_status(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static int do_task_stat(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task, int whole)
int proc_tid_stat(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
int proc_tgid_stat(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
int proc_pid_statm(struct seq_file *m, struct pid_namespace *ns, struct pid *pid, struct task_struct *task)
static struct pid * get_children_pid(struct inode *inode, struct pid *pid_prev, loff_t pos)
static int children_seq_show(struct seq_file *seq, void *v)
static void *children_seq_start(struct seq_file *seq, loff_t *pos)
static void *children_seq_next(struct seq_file *seq, void *v, loff_t *pos)
static void children_seq_stop(struct seq_file *seq, void *v)
static int children_seq_open(struct inode *inode, struct file *file)
\n
     16 struct seq_file *m
      7 struct task_struct *p
      6 struct task_struct *task
      6 struct pid *pid
      6 struct pid_namespace *ns
      4 struct seq_file *seq
      3 void *v
      2 struct mm_struct *mm
      2 struct inode *inode
      2 loff_t *pos
      2 const char *header
      1 struct task_struct *tsk
      1 struct pid *pid_prev
      1 struct file *file
      1 sigset_t *set
      1 sigset_t *ign
      1 sigset_t *catch
      1 loff_t pos
      1 kernel_cap_t *a
      1 int whole
      1 bool escape
