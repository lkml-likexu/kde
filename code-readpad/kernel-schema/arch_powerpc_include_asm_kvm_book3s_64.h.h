
\n
static inline bool kvmhv_on_pseries(void)
static inline bool kvmhv_on_pseries(void)
return !cpu_has_feature(CPU_FTR_HVMODE)
; } static inline bool kvmhv_on_pseries(void)
static inline struct kvmppc_book3s_shadow_vcpu *svcpu_get(struct kvm_vcpu *vcpu)
static inline void svcpu_put(struct kvmppc_book3s_shadow_vcpu *svcpu)
static inline bool kvm_is_radix(struct kvm *kvm)
static inline bool kvmhv_vcpu_is_radix(struct kvm_vcpu *vcpu)
static inline long try_lock_hpte(__be64 *hpte, unsigned long bits)
static inline void unlock_hpte(__be64 *hpte, unsigned long hpte_v)
static inline void __unlock_hpte(__be64 *hpte, unsigned long hpte_v)
static inline int kvmppc_hpte_page_shifts(unsigned long h, unsigned long l)
static inline int kvmppc_hpte_base_page_shift(unsigned long h, unsigned long l)
static inline int kvmppc_hpte_actual_page_shift(unsigned long h, unsigned long l)
static inline unsigned long kvmppc_actual_pgsz(unsigned long v, unsigned long r)
static inline int kvmppc_pgsize_lp_encoding(int base_shift, int actual_shift)
static inline unsigned long compute_tlbie_rb(unsigned long v, unsigned long r, unsigned long pte_index)
static inline unsigned long hpte_rpn(unsigned long ptel, unsigned long psize)
static inline int hpte_is_writable(unsigned long ptel)
static inline unsigned long hpte_make_readonly(unsigned long ptel)
static inline bool hpte_cache_flags_ok(unsigned long hptel, bool is_ci)
static inline pte_t kvmppc_read_update_linux_pte(pte_t *ptep, int writing)
static inline bool hpte_read_permission(unsigned long pp, unsigned long key)
static inline bool hpte_write_permission(unsigned long pp, unsigned long key)
static inline int hpte_get_skey_perm(unsigned long hpte_r, unsigned long amr)
static inline void lock_rmap(unsigned long *rmap)
static inline void unlock_rmap(unsigned long *rmap)
static inline bool slot_is_aligned(struct kvm_memory_slot *memslot, unsigned long pagesize)
static inline unsigned long slb_pgsize_encoding(unsigned long psize)
static inline int is_vrma_hpte(unsigned long hpte_v)
static inline void note_hpte_modification(struct kvm *kvm, struct revmap_entry *rev)
static inline struct kvm_memslots *kvm_memslots_raw(struct kvm *kvm)
static inline unsigned long kvmppc_hpt_npte(struct kvm_hpt_info *hpt)
static inline unsigned long kvmppc_hpt_mask(struct kvm_hpt_info *hpt)
static inline void set_dirty_bits(unsigned long *map, unsigned long i, unsigned long npages)
static inline void set_dirty_bits_atomic(unsigned long *map, unsigned long i, unsigned long npages)
static inline u64 sanitize_msr(u64 msr)
static inline void copy_from_checkpoint(struct kvm_vcpu *vcpu)
static inline void copy_to_checkpoint(struct kvm_vcpu *vcpu)
\n
      4 struct kvm_vcpu *vcpu
      3 void
      3 unsigned long ptel
      3 unsigned long l
      3 unsigned long hpte_v
      3 unsigned long h
      3 struct kvm *kvm
      3 __be64 *hpte
      2 unsigned long v
      2 unsigned long *rmap
      2 unsigned long r
      2 unsigned long psize
      2 unsigned long pp
      2 unsigned long npages
      2 unsigned long *map
      2 unsigned long key
      2 unsigned long i
      2 struct kvm_hpt_info *hpt
      1 unsigned long pte_index
      1 unsigned long pagesize
      1 unsigned long hpte_r
      1 unsigned long hptel
      1 unsigned long bits
      1 unsigned long amr
      1 u64 msr
      1 struct revmap_entry *rev
      1 struct kvmppc_book3s_shadow_vcpu *svcpu
      1 struct kvm_memory_slot *memslot
      1 pte_t *ptep
      1 int writing
      1 int base_shift
      1 int actual_shift
      1 CPU_FTR_HVMODE
      1 bool is_ci
