
static inline bool is_omap_iommu_detached(struct omap_iommu *obj)
static ssize_t omap2_iommu_dump_ctx(struct omap_iommu *obj, char *buf, ssize_t len)
static ssize_t omap_iommu_dump_ctx(struct omap_iommu *obj, char *buf, ssize_t bytes)
static ssize_t debug_read_regs(struct file *file, char __user *userbuf, size_t count, loff_t *ppos)
static int __dump_tlb_entries(struct omap_iommu *obj, struct cr_regs *crs, int num)
static ssize_t iotlb_dump_cr(struct omap_iommu *obj, struct cr_regs *cr, struct seq_file *s)
static size_t omap_dump_tlb_entries(struct omap_iommu *obj, struct seq_file *s)
static int debug_read_tlb(struct seq_file *s, void *data)
static void dump_ioptable(struct seq_file *s)
static int debug_read_pagetable(struct seq_file *s, void *data)
void omap_iommu_debugfs_add(struct omap_iommu *obj)
void omap_iommu_debugfs_remove(struct omap_iommu *obj)
void __init omap_iommu_debugfs_init(void)
void __exit omap_iommu_debugfs_exit(void)
   8 struct omap_iommu *obj
   5 struct seq_file *s
   2 void *data
   2 void
   2 char *buf
   1 struct file *file
   1 struct cr_regs *crs
   1 struct cr_regs *cr
   1 ssize_t len
   1 ssize_t bytes
   1 size_t count
   1 loff_t *ppos
   1 int num
   1 char __user *userbuf
