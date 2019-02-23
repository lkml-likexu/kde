
\n
bool intel_gvt_ggtt_validate_range(struct intel_vgpu *vgpu, u64 addr, u32 size)
int intel_gvt_ggtt_gmadr_g2h(struct intel_vgpu *vgpu, u64 g_addr, u64 *h_addr)
int intel_gvt_ggtt_gmadr_h2g(struct intel_vgpu *vgpu, u64 h_addr, u64 *g_addr)
int intel_gvt_ggtt_index_g2h(struct intel_vgpu *vgpu, unsigned long g_index, unsigned long *h_index)
int intel_gvt_ggtt_h2g_index(struct intel_vgpu *vgpu, unsigned long h_index, unsigned long *g_index)
static inline int get_next_pt_type(int type)
static inline int get_pt_type(int type)
static inline int get_entry_type(int type)
static inline int get_pse_type(int type)
static u64 read_pte64(struct drm_i915_private *dev_priv, unsigned long index)
static void ggtt_invalidate(struct drm_i915_private *dev_priv)
static void write_pte64(struct drm_i915_private *dev_priv, unsigned long index, u64 pte)
static inline int gtt_get_entry64(void *pt, struct intel_gvt_gtt_entry *e, unsigned long index, bool hypervisor_access, unsigned long gpa, struct intel_vgpu *vgpu)
static inline int gtt_set_entry64(void *pt, struct intel_gvt_gtt_entry *e, unsigned long index, bool hypervisor_access, unsigned long gpa, struct intel_vgpu *vgpu)
static unsigned long gen8_gtt_get_pfn(struct intel_gvt_gtt_entry *e)
static void gen8_gtt_set_pfn(struct intel_gvt_gtt_entry *e, unsigned long pfn)
static bool gen8_gtt_test_pse(struct intel_gvt_gtt_entry *e)
static void gen8_gtt_clear_pse(struct intel_gvt_gtt_entry *e)
static bool gen8_gtt_test_ips(struct intel_gvt_gtt_entry *e)
static void gen8_gtt_clear_ips(struct intel_gvt_gtt_entry *e)
static bool gen8_gtt_test_present(struct intel_gvt_gtt_entry *e)
static void gtt_entry_clear_present(struct intel_gvt_gtt_entry *e)
static void gtt_entry_set_present(struct intel_gvt_gtt_entry *e)
static bool gen8_gtt_test_64k_splited(struct intel_gvt_gtt_entry *e)
static void gen8_gtt_set_64k_splited(struct intel_gvt_gtt_entry *e)
static void gen8_gtt_clear_64k_splited(struct intel_gvt_gtt_entry *e)
static unsigned long gma_to_ggtt_pte_index(unsigned long gma)
define DEFINE_PPGTT_GMA_TO_INDEX(prefix, ename, exp)
\ static unsigned long prefix_gma_to_ename_index(unsigned long gma)
\static void update_entry_type_for_real(struct intel_gvt_gtt_pte_ops *pte_ops, struct intel_gvt_gtt_entry *entry, bool ips)
static void _ppgtt_get_root_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index, bool guest)
static inline void ppgtt_get_guest_root_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index)
static inline void ppgtt_get_shadow_root_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index)
static void _ppgtt_set_root_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index, bool guest)
static inline void ppgtt_set_guest_root_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index)
static inline void ppgtt_set_shadow_root_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index)
static void ggtt_get_guest_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index)
static void ggtt_set_guest_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index)
static void ggtt_get_host_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index)
static void ggtt_set_host_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *entry, unsigned long index)
static inline int ppgtt_spt_get_entry( struct intel_vgpu_ppgtt_spt *spt, void *page_table, int type, struct intel_gvt_gtt_entry *e, unsigned long index, bool guest)
static inline int ppgtt_spt_set_entry( struct intel_vgpu_ppgtt_spt *spt, void *page_table, int type, struct intel_gvt_gtt_entry *e, unsigned long index, bool guest)
static void *alloc_spt(gfp_t gfp_mask)
static void free_spt(struct intel_vgpu_ppgtt_spt *spt)
static void ppgtt_free_spt(struct intel_vgpu_ppgtt_spt *spt)
static void ppgtt_free_all_spt(struct intel_vgpu *vgpu)
static int ppgtt_write_protection_handler( struct intel_vgpu_page_track *page_track, u64 gpa, void *data, int bytes)
static struct intel_vgpu_ppgtt_spt *intel_vgpu_find_spt_by_gfn( struct intel_vgpu *vgpu, unsigned long gfn)
static inline struct intel_vgpu_ppgtt_spt *intel_vgpu_find_spt_by_mfn( struct intel_vgpu *vgpu, unsigned long mfn)
static struct intel_vgpu_ppgtt_spt *ppgtt_alloc_spt( struct intel_vgpu *vgpu, intel_gvt_gtt_type_t type)
static struct intel_vgpu_ppgtt_spt *ppgtt_alloc_spt_gfn( struct intel_vgpu *vgpu, intel_gvt_gtt_type_t type, unsigned long gfn, bool guest_pde_ips)
static inline void ppgtt_get_spt(struct intel_vgpu_ppgtt_spt *spt)
static inline int ppgtt_put_spt(struct intel_vgpu_ppgtt_spt *spt)
static int ppgtt_invalidate_spt_by_shadow_entry(struct intel_vgpu *vgpu, struct intel_gvt_gtt_entry *e)
static inline void ppgtt_invalidate_pte(struct intel_vgpu_ppgtt_spt *spt, struct intel_gvt_gtt_entry *entry)
static int ppgtt_invalidate_spt(struct intel_vgpu_ppgtt_spt *spt)
static bool vgpu_ips_enabled(struct intel_vgpu *vgpu)
static struct intel_vgpu_ppgtt_spt *ppgtt_populate_spt_by_guest_entry( struct intel_vgpu *vgpu, struct intel_gvt_gtt_entry *we)
static inline void ppgtt_generate_shadow_entry(struct intel_gvt_gtt_entry *se, struct intel_vgpu_ppgtt_spt *s, struct intel_gvt_gtt_entry *ge)
static int is_2MB_gtt_possible(struct intel_vgpu *vgpu, struct intel_gvt_gtt_entry *entry)
static int split_2MB_gtt_entry(struct intel_vgpu *vgpu, struct intel_vgpu_ppgtt_spt *spt, unsigned long index, struct intel_gvt_gtt_entry *se)
static int split_64KB_gtt_entry(struct intel_vgpu *vgpu, struct intel_vgpu_ppgtt_spt *spt, unsigned long index, struct intel_gvt_gtt_entry *se)
static int ppgtt_populate_shadow_entry(struct intel_vgpu *vgpu, struct intel_vgpu_ppgtt_spt *spt, unsigned long index, struct intel_gvt_gtt_entry *ge)
static int ppgtt_populate_spt(struct intel_vgpu_ppgtt_spt *spt)
static int ppgtt_handle_guest_entry_removal(struct intel_vgpu_ppgtt_spt *spt, struct intel_gvt_gtt_entry *se, unsigned long index)
static int ppgtt_handle_guest_entry_add(struct intel_vgpu_ppgtt_spt *spt, struct intel_gvt_gtt_entry *we, unsigned long index)
static int sync_oos_page(struct intel_vgpu *vgpu, struct intel_vgpu_oos_page *oos_page)
static int detach_oos_page(struct intel_vgpu *vgpu, struct intel_vgpu_oos_page *oos_page)
static int attach_oos_page(struct intel_vgpu_oos_page *oos_page, struct intel_vgpu_ppgtt_spt *spt)
static int ppgtt_set_guest_page_sync(struct intel_vgpu_ppgtt_spt *spt)
static int ppgtt_allocate_oos_page(struct intel_vgpu_ppgtt_spt *spt)
static int ppgtt_set_guest_page_oos(struct intel_vgpu_ppgtt_spt *spt)
int intel_vgpu_sync_oos_pages(struct intel_vgpu *vgpu)
static int ppgtt_handle_guest_write_page_table( struct intel_vgpu_ppgtt_spt *spt, struct intel_gvt_gtt_entry *we, unsigned long index)
static inline bool can_do_out_of_sync(struct intel_vgpu_ppgtt_spt *spt)
static void ppgtt_set_post_shadow(struct intel_vgpu_ppgtt_spt *spt, unsigned long index)
int intel_vgpu_flush_post_shadow(struct intel_vgpu *vgpu)
static int ppgtt_handle_guest_write_page_table_bytes( struct intel_vgpu_ppgtt_spt *spt, u64 pa, void *p_data, int bytes)
static void invalidate_ppgtt_mm(struct intel_vgpu_mm *mm)
static int shadow_ppgtt_mm(struct intel_vgpu_mm *mm)
static struct intel_vgpu_mm *vgpu_alloc_mm(struct intel_vgpu *vgpu)
static void vgpu_free_mm(struct intel_vgpu_mm *mm)
struct intel_vgpu_mm *intel_vgpu_create_ppgtt_mm(struct intel_vgpu *vgpu, intel_gvt_gtt_type_t root_entry_type, u64 pdps[])
static struct intel_vgpu_mm *intel_vgpu_create_ggtt_mm(struct intel_vgpu *vgpu)
void _intel_vgpu_mm_release(struct kref *mm_ref)
void intel_vgpu_unpin_mm(struct intel_vgpu_mm *mm)
int intel_vgpu_pin_mm(struct intel_vgpu_mm *mm)
static int reclaim_one_ppgtt_mm(struct intel_gvt *gvt)
static inline int ppgtt_get_next_level_entry(struct intel_vgpu_mm *mm, struct intel_gvt_gtt_entry *e, unsigned long index, bool guest)
unsigned long intel_vgpu_gma_to_gpa(struct intel_vgpu_mm *mm, unsigned long gma)
static int emulate_ggtt_mmio_read(struct intel_vgpu *vgpu, unsigned int off, void *p_data, unsigned int bytes)
int intel_vgpu_emulate_ggtt_mmio_read(struct intel_vgpu *vgpu, unsigned int off, void *p_data, unsigned int bytes)
static void ggtt_invalidate_pte(struct intel_vgpu *vgpu, struct intel_gvt_gtt_entry *entry)
static int emulate_ggtt_mmio_write(struct intel_vgpu *vgpu, unsigned int off, void *p_data, unsigned int bytes)
int intel_vgpu_emulate_ggtt_mmio_write(struct intel_vgpu *vgpu, unsigned int off, void *p_data, unsigned int bytes)
static int alloc_scratch_pages(struct intel_vgpu *vgpu, intel_gvt_gtt_type_t type)
static int release_scratch_page_tree(struct intel_vgpu *vgpu)
static int create_scratch_page_tree(struct intel_vgpu *vgpu)
int intel_vgpu_init_gtt(struct intel_vgpu *vgpu)
static void intel_vgpu_destroy_all_ppgtt_mm(struct intel_vgpu *vgpu)
static void intel_vgpu_destroy_ggtt_mm(struct intel_vgpu *vgpu)
void intel_vgpu_clean_gtt(struct intel_vgpu *vgpu)
static void clean_spt_oos(struct intel_gvt *gvt)
static int setup_spt_oos(struct intel_gvt *gvt)
struct intel_vgpu_mm *intel_vgpu_find_ppgtt_mm(struct intel_vgpu *vgpu, u64 pdps[])
struct intel_vgpu_mm *intel_vgpu_get_ppgtt_mm(struct intel_vgpu *vgpu, intel_gvt_gtt_type_t root_entry_type, u64 pdps[])
int intel_vgpu_put_ppgtt_mm(struct intel_vgpu *vgpu, u64 pdps[])
int intel_gvt_init_gtt(struct intel_gvt *gvt)
void intel_gvt_clean_gtt(struct intel_gvt *gvt)
void intel_vgpu_invalidate_ppgtt(struct intel_vgpu *vgpu)
void intel_vgpu_reset_ggtt(struct intel_vgpu *vgpu, bool invalidate_old)
void intel_vgpu_reset_gtt(struct intel_vgpu *vgpu)
\n
     44 struct intel_vgpu *vgpu
     24 unsigned long index
     22 struct intel_vgpu_ppgtt_spt *spt
     18 struct intel_gvt_gtt_entry *e
     17 struct intel_vgpu_mm *mm
     14 struct intel_gvt_gtt_entry *entry
      6 int type
      5 void *p_data
      5 struct intel_gvt *gvt
      5 bool guest
      4 unsigned int off
      4 unsigned int bytes
      4 u64 pdps[]
      4 struct intel_gvt_gtt_entry *se
      3 unsigned long gma
      3 struct intel_vgpu_oos_page *oos_page
      3 struct intel_gvt_gtt_entry *we
      3 struct drm_i915_private *dev_priv
      3 intel_gvt_gtt_type_t type
      2 void *pt
      2 void *page_table
      2 unsigned long gpa
      2 unsigned long gfn
      2 struct intel_gvt_gtt_entry *ge
      2 intel_gvt_gtt_type_t root_entry_type
      2 int bytes
      2 bool hypervisor_access
      1 void *data
      1 unsigned long pfn
      1 unsigned long mfn
      1 unsigned long h_index
      1 unsigned long *h_index
      1 unsigned long g_index
      1 unsigned long *g_index
      1 u64 pte
      1 u64 pa
      1 u64 h_addr
      1 u64 *h_addr
      1 u64 gpa
      1 u64 g_addr
      1 u64 *g_addr
      1 u64 addr
      1 u32 size
      1 struct kref *mm_ref
      1 struct intel_vgpu_ppgtt_spt *s
      1 struct intel_vgpu_page_track *page_track
      1 struct intel_gvt_gtt_pte_ops *pte_ops
      1 prefix
      1 gfp_t gfp_mask
      1 exp
      1 ename
      1 bool ips
      1 bool invalidate_old
      1 bool guest_pde_ips
