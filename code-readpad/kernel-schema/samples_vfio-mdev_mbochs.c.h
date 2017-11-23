
static const char *vbe_name(u32 index)
static const struct mbochs_type *mbochs_find_type(struct kobject *kobj)
static void mbochs_create_config_space(struct mdev_state *mdev_state)
static int mbochs_check_framebuffer(struct mdev_state *mdev_state, struct mbochs_mode *mode)
static bool mbochs_modes_equal(struct mbochs_mode *mode1, struct mbochs_mode *mode2)
static void handle_pci_cfg_write(struct mdev_state *mdev_state, u16 offset, char *buf, u32 count)
static void handle_mmio_write(struct mdev_state *mdev_state, u16 offset, char *buf, u32 count)
static void handle_mmio_read(struct mdev_state *mdev_state, u16 offset, char *buf, u32 count)
static ssize_t mdev_access(struct mdev_device *mdev, char *buf, size_t count, loff_t pos, bool is_write)
static int mbochs_reset(struct mdev_device *mdev)
static int mbochs_create(struct kobject *kobj, struct mdev_device *mdev)
static int mbochs_remove(struct mdev_device *mdev)
static ssize_t mbochs_read(struct mdev_device *mdev, char __user *buf, size_t count, loff_t *ppos)
static ssize_t mbochs_write(struct mdev_device *mdev, const char __user *buf, size_t count, loff_t *ppos)
static struct page *__mbochs_get_page(struct mdev_state *mdev_state, pgoff_t pgoff)
static struct page *mbochs_get_page(struct mdev_state *mdev_state, pgoff_t pgoff)
static void mbochs_put_pages(struct mdev_state *mdev_state)
static vm_fault_t mbochs_region_vm_fault(struct vm_fault *vmf)
static int mbochs_mmap(struct mdev_device *mdev, struct vm_area_struct *vma)
static vm_fault_t mbochs_dmabuf_vm_fault(struct vm_fault *vmf)
static int mbochs_mmap_dmabuf(struct dma_buf *buf, struct vm_area_struct *vma)
static void mbochs_print_dmabuf(struct mbochs_dmabuf *dmabuf, const char *prefix)
static struct sg_table *mbochs_map_dmabuf(struct dma_buf_attachment *at, enum dma_data_direction direction)
static void mbochs_unmap_dmabuf(struct dma_buf_attachment *at, struct sg_table *sg, enum dma_data_direction direction)
static void mbochs_release_dmabuf(struct dma_buf *buf)
static void *mbochs_kmap_dmabuf(struct dma_buf *buf, unsigned long page_num)
static void mbochs_kunmap_dmabuf(struct dma_buf *buf, unsigned long page_num, void *vaddr)
static struct mbochs_dmabuf *mbochs_dmabuf_alloc(struct mdev_state *mdev_state, struct mbochs_mode *mode)
static struct mbochs_dmabuf * mbochs_dmabuf_find_by_mode(struct mdev_state *mdev_state, struct mbochs_mode *mode)
static struct mbochs_dmabuf * mbochs_dmabuf_find_by_id(struct mdev_state *mdev_state, u32 id)
static int mbochs_dmabuf_export(struct mbochs_dmabuf *dmabuf)
static int mbochs_get_region_info(struct mdev_device *mdev, struct vfio_region_info *region_info, u16 *cap_type_id, void **cap_type)
static int mbochs_get_irq_info(struct mdev_device *mdev, struct vfio_irq_info *irq_info)
static int mbochs_get_device_info(struct mdev_device *mdev, struct vfio_device_info *dev_info)
static int mbochs_query_gfx_plane(struct mdev_device *mdev, struct vfio_device_gfx_plane_info *plane)
static int mbochs_get_gfx_dmabuf(struct mdev_device *mdev, u32 id)
static long mbochs_ioctl(struct mdev_device *mdev, unsigned int cmd, unsigned long arg)
static int mbochs_open(struct mdev_device *mdev)
static void mbochs_close(struct mdev_device *mdev)
static ssize_t memory_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t name_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t description_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t available_instances_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t device_api_show(struct kobject *kobj, struct device *dev, char *buf)
static void mbochs_device_release(struct device *dev)
static int __init mbochs_dev_init(void)
static void __exit mbochs_dev_exit(void)
  15 struct mdev_device *mdev
  11 struct mdev_state *mdev_state
   9 char *buf
   6 struct kobject *kobj
   6 struct device *dev
   4 struct dma_buf *buf
   3 u32 count
   3 u16 offset
   3 struct mbochs_mode *mode
   3 size_t count
   2 void
   2 unsigned long page_num
   2 u32 id
   2 struct vm_fault *vmf
   2 struct vm_area_struct *vma
   2 struct mbochs_dmabuf *dmabuf
   2 struct dma_buf_attachment *at
   2 pgoff_t pgoff
   2 loff_t *ppos
   2 enum dma_data_direction direction
   1 void *vaddr
   1 void **cap_type
   1 unsigned long arg
   1 unsigned int cmd
   1 u32 index
   1 u16 *cap_type_id
   1 struct vfio_region_info *region_info
   1 struct vfio_irq_info *irq_info
   1 struct vfio_device_info *dev_info
   1 struct vfio_device_gfx_plane_info *plane
   1 struct sg_table *sg
   1 struct mbochs_mode *mode2
   1 struct mbochs_mode *mode1
   1 struct device_attribute *attr
   1 loff_t pos
   1 const char __user *buf
   1 const char *prefix
   1 char __user *buf
   1 bool is_write
