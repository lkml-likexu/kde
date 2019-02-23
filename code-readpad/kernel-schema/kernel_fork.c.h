
EXPORT_SYMBOL_GPL(lockdep_tasklist_lock_is_held);
EXPORT_SYMBOL_GPL(__mmdrop);
EXPORT_SYMBOL_GPL(__put_task_struct);
EXPORT_SYMBOL_GPL(mmput);
EXPORT_SYMBOL_GPL(get_task_mm);
\n
int lockdep_tasklist_lock_is_held(void)
int nr_processes(void)
void __weak arch_release_task_struct(struct task_struct *tsk)
static inline struct task_struct *alloc_task_struct_node(int node)
static inline void free_task_struct(struct task_struct *tsk)
static int free_vm_stack_cache(unsigned int cpu)
static unsigned long *alloc_thread_stack_node(struct task_struct *tsk, int node)
static inline void free_thread_stack(struct task_struct *tsk)
static unsigned long *alloc_thread_stack_node(struct task_struct *tsk, int node)
static void free_thread_stack(struct task_struct *tsk)
void thread_stack_cache_init(void)
struct vm_area_struct *vm_area_alloc(struct mm_struct *mm)
struct vm_area_struct *vm_area_dup(struct vm_area_struct *orig)
void vm_area_free(struct vm_area_struct *vma)
static void account_kernel_stack(struct task_struct *tsk, int account)
static int memcg_charge_kernel_stack(struct task_struct *tsk)
static void release_task_stack(struct task_struct *tsk)
void put_task_stack(struct task_struct *tsk)
void free_task(struct task_struct *tsk)
static __latent_entropy int dup_mmap(struct mm_struct *mm, struct mm_struct *oldmm)
static inline int mm_alloc_pgd(struct mm_struct *mm)
static inline void mm_free_pgd(struct mm_struct *mm)
static inline void mm_free_pgd(struct mm_struct *mm)
pgd_free(mm, mm->pgd)
; } static int dup_mmap(struct mm_struct *mm, struct mm_struct *oldmm)
static void check_mm(struct mm_struct *mm)
void __mmdrop(struct mm_struct *mm)
static void mmdrop_async_fn(struct work_struct *work)
static void mmdrop_async(struct mm_struct *mm)
static inline void free_signal_struct(struct signal_struct *sig)
static inline void put_signal_struct(struct signal_struct *sig)
void __put_task_struct(struct task_struct *tsk)
static void set_max_threads(unsigned int max_threads_suggested)
static void task_struct_whitelist(unsigned long *offset, unsigned long *size)
void __init fork_init(void)
int __weak arch_dup_task_struct(struct task_struct *dst, struct task_struct *src)
void set_task_stack_end_magic(struct task_struct *tsk)
static struct task_struct *dup_task_struct(struct task_struct *orig, int node)
static int __init coredump_filter_setup(char *s)
static void mm_init_aio(struct mm_struct *mm)
static void mm_init_owner(struct mm_struct *mm, struct task_struct *p)
static void mm_init_uprobes_state(struct mm_struct *mm)
static struct mm_struct *mm_init(struct mm_struct *mm, struct task_struct *p, struct user_namespace *user_ns)
struct mm_struct *mm_alloc(void)
static inline void __mmput(struct mm_struct *mm)
void mmput(struct mm_struct *mm)
static void mmput_async_fn(struct work_struct *work)
void mmput_async(struct mm_struct *mm)
void set_mm_exe_file(struct mm_struct *mm, struct file *new_exe_file)
struct file *get_mm_exe_file(struct mm_struct *mm)
struct file *get_task_exe_file(struct task_struct *task)
struct mm_struct *get_task_mm(struct task_struct *task)
struct mm_struct *mm_access(struct task_struct *task, unsigned int mode)
static void complete_vfork_done(struct task_struct *tsk)
static int wait_for_vfork_done(struct task_struct *child, struct completion *vfork)
void mm_release(struct task_struct *tsk, struct mm_struct *mm)
static struct mm_struct *dup_mm(struct task_struct *tsk)
static int copy_mm(unsigned long clone_flags, struct task_struct *tsk)
static int copy_fs(unsigned long clone_flags, struct task_struct *tsk)
static int copy_files(unsigned long clone_flags, struct task_struct *tsk)
static int copy_io(unsigned long clone_flags, struct task_struct *tsk)
static int copy_sighand(unsigned long clone_flags, struct task_struct *tsk)
void __cleanup_sighand(struct sighand_struct *sighand)
static void posix_cpu_timers_init_group(struct signal_struct *sig)
static int copy_signal(unsigned long clone_flags, struct task_struct *tsk)
static void copy_seccomp(struct task_struct *p)
SYSCALL_DEFINE1(set_tid_address, int __user *, tidptr)
static void rt_mutex_init_task(struct task_struct *p)
static void posix_cpu_timers_init(struct task_struct *tsk)
static inline void init_task_pid_links(struct task_struct *task)
static inline void init_task_pid(struct task_struct *task, enum pid_type type, struct pid *pid)
static inline void rcu_copy_process(struct task_struct *p)
static __latent_entropy struct task_struct *copy_process(unsigned long clone_flags, unsigned long stack_start, unsigned long stack_size, int __user *child_tidptr, struct pid *pid, int trace, unsigned long tls, int node)
static inline void init_idle_pids(struct task_struct *idle)
struct task_struct *fork_idle(int cpu)
long _do_fork(unsigned long clone_flags, unsigned long stack_start, unsigned long stack_size, int __user *parent_tidptr, int __user *child_tidptr, unsigned long tls)
long do_fork(unsigned long clone_flags, unsigned long stack_start, unsigned long stack_size, int __user *parent_tidptr, int __user *child_tidptr)
pid_t kernel_thread(int (*fn)
(void *)
, void *arg, unsigned long flags)
SYSCALL_DEFINE0(fork)
SYSCALL_DEFINE0(vfork)
SYSCALL_DEFINE5(clone, unsigned long, clone_flags, unsigned long, newsp, int __user *, parent_tidptr, unsigned long, tls, int __user *, child_tidptr)
elif defined(CONFIG_CLONE_BACKWARDS2)
SYSCALL_DEFINE5(clone, unsigned long, newsp, unsigned long, clone_flags, int __user *, parent_tidptr, int __user *, child_tidptr, unsigned long, tls)
elif defined(CONFIG_CLONE_BACKWARDS3)
SYSCALL_DEFINE6(clone, unsigned long, clone_flags, unsigned long, newsp, int, stack_size, int __user *, parent_tidptr, int __user *, child_tidptr, unsigned long, tls)
SYSCALL_DEFINE5(clone, unsigned long, clone_flags, unsigned long, newsp, int __user *, parent_tidptr, int __user *, child_tidptr, unsigned long, tls)
endif void walk_process_tree(struct task_struct *top, proc_visitor visitor, void *data)
static void sighand_ctor(void *data)
void __init proc_caches_init(void)
static int check_unshare_flags(unsigned long unshare_flags)
static int unshare_fs(unsigned long unshare_flags, struct fs_struct **new_fsp)
static int unshare_fd(unsigned long unshare_flags, struct files_struct **new_fdp)
int ksys_unshare(unsigned long unshare_flags)
SYSCALL_DEFINE1(unshare, unsigned long, unshare_flags)
int unshare_files(struct files_struct **displaced)
int sysctl_max_threads(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
\n
     23 struct task_struct *tsk
     19 struct mm_struct *mm
     13 unsigned long
      9 unsigned long clone_flags
      9 int __user *
      6 void
      5 struct task_struct *task
      5 struct task_struct *p
      5 int node
      4 unsigned long unshare_flags
      4 tls
      4 parent_tidptr
      4 newsp
      4 clone_flags
      4 clone
      4 child_tidptr
      3 unsigned long stack_start
      3 unsigned long stack_size
      3 struct signal_struct *sig
      3 int __user *child_tidptr
      2 void *data
      2 unsigned long tls
      2 struct work_struct *work
      2 struct pid *pid
      2 struct mm_struct *oldmm
      2 int __user *parent_tidptr
      1 void __user *buffer
      1 void *
      1 vfork
      1 unsigned long *size
      1 unsigned long *offset
      1 unsigned int mode
      1 unsigned int max_threads_suggested
      1 unsigned int cpu
      1 unshare_flags
      1 unshare
      1 tidptr
      1 struct vm_area_struct *vma
      1 struct vm_area_struct *orig
      1 struct user_namespace *user_ns
      1 struct task_struct *top
      1 struct task_struct *src
      1 struct task_struct *orig
      1 struct task_struct *idle
      1 struct task_struct *dst
      1 struct task_struct *child
      1 struct sighand_struct *sighand
      1 struct fs_struct **new_fsp
      1 struct files_struct **new_fdp
      1 struct files_struct **displaced
      1 struct file *new_exe_file
      1 struct ctl_table *table
      1 struct completion *vfork
      1 stack_size
      1 size_t *lenp
      1 set_tid_address
      1 __put_task_struct
      1 proc_visitor visitor
      1 mmput
      1 mm->pgd
      1 __mmdrop
      1 mm
      1 loff_t *ppos
      1 lockdep_tasklist_lock_is_held
      1 int write
      1 int trace
      1 int *fn
      1 int cpu
      1 int account
      1 int
      1 get_task_mm
      1 fork
      1 enum pid_type type
      1 CONFIG_CLONE_BACKWARDS3
      1 CONFIG_CLONE_BACKWARDS2
      1 char *s
