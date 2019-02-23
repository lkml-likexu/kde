
\n
static irqreturn_t DIO0_irq_handler(int irq, void *dev_id)
static irqreturn_t DIO1_irq_handler(int irq, void *dev_id)
static int rf69_set_rx_cfg(struct pi433_device *dev, struct pi433_rx_cfg *rx_cfg)
static int rf69_set_tx_cfg(struct pi433_device *dev, struct pi433_tx_cfg *tx_cfg)
static int pi433_start_rx(struct pi433_device *dev)
static int pi433_receive(void *data)
static int pi433_tx_thread(void *data)
static ssize_t pi433_read(struct file *filp, char __user *buf, size_t size, loff_t *f_pos)
static ssize_t pi433_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
static long pi433_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
static long pi433_compat_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
static int pi433_open(struct inode *inode, struct file *filp)
static int pi433_release(struct inode *inode, struct file *filp)
static int setup_gpio(struct pi433_device *device)
static void free_gpio(struct pi433_device *device)
static int pi433_get_minor(struct pi433_device *device)
static void pi433_free_minor(struct pi433_device *dev)
static int pi433_probe(struct spi_device *spi)
static int pi433_remove(struct spi_device *spi)
static int __init pi433_init(void)
static void __exit pi433_exit(void)
\n
      6 struct file *filp
      4 struct pi433_device *dev
      3 struct pi433_device *device
      2 void *dev_id
      2 void *data
      2 void
      2 unsigned long arg
      2 unsigned int cmd
      2 struct spi_device *spi
      2 struct inode *inode
      2 loff_t *f_pos
      2 int irq
      1 struct pi433_tx_cfg *tx_cfg
      1 struct pi433_rx_cfg *rx_cfg
      1 size_t size
      1 size_t count
      1 const char __user *buf
      1 char __user *buf
