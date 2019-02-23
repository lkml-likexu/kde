
EXPORT_SYMBOL_GPL(gmap_create);
EXPORT_SYMBOL_GPL(gmap_get);
EXPORT_SYMBOL_GPL(gmap_put);
EXPORT_SYMBOL_GPL(gmap_remove);
EXPORT_SYMBOL_GPL(gmap_enable);
EXPORT_SYMBOL_GPL(gmap_disable);
EXPORT_SYMBOL_GPL(gmap_get_enabled);
EXPORT_SYMBOL_GPL(gmap_unmap_segment);
EXPORT_SYMBOL_GPL(gmap_map_segment);
EXPORT_SYMBOL_GPL(__gmap_translate);
EXPORT_SYMBOL_GPL(gmap_translate);
EXPORT_SYMBOL_GPL(gmap_fault);
EXPORT_SYMBOL_GPL(__gmap_zap);
EXPORT_SYMBOL_GPL(gmap_discard);
EXPORT_SYMBOL_GPL(gmap_register_pte_notifier);
EXPORT_SYMBOL_GPL(gmap_unregister_pte_notifier);
EXPORT_SYMBOL_GPL(gmap_mprotect_notify);
EXPORT_SYMBOL_GPL(gmap_read_table);
EXPORT_SYMBOL_GPL(gmap_shadow_valid);
EXPORT_SYMBOL_GPL(gmap_shadow);
EXPORT_SYMBOL_GPL(gmap_shadow_r2t);
EXPORT_SYMBOL_GPL(gmap_shadow_r3t);
EXPORT_SYMBOL_GPL(gmap_shadow_sgt);
EXPORT_SYMBOL_GPL(gmap_shadow_pgt_lookup);
EXPORT_SYMBOL_GPL(gmap_shadow_pgt);
EXPORT_SYMBOL_GPL(gmap_shadow_page);
EXPORT_SYMBOL_GPL(ptep_notify);
EXPORT_SYMBOL_GPL(gmap_pmdp_invalidate);
EXPORT_SYMBOL_GPL(gmap_pmdp_csp);
EXPORT_SYMBOL_GPL(gmap_pmdp_idte_local);
EXPORT_SYMBOL_GPL(gmap_pmdp_idte_global);
EXPORT_SYMBOL_GPL(gmap_sync_dirty_log_pmd);
EXPORT_SYMBOL_GPL(s390_enable_sie);
EXPORT_SYMBOL_GPL(s390_enable_skey);
EXPORT_SYMBOL_GPL(s390_reset_cmma);
\n
static struct gmap *gmap_alloc(unsigned long limit)
struct gmap *gmap_create(struct mm_struct *mm, unsigned long limit)
static void gmap_flush_tlb(struct gmap *gmap)
static void gmap_radix_tree_free(struct radix_tree_root *root)
static void gmap_rmap_radix_tree_free(struct radix_tree_root *root)
static void gmap_free(struct gmap *gmap)
struct gmap *gmap_get(struct gmap *gmap)
void gmap_put(struct gmap *gmap)
void gmap_remove(struct gmap *gmap)
void gmap_enable(struct gmap *gmap)
void gmap_disable(struct gmap *gmap)
struct gmap *gmap_get_enabled(void)
static int gmap_alloc_table(struct gmap *gmap, unsigned long *table, unsigned long init, unsigned long gaddr)
static unsigned long __gmap_segment_gaddr(unsigned long *entry)
static int __gmap_unlink_by_vmaddr(struct gmap *gmap, unsigned long vmaddr)
static int __gmap_unmap_by_gaddr(struct gmap *gmap, unsigned long gaddr)
int gmap_unmap_segment(struct gmap *gmap, unsigned long to, unsigned long len)
int gmap_map_segment(struct gmap *gmap, unsigned long from, unsigned long to, unsigned long len)
unsigned long __gmap_translate(struct gmap *gmap, unsigned long gaddr)
unsigned long gmap_translate(struct gmap *gmap, unsigned long gaddr)
void gmap_unlink(struct mm_struct *mm, unsigned long *table, unsigned long vmaddr)
int __gmap_link(struct gmap *gmap, unsigned long gaddr, unsigned long vmaddr)
int gmap_fault(struct gmap *gmap, unsigned long gaddr, unsigned int fault_flags)
void __gmap_zap(struct gmap *gmap, unsigned long gaddr)
void gmap_discard(struct gmap *gmap, unsigned long from, unsigned long to)
void gmap_register_pte_notifier(struct gmap_notifier *nb)
void gmap_unregister_pte_notifier(struct gmap_notifier *nb)
static void gmap_call_notifier(struct gmap *gmap, unsigned long start, unsigned long end)
static inline unsigned long *gmap_table_walk(struct gmap *gmap, unsigned long gaddr, int level)
static pte_t *gmap_pte_op_walk(struct gmap *gmap, unsigned long gaddr, spinlock_t **ptl)
static int gmap_pte_op_fixup(struct gmap *gmap, unsigned long gaddr, unsigned long vmaddr, int prot)
static void gmap_pte_op_end(spinlock_t *ptl)
static inline pmd_t *gmap_pmd_op_walk(struct gmap *gmap, unsigned long gaddr)
static inline void gmap_pmd_op_end(struct gmap *gmap, pmd_t *pmdp)
static int gmap_protect_pmd(struct gmap *gmap, unsigned long gaddr, pmd_t *pmdp, int prot, unsigned long bits)
static int gmap_protect_pte(struct gmap *gmap, unsigned long gaddr, pmd_t *pmdp, int prot, unsigned long bits)
static int gmap_protect_range(struct gmap *gmap, unsigned long gaddr, unsigned long len, int prot, unsigned long bits)
int gmap_mprotect_notify(struct gmap *gmap, unsigned long gaddr, unsigned long len, int prot)
int gmap_read_table(struct gmap *gmap, unsigned long gaddr, unsigned long *val)
static inline void gmap_insert_rmap(struct gmap *sg, unsigned long vmaddr, struct gmap_rmap *rmap)
static int gmap_protect_rmap(struct gmap *sg, unsigned long raddr, unsigned long paddr, unsigned long len)
static inline void gmap_idte_one(unsigned long asce, unsigned long vaddr)
static void gmap_unshadow_page(struct gmap *sg, unsigned long raddr)
static void __gmap_unshadow_pgt(struct gmap *sg, unsigned long raddr, unsigned long *pgt)
static void gmap_unshadow_pgt(struct gmap *sg, unsigned long raddr)
static void __gmap_unshadow_sgt(struct gmap *sg, unsigned long raddr, unsigned long *sgt)
static void gmap_unshadow_sgt(struct gmap *sg, unsigned long raddr)
static void __gmap_unshadow_r3t(struct gmap *sg, unsigned long raddr, unsigned long *r3t)
static void gmap_unshadow_r3t(struct gmap *sg, unsigned long raddr)
static void __gmap_unshadow_r2t(struct gmap *sg, unsigned long raddr, unsigned long *r2t)
static void gmap_unshadow_r2t(struct gmap *sg, unsigned long raddr)
static void __gmap_unshadow_r1t(struct gmap *sg, unsigned long raddr, unsigned long *r1t)
static void gmap_unshadow(struct gmap *sg)
static struct gmap *gmap_find_shadow(struct gmap *parent, unsigned long asce, int edat_level)
int gmap_shadow_valid(struct gmap *sg, unsigned long asce, int edat_level)
struct gmap *gmap_shadow(struct gmap *parent, unsigned long asce, int edat_level)
int gmap_shadow_r2t(struct gmap *sg, unsigned long saddr, unsigned long r2t, int fake)
int gmap_shadow_r3t(struct gmap *sg, unsigned long saddr, unsigned long r3t, int fake)
int gmap_shadow_sgt(struct gmap *sg, unsigned long saddr, unsigned long sgt, int fake)
int gmap_shadow_pgt_lookup(struct gmap *sg, unsigned long saddr, unsigned long *pgt, int *dat_protection, int *fake)
int gmap_shadow_pgt(struct gmap *sg, unsigned long saddr, unsigned long pgt, int fake)
int gmap_shadow_page(struct gmap *sg, unsigned long saddr, pte_t pte)
static void gmap_shadow_notify(struct gmap *sg, unsigned long vmaddr, unsigned long gaddr)
void ptep_notify(struct mm_struct *mm, unsigned long vmaddr, pte_t *pte, unsigned long bits)
static void pmdp_notify_gmap(struct gmap *gmap, pmd_t *pmdp, unsigned long gaddr)
static void gmap_pmdp_xchg(struct gmap *gmap, pmd_t *pmdp, pmd_t new, unsigned long gaddr)
static void gmap_pmdp_clear(struct mm_struct *mm, unsigned long vmaddr, int purge)
void gmap_pmdp_invalidate(struct mm_struct *mm, unsigned long vmaddr)
void gmap_pmdp_csp(struct mm_struct *mm, unsigned long vmaddr)
void gmap_pmdp_idte_local(struct mm_struct *mm, unsigned long vmaddr)
void gmap_pmdp_idte_global(struct mm_struct *mm, unsigned long vmaddr)
bool gmap_test_and_clear_dirty_pmd(struct gmap *gmap, pmd_t *pmdp, unsigned long gaddr)
void gmap_sync_dirty_log_pmd(struct gmap *gmap, unsigned long bitmap[4], unsigned long gaddr, unsigned long vmaddr)
static inline void thp_split_mm(struct mm_struct *mm)
static int __zap_zero_pages(pmd_t *pmd, unsigned long start, unsigned long end, struct mm_walk *walk)
static inline void zap_zero_pages(struct mm_struct *mm)
int s390_enable_sie(void)
static int __s390_enable_skey_pte(pte_t *pte, unsigned long addr, unsigned long next, struct mm_walk *walk)
static int __s390_enable_skey_hugetlb(pte_t *pte, unsigned long addr, unsigned long hmask, unsigned long next, struct mm_walk *walk)
int s390_enable_skey(void)
static int __s390_reset_cmma(pte_t *pte, unsigned long addr, unsigned long next, struct mm_walk *walk)
void s390_reset_cmma(struct mm_struct *mm)
\n
     33 struct gmap *gmap
     21 unsigned long gaddr
     21 struct gmap *sg
     13 unsigned long vmaddr
     11 unsigned long raddr
     11 struct mm_struct *mm
      6 unsigned long saddr
      6 pmd_t *pmdp
      5 unsigned long len
      5 int prot
      4 unsigned long bits
      4 unsigned long asce
      4 struct mm_walk *walk
      4 pte_t *pte
      4 int fake
      3 void
      3 unsigned long to
      3 unsigned long next
      3 unsigned long addr
      3 int edat_level
      2 unsigned long *table
      2 unsigned long start
      2 unsigned long *pgt
      2 unsigned long limit
      2 unsigned long from
      2 unsigned long end
      2 struct radix_tree_root *root
      2 struct gmap *parent
      2 struct gmap_notifier *nb
      1 unsigned long *val
      1 unsigned long vaddr
      1 unsigned long *sgt
      1 unsigned long sgt
      1 unsigned long *r3t
      1 unsigned long r3t
      1 unsigned long *r2t
      1 unsigned long r2t
      1 unsigned long *r1t
      1 unsigned long pgt
      1 unsigned long paddr
      1 unsigned long init
      1 unsigned long hmask
      1 unsigned long *entry
      1 unsigned long bitmap[4]
      1 unsigned int fault_flags
      1 struct gmap_rmap *rmap
      1 spinlock_t **ptl
      1 spinlock_t *ptl
      1 s390_reset_cmma
      1 s390_enable_skey
      1 s390_enable_sie
      1 pte_t pte
      1 ptep_notify
      1 pmd_t *pmd
      1 pmd_t new
      1 int purge
      1 int level
      1 int *fake
      1 int *dat_protection
      1 __gmap_zap
      1 gmap_unregister_pte_notifier
      1 gmap_unmap_segment
      1 gmap_translate
      1 __gmap_translate
      1 gmap_sync_dirty_log_pmd
      1 gmap_shadow_valid
      1 gmap_shadow_sgt
      1 gmap_shadow_r3t
      1 gmap_shadow_r2t
      1 gmap_shadow_pgt_lookup
      1 gmap_shadow_pgt
      1 gmap_shadow_page
      1 gmap_shadow
      1 gmap_remove
      1 gmap_register_pte_notifier
      1 gmap_read_table
      1 gmap_put
      1 gmap_pmdp_invalidate
      1 gmap_pmdp_idte_local
      1 gmap_pmdp_idte_global
      1 gmap_pmdp_csp
      1 gmap_mprotect_notify
      1 gmap_map_segment
      1 gmap_get_enabled
      1 gmap_get
      1 gmap_fault
      1 gmap_enable
      1 gmap_discard
      1 gmap_disable
      1 gmap_create
