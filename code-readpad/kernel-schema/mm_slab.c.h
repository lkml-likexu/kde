
static void kmem_cache_node_init(struct kmem_cache_node *parent)
static int obj_offset(struct kmem_cache *cachep)
static unsigned long long *dbg_redzone1(struct kmem_cache *cachep, void *objp)
static unsigned long long *dbg_redzone2(struct kmem_cache *cachep, void *objp)
static void **dbg_userword(struct kmem_cache *cachep, void *objp)
static inline bool is_store_user_clean(struct kmem_cache *cachep)
static inline void set_store_user_clean(struct kmem_cache *cachep)
static inline void set_store_user_dirty(struct kmem_cache *cachep)
static inline struct kmem_cache *virt_to_cache(const void *obj)
static inline void *index_to_obj(struct kmem_cache *cache, struct page *page, unsigned int idx)
static inline unsigned int obj_to_index(const struct kmem_cache *cache, const struct page *page, void *obj)
static inline struct array_cache *cpu_cache_get(struct kmem_cache *cachep)
static unsigned int cache_estimate(unsigned long gfporder, size_t buffer_size, slab_flags_t flags, size_t *left_over)
static void __slab_error(const char *function, struct kmem_cache *cachep, char *msg)
static int use_alien_caches __read_mostly = 1; static int __init noaliencache_setup(char *s)
static int __init slab_max_order_setup(char *str)
static void init_reap_node(int cpu)
static void next_reap_node(void)
static void start_cpu_timer(int cpu)
static void init_arraycache(struct array_cache *ac, int limit, int batch)
static struct array_cache *alloc_arraycache(int node, int entries, int batchcount, gfp_t gfp)
static noinline void cache_free_pfmemalloc(struct kmem_cache *cachep, struct page *page, void *objp)
static int transfer_objects(struct array_cache *to, struct array_cache *from, unsigned int max)
static inline struct alien_cache **alloc_alien_cache(int node, int limit, gfp_t gfp)
static inline void free_alien_cache(struct alien_cache **ac_ptr)
static inline int cache_free_alien(struct kmem_cache *cachep, void *objp)
static inline void *alternate_node_alloc(struct kmem_cache *cachep, gfp_t flags)
static inline void *____cache_alloc_node(struct kmem_cache *cachep, gfp_t flags, int nodeid)
static inline gfp_t gfp_exact_node(gfp_t flags)
static struct alien_cache *__alloc_alien_cache(int node, int entries, int batch, gfp_t gfp)
static struct alien_cache **alloc_alien_cache(int node, int limit, gfp_t gfp)
static void free_alien_cache(struct alien_cache **alc_ptr)
static void __drain_alien_cache(struct kmem_cache *cachep, struct array_cache *ac, int node, struct list_head *list)
static void reap_alien(struct kmem_cache *cachep, struct kmem_cache_node *n)
static void drain_alien_cache(struct kmem_cache *cachep, struct alien_cache **alien)
static int __cache_free_alien(struct kmem_cache *cachep, void *objp, int node, int page_node)
static inline int cache_free_alien(struct kmem_cache *cachep, void *objp)
static inline gfp_t gfp_exact_node(gfp_t flags)
static int init_cache_node(struct kmem_cache *cachep, int node, gfp_t gfp)
static int init_cache_node_node(int node)
static int setup_kmem_cache_node(struct kmem_cache *cachep, int node, gfp_t gfp, bool force_change)
static void cpuup_canceled(long cpu)
static int cpuup_prepare(long cpu)
int slab_prepare_cpu(unsigned int cpu)
int slab_dead_cpu(unsigned int cpu)
static int slab_online_cpu(unsigned int cpu)
static int slab_offline_cpu(unsigned int cpu)
static int __meminit drain_cache_node_node(int node)
static int __meminit slab_memory_callback(struct notifier_block *self, unsigned long action, void *arg)
static void __init init_list(struct kmem_cache *cachep, struct kmem_cache_node *list, int nodeid)
static void __init set_up_node(struct kmem_cache *cachep, int index)
void __init kmem_cache_init(void)
void __init kmem_cache_init_late(void)
static int __init cpucache_init(void)
static noinline void slab_out_of_memory(struct kmem_cache *cachep, gfp_t gfpflags, int nodeid)
static struct page *kmem_getpages(struct kmem_cache *cachep, gfp_t flags, int nodeid)
static void kmem_freepages(struct kmem_cache *cachep, struct page *page)
static void kmem_rcu_free(struct rcu_head *head)
static bool is_debug_pagealloc_cache(struct kmem_cache *cachep)
static void store_stackinfo(struct kmem_cache *cachep, unsigned long *addr, unsigned long caller)
static void slab_kernel_map(struct kmem_cache *cachep, void *objp, int map, unsigned long caller)
static void poison_obj(struct kmem_cache *cachep, void *addr, unsigned char val)
static void dump_line(char *data, int offset, int limit)
static void print_objinfo(struct kmem_cache *cachep, void *objp, int lines)
static void check_poison_obj(struct kmem_cache *cachep, void *objp)
static void slab_destroy_debugcheck(struct kmem_cache *cachep, struct page *page)
check_poison_obj(cachep, objp)
;slab_kernel_map(cachep, objp, 1, 0)
; }if (*dbg_redzone1(cachep, objp)
!= RED_INACTIVE)
slab_error(cachep, "start of a freed object was overwritten")
;if (*dbg_redzone2(cachep, objp)
!= RED_INACTIVE)
slab_error(cachep, "end of a freed object was overwritten")
; }} } static void slab_destroy_debugcheck(struct kmem_cache *cachep, struct page *page)
static void slab_destroy(struct kmem_cache *cachep, struct page *page)
static void slabs_destroy(struct kmem_cache *cachep, struct list_head *list)
static size_t calculate_slab_order(struct kmem_cache *cachep, size_t size, slab_flags_t flags)
static struct array_cache __percpu *alloc_kmem_cache_cpus( struct kmem_cache *cachep, int entries, int batchcount)
static int __ref setup_cpu_cache(struct kmem_cache *cachep, gfp_t gfp)
slab_flags_t kmem_cache_flags(unsigned int object_size, slab_flags_t flags, const char *name, void (*ctor)
(void *)
)
struct kmem_cache * __kmem_cache_alias(const char *name, unsigned int size, unsigned int align, slab_flags_t flags, void (*ctor)
(void *)
)
static bool set_objfreelist_slab_cache(struct kmem_cache *cachep, size_t size, slab_flags_t flags)
static bool set_off_slab_cache(struct kmem_cache *cachep, size_t size, slab_flags_t flags)
static bool set_on_slab_cache(struct kmem_cache *cachep, size_t size, slab_flags_t flags)
int __kmem_cache_create(struct kmem_cache *cachep, slab_flags_t flags)
static void check_irq_off(void)
static void check_irq_on(void)
static void check_mutex_acquired(void)
static void check_spinlock_acquired(struct kmem_cache *cachep)
static void check_spinlock_acquired_node(struct kmem_cache *cachep, int node)
static void drain_array_locked(struct kmem_cache *cachep, struct array_cache *ac, int node, bool free_all, struct list_head *list)
static void do_drain(void *arg)
static void drain_cpu_caches(struct kmem_cache *cachep)
static int drain_freelist(struct kmem_cache *cache, struct kmem_cache_node *n, int tofree)
bool __kmem_cache_empty(struct kmem_cache *s)
int __kmem_cache_shrink(struct kmem_cache *cachep)
void __kmemcg_cache_deactivate(struct kmem_cache *cachep)
int __kmem_cache_shutdown(struct kmem_cache *cachep)
void __kmem_cache_release(struct kmem_cache *cachep)
static void *alloc_slabmgmt(struct kmem_cache *cachep, struct page *page, int colour_off, gfp_t local_flags, int nodeid)
static inline freelist_idx_t get_free_obj(struct page *page, unsigned int idx)
static inline void set_free_obj(struct page *page, unsigned int idx, freelist_idx_t val)
static void cache_init_objs_debug(struct kmem_cache *cachep, struct page *page)
static bool freelist_state_initialize(union freelist_init_state *state, struct kmem_cache *cachep, unsigned int count)
static freelist_idx_t next_random_slot(union freelist_init_state *state)
static void swap_free_obj(struct page *page, unsigned int a, unsigned int b)
static bool shuffle_freelist(struct kmem_cache *cachep, struct page *page)
return true; } static inline bool shuffle_freelist(struct kmem_cache *cachep, struct page *page)
static void cache_init_objs(struct kmem_cache *cachep, struct page *page)
static void *slab_get_obj(struct kmem_cache *cachep, struct page *page)
static void slab_put_obj(struct kmem_cache *cachep, struct page *page, void *objp)
static void slab_map_pages(struct kmem_cache *cache, struct page *page, void *freelist)
static struct page *cache_grow_begin(struct kmem_cache *cachep, gfp_t flags, int nodeid)
static void cache_grow_end(struct kmem_cache *cachep, struct page *page)
static void kfree_debugcheck(const void *objp)
static inline void verify_redzone_free(struct kmem_cache *cache, void *obj)
static void *cache_free_debugcheck(struct kmem_cache *cachep, void *objp, unsigned long caller)
static inline void fixup_objfreelist_debug(struct kmem_cache *cachep, void **list)
static inline void fixup_slab_list(struct kmem_cache *cachep, struct kmem_cache_node *n, struct page *page, void **list)
static noinline struct page *get_valid_first_slab(struct kmem_cache_node *n, struct page *page, bool pfmemalloc)
static struct page *get_first_slab(struct kmem_cache_node *n, bool pfmemalloc)
static noinline void *cache_alloc_pfmemalloc(struct kmem_cache *cachep, struct kmem_cache_node *n, gfp_t flags)
static __always_inline int alloc_block(struct kmem_cache *cachep, struct array_cache *ac, struct page *page, int batchcount)
static void *cache_alloc_refill(struct kmem_cache *cachep, gfp_t flags)
static inline void cache_alloc_debugcheck_before(struct kmem_cache *cachep, gfp_t flags)
static void *cache_alloc_debugcheck_after(struct kmem_cache *cachep, gfp_t flags, void *objp, unsigned long caller)
static inline void *____cache_alloc(struct kmem_cache *cachep, gfp_t flags)
static void *alternate_node_alloc(struct kmem_cache *cachep, gfp_t flags)
static void *fallback_alloc(struct kmem_cache *cache, gfp_t flags)
static void *____cache_alloc_node(struct kmem_cache *cachep, gfp_t flags, int nodeid)
static __always_inline void * slab_alloc_node(struct kmem_cache *cachep, gfp_t flags, int nodeid, unsigned long caller)
static __always_inline void * __do_cache_alloc(struct kmem_cache *cache, gfp_t flags)
static __always_inline void * __do_cache_alloc(struct kmem_cache *cachep, gfp_t flags)
static __always_inline void * slab_alloc(struct kmem_cache *cachep, gfp_t flags, unsigned long caller)
static void free_block(struct kmem_cache *cachep, void **objpp, int nr_objects, int node, struct list_head *list)
static void cache_flusharray(struct kmem_cache *cachep, struct array_cache *ac)
static __always_inline void __cache_free(struct kmem_cache *cachep, void *objp, unsigned long caller)
void ___cache_free(struct kmem_cache *cachep, void *objp, unsigned long caller)
void *kmem_cache_alloc(struct kmem_cache *cachep, gfp_t flags)
static __always_inline void cache_alloc_debugcheck_after_bulk(struct kmem_cache *s, gfp_t flags, size_t size, void **p, unsigned long caller)
int kmem_cache_alloc_bulk(struct kmem_cache *s, gfp_t flags, size_t size, void **p)
void * kmem_cache_alloc_trace(struct kmem_cache *cachep, gfp_t flags, size_t size)
void *kmem_cache_alloc_node(struct kmem_cache *cachep, gfp_t flags, int nodeid)
void *kmem_cache_alloc_node_trace(struct kmem_cache *cachep, gfp_t flags, int nodeid, size_t size)
static __always_inline void * __do_kmalloc_node(size_t size, gfp_t flags, int node, unsigned long caller)
void *__kmalloc_node(size_t size, gfp_t flags, int node)
void *__kmalloc_node_track_caller(size_t size, gfp_t flags, int node, unsigned long caller)
static __always_inline void *__do_kmalloc(size_t size, gfp_t flags, unsigned long caller)
void *__kmalloc(size_t size, gfp_t flags)
void *__kmalloc_track_caller(size_t size, gfp_t flags, unsigned long caller)
void kmem_cache_free(struct kmem_cache *cachep, void *objp)
void kmem_cache_free_bulk(struct kmem_cache *orig_s, size_t size, void **p)
void kfree(const void *objp)
static int setup_kmem_cache_nodes(struct kmem_cache *cachep, gfp_t gfp)
static int __do_tune_cpucache(struct kmem_cache *cachep, int limit, int batchcount, int shared, gfp_t gfp)
static int do_tune_cpucache(struct kmem_cache *cachep, int limit, int batchcount, int shared, gfp_t gfp)
static int enable_cpucache(struct kmem_cache *cachep, gfp_t gfp)
static void drain_array(struct kmem_cache *cachep, struct kmem_cache_node *n, struct array_cache *ac, int node)
static void cache_reap(struct work_struct *w)
void get_slabinfo(struct kmem_cache *cachep, struct slabinfo *sinfo)
void slabinfo_show_stats(struct seq_file *m, struct kmem_cache *cachep)
define MAX_SLABINFO_WRITE 128ssize_t slabinfo_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
static inline int add_caller(unsigned long *n, unsigned long v)
static void handle_slab(unsigned long *n, struct kmem_cache *c, struct page *page)
static void show_symbol(struct seq_file *m, unsigned long address)
static int leaks_show(struct seq_file *m, void *p)
static int slabstats_open(struct inode *inode, struct file *file)
static int __init slab_proc_init(void)
void __check_heap_object(const void *ptr, unsigned long n, struct page *page, bool to_user)
size_t ksize(const void *objp)
  90 struct kmem_cache *cachep
  30 gfp_t flags
  23 struct page *page
  17 int node
  16 void *objp
  15 size_t size
  13 unsigned long caller
  11 gfp_t gfp
  10 int nodeid
   8 void
   8 slab_flags_t flags
   7 struct kmem_cache_node *n
   6 struct kmem_cache *cache
   6 struct array_cache *ac
   6 int limit
   5 int batchcount
   4 unsigned int cpu
   4 struct list_head *list
   4 objp
   4 cachep
   3 void **p
   3 unsigned int idx
   3 struct seq_file *m
   3 struct kmem_cache *s
   3 int entries
   3 const void *objp
   2 void *obj
   2 void *ctor
   2 void *arg
   2 void **list
   2 void *
   2 unsigned long *n
   2 union freelist_init_state *state
   2 struct file *file
   2 long cpu
   2 int shared
   2 int cpu
   2 int batch
   2 const char *name
   2 bool pfmemalloc
   1 void *p
   1 void *freelist
   1 void *addr
   1 void **objpp
   1 unsigned long v
   1 unsigned long n
   1 unsigned long gfporder
   1 unsigned long address
   1 unsigned long action
   1 unsigned long *addr
   1 unsigned int size
   1 unsigned int object_size
   1 unsigned int max
   1 unsigned int count
   1 unsigned int b
   1 unsigned int align
   1 unsigned int a
   1 unsigned char val
   1 struct work_struct *w
   1 struct slabinfo *sinfo
   1 struct rcu_head *head
   1 struct notifier_block *self
   1 struct kmem_cache_node *parent
   1 struct kmem_cache_node *list
   1 struct kmem_cache *orig_s
   1 struct kmem_cache *c
   1 struct inode *inode
   1 struct array_cache *to
   1 struct array_cache *from
   1 struct alien_cache **alien
   1 struct alien_cache **alc_ptr
   1 struct alien_cache **ac_ptr
   1 size_t count
   1 size_t buffer_size
   1 size_t *left_over
   1 loff_t *ppos
   1 int tofree
   1 int page_node
   1 int offset
   1 int nr_objects
   1 int map
   1 int lines
   1 int index
   1 int colour_off
   1 gfp_t local_flags
   1 gfp_t gfpflags
   1 freelist_idx_t val
   1 const void *ptr
   1 const void *obj
   1 const struct page *page
   1 const struct kmem_cache *cache
   1 const char __user *buffer
   1 const char *function
   1 char *str
   1 char *s
   1 char *msg
   1 char *data
   1 bool to_user
   1 bool free_all
   1 bool force_change
   1 1
   1 0
   1 *dbg_redzone2cachep
   1 *dbg_redzone1cachep
   1 "start of a freed object was overwritten"
   1 "end of a freed object was overwritten"
