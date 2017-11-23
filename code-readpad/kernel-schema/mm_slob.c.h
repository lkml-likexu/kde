
static inline int slob_page_free(struct page *sp)
static void set_slob_page_free(struct page *sp, struct list_head *list)
static inline void clear_slob_page_free(struct page *sp)
static void set_slob(slob_t *s, slobidx_t size, slob_t *next)
static slobidx_t slob_units(slob_t *s)
static slob_t *slob_next(slob_t *s)
static int slob_last(slob_t *s)
static void *slob_new_pages(gfp_t gfp, int order, int node)
static void slob_free_pages(void *b, int order)
static void *slob_page_alloc(struct page *sp, size_t size, int align)
static void *slob_alloc(size_t size, gfp_t gfp, int align, int node)
static void slob_free(void *block, int size)
static __always_inline void * __do_kmalloc_node(size_t size, gfp_t gfp, int node, unsigned long caller)
void *__kmalloc(size_t size, gfp_t gfp)
void *__kmalloc_track_caller(size_t size, gfp_t gfp, unsigned long caller)
void *__kmalloc_node_track_caller(size_t size, gfp_t gfp, int node, unsigned long caller)
void kfree(const void *block)
size_t ksize(const void *block)
int __kmem_cache_create(struct kmem_cache *c, slab_flags_t flags)
static void *slob_alloc_node(struct kmem_cache *c, gfp_t flags, int node)
void *kmem_cache_alloc(struct kmem_cache *cachep, gfp_t flags)
void *__kmalloc_node(size_t size, gfp_t gfp, int node)
void *kmem_cache_alloc_node(struct kmem_cache *cachep, gfp_t gfp, int node)
static void __kmem_cache_free(void *b, int size)
static void kmem_rcu_free(struct rcu_head *head)
void kmem_cache_free(struct kmem_cache *c, void *b)
void kmem_cache_free_bulk(struct kmem_cache *s, size_t size, void **p)
int kmem_cache_alloc_bulk(struct kmem_cache *s, gfp_t flags, size_t size, void **p)
int __kmem_cache_shutdown(struct kmem_cache *c)
void __kmem_cache_release(struct kmem_cache *c)
int __kmem_cache_shrink(struct kmem_cache *d)
void __init kmem_cache_init(void)
void __init kmem_cache_init_late(void)
   9 size_t size
   8 gfp_t gfp
   7 int node
   5 struct kmem_cache *c
   4 struct page *sp
   4 slob_t *s
   3 void *b
   3 unsigned long caller
   3 gfp_t flags
   2 void **p
   2 void
   2 struct kmem_cache *s
   2 struct kmem_cache *cachep
   2 int size
   2 int order
   2 int align
   2 const void *block
   1 void *block
   1 struct rcu_head *head
   1 struct list_head *list
   1 struct kmem_cache *d
   1 slobidx_t size
   1 slob_t *next
   1 slab_flags_t flags
