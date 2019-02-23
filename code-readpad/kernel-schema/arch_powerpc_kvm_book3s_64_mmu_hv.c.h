
\n
int kvmppc_allocate_hpt(struct kvm_hpt_info *info, u32 order)
void kvmppc_set_hpt(struct kvm *kvm, struct kvm_hpt_info *info)
long kvmppc_alloc_reset_hpt(struct kvm *kvm, int order)
void kvmppc_free_hpt(struct kvm_hpt_info *info)
static inline unsigned long hpte0_pgsize_encoding(unsigned long pgsize)
static inline unsigned long hpte1_pgsize_encoding(unsigned long pgsize)
void kvmppc_map_vrma(struct kvm_vcpu *vcpu, struct kvm_memory_slot *memslot, unsigned long porder)
int kvmppc_mmu_hv_init(void)
static void kvmppc_mmu_book3s_64_hv_reset_msr(struct kvm_vcpu *vcpu)
static long kvmppc_virtmode_do_h_enter(struct kvm *kvm, unsigned long flags, long pte_index, unsigned long pteh, unsigned long ptel, unsigned long *pte_idx_ret)
static struct kvmppc_slb *kvmppc_mmu_book3s_hv_find_slbe(struct kvm_vcpu *vcpu, gva_t eaddr)
static unsigned long kvmppc_mmu_get_real_addr(unsigned long v, unsigned long r, unsigned long ea)
static int kvmppc_mmu_book3s_64_hv_xlate(struct kvm_vcpu *vcpu, gva_t eaddr, struct kvmppc_pte *gpte, bool data, bool iswrite)
static int instruction_is_store(unsigned int instr)
int kvmppc_hv_emulate_mmio(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned long gpa, gva_t ea, int is_store)
int kvmppc_book3s_hv_page_fault(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned long ea, unsigned long dsisr)
void kvmppc_rmap_reset(struct kvm *kvm)
static int kvm_handle_hva_range(struct kvm *kvm, unsigned long start, unsigned long end, hva_handler_fn handler)
static int kvm_handle_hva(struct kvm *kvm, unsigned long hva, hva_handler_fn handler)
static void kvmppc_unmap_hpte(struct kvm *kvm, unsigned long i, struct kvm_memory_slot *memslot, unsigned long *rmapp, unsigned long gfn)
static int kvm_unmap_rmapp(struct kvm *kvm, struct kvm_memory_slot *memslot, unsigned long gfn)
int kvm_unmap_hva_range_hv(struct kvm *kvm, unsigned long start, unsigned long end)
void kvmppc_core_flush_memslot_hv(struct kvm *kvm, struct kvm_memory_slot *memslot)
static int kvm_age_rmapp(struct kvm *kvm, struct kvm_memory_slot *memslot, unsigned long gfn)
int kvm_age_hva_hv(struct kvm *kvm, unsigned long start, unsigned long end)
static int kvm_test_age_rmapp(struct kvm *kvm, struct kvm_memory_slot *memslot, unsigned long gfn)
int kvm_test_age_hva_hv(struct kvm *kvm, unsigned long hva)
void kvm_set_spte_hva_hv(struct kvm *kvm, unsigned long hva, pte_t pte)
static int vcpus_running(struct kvm *kvm)
static int kvm_test_clear_dirty_npages(struct kvm *kvm, unsigned long *rmapp)
void kvmppc_harvest_vpa_dirty(struct kvmppc_vpa *vpa, struct kvm_memory_slot *memslot, unsigned long *map)
long kvmppc_hv_get_dirty_log_hpt(struct kvm *kvm, struct kvm_memory_slot *memslot, unsigned long *map)
void *kvmppc_pin_guest_page(struct kvm *kvm, unsigned long gpa, unsigned long *nb_ret)
void kvmppc_unpin_guest_page(struct kvm *kvm, void *va, unsigned long gpa, bool dirty)
static int resize_hpt_allocate(struct kvm_resize_hpt *resize)
static unsigned long resize_hpt_rehash_hpte(struct kvm_resize_hpt *resize, unsigned long idx)
static int resize_hpt_rehash(struct kvm_resize_hpt *resize)
static void resize_hpt_pivot(struct kvm_resize_hpt *resize)
static void resize_hpt_release(struct kvm *kvm, struct kvm_resize_hpt *resize)
static void resize_hpt_prepare_work(struct work_struct *work)
long kvm_vm_ioctl_resize_hpt_prepare(struct kvm *kvm, struct kvm_ppc_resize_hpt *rhpt)
static void resize_hpt_boot_vcpu(void *opaque)
long kvm_vm_ioctl_resize_hpt_commit(struct kvm *kvm, struct kvm_ppc_resize_hpt *rhpt)
static int hpte_dirty(struct revmap_entry *revp, __be64 *hptp)
static long record_hpte(unsigned long flags, __be64 *hptp, unsigned long *hpte, struct revmap_entry *revp, int want_valid, int first_pass)
static ssize_t kvm_htab_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static ssize_t kvm_htab_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static int kvm_htab_release(struct inode *inode, struct file *filp)
int kvm_vm_ioctl_get_htab_fd(struct kvm *kvm, struct kvm_get_htab_fd *ghf)
static int debugfs_htab_open(struct inode *inode, struct file *file)
static int debugfs_htab_release(struct inode *inode, struct file *file)
static ssize_t debugfs_htab_read(struct file *file, char __user *buf, size_t len, loff_t *ppos)
static ssize_t debugfs_htab_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
void kvmppc_mmu_debugfs_init(struct kvm *kvm)
void kvmppc_mmu_book3s_hv_init(struct kvm_vcpu *vcpu)
\n
     25 struct kvm *kvm
      8 struct kvm_memory_slot *memslot
      7 struct kvm_vcpu *vcpu
      6 struct file *file
      5 struct kvm_resize_hpt *resize
      4 unsigned long gfn
      4 loff_t *ppos
      3 unsigned long start
      3 unsigned long hva
      3 unsigned long gpa
      3 unsigned long end
      3 struct kvm_hpt_info *info
      3 struct inode *inode
      2 unsigned long *rmapp
      2 unsigned long pgsize
      2 unsigned long *map
      2 unsigned long flags
      2 unsigned long ea
      2 struct revmap_entry *revp
      2 struct kvm_run *run
      2 struct kvm_ppc_resize_hpt *rhpt
      2 size_t len
      2 size_t count
      2 hva_handler_fn handler
      2 gva_t eaddr
      2 const char __user *buf
      2 char __user *buf
      2 __be64 *hptp
      1 void *va
      1 void *opaque
      1 void
      1 unsigned long v
      1 unsigned long r
      1 unsigned long ptel
      1 unsigned long *pte_idx_ret
      1 unsigned long pteh
      1 unsigned long porder
      1 unsigned long *nb_ret
      1 unsigned long idx
      1 unsigned long i
      1 unsigned long *hpte
      1 unsigned long dsisr
      1 unsigned int instr
      1 u32 order
      1 struct work_struct *work
      1 struct kvmppc_vpa *vpa
      1 struct kvmppc_pte *gpte
      1 struct kvm_get_htab_fd *ghf
      1 struct file *filp
      1 pte_t pte
      1 long pte_index
      1 int want_valid
      1 int order
      1 int is_store
      1 int first_pass
      1 gva_t ea
      1 bool iswrite
      1 bool dirty
      1 bool data
