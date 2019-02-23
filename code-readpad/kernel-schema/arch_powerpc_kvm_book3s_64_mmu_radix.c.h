
EXPORT_SYMBOL_GPL(__kvmhv_copy_tofrom_guest_radix);
EXPORT_SYMBOL_GPL(kvmhv_copy_from_guest_radix);
EXPORT_SYMBOL_GPL(kvmhv_copy_to_guest_radix);
\n
unsigned long __kvmhv_copy_tofrom_guest_radix(int lpid, int pid, gva_t eaddr, void *to, void *from, unsigned long n)
static long kvmhv_copy_tofrom_guest_radix(struct kvm_vcpu *vcpu, gva_t eaddr, void *to, void *from, unsigned long n)
long kvmhv_copy_from_guest_radix(struct kvm_vcpu *vcpu, gva_t eaddr, void *to, unsigned long n)
long kvmhv_copy_to_guest_radix(struct kvm_vcpu *vcpu, gva_t eaddr, void *from, unsigned long n)
int kvmppc_mmu_walk_radix_tree(struct kvm_vcpu *vcpu, gva_t eaddr, struct kvmppc_pte *gpte, u64 root, u64 *pte_ret_p)
int kvmppc_mmu_radix_translate_table(struct kvm_vcpu *vcpu, gva_t eaddr, struct kvmppc_pte *gpte, u64 table, int table_index, u64 *pte_ret_p)
int kvmppc_mmu_radix_xlate(struct kvm_vcpu *vcpu, gva_t eaddr, struct kvmppc_pte *gpte, bool data, bool iswrite)
void kvmppc_radix_tlbie_page(struct kvm *kvm, unsigned long addr, unsigned int pshift, unsigned int lpid)
static void kvmppc_radix_flush_pwc(struct kvm *kvm, unsigned int lpid)
static unsigned long kvmppc_radix_update_pte(struct kvm *kvm, pte_t *ptep, unsigned long clr, unsigned long set, unsigned long addr, unsigned int shift)
void kvmppc_radix_set_pte_at(struct kvm *kvm, unsigned long addr, pte_t *ptep, pte_t pte)
static pte_t *kvmppc_pte_alloc(void)
static void kvmppc_pte_free(pte_t *ptep)
static inline int pmd_is_leaf(pmd_t pmd)
static pmd_t *kvmppc_pmd_alloc(void)
static void kvmppc_pmd_free(pmd_t *pmdp)
static void kvmppc_unmap_free_pte(struct kvm *kvm, pte_t *pte, bool full, unsigned int lpid)
static void kvmppc_unmap_free_pmd(struct kvm *kvm, pmd_t *pmd, bool full, unsigned int lpid)
static void kvmppc_unmap_free_pud(struct kvm *kvm, pud_t *pud, unsigned int lpid)
void kvmppc_free_pgtable_radix(struct kvm *kvm, pgd_t *pgd, unsigned int lpid)
void kvmppc_free_radix(struct kvm *kvm)
static void kvmppc_unmap_free_pmd_entry_table(struct kvm *kvm, pmd_t *pmd, unsigned long gpa, unsigned int lpid)
static void kvmppc_unmap_free_pud_entry_table(struct kvm *kvm, pud_t *pud, unsigned long gpa, unsigned int lpid)
int kvmppc_create_pte(struct kvm *kvm, pgd_t *pgtable, pte_t pte, unsigned long gpa, unsigned int level, unsigned long mmu_seq, unsigned int lpid, unsigned long *rmapp, struct rmap_nested **n_rmap)
bool kvmppc_hv_handle_set_rc(struct kvm *kvm, pgd_t *pgtable, bool writing, unsigned long gpa, unsigned int lpid)
int kvmppc_book3s_instantiate_page(struct kvm_vcpu *vcpu, unsigned long gpa, struct kvm_memory_slot *memslot, bool writing, bool kvm_ro, pte_t *inserted_pte, unsigned int *levelp)
int kvmppc_book3s_radix_page_fault(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned long ea, unsigned long dsisr)
int kvm_unmap_radix(struct kvm *kvm, struct kvm_memory_slot *memslot, unsigned long gfn)
int kvm_age_radix(struct kvm *kvm, struct kvm_memory_slot *memslot, unsigned long gfn)
int kvm_test_age_radix(struct kvm *kvm, struct kvm_memory_slot *memslot, unsigned long gfn)
static int kvm_radix_test_clear_dirty(struct kvm *kvm, struct kvm_memory_slot *memslot, int pagenum)
long kvmppc_hv_get_dirty_log_radix(struct kvm *kvm, struct kvm_memory_slot *memslot, unsigned long *map)
void kvmppc_radix_flush_memslot(struct kvm *kvm, const struct kvm_memory_slot *memslot)
static void add_rmmu_ap_encoding(struct kvm_ppc_rmmu_info *info, int psize, int *indexp)
int kvmhv_get_rmmu_info(struct kvm *kvm, struct kvm_ppc_rmmu_info *info)
int kvmppc_init_vm_radix(struct kvm *kvm)
static void pte_ctor(void *addr)
static void pmd_ctor(void *addr)
static int debugfs_radix_open(struct inode *inode, struct file *file)
static int debugfs_radix_release(struct inode *inode, struct file *file)
static ssize_t debugfs_radix_read(struct file *file, char __user *buf, size_t len, loff_t *ppos)
static ssize_t debugfs_radix_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
void kvmhv_radix_debugfs_init(struct kvm *kvm)
int kvmppc_radix_init(void)
void kvmppc_radix_exit(void)
\n
     22 struct kvm *kvm
     10 unsigned int lpid
      8 struct kvm_vcpu *vcpu
      7 gva_t eaddr
      6 struct kvm_memory_slot *memslot
      5 unsigned long gpa
      4 void
      4 unsigned long n
      4 struct file *file
      3 void *to
      3 void *from
      3 unsigned long gfn
      3 unsigned long addr
      3 struct kvmppc_pte *gpte
      3 pte_t *ptep
      2 void *addr
      2 u64 *pte_ret_p
      2 struct kvm_ppc_rmmu_info *info
      2 struct inode *inode
      2 size_t len
      2 pud_t *pud
      2 pte_t pte
      2 pmd_t *pmd
      2 pgd_t *pgtable
      2 loff_t *ppos
      2 bool writing
      2 bool full
      1 unsigned long set
      1 unsigned long *rmapp
      1 unsigned long mmu_seq
      1 unsigned long *map
      1 unsigned long ea
      1 unsigned long dsisr
      1 unsigned long clr
      1 unsigned int shift
      1 unsigned int pshift
      1 unsigned int *levelp
      1 unsigned int level
      1 u64 table
      1 u64 root
      1 struct rmap_nested **n_rmap
      1 struct kvm_run *run
      1 pte_t *pte
      1 pte_t *inserted_pte
      1 pmd_t *pmdp
      1 pmd_t pmd
      1 pgd_t *pgd
      1 kvmhv_copy_to_guest_radix
      1 __kvmhv_copy_tofrom_guest_radix
      1 kvmhv_copy_from_guest_radix
      1 int table_index
      1 int psize
      1 int pid
      1 int pagenum
      1 int lpid
      1 int *indexp
      1 const struct kvm_memory_slot *memslot
      1 const char __user *buf
      1 char __user *buf
      1 bool kvm_ro
      1 bool iswrite
      1 bool data
