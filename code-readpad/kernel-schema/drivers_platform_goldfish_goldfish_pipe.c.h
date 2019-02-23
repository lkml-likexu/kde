
\n
static int goldfish_pipe_cmd_locked(struct goldfish_pipe *pipe, enum PipeCmdCode cmd)
static int goldfish_pipe_cmd(struct goldfish_pipe *pipe, enum PipeCmdCode cmd)
static int goldfish_pipe_error_convert(int status)
static int pin_user_pages(unsigned long first_page, unsigned long last_page, unsigned int last_page_size, int is_write, struct page *pages[MAX_BUFFERS_PER_COMMAND], unsigned int *iter_last_page_size)
static void release_user_pages(struct page **pages, int pages_count, int is_write, s32 consumed_size)
static void populate_rw_params(struct page **pages, int pages_count, unsigned long address, unsigned long address_end, unsigned long first_page, unsigned long last_page, unsigned int iter_last_page_size, int is_write, struct goldfish_pipe_command *command)
static int transfer_max_buffers(struct goldfish_pipe *pipe, unsigned long address, unsigned long address_end, int is_write, unsigned long last_page, unsigned int last_page_size, s32 *consumed_size, int *status)
static int wait_for_host_signal(struct goldfish_pipe *pipe, int is_write)
static ssize_t goldfish_pipe_read_write(struct file *filp, char __user *buffer, size_t bufflen, int is_write)
static ssize_t goldfish_pipe_read(struct file *filp, char __user *buffer, size_t bufflen, loff_t *ppos)
static ssize_t goldfish_pipe_write(struct file *filp, const char __user *buffer, size_t bufflen, loff_t *ppos)
static __poll_t goldfish_pipe_poll(struct file *filp, poll_table *wait)
static void signalled_pipes_add_locked(struct goldfish_pipe_dev *dev, u32 id, u32 flags)
static void signalled_pipes_remove_locked(struct goldfish_pipe_dev *dev, struct goldfish_pipe *pipe)
static struct goldfish_pipe *signalled_pipes_pop_front( struct goldfish_pipe_dev *dev, int *wakes)
static void goldfish_interrupt_task(unsigned long dev_addr)
static irqreturn_t goldfish_pipe_interrupt(int irq, void *dev_id)
static int get_free_pipe_id_locked(struct goldfish_pipe_dev *dev)
static struct goldfish_pipe_dev *to_goldfish_pipe_dev(struct file *file)
static int goldfish_pipe_open(struct inode *inode, struct file *file)
static int goldfish_pipe_release(struct inode *inode, struct file *filp)
static void init_miscdevice(struct miscdevice *miscdev)
static void write_pa_addr(void *addr, void __iomem *portl, void __iomem *porth)
static int goldfish_pipe_device_init(struct platform_device *pdev, struct goldfish_pipe_dev *dev)
static void goldfish_pipe_device_deinit(struct platform_device *pdev, struct goldfish_pipe_dev *dev)
static int goldfish_pipe_probe(struct platform_device *pdev)
static int goldfish_pipe_remove(struct platform_device *pdev)
\n
      6 struct goldfish_pipe_dev *dev
      6 int is_write
      5 struct goldfish_pipe *pipe
      5 struct file *filp
      4 struct platform_device *pdev
      3 unsigned long last_page
      3 size_t bufflen
      2 unsigned long first_page
      2 unsigned long address_end
      2 unsigned long address
      2 unsigned int last_page_size
      2 struct page **pages
      2 struct inode *inode
      2 struct file *file
      2 loff_t *ppos
      2 int pages_count
      2 enum PipeCmdCode cmd
      2 char __user *buffer
      1 void __iomem *portl
      1 void __iomem *porth
      1 void *dev_id
      1 void *addr
      1 unsigned long dev_addr
      1 unsigned int iter_last_page_size
      1 unsigned int *iter_last_page_size
      1 u32 id
      1 u32 flags
      1 struct page *pages[MAX_BUFFERS_PER_COMMAND]
      1 struct miscdevice *miscdev
      1 struct goldfish_pipe_command *command
      1 s32 consumed_size
      1 s32 *consumed_size
      1 poll_table *wait
      1 int *wakes
      1 int *status
      1 int status
      1 int irq
      1 const char __user *buffer
