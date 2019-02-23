
\n
static int rio_mport_maint_rd(struct mport_cdev_priv *priv, void __user *arg, int local)
static int rio_mport_maint_wr(struct mport_cdev_priv *priv, void __user *arg, int local)
static int rio_mport_create_outbound_mapping(struct mport_dev *md, struct file *filp, u16 rioid, u64 raddr, u32 size, dma_addr_t *paddr)
static int rio_mport_get_outbound_mapping(struct mport_dev *md, struct file *filp, u16 rioid, u64 raddr, u32 size, dma_addr_t *paddr)
static int rio_mport_obw_map(struct file *filp, void __user *arg)
static int rio_mport_obw_free(struct file *filp, void __user *arg)
static int maint_hdid_set(struct mport_cdev_priv *priv, void __user *arg)
static int maint_comptag_set(struct mport_cdev_priv *priv, void __user *arg)
static void mport_release_def_dma(struct kref *dma_ref)
static void mport_release_dma(struct kref *dma_ref)
static void dma_req_free(struct kref *ref)
static void dma_xfer_callback(void *param)
static struct dma_async_tx_descriptor *prep_dma_xfer(struct dma_chan *chan, struct rio_transfer_io *transfer, struct sg_table *sgt, int nents, enum dma_transfer_direction dir, enum dma_ctrl_flags flags)
static int get_dma_channel(struct mport_cdev_priv *priv)
static void put_dma_channel(struct mport_cdev_priv *priv)
static int do_dma_request(struct mport_dma_req *req, struct rio_transfer_io *xfer, enum rio_transfer_sync sync, int nents)
static int rio_dma_transfer(struct file *filp, u32 transfer_mode, enum rio_transfer_sync sync, enum dma_data_direction dir, struct rio_transfer_io *xfer)
static int rio_mport_transfer_ioctl(struct file *filp, void __user *arg)
static int rio_mport_wait_for_async_dma(struct file *filp, void __user *arg)
static int rio_mport_create_dma_mapping(struct mport_dev *md, struct file *filp, u64 size, struct rio_mport_mapping **mapping)
static int rio_mport_alloc_dma(struct file *filp, void __user *arg)
static int rio_mport_free_dma(struct file *filp, void __user *arg)
return 0; } static int rio_mport_transfer_ioctl(struct file *filp, void *arg)
static int rio_mport_wait_for_async_dma(struct file *filp, void __user *arg)
static int rio_mport_alloc_dma(struct file *filp, void __user *arg)
static int rio_mport_free_dma(struct file *filp, void __user *arg)
static int rio_mport_create_inbound_mapping(struct mport_dev *md, struct file *filp, u64 raddr, u64 size, struct rio_mport_mapping **mapping)
static int rio_mport_get_inbound_mapping(struct mport_dev *md, struct file *filp, u64 raddr, u64 size, struct rio_mport_mapping **mapping)
static int rio_mport_map_inbound(struct file *filp, void __user *arg)
static int rio_mport_inbound_free(struct file *filp, void __user *arg)
static int maint_port_idx_get(struct mport_cdev_priv *priv, void __user *arg)
static int rio_mport_add_event(struct mport_cdev_priv *priv, struct rio_event *event)
static void rio_mport_doorbell_handler(struct rio_mport *mport, void *dev_id, u16 src, u16 dst, u16 info)
static int rio_mport_add_db_filter(struct mport_cdev_priv *priv, void __user *arg)
static void rio_mport_delete_db_filter(struct rio_mport_db_filter *db_filter)
static int rio_mport_remove_db_filter(struct mport_cdev_priv *priv, void __user *arg)
static int rio_mport_match_pw(union rio_pw_msg *msg, struct rio_pw_filter *filter)
static int rio_mport_pw_handler(struct rio_mport *mport, void *context, union rio_pw_msg *msg, int step)
static int rio_mport_add_pw_filter(struct mport_cdev_priv *priv, void __user *arg)
static void rio_mport_delete_pw_filter(struct rio_mport_pw_filter *pw_filter)
static int rio_mport_match_pw_filter(struct rio_pw_filter *a, struct rio_pw_filter *b)
static int rio_mport_remove_pw_filter(struct mport_cdev_priv *priv, void __user *arg)
static void rio_release_dev(struct device *dev)
static void rio_release_net(struct device *dev)
static int rio_mport_add_riodev(struct mport_cdev_priv *priv, void __user *arg)
static int rio_mport_del_riodev(struct mport_cdev_priv *priv, void __user *arg)
static int mport_cdev_open(struct inode *inode, struct file *filp)
static int mport_cdev_fasync(int fd, struct file *filp, int mode)
static void mport_cdev_release_dma(struct file *filp)
static int mport_cdev_release(struct inode *inode, struct file *filp)
static long mport_cdev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
static void mport_release_mapping(struct kref *ref)
static void mport_mm_open(struct vm_area_struct *vma)
static void mport_mm_close(struct vm_area_struct *vma)
static int mport_cdev_mmap(struct file *filp, struct vm_area_struct *vma)
static __poll_t mport_cdev_poll(struct file *filp, poll_table *wait)
static ssize_t mport_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
static ssize_t mport_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
static void mport_device_release(struct device *dev)
static struct mport_dev *mport_cdev_add(struct rio_mport *mport)
static void mport_cdev_terminate_dma(struct mport_dev *md)
static int mport_cdev_kill_fasync(struct mport_dev *md)
static void mport_cdev_remove(struct mport_dev *md)
static int mport_add_mport(struct device *dev, struct class_interface *class_intf)
static void mport_remove_mport(struct device *dev, struct class_interface *class_intf)
static int __init mport_init(void)
static void __exit mport_exit(void)
\n
     27 struct file *filp
     22 void __user *arg
     14 struct mport_cdev_priv *priv
      8 struct mport_dev *md
      5 struct device *dev
      4 u64 raddr
      3 u64 size
      3 struct vm_area_struct *vma
      3 struct rio_mport *mport
      3 struct rio_mport_mapping **mapping
      2 void
      2 union rio_pw_msg *msg
      2 u32 size
      2 u16 rioid
      2 struct rio_transfer_io *xfer
      2 struct kref *ref
      2 struct kref *dma_ref
      2 struct inode *inode
      2 struct class_interface *class_intf
      2 size_t count
      2 loff_t *ppos
      2 int nents
      2 int local
      2 enum rio_transfer_sync sync
      2 dma_addr_t *paddr
      1 void *param
      1 void *dev_id
      1 void *context
      1 void *arg
      1 unsigned long arg
      1 unsigned int cmd
      1 u32 transfer_mode
      1 u16 src
      1 u16 info
      1 u16 dst
      1 struct sg_table *sgt
      1 struct rio_transfer_io *transfer
      1 struct rio_pw_filter *filter
      1 struct rio_pw_filter *b
      1 struct rio_pw_filter *a
      1 struct rio_mport_pw_filter *pw_filter
      1 struct rio_mport_db_filter *db_filter
      1 struct rio_event *event
      1 struct mport_dma_req *req
      1 struct dma_chan *chan
      1 poll_table *wait
      1 int step
      1 int mode
      1 int fd
      1 enum dma_transfer_direction dir
      1 enum dma_data_direction dir
      1 enum dma_ctrl_flags flags
      1 const char __user *buf
      1 char __user *buf
