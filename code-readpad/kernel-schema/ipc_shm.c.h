
\n
struct shmid_kernelvoid shm_init_ns(struct ipc_namespace *ns)
static void do_shm_rmid(struct ipc_namespace *ns, struct kern_ipc_perm *ipcp)
void shm_exit_ns(struct ipc_namespace *ns)
static int __init ipc_ns_init(void)
void __init shm_init(void)
static inline struct shmid_kernel *shm_obtain_object(struct ipc_namespace *ns, int id)
static inline struct shmid_kernel *shm_obtain_object_check(struct ipc_namespace *ns, int id)
static inline struct shmid_kernel *shm_lock(struct ipc_namespace *ns, int id)
static inline void shm_lock_by_ptr(struct shmid_kernel *ipcp)
static void shm_rcu_free(struct rcu_head *head)
static inline void shm_rmid(struct ipc_namespace *ns, struct shmid_kernel *s)
static int __shm_open(struct vm_area_struct *vma)
static void shm_open(struct vm_area_struct *vma)
static void shm_destroy(struct ipc_namespace *ns, struct shmid_kernel *shp)
static bool shm_may_destroy(struct ipc_namespace *ns, struct shmid_kernel *shp)
static void shm_close(struct vm_area_struct *vma)
static int shm_try_destroy_orphaned(int id, void *p, void *data)
void shm_destroy_orphaned(struct ipc_namespace *ns)
void exit_shm(struct task_struct *task)
static vm_fault_t shm_fault(struct vm_fault *vmf)
static int shm_split(struct vm_area_struct *vma, unsigned long addr)
static unsigned long shm_pagesize(struct vm_area_struct *vma)
static int shm_set_policy(struct vm_area_struct *vma, struct mempolicy *new)
static struct mempolicy *shm_get_policy(struct vm_area_struct *vma, unsigned long addr)
static int shm_mmap(struct file *file, struct vm_area_struct *vma)
static int shm_release(struct inode *ino, struct file *file)
static int shm_fsync(struct file *file, loff_t start, loff_t end, int datasync)
static long shm_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
static unsigned long shm_get_unmapped_area(struct file *file, unsigned long addr, unsigned long len, unsigned long pgoff, unsigned long flags)
bool is_file_shm_hugepages(struct file *file)
static int newseg(struct ipc_namespace *ns, struct ipc_params *params)
static inline int shm_more_checks(struct kern_ipc_perm *ipcp, struct ipc_params *params)
long ksys_shmget(key_t key, size_t size, int shmflg)
SYSCALL_DEFINE3(shmget, key_t, key, size_t, size, int, shmflg)
static inline unsigned long copy_shmid_to_user(void __user *buf, struct shmid64_ds *in, int version)
static inline unsigned long copy_shmid_from_user(struct shmid64_ds *out, void __user *buf, int version)
static inline unsigned long copy_shminfo_to_user(void __user *buf, struct shminfo64 *in, int version)
static void shm_add_rss_swap(struct shmid_kernel *shp, unsigned long *rss_add, unsigned long *swp_add)
static void shm_get_stat(struct ipc_namespace *ns, unsigned long *rss, unsigned long *swp)
static int shmctl_down(struct ipc_namespace *ns, int shmid, int cmd, struct shmid64_ds *shmid64)
static int shmctl_ipc_info(struct ipc_namespace *ns, struct shminfo64 *shminfo)
static int shmctl_shm_info(struct ipc_namespace *ns, struct shm_info *shm_info)
static int shmctl_stat(struct ipc_namespace *ns, int shmid, int cmd, struct shmid64_ds *tbuf)
static int shmctl_do_lock(struct ipc_namespace *ns, int shmid, int cmd)
long ksys_shmctl(int shmid, int cmd, struct shmid_ds __user *buf)
SYSCALL_DEFINE3(shmctl, int, shmid, int, cmd, struct shmid_ds __user *, buf)
static int copy_compat_shminfo_to_user(void __user *buf, struct shminfo64 *in, int version)
static int put_compat_shm_info(struct shm_info *ip, struct compat_shm_info __user *uip)
static int copy_compat_shmid_to_user(void __user *buf, struct shmid64_ds *in, int version)
static int copy_compat_shmid_from_user(struct shmid64_ds *out, void __user *buf, int version)
long compat_ksys_shmctl(int shmid, int cmd, void __user *uptr)
COMPAT_SYSCALL_DEFINE3(shmctl, int, shmid, int, cmd, void __user *, uptr)
long do_shmat(int shmid, char __user *shmaddr, int shmflg, ulong *raddr, unsigned long shmlba)
SYSCALL_DEFINE3(shmat, int, shmid, char __user *, shmaddr, int, shmflg)
COMPAT_SYSCALL_DEFINE3(shmat, int, shmid, compat_uptr_t, shmaddr, int, shmflg)
long ksys_shmdt(char __user *shmaddr)
SYSCALL_DEFINE1(shmdt, char __user *, shmaddr)
static int sysvipc_shm_proc_show(struct seq_file *s, void *it)
\n
     17 struct ipc_namespace *ns
      9 int
      8 struct vm_area_struct *vma
      6 void __user *buf
      6 struct file *file
      6 int version
      6 int shmid
      5 int cmd
      4 shmid
      4 int id
      3 unsigned long addr
      3 struct shmid_kernel *shp
      3 shmflg
      3 shmaddr
      2 void
      2 struct shminfo64 *in
      2 struct shmid64_ds *out
      2 struct shmid64_ds *in
      2 struct kern_ipc_perm *ipcp
      2 struct ipc_params *params
      2 shmctl
      2 shmat
      2 int shmflg
      2 cmd
      2 char __user *shmaddr
      2 char __user *
      1 void __user *uptr
      1 void __user *
      1 void *p
      1 void *it
      1 void *data
      1 uptr
      1 unsigned long *swp_add
      1 unsigned long *swp
      1 unsigned long shmlba
      1 unsigned long *rss_add
      1 unsigned long *rss
      1 unsigned long pgoff
      1 unsigned long len
      1 unsigned long flags
      1 ulong *raddr
      1 struct vm_fault *vmf
      1 struct task_struct *task
      1 struct shm_info *shm_info
      1 struct shm_info *ip
      1 struct shminfo64 *shminfo
      1 struct shmid_kernel *s
      1 struct shmid_kernel *ipcp
      1 struct shmid_ds __user *buf
      1 struct shmid_ds __user *
      1 struct shmid64_ds *tbuf
      1 struct shmid64_ds *shmid64
      1 struct seq_file *s
      1 struct rcu_head *head
      1 struct mempolicy *new
      1 struct inode *ino
      1 struct compat_shm_info __user *uip
      1 size_t size
      1 size_t
      1 size
      1 shmget
      1 shmdt
      1 loff_t start
      1 loff_t offset
      1 loff_t len
      1 loff_t end
      1 key_t key
      1 key_t
      1 key
      1 int mode
      1 int datasync
      1 compat_uptr_t
      1 buf
