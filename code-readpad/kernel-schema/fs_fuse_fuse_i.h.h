
\n
define FUSE_IO_PRIV_SYNC(i)
\ static inline struct fuse_conn *get_fuse_conn_super(struct super_block *sb)
static inline struct fuse_conn *get_fuse_conn(struct inode *inode)
static inline struct fuse_inode *get_fuse_inode(struct inode *inode)
static inline u64 get_node_id(struct inode *inode)
static inline int invalid_nodeid(u64 nodeid)
\n
      3 struct inode *inode
      1 u64 nodeid
      1 struct super_block *sb
      1 i
