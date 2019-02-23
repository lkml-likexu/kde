
\n
static int usbfs_increase_memory_usage(u64 amount)
static void usbfs_decrease_memory_usage(u64 amount)
static int connected(struct usb_dev_state *ps)
static void dec_usb_memory_use_count(struct usb_memory *usbm, int *count)
static void usbdev_vm_open(struct vm_area_struct *vma)
static void usbdev_vm_close(struct vm_area_struct *vma)
static int usbdev_mmap(struct file *file, struct vm_area_struct *vma)
static ssize_t usbdev_read(struct file *file, char __user *buf, size_t nbytes, loff_t *ppos)
static struct async *alloc_async(unsigned int numisoframes)
static void free_async(struct async *as)
static void async_newpending(struct async *as)
static void async_removepending(struct async *as)
static struct async *async_getcompleted(struct usb_dev_state *ps)
static struct async *async_getpending(struct usb_dev_state *ps, void __user *userurb)
static void snoop_urb(struct usb_device *udev, void __user *userurb, int pipe, unsigned length, int timeout_or_status, enum snoop_when when, unsigned char *data, unsigned data_len)
static void snoop_urb_data(struct urb *urb, unsigned len)
static int copy_urb_data_to_user(u8 __user *userbuffer, struct urb *urb)
static void cancel_bulk_urbs(struct usb_dev_state *ps, unsigned bulk_addr)
__releases(ps->lock)
__acquires(ps->lock)
static void async_completed(struct urb *urb)
static void destroy_async(struct usb_dev_state *ps, struct list_head *list)
static void destroy_async_on_interface(struct usb_dev_state *ps, unsigned int ifnum)
static void destroy_all_async(struct usb_dev_state *ps)
static int driver_probe(struct usb_interface *intf, const struct usb_device_id *id)
static void driver_disconnect(struct usb_interface *intf)
static int driver_suspend(struct usb_interface *intf, pm_message_t msg)
static int driver_resume(struct usb_interface *intf)
static int claimintf(struct usb_dev_state *ps, unsigned int ifnum)
static int releaseintf(struct usb_dev_state *ps, unsigned int ifnum)
static int checkintf(struct usb_dev_state *ps, unsigned int ifnum)
static int findintfep(struct usb_device *dev, unsigned int ep)
static int check_ctrlrecip(struct usb_dev_state *ps, unsigned int requesttype, unsigned int request, unsigned int index)
static struct usb_host_endpoint *ep_to_host_endpoint(struct usb_device *dev, unsigned char ep)
static int parse_usbdevfs_streams(struct usb_dev_state *ps, struct usbdevfs_streams __user *streams, unsigned int *num_streams_ret, unsigned int *num_eps_ret, struct usb_host_endpoint ***eps_ret, struct usb_interface **intf_ret)
static int match_devt(struct device *dev, void *data)
static struct usb_device *usbdev_lookup_by_devt(dev_t devt)
static int usbdev_open(struct inode *inode, struct file *file)
static int usbdev_release(struct inode *inode, struct file *file)
static int proc_control(struct usb_dev_state *ps, void __user *arg)
static int proc_bulk(struct usb_dev_state *ps, void __user *arg)
static void check_reset_of_active_ep(struct usb_device *udev, unsigned int epnum, char *ioctl_name)
static int proc_resetep(struct usb_dev_state *ps, void __user *arg)
static int proc_clearhalt(struct usb_dev_state *ps, void __user *arg)
static int proc_getdriver(struct usb_dev_state *ps, void __user *arg)
static int proc_connectinfo(struct usb_dev_state *ps, void __user *arg)
static int proc_resetdevice(struct usb_dev_state *ps)
static int proc_setintf(struct usb_dev_state *ps, void __user *arg)
static int proc_setconfig(struct usb_dev_state *ps, void __user *arg)
static struct usb_memory * find_memory_area(struct usb_dev_state *ps, const struct usbdevfs_urb *uurb)
static int proc_do_submiturb(struct usb_dev_state *ps, struct usbdevfs_urb *uurb, struct usbdevfs_iso_packet_desc __user *iso_frame_desc, void __user *arg)
static int proc_submiturb(struct usb_dev_state *ps, void __user *arg)
static int proc_unlinkurb(struct usb_dev_state *ps, void __user *arg)
static void compute_isochronous_actual_length(struct urb *urb)
static int processcompl(struct async *as, void __user * __user *arg)
static struct async *reap_as(struct usb_dev_state *ps)
static int proc_reapurb(struct usb_dev_state *ps, void __user *arg)
static int proc_reapurbnonblock(struct usb_dev_state *ps, void __user *arg)
static int proc_control_compat(struct usb_dev_state *ps, struct usbdevfs_ctrltransfer32 __user *p32)
static int proc_bulk_compat(struct usb_dev_state *ps, struct usbdevfs_bulktransfer32 __user *p32)
return proc_bulk(ps, p)
; } static int proc_disconnectsignal_compat(struct usb_dev_state *ps, void __user *arg)
static int get_urb32(struct usbdevfs_urb *kurb, struct usbdevfs_urb32 __user *uurb)
static int proc_submiturb_compat(struct usb_dev_state *ps, void __user *arg)
static int processcompl_compat(struct async *as, void __user * __user *arg)
static int proc_reapurb_compat(struct usb_dev_state *ps, void __user *arg)
static int proc_reapurbnonblock_compat(struct usb_dev_state *ps, void __user *arg)
static int proc_disconnectsignal(struct usb_dev_state *ps, void __user *arg)
static int proc_claiminterface(struct usb_dev_state *ps, void __user *arg)
static int proc_releaseinterface(struct usb_dev_state *ps, void __user *arg)
static int proc_ioctl(struct usb_dev_state *ps, struct usbdevfs_ioctl *ctl)
static int proc_ioctl_default(struct usb_dev_state *ps, void __user *arg)
static int proc_ioctl_compat(struct usb_dev_state *ps, compat_uptr_t arg)
static int proc_claim_port(struct usb_dev_state *ps, void __user *arg)
static int proc_release_port(struct usb_dev_state *ps, void __user *arg)
static int proc_get_capabilities(struct usb_dev_state *ps, void __user *arg)
static int proc_disconnect_claim(struct usb_dev_state *ps, void __user *arg)
static int proc_alloc_streams(struct usb_dev_state *ps, void __user *arg)
static int proc_free_streams(struct usb_dev_state *ps, void __user *arg)
static int proc_drop_privileges(struct usb_dev_state *ps, void __user *arg)
static long usbdev_do_ioctl(struct file *file, unsigned int cmd, void __user *p)
static long usbdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static long usbdev_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static __poll_t usbdev_poll(struct file *file, struct poll_table_struct *wait)
static void usbdev_remove(struct usb_device *udev)
static int usbdev_notify(struct notifier_block *self, unsigned long action, void *dev)
int __init usb_devio_init(void)
void usb_devio_cleanup(void)
\n
     47 struct usb_dev_state *ps
     28 void __user *arg
      8 struct file *file
      5 struct async *as
      4 unsigned int ifnum
      4 struct usb_interface *intf
      4 struct urb *urb
      3 unsigned int cmd
      3 struct vm_area_struct *vma
      3 struct usb_device *udev
      2 void __user *userurb
      2 void __user * __user *arg
      2 void
      2 unsigned long arg
      2 u64 amount
      2 struct usb_device *dev
      2 struct inode *inode
      2 ps->lock
      1 void __user *p
      1 void *dev
      1 void *data
      1 unsigned long action
      1 unsigned length
      1 unsigned len
      1 unsigned int requesttype
      1 unsigned int request
      1 unsigned int *num_streams_ret
      1 unsigned int numisoframes
      1 unsigned int *num_eps_ret
      1 unsigned int index
      1 unsigned int epnum
      1 unsigned int ep
      1 unsigned data_len
      1 unsigned char ep
      1 unsigned char *data
      1 unsigned bulk_addr
      1 u8 __user *userbuffer
      1 struct usb_memory *usbm
      1 struct usb_interface **intf_ret
      1 struct usb_host_endpoint ***eps_ret
      1 struct usbdevfs_urb *uurb
      1 struct usbdevfs_urb *kurb
      1 struct usbdevfs_urb32 __user *uurb
      1 struct usbdevfs_streams __user *streams
      1 struct usbdevfs_iso_packet_desc __user *iso_frame_desc
      1 struct usbdevfs_ioctl *ctl
      1 struct usbdevfs_ctrltransfer32 __user *p32
      1 struct usbdevfs_bulktransfer32 __user *p32
      1 struct poll_table_struct *wait
      1 struct notifier_block *self
      1 struct list_head *list
      1 struct device *dev
      1 size_t nbytes
      1 ps
      1 pm_message_t msg
      1 p
      1 loff_t *ppos
      1 int timeout_or_status
      1 int pipe
      1 int *count
      1 enum snoop_when when
      1 dev_t devt
      1 const struct usb_device_id *id
      1 const struct usbdevfs_urb *uurb
      1 compat_uptr_t arg
      1 char __user *buf
      1 char *ioctl_name
