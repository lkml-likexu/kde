
EXPORT_SYMBOL_GPL(add_input_randomness);
EXPORT_SYMBOL_GPL(add_interrupt_randomness);
EXPORT_SYMBOL_GPL(add_disk_randomness);
EXPORT_SYMBOL_GPL(add_hwgenerator_randomness);
\n
static void _mix_pool_bytes(struct entropy_store *r, const void *in, int nbytes)
static void __mix_pool_bytes(struct entropy_store *r, const void *in, int nbytes)
static void mix_pool_bytes(struct entropy_store *r, const void *in, int nbytes)
static void fast_mix(struct fast_pool *f)
static void process_random_ready_list(void)
static void credit_entropy_bits(struct entropy_store *r, int nbits)
static int credit_entropy_bits_safe(struct entropy_store *r, int nbits)
static bool trust_cpu __ro_after_init = IS_ENABLED(CONFIG_RANDOM_TRUST_CPU)
; static int __init parse_trust_cpu(char *arg)
static void crng_initialize(struct crng_state *crng)
static void do_numa_crng_init(struct work_struct *work)
static void numa_crng_init(void)
static int crng_fast_load(const char *cp, size_t len)
static int crng_slow_load(const char *cp, size_t len)
static void crng_reseed(struct crng_state *crng, struct entropy_store *r)
static void _extract_crng(struct crng_state *crng, __u8 out[CHACHA_BLOCK_SIZE])
static void extract_crng(__u8 out[CHACHA_BLOCK_SIZE])
static void _crng_backtrack_protect(struct crng_state *crng, __u8 tmp[CHACHA_BLOCK_SIZE], int used)
static void crng_backtrack_protect(__u8 tmp[CHACHA_BLOCK_SIZE], int used)
static ssize_t extract_crng_user(void __user *buf, size_t nbytes)
void add_device_randomness(const void *buf, unsigned int size)
static void add_timer_randomness(struct timer_rand_state *state, unsigned num)
void add_input_randomness(unsigned int type, unsigned int code, unsigned int value)
static void add_interrupt_bench(cycles_t start)
static __u32 get_reg(struct fast_pool *f, struct pt_regs *regs)
void add_interrupt_randomness(int irq, int irq_flags)
void add_disk_randomness(struct gendisk *disk)
static void _xfer_secondary_pool(struct entropy_store *r, size_t nbytes)
; static void xfer_secondary_pool(struct entropy_store *r, size_t nbytes)
static void _xfer_secondary_pool(struct entropy_store *r, size_t nbytes)
static void push_to_pool(struct work_struct *work)
static size_t account(struct entropy_store *r, size_t nbytes, int min, int reserved)
static void extract_buf(struct entropy_store *r, __u8 *out)
static ssize_t _extract_entropy(struct entropy_store *r, void *buf, size_t nbytes, int fips)
static ssize_t extract_entropy(struct entropy_store *r, void *buf, size_t nbytes, int min, int reserved)
static ssize_t extract_entropy_user(struct entropy_store *r, void __user *buf, size_t nbytes)
static void _warn_unseeded_randomness(const char *func_name, void *caller, void **previous)
static void _get_random_bytes(void *buf, int nbytes)
void get_random_bytes(void *buf, int nbytes)
int wait_for_random_bytes(void)
bool rng_is_initialized(void)
int add_random_ready_callback(struct random_ready_callback *rdy)
void del_random_ready_callback(struct random_ready_callback *rdy)
int __must_check get_random_bytes_arch(void *buf, int nbytes)
static void init_std_data(struct entropy_store *r)
static int rand_initialize(void)
void rand_initialize_disk(struct gendisk *disk)
static ssize_t _random_read(int nonblock, char __user *buf, size_t nbytes)
static ssize_t random_read(struct file *file, char __user *buf, size_t nbytes, loff_t *ppos)
static ssize_t urandom_read(struct file *file, char __user *buf, size_t nbytes, loff_t *ppos)
static __poll_t random_poll(struct file *file, poll_table * wait)
static int write_pool(struct entropy_store *r, const char __user *buffer, size_t count)
static ssize_t random_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
static long random_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
static int random_fasync(int fd, struct file *filp, int on)
SYSCALL_DEFINE3(getrandom, char __user *, buf, size_t, count, unsigned int, flags)
static int proc_do_uuid(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static int proc_do_entropy(struct ctl_table *table, int write, void __user *buffer, size_t *lenp, loff_t *ppos)
static DEFINE_PER_CPU(struct batched_entropy, batched_entropy_u64)
; u64 get_random_u64(void)
static DEFINE_PER_CPU(struct batched_entropy, batched_entropy_u32)
; u32 get_random_u32(void)
static void invalidate_batched_entropy(void)
unsigned long randomize_page(unsigned long start, unsigned long range)
void add_hwgenerator_randomness(const char *buffer, size_t count, size_t entropy)
\n
     16 struct entropy_store *r
     11 size_t nbytes
      8 void
      6 int nbytes
      5 void *buf
      5 loff_t *ppos
      4 struct file *file
      4 struct crng_state *crng
      3 size_t count
      3 const void *in
      3 char __user *buf
      2 void __user *buffer
      2 void __user *buf
      2 __u8 tmp[CHACHA_BLOCK_SIZE]
      2 __u8 out[CHACHA_BLOCK_SIZE]
      2 struct work_struct *work
      2 struct random_ready_callback *rdy
      2 struct gendisk *disk
      2 struct fast_pool *f
      2 struct ctl_table *table
      2 struct batched_entropy
      2 size_t *lenp
      2 size_t len
      2 int write
      2 int used
      2 int reserved
      2 int nbits
      2 int min
      2 const char __user *buffer
      2 const char *cp
      1 void **previous
      1 void *caller
      1 unsigned num
      1 unsigned long start
      1 unsigned long range
      1 unsigned long arg
      1 unsigned int value
      1 unsigned int type
      1 unsigned int size
      1 unsigned int code
      1 unsigned int cmd
      1 unsigned int
      1 __u8 *out
      1 struct timer_rand_state *state
      1 struct pt_regs *regs
      1 struct file *filp
      1 struct file *f
      1 size_t entropy
      1 size_t
      1 poll_table * wait
      1 int on
      1 int nonblock
      1 int irq_flags
      1 int irq
      1 int fips
      1 int fd
      1 getrandom
      1 flags
      1 cycles_t start
      1 count
      1 const void *buf
      1 const char *func_name
      1 const char *buffer
      1 CONFIG_RANDOM_TRUST_CPU
      1 char __user *
      1 char *arg
      1 buf
      1 batched_entropy_u64
      1 batched_entropy_u32
      1 add_interrupt_randomness
      1 add_input_randomness
      1 add_hwgenerator_randomness
      1 add_disk_randomness
