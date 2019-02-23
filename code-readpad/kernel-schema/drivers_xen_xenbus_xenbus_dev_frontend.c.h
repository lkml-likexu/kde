
EXPORT_SYMBOL_GPL(xen_xenbus_fops);
\n
static ssize_t xenbus_file_read(struct file *filp, char __user *ubuf, size_t len, loff_t *ppos)
static int queue_reply(struct list_head *queue, const void *data, size_t len)
static void queue_cleanup(struct list_head *list)
static void free_watch_adapter(struct watch_adapter *watch)
static struct watch_adapter *alloc_watch_adapter(const char *path, const char *token)
static void watch_fired(struct xenbus_watch *watch, const char *path, const char *token)
static void xenbus_file_free(struct kref *kref)
static struct xenbus_transaction_holder *xenbus_get_transaction(struct xenbus_file_priv *u, uint32_t tx_id)
void xenbus_dev_queue_reply(struct xb_req_data *req)
static int xenbus_command_reply(struct xenbus_file_priv *u, unsigned int msg_type, const char *reply)
static int xenbus_write_transaction(unsigned msg_type, struct xenbus_file_priv *u)
static int xenbus_write_watch(unsigned msg_type, struct xenbus_file_priv *u)
static ssize_t xenbus_file_write(struct file *filp, const char __user *ubuf, size_t len, loff_t *ppos)
static int xenbus_file_open(struct inode *inode, struct file *filp)
static int xenbus_file_release(struct inode *inode, struct file *filp)
static __poll_t xenbus_file_poll(struct file *file, poll_table *wait)
static int __init xenbus_init(void)
\n
      4 struct xenbus_file_priv *u
      4 struct file *filp
      3 size_t len
      2 unsigned msg_type
      2 struct inode *inode
      2 loff_t *ppos
      2 const char *token
      2 const char *path
      1 xen_xenbus_fops
      1 void
      1 unsigned int msg_type
      1 uint32_t tx_id
      1 struct xenbus_watch *watch
      1 struct xb_req_data *req
      1 struct watch_adapter *watch
      1 struct list_head *queue
      1 struct list_head *list
      1 struct kref *kref
      1 struct file *file
      1 poll_table *wait
      1 const void *data
      1 const char __user *ubuf
      1 const char *reply
      1 char __user *ubuf
