
EXPORT_SYMBOL_GPL(dax_read_lock);
EXPORT_SYMBOL_GPL(dax_read_unlock);
EXPORT_SYMBOL_GPL(fs_dax_get_by_bdev);
EXPORT_SYMBOL_GPL(__bdev_dax_supported);
EXPORT_SYMBOL_GPL(dax_attribute_group);
EXPORT_SYMBOL_GPL(dax_direct_access);
EXPORT_SYMBOL_GPL(dax_copy_from_iter);
EXPORT_SYMBOL_GPL(dax_copy_to_iter);
EXPORT_SYMBOL_GPL(dax_flush);
EXPORT_SYMBOL_GPL(dax_write_cache);
EXPORT_SYMBOL_GPL(dax_write_cache_enabled);
EXPORT_SYMBOL_GPL(dax_alive);
EXPORT_SYMBOL_GPL(kill_dax);
EXPORT_SYMBOL_GPL(alloc_dax);
EXPORT_SYMBOL_GPL(put_dax);
EXPORT_SYMBOL_GPL(dax_get_by_host);
EXPORT_SYMBOL_GPL(inode_dax);
EXPORT_SYMBOL_GPL(dax_inode);
EXPORT_SYMBOL_GPL(dax_get_private);
\n
int dax_read_lock(void)
void dax_read_unlock(int id)
int bdev_dax_pgoff(struct block_device *bdev, sector_t sector, size_t size, pgoff_t *pgoff)
struct dax_device *fs_dax_get_by_bdev(struct block_device *bdev)
bool __bdev_dax_supported(struct block_device *bdev, int blocksize)
static ssize_t write_cache_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t write_cache_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
static umode_t dax_visible(struct kobject *kobj, struct attribute *a, int n)
long dax_direct_access(struct dax_device *dax_dev, pgoff_t pgoff, long nr_pages, void **kaddr, pfn_t *pfn)
size_t dax_copy_from_iter(struct dax_device *dax_dev, pgoff_t pgoff, void *addr, size_t bytes, struct iov_iter *i)
size_t dax_copy_to_iter(struct dax_device *dax_dev, pgoff_t pgoff, void *addr, size_t bytes, struct iov_iter *i)
void arch_wb_cache_pmem(void *addr, size_t size)
; void dax_flush(struct dax_device *dax_dev, void *addr, size_t size)
arch_wb_cache_pmem(addr, size)
; } void dax_flush(struct dax_device *dax_dev, void *addr, size_t size)
void dax_write_cache(struct dax_device *dax_dev, bool wc)
bool dax_write_cache_enabled(struct dax_device *dax_dev)
bool dax_alive(struct dax_device *dax_dev)
static int dax_host_hash(const char *host)
void kill_dax(struct dax_device *dax_dev)
static struct inode *dax_alloc_inode(struct super_block *sb)
static struct dax_device *to_dax_dev(struct inode *inode)
static void dax_i_callback(struct rcu_head *head)
static void dax_destroy_inode(struct inode *inode)
static struct dentry *dax_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
static int dax_test(struct inode *inode, void *data)
static int dax_set(struct inode *inode, void *data)
static struct dax_device *dax_dev_get(dev_t devt)
static void dax_add_host(struct dax_device *dax_dev, const char *host)
struct dax_device *alloc_dax(void *private, const char *__host, const struct dax_operations *ops)
void put_dax(struct dax_device *dax_dev)
struct dax_device *dax_get_by_host(const char *host)
struct dax_device *inode_dax(struct inode *inode)
struct inode *dax_inode(struct dax_device *dax_dev)
void *dax_get_private(struct dax_device *dax_dev)
static void init_once(void *_dax_dev)
static int __dax_fs_init(void)
static void __dax_fs_exit(void)
static int __init dax_fs_init(void)
static void __exit dax_fs_exit(void)
\n
     13 struct dax_device *dax_dev
      5 void *addr
      5 void
      5 struct inode *inode
      4 size_t size
      3 void *data
      3 struct block_device *bdev
      3 pgoff_t pgoff
      3 const char *host
      2 struct iov_iter *i
      2 struct device *dev
      2 struct device_attribute *attr
      2 size_t bytes
      1 void *private
      1 void **kaddr
      1 void *_dax_dev
      1 struct super_block *sb
      1 struct rcu_head *head
      1 struct kobject *kobj
      1 struct file_system_type *fs_type
      1 struct attribute *a
      1 size_t len
      1 size
      1 sector_t sector
      1 put_dax
      1 pgoff_t *pgoff
      1 pfn_t *pfn
      1 long nr_pages
      1 kill_dax
      1 int n
      1 int id
      1 int flags
      1 int blocksize
      1 inode_dax
      1 fs_dax_get_by_bdev
      1 dev_t devt
      1 dax_write_cache_enabled
      1 dax_write_cache
      1 dax_read_unlock
      1 dax_read_lock
      1 dax_inode
      1 dax_get_private
      1 dax_get_by_host
      1 dax_flush
      1 dax_direct_access
      1 dax_copy_to_iter
      1 dax_copy_from_iter
      1 dax_attribute_group
      1 dax_alive
      1 const struct dax_operations *ops
      1 const char *__host
      1 const char *dev_name
      1 const char *buf
      1 char *buf
      1 bool wc
      1 __bdev_dax_supported
      1 alloc_dax
      1 addr
