
EXPORT_SYMBOL_GPL(kvmppc_add_revmap_chain);
EXPORT_SYMBOL_GPL(kvmppc_update_dirty_map);
EXPORT_SYMBOL_GPL(kvmppc_do_h_enter);
EXPORT_SYMBOL_GPL(kvmppc_do_h_remove);
EXPORT_SYMBOL_GPL(kvmppc_invalidate_hpte);
EXPORT_SYMBOL_GPL(kvmppc_clear_ref_hpte);
\n
static void *real_vmalloc_addr(void *x)
static int global_invalidates(struct kvm *kvm)
void kvmppc_add_revmap_chain(struct kvm *kvm, struct revmap_entry *rev, unsigned long *rmap, long pte_index, int realmode)
void kvmppc_update_dirty_map(const struct kvm_memory_slot *memslot, unsigned long gfn, unsigned long psize)
static void kvmppc_set_dirty_from_hpte(struct kvm *kvm, unsigned long hpte_v, unsigned long hpte_gr)
static unsigned long *revmap_for_hpte(struct kvm *kvm, unsigned long hpte_v, unsigned long hpte_gr, struct kvm_memory_slot **memslotp, unsigned long *gfnp)
static void remove_revmap_chain(struct kvm *kvm, long pte_index, struct revmap_entry *rev, unsigned long hpte_v, unsigned long hpte_r)
long kvmppc_do_h_enter(struct kvm *kvm, unsigned long flags, long pte_index, unsigned long pteh, unsigned long ptel, pgd_t *pgdir, bool realmode, unsigned long *pte_idx_ret)
long kvmppc_h_enter(struct kvm_vcpu *vcpu, unsigned long flags, long pte_index, unsigned long pteh, unsigned long ptel)
static inline int is_mmio_hpte(unsigned long v, unsigned long r)
static void do_tlbies(struct kvm *kvm, unsigned long *rbvalues, long npages, int global, bool need_sync)
long kvmppc_do_h_remove(struct kvm *kvm, unsigned long flags, unsigned long pte_index, unsigned long avpn, unsigned long *hpret)
long kvmppc_h_remove(struct kvm_vcpu *vcpu, unsigned long flags, unsigned long pte_index, unsigned long avpn)
long kvmppc_h_bulk_remove(struct kvm_vcpu *vcpu)
long kvmppc_h_protect(struct kvm_vcpu *vcpu, unsigned long flags, unsigned long pte_index, unsigned long avpn, unsigned long va)
long kvmppc_h_read(struct kvm_vcpu *vcpu, unsigned long flags, unsigned long pte_index)
long kvmppc_h_clear_ref(struct kvm_vcpu *vcpu, unsigned long flags, unsigned long pte_index)
long kvmppc_h_clear_mod(struct kvm_vcpu *vcpu, unsigned long flags, unsigned long pte_index)
void kvmppc_invalidate_hpte(struct kvm *kvm, __be64 *hptep, unsigned long pte_index)
void kvmppc_clear_ref_hpte(struct kvm *kvm, __be64 *hptep, unsigned long pte_index)
static struct mmio_hpte_cache_entry *mmio_cache_search(struct kvm_vcpu *vcpu, unsigned long eaddr, unsigned long slb_v, long mmio_update)
static struct mmio_hpte_cache_entry *next_mmio_cache_entry(struct kvm_vcpu *vcpu)
long kvmppc_hv_find_lock_hpte(struct kvm *kvm, gva_t eaddr, unsigned long slb_v, unsigned long valid)
long kvmppc_hpte_hv_fault(struct kvm_vcpu *vcpu, unsigned long addr, unsigned long slb_v, unsigned int status, bool data)
\n
     11 struct kvm *kvm
     10 struct kvm_vcpu *vcpu
      8 unsigned long pte_index
      8 unsigned long flags
      4 long pte_index
      3 unsigned long slb_v
      3 unsigned long hpte_v
      3 unsigned long avpn
      2 unsigned long ptel
      2 unsigned long pteh
      2 unsigned long hpte_gr
      2 struct revmap_entry *rev
      2 __be64 *hptep
      1 void *x
      1 unsigned long valid
      1 unsigned long va
      1 unsigned long v
      1 unsigned long *rmap
      1 unsigned long *rbvalues
      1 unsigned long r
      1 unsigned long *pte_idx_ret
      1 unsigned long psize
      1 unsigned long hpte_r
      1 unsigned long *hpret
      1 unsigned long *gfnp
      1 unsigned long gfn
      1 unsigned long eaddr
      1 unsigned long addr
      1 unsigned int status
      1 struct kvm_memory_slot **memslotp
      1 pgd_t *pgdir
      1 long npages
      1 long mmio_update
      1 kvmppc_update_dirty_map
      1 kvmppc_invalidate_hpte
      1 kvmppc_do_h_remove
      1 kvmppc_do_h_enter
      1 kvmppc_clear_ref_hpte
      1 kvmppc_add_revmap_chain
      1 int realmode
      1 int global
      1 gva_t eaddr
      1 const struct kvm_memory_slot *memslot
      1 bool realmode
      1 bool need_sync
      1 bool data
