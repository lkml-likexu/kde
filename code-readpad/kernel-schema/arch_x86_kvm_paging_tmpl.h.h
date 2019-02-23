
\n
static gfn_t gpte_to_gfn_lvl(pt_element_t gpte, int lvl)
static inline void FNAME(protect_clean_gpte)
(struct kvm_mmu *mmu, unsigned *access, unsigned gpte)
static inline int FNAME(is_present_gpte)
(unsigned long pte)
static int FNAME(cmpxchg_gpte)
(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, pt_element_t __user *ptep_user, unsigned index, pt_element_t orig_pte, pt_element_t new_pte)
static bool FNAME(prefetch_invalid_gpte)
(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, u64 *spte, u64 gpte)
static inline unsigned FNAME(gpte_access)
(u64 gpte)
static int FNAME(update_accessed_dirty_bits)
(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, struct guest_walker *walker, int write_fault)
static inline unsigned FNAME(gpte_pkeys)
(struct kvm_vcpu *vcpu, u64 gpte)
static int FNAME(walk_addr_generic)
(struct guest_walker *walker, struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, gva_t addr, u32 access)
static int FNAME(walk_addr)
(struct guest_walker *walker, struct kvm_vcpu *vcpu, gva_t addr, u32 access)
static int FNAME(walk_addr_nested)
(struct guest_walker *walker, struct kvm_vcpu *vcpu, gva_t addr, u32 access)
static bool FNAME(prefetch_gpte)
(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, u64 *spte, pt_element_t gpte, bool no_dirty_log)
static void FNAME(update_pte)
(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, u64 *spte, const void *pte)
static bool FNAME(gpte_changed)
(struct kvm_vcpu *vcpu, struct guest_walker *gw, int level)
static void FNAME(pte_prefetch)
(struct kvm_vcpu *vcpu, struct guest_walker *gw, u64 *sptep)
static int FNAME(fetch)
(struct kvm_vcpu *vcpu, gva_t addr, struct guest_walker *gw, int write_fault, int hlevel, kvm_pfn_t pfn, bool map_writable, bool prefault)
static bool FNAME(is_self_change_mapping)
(struct kvm_vcpu *vcpu, struct guest_walker *walker, int user_fault, bool *write_fault_to_shadow_pgtable)
static int FNAME(page_fault)
(struct kvm_vcpu *vcpu, gva_t addr, u32 error_code, bool prefault)
static gpa_t FNAME(get_level1_sp_gpa)
(struct kvm_mmu_page *sp)
static void FNAME(invlpg)
(struct kvm_vcpu *vcpu, gva_t gva, hpa_t root_hpa)
static gpa_t FNAME(gva_to_gpa)
(struct kvm_vcpu *vcpu, gva_t vaddr, u32 access, struct x86_exception *exception)
static gpa_t FNAME(gva_to_gpa_nested)
(struct kvm_vcpu *vcpu, gva_t vaddr, u32 access, struct x86_exception *exception)
static int FNAME(sync_page)
(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp)
\n
     18 struct kvm_vcpu *vcpu
      5 u32 access
      5 struct kvm_mmu_page *sp
      5 struct guest_walker *walker
      5 gva_t addr
      4 struct kvm_mmu *mmu
      3 u64 *spte
      3 u64 gpte
      3 struct guest_walker *gw
      2 struct x86_exception *exception
      2 pt_element_t gpte
      2 int write_fault
      2 gva_t vaddr
      2 bool prefault
      1 walk_addr_nested
      1 walk_addr_generic
      1 walk_addr
      1 update_pte
      1 update_accessed_dirty_bits
      1 unsigned long pte
      1 unsigned index
      1 unsigned gpte
      1 unsigned *access
      1 u64 *sptep
      1 u32 error_code
      1 sync_page
      1 pte_prefetch
      1 pt_element_t __user *ptep_user
      1 pt_element_t orig_pte
      1 pt_element_t new_pte
      1 protect_clean_gpte
      1 prefetch_invalid_gpte
      1 prefetch_gpte
      1 page_fault
      1 kvm_pfn_t pfn
      1 is_self_change_mapping
      1 is_present_gpte
      1 invlpg
      1 int user_fault
      1 int lvl
      1 int level
      1 int hlevel
      1 hpa_t root_hpa
      1 gva_to_gpa_nested
      1 gva_to_gpa
      1 gva_t gva
      1 gpte_pkeys
      1 gpte_changed
      1 gpte_access
      1 get_level1_sp_gpa
      1 fetch
      1 const void *pte
      1 cmpxchg_gpte
      1 bool *write_fault_to_shadow_pgtable
      1 bool no_dirty_log
      1 bool map_writable
