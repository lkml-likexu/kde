
\n
static u64 node_start(struct umem_odp_node *n)
static u64 node_last(struct umem_odp_node *n)
static void ib_umem_notifier_start_account(struct ib_umem_odp *umem_odp)
static void ib_umem_notifier_end_account(struct ib_umem_odp *umem_odp)
static int ib_umem_notifier_release_trampoline(struct ib_umem_odp *umem_odp, u64 start, u64 end, void *cookie)
static void ib_umem_notifier_release(struct mmu_notifier *mn, struct mm_struct *mm)
static int invalidate_range_start_trampoline(struct ib_umem_odp *item, u64 start, u64 end, void *cookie)
static int ib_umem_notifier_invalidate_range_start(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static int invalidate_range_end_trampoline(struct ib_umem_odp *item, u64 start, u64 end, void *cookie)
static void ib_umem_notifier_invalidate_range_end(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static void add_umem_to_per_mm(struct ib_umem_odp *umem_odp)
static void remove_umem_from_per_mm(struct ib_umem_odp *umem_odp)
static struct ib_ucontext_per_mm *alloc_per_mm(struct ib_ucontext *ctx, struct mm_struct *mm)
static int get_per_mm(struct ib_umem_odp *umem_odp)
static void free_per_mm(struct rcu_head *rcu)
void put_per_mm(struct ib_umem_odp *umem_odp)
struct ib_umem_odp *ib_alloc_odp_umem(struct ib_ucontext_per_mm *per_mm, unsigned long addr, size_t size)
int ib_umem_odp_get(struct ib_umem_odp *umem_odp, int access)
void ib_umem_odp_release(struct ib_umem_odp *umem_odp)
static int ib_umem_odp_map_dma_single_page( struct ib_umem_odp *umem_odp, int page_index, struct page *page, u64 access_mask, unsigned long current_seq)
int ib_umem_odp_map_dma_pages(struct ib_umem_odp *umem_odp, u64 user_virt, u64 bcnt, u64 access_mask, unsigned long current_seq)
void ib_umem_odp_unmap_dma_pages(struct ib_umem_odp *umem_odp, u64 virt, u64 bound)
int rbt_ib_umem_for_each_in_range(struct rb_root_cached *root, u64 start, u64 last, umem_call_back cb, bool blockable, void *cookie)
struct ib_umem_odp *rbt_ib_umem_lookup(struct rb_root_cached *root, u64 addr, u64 length)
\n
     12 struct ib_umem_odp *umem_odp
      4 void *cookie
      4 u64 start
      3 u64 end
      3 struct mmu_notifier *mn
      2 unsigned long current_seq
      2 u64 access_mask
      2 struct umem_odp_node *n
      2 struct rb_root_cached *root
      2 struct mm_struct *mm
      2 struct ib_umem_odp *item
      2 const struct mmu_notifier_range *range
      1 unsigned long addr
      1 umem_call_back cb
      1 u64 virt
      1 u64 user_virt
      1 u64 length
      1 u64 last
      1 u64 bound
      1 u64 bcnt
      1 u64 addr
      1 struct rcu_head *rcu
      1 struct page *page
      1 struct ib_ucontext_per_mm *per_mm
      1 struct ib_ucontext *ctx
      1 size_t size
      1 int page_index
      1 int access
      1 bool blockable
