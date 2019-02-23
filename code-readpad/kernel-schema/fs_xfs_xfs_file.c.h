
\n
int xfs_update_prealloc_flags(struct xfs_inode *ip, enum xfs_prealloc_flags flags)
STATIC int xfs_dir_fsync(struct file*file, loff_t start, loff_t end, int datasync)
STATIC int xfs_file_fsync(struct file*file, loff_t start, loff_t end, int datasync)
STATIC ssize_t xfs_file_dio_aio_read(struct kiocb*iocb, struct iov_iter*to)
static noinline ssize_t xfs_file_dax_read(struct kiocb*iocb, struct iov_iter*to)
STATIC ssize_t xfs_file_buffered_aio_read(struct kiocb*iocb, struct iov_iter*to)
STATIC ssize_t xfs_file_read_iter(struct kiocb*iocb, struct iov_iter*to)
STATIC ssize_t xfs_file_aio_write_checks(struct kiocb*iocb, struct iov_iter*from, int *iolock)
static int xfs_dio_write_end_io(struct kiocb*iocb, ssize_t size, unsignedflags)
STATIC ssize_t xfs_file_dio_aio_write(struct kiocb*iocb, struct iov_iter*from)
static noinline ssize_t xfs_file_dax_write(struct kiocb*iocb, struct iov_iter*from)
STATIC ssize_t xfs_file_buffered_aio_write(struct kiocb*iocb, struct iov_iter*from)
STATIC ssize_t xfs_file_write_iter(struct kiocb*iocb, struct iov_iter*from)
static void xfs_wait_dax_page(struct inode*inode)
static int xfs_break_dax_layouts(struct inode*inode, bool *retry)
int xfs_break_layouts(struct inode*inode, uint *iolock, enum layout_break_reason reason)
STATIC long xfs_file_fallocate(struct file*file, int mode, loff_t offset, loff_t len)
STATIC loff_t xfs_file_remap_range(struct file*file_in, loff_t pos_in, struct file*file_out, loff_t pos_out, loff_t len, unsigned intremap_flags)
STATIC int xfs_file_open(struct inode *inode, struct file *file)
STATIC int xfs_dir_open(struct inode *inode, struct file *file)
STATIC int xfs_file_release(struct inode *inode, struct file *filp)
STATIC int xfs_file_readdir(struct file *file, struct dir_context *ctx)
STATIC loff_t xfs_file_llseek(struct file *file, loff_toffset, intwhence)
static vm_fault_t __xfs_filemap_fault(struct vm_fault*vmf, enum page_entry_size pe_size, bool write_fault)
static vm_fault_t xfs_filemap_fault(struct vm_fault*vmf)
static vm_fault_t xfs_filemap_huge_fault(struct vm_fault*vmf, enum page_entry_size pe_size)
static vm_fault_t xfs_filemap_page_mkwrite(struct vm_fault*vmf)
static vm_fault_t xfs_filemap_pfn_mkwrite(struct vm_fault*vmf)
STATIC int xfs_file_mmap(struct file *filp, struct vm_area_struct *vma)
\n
     10 struct kiocb*iocb
      5 struct vm_fault*vmf
      5 struct iov_iter*from
      4 struct iov_iter*to
      4 struct file *file
      3 struct inode*inode
      3 struct inode *inode
      3 struct file*file
      2 struct file *filp
      2 loff_t start
      2 loff_t len
      2 loff_t end
      2 int datasync
      2 enum page_entry_size pe_size
      1 unsigned intremap_flags
      1 unsignedflags
      1 uint *iolock
      1 struct xfs_inode *ip
      1 struct vm_area_struct *vma
      1 struct file*file_out
      1 struct file*file_in
      1 struct dir_context *ctx
      1 ssize_t size
      1 loff_t pos_out
      1 loff_t pos_in
      1 loff_t offset
      1 loff_toffset
      1 intwhence
      1 int mode
      1 int *iolock
      1 enum xfs_prealloc_flags flags
      1 enum layout_break_reason reason
      1 bool write_fault
      1 bool *retry
