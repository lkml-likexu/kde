
\n
static __always_inline enum kmalloc_cache_type kmalloc_type(gfp_t flags)
static __always_inline unsigned int kmalloc_index(size_t size)
static __always_inline void kfree_bulk(size_t size, void **p)
void *__kmalloc_node(size_t size, gfp_t flags, int node)
__assume_kmalloc_alignment __malloc; void *kmem_cache_alloc_node(struct kmem_cache *, gfp_t flags, int node)
__assume_slab_alignment __malloc; static __always_inline void *__kmalloc_node(size_t size, gfp_t flags, int node)
static __always_inline void *kmem_cache_alloc_node(struct kmem_cache *s, gfp_t flags, int node)
extern void *kmem_cache_alloc_node_trace(struct kmem_cache *s, gfp_t gfpflags, int node, size_t size)
__assume_slab_alignment __malloc; static __always_inline void * kmem_cache_alloc_node_trace(struct kmem_cache *s, gfp_t gfpflags, int node, size_t size)
static __always_inline void *kmem_cache_alloc_trace(struct kmem_cache *s, gfp_t flags, size_t size)
static __always_inline void * kmem_cache_alloc_node_trace(struct kmem_cache *s, gfp_t gfpflags, int node, size_t size)
extern void *kmalloc_order_trace(size_t size, gfp_t flags, unsigned int order)
__assume_page_alignment __malloc; static __always_inline void * kmalloc_order_trace(size_t size, gfp_t flags, unsigned int order)
static __always_inline void *kmalloc_large(size_t size, gfp_t flags)
static __always_inline void *kmalloc(size_t size, gfp_t flags)
static __always_inline unsigned int kmalloc_size(unsigned int n)
static __always_inline void *kmalloc_node(size_t size, gfp_t flags, int node)
static inline void *kmalloc_array(size_t n, size_t size, gfp_t flags)
static inline void *kcalloc(size_t n, size_t size, gfp_t flags)
static inline void *kmalloc_array_node(size_t n, size_t size, gfp_t flags, int node)
static inline void *kcalloc_node(size_t n, size_t size, gfp_t flags, int node)
static inline void *kmem_cache_zalloc(struct kmem_cache *k, gfp_t flags)
static inline void *kzalloc(size_t size, gfp_t flags)
static inline void *kzalloc_node(size_t size, gfp_t flags, int node)
\n
     19 size_t size
     18 gfp_t flags
     11 int node
      5 struct kmem_cache *s
      4 size_t n
      3 gfp_t gfpflags
      2 unsigned int order
      1 void **p
      1 unsigned int n
      1 struct kmem_cache *k
      1 struct kmem_cache *
