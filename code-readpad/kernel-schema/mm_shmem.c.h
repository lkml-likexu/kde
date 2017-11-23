
EXPORT_SYMBOL_GPL(shmem_truncate_range);
EXPORT_SYMBOL_GPL(shmem_truncate_range);
EXPORT_SYMBOL_GPL(shmem_file_setup);
EXPORT_SYMBOL_GPL(shmem_file_setup_with_mnt);
EXPORT_SYMBOL_GPL(shmem_read_mapping_page_gfp);
static unsigned long shmem_default_max_blocks(void)
static unsigned long shmem_default_max_inodes(void)
int shmem_getpage(struct inode *inode, pgoff_t index, struct page **pagep, enum sgp_type sgp)
static inline struct shmem_sb_info *SHMEM_SB(struct super_block *sb)
static inline int shmem_acct_size(unsigned long flags, loff_t size)
static inline void shmem_unacct_size(unsigned long flags, loff_t size)
static inline int shmem_reacct_size(unsigned long flags, loff_t oldsize, loff_t newsize)
static inline int shmem_acct_block(unsigned long flags, long pages)
static inline void shmem_unacct_blocks(unsigned long flags, long pages)
static inline bool shmem_inode_acct_block(struct inode *inode, long pages)
static inline void shmem_inode_unacct_blocks(struct inode *inode, long pages)
bool vma_is_shmem(struct vm_area_struct *vma)
static int shmem_reserve_inode(struct super_block *sb)
static void shmem_free_inode(struct super_block *sb)
static void shmem_recalc_inode(struct inode *inode)
bool shmem_charge(struct inode *inode, long pages)
void shmem_uncharge(struct inode *inode, long pages)
static int shmem_replace_entry(struct address_space *mapping, pgoff_t index, void *expected, void *replacement)
static bool shmem_confirm_swap(struct address_space *mapping, pgoff_t index, swp_entry_t swap)
static int shmem_parse_huge(const char *str)
static const char *shmem_format_huge(int huge)
static unsigned long shmem_unused_huge_shrink(struct shmem_sb_info *sbinfo, struct shrink_control *sc, unsigned long nr_to_split)
static long shmem_unused_huge_scan(struct super_block *sb, struct shrink_control *sc)
static long shmem_unused_huge_count(struct super_block *sb, struct shrink_control *sc)
static unsigned long shmem_unused_huge_shrink(struct shmem_sb_info *sbinfo, struct shrink_control *sc, unsigned long nr_to_split)
static inline bool is_huge_enabled(struct shmem_sb_info *sbinfo)
static int shmem_add_to_page_cache(struct page *page, struct address_space *mapping, pgoff_t index, void *expected, gfp_t gfp)
static void shmem_delete_from_page_cache(struct page *page, void *radswap)
static int shmem_free_swap(struct address_space *mapping, pgoff_t index, void *radswap)
unsigned long shmem_partial_swap_usage(struct address_space *mapping, pgoff_t start, pgoff_t end)
unsigned long shmem_swap_usage(struct vm_area_struct *vma)
void shmem_unlock_mapping(struct address_space *mapping)
static void shmem_undo_range(struct inode *inode, loff_t lstart, loff_t lend, bool unfalloc)
void shmem_truncate_range(struct inode *inode, loff_t lstart, loff_t lend)
static int shmem_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
static int shmem_setattr(struct dentry *dentry, struct iattr *attr)
static void shmem_evict_inode(struct inode *inode)
static unsigned long find_swap_entry(struct xarray *xa, void *item)
static int shmem_unuse_inode(struct shmem_inode_info *info, swp_entry_t swap, struct page **pagep)
int shmem_unuse(swp_entry_t swap, struct page *page)
static int shmem_writepage(struct page *page, struct writeback_control *wbc)
static void shmem_show_mpol(struct seq_file *seq, struct mempolicy *mpol)
static struct mempolicy *shmem_get_sbmpol(struct shmem_sb_info *sbinfo)
static struct mempolicy *shmem_get_sbmpol(struct shmem_sb_info *sbinfo)
struct mempolicy *mpol = NULL; spin_lock(&sbinfo->stat_lock)
;mpol = sbinfo->mpol; mpol_get(mpol)
; spin_unlock(&sbinfo->stat_lock)
;}return mpol; } static inline void shmem_show_mpol(struct seq_file *seq, struct mempolicy *mpol)
static struct mempolicy *shmem_get_sbmpol(struct shmem_sb_info *sbinfo)
struct mempolicy *mpol = NULL; spin_lock(&sbinfo->stat_lock)
;mpol = sbinfo->mpol; mpol_get(mpol)
; spin_unlock(&sbinfo->stat_lock)
;}return mpol; } static inline void shmem_show_mpol(struct seq_file *seq, struct mempolicy *mpol)
} static inline struct mempolicy *shmem_get_sbmpol(struct shmem_sb_info *sbinfo)
static void shmem_pseudo_vma_init(struct vm_area_struct *vma, struct shmem_inode_info *info, pgoff_t index)
static void shmem_pseudo_vma_destroy(struct vm_area_struct *vma)
static struct page *shmem_swapin(swp_entry_t swap, gfp_t gfp, struct shmem_inode_info *info, pgoff_t index)
static struct page *shmem_alloc_hugepage(gfp_t gfp, struct shmem_inode_info *info, pgoff_t index)
static struct page *shmem_alloc_page(gfp_t gfp, struct shmem_inode_info *info, pgoff_t index)
static struct page *shmem_alloc_and_acct_page(gfp_t gfp, struct inode *inode, pgoff_t index, bool huge)
static bool shmem_should_replace_page(struct page *page, gfp_t gfp)
static int shmem_replace_page(struct page **pagep, gfp_t gfp, struct shmem_inode_info *info, pgoff_t index)
static int shmem_getpage_gfp(struct inode *inode, pgoff_t index, struct page **pagep, enum sgp_type sgp, gfp_t gfp, struct vm_area_struct *vma, struct vm_fault *vmf, vm_fault_t *fault_type)
static int synchronous_wake_function(wait_queue_entry_t *wait, unsigned mode, int sync, void *key)
static vm_fault_t shmem_fault(struct vm_fault *vmf)
unsigned long shmem_get_unmapped_area(struct file *file, unsigned long uaddr, unsigned long len, unsigned long pgoff, unsigned long flags)
static int shmem_set_policy(struct vm_area_struct *vma, struct mempolicy *mpol)
static struct mempolicy *shmem_get_policy(struct vm_area_struct *vma, unsigned long addr)
int shmem_lock(struct file *file, int lock, struct user_struct *user)
static int shmem_mmap(struct file *file, struct vm_area_struct *vma)
static struct inode *shmem_get_inode(struct super_block *sb, const struct inode *dir, umode_t mode, dev_t dev, unsigned long flags)
bool shmem_mapping(struct address_space *mapping)
static int shmem_mfill_atomic_pte(struct mm_struct *dst_mm, pmd_t *dst_pmd, struct vm_area_struct *dst_vma, unsigned long dst_addr, unsigned long src_addr, bool zeropage, struct page **pagep)
int shmem_mcopy_atomic_pte(struct mm_struct *dst_mm, pmd_t *dst_pmd, struct vm_area_struct *dst_vma, unsigned long dst_addr, unsigned long src_addr, struct page **pagep)
int shmem_mfill_zeropage_pte(struct mm_struct *dst_mm, pmd_t *dst_pmd, struct vm_area_struct *dst_vma, unsigned long dst_addr)
static int shmem_write_begin(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned flags, struct page **pagep, void **fsdata)
static int shmem_write_end(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned copied, struct page *page, void *fsdata)
static ssize_t shmem_file_read_iter(struct kiocb *iocb, struct iov_iter *to)
static pgoff_t shmem_seek_hole_data(struct address_space *mapping, pgoff_t index, pgoff_t end, int whence)
static loff_t shmem_file_llseek(struct file *file, loff_t offset, int whence)
static long shmem_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
static int shmem_statfs(struct dentry *dentry, struct kstatfs *buf)
static int shmem_mknod(struct inode *dir, struct dentry *dentry, umode_t mode, dev_t dev)
static int shmem_tmpfile(struct inode *dir, struct dentry *dentry, umode_t mode)
static int shmem_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
static int shmem_create(struct inode *dir, struct dentry *dentry, umode_t mode, bool excl)
static int shmem_link(struct dentry *old_dentry, struct inode *dir, struct dentry *dentry)
static int shmem_unlink(struct inode *dir, struct dentry *dentry)
static int shmem_rmdir(struct inode *dir, struct dentry *dentry)
static int shmem_exchange(struct inode *old_dir, struct dentry *old_dentry, struct inode *new_dir, struct dentry *new_dentry)
static int shmem_whiteout(struct inode *old_dir, struct dentry *old_dentry)
static int shmem_rename2(struct inode *old_dir, struct dentry *old_dentry, struct inode *new_dir, struct dentry *new_dentry, unsigned int flags)
static int shmem_symlink(struct inode *dir, struct dentry *dentry, const char *symname)
static void shmem_put_link(void *arg)
static const char *shmem_get_link(struct dentry *dentry, struct inode *inode, struct delayed_call *done)
static int shmem_initxattrs(struct inode *inode, const struct xattr *xattr_array, void *fs_info)
static int shmem_xattr_handler_get(const struct xattr_handler *handler, struct dentry *unused, struct inode *inode, const char *name, void *buffer, size_t size)
static int shmem_xattr_handler_set(const struct xattr_handler *handler, struct dentry *unused, struct inode *inode, const char *name, const void *value, size_t size, int flags)
static ssize_t shmem_listxattr(struct dentry *dentry, char *buffer, size_t size)
static struct dentry *shmem_get_parent(struct dentry *child)
static int shmem_match(struct inode *ino, void *vfh)
static struct dentry *shmem_find_alias(struct inode *inode)
static struct dentry *shmem_fh_to_dentry(struct super_block *sb, struct fid *fid, int fh_len, int fh_type)
static int shmem_encode_fh(struct inode *inode, __u32 *fh, int *len, struct inode *parent)
static int shmem_parse_options(char *options, struct shmem_sb_info *sbinfo, bool remount)
static int shmem_remount_fs(struct super_block *sb, int *flags, char *data)
static int shmem_show_options(struct seq_file *seq, struct dentry *root)
static void shmem_put_super(struct super_block *sb)
int shmem_fill_super(struct super_block *sb, void *data, int silent)
static struct inode *shmem_alloc_inode(struct super_block *sb)
static void shmem_destroy_callback(struct rcu_head *head)
static void shmem_destroy_inode(struct inode *inode)
static void shmem_init_inode(void *foo)
static void shmem_init_inodecache(void)
static void shmem_destroy_inodecache(void)
static struct dentry *shmem_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
int __init shmem_init(void)
static ssize_t shmem_enabled_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
static ssize_t shmem_enabled_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
bool shmem_huge_enabled(struct vm_area_struct *vma)
int __init shmem_init(void)
int shmem_unuse(swp_entry_t swap, struct page *page)
int shmem_lock(struct file *file, int lock, struct user_struct *user)
void shmem_unlock_mapping(struct address_space *mapping)
unsigned long shmem_get_unmapped_area(struct file *file, unsigned long addr, unsigned long len, unsigned long pgoff, unsigned long flags)
void shmem_truncate_range(struct inode *inode, loff_t lstart, loff_t lend)
static struct file *__shmem_file_setup(struct vfsmount *mnt, const char *name, loff_t size, unsigned long flags, unsigned int i_flags)
struct file *shmem_kernel_file_setup(const char *name, loff_t size, unsigned long flags)
struct file *shmem_file_setup(const char *name, loff_t size, unsigned long flags)
struct file *shmem_file_setup_with_mnt(struct vfsmount *mnt, const char *name, loff_t size, unsigned long flags)
int shmem_zero_setup(struct vm_area_struct *vma)
struct page *shmem_read_mapping_page_gfp(struct address_space *mapping, pgoff_t index, gfp_t gfp)
  19 struct inode *inode
  14 pgoff_t index
  12 unsigned long flags
  12 struct dentry *dentry
  12 struct address_space *mapping
  11 struct super_block *sb
  10 struct vm_area_struct *vma
   9 struct file *file
   9 gfp_t gfp
   8 struct shmem_sb_info *sbinfo
   8 struct inode *dir
   7 struct page *page
   7 struct page **pagep
   6 void
   6 struct shmem_inode_info *info
   6 long pages
   6 loff_t size
   6 const char *name
   5 umode_t mode
   5 swp_entry_t swap
   4 struct shrink_control *sc
   4 struct seq_file *seq
   4 struct mempolicy *mpol
   4 struct dentry *old_dentry
   4 &sbinfo->stat_lock
   3 unsigned long dst_addr
   3 struct vm_area_struct *dst_vma
   3 struct mm_struct *dst_mm
   3 struct inode *old_dir
   3 size_t size
   3 pmd_t *dst_pmd
   3 loff_t lstart
   3 loff_t lend
   2 void *radswap
   2 void *expected
   2 void *data
   2 unsigned long src_addr
   2 unsigned long pgoff
   2 unsigned long nr_to_split
   2 unsigned long len
   2 unsigned long addr
   2 unsigned len
   2 struct vm_fault *vmf
   2 struct vfsmount *mnt
   2 struct user_struct *user
   2 struct kobject *kobj
   2 struct kobj_attribute *attr
   2 struct inode *new_dir
   2 struct dentry *unused
   2 struct dentry *new_dentry
   2 shmem_truncate_range
   2 pgoff_t end
   2 mpol
   2 loff_t pos
   2 loff_t offset
   2 int whence
   2 int lock
   2 int flags
   2 enum sgp_type sgp
   2 dev_t dev
   2 const struct xattr_handler *handler
   1 wait_queue_entry_t *wait
   1 void *vfh
   1 void *replacement
   1 void *key
   1 void *item
   1 void *fsdata
   1 void *fs_info
   1 void *foo
   1 void *buffer
   1 void *arg
   1 void **fsdata
   1 vm_fault_t *fault_type
   1 unsigned mode
   1 unsigned long uaddr
   1 unsigned int query_flags
   1 unsigned int i_flags
   1 unsigned int flags
   1 unsigned flags
   1 unsigned copied
   1 u32 request_mask
   1 struct xarray *xa
   1 struct writeback_control *wbc
   1 struct rcu_head *head
   1 struct kstatfs *buf
   1 struct kstat *stat
   1 struct kiocb *iocb
   1 struct iov_iter *to
   1 struct inode *parent
   1 struct inode *ino
   1 struct iattr *attr
   1 struct file_system_type *fs_type
   1 struct fid *fid
   1 struct dentry *root
   1 struct dentry *child
   1 struct delayed_call *done
   1 size_t count
   1 shmem_read_mapping_page_gfp
   1 shmem_file_setup_with_mnt
   1 shmem_file_setup
   1 pgoff_t start
   1 loff_t oldsize
   1 loff_t newsize
   1 loff_t len
   1 int sync
   1 int silent
   1 int mode
   1 int huge
   1 int fh_type
   1 int fh_len
   1 int *len
   1 int *flags
   1 const void *value
   1 const struct xattr *xattr_array
   1 const struct path *path
   1 const struct inode *dir
   1 const char *symname
   1 const char *str
   1 const char *dev_name
   1 const char *buf
   1 char *options
   1 char *data
   1 char *buffer
   1 char *buf
   1 bool zeropage
   1 bool unfalloc
   1 bool remount
   1 bool huge
   1 bool excl
   1 __u32 *fh
