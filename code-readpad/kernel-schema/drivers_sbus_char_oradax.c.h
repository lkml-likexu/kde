
\n
static int __init dax_attach(void)
static void __exit dax_detach(void)
static int dax_devmap(struct file *f, struct vm_area_struct *vma)
static void dax_unlock_pages(struct dax_ctx *ctx, int ccb_index, int nelem)
static int dax_lock_page(void *va, struct page **p)
static int dax_lock_pages(struct dax_ctx *ctx, int idx, int nelem, u64 *err_va)
static void dax_ccb_wait(struct dax_ctx *ctx, int idx)
static int dax_close(struct inode *ino, struct file *f)
static ssize_t dax_read(struct file *f, char __user *buf, size_t count, loff_t *ppos)
static ssize_t dax_write(struct file *f, const char __user *buf, size_t count, loff_t *ppos)
static int dax_open(struct inode *inode, struct file *f)
static char *dax_hv_errno(unsigned long hv_ret, int *ret)
static int dax_ccb_kill(u64 ca, u16 *kill_res)
static int dax_ccb_info(u64 ca, struct ccb_info_result *info)
static void dax_prt_ccbs(struct dax_ccb *ccb, int nelem)
static int dax_preprocess_usr_ccbs(struct dax_ctx *ctx, int idx, int nelem)
static int dax_ccb_exec(struct dax_ctx *ctx, const char __user *buf, size_t count, loff_t *ppos)
\n
      5 struct file *f
      5 struct dax_ctx *ctx
      4 int nelem
      3 size_t count
      3 loff_t *ppos
      3 int idx
      2 void
      2 u64 ca
      2 const char __user *buf
      1 void *va
      1 unsigned long hv_ret
      1 u64 *err_va
      1 u16 *kill_res
      1 struct vm_area_struct *vma
      1 struct page **p
      1 struct inode *inode
      1 struct inode *ino
      1 struct dax_ccb *ccb
      1 struct ccb_info_result *info
      1 int *ret
      1 int ccb_index
      1 char __user *buf
