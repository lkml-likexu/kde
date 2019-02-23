
EXPORT_SYMBOL_GPL(stm_register_protocol);
EXPORT_SYMBOL_GPL(stm_unregister_protocol);
EXPORT_SYMBOL_GPL(stm_data_write);
EXPORT_SYMBOL_GPL(stm_register_device);
EXPORT_SYMBOL_GPL(stm_unregister_device);
EXPORT_SYMBOL_GPL(stm_source_register_device);
EXPORT_SYMBOL_GPL(stm_source_unregister_device);
EXPORT_SYMBOL_GPL(stm_source_write);
\n
static ssize_t masters_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t channels_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t hw_override_show(struct device *dev, struct device_attribute *attr, char *buf)
static int stm_dev_match(struct device *dev, const void *data)
struct stm_device *stm_find_device(const char *buf)
void stm_put_device(struct stm_device *stm)
static inline struct stp_master * stm_master(struct stm_device *stm, unsigned int idx)
static int stp_master_alloc(struct stm_device *stm, unsigned int idx)
static void stp_master_free(struct stm_device *stm, unsigned int idx)
static void stm_output_claim(struct stm_device *stm, struct stm_output *output)
static void stm_output_disclaim(struct stm_device *stm, struct stm_output *output)
static int find_free_channels(unsigned long *bitmap, unsigned int start, unsigned int end, unsigned int width)
static int stm_find_master_chan(struct stm_device *stm, unsigned int width, unsigned int *mstart, unsigned int mend, unsigned int *cstart, unsigned int cend)
static int stm_output_assign(struct stm_device *stm, unsigned int width, struct stp_policy_node *policy_node, struct stm_output *output)
static void stm_output_free(struct stm_device *stm, struct stm_output *output)
static void stm_output_init(struct stm_output *output)
static int major_match(struct device *dev, const void *data)
static const struct stm_pdrv_entry * __stm_lookup_protocol(const char *name)
int stm_register_protocol(const struct stm_protocol_driver *pdrv)
void stm_unregister_protocol(const struct stm_protocol_driver *pdrv)
static bool stm_get_protocol(const struct stm_protocol_driver *pdrv)
void stm_put_protocol(const struct stm_protocol_driver *pdrv)
int stm_lookup_protocol(const char *name, const struct stm_protocol_driver **pdrv, const struct config_item_type **node_type)
static int stm_char_open(struct inode *inode, struct file *file)
static int stm_char_release(struct inode *inode, struct file *file)
static int stm_assign_first_policy(struct stm_device *stm, struct stm_output *output, char **ids, unsigned int width)
ssize_t notrace stm_data_write(struct stm_data *data, unsigned int m, unsigned int c, bool ts_first, const void *buf, size_t count)
static ssize_t notrace stm_write(struct stm_device *stm, struct stm_output *output, unsigned int chan, const char *buf, size_t count)
static ssize_t stm_char_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static void stm_mmap_open(struct vm_area_struct *vma)
static void stm_mmap_close(struct vm_area_struct *vma)
static int stm_char_mmap(struct file *file, struct vm_area_struct *vma)
static int stm_char_policy_set_ioctl(struct stm_file *stmf, void __user *arg)
static int stm_char_policy_get_ioctl(struct stm_file *stmf, void __user *arg)
static long stm_char_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long stm_char_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static void stm_device_release(struct device *dev)
int stm_register_device(struct device *parent, struct stm_data *stm_data, struct module *owner)
void stm_unregister_device(struct stm_data *stm_data)
static int stm_source_link_add(struct stm_source_device *src, struct stm_device *stm)
static int __stm_source_link_drop(struct stm_source_device *src, struct stm_device *stm)
static void stm_source_link_drop(struct stm_source_device *src)
static ssize_t stm_source_link_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t stm_source_link_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static void stm_source_device_release(struct device *dev)
int stm_source_register_device(struct device *parent, struct stm_source_data *data)
void stm_source_unregister_device(struct stm_source_data *data)
int notrace stm_source_write(struct stm_source_data *data, unsigned int chan, const char *buf, size_t count)
static int __init stm_core_init(void)
static void __exit stm_core_exit(void)
\n
     13 struct stm_device *stm
      9 struct device *dev
      7 struct stm_output *output
      6 struct file *file
      5 struct device_attribute *attr
      5 size_t count
      4 unsigned int width
      4 const struct stm_protocol_driver *pdrv
      4 const char *buf
      4 char *buf
      3 unsigned int idx
      3 struct vm_area_struct *vma
      3 struct stm_source_device *src
      3 struct stm_source_data *data
      2 void __user *arg
      2 void
      2 unsigned long arg
      2 unsigned int cmd
      2 unsigned int chan
      2 struct stm_file *stmf
      2 struct stm_data *stm_data
      2 struct inode *inode
      2 struct device *parent
      2 const void *data
      2 const char *name
      1 unsigned long *bitmap
      1 unsigned int start
      1 unsigned int *mstart
      1 unsigned int mend
      1 unsigned int m
      1 unsigned int end
      1 unsigned int *cstart
      1 unsigned int cend
      1 unsigned int c
      1 struct stp_policy_node *policy_node
      1 struct stm_data *data
      1 struct module *owner
      1 stm_unregister_protocol
      1 stm_unregister_device
      1 stm_source_write
      1 stm_source_unregister_device
      1 stm_source_register_device
      1 stm_register_protocol
      1 stm_register_device
      1 stm_data_write
      1 loff_t *ppos
      1 const void *buf
      1 const struct stm_protocol_driver **pdrv
      1 const struct config_item_type **node_type
      1 const char __user *buf
      1 char **ids
      1 bool ts_first
