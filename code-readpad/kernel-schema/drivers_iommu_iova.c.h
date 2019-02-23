
EXPORT_SYMBOL_GPL(init_iova_domain);
EXPORT_SYMBOL_GPL(init_iova_flush_queue);
EXPORT_SYMBOL_GPL(iova_cache_get);
EXPORT_SYMBOL_GPL(iova_cache_put);
EXPORT_SYMBOL_GPL(alloc_iova);
EXPORT_SYMBOL_GPL(find_iova);
EXPORT_SYMBOL_GPL(__free_iova);
EXPORT_SYMBOL_GPL(free_iova);
EXPORT_SYMBOL_GPL(alloc_iova_fast);
EXPORT_SYMBOL_GPL(free_iova_fast);
EXPORT_SYMBOL_GPL(queue_iova);
EXPORT_SYMBOL_GPL(put_iova_domain);
EXPORT_SYMBOL_GPL(reserve_iova);
EXPORT_SYMBOL_GPL(copy_reserved_iova);
\n
void init_iova_domain(struct iova_domain *iovad, unsigned long granule, unsigned long start_pfn)
static void free_iova_flush_queue(struct iova_domain *iovad)
int init_iova_flush_queue(struct iova_domain *iovad, iova_flush_cb flush_cb, iova_entry_dtor entry_dtor)
static struct rb_node * __get_cached_rbnode(struct iova_domain *iovad, unsigned long limit_pfn)
static void __cached_rbnode_insert_update(struct iova_domain *iovad, struct iova *new)
static void __cached_rbnode_delete_update(struct iova_domain *iovad, struct iova *free)
static void iova_insert_rbtree(struct rb_root *root, struct iova *iova, struct rb_node *start)
static int __alloc_and_insert_iova_range(struct iova_domain *iovad, unsigned long size, unsigned long limit_pfn, struct iova *new, bool size_aligned)
struct iova *alloc_iova_mem(void)
void free_iova_mem(struct iova *iova)
int iova_cache_get(void)
void iova_cache_put(void)
struct iova * alloc_iova(struct iova_domain *iovad, unsigned long size, unsigned long limit_pfn, bool size_aligned)
static struct iova * private_find_iova(struct iova_domain *iovad, unsigned long pfn)
static void private_free_iova(struct iova_domain *iovad, struct iova *iova)
struct iova *find_iova(struct iova_domain *iovad, unsigned long pfn)
void __free_iova(struct iova_domain *iovad, struct iova *iova)
void free_iova(struct iova_domain *iovad, unsigned long pfn)
unsigned long alloc_iova_fast(struct iova_domain *iovad, unsigned long size, unsigned long limit_pfn, bool flush_rcache)
void free_iova_fast(struct iova_domain *iovad, unsigned long pfn, unsigned long size)
static inline bool fq_full(struct iova_fq *fq)
static inline unsigned fq_ring_add(struct iova_fq *fq)
static void fq_ring_free(struct iova_domain *iovad, struct iova_fq *fq)
static void iova_domain_flush(struct iova_domain *iovad)
static void fq_destroy_all_entries(struct iova_domain *iovad)
static void fq_flush_timeout(struct timer_list *t)
void queue_iova(struct iova_domain *iovad, unsigned long pfn, unsigned long pages, unsigned long data)
void put_iova_domain(struct iova_domain *iovad)
static int __is_range_overlap(struct rb_node *node, unsigned long pfn_lo, unsigned long pfn_hi)
static inline struct iova * alloc_and_init_iova(unsigned long pfn_lo, unsigned long pfn_hi)
static struct iova * __insert_new_range(struct iova_domain *iovad, unsigned long pfn_lo, unsigned long pfn_hi)
static void __adjust_overlap_range(struct iova *iova, unsigned long *pfn_lo, unsigned long *pfn_hi)
struct iova * reserve_iova(struct iova_domain *iovad, unsigned long pfn_lo, unsigned long pfn_hi)
void copy_reserved_iova(struct iova_domain *from, struct iova_domain *to)
struct iova * split_and_remove_iova(struct iova_domain *iovad, struct iova *iova, unsigned long pfn_lo, unsigned long pfn_hi)
static struct iova_magazine *iova_magazine_alloc(gfp_t flags)
static void iova_magazine_free(struct iova_magazine *mag)
static void iova_magazine_free_pfns(struct iova_magazine *mag, struct iova_domain *iovad)
static bool iova_magazine_full(struct iova_magazine *mag)
static bool iova_magazine_empty(struct iova_magazine *mag)
static unsigned long iova_magazine_pop(struct iova_magazine *mag, unsigned long limit_pfn)
static void iova_magazine_push(struct iova_magazine *mag, unsigned long pfn)
static void init_iova_rcaches(struct iova_domain *iovad)
static bool __iova_rcache_insert(struct iova_domain *iovad, struct iova_rcache *rcache, unsigned long iova_pfn)
static bool iova_rcache_insert(struct iova_domain *iovad, unsigned long pfn, unsigned long size)
static unsigned long __iova_rcache_get(struct iova_rcache *rcache, unsigned long limit_pfn)
static unsigned long iova_rcache_get(struct iova_domain *iovad, unsigned long size, unsigned long limit_pfn)
static void free_iova_rcaches(struct iova_domain *iovad)
void free_cpu_cached_iovas(unsigned int cpu, struct iova_domain *iovad)
\n
     30 struct iova_domain *iovad
      7 unsigned long pfn
      7 unsigned long limit_pfn
      6 unsigned long size
      6 struct iova_magazine *mag
      6 struct iova *iova
      5 unsigned long pfn_lo
      5 unsigned long pfn_hi
      3 void
      3 struct iova_fq *fq
      2 struct iova_rcache *rcache
      2 struct iova *new
      2 bool size_aligned
      1 unsigned long start_pfn
      1 unsigned long *pfn_lo
      1 unsigned long *pfn_hi
      1 unsigned long pages
      1 unsigned long iova_pfn
      1 unsigned long granule
      1 unsigned long data
      1 unsigned int cpu
      1 struct timer_list *t
      1 struct rb_root *root
      1 struct rb_node *start
      1 struct rb_node *node
      1 struct iova *free
      1 struct iova_domain *to
      1 struct iova_domain *from
      1 reserve_iova
      1 queue_iova
      1 put_iova_domain
      1 iova_flush_cb flush_cb
      1 iova_entry_dtor entry_dtor
      1 iova_cache_put
      1 iova_cache_get
      1 init_iova_flush_queue
      1 init_iova_domain
      1 gfp_t flags
      1 free_iova_fast
      1 free_iova
      1 __free_iova
      1 find_iova
      1 copy_reserved_iova
      1 bool flush_rcache
      1 alloc_iova_fast
      1 alloc_iova
