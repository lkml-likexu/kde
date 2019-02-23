
EXPORT_SYMBOL_GPL(console_drivers);
EXPORT_SYMBOL_GPL(vprintk_default);
EXPORT_SYMBOL_GPL(kmsg_dump_register);
EXPORT_SYMBOL_GPL(kmsg_dump_unregister);
EXPORT_SYMBOL_GPL(kmsg_dump_get_line);
EXPORT_SYMBOL_GPL(kmsg_dump_get_buffer);
EXPORT_SYMBOL_GPL(kmsg_dump_rewind);
\n
static int __control_devkmsg(char *str)
static int __init control_devkmsg(char *str)
int devkmsg_sysctl_set_loglvl(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int __down_trylock_console_sem(unsigned long ip)
static void __up_console_sem(unsigned long ip)
char *log_buf_addr_get(void)
u32 log_buf_len_get(void)
static char *log_text(const struct printk_log *msg)
static char *log_dict(const struct printk_log *msg)
static struct printk_log *log_from_idx(u32 idx)
static u32 log_next(u32 idx)
static int logbuf_has_space(u32 msg_size, bool empty)
static int log_make_free_space(u32 msg_size)
static u32 msg_used_size(u16 text_len, u16 dict_len, u32 *pad_len)
static u32 truncate_msg(u16 *text_len, u16 *trunc_msg_len, u16 *dict_len, u32 *pad_len)
static int log_store(int facility, int level, enum log_flags flags, u64 ts_nsec, const char *dict, u16 dict_len, const char *text, u16 text_len)
static int syslog_action_restricted(int type)
static int check_syslog_permissions(int type, int source)
static void append_char(char **pp, char *e, char c)
static ssize_t msg_print_ext_header(char *buf, size_t size, struct printk_log *msg, u64 seq)
static ssize_t msg_print_ext_body(char *buf, size_t size, char *dict, size_t dict_len, char *text, size_t text_len)
static __printf(3, 4)
__cold int devkmsg_emit(int facility, int level, const char *fmt, ...)
static ssize_t devkmsg_write(struct kiocb *iocb, struct iov_iter *from)
static ssize_t devkmsg_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static loff_t devkmsg_llseek(struct file *file, loff_t offset, int whence)
static __poll_t devkmsg_poll(struct file *file, poll_table *wait)
static int devkmsg_open(struct inode *inode, struct file *file)
static int devkmsg_release(struct inode *inode, struct file *file)
void log_buf_vmcoreinfo_setup(void)
static void __init log_buf_len_update(u64 size)
static int __init log_buf_len_setup(char *str)
static void __init log_buf_add_cpu(void)
void __init setup_log_buf(int early)
static int __init ignore_loglevel_setup(char *str)
static bool suppress_message_printing(int level)
static int __init boot_delay_setup(char *str)
static void boot_delay_msec(int level)
timeout = jiffies + msecs_to_jiffies(boot_delay)
; k--; cpu_relax()
;if (time_after(jiffies, timeout)
)
break; touch_nmi_watchdog()
;} } static inline void boot_delay_msec(int level)
static size_t print_syslog(unsigned int level, char *buf)
static size_t print_time(u64 ts, char *buf)
static size_t print_prefix(const struct printk_log *msg, bool syslog, bool time, char *buf)
static size_t msg_print_text(const struct printk_log *msg, bool syslog, bool time, char *buf, size_t size)
static int syslog_print(char __user *buf, int size)
static int syslog_print_all(char __user *buf, int size, bool clear)
static void syslog_clear(void)
int do_syslog(int type, char __user *buf, int len, int source)
SYSCALL_DEFINE3(syslog, int, type, char __user *, buf, int, len)
static void console_lock_spinning_enable(void)
static int console_lock_spinning_disable_and_check(void)
static int console_trylock_spinning(void)
static void call_console_drivers(const char *ext_text, size_t ext_len, const char *text, size_t len)
static inline void printk_delay(void)
static void cont_flush(void)
static bool cont_add(int facility, int level, enum log_flags flags, const char *text, size_t len)
static size_t log_output(int facility, int level, enum log_flags lflags, const char *dict, size_t dictlen, char *text, size_t text_len)
int vprintk_store(int facility, int level, const char *dict, size_t dictlen, const char *fmt, va_list args)
asmlinkage int vprintk_emit(int facility, int level, const char *dict, size_t dictlen, const char *fmt, va_list args)
asmlinkage int vprintk(const char *fmt, va_list args)
int vprintk_default(const char *fmt, va_list args)
asmlinkage __visible int printk(const char *fmt, ...)
asmlinkage __visible void early_printk(const char *fmt, ...)
static int __add_preferred_console(char *name, int idx, char *options, char *brl_options)
static int __init console_msg_format_setup(char *str)
static int __init console_setup(char *str)
int add_preferred_console(char *name, int idx, char *options)
static int __init console_suspend_disable(char *str)
void suspend_console(void)
void resume_console(void)
static int console_cpu_notify(unsigned int cpu)
void console_lock(void)
int console_trylock(void)
int is_console_locked(void)
static int have_callable_console(void)
static inline int can_use_console(void)
void console_unlock(void)
void __sched console_conditional_schedule(void)
void console_unblank(void)
void console_flush_on_panic(void)
struct tty_driver *console_device(int *index)
void console_stop(struct console *console)
void console_start(struct console *console)
static int __init keep_bootcon_setup(char *str)
void register_console(struct console *newcon)
int unregister_console(struct console *console)
void __init console_init(void)
static int __init printk_late_init(void)
static void wake_up_klogd_work_func(struct irq_work *irq_work)
void wake_up_klogd(void)
void defer_console_output(void)
int vprintk_deferred(const char *fmt, va_list args)
int printk_deferred(const char *fmt, ...)
int __printk_ratelimit(const char *func)
bool printk_timed_ratelimit(unsigned long *caller_jiffies, unsigned int interval_msecs)
int kmsg_dump_register(struct kmsg_dumper *dumper)
int kmsg_dump_unregister(struct kmsg_dumper *dumper)
void kmsg_dump(enum kmsg_dump_reason reason)
bool kmsg_dump_get_line_nolock(struct kmsg_dumper *dumper, bool syslog, char *line, size_t size, size_t *len)
bool kmsg_dump_get_line(struct kmsg_dumper *dumper, bool syslog, char *line, size_t size, size_t *len)
bool kmsg_dump_get_buffer(struct kmsg_dumper *dumper, bool syslog, char *buf, size_t size, size_t *len)
void kmsg_dump_rewind_nolock(struct kmsg_dumper *dumper)
void kmsg_dump_rewind(struct kmsg_dumper *dumper)
\n
     25 void
      9 int level
      9 const char *fmt
      9 char *str
      7 struct kmsg_dumper *dumper
      7 char *buf
      6 size_t size
      6 int facility
      5 va_list args
      5 struct file *file
      5 bool syslog
      4 const struct printk_log *msg
      4 const char *dict
      4 char __user *buf
      4 ...
      3 struct console *console
      3 size_t *len
      3 size_t dictlen
      3 int type
      3 const char *text
      2 unsigned long ip
      2 u32 *pad_len
      2 u32 msg_size
      2 u32 idx
      2 u16 text_len
      2 u16 dict_len
      2 struct inode *inode
      2 size_t text_len
      2 size_t len
      2 loff_t *ppos
      2 int source
      2 int size
      2 int idx
      2 int
      2 enum log_flags flags
      2 char *text
      2 char *options
      2 char *name
      2 char *line
      2 bool time
      2 
      1 vprintk_default
      1 void __user *buffer
      1 unsigned long *caller_jiffies
      1 unsigned int level
      1 unsigned int interval_msecs
      1 unsigned int cpu
      1 u64 ts_nsec
      1 u64 ts
      1 u64 size
      1 u64 seq
      1 u16 *trunc_msg_len
      1 u16 *text_len
      1 u16 *dict_len
      1 type
      1 timeout
      1 time_afterjiffies
      1 syslog
      1 struct printk_log *msg
      1 struct kiocb *iocb
      1 struct irq_work *irq_work
      1 struct iov_iter *from
      1 struct ctl_table *table
      1 struct console *newcon
      1 size_t *lenp
      1 size_t ext_len
      1 size_t dict_len
      1 size_t count
      1 poll_table *wait
      1 loff_t offset
      1 len
      1 kmsg_dump_unregister
      1 kmsg_dump_rewind
      1 kmsg_dump_register
      1 kmsg_dump_get_line
      1 kmsg_dump_get_buffer
      1 int write
      1 int whence
      1 int len
      1 int *index
      1 int early
      1 enum log_flags lflags
      1 enum kmsg_dump_reason reason
      1 const char *func
      1 const char *ext_text
      1 console_drivers
      1 char __user *
      1 char **pp
      1 char *e
      1 char *dict
      1 char c
      1 char *brl_options
      1 buf
      1 boot_delay
      1 bool empty
      1 bool clear
      1 4
      1 3
