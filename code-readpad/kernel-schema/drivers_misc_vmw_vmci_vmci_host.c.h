
\n
bool vmci_host_code_active(void)
static int vmci_host_open(struct inode *inode, struct file *filp)
static int vmci_host_close(struct inode *inode, struct file *filp)
static __poll_t vmci_host_poll(struct file *filp, poll_table *wait)
static int drv_cp_harray_to_user(void __user *user_buf_uva, u64 *user_buf_size, struct vmci_handle_arr *handle_array, int *retval)
static int vmci_host_setup_notify(struct vmci_ctx *context, unsigned long uva)
static int vmci_host_get_version(struct vmci_host_dev *vmci_host_dev, unsigned int cmd, void __user *uptr)
static int vmci_host_do_init_context(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_send_datagram(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_receive_datagram(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_alloc_queuepair(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_queuepair_setva(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_queuepair_setpf(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_qp_detach(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_ctx_add_notify(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_ctx_remove_notify(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_ctx_get_cpt_state(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_ctx_set_cpt_state(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_get_context_id(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_set_notify(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_notify_resource(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static int vmci_host_do_recv_notifications(struct vmci_host_dev *vmci_host_dev, const char *ioctl_name, void __user *uptr)
static long vmci_host_unlocked_ioctl(struct file *filp, unsigned int iocmd, unsigned long ioarg)
int __init vmci_host_init(void)
void __exit vmci_host_exit(void)
\n
     16 void __user *uptr
     16 struct vmci_host_dev *vmci_host_dev
     15 const char *ioctl_name
      4 struct file *filp
      3 void
      2 struct inode *inode
      1 void __user *user_buf_uva
      1 unsigned long uva
      1 unsigned long ioarg
      1 unsigned int iocmd
      1 unsigned int cmd
      1 u64 *user_buf_size
      1 struct vmci_handle_arr *handle_array
      1 struct vmci_ctx *context
      1 poll_table *wait
      1 int *retval
