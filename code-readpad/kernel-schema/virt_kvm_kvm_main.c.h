
EXPORT_SYMBOL_GPL(halt_poll_ns);
EXPORT_SYMBOL_GPL(halt_poll_ns_grow);
EXPORT_SYMBOL_GPL(halt_poll_ns_shrink);
EXPORT_SYMBOL_GPL(kvm_vcpu_cache);
EXPORT_SYMBOL_GPL(kvm_debugfs_dir);
EXPORT_SYMBOL_GPL(kvm_rebooting);
EXPORT_SYMBOL_GPL(vcpu_load);
EXPORT_SYMBOL_GPL(vcpu_put);
EXPORT_SYMBOL_GPL(kvm_flush_remote_tlbs);
EXPORT_SYMBOL_GPL(kvm_vcpu_init);
EXPORT_SYMBOL_GPL(kvm_vcpu_uninit);
EXPORT_SYMBOL_GPL(kvm_get_kvm);
EXPORT_SYMBOL_GPL(kvm_put_kvm);
EXPORT_SYMBOL_GPL(__kvm_set_memory_region);
EXPORT_SYMBOL_GPL(kvm_set_memory_region);
EXPORT_SYMBOL_GPL(kvm_get_dirty_log);
EXPORT_SYMBOL_GPL(kvm_get_dirty_log_protect);
EXPORT_SYMBOL_GPL(kvm_disable_largepages);
EXPORT_SYMBOL_GPL(gfn_to_memslot);
EXPORT_SYMBOL_GPL(kvm_is_visible_gfn);
EXPORT_SYMBOL_GPL(gfn_to_hva_memslot);
EXPORT_SYMBOL_GPL(gfn_to_hva);
EXPORT_SYMBOL_GPL(kvm_vcpu_gfn_to_hva);
EXPORT_SYMBOL_GPL(__gfn_to_pfn_memslot);
EXPORT_SYMBOL_GPL(gfn_to_pfn_prot);
EXPORT_SYMBOL_GPL(gfn_to_pfn_memslot);
EXPORT_SYMBOL_GPL(gfn_to_pfn_memslot_atomic);
EXPORT_SYMBOL_GPL(gfn_to_pfn_atomic);
EXPORT_SYMBOL_GPL(kvm_vcpu_gfn_to_pfn_atomic);
EXPORT_SYMBOL_GPL(gfn_to_pfn);
EXPORT_SYMBOL_GPL(kvm_vcpu_gfn_to_pfn);
EXPORT_SYMBOL_GPL(gfn_to_page_many_atomic);
EXPORT_SYMBOL_GPL(gfn_to_page);
EXPORT_SYMBOL_GPL(kvm_vcpu_gfn_to_page);
EXPORT_SYMBOL_GPL(kvm_release_page_clean);
EXPORT_SYMBOL_GPL(kvm_release_pfn_clean);
EXPORT_SYMBOL_GPL(kvm_release_page_dirty);
EXPORT_SYMBOL_GPL(kvm_release_pfn_dirty);
EXPORT_SYMBOL_GPL(kvm_set_pfn_dirty);
EXPORT_SYMBOL_GPL(kvm_set_pfn_accessed);
EXPORT_SYMBOL_GPL(kvm_get_pfn);
EXPORT_SYMBOL_GPL(kvm_read_guest_page);
EXPORT_SYMBOL_GPL(kvm_vcpu_read_guest_page);
EXPORT_SYMBOL_GPL(kvm_read_guest);
EXPORT_SYMBOL_GPL(kvm_vcpu_read_guest);
EXPORT_SYMBOL_GPL(kvm_read_guest_atomic);
EXPORT_SYMBOL_GPL(kvm_vcpu_read_guest_atomic);
EXPORT_SYMBOL_GPL(kvm_write_guest_page);
EXPORT_SYMBOL_GPL(kvm_vcpu_write_guest_page);
EXPORT_SYMBOL_GPL(kvm_write_guest);
EXPORT_SYMBOL_GPL(kvm_vcpu_write_guest);
EXPORT_SYMBOL_GPL(kvm_gfn_to_hva_cache_init);
EXPORT_SYMBOL_GPL(kvm_write_guest_offset_cached);
EXPORT_SYMBOL_GPL(kvm_write_guest_cached);
EXPORT_SYMBOL_GPL(kvm_read_guest_cached);
EXPORT_SYMBOL_GPL(kvm_clear_guest_page);
EXPORT_SYMBOL_GPL(kvm_clear_guest);
EXPORT_SYMBOL_GPL(mark_page_dirty);
EXPORT_SYMBOL_GPL(kvm_vcpu_mark_page_dirty);
EXPORT_SYMBOL_GPL(kvm_vcpu_block);
EXPORT_SYMBOL_GPL(kvm_vcpu_wake_up);
EXPORT_SYMBOL_GPL(kvm_vcpu_kick);
EXPORT_SYMBOL_GPL(kvm_vcpu_yield_to);
EXPORT_SYMBOL_GPL(kvm_vcpu_on_spin);
EXPORT_SYMBOL_GPL(kvm_io_bus_write);
EXPORT_SYMBOL_GPL(kvm_io_bus_get_dev);
EXPORT_SYMBOL_GPL(kvm_init);
EXPORT_SYMBOL_GPL(kvm_exit);
__weak int kvm_arch_mmu_notifier_invalidate_range(struct kvm *kvm, unsigned long start, unsigned long end, bool blockable)
bool kvm_is_reserved_pfn(kvm_pfn_t pfn)
void vcpu_load(struct kvm_vcpu *vcpu)
void vcpu_put(struct kvm_vcpu *vcpu)
static bool kvm_request_needs_ipi(struct kvm_vcpu *vcpu, unsigned req)
static void ack_flush(void *_completed)
static inline bool kvm_kick_many_cpus(const struct cpumask *cpus, bool wait)
bool kvm_make_vcpus_request_mask(struct kvm *kvm, unsigned int req, unsigned long *vcpu_bitmap, cpumask_var_t tmp)
bool kvm_make_all_cpus_request(struct kvm *kvm, unsigned int req)
void kvm_flush_remote_tlbs(struct kvm *kvm)
void kvm_reload_remote_mmus(struct kvm *kvm)
int kvm_vcpu_init(struct kvm_vcpu *vcpu, struct kvm *kvm, unsigned id)
void kvm_vcpu_uninit(struct kvm_vcpu *vcpu)
static inline struct kvm *mmu_notifier_to_kvm(struct mmu_notifier *mn)
static void kvm_mmu_notifier_change_pte(struct mmu_notifier *mn, struct mm_struct *mm, unsigned long address, pte_t pte)
static int kvm_mmu_notifier_invalidate_range_start(struct mmu_notifier *mn, struct mm_struct *mm, unsigned long start, unsigned long end, bool blockable)
static void kvm_mmu_notifier_invalidate_range_end(struct mmu_notifier *mn, struct mm_struct *mm, unsigned long start, unsigned long end)
static int kvm_mmu_notifier_clear_flush_young(struct mmu_notifier *mn, struct mm_struct *mm, unsigned long start, unsigned long end)
static int kvm_mmu_notifier_clear_young(struct mmu_notifier *mn, struct mm_struct *mm, unsigned long start, unsigned long end)
static int kvm_mmu_notifier_test_young(struct mmu_notifier *mn, struct mm_struct *mm, unsigned long address)
static void kvm_mmu_notifier_release(struct mmu_notifier *mn, struct mm_struct *mm)
static int kvm_init_mmu_notifier(struct kvm *kvm)
static int kvm_init_mmu_notifier(struct kvm *kvm)
static struct kvm_memslots *kvm_alloc_memslots(void)
static void kvm_destroy_dirty_bitmap(struct kvm_memory_slot *memslot)
static void kvm_free_memslot(struct kvm *kvm, struct kvm_memory_slot *free, struct kvm_memory_slot *dont)
static void kvm_free_memslots(struct kvm *kvm, struct kvm_memslots *slots)
static void kvm_destroy_vm_debugfs(struct kvm *kvm)
static int kvm_create_vm_debugfs(struct kvm *kvm, int fd)
static struct kvm *kvm_create_vm(unsigned long type)
static void kvm_destroy_devices(struct kvm *kvm)
static void kvm_destroy_vm(struct kvm *kvm)
void kvm_get_kvm(struct kvm *kvm)
void kvm_put_kvm(struct kvm *kvm)
static int kvm_vm_release(struct inode *inode, struct file *filp)
static int kvm_create_dirty_bitmap(struct kvm_memory_slot *memslot)
static void update_memslots(struct kvm_memslots *slots, struct kvm_memory_slot *new, enum kvm_mr_change change)
static int check_memory_region_flags(const struct kvm_userspace_memory_region *mem)
static struct kvm_memslots *install_new_memslots(struct kvm *kvm, int as_id, struct kvm_memslots *slots)
int __kvm_set_memory_region(struct kvm *kvm, const struct kvm_userspace_memory_region *mem)
int kvm_set_memory_region(struct kvm *kvm, const struct kvm_userspace_memory_region *mem)
static int kvm_vm_ioctl_set_memory_region(struct kvm *kvm, struct kvm_userspace_memory_region *mem)
int kvm_get_dirty_log(struct kvm *kvm, struct kvm_dirty_log *log, int *is_dirty)
int kvm_get_dirty_log_protect(struct kvm *kvm, struct kvm_dirty_log *log, bool *is_dirty)
bool kvm_largepages_enabled(void)
void kvm_disable_largepages(void)
struct kvm_memory_slot *gfn_to_memslot(struct kvm *kvm, gfn_t gfn)
struct kvm_memory_slot *kvm_vcpu_gfn_to_memslot(struct kvm_vcpu *vcpu, gfn_t gfn)
bool kvm_is_visible_gfn(struct kvm *kvm, gfn_t gfn)
unsigned long kvm_host_page_size(struct kvm *kvm, gfn_t gfn)
static bool memslot_is_readonly(struct kvm_memory_slot *slot)
static unsigned long __gfn_to_hva_many(struct kvm_memory_slot *slot, gfn_t gfn, gfn_t *nr_pages, bool write)
static unsigned long gfn_to_hva_many(struct kvm_memory_slot *slot, gfn_t gfn, gfn_t *nr_pages)
unsigned long gfn_to_hva_memslot(struct kvm_memory_slot *slot, gfn_t gfn)
unsigned long gfn_to_hva(struct kvm *kvm, gfn_t gfn)
unsigned long kvm_vcpu_gfn_to_hva(struct kvm_vcpu *vcpu, gfn_t gfn)
unsigned long gfn_to_hva_memslot_prot(struct kvm_memory_slot *slot, gfn_t gfn, bool *writable)
unsigned long gfn_to_hva_prot(struct kvm *kvm, gfn_t gfn, bool *writable)
unsigned long kvm_vcpu_gfn_to_hva_prot(struct kvm_vcpu *vcpu, gfn_t gfn, bool *writable)
static inline int check_user_page_hwpoison(unsigned long addr)
static bool hva_to_pfn_fast(unsigned long addr, bool write_fault, bool *writable, kvm_pfn_t *pfn)
static int hva_to_pfn_slow(unsigned long addr, bool *async, bool write_fault, bool *writable, kvm_pfn_t *pfn)
static bool vma_is_valid(struct vm_area_struct *vma, bool write_fault)
static int hva_to_pfn_remapped(struct vm_area_struct *vma, unsigned long addr, bool *async, bool write_fault, bool *writable, kvm_pfn_t *p_pfn)
static kvm_pfn_t hva_to_pfn(unsigned long addr, bool atomic, bool *async, bool write_fault, bool *writable)
kvm_pfn_t __gfn_to_pfn_memslot(struct kvm_memory_slot *slot, gfn_t gfn, bool atomic, bool *async, bool write_fault, bool *writable)
kvm_pfn_t gfn_to_pfn_prot(struct kvm *kvm, gfn_t gfn, bool write_fault, bool *writable)
kvm_pfn_t gfn_to_pfn_memslot(struct kvm_memory_slot *slot, gfn_t gfn)
kvm_pfn_t gfn_to_pfn_memslot_atomic(struct kvm_memory_slot *slot, gfn_t gfn)
kvm_pfn_t gfn_to_pfn_atomic(struct kvm *kvm, gfn_t gfn)
kvm_pfn_t kvm_vcpu_gfn_to_pfn_atomic(struct kvm_vcpu *vcpu, gfn_t gfn)
kvm_pfn_t gfn_to_pfn(struct kvm *kvm, gfn_t gfn)
kvm_pfn_t kvm_vcpu_gfn_to_pfn(struct kvm_vcpu *vcpu, gfn_t gfn)
int gfn_to_page_many_atomic(struct kvm_memory_slot *slot, gfn_t gfn, struct page **pages, int nr_pages)
static struct page *kvm_pfn_to_page(kvm_pfn_t pfn)
struct page *gfn_to_page(struct kvm *kvm, gfn_t gfn)
struct page *kvm_vcpu_gfn_to_page(struct kvm_vcpu *vcpu, gfn_t gfn)
void kvm_release_page_clean(struct page *page)
void kvm_release_pfn_clean(kvm_pfn_t pfn)
void kvm_release_page_dirty(struct page *page)
void kvm_release_pfn_dirty(kvm_pfn_t pfn)
void kvm_set_pfn_dirty(kvm_pfn_t pfn)
void kvm_set_pfn_accessed(kvm_pfn_t pfn)
void kvm_get_pfn(kvm_pfn_t pfn)
static int next_segment(unsigned long len, int offset)
static int __kvm_read_guest_page(struct kvm_memory_slot *slot, gfn_t gfn, void *data, int offset, int len)
int kvm_read_guest_page(struct kvm *kvm, gfn_t gfn, void *data, int offset, int len)
int kvm_vcpu_read_guest_page(struct kvm_vcpu *vcpu, gfn_t gfn, void *data, int offset, int len)
int kvm_read_guest(struct kvm *kvm, gpa_t gpa, void *data, unsigned long len)
int kvm_vcpu_read_guest(struct kvm_vcpu *vcpu, gpa_t gpa, void *data, unsigned long len)
static int __kvm_read_guest_atomic(struct kvm_memory_slot *slot, gfn_t gfn, void *data, int offset, unsigned long len)
int kvm_read_guest_atomic(struct kvm *kvm, gpa_t gpa, void *data, unsigned long len)
int kvm_vcpu_read_guest_atomic(struct kvm_vcpu *vcpu, gpa_t gpa, void *data, unsigned long len)
static int __kvm_write_guest_page(struct kvm_memory_slot *memslot, gfn_t gfn, const void *data, int offset, int len)
int kvm_write_guest_page(struct kvm *kvm, gfn_t gfn, const void *data, int offset, int len)
int kvm_vcpu_write_guest_page(struct kvm_vcpu *vcpu, gfn_t gfn, const void *data, int offset, int len)
int kvm_write_guest(struct kvm *kvm, gpa_t gpa, const void *data, unsigned long len)
int kvm_vcpu_write_guest(struct kvm_vcpu *vcpu, gpa_t gpa, const void *data, unsigned long len)
static int __kvm_gfn_to_hva_cache_init(struct kvm_memslots *slots, struct gfn_to_hva_cache *ghc, gpa_t gpa, unsigned long len)
int kvm_gfn_to_hva_cache_init(struct kvm *kvm, struct gfn_to_hva_cache *ghc, gpa_t gpa, unsigned long len)
int kvm_write_guest_offset_cached(struct kvm *kvm, struct gfn_to_hva_cache *ghc, void *data, int offset, unsigned long len)
int kvm_write_guest_cached(struct kvm *kvm, struct gfn_to_hva_cache *ghc, void *data, unsigned long len)
int kvm_read_guest_cached(struct kvm *kvm, struct gfn_to_hva_cache *ghc, void *data, unsigned long len)
int kvm_clear_guest_page(struct kvm *kvm, gfn_t gfn, int offset, int len)
int kvm_clear_guest(struct kvm *kvm, gpa_t gpa, unsigned long len)
static void mark_page_dirty_in_slot(struct kvm_memory_slot *memslot, gfn_t gfn)
void mark_page_dirty(struct kvm *kvm, gfn_t gfn)
void kvm_vcpu_mark_page_dirty(struct kvm_vcpu *vcpu, gfn_t gfn)
void kvm_sigset_activate(struct kvm_vcpu *vcpu)
void kvm_sigset_deactivate(struct kvm_vcpu *vcpu)
static void grow_halt_poll_ns(struct kvm_vcpu *vcpu)
static void shrink_halt_poll_ns(struct kvm_vcpu *vcpu)
static int kvm_vcpu_check_block(struct kvm_vcpu *vcpu)
void kvm_vcpu_block(struct kvm_vcpu *vcpu)
bool kvm_vcpu_wake_up(struct kvm_vcpu *vcpu)
void kvm_vcpu_kick(struct kvm_vcpu *vcpu)
int kvm_vcpu_yield_to(struct kvm_vcpu *target)
static bool kvm_vcpu_eligible_for_directed_yield(struct kvm_vcpu *vcpu)
void kvm_vcpu_on_spin(struct kvm_vcpu *me, bool yield_to_kernel_mode)
static vm_fault_t kvm_vcpu_fault(struct vm_fault *vmf)
static int kvm_vcpu_mmap(struct file *file, struct vm_area_struct *vma)
static int kvm_vcpu_release(struct inode *inode, struct file *filp)
static int create_vcpu_fd(struct kvm_vcpu *vcpu)
static int kvm_create_vcpu_debugfs(struct kvm_vcpu *vcpu)
static int kvm_vm_ioctl_create_vcpu(struct kvm *kvm, u32 id)
static int kvm_vcpu_ioctl_set_sigmask(struct kvm_vcpu *vcpu, sigset_t *sigset)
static long kvm_vcpu_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
static long kvm_vcpu_compat_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
static int kvm_device_ioctl_attr(struct kvm_device *dev, int (*accessor)
(struct kvm_device *dev, struct kvm_device_attr *attr)
, unsigned long arg)
static long kvm_device_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
static int kvm_device_release(struct inode *inode, struct file *filp)
struct kvm_device *kvm_device_from_filp(struct file *filp)
int kvm_register_device_ops(struct kvm_device_ops *ops, u32 type)
void kvm_unregister_device_ops(u32 type)
static int kvm_ioctl_create_device(struct kvm *kvm, struct kvm_create_device *cd)
static long kvm_vm_ioctl_check_extension_generic(struct kvm *kvm, long arg)
static long kvm_vm_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
static long kvm_vm_compat_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
static int kvm_dev_ioctl_create_vm(unsigned long type)
static long kvm_dev_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
static void hardware_enable_nolock(void *junk)
static int kvm_starting_cpu(unsigned int cpu)
static void hardware_disable_nolock(void *junk)
static int kvm_dying_cpu(unsigned int cpu)
static void hardware_disable_all_nolock(void)
static void hardware_disable_all(void)
static int hardware_enable_all(void)
static int kvm_reboot(struct notifier_block *notifier, unsigned long val, void *v)
static void kvm_io_bus_destroy(struct kvm_io_bus *bus)
static inline int kvm_io_bus_cmp(const struct kvm_io_range *r1, const struct kvm_io_range *r2)
static int kvm_io_bus_sort_cmp(const void *p1, const void *p2)
static int kvm_io_bus_get_first_dev(struct kvm_io_bus *bus, gpa_t addr, int len)
static int __kvm_io_bus_write(struct kvm_vcpu *vcpu, struct kvm_io_bus *bus, struct kvm_io_range *range, const void *val)
int kvm_io_bus_write(struct kvm_vcpu *vcpu, enum kvm_bus bus_idx, gpa_t addr, int len, const void *val)
int kvm_io_bus_write_cookie(struct kvm_vcpu *vcpu, enum kvm_bus bus_idx, gpa_t addr, int len, const void *val, long cookie)
static int __kvm_io_bus_read(struct kvm_vcpu *vcpu, struct kvm_io_bus *bus, struct kvm_io_range *range, void *val)
int kvm_io_bus_read(struct kvm_vcpu *vcpu, enum kvm_bus bus_idx, gpa_t addr, int len, void *val)
int kvm_io_bus_register_dev(struct kvm *kvm, enum kvm_bus bus_idx, gpa_t addr, int len, struct kvm_io_device *dev)
void kvm_io_bus_unregister_dev(struct kvm *kvm, enum kvm_bus bus_idx, struct kvm_io_device *dev)
struct kvm_io_device *kvm_io_bus_get_dev(struct kvm *kvm, enum kvm_bus bus_idx, gpa_t addr)
static int kvm_debugfs_open(struct inode *inode, struct file *file, int (*get)
(void *, u64 *)
, int (*set)
(void *, u64)
, const char *fmt)
static int kvm_debugfs_release(struct inode *inode, struct file *file)
static int vm_stat_get_per_vm(void *data, u64 *val)
static int vm_stat_clear_per_vm(void *data, u64 val)
static int vm_stat_get_per_vm_open(struct inode *inode, struct file *file)
static int vcpu_stat_get_per_vm(void *data, u64 *val)
static int vcpu_stat_clear_per_vm(void *data, u64 val)
static int vcpu_stat_get_per_vm_open(struct inode *inode, struct file *file)
static int vm_stat_get(void *_offset, u64 *val)
static int vm_stat_clear(void *_offset, u64 val)
static int vcpu_stat_get(void *_offset, u64 *val)
static int vcpu_stat_clear(void *_offset, u64 val)
static void kvm_uevent_notify_change(unsigned int type, struct kvm *kvm)
static void kvm_init_debug(void)
static int kvm_suspend(void)
static void kvm_resume(void)
static inline struct kvm_vcpu *preempt_notifier_to_vcpu(struct preempt_notifier *pn)
static void kvm_sched_in(struct preempt_notifier *pn, int cpu)
static void kvm_sched_out(struct preempt_notifier *pn, struct task_struct *next)
int kvm_init(void *opaque, unsigned vcpu_size, unsigned vcpu_align, struct module *module)
void kvm_exit(void)
  50 struct kvm *kvm
  34 struct kvm_vcpu *vcpu
  34 gfn_t gfn
  15 void *data
  14 unsigned long len
  12 int len
  11 struct kvm_memory_slot *slot
  10 void
  10 struct file *filp
  10 int offset
   9 gpa_t gpa
   9 bool *writable
   8 struct mmu_notifier *mn
   7 struct mm_struct *mm
   7 struct inode *inode
   7 kvm_pfn_t pfn
   7 bool write_fault
   6 unsigned long arg
   6 unsigned int ioctl
   6 gpa_t addr
   6 enum kvm_bus bus_idx
   5 unsigned long start
   5 unsigned long end
   5 unsigned long addr
   5 struct gfn_to_hva_cache *ghc
   5 struct file *file
   5 const void *data
   4 void *_offset
   4 u64 val
   4 u64 *val
   4 struct kvm_memslots *slots
   4 struct kvm_memory_slot *memslot
   4 struct kvm_io_bus *bus
   4 bool *async
   3 struct vm_area_struct *vma
   3 struct preempt_notifier *pn
   3 const void *val
   3 const struct kvm_userspace_memory_region *mem
   2 void *val
   2 void *junk
   2 void *
   2 unsigned long type
   2 unsigned long address
   2 unsigned int req
   2 unsigned int cpu
   2 u32 type
   2 struct page *page
   2 struct kvm_io_range *range
   2 struct kvm_io_device *dev
   2 struct kvm_dirty_log *log
   2 struct kvm_device *dev
   2 kvm_pfn_t *pfn
   2 gfn_t *nr_pages
   2 bool blockable
   2 bool atomic
   1 void *v
   1 void *opaque
   1 void *_completed
   1 vcpu_put
   1 vcpu_load
   1 unsigned vcpu_size
   1 unsigned vcpu_align
   1 unsigned req
   1 unsigned long val
   1 unsigned long *vcpu_bitmap
   1 unsigned int type
   1 unsigned id
   1 u64 *
   1 u64
   1 u32 id
   1 struct vm_fault *vmf
   1 struct task_struct *next
   1 struct page **pages
   1 struct notifier_block *notifier
   1 struct module *module
   1 struct kvm_vcpu *target
   1 struct kvm_vcpu *me
   1 struct kvm_userspace_memory_region *mem
   1 struct kvm_memory_slot *new
   1 struct kvm_memory_slot *free
   1 struct kvm_memory_slot *dont
   1 struct kvm_device_ops *ops
   1 struct kvm_device_attr *attr
   1 struct kvm_create_device *cd
   1 sigset_t *sigset
   1 pte_t pte
   1 mark_page_dirty
   1 long cookie
   1 long arg
   1 kvm_write_guest_page
   1 kvm_write_guest_offset_cached
   1 kvm_write_guest_cached
   1 kvm_write_guest
   1 kvm_vcpu_yield_to
   1 kvm_vcpu_write_guest_page
   1 kvm_vcpu_write_guest
   1 kvm_vcpu_wake_up
   1 kvm_vcpu_uninit
   1 kvm_vcpu_read_guest_page
   1 kvm_vcpu_read_guest_atomic
   1 kvm_vcpu_read_guest
   1 kvm_vcpu_on_spin
   1 kvm_vcpu_mark_page_dirty
   1 kvm_vcpu_kick
   1 kvm_vcpu_init
   1 kvm_vcpu_gfn_to_pfn_atomic
   1 kvm_vcpu_gfn_to_pfn
   1 kvm_vcpu_gfn_to_page
   1 kvm_vcpu_gfn_to_hva
   1 kvm_vcpu_cache
   1 kvm_vcpu_block
   1 kvm_set_pfn_dirty
   1 kvm_set_pfn_accessed
   1 kvm_set_memory_region
   1 kvm_release_pfn_dirty
   1 kvm_release_pfn_clean
   1 kvm_release_page_dirty
   1 kvm_release_page_clean
   1 kvm_rebooting
   1 kvm_read_guest_page
   1 kvm_read_guest_cached
   1 kvm_read_guest_atomic
   1 kvm_read_guest
   1 kvm_put_kvm
   1 kvm_pfn_t *p_pfn
   1 kvm_is_visible_gfn
   1 kvm_io_bus_write
   1 kvm_io_bus_get_dev
   1 kvm_init
   1 kvm_gfn_to_hva_cache_init
   1 kvm_get_pfn
   1 kvm_get_kvm
   1 kvm_get_dirty_log_protect
   1 kvm_get_dirty_log
   1 kvm_flush_remote_tlbs
   1 kvm_exit
   1 kvm_disable_largepages
   1 kvm_debugfs_dir
   1 kvm_clear_guest_page
   1 kvm_clear_guest
   1 int nr_pages
   1 int fd
   1 int cpu
   1 int as_id
   1 int *is_dirty
   1 int *get
   1 int *accessor
   1 halt_poll_ns_shrink
   1 halt_poll_ns_grow
   1 halt_poll_ns
   1 gfn_to_pfn_prot
   1 gfn_to_pfn_memslot_atomic
   1 gfn_to_pfn_memslot
   1 gfn_to_pfn_atomic
   1 gfn_to_pfn
   1 gfn_to_page_many_atomic
   1 gfn_to_page
   1 gfn_to_memslot
   1 gfn_to_hva_memslot
   1 gfn_to_hva
   1 enum kvm_mr_change change
   1 cpumask_var_t tmp
   1 const void *p2
   1 const void *p1
   1 const struct kvm_io_range *r2
   1 const struct kvm_io_range *r1
   1 const struct cpumask *cpus
   1 bool yield_to_kernel_mode
   1 bool write
   1 bool wait
   1 bool *is_dirty
   1 __kvm_set_memory_region
   1 __gfn_to_pfn_memslot
   1 *set
