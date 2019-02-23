
\n
static int xenbus_backend_open(struct inode *inode, struct file *filp)
static long xenbus_alloc(domid_t domid)
static long xenbus_backend_ioctl(struct file *file, unsigned int cmd, unsigned long data)
static int xenbus_backend_mmap(struct file *file, struct vm_area_struct *vma)
static int __init xenbus_backend_init(void)
\n
      2 struct file *file
      1 void
      1 unsigned long data
      1 unsigned int cmd
      1 struct vm_area_struct *vma
      1 struct inode *inode
      1 struct file *filp
      1 domid_t domid
