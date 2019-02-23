
EXPORT_SYMBOL_GPL(xenbus_directory);
EXPORT_SYMBOL_GPL(xenbus_exists);
EXPORT_SYMBOL_GPL(xenbus_read);
EXPORT_SYMBOL_GPL(xenbus_write);
EXPORT_SYMBOL_GPL(xenbus_mkdir);
EXPORT_SYMBOL_GPL(xenbus_rm);
EXPORT_SYMBOL_GPL(xenbus_transaction_start);
EXPORT_SYMBOL_GPL(xenbus_transaction_end);
EXPORT_SYMBOL_GPL(xenbus_scanf);
EXPORT_SYMBOL_GPL(xenbus_read_unsigned);
EXPORT_SYMBOL_GPL(xenbus_printf);
EXPORT_SYMBOL_GPL(xenbus_gather);
EXPORT_SYMBOL_GPL(register_xenbus_watch);
EXPORT_SYMBOL_GPL(unregister_xenbus_watch);
\n
static void xs_suspend_enter(void)
static void xs_suspend_exit(void)
static uint32_t xs_request_enter(struct xb_req_data *req)
void xs_request_exit(struct xb_req_data *req)
static int get_error(const char *errorstring)
static bool xenbus_ok(void)
static bool test_reply(struct xb_req_data *req)
static void *read_reply(struct xb_req_data *req)
static void xs_send(struct xb_req_data *req, struct xsd_sockmsg *msg)
static void *xs_wait_for_reply(struct xb_req_data *req, struct xsd_sockmsg *msg)
static void xs_wake_up(struct xb_req_data *req)
int xenbus_dev_request_and_reply(struct xsd_sockmsg *msg, void *par)
static void *xs_talkv(struct xenbus_transaction t, enum xsd_sockmsg_type type, const struct kvec *iovec, unsigned int num_vecs, unsigned int *len)
static void *xs_single(struct xenbus_transaction t, enum xsd_sockmsg_type type, const char *string, unsigned int *len)
static int xs_error(char *reply)
static unsigned int count_strings(const char *strings, unsigned int len)
static char *join(const char *dir, const char *name)
static char **split(char *strings, unsigned int len, unsigned int *num)
char **xenbus_directory(struct xenbus_transaction t, const char *dir, const char *node, unsigned int *num)
int xenbus_exists(struct xenbus_transaction t, const char *dir, const char *node)
void *xenbus_read(struct xenbus_transaction t, const char *dir, const char *node, unsigned int *len)
int xenbus_write(struct xenbus_transaction t, const char *dir, const char *node, const char *string)
int xenbus_mkdir(struct xenbus_transaction t, const char *dir, const char *node)
int xenbus_rm(struct xenbus_transaction t, const char *dir, const char *node)
int xenbus_transaction_start(struct xenbus_transaction *t)
int xenbus_transaction_end(struct xenbus_transaction t, int abort)
int xenbus_scanf(struct xenbus_transaction t, const char *dir, const char *node, const char *fmt, ...)
unsigned int xenbus_read_unsigned(const char *dir, const char *node, unsigned int default_val)
int xenbus_printf(struct xenbus_transaction t, const char *dir, const char *node, const char *fmt, ...)
int xenbus_gather(struct xenbus_transaction t, const char *dir, ...)
static int xs_watch(const char *path, const char *token)
static int xs_unwatch(const char *path, const char *token)
static struct xenbus_watch *find_watch(const char *token)
int xs_watch_msg(struct xs_watch_event *event)
static bool xen_strict_xenbus_quirk(void)
} static void xs_reset_watches(void)
int register_xenbus_watch(struct xenbus_watch *watch)
void unregister_xenbus_watch(struct xenbus_watch *watch)
void xs_suspend(void)
void xs_resume(void)
void xs_suspend_cancel(void)
static int xenwatch_thread(void *unused)
static int xs_reboot_notify(struct notifier_block *nb, unsigned long code, void *unused)
int xs_init(void)
\n
     12 struct xenbus_transaction t
     11 const char *dir
      9 void
      9 const char *node
      7 struct xb_req_data *req
      3 unsigned int *len
      3 struct xsd_sockmsg *msg
      3 const char *token
      3 ...
      2 void *unused
      2 unsigned int *num
      2 unsigned int len
      2 struct xenbus_watch *watch
      2 enum xsd_sockmsg_type type
      2 const char *string
      2 const char *path
      2 const char *fmt
      1 xenbus_write
      1 xenbus_transaction_start
      1 xenbus_transaction_end
      1 xenbus_scanf
      1 xenbus_rm
      1 xenbus_read_unsigned
      1 xenbus_read
      1 xenbus_printf
      1 xenbus_mkdir
      1 xenbus_gather
      1 xenbus_exists
      1 xenbus_directory
      1 void *par
      1 unsigned long code
      1 unsigned int num_vecs
      1 unsigned int default_val
      1 unregister_xenbus_watch
      1 struct xs_watch_event *event
      1 struct xenbus_transaction *t
      1 struct notifier_block *nb
      1 register_xenbus_watch
      1 int abort
      1 const struct kvec *iovec
      1 const char *strings
      1 const char *name
      1 const char *errorstring
      1 char *strings
      1 char *reply
