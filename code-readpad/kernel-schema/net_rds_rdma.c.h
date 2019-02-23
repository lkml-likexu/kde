
\n
static unsigned int rds_pages_in_vec(struct rds_iovec *vec)
static struct rds_mr *rds_mr_tree_walk(struct rb_root *root, u64 key, struct rds_mr *insert)
static void rds_destroy_mr(struct rds_mr *mr)
void __rds_put_mr_final(struct rds_mr *mr)
void rds_rdma_drop_keys(struct rds_sock *rs)
static int rds_pin_pages(unsigned long user_addr, unsigned int nr_pages, struct page **pages, int write)
static int __rds_rdma_map(struct rds_sock *rs, struct rds_get_mr_args *args, u64 *cookie_ret, struct rds_mr **mr_ret, struct rds_conn_path *cp)
int rds_get_mr(struct rds_sock *rs, char __user *optval, int optlen)
int rds_get_mr_for_dest(struct rds_sock *rs, char __user *optval, int optlen)
int rds_free_mr(struct rds_sock *rs, char __user *optval, int optlen)
void rds_rdma_unuse(struct rds_sock *rs, u32 r_key, int force)
void rds_rdma_free_op(struct rm_rdma_op *ro)
void rds_atomic_free_op(struct rm_atomic_op *ao)
static int rds_rdma_pages(struct rds_iovec iov[], int nr_iovecs)
int rds_rdma_extra_size(struct rds_rdma_args *args, struct rds_iov_vector *iov)
int rds_cmsg_rdma_args(struct rds_sock *rs, struct rds_message *rm, struct cmsghdr *cmsg, struct rds_iov_vector *vec)
int rds_cmsg_rdma_dest(struct rds_sock *rs, struct rds_message *rm, struct cmsghdr *cmsg)
int rds_cmsg_rdma_map(struct rds_sock *rs, struct rds_message *rm, struct cmsghdr *cmsg)
int rds_cmsg_atomic(struct rds_sock *rs, struct rds_message *rm, struct cmsghdr *cmsg)
\n
     10 struct rds_sock *rs
      4 struct rds_message *rm
      4 struct cmsghdr *cmsg
      3 int optlen
      3 char __user *optval
      2 struct rds_mr *mr
      1 unsigned long user_addr
      1 unsigned int nr_pages
      1 u64 key
      1 u64 *cookie_ret
      1 u32 r_key
      1 struct rm_rdma_op *ro
      1 struct rm_atomic_op *ao
      1 struct rds_rdma_args *args
      1 struct rds_mr **mr_ret
      1 struct rds_mr *insert
      1 struct rds_iov_vector *vec
      1 struct rds_iov_vector *iov
      1 struct rds_iovec *vec
      1 struct rds_iovec iov[]
      1 struct rds_get_mr_args *args
      1 struct rds_conn_path *cp
      1 struct rb_root *root
      1 struct page **pages
      1 int write
      1 int nr_iovecs
      1 int force
