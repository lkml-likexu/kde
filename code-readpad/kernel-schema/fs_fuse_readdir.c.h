
\n
static bool fuse_use_readdirplus(struct inode *dir, struct dir_context *ctx)
static void fuse_add_dirent_to_cache(struct file *file, struct fuse_dirent *dirent, loff_t pos)
static void fuse_readdir_cache_end(struct file *file, loff_t pos)
static bool fuse_emit(struct file *file, struct dir_context *ctx, struct fuse_dirent *dirent)
static int parse_dirfile(char *buf, size_t nbytes, struct file *file, struct dir_context *ctx)
static int fuse_direntplus_link(struct file *file, struct fuse_direntplus *direntplus, u64 attr_version)
static int parse_dirplusfile(char *buf, size_t nbytes, struct file *file, struct dir_context *ctx, u64 attr_version)
static int fuse_readdir_uncached(struct file *file, struct dir_context *ctx)
static enum fuse_parse_result fuse_parse_cache(struct fuse_file *ff, void *addr, unsigned int size, struct dir_context *ctx)
static void fuse_rdc_reset(struct inode *inode)
static int fuse_readdir_cached(struct file *file, struct dir_context *ctx)
int fuse_readdir(struct file *file, struct dir_context *ctx)
\n
      9 struct file *file
      8 struct dir_context *ctx
      2 u64 attr_version
      2 struct fuse_dirent *dirent
      2 size_t nbytes
      2 loff_t pos
      2 char *buf
      1 void *addr
      1 unsigned int size
      1 struct inode *inode
      1 struct inode *dir
      1 struct fuse_file *ff
      1 struct fuse_direntplus *direntplus
