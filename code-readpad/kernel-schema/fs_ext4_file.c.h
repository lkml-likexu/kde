
\n
static ssize_t ext4_dax_read_iter(struct kiocb *iocb, struct iov_iter *to)
static ssize_t ext4_file_read_iter(struct kiocb *iocb, struct iov_iter *to)
static int ext4_release_file(struct inode *inode, struct file *filp)
static void ext4_unwritten_wait(struct inode *inode)
static int ext4_unaligned_aio(struct inode *inode, struct iov_iter *from, loff_t pos)
static bool ext4_overwrite_io(struct inode *inode, loff_t pos, loff_t len)
static ssize_t ext4_write_checks(struct kiocb *iocb, struct iov_iter *from)
static ssize_t ext4_dax_write_iter(struct kiocb *iocb, struct iov_iter *from)
static ssize_t ext4_file_write_iter(struct kiocb *iocb, struct iov_iter *from)
static vm_fault_t ext4_dax_huge_fault(struct vm_fault *vmf, enum page_entry_size pe_size)
static vm_fault_t ext4_dax_fault(struct vm_fault *vmf)
static int ext4_file_mmap(struct file *file, struct vm_area_struct *vma)
static int ext4_sample_last_mounted(struct super_block *sb, struct vfsmount *mnt)
static int ext4_file_open(struct inode * inode, struct file * filp)
loff_t ext4_llseek(struct file *file, loff_t offset, int whence)
\n
      5 struct kiocb *iocb
      4 struct iov_iter *from
      4 struct inode *inode
      2 struct vm_fault *vmf
      2 struct iov_iter *to
      2 struct file *file
      2 loff_t pos
      1 struct vm_area_struct *vma
      1 struct vfsmount *mnt
      1 struct super_block *sb
      1 struct inode * inode
      1 struct file * filp
      1 struct file *filp
      1 loff_t offset
      1 loff_t len
      1 int whence
      1 enum page_entry_size pe_size
