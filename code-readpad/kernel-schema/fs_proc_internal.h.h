
\n
static inline struct proc_inode *PROC_I(const struct inode *inode)
static inline struct proc_dir_entry *PDE(const struct inode *inode)
static inline void *__PDE_DATA(const struct inode *inode)
static inline struct pid *proc_pid(const struct inode *inode)
static inline struct task_struct *get_proc_task(const struct inode *inode)
static inline struct proc_dir_entry *pde_get(struct proc_dir_entry *pde)
static inline bool is_empty_pde(const struct proc_dir_entry *pde)
\n
      5 const struct inode *inode
      1 struct proc_dir_entry *pde
      1 const struct proc_dir_entry *pde
