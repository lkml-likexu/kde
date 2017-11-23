
EXPORT_SYMBOL_GPL(kvm_mmu_set_mmio_spte_mask);
EXPORT_SYMBOL_GPL(kvm_mmu_set_mask_ptes);
EXPORT_SYMBOL_GPL(kvm_mmu_clear_dirty_pt_masked);
EXPORT_SYMBOL_GPL(kvm_mmu_unprotect_page);
EXPORT_SYMBOL_GPL(kvm_mmu_free_roots);
EXPORT_SYMBOL_GPL(kvm_mmu_sync_roots);
EXPORT_SYMBOL_GPL(kvm_handle_page_fault);
EXPORT_SYMBOL_GPL(kvm_mmu_new_cr3);
EXPORT_SYMBOL_GPL(reset_shadow_zero_bits_mask);
EXPORT_SYMBOL_GPL(kvm_init_shadow_mmu);
EXPORT_SYMBOL_GPL(kvm_init_shadow_ept_mmu);
EXPORT_SYMBOL_GPL(kvm_init_mmu);
EXPORT_SYMBOL_GPL(kvm_mmu_reset_context);
EXPORT_SYMBOL_GPL(kvm_mmu_load);
EXPORT_SYMBOL_GPL(kvm_mmu_unload);
EXPORT_SYMBOL_GPL(kvm_mmu_unprotect_page_virt);
EXPORT_SYMBOL_GPL(kvm_mmu_page_fault);
EXPORT_SYMBOL_GPL(kvm_mmu_invlpg);
EXPORT_SYMBOL_GPL(kvm_mmu_invpcid_gva);
EXPORT_SYMBOL_GPL(kvm_enable_tdp);
EXPORT_SYMBOL_GPL(kvm_disable_tdp);
EXPORT_SYMBOL_GPL(kvm_mmu_slot_leaf_clear_dirty);
EXPORT_SYMBOL_GPL(kvm_mmu_slot_largepage_remove_write_access);
EXPORT_SYMBOL_GPL(kvm_mmu_slot_set_dirty);
void kvm_mmu_set_mmio_spte_mask(u64 mmio_mask, u64 mmio_value)
static inline bool sp_ad_disabled(struct kvm_mmu_page *sp)
static inline bool spte_ad_enabled(u64 spte)
static inline u64 spte_shadow_accessed_mask(u64 spte)
static inline u64 spte_shadow_dirty_mask(u64 spte)
static inline bool is_access_track_spte(u64 spte)
static u64 generation_mmio_spte_mask(unsigned int gen)
static unsigned int get_mmio_spte_generation(u64 spte)
static unsigned int kvm_current_mmio_generation(struct kvm_vcpu *vcpu)
static void mark_mmio_spte(struct kvm_vcpu *vcpu, u64 *sptep, u64 gfn, unsigned access)
static bool is_mmio_spte(u64 spte)
static gfn_t get_mmio_spte_gfn(u64 spte)
static unsigned get_mmio_spte_access(u64 spte)
static bool set_mmio_spte(struct kvm_vcpu *vcpu, u64 *sptep, gfn_t gfn, kvm_pfn_t pfn, unsigned access)
static bool check_mmio_spte(struct kvm_vcpu *vcpu, u64 spte)
void kvm_mmu_set_mask_ptes(u64 user_mask, u64 accessed_mask, u64 dirty_mask, u64 nx_mask, u64 x_mask, u64 p_mask, u64 acc_track_mask, u64 me_mask)
static void kvm_mmu_reset_all_pte_masks(void)
static int is_cpuid_PSE36(void)
static int is_nx(struct kvm_vcpu *vcpu)
static int is_shadow_present_pte(u64 pte)
static int is_large_pte(u64 pte)
static int is_last_spte(u64 pte, int level)
static bool is_executable_pte(u64 spte)
static kvm_pfn_t spte_to_pfn(u64 pte)
static gfn_t pse36_gfn_delta(u32 gpte)
static void __set_spte(u64 *sptep, u64 spte)
static void __update_clear_spte_fast(u64 *sptep, u64 spte)
static u64 __update_clear_spte_slow(u64 *sptep, u64 spte)
static u64 __get_spte_lockless(u64 *sptep)
static void count_spte_clear(u64 *sptep, u64 spte)
static void __set_spte(u64 *sptep, u64 spte)
static void __update_clear_spte_fast(u64 *sptep, u64 spte)
static u64 __update_clear_spte_slow(u64 *sptep, u64 spte)
static u64 __get_spte_lockless(u64 *sptep)
static bool spte_can_locklessly_be_made_writable(u64 spte)
static bool spte_has_volatile_bits(u64 spte)
static bool is_accessed_spte(u64 spte)
static bool is_dirty_spte(u64 spte)
static void mmu_spte_set(u64 *sptep, u64 new_spte)
static u64 mmu_spte_update_no_track(u64 *sptep, u64 new_spte)
static bool mmu_spte_update(u64 *sptep, u64 new_spte)
static int mmu_spte_clear_track_bits(u64 *sptep)
static void mmu_spte_clear_no_track(u64 *sptep)
static u64 mmu_spte_get_lockless(u64 *sptep)
static u64 mark_spte_for_access_track(u64 spte)
static u64 restore_acc_track_spte(u64 spte)
static bool mmu_spte_age(u64 *sptep)
static void walk_shadow_page_lockless_begin(struct kvm_vcpu *vcpu)
static void walk_shadow_page_lockless_end(struct kvm_vcpu *vcpu)
static int mmu_topup_memory_cache(struct kvm_mmu_memory_cache *cache, struct kmem_cache *base_cache, int min)
static int mmu_memory_cache_free_objects(struct kvm_mmu_memory_cache *cache)
static void mmu_free_memory_cache(struct kvm_mmu_memory_cache *mc, struct kmem_cache *cache)
static int mmu_topup_memory_cache_page(struct kvm_mmu_memory_cache *cache, int min)
static void mmu_free_memory_cache_page(struct kvm_mmu_memory_cache *mc)
static int mmu_topup_memory_caches(struct kvm_vcpu *vcpu)
static void mmu_free_memory_caches(struct kvm_vcpu *vcpu)
static void *mmu_memory_cache_alloc(struct kvm_mmu_memory_cache *mc)
static struct pte_list_desc *mmu_alloc_pte_list_desc(struct kvm_vcpu *vcpu)
static void mmu_free_pte_list_desc(struct pte_list_desc *pte_list_desc)
static gfn_t kvm_mmu_page_get_gfn(struct kvm_mmu_page *sp, int index)
static void kvm_mmu_page_set_gfn(struct kvm_mmu_page *sp, int index, gfn_t gfn)
static struct kvm_lpage_info *lpage_info_slot(gfn_t gfn, struct kvm_memory_slot *slot, int level)
static void update_gfn_disallow_lpage_count(struct kvm_memory_slot *slot, gfn_t gfn, int count)
void kvm_mmu_gfn_disallow_lpage(struct kvm_memory_slot *slot, gfn_t gfn)
void kvm_mmu_gfn_allow_lpage(struct kvm_memory_slot *slot, gfn_t gfn)
static void account_shadowed(struct kvm *kvm, struct kvm_mmu_page *sp)
static void unaccount_shadowed(struct kvm *kvm, struct kvm_mmu_page *sp)
static bool __mmu_gfn_lpage_is_disallowed(gfn_t gfn, int level, struct kvm_memory_slot *slot)
static bool mmu_gfn_lpage_is_disallowed(struct kvm_vcpu *vcpu, gfn_t gfn, int level)
static int host_mapping_level(struct kvm *kvm, gfn_t gfn)
static inline bool memslot_valid_for_gpte(struct kvm_memory_slot *slot, bool no_dirty_log)
static struct kvm_memory_slot * gfn_to_memslot_dirty_bitmap(struct kvm_vcpu *vcpu, gfn_t gfn, bool no_dirty_log)
static int mapping_level(struct kvm_vcpu *vcpu, gfn_t large_gfn, bool *force_pt_level)
static int pte_list_add(struct kvm_vcpu *vcpu, u64 *spte, struct kvm_rmap_head *rmap_head)
static void pte_list_desc_remove_entry(struct kvm_rmap_head *rmap_head, struct pte_list_desc *desc, int i, struct pte_list_desc *prev_desc)
static void __pte_list_remove(u64 *spte, struct kvm_rmap_head *rmap_head)
static void pte_list_remove(struct kvm_rmap_head *rmap_head, u64 *sptep)
static struct kvm_rmap_head *__gfn_to_rmap(gfn_t gfn, int level, struct kvm_memory_slot *slot)
static struct kvm_rmap_head *gfn_to_rmap(struct kvm *kvm, gfn_t gfn, struct kvm_mmu_page *sp)
static bool rmap_can_add(struct kvm_vcpu *vcpu)
static int rmap_add(struct kvm_vcpu *vcpu, u64 *spte, gfn_t gfn)
static void rmap_remove(struct kvm *kvm, u64 *spte)
static u64 *rmap_get_first(struct kvm_rmap_head *rmap_head, struct rmap_iterator *iter)
static u64 *rmap_get_next(struct rmap_iterator *iter)
static void drop_spte(struct kvm *kvm, u64 *sptep)
static bool __drop_large_spte(struct kvm *kvm, u64 *sptep)
static void drop_large_spte(struct kvm_vcpu *vcpu, u64 *sptep)
static bool spte_write_protect(u64 *sptep, bool pt_protect)
static bool __rmap_write_protect(struct kvm *kvm, struct kvm_rmap_head *rmap_head, bool pt_protect)
static bool spte_clear_dirty(u64 *sptep)
static bool wrprot_ad_disabled_spte(u64 *sptep)
static bool __rmap_clear_dirty(struct kvm *kvm, struct kvm_rmap_head *rmap_head)
static bool spte_set_dirty(u64 *sptep)
static bool __rmap_set_dirty(struct kvm *kvm, struct kvm_rmap_head *rmap_head)
static void kvm_mmu_write_protect_pt_masked(struct kvm *kvm, struct kvm_memory_slot *slot, gfn_t gfn_offset, unsigned long mask)
void kvm_mmu_clear_dirty_pt_masked(struct kvm *kvm, struct kvm_memory_slot *slot, gfn_t gfn_offset, unsigned long mask)
void kvm_arch_mmu_enable_log_dirty_pt_masked(struct kvm *kvm, struct kvm_memory_slot *slot, gfn_t gfn_offset, unsigned long mask)
int kvm_arch_write_log_dirty(struct kvm_vcpu *vcpu)
bool kvm_mmu_slot_gfn_write_protect(struct kvm *kvm, struct kvm_memory_slot *slot, u64 gfn)
static bool rmap_write_protect(struct kvm_vcpu *vcpu, u64 gfn)
static bool kvm_zap_rmapp(struct kvm *kvm, struct kvm_rmap_head *rmap_head)
static int kvm_unmap_rmapp(struct kvm *kvm, struct kvm_rmap_head *rmap_head, struct kvm_memory_slot *slot, gfn_t gfn, int level, unsigned long data)
static int kvm_set_pte_rmapp(struct kvm *kvm, struct kvm_rmap_head *rmap_head, struct kvm_memory_slot *slot, gfn_t gfn, int level, unsigned long data)
static void rmap_walk_init_level(struct slot_rmap_walk_iterator *iterator, int level)
static void slot_rmap_walk_init(struct slot_rmap_walk_iterator *iterator, struct kvm_memory_slot *slot, int start_level, int end_level, gfn_t start_gfn, gfn_t end_gfn)
static bool slot_rmap_walk_okay(struct slot_rmap_walk_iterator *iterator)
static void slot_rmap_walk_next(struct slot_rmap_walk_iterator *iterator)
static int kvm_handle_hva_range(struct kvm *kvm, unsigned long start, unsigned long end, unsigned long data, int (*handler)
(struct kvm *kvm, struct kvm_rmap_head *rmap_head, struct kvm_memory_slot *slot, gfn_t gfn, int level, unsigned long data)
)
static int kvm_handle_hva(struct kvm *kvm, unsigned long hva, unsigned long data, int (*handler)
(struct kvm *kvm, struct kvm_rmap_head *rmap_head, struct kvm_memory_slot *slot, gfn_t gfn, int level, unsigned long data)
)
int kvm_unmap_hva_range(struct kvm *kvm, unsigned long start, unsigned long end)
void kvm_set_spte_hva(struct kvm *kvm, unsigned long hva, pte_t pte)
static int kvm_age_rmapp(struct kvm *kvm, struct kvm_rmap_head *rmap_head, struct kvm_memory_slot *slot, gfn_t gfn, int level, unsigned long data)
static int kvm_test_age_rmapp(struct kvm *kvm, struct kvm_rmap_head *rmap_head, struct kvm_memory_slot *slot, gfn_t gfn, int level, unsigned long data)
static void rmap_recycle(struct kvm_vcpu *vcpu, u64 *spte, gfn_t gfn)
int kvm_age_hva(struct kvm *kvm, unsigned long start, unsigned long end)
int kvm_test_age_hva(struct kvm *kvm, unsigned long hva)
static int is_empty_shadow_page(u64 *spt)
static inline void kvm_mod_used_mmu_pages(struct kvm *kvm, int nr)
static void kvm_mmu_free_page(struct kvm_mmu_page *sp)
static unsigned kvm_page_table_hashfn(gfn_t gfn)
static void mmu_page_add_parent_pte(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, u64 *parent_pte)
static void mmu_page_remove_parent_pte(struct kvm_mmu_page *sp, u64 *parent_pte)
static void drop_parent_pte(struct kvm_mmu_page *sp, u64 *parent_pte)
static struct kvm_mmu_page *kvm_mmu_alloc_page(struct kvm_vcpu *vcpu, int direct)
static void mark_unsync(u64 *spte)
; static void kvm_mmu_mark_parents_unsync(struct kvm_mmu_page *sp)
static void mark_unsync(u64 *spte)
static int nonpaging_sync_page(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp)
static void nonpaging_invlpg(struct kvm_vcpu *vcpu, gva_t gva, hpa_t root)
static void nonpaging_update_pte(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, u64 *spte, const void *pte)
static int mmu_pages_add(struct kvm_mmu_pages *pvec, struct kvm_mmu_page *sp, int idx)
static inline void clear_unsync_child_bit(struct kvm_mmu_page *sp, int idx)
static int __mmu_unsync_walk(struct kvm_mmu_page *sp, struct kvm_mmu_pages *pvec)
static int mmu_unsync_walk(struct kvm_mmu_page *sp, struct kvm_mmu_pages *pvec)
static void kvm_unlink_unsync_page(struct kvm *kvm, struct kvm_mmu_page *sp)
static bool __kvm_sync_page(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, struct list_head *invalid_list)
static void kvm_mmu_flush_or_zap(struct kvm_vcpu *vcpu, struct list_head *invalid_list, bool remote_flush, bool local_flush)
static bool is_obsolete_sp(struct kvm *kvm, struct kvm_mmu_page *sp)
static bool kvm_sync_page(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, struct list_head *invalid_list)
static bool kvm_sync_pages(struct kvm_vcpu *vcpu, gfn_t gfn, struct list_head *invalid_list)
static int mmu_pages_next(struct kvm_mmu_pages *pvec, struct mmu_page_path *parents, int i)
static int mmu_pages_first(struct kvm_mmu_pages *pvec, struct mmu_page_path *parents)
static void mmu_pages_clear_parents(struct mmu_page_path *parents)
static void mmu_sync_children(struct kvm_vcpu *vcpu, struct kvm_mmu_page *parent)
static void __clear_sp_write_flooding_count(struct kvm_mmu_page *sp)
static void clear_sp_write_flooding_count(u64 *spte)
static struct kvm_mmu_page *kvm_mmu_get_page(struct kvm_vcpu *vcpu, gfn_t gfn, gva_t gaddr, unsigned level, int direct, unsigned access)
static void shadow_walk_init_using_root(struct kvm_shadow_walk_iterator *iterator, struct kvm_vcpu *vcpu, hpa_t root, u64 addr)
static void shadow_walk_init(struct kvm_shadow_walk_iterator *iterator, struct kvm_vcpu *vcpu, u64 addr)
static bool shadow_walk_okay(struct kvm_shadow_walk_iterator *iterator)
static void __shadow_walk_next(struct kvm_shadow_walk_iterator *iterator, u64 spte)
static void shadow_walk_next(struct kvm_shadow_walk_iterator *iterator)
static void link_shadow_page(struct kvm_vcpu *vcpu, u64 *sptep, struct kvm_mmu_page *sp)
static void validate_direct_spte(struct kvm_vcpu *vcpu, u64 *sptep, unsigned direct_access)
static bool mmu_page_zap_pte(struct kvm *kvm, struct kvm_mmu_page *sp, u64 *spte)
static void kvm_mmu_page_unlink_children(struct kvm *kvm, struct kvm_mmu_page *sp)
static void kvm_mmu_unlink_parents(struct kvm *kvm, struct kvm_mmu_page *sp)
static int mmu_zap_unsync_children(struct kvm *kvm, struct kvm_mmu_page *parent, struct list_head *invalid_list)
static int kvm_mmu_prepare_zap_page(struct kvm *kvm, struct kvm_mmu_page *sp, struct list_head *invalid_list)
static void kvm_mmu_commit_zap_page(struct kvm *kvm, struct list_head *invalid_list)
static bool prepare_zap_oldest_mmu_page(struct kvm *kvm, struct list_head *invalid_list)
void kvm_mmu_change_mmu_pages(struct kvm *kvm, unsigned int goal_nr_mmu_pages)
int kvm_mmu_unprotect_page(struct kvm *kvm, gfn_t gfn)
static void kvm_unsync_page(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp)
static bool mmu_need_write_protect(struct kvm_vcpu *vcpu, gfn_t gfn, bool can_unsync)
static bool kvm_is_mmio_pfn(kvm_pfn_t pfn)
static int set_spte(struct kvm_vcpu *vcpu, u64 *sptep, unsigned pte_access, int level, gfn_t gfn, kvm_pfn_t pfn, bool speculative, bool can_unsync, bool host_writable)
static int mmu_set_spte(struct kvm_vcpu *vcpu, u64 *sptep, unsigned pte_access, int write_fault, int level, gfn_t gfn, kvm_pfn_t pfn, bool speculative, bool host_writable)
static kvm_pfn_t pte_prefetch_gfn_to_pfn(struct kvm_vcpu *vcpu, gfn_t gfn, bool no_dirty_log)
static int direct_pte_prefetch_many(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, u64 *start, u64 *end)
static void __direct_pte_prefetch(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, u64 *sptep)
static void direct_pte_prefetch(struct kvm_vcpu *vcpu, u64 *sptep)
static int __direct_map(struct kvm_vcpu *vcpu, int write, int map_writable, int level, gfn_t gfn, kvm_pfn_t pfn, bool prefault)
static void kvm_send_hwpoison_signal(unsigned long address, struct task_struct *tsk)
static int kvm_handle_bad_page(struct kvm_vcpu *vcpu, gfn_t gfn, kvm_pfn_t pfn)
static void transparent_hugepage_adjust(struct kvm_vcpu *vcpu, gfn_t *gfnp, kvm_pfn_t *pfnp, int *levelp)
static bool handle_abnormal_pfn(struct kvm_vcpu *vcpu, gva_t gva, gfn_t gfn, kvm_pfn_t pfn, unsigned access, int *ret_val)
static bool page_fault_can_be_fast(u32 error_code)
static bool fast_pf_fix_direct_spte(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, u64 *sptep, u64 old_spte, u64 new_spte)
static bool is_access_allowed(u32 fault_err_code, u64 spte)
static bool fast_page_fault(struct kvm_vcpu *vcpu, gva_t gva, int level, u32 error_code)
static int nonpaging_map(struct kvm_vcpu *vcpu, gva_t v, u32 error_code, gfn_t gfn, bool prefault)
static void mmu_free_root_page(struct kvm *kvm, hpa_t *root_hpa, struct list_head *invalid_list)
void kvm_mmu_free_roots(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, ulong roots_to_free)
static int mmu_check_root(struct kvm_vcpu *vcpu, gfn_t root_gfn)
static int mmu_alloc_direct_roots(struct kvm_vcpu *vcpu)
static int mmu_alloc_shadow_roots(struct kvm_vcpu *vcpu)
static int mmu_alloc_roots(struct kvm_vcpu *vcpu)
void kvm_mmu_sync_roots(struct kvm_vcpu *vcpu)
static gpa_t nonpaging_gva_to_gpa(struct kvm_vcpu *vcpu, gva_t vaddr, u32 access, struct x86_exception *exception)
static gpa_t nonpaging_gva_to_gpa_nested(struct kvm_vcpu *vcpu, gva_t vaddr, u32 access, struct x86_exception *exception)
static bool __is_rsvd_bits_set(struct rsvd_bits_validate *rsvd_check, u64 pte, int level)
static bool is_rsvd_bits_set(struct kvm_mmu *mmu, u64 gpte, int level)
static bool is_shadow_zero_bits_set(struct kvm_mmu *mmu, u64 spte, int level)
static bool mmio_info_in_cache(struct kvm_vcpu *vcpu, u64 addr, bool direct)
static bool walk_shadow_page_get_mmio_spte(struct kvm_vcpu *vcpu, u64 addr, u64 *sptep)
static int handle_mmio_page_fault(struct kvm_vcpu *vcpu, u64 addr, bool direct)
static bool page_fault_handle_page_track(struct kvm_vcpu *vcpu, u32 error_code, gfn_t gfn)
static void shadow_page_table_clear_flood(struct kvm_vcpu *vcpu, gva_t addr)
static int nonpaging_page_fault(struct kvm_vcpu *vcpu, gva_t gva, u32 error_code, bool prefault)
static int kvm_arch_setup_async_pf(struct kvm_vcpu *vcpu, gva_t gva, gfn_t gfn)
bool kvm_can_do_async_pf(struct kvm_vcpu *vcpu)
static bool try_async_pf(struct kvm_vcpu *vcpu, bool prefault, gfn_t gfn, gva_t gva, kvm_pfn_t *pfn, bool write, bool *writable)
int kvm_handle_page_fault(struct kvm_vcpu *vcpu, u64 error_code, u64 fault_address, char *insn, int insn_len)
static bool check_hugepage_cache_consistency(struct kvm_vcpu *vcpu, gfn_t gfn, int level)
static int tdp_page_fault(struct kvm_vcpu *vcpu, gva_t gpa, u32 error_code, bool prefault)
static void nonpaging_init_context(struct kvm_vcpu *vcpu, struct kvm_mmu *context)
static bool cached_root_available(struct kvm_vcpu *vcpu, gpa_t new_cr3, union kvm_mmu_page_role new_role)
static bool fast_cr3_switch(struct kvm_vcpu *vcpu, gpa_t new_cr3, union kvm_mmu_page_role new_role, bool skip_tlb_flush)
static void __kvm_mmu_new_cr3(struct kvm_vcpu *vcpu, gpa_t new_cr3, union kvm_mmu_page_role new_role, bool skip_tlb_flush)
void kvm_mmu_new_cr3(struct kvm_vcpu *vcpu, gpa_t new_cr3, bool skip_tlb_flush)
static unsigned long get_cr3(struct kvm_vcpu *vcpu)
static void inject_page_fault(struct kvm_vcpu *vcpu, struct x86_exception *fault)
static bool sync_mmio_spte(struct kvm_vcpu *vcpu, u64 *sptep, gfn_t gfn, unsigned access, int *nr_present)
static inline bool is_last_gpte(struct kvm_mmu *mmu, unsigned level, unsigned gpte)
static void __reset_rsvds_bits_mask(struct kvm_vcpu *vcpu, struct rsvd_bits_validate *rsvd_check, int maxphyaddr, int level, bool nx, bool gbpages, bool pse, bool amd)
static void reset_rsvds_bits_mask(struct kvm_vcpu *vcpu, struct kvm_mmu *context)
static void __reset_rsvds_bits_mask_ept(struct rsvd_bits_validate *rsvd_check, int maxphyaddr, bool execonly)
static void reset_rsvds_bits_mask_ept(struct kvm_vcpu *vcpu, struct kvm_mmu *context, bool execonly)
void reset_shadow_zero_bits_mask(struct kvm_vcpu *vcpu, struct kvm_mmu *context)
static inline bool boot_cpu_is_amd(void)
static void reset_tdp_shadow_zero_bits_mask(struct kvm_vcpu *vcpu, struct kvm_mmu *context)
static void reset_ept_shadow_zero_bits_mask(struct kvm_vcpu *vcpu, struct kvm_mmu *context, bool execonly)
static void update_permission_bitmask(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, bool ept)
static void update_pkru_bitmask(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu, bool ept)
static void update_last_nonleaf_level(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu)
static void paging64_init_context_common(struct kvm_vcpu *vcpu, struct kvm_mmu *context, int level)
static void paging64_init_context(struct kvm_vcpu *vcpu, struct kvm_mmu *context)
static void paging32_init_context(struct kvm_vcpu *vcpu, struct kvm_mmu *context)
static void paging32E_init_context(struct kvm_vcpu *vcpu, struct kvm_mmu *context)
static union kvm_mmu_extended_role kvm_calc_mmu_role_ext(struct kvm_vcpu *vcpu)
static union kvm_mmu_role kvm_calc_mmu_role_common(struct kvm_vcpu *vcpu, bool base_only)
static union kvm_mmu_role kvm_calc_tdp_mmu_root_page_role(struct kvm_vcpu *vcpu, bool base_only)
static void init_kvm_tdp_mmu(struct kvm_vcpu *vcpu)
static union kvm_mmu_role kvm_calc_shadow_mmu_root_page_role(struct kvm_vcpu *vcpu, bool base_only)
void kvm_init_shadow_mmu(struct kvm_vcpu *vcpu)
static union kvm_mmu_role kvm_calc_shadow_ept_root_page_role(struct kvm_vcpu *vcpu, bool accessed_dirty, bool execonly)
void kvm_init_shadow_ept_mmu(struct kvm_vcpu *vcpu, bool execonly, bool accessed_dirty, gpa_t new_eptp)
static void init_kvm_softmmu(struct kvm_vcpu *vcpu)
static void init_kvm_nested_mmu(struct kvm_vcpu *vcpu)
void kvm_init_mmu(struct kvm_vcpu *vcpu, bool reset_roots)
static union kvm_mmu_page_role kvm_mmu_calc_root_page_role(struct kvm_vcpu *vcpu)
void kvm_mmu_reset_context(struct kvm_vcpu *vcpu)
int kvm_mmu_load(struct kvm_vcpu *vcpu)
void kvm_mmu_unload(struct kvm_vcpu *vcpu)
static void mmu_pte_write_new_pte(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp, u64 *spte, const void *new)
static bool need_remote_flush(u64 old, u64 new)
static u64 mmu_pte_write_fetch_gpte(struct kvm_vcpu *vcpu, gpa_t *gpa, const u8 *new, int *bytes)
static bool detect_write_flooding(struct kvm_mmu_page *sp)
static bool detect_write_misaligned(struct kvm_mmu_page *sp, gpa_t gpa, int bytes)
static u64 *get_written_sptes(struct kvm_mmu_page *sp, gpa_t gpa, int *nspte)
static void kvm_mmu_pte_write(struct kvm_vcpu *vcpu, gpa_t gpa, const u8 *new, int bytes, struct kvm_page_track_notifier_node *node)
int kvm_mmu_unprotect_page_virt(struct kvm_vcpu *vcpu, gva_t gva)
static int make_mmu_pages_available(struct kvm_vcpu *vcpu)
int kvm_mmu_page_fault(struct kvm_vcpu *vcpu, gva_t cr2, u64 error_code, void *insn, int insn_len)
void kvm_mmu_invlpg(struct kvm_vcpu *vcpu, gva_t gva)
void kvm_mmu_invpcid_gva(struct kvm_vcpu *vcpu, gva_t gva, unsigned long pcid)
void kvm_enable_tdp(void)
void kvm_disable_tdp(void)
static void free_mmu_pages(struct kvm_vcpu *vcpu)
static int alloc_mmu_pages(struct kvm_vcpu *vcpu)
int kvm_mmu_create(struct kvm_vcpu *vcpu)
static void kvm_mmu_invalidate_zap_pages_in_memslot(struct kvm *kvm, struct kvm_memory_slot *slot, struct kvm_page_track_notifier_node *node)
void kvm_mmu_init_vm(struct kvm *kvm)
void kvm_mmu_uninit_vm(struct kvm *kvm)
static __always_inline bool slot_handle_level_range(struct kvm *kvm, struct kvm_memory_slot *memslot, slot_level_handler fn, int start_level, int end_level, gfn_t start_gfn, gfn_t end_gfn, bool lock_flush_tlb)
static __always_inline bool slot_handle_level(struct kvm *kvm, struct kvm_memory_slot *memslot, slot_level_handler fn, int start_level, int end_level, bool lock_flush_tlb)
static __always_inline bool slot_handle_all_level(struct kvm *kvm, struct kvm_memory_slot *memslot, slot_level_handler fn, bool lock_flush_tlb)
static __always_inline bool slot_handle_large_level(struct kvm *kvm, struct kvm_memory_slot *memslot, slot_level_handler fn, bool lock_flush_tlb)
static __always_inline bool slot_handle_leaf(struct kvm *kvm, struct kvm_memory_slot *memslot, slot_level_handler fn, bool lock_flush_tlb)
void kvm_zap_gfn_range(struct kvm *kvm, gfn_t gfn_start, gfn_t gfn_end)
static bool slot_rmap_write_protect(struct kvm *kvm, struct kvm_rmap_head *rmap_head)
void kvm_mmu_slot_remove_write_access(struct kvm *kvm, struct kvm_memory_slot *memslot)
static bool kvm_mmu_zap_collapsible_spte(struct kvm *kvm, struct kvm_rmap_head *rmap_head)
void kvm_mmu_zap_collapsible_sptes(struct kvm *kvm, const struct kvm_memory_slot *memslot)
void kvm_mmu_slot_leaf_clear_dirty(struct kvm *kvm, struct kvm_memory_slot *memslot)
void kvm_mmu_slot_largepage_remove_write_access(struct kvm *kvm, struct kvm_memory_slot *memslot)
void kvm_mmu_slot_set_dirty(struct kvm *kvm, struct kvm_memory_slot *memslot)
define BATCH_ZAP_PAGES 10 static void kvm_zap_obsolete_pages(struct kvm *kvm)
void kvm_mmu_invalidate_zap_all_pages(struct kvm *kvm)
static bool kvm_has_zapped_obsolete_pages(struct kvm *kvm)
void kvm_mmu_invalidate_mmio_sptes(struct kvm *kvm, struct kvm_memslots *slots)
static unsigned long mmu_shrink_scan(struct shrinker *shrink, struct shrink_control *sc)
static unsigned long mmu_shrink_count(struct shrinker *shrink, struct shrink_control *sc)
static void mmu_destroy_caches(void)
int kvm_mmu_module_init(void)
unsigned int kvm_mmu_calculate_mmu_pages(struct kvm *kvm)
void kvm_mmu_destroy(struct kvm_vcpu *vcpu)
void kvm_mmu_module_exit(void)
 118 struct kvm_vcpu *vcpu
  61 struct kvm *kvm
  37 gfn_t gfn
  35 u64 *sptep
  35 struct kvm_mmu_page *sp
  26 u64 spte
  22 int level
  19 struct kvm_memory_slot *slot
  17 struct kvm_rmap_head *rmap_head
  11 u64 *spte
  10 struct kvm_mmu *context
   9 struct list_head *invalid_list
   9 struct kvm_memory_slot *memslot
   9 gva_t gva
   8 void
   8 unsigned long data
   7 struct kvm_mmu *mmu
   7 kvm_pfn_t pfn
   6 u32 error_code
   5 unsigned access
   5 u64 pte
   5 u64 addr
   5 struct kvm_shadow_walk_iterator *iterator
   5 struct kvm_mmu_pages *pvec
   5 slot_level_handler fn
   5 bool prefault
   5 bool lock_flush_tlb
   5 bool execonly
   4 u64 new_spte
   4 struct slot_rmap_walk_iterator *iterator
   4 gpa_t new_cr3
   3 unsigned long start
   3 unsigned long mask
   3 unsigned long hva
   3 unsigned long end
   3 union kvm_mmu_page_role new_role
   3 u64 gfn
   3 u64 *parent_pte
   3 struct rsvd_bits_validate *rsvd_check
   3 struct mmu_page_path *parents
   3 struct kvm_mmu_memory_cache *mc
   3 struct kvm_mmu_memory_cache *cache
   3 int start_level
   3 int end_level
   3 gpa_t gpa
   3 gfn_t gfn_offset
   3 bool skip_tlb_flush
   3 bool no_dirty_log
   3 bool base_only
   2 unsigned pte_access
   2 unsigned level
   2 u64 error_code
   2 u32 access
   2 struct x86_exception *exception
   2 struct shrinker *shrink
   2 struct shrink_control *sc
   2 struct rmap_iterator *iter
   2 struct kvm_page_track_notifier_node *node
   2 struct kvm_mmu_page *parent
   2 int min
   2 int maxphyaddr
   2 int insn_len
   2 int index
   2 int idx
   2 int i
   2 int direct
   2 int bytes
   2 int *handler
   2 hpa_t root
   2 gva_t vaddr
   2 gfn_t start_gfn
   2 gfn_t end_gfn
   2 const u8 *new
   2 bool speculative
   2 bool pt_protect
   2 bool host_writable
   2 bool ept
   2 bool direct
   2 bool can_unsync
   2 bool accessed_dirty
   1 void *insn
   1 unsigned long pcid
   1 unsigned long address
   1 unsigned int goal_nr_mmu_pages
   1 unsigned int gen
   1 unsigned gpte
   1 unsigned direct_access
   1 ulong roots_to_free
   1 u64 x_mask
   1 u64 user_mask
   1 u64 p_mask
   1 u64 old_spte
   1 u64 old
   1 u64 nx_mask
   1 u64 new
   1 u64 mmio_value
   1 u64 mmio_mask
   1 u64 me_mask
   1 u64 gpte
   1 u64 fault_address
   1 u64 dirty_mask
   1 u64 accessed_mask
   1 u64 acc_track_mask
   1 u64 *start
   1 u64 *spt
   1 u64 *end
   1 u32 gpte
   1 u32 fault_err_code
   1 struct x86_exception *fault
   1 struct task_struct *tsk
   1 struct pte_list_desc *pte_list_desc
   1 struct pte_list_desc *prev_desc
   1 struct pte_list_desc *desc
   1 struct kvm_memslots *slots
   1 struct kmem_cache *cache
   1 struct kmem_cache *base_cache
   1 reset_shadow_zero_bits_mask
   1 pte_t pte
   1 kvm_pfn_t *pfnp
   1 kvm_pfn_t *pfn
   1 kvm_mmu_unprotect_page_virt
   1 kvm_mmu_unprotect_page
   1 kvm_mmu_unload
   1 kvm_mmu_sync_roots
   1 kvm_mmu_slot_set_dirty
   1 kvm_mmu_slot_leaf_clear_dirty
   1 kvm_mmu_slot_largepage_remove_write_access
   1 kvm_mmu_set_mmio_spte_mask
   1 kvm_mmu_set_mask_ptes
   1 kvm_mmu_reset_context
   1 kvm_mmu_page_fault
   1 kvm_mmu_new_cr3
   1 kvm_mmu_load
   1 kvm_mmu_invpcid_gva
   1 kvm_mmu_invlpg
   1 kvm_mmu_free_roots
   1 kvm_mmu_clear_dirty_pt_masked
   1 kvm_init_shadow_mmu
   1 kvm_init_shadow_ept_mmu
   1 kvm_init_mmu
   1 kvm_handle_page_fault
   1 kvm_enable_tdp
   1 kvm_disable_tdp
   1 int write_fault
   1 int write
   1 int nr
   1 int map_writable
   1 int count
   1 int *ret_val
   1 int *nspte
   1 int *nr_present
   1 int *levelp
   1 int *bytes
   1 hpa_t *root_hpa
   1 gva_t v
   1 gva_t gpa
   1 gva_t gaddr
   1 gva_t cr2
   1 gva_t addr
   1 gpa_t new_eptp
   1 gpa_t *gpa
   1 gfn_t root_gfn
   1 gfn_t large_gfn
   1 gfn_t gfn_start
   1 gfn_t gfn_end
   1 gfn_t *gfnp
   1 const void *pte
   1 const void *new
   1 const struct kvm_memory_slot *memslot
   1 char *insn
   1 bool write
   1 bool reset_roots
   1 bool remote_flush
   1 bool pse
   1 bool nx
   1 bool local_flush
   1 bool gbpages
   1 bool amd
   1 bool *writable
   1 bool *force_pt_level
