
\n
static inline void hugetlb_set_vma_policy(struct vm_area_struct *vma, struct inode *inode, pgoff_t index)
static inline void hugetlb_drop_vma_policy(struct vm_area_struct *vma)
static inline void hugetlb_drop_vma_policy(struct vm_area_struct *vma)
mpol_cond_put(vma->vm_policy)
; } static inline void hugetlb_set_vma_policy(struct vm_area_struct *vma, struct inode *inode, pgoff_t index)
static inline void hugetlb_drop_vma_policy(struct vm_area_struct *vma)
static void huge_pagevec_release(struct pagevec *pvec)
static int hugetlbfs_file_mmap(struct file *file, struct vm_area_struct *vma)
static unsigned long hugetlb_get_unmapped_area(struct file *file, unsigned long addr, unsigned long len, unsigned long pgoff, unsigned long flags)
static size_t hugetlbfs_read_actor(struct page *page, unsigned long offset, struct iov_iter *to, unsigned long size)
static ssize_t hugetlbfs_read_iter(struct kiocb *iocb, struct iov_iter *to)
static int hugetlbfs_write_begin(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned flags, struct page **pagep, void **fsdata)
static int hugetlbfs_write_end(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned copied, struct page *page, void *fsdata)
static void remove_huge_page(struct page *page)
static void hugetlb_vmdelete_list(struct rb_root_cached *root, pgoff_t start, pgoff_t end)
static void remove_inode_hugepages(struct inode *inode, loff_t lstart, loff_t lend)
static void hugetlbfs_evict_inode(struct inode *inode)
static int hugetlb_vmtruncate(struct inode *inode, loff_t offset)
static long hugetlbfs_punch_hole(struct inode *inode, loff_t offset, loff_t len)
static long hugetlbfs_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
static int hugetlbfs_setattr(struct dentry *dentry, struct iattr *attr)
static struct inode *hugetlbfs_get_root(struct super_block *sb, struct hugetlbfs_config *config)
static struct inode *hugetlbfs_get_inode(struct super_block *sb, struct inode *dir, umode_t mode, dev_t dev)
static int hugetlbfs_mknod(struct inode *dir, struct dentry *dentry, umode_t mode, dev_t dev)
static int hugetlbfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
static int hugetlbfs_create(struct inode *dir, struct dentry *dentry, umode_t mode, bool excl)
static int hugetlbfs_symlink(struct inode *dir, struct dentry *dentry, const char *symname)
static int hugetlbfs_set_page_dirty(struct page *page)
static int hugetlbfs_migrate_page(struct address_space *mapping, struct page *newpage, struct page *page, enum migrate_mode mode)
static int hugetlbfs_error_remove_page(struct address_space *mapping, struct page *page)
static int hugetlbfs_show_options(struct seq_file *m, struct dentry *root)
static int hugetlbfs_statfs(struct dentry *dentry, struct kstatfs *buf)
static void hugetlbfs_put_super(struct super_block *sb)
static inline int hugetlbfs_dec_free_inodes(struct hugetlbfs_sb_info *sbinfo)
static void hugetlbfs_inc_free_inodes(struct hugetlbfs_sb_info *sbinfo)
static struct inode *hugetlbfs_alloc_inode(struct super_block *sb)
static void hugetlbfs_i_callback(struct rcu_head *head)
static void hugetlbfs_destroy_inode(struct inode *inode)
static void init_once(void *foo)
static long hugetlbfs_size_to_hpages(struct hstate *h, unsigned long long size_opt, enum hugetlbfs_size_type val_type)
static int hugetlbfs_parse_options(char *options, struct hugetlbfs_config *pconfig)
static int hugetlbfs_fill_super(struct super_block *sb, void *data, int silent)
static struct dentry *hugetlbfs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
static int can_do_hugetlb_shm(void)
static int get_hstate_idx(int page_size_log)
struct file *hugetlb_file_setup(const char *name, size_t size, vm_flags_t acctflag, struct user_struct **user, int creat_flags, int page_size_log)
static int __init init_hugetlbfs_fs(void)
\n
      7 struct inode *inode
      6 struct vm_area_struct *vma
      6 struct page *page
      6 struct dentry *dentry
      5 struct super_block *sb
      5 struct inode *dir
      5 struct file *file
      4 umode_t mode
      4 struct address_space *mapping
      3 loff_t offset
      2 void *data
      2 void
      2 unsigned len
      2 struct iov_iter *to
      2 struct hugetlbfs_sb_info *sbinfo
      2 pgoff_t index
      2 loff_t pos
      2 loff_t len
      2 int page_size_log
      2 dev_t dev
      1 void **fsdata
      1 void *fsdata
      1 void *foo
      1 vm_flags_t acctflag
      1 vma->vm_policy
      1 unsigned long size
      1 unsigned long pgoff
      1 unsigned long offset
      1 unsigned long long size_opt
      1 unsigned long len
      1 unsigned long flags
      1 unsigned long addr
      1 unsigned flags
      1 unsigned copied
      1 struct user_struct **user
      1 struct seq_file *m
      1 struct rcu_head *head
      1 struct rb_root_cached *root
      1 struct pagevec *pvec
      1 struct page **pagep
      1 struct page *newpage
      1 struct kstatfs *buf
      1 struct kiocb *iocb
      1 struct iattr *attr
      1 struct hugetlbfs_config *pconfig
      1 struct hugetlbfs_config *config
      1 struct hstate *h
      1 struct file_system_type *fs_type
      1 struct dentry *root
      1 size_t size
      1 pgoff_t start
      1 pgoff_t end
      1 loff_t lstart
      1 loff_t lend
      1 int silent
      1 int mode
      1 int flags
      1 int creat_flags
      1 enum migrate_mode mode
      1 enum hugetlbfs_size_type val_type
      1 const char *symname
      1 const char *name
      1 const char *dev_name
      1 char *options
      1 bool excl
