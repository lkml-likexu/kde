
EXPORT_SYMBOL_GPL(kvmppc_h_put_tce);
EXPORT_SYMBOL_GPL(kvmppc_h_put_tce_indirect);
EXPORT_SYMBOL_GPL(kvmppc_h_stuff_tce);
\n
static unsigned long kvmppc_tce_pages(unsigned long iommu_pages)
static unsigned long kvmppc_stt_pages(unsigned long tce_pages)
static long kvmppc_account_memlimit(unsigned long stt_pages, bool inc)
static void kvm_spapr_tce_iommu_table_free(struct rcu_head *head)
static void kvm_spapr_tce_liobn_put(struct kref *kref)
extern void kvm_spapr_tce_release_iommu_group(struct kvm *kvm, struct iommu_group *grp)
extern long kvm_spapr_tce_attach_iommu_group(struct kvm *kvm, int tablefd, struct iommu_group *grp)
static void release_spapr_tce_table(struct rcu_head *head)
static vm_fault_t kvm_spapr_tce_fault(struct vm_fault *vmf)
static int kvm_spapr_tce_mmap(struct file *file, struct vm_area_struct *vma)
static int kvm_spapr_tce_release(struct inode *inode, struct file *filp)
long kvm_vm_ioctl_create_spapr_tce(struct kvm *kvm, struct kvm_create_spapr_tce_64 *args)
static long kvmppc_tce_validate(struct kvmppc_spapr_tce_table *stt, unsigned long tce)
static void kvmppc_clear_tce(struct mm_struct *mm, struct iommu_table *tbl, unsigned long entry)
static long kvmppc_tce_iommu_mapped_dec(struct kvm *kvm, struct iommu_table *tbl, unsigned long entry)
static long kvmppc_tce_iommu_do_unmap(struct kvm *kvm, struct iommu_table *tbl, unsigned long entry)
static long kvmppc_tce_iommu_unmap(struct kvm *kvm, struct kvmppc_spapr_tce_table *stt, struct iommu_table *tbl, unsigned long entry)
long kvmppc_tce_iommu_do_map(struct kvm *kvm, struct iommu_table *tbl, unsigned long entry, unsigned long ua, enum dma_data_direction dir)
static long kvmppc_tce_iommu_map(struct kvm *kvm, struct kvmppc_spapr_tce_table *stt, struct iommu_table *tbl, unsigned long entry, unsigned long ua, enum dma_data_direction dir)
long kvmppc_h_put_tce(struct kvm_vcpu *vcpu, unsigned long liobn, unsigned long ioba, unsigned long tce)
long kvmppc_h_put_tce_indirect(struct kvm_vcpu *vcpu, unsigned long liobn, unsigned long ioba, unsigned long tce_list, unsigned long npages)
long kvmppc_h_stuff_tce(struct kvm_vcpu *vcpu, unsigned long liobn, unsigned long ioba, unsigned long tce_value, unsigned long npages)
\n
      8 struct kvm *kvm
      6 unsigned long entry
      6 struct iommu_table *tbl
      3 unsigned long liobn
      3 unsigned long ioba
      3 struct kvm_vcpu *vcpu
      3 struct kvmppc_spapr_tce_table *stt
      2 unsigned long ua
      2 unsigned long tce
      2 unsigned long npages
      2 struct rcu_head *head
      2 struct iommu_group *grp
      2 enum dma_data_direction dir
      1 unsigned long tce_value
      1 unsigned long tce_pages
      1 unsigned long tce_list
      1 unsigned long stt_pages
      1 unsigned long iommu_pages
      1 struct vm_fault *vmf
      1 struct vm_area_struct *vma
      1 struct mm_struct *mm
      1 struct kvm_create_spapr_tce_64 *args
      1 struct kref *kref
      1 struct inode *inode
      1 struct file *filp
      1 struct file *file
      1 kvmppc_h_stuff_tce
      1 kvmppc_h_put_tce_indirect
      1 kvmppc_h_put_tce
      1 int tablefd
      1 bool inc
