
\n
static void decode_register(char *str, size_t size, const struct error_descr *descr, const uint64_t reg)
static unsigned long get_bits(unsigned long data, int pos, int width)
define DEBUGFS_FIELD_ATTR(_type, _field)
\ static ssize_t thunderx__type__field_read(struct file *file, \char __user *data, \size_t count, loff_t *ppos)
\define DEBUGFS_FIELD_ATTR(_type, _field)
\ static ssize_t thunderx__type__field_read(struct file *file, \char __user *data, \size_t count, loff_t *ppos)
\struct thunderx__type *pdata = file->private_data;\char buf[20]; \\snprintf(buf, count, "0x%016llx", pdata->_field)
;\return simple_read_from_buffer(data, count, ppos, \buf, sizeof(buf)
)
;\ } \\ static ssize_t thunderx__type__field_write(struct file *file, \ const char __user *data, \ size_t count, loff_t *ppos)
\define DEBUGFS_REG_ATTR(_type, _name, _reg)
\ static ssize_t thunderx__type__name_read(struct file *file, \ char __user *data, \ size_t count, loff_t *ppos)
\define DEBUGFS_REG_ATTR(_type, _name, _reg)
\ static ssize_t thunderx__type__name_read(struct file *file, \ char __user *data, \ size_t count, loff_t *ppos)
\struct thunderx__type *pdata = file->private_data;\char buf[20]; \\sprintf(buf, "0x%016llx", readq(pdata->regs + _reg)
)
;\return simple_read_from_buffer(data, count, ppos, \buf, sizeof(buf)
)
;\ } \\ static ssize_t thunderx__type__name_write(struct file *file, \const char __user *data, \size_t count, loff_t *ppos)
\static ssize_t thunderx_lmc_inject_int_write(struct file *file, const char __user *data, size_t count, loff_t *ppos)
static ssize_t thunderx_lmc_int_read(struct file *file, char __user *data, size_t count, loff_t *ppos)
static int inject_ecc_fn(void *arg)
static ssize_t thunderx_lmc_inject_ecc_write(struct file *file, const char __user *data, size_t count, loff_t *ppos)
static int thunderx_create_debugfs_nodes(struct dentry *parent, struct debugfs_entry *attrs[], void *data, size_t num)
static phys_addr_t thunderx_faddr_to_phys(u64 faddr, struct thunderx_lmc *lmc)
static unsigned int thunderx_get_num_lmcs(unsigned int node)
static irqreturn_t thunderx_lmc_err_isr(int irq, void *dev_id)
static irqreturn_t thunderx_lmc_threaded_isr(int irq, void *dev_id)
static inline int pci_dev_to_mc_idx(struct pci_dev *pdev)
static int thunderx_lmc_probe(struct pci_dev *pdev, const struct pci_device_id *id)
static void thunderx_lmc_remove(struct pci_dev *pdev)
static irqreturn_t thunderx_ocx_com_isr(int irq, void *irq_id)
static irqreturn_t thunderx_ocx_com_threaded_isr(int irq, void *irq_id)
static irqreturn_t thunderx_ocx_lnk_isr(int irq, void *irq_id)
static irqreturn_t thunderx_ocx_lnk_threaded_isr(int irq, void *irq_id)
static void thunderx_ocx_clearstats(struct thunderx_ocx *ocx)
static int thunderx_ocx_probe(struct pci_dev *pdev, const struct pci_device_id *id)
static void thunderx_ocx_remove(struct pci_dev *pdev)
static irqreturn_t thunderx_l2c_tad_isr(int irq, void *irq_id)
static irqreturn_t thunderx_l2c_cbc_isr(int irq, void *irq_id)
static irqreturn_t thunderx_l2c_mci_isr(int irq, void *irq_id)
static irqreturn_t thunderx_l2c_threaded_isr(int irq, void *irq_id)
static int thunderx_l2c_probe(struct pci_dev *pdev, const struct pci_device_id *id)
static void thunderx_l2c_remove(struct pci_dev *pdev)
static int __init thunderx_edac_init(void)
static void __exit thunderx_edac_exit(void)
\n
     10 int irq
      9 struct file *file
      9 loff_t *ppos
      8 void *irq_id
      7 struct pci_dev *pdev
      4 _type
      3 size_t count
      3 \size_t count
      3 \ size_t count
      3 count
      3 const struct pci_device_id *id
      2 void *dev_id
      2 void
      2 sizeofbuf
      2 _reg
      2 ppos
      2 _name
      2 _field
      2 data
      2 const char __user *data
      2 \char __user *data
      2 \ char __user *data
      2 \buf
      2 buf
      2 "0x%016llx"
      1 void *data
      1 void *arg
      1 unsigned long data
      1 unsigned int node
      1 u64 faddr
      1 struct thunderx_ocx *ocx
      1 struct thunderx_lmc *lmc
      1 struct dentry *parent
      1 struct debugfs_entry *attrs[]
      1 size_t size
      1 size_t num
      1 readqpdata->regs + _reg
      1 pdata->_field
      1 int width
      1 int pos
      1 const uint64_t reg
      1 const struct error_descr *descr
      1 \const char __user *data
      1 \ const char __user *data
      1 char __user *data
      1 char *str
