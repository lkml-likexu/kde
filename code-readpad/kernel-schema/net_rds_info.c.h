
EXPORT_SYMBOL_GPL(rds_info_register_func);
EXPORT_SYMBOL_GPL(rds_info_deregister_func);
EXPORT_SYMBOL_GPL(rds_info_copy);
\n
void rds_info_register_func(int optname, rds_info_func func)
void rds_info_deregister_func(int optname, rds_info_func func)
void rds_info_iter_unmap(struct rds_info_iterator *iter)
void rds_info_copy(struct rds_info_iterator *iter, void *data, unsigned long bytes)
int rds_info_getsockopt(struct socket *sock, int optname, char __user *optval, int __user *optlen)
\n
      3 int optname
      2 struct rds_info_iterator *iter
      2 rds_info_func func
      1 void *data
      1 unsigned long bytes
      1 struct socket *sock
      1 rds_info_register_func
      1 rds_info_deregister_func
      1 rds_info_copy
      1 int __user *optlen
      1 char __user *optval
