
EXPORT_SYMBOL_GPL(kvmgt_mpt);
\n
static inline bool handle_valid(unsigned long handle)
static void gvt_unpin_guest_page(struct intel_vgpu *vgpu, unsigned long gfn, unsigned long size)
static int gvt_pin_guest_page(struct intel_vgpu *vgpu, unsigned long gfn, unsigned long size, struct page **page)
static int gvt_dma_map_page(struct intel_vgpu *vgpu, unsigned long gfn, dma_addr_t *dma_addr, unsigned long size)
static void gvt_dma_unmap_page(struct intel_vgpu *vgpu, unsigned long gfn, dma_addr_t dma_addr, unsigned long size)
static struct gvt_dma *__gvt_cache_find_dma_addr(struct intel_vgpu *vgpu, dma_addr_t dma_addr)
static struct gvt_dma *__gvt_cache_find_gfn(struct intel_vgpu *vgpu, gfn_t gfn)
static int __gvt_cache_add(struct intel_vgpu *vgpu, gfn_t gfn, dma_addr_t dma_addr, unsigned long size)
static void __gvt_cache_remove_entry(struct intel_vgpu *vgpu, struct gvt_dma *entry)
static void gvt_cache_destroy(struct intel_vgpu *vgpu)
static void gvt_cache_init(struct intel_vgpu *vgpu)
static void kvmgt_protect_table_init(struct kvmgt_guest_info *info)
static void kvmgt_protect_table_destroy(struct kvmgt_guest_info *info)
static struct kvmgt_pgfn * __kvmgt_protect_table_find(struct kvmgt_guest_info *info, gfn_t gfn)
static bool kvmgt_gfn_is_write_protected(struct kvmgt_guest_info *info, gfn_t gfn)
static void kvmgt_protect_table_add(struct kvmgt_guest_info *info, gfn_t gfn)
static void kvmgt_protect_table_del(struct kvmgt_guest_info *info, gfn_t gfn)
static size_t intel_vgpu_reg_rw_opregion(struct intel_vgpu *vgpu, char *buf, size_t count, loff_t *ppos, bool iswrite)
static void intel_vgpu_reg_release_opregion(struct intel_vgpu *vgpu, struct vfio_region *region)
static int intel_vgpu_register_reg(struct intel_vgpu *vgpu, unsigned int type, unsigned int subtype, const struct intel_vgpu_regops *ops, size_t size, u32 flags, void *data)
static int kvmgt_get_vfio_device(void *p_vgpu)
static int kvmgt_set_opregion(void *p_vgpu)
static void kvmgt_put_vfio_device(void *vgpu)
static int intel_vgpu_create(struct kobject *kobj, struct mdev_device *mdev)
static int intel_vgpu_remove(struct mdev_device *mdev)
static int intel_vgpu_iommu_notifier(struct notifier_block *nb, unsigned long action, void *data)
static int intel_vgpu_group_notifier(struct notifier_block *nb, unsigned long action, void *data)
static int intel_vgpu_open(struct mdev_device *mdev)
static void intel_vgpu_release_msi_eventfd_ctx(struct intel_vgpu *vgpu)
static void __intel_vgpu_release(struct intel_vgpu *vgpu)
static void intel_vgpu_release(struct mdev_device *mdev)
static void intel_vgpu_release_work(struct work_struct *work)
static uint64_t intel_vgpu_get_bar_addr(struct intel_vgpu *vgpu, int bar)
static int intel_vgpu_bar_rw(struct intel_vgpu *vgpu, int bar, uint64_t off, void *buf, unsigned int count, bool is_write)
static inline bool intel_vgpu_in_aperture(struct intel_vgpu *vgpu, uint64_t off)
static int intel_vgpu_aperture_rw(struct intel_vgpu *vgpu, uint64_t off, void *buf, unsigned long count, bool is_write)
static ssize_t intel_vgpu_rw(struct mdev_device *mdev, char *buf, size_t count, loff_t *ppos, bool is_write)
static bool gtt_entry(struct mdev_device *mdev, loff_t *ppos)
static ssize_t intel_vgpu_read(struct mdev_device *mdev, char __user *buf, size_t count, loff_t *ppos)
static ssize_t intel_vgpu_write(struct mdev_device *mdev, const char __user *buf, size_t count, loff_t *ppos)
static int intel_vgpu_mmap(struct mdev_device *mdev, struct vm_area_struct *vma)
static int intel_vgpu_get_irq_count(struct intel_vgpu *vgpu, int type)
static int intel_vgpu_set_intx_mask(struct intel_vgpu *vgpu, unsigned int index, unsigned int start, unsigned int count, uint32_t flags, void *data)
static int intel_vgpu_set_intx_unmask(struct intel_vgpu *vgpu, unsigned int index, unsigned int start, unsigned int count, uint32_t flags, void *data)
static int intel_vgpu_set_intx_trigger(struct intel_vgpu *vgpu, unsigned int index, unsigned int start, unsigned int count, uint32_t flags, void *data)
static int intel_vgpu_set_msi_trigger(struct intel_vgpu *vgpu, unsigned int index, unsigned int start, unsigned int count, uint32_t flags, void *data)
static int intel_vgpu_set_irqs(struct intel_vgpu *vgpu, uint32_t flags, unsigned int index, unsigned int start, unsigned int count, void *data)
static long intel_vgpu_ioctl(struct mdev_device *mdev, unsigned int cmd, unsigned long arg)
static ssize_t vgpu_id_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t hw_id_show(struct device *dev, struct device_attribute *attr, char *buf)
static int kvmgt_host_init(struct device *dev, void *gvt, const void *ops)
static void kvmgt_host_exit(struct device *dev, void *gvt)
static int kvmgt_page_track_add(unsigned long handle, u64 gfn)
static int kvmgt_page_track_remove(unsigned long handle, u64 gfn)
static void kvmgt_page_track_write(struct kvm_vcpu *vcpu, gpa_t gpa, const u8 *val, int len, struct kvm_page_track_notifier_node *node)
static void kvmgt_page_track_flush_slot(struct kvm *kvm, struct kvm_memory_slot *slot, struct kvm_page_track_notifier_node *node)
static bool __kvmgt_vgpu_exist(struct intel_vgpu *vgpu, struct kvm *kvm)
static int kvmgt_guest_init(struct mdev_device *mdev)
static bool kvmgt_guest_exit(struct kvmgt_guest_info *info)
static int kvmgt_attach_vgpu(void *vgpu, unsigned long *handle)
static void kvmgt_detach_vgpu(void *p_vgpu)
static int kvmgt_inject_msi(unsigned long handle, u32 addr, u16 data)
static unsigned long kvmgt_gfn_to_pfn(unsigned long handle, unsigned long gfn)
static int kvmgt_dma_map_guest_page(unsigned long handle, unsigned long gfn, unsigned long size, dma_addr_t *dma_addr)
static void __gvt_dma_release(struct kref *ref)
static void kvmgt_dma_unmap_guest_page(unsigned long handle, dma_addr_t dma_addr)
static int kvmgt_rw_gpa(unsigned long handle, unsigned long gpa, void *buf, unsigned long len, bool write)
static int kvmgt_read_gpa(unsigned long handle, unsigned long gpa, void *buf, unsigned long len)
static int kvmgt_write_gpa(unsigned long handle, unsigned long gpa, void *buf, unsigned long len)
static unsigned long kvmgt_virt_to_pfn(void *addr)
static bool kvmgt_is_valid_gfn(unsigned long handle, unsigned long gfn)
static int __init kvmgt_init(void)
static void __exit kvmgt_exit(void)
\n
     26 struct intel_vgpu *vgpu
     11 unsigned long handle
     11 struct mdev_device *mdev
      8 void *data
      7 unsigned long gfn
      7 struct kvmgt_guest_info *info
      6 unsigned long size
      6 unsigned int count
      6 gfn_t gfn
      5 void *buf
      5 unsigned int start
      5 unsigned int index
      5 uint32_t flags
      5 loff_t *ppos
      4 struct device *dev
      4 size_t count
      4 dma_addr_t dma_addr
      4 char *buf
      3 void *p_vgpu
      3 unsigned long len
      3 unsigned long gpa
      3 uint64_t off
      3 bool is_write
      2 void *vgpu
      2 void *gvt
      2 void
      2 unsigned long action
      2 u64 gfn
      2 struct notifier_block *nb
      2 struct kvm_page_track_notifier_node *node
      2 struct kvm *kvm
      2 struct device_attribute *attr
      2 int bar
      2 dma_addr_t *dma_addr
      1 void *addr
      1 unsigned long *handle
      1 unsigned long count
      1 unsigned long arg
      1 unsigned int type
      1 unsigned int subtype
      1 unsigned int cmd
      1 u32 flags
      1 u32 addr
      1 u16 data
      1 struct work_struct *work
      1 struct vm_area_struct *vma
      1 struct vfio_region *region
      1 struct page **page
      1 struct kvm_vcpu *vcpu
      1 struct kvm_memory_slot *slot
      1 struct kref *ref
      1 struct kobject *kobj
      1 struct gvt_dma *entry
      1 size_t size
      1 kvmgt_mpt
      1 int type
      1 int len
      1 gpa_t gpa
      1 const void *ops
      1 const u8 *val
      1 const struct intel_vgpu_regops *ops
      1 const char __user *buf
      1 char __user *buf
      1 bool write
      1 bool iswrite
