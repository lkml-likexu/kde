
\n
int __execute_only_pkey(struct mm_struct *mm)
static inline bool vma_is_pkey_exec_only(struct vm_area_struct *vma)
int __arch_override_mprotect_pkey(struct vm_area_struct *vma, int prot, int pkey)
void copy_init_pkru_to_fpregs(void)
static ssize_t init_pkru_read_file(struct file *file, char __user *user_buf, size_t count, loff_t *ppos)
static ssize_t init_pkru_write_file(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
static int __init create_init_pkru_value(void)
static __init int setup_init_pkru(char *opt)
\n
      2 void
      2 struct vm_area_struct *vma
      2 struct file *file
      2 size_t count
      2 loff_t *ppos
      1 struct mm_struct *mm
      1 int prot
      1 int pkey
      1 const char __user *user_buf
      1 char __user *user_buf
      1 char *opt
