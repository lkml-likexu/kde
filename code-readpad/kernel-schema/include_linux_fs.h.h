
\n
static inline bool is_sync_kiocb(struct kiocb *kiocb)
static inline bool mapping_tagged(struct address_space *mapping, xa_mark_t tag)
static inline void i_mmap_lock_write(struct address_space *mapping)
static inline void i_mmap_unlock_write(struct address_space *mapping)
static inline void i_mmap_lock_read(struct address_space *mapping)
static inline void i_mmap_unlock_read(struct address_space *mapping)
static inline int mapping_mapped(struct address_space *mapping)
static inline int mapping_writably_mapped(struct address_space *mapping)
static inline int mapping_map_writable(struct address_space *mapping)
static inline void mapping_unmap_writable(struct address_space *mapping)
static inline int mapping_deny_writable(struct address_space *mapping)
static inline void mapping_allow_writable(struct address_space *mapping)
static inline struct posix_acl * uncached_acl_sentinel(struct task_struct *task)
static inline bool is_uncached_acl(struct posix_acl *acl)
static inline unsigned int i_blocksize(const struct inode *node)
static inline int inode_unhashed(struct inode *inode)
static inline void inode_fake_hash(struct inode *inode)
enum inode_i_mutex_lock_class static inline void inode_lock(struct inode *inode)
static inline void inode_unlock(struct inode *inode)
static inline void inode_lock_shared(struct inode *inode)
static inline void inode_unlock_shared(struct inode *inode)
static inline int inode_trylock(struct inode *inode)
static inline int inode_trylock_shared(struct inode *inode)
static inline int inode_is_locked(struct inode *inode)
static inline void inode_lock_nested(struct inode *inode, unsigned subclass)
static inline void inode_lock_shared_nested(struct inode *inode, unsigned subclass)
static inline loff_t i_size_read(const struct inode *inode)
static inline void i_size_write(struct inode *inode, loff_t i_size)
static inline unsigned iminor(const struct inode *inode)
static inline unsigned imajor(const struct inode *inode)
static inline int ra_has_index(struct file_ra_state *ra, pgoff_t index)
static inline struct file *get_file(struct file *f)
void locks_free_lock_context(struct inode *inode)
; void locks_free_lock(struct file_lock *fl)
; extern void locks_init_lock(struct file_lock *)
; extern struct file_lock * locks_alloc_lock(void)
; extern void locks_copy_lock(struct file_lock *, struct file_lock *)
; extern void locks_copy_conflock(struct file_lock *, struct file_lock *)
; extern void locks_remove_posix(struct file *, fl_owner_t)
; extern void locks_remove_file(struct file *)
; extern void locks_release_private(struct file_lock *)
; extern void posix_test_lock(struct file *, struct file_lock *)
; extern int posix_lock_file(struct file *, struct file_lock *, struct file_lock *)
; extern int locks_delete_block(struct file_lock *)
; extern int vfs_test_lock(struct file *, struct file_lock *)
; extern int vfs_lock_file(struct file *, unsigned int, struct file_lock *, struct file_lock *)
; extern int vfs_cancel_lock(struct file *filp, struct file_lock *fl)
; extern int locks_lock_inode_wait(struct inode *inode, struct file_lock *fl)
; extern int __break_lease(struct inode *inode, unsigned int flags, unsigned int type)
; extern void lease_get_mtime(struct inode *, struct timespec64 *time)
; extern int generic_setlease(struct file *, long, struct file_lock **, void **priv)
; extern int vfs_setlease(struct file *, long, struct file_lock **, void **)
; extern int lease_modify(struct file_lock *, int, struct list_head *)
; struct files_struct; extern void show_fd_locks(struct seq_file *f, struct file *filp, struct files_struct *files)
; static inline int fcntl_getlk(struct file *file, unsigned int cmd, struct flock __user *user)
static inline int fcntl_setlk(unsigned int fd, struct file *file, unsigned int cmd, struct flock __user *user)
static inline int fcntl_getlk64(struct file *file, unsigned int cmd, struct flock64 __user *user)
static inline int fcntl_setlk64(unsigned int fd, struct file *file, unsigned int cmd, struct flock64 __user *user)
static inline int fcntl_setlk64(unsigned int fd, struct file *file, unsigned int cmd, struct flock64 __user *user)
return -EACCES; }endif static inline int fcntl_setlease(unsigned int fd, struct file *filp, long arg)
static inline int fcntl_getlease(struct file *filp)
static inline void locks_free_lock_context(struct inode *inode)
static inline void locks_init_lock(struct file_lock *fl)
static inline void locks_copy_conflock(struct file_lock *new, struct file_lock *fl)
static inline void locks_copy_lock(struct file_lock *new, struct file_lock *fl)
static inline void locks_remove_posix(struct file *filp, fl_owner_t owner)
static inline void locks_remove_file(struct file *filp)
static inline void posix_test_lock(struct file *filp, struct file_lock *fl)
static inline int posix_lock_file(struct file *filp, struct file_lock *fl, struct file_lock *conflock)
static inline int locks_delete_block(struct file_lock *waiter)
static inline int vfs_test_lock(struct file *filp, struct file_lock *fl)
static inline int vfs_lock_file(struct file *filp, unsigned int cmd, struct file_lock *fl, struct file_lock *conf)
static inline int vfs_cancel_lock(struct file *filp, struct file_lock *fl)
static inline int locks_lock_inode_wait(struct inode *inode, struct file_lock *fl)
static inline int __break_lease(struct inode *inode, unsigned int mode, unsigned int type)
static inline void lease_get_mtime(struct inode *inode, struct timespec64 *time)
static inline int generic_setlease(struct file *filp, long arg, struct file_lock **flp, void **priv)
static inline int vfs_setlease(struct file *filp, long arg, struct file_lock **lease, void **priv)
static inline int lease_modify(struct file_lock *fl, int arg, struct list_head *dispose)
static inline struct inode *file_inode(const struct file *f)
static inline struct dentry *file_dentry(const struct file *file)
static inline int locks_lock_file_wait(struct file *filp, struct file_lock *fl)
static inline uid_t i_uid_read(const struct inode *inode)
static inline gid_t i_gid_read(const struct inode *inode)
static inline void i_uid_write(struct inode *inode, uid_t uid)
static inline void i_gid_write(struct inode *inode, gid_t gid)
static inline void sb_end_write(struct super_block *sb)
static inline void sb_end_pagefault(struct super_block *sb)
static inline void sb_end_intwrite(struct super_block *sb)
static inline void sb_start_write(struct super_block *sb)
static inline int sb_start_write_trylock(struct super_block *sb)
static inline void sb_start_pagefault(struct super_block *sb)
static inline void sb_start_intwrite(struct super_block *sb)
static inline int sb_start_intwrite_trylock(struct super_block *sb)
static inline ssize_t call_read_iter(struct file *file, struct kiocb *kio, struct iov_iter *iter)
static inline ssize_t call_write_iter(struct file *file, struct kiocb *kio, struct iov_iter *iter)
static inline int call_mmap(struct file *file, struct vm_area_struct *vma)
static inline bool HAS_UNMAPPED_ID(struct inode *inode)
static inline enum rw_hint file_write_hint(struct file *file)
static inline u16 ki_hint_validate(enum rw_hint hint)
static inline void init_sync_kiocb(struct kiocb *kiocb, struct file *filp)
extern void __mark_inode_dirty(struct inode *, int)
; static inline void mark_inode_dirty(struct inode *inode)
static inline void mark_inode_dirty_sync(struct inode *inode)
static inline void inode_inc_link_count(struct inode *inode)
static inline void inode_dec_link_count(struct inode *inode)
extern bool atime_needs_update(const struct path *, struct inode *)
; extern void touch_atime(const struct path *)
; static inline void file_accessed(struct file *file)
extern struct dentry *mount_ns(struct file_system_type *fs_type, int flags, void *data, void *ns, struct user_namespace *user_ns, int (*fill_super)
(struct super_block *, void *, int)
)
; extern struct dentry *mount_bdev(struct file_system_type *fs_type, int flags, const char *dev_name, void *data, int (*fill_super)
(struct super_block *, void *, int)
)
; static inline struct dentry *mount_bdev(struct file_system_type *fs_type, int flags, const char *dev_name, void *data, int (*fill_super)
(struct super_block *, void *, int)
)
extern struct dentry *mount_ns(struct file_system_type *fs_type, int flags, void *data, void *ns, struct user_namespace *user_ns, int (*fill_super)
(struct super_block *, void *, int)
)
; extern struct dentry *mount_bdev(struct file_system_type *fs_type, int flags, const char *dev_name, void *data, int (*fill_super)
(struct super_block *, void *, int)
)
; static inline struct dentry *mount_bdev(struct file_system_type *fs_type, int flags, const char *dev_name, void *data, int (*fill_super)
(struct super_block *, void *, int)
)
return ERR_PTR(-ENODEV)
; }endif extern struct dentry *mount_single(struct file_system_type *fs_type, int flags, void *data, int (*fill_super)
(struct super_block *, void *, int)
)
; extern struct dentry *mount_nodev(struct file_system_type *fs_type, int flags, void *data, int (*fill_super)
(struct super_block *, void *, int)
)
; extern struct dentry *mount_subtree(struct vfsmount *mnt, const char *path)
; void generic_shutdown_super(struct super_block *sb)
; void kill_block_super(struct super_block *sb)
; static inline void kill_block_super(struct super_block *sb)
static inline struct dentry * mount_pseudo(struct file_system_type *fs_type, char *name, const struct super_operations *ops, const struct dentry_operations *dops, unsigned long magic)
static inline int __mandatory_lock(struct inode *ino)
static inline int mandatory_lock(struct inode *ino)
static inline int locks_verify_locked(struct file *file)
static inline int locks_verify_truncate(struct inode *inode, struct file *f, loff_t size)
static inline int locks_mandatory_locked(struct file *file)
static inline int locks_mandatory_area(struct inode *inode, struct file *filp, loff_t start, loff_t end, unsigned char type)
static inline int __mandatory_lock(struct inode *inode)
static inline int mandatory_lock(struct inode *inode)
static inline int locks_verify_locked(struct file *file)
static inline int locks_verify_truncate(struct inode *inode, struct file *filp, size_t size)
static inline int break_lease(struct inode *inode, unsigned int mode)
static inline int break_deleg(struct inode *inode, unsigned int mode)
static inline int try_break_deleg(struct inode *inode, struct inode **delegated_inode)
static inline int break_deleg_wait(struct inode **delegated_inode)
static inline int break_layout(struct inode *inode, bool wait)
static inline int break_lease(struct inode *inode, unsigned int mode)
static inline int break_deleg(struct inode *inode, unsigned int mode)
static inline int try_break_deleg(struct inode *inode, struct inode **delegated_inode)
static inline int break_deleg_wait(struct inode **delegated_inode)
static inline int break_layout(struct inode *inode, bool wait)
extern long vfs_truncate(const struct path *, loff_t)
; extern int do_truncate(struct dentry *, loff_t start, unsigned int time_attrs, struct file *filp)
; extern int vfs_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
; extern long do_sys_open(int dfd, const char __user *filename, int flags, umode_t mode)
; extern struct file *file_open_name(struct filename *, int, umode_t)
; extern struct file *filp_open(const char *, int, umode_t)
; extern struct file *file_open_root(struct dentry *, struct vfsmount *, const char *, int, umode_t)
; extern struct file * dentry_open(const struct path *, int, const struct cred *)
; extern struct file * open_with_fake_path(const struct path *, int, struct inode*, const struct cred *)
; static inline struct file *file_clone_open(struct file *file)
static inline bool sb_is_blkdev_sb(struct super_block *sb)
static inline struct super_block *freeze_bdev(struct block_device *sb)
static inline int thaw_bdev(struct block_device *bdev, struct super_block *sb)
static inline int emergency_thaw_bdev(struct super_block *sb)
static inline void iterate_bdevs(void (*f)
(struct block_device *, void *)
, void *arg)
static inline bool sb_is_blkdev_sb(struct super_block *sb)
extern int bd_link_disk_holder(struct block_device *bdev, struct gendisk *disk)
; extern void bd_unlink_disk_holder(struct block_device *bdev, struct gendisk *disk)
; static inline int bd_link_disk_holder(struct block_device *bdev, struct gendisk *disk)
extern int bd_link_disk_holder(struct block_device *bdev, struct gendisk *disk)
; extern void bd_unlink_disk_holder(struct block_device *bdev, struct gendisk *disk)
; static inline int bd_link_disk_holder(struct block_device *bdev, struct gendisk *disk)
return 0; } static inline void bd_unlink_disk_holder(struct block_device *bdev, struct gendisk *disk)
static inline int register_chrdev(unsigned int major, const char *name, const struct file_operations *fops)
static inline void unregister_chrdev(unsigned int major, const char *name)
static inline void invalidate_remote_inode(struct inode *inode)
static inline int filemap_fdatawait(struct address_space *mapping)
static inline int file_write_and_wait(struct file *file)
static inline void filemap_set_wb_err(struct address_space *mapping, int err)
static inline int filemap_check_wb_err(struct address_space *mapping, errseq_t since)
static inline errseq_t filemap_sample_wb_err(struct address_space *mapping)
static inline ssize_t generic_write_sync(struct kiocb *iocb, ssize_t count)
static inline bool execute_ok(struct inode *inode)
static inline void file_start_write(struct file *file)
static inline bool file_start_write_trylock(struct file *file)
static inline void file_end_write(struct file *file)
static inline int get_write_access(struct inode *inode)
static inline int get_write_access(struct inode *inode)
return atomic_inc_unless_negative(&inode->i_writecount)
? 0 : -ETXTBSY; } static inline int deny_write_access(struct file *file)
static inline int get_write_access(struct inode *inode)
return atomic_inc_unless_negative(&inode->i_writecount)
? 0 : -ETXTBSY; } static inline int deny_write_access(struct file *file)
struct inode *inode = file_inode(file)
;return atomic_dec_unless_positive(&inode->i_writecount)
? 0 : -ETXTBSY; } static inline void put_write_access(struct inode * inode)
static inline int get_write_access(struct inode *inode)
return atomic_inc_unless_negative(&inode->i_writecount)
? 0 : -ETXTBSY; } static inline int deny_write_access(struct file *file)
struct inode *inode = file_inode(file)
;return atomic_dec_unless_positive(&inode->i_writecount)
? 0 : -ETXTBSY; } static inline void put_write_access(struct inode * inode)
atomic_dec(&inode->i_writecount)
; } static inline void allow_write_access(struct file *file)
static inline int get_write_access(struct inode *inode)
return atomic_inc_unless_negative(&inode->i_writecount)
? 0 : -ETXTBSY; } static inline int deny_write_access(struct file *file)
struct inode *inode = file_inode(file)
;return atomic_dec_unless_positive(&inode->i_writecount)
? 0 : -ETXTBSY; } static inline void put_write_access(struct inode * inode)
atomic_dec(&inode->i_writecount)
; } static inline void allow_write_access(struct file *file)
if (file)
atomic_inc(&file_inode(file)
->i_writecount)
; } static inline bool inode_is_open_for_write(const struct inode *inode)
static inline void i_readcount_dec(struct inode *inode)
static inline void i_readcount_dec(struct inode *inode)
BUG_ON(!atomic_read(&inode->i_readcount)
)
;atomic_dec(&inode->i_readcount)
; } static inline void i_readcount_inc(struct inode *inode)
static inline void i_readcount_dec(struct inode *inode)
BUG_ON(!atomic_read(&inode->i_readcount)
)
;atomic_dec(&inode->i_readcount)
; } static inline void i_readcount_inc(struct inode *inode)
atomic_inc(&inode->i_readcount)
; } static inline void i_readcount_dec(struct inode *inode)
static inline void i_readcount_dec(struct inode *inode)
BUG_ON(!atomic_read(&inode->i_readcount)
)
;atomic_dec(&inode->i_readcount)
; } static inline void i_readcount_inc(struct inode *inode)
atomic_inc(&inode->i_readcount)
; } static inline void i_readcount_dec(struct inode *inode)
return; } static inline void i_readcount_inc(struct inode *inode)
static inline const char *kernel_read_file_id_str(enum kernel_read_file_id id)
extern int inode_init_always(struct super_block *, struct inode *)
; extern void inode_init_once(struct inode *)
; extern void address_space_init_once(struct address_space *mapping)
; extern struct inode * igrab(struct inode *)
; extern ino_t iunique(struct super_block *, ino_t)
; extern int inode_needs_sync(struct inode *inode)
; extern int generic_delete_inode(struct inode *inode)
; static inline int generic_drop_inode(struct inode *inode)
extern void __insert_inode_hash(struct inode *, unsigned long hashval)
; static inline void insert_inode_hash(struct inode *inode)
extern void __remove_inode_hash(struct inode *)
; static inline void remove_inode_hash(struct inode *inode)
static inline ssize_t blockdev_direct_IO(struct kiocb *iocb, struct inode *inode, struct iov_iter *iter, get_block_t get_block)
static inline void inode_dio_begin(struct inode *inode)
static inline void inode_dio_end(struct inode *inode)
extern int readlink_copy(char __user *, int, const char *)
; extern int page_readlink(struct dentry *, char __user *, int)
; extern const char *page_get_link(struct dentry *, struct inode *, struct delayed_call *)
; extern void page_put_link(void *)
; extern int __page_symlink(struct inode *inode, const char *symname, int len, int nofs)
; extern int page_symlink(struct inode *inode, const char *symname, int len)
; extern const struct inode_operations page_symlink_inode_operations; extern void kfree_link(void *)
; extern void generic_fillattr(struct inode *, struct kstat *)
; extern int vfs_getattr_nosec(const struct path *, struct kstat *, u32, unsigned int)
; extern int vfs_getattr(const struct path *, struct kstat *, u32, unsigned int)
; void __inode_add_bytes(struct inode *inode, loff_t bytes)
; void inode_add_bytes(struct inode *inode, loff_t bytes)
; void __inode_sub_bytes(struct inode *inode, loff_t bytes)
; void inode_sub_bytes(struct inode *inode, loff_t bytes)
; static inline loff_t __inode_get_bytes(struct inode *inode)
static inline int vfs_stat(const char __user *filename, struct kstat *stat)
static inline int vfs_stat(const char __user *filename, struct kstat *stat)
return vfs_statx(AT_FDCWD, filename, AT_NO_AUTOMOUNT, stat, STATX_BASIC_STATS)
; } static inline int vfs_lstat(const char __user *name, struct kstat *stat)
static inline int vfs_stat(const char __user *filename, struct kstat *stat)
return vfs_statx(AT_FDCWD, filename, AT_NO_AUTOMOUNT, stat, STATX_BASIC_STATS)
; } static inline int vfs_lstat(const char __user *name, struct kstat *stat)
return vfs_statx(AT_FDCWD, name, AT_SYMLINK_NOFOLLOW | AT_NO_AUTOMOUNT, stat, STATX_BASIC_STATS)
; } static inline int vfs_fstatat(int dfd, const char __user *filename, struct kstat *stat, int flags)
static inline int vfs_stat(const char __user *filename, struct kstat *stat)
return vfs_statx(AT_FDCWD, filename, AT_NO_AUTOMOUNT, stat, STATX_BASIC_STATS)
; } static inline int vfs_lstat(const char __user *name, struct kstat *stat)
return vfs_statx(AT_FDCWD, name, AT_SYMLINK_NOFOLLOW | AT_NO_AUTOMOUNT, stat, STATX_BASIC_STATS)
; } static inline int vfs_fstatat(int dfd, const char __user *filename, struct kstat *stat, int flags)
return vfs_statx(dfd, filename, flags | AT_NO_AUTOMOUNT, stat, STATX_BASIC_STATS)
; } static inline int vfs_fstat(int fd, struct kstat *stat)
static inline bool io_is_direct(struct file *filp)
static inline bool vma_is_dax(struct vm_area_struct *vma)
static inline bool vma_is_fsdax(struct vm_area_struct *vma)
static inline int iocb_flags(struct file *file)
static inline int kiocb_set_rw_flags(struct kiocb *ki, rwf_t flags)
static inline ino_t parent_ino(struct dentry *dentry)
define DEFINE_SIMPLE_ATTRIBUTE(__fops, __get, __set, __fmt)
\ static int __fops_open(struct inode *inode, struct file *file)
\ static inline __printf(1, 2)
void __simple_attr_check_format(const char *fmt, ...)
static inline bool is_sxid(umode_t mode)
static inline int check_sticky(struct inode *dir, struct inode *inode)
static inline void inode_has_no_xattr(struct inode *inode)
static inline bool is_root_inode(struct inode *inode)
static inline bool dir_emit(struct dir_context *ctx, const char *name, int namelen, u64 ino, unsigned type)
static inline bool dir_emit(struct dir_context *ctx, const char *name, int namelen, u64 ino, unsigned type)
return ctx->actor(ctx, name, namelen, ctx->pos, ino, type)
== 0; } static inline bool dir_emit_dot(struct file *file, struct dir_context *ctx)
static inline bool dir_emit(struct dir_context *ctx, const char *name, int namelen, u64 ino, unsigned type)
return ctx->actor(ctx, name, namelen, ctx->pos, ino, type)
== 0; } static inline bool dir_emit_dot(struct file *file, struct dir_context *ctx)
return ctx->actor(ctx, ".", 1, ctx->pos, file->f_path.dentry->d_inode->i_ino, DT_DIR)
== 0; } static inline bool dir_emit_dotdot(struct file *file, struct dir_context *ctx)
static inline bool dir_emit(struct dir_context *ctx, const char *name, int namelen, u64 ino, unsigned type)
return ctx->actor(ctx, name, namelen, ctx->pos, ino, type)
== 0; } static inline bool dir_emit_dot(struct file *file, struct dir_context *ctx)
return ctx->actor(ctx, ".", 1, ctx->pos, file->f_path.dentry->d_inode->i_ino, DT_DIR)
== 0; } static inline bool dir_emit_dotdot(struct file *file, struct dir_context *ctx)
return ctx->actor(ctx, "..", 2, ctx->pos, parent_ino(file->f_path.dentry)
, DT_DIR)
== 0; } static inline bool dir_emit_dots(struct file *file, struct dir_context *ctx)
static inline bool dir_emit(struct dir_context *ctx, const char *name, int namelen, u64 ino, unsigned type)
return ctx->actor(ctx, name, namelen, ctx->pos, ino, type)
== 0; } static inline bool dir_emit_dot(struct file *file, struct dir_context *ctx)
return ctx->actor(ctx, ".", 1, ctx->pos, file->f_path.dentry->d_inode->i_ino, DT_DIR)
== 0; } static inline bool dir_emit_dotdot(struct file *file, struct dir_context *ctx)
return ctx->actor(ctx, "..", 2, ctx->pos, parent_ino(file->f_path.dentry)
, DT_DIR)
== 0; } static inline bool dir_emit_dots(struct file *file, struct dir_context *ctx)
if (!dir_emit_dot(file, ctx)
)
return false; ctx->pos = 1;} if (!dir_emit_dotdot(file, ctx)
)
return false; ctx->pos = 2;}return true; } static inline bool dir_relax(struct inode *inode)
static inline bool dir_relax_shared(struct inode *inode)
\n
     77 struct inode *inode
     36 struct file *file
     19 struct file *filp
     17 int
     16 struct address_space *mapping
     15 struct super_block *sb
     14 struct file_lock *fl
     14 struct file_lock *
     14 struct dir_context *ctx
     11 void *
     11 int flags
     11 ctx
     10 struct super_block *
     10 struct kstat *stat
     10 struct inode *
      9 struct file_system_type *fs_type
      9 &inode->i_writecount
      9 ctx->pos
      8 void *data
      8 struct file *
      8 struct block_device *bdev
      8 int *fill_super
      7 struct gendisk *disk
      7 const struct path *
      7 const char __user *filename
      7 const char *name
      6 unsigned int cmd
      6 STATX_BASIC_STATS
      6 stat
      6 name
      6 const struct inode *inode
      5 unsigned type
      5 unsigned int mode
      5 u64 ino
      5 int namelen
      5 &inode->i_readcount
      5 AT_FDCWD
      4 unsigned int fd
      4 type
      4 struct inode **delegated_inode
      4 struct dentry *
      4 namelen
      4 loff_t bytes
      4 ino
      4 filename
      4 file
      4 const char *dev_name
      4 1
      3 void **priv
      3 unsigned int
      3 umode_t
      3 struct vm_area_struct *vma
      3 struct kstat *
      3 struct iov_iter *iter
      3 struct inode * inode
      3 struct flock64 __user *user
      3 long arg
      3 int dfd
      3 file->f_path.dentry->d_inode->i_ino
      3 DT_DIR
      3 const char __user *name
      3 const char *
      3 !atomic_read&inode->i_readcount
      3 AT_NO_AUTOMOUNT
      3 2
      3 "."
      2 void *ns
      2 unsigned subclass
      2 unsigned int type
      2 unsigned int major
      2 umode_t mode
      2 u32
      2 struct user_namespace *user_ns
      2 struct timespec64 *time
      2 struct kiocb *kiocb
      2 struct kiocb *kio
      2 struct kiocb *iocb
      2 struct inode *ino
      2 struct flock __user *user
      2 struct file_lock *new
      2 struct file_lock **
      2 struct file *f
      2 parent_inofile->f_path.dentry
      2 long
      2 loff_t start
      2 int len
      2 const struct cred *
      2 const char *symname
      2 char __user *
      2 bool wait
      2 AT_SYMLINK_NOFOLLOW | AT_NO_AUTOMOUNT
      2 ".."
      1 xa_mark_t tag
      1 void *f
      1 void **
      1 void
      1 unsigned long magic
      1 unsigned long hashval
      1 unsigned int time_attrs
      1 unsigned int flags
      1 unsigned char type
      1 uid_t uid
      1 struct vfsmount *mnt
      1 struct vfsmount *
      1 struct task_struct *task
      1 struct seq_file *f
      1 struct posix_acl *acl
      1 struct list_head *dispose
      1 struct list_head *
      1 struct kiocb *ki
      1 struct inode *dir
      1 struct inode*
      1 struct files_struct *files
      1 struct file_ra_state *ra
      1 struct filename *
      1 struct file_lock *waiter
      1 struct file_lock **lease
      1 struct file_lock **flp
      1 struct file_lock *conflock
      1 struct file_lock *conf
      1 struct dentry *dentry
      1 struct delayed_call *
      1 struct block_device *sb
      1 struct block_device *
      1 ssize_t count
      1 size_t size
      1 __set
      1 rwf_t flags
      1 pgoff_t index
      1 loff_t size
      1 loff_t offset
      1 loff_t len
      1 loff_t i_size
      1 loff_t end
      1 loff_t
      1 int nofs
      1 int mode
      1 int fd
      1 int err
      1 int arg
      1 ino_t
      1 gid_t gid
      1 get_block_t get_block
      1 __get
      1 __fops
      1 __fmt
      1 fl_owner_t owner
      1 fl_owner_t
      1 flags | AT_NO_AUTOMOUNT
      1 &file_inodefile
      1 errseq_t since
      1 enum rw_hint hint
      1 enum kernel_read_file_id id
      1 -ENODEV
      1 !dir_emit_dotfile
      1 !dir_emit_dotdotfile
      1 dfd
      1 const struct super_operations *ops
      1 const struct inode *node
      1 const struct file_operations *fops
      1 const struct file *file
      1 const struct file *f
      1 const struct dentry_operations *dops
      1 const char *path
      1 const char *fmt
      1 char *name
      1 ...
