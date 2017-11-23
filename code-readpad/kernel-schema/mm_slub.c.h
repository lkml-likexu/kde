
static inline int kmem_cache_debug(struct kmem_cache *s)
void *fixup_red_left(struct kmem_cache *s, void *p)
static inline bool kmem_cache_has_cpu_partial(struct kmem_cache *s)
static inline void stat(const struct kmem_cache *s, enum stat_item si)
static inline void *freelist_ptr(const struct kmem_cache *s, void *ptr, unsigned long ptr_addr)
static inline void *freelist_dereference(const struct kmem_cache *s, void *ptr_addr)
static inline void *get_freepointer(struct kmem_cache *s, void *object)
static void prefetch_freepointer(const struct kmem_cache *s, void *object)
static inline void *get_freepointer_safe(struct kmem_cache *s, void *object)
static inline void set_freepointer(struct kmem_cache *s, void *object, void *fp)
static inline unsigned int slab_index(void *p, struct kmem_cache *s, void *addr)
static inline unsigned int order_objects(unsigned int order, unsigned int size)
static inline struct kmem_cache_order_objects oo_make(unsigned int order, unsigned int size)
static inline unsigned int oo_order(struct kmem_cache_order_objects x)
static inline unsigned int oo_objects(struct kmem_cache_order_objects x)
static __always_inline void slab_lock(struct page *page)
static __always_inline void slab_unlock(struct page *page)
static inline bool __cmpxchg_double_slab(struct kmem_cache *s, struct page *page, void *freelist_old, unsigned long counters_old, void *freelist_new, unsigned long counters_new, const char *n)
static inline bool cmpxchg_double_slab(struct kmem_cache *s, struct page *page, void *freelist_old, unsigned long counters_old, void *freelist_new, unsigned long counters_new, const char *n)
static void get_map(struct kmem_cache *s, struct page *page, unsigned long *map)
static inline unsigned int size_from_object(struct kmem_cache *s)
static inline void *restore_red_left(struct kmem_cache *s, void *p)
static inline void metadata_access_enable(void)
static inline void metadata_access_disable(void)
static inline int check_valid_pointer(struct kmem_cache *s, struct page *page, void *object)
static void print_section(char *level, char *text, u8 *addr, unsigned int length)
static struct track *get_track(struct kmem_cache *s, void *object, enum track_item alloc)
static void set_track(struct kmem_cache *s, void *object, enum track_item alloc, unsigned long addr)
static void init_tracking(struct kmem_cache *s, void *object)
static void print_track(const char *s, struct track *t, unsigned long pr_time)
static void print_tracking(struct kmem_cache *s, void *object)
static void print_page_info(struct page *page)
static void slab_bug(struct kmem_cache *s, char *fmt, ...)
static void slab_fix(struct kmem_cache *s, char *fmt, ...)
static void print_trailer(struct kmem_cache *s, struct page *page, u8 *p)
void object_err(struct kmem_cache *s, struct page *page, u8 *object, char *reason)
static __printf(3, 4)
void slab_err(struct kmem_cache *s, struct page *page, const char *fmt, ...)
static void init_object(struct kmem_cache *s, void *object, u8 val)
static void restore_bytes(struct kmem_cache *s, char *message, u8 data, void *from, void *to)
static int check_bytes_and_report(struct kmem_cache *s, struct page *page, u8 *object, char *what, u8 *start, unsigned int value, unsigned int bytes)
static int check_pad_bytes(struct kmem_cache *s, struct page *page, u8 *p)
static int slab_pad_check(struct kmem_cache *s, struct page *page)
static int check_object(struct kmem_cache *s, struct page *page, void *object, u8 val)
static int check_slab(struct kmem_cache *s, struct page *page)
static int on_freelist(struct kmem_cache *s, struct page *page, void *search)
static void trace(struct kmem_cache *s, struct page *page, void *object, int alloc)
static void add_full(struct kmem_cache *s, struct kmem_cache_node *n, struct page *page)
static void remove_full(struct kmem_cache *s, struct kmem_cache_node *n, struct page *page)
static inline unsigned long slabs_node(struct kmem_cache *s, int node)
static inline unsigned long node_nr_slabs(struct kmem_cache_node *n)
static inline void inc_slabs_node(struct kmem_cache *s, int node, int objects)
atomic_long_inc(&n->nr_slabs)
; atomic_long_add(objects, &n->total_objects)
;} } static inline void dec_slabs_node(struct kmem_cache *s, int node, int objects)
static void setup_object_debug(struct kmem_cache *s, struct page *page, void *object)
static inline int alloc_consistency_checks(struct kmem_cache *s, struct page *page, void *object, unsigned long addr)
static noinline int alloc_debug_processing(struct kmem_cache *s, struct page *page, void *object, unsigned long addr)
static inline int free_consistency_checks(struct kmem_cache *s, struct page *page, void *object, unsigned long addr)
static noinline int free_debug_processing(struct kmem_cache *s, struct page *page, void *head, void *tail, int bulk_cnt, unsigned long addr)
static int __init setup_slub_debug(char *str)
slab_flags_t kmem_cache_flags(unsigned int object_size, slab_flags_t flags, const char *name, void (*ctor)
(void *)
)
static inline int slab_pad_check(struct kmem_cache *s, struct page *page)
static inline int check_object(struct kmem_cache *s, struct page *page, static inline void add_full(struct kmem_cache *s, struct kmem_cache_node *n, static inline void remove_full(struct kmem_cache *s, struct kmem_cache_node *n, slab_flags_t kmem_cache_flags(unsigned int object_size, slab_flags_t flags, const char *name, void (*ctor)
(void *)
)
static inline void kmalloc_large_node_hook(void *ptr, size_t size, gfp_t flags)
static __always_inline void kfree_hook(void *x)
static __always_inline bool slab_free_hook(struct kmem_cache *s, void *x)
static inline bool slab_free_freelist_hook(struct kmem_cache *s, void **head, void **tail)
static void setup_object(struct kmem_cache *s, struct page *page, void *object)
static inline struct page *alloc_slab_page(struct kmem_cache *s, gfp_t flags, int node, struct kmem_cache_order_objects oo)
static int init_cache_random_seq(struct kmem_cache *s)
static void __init init_freelist_randomization(void)
static void *next_freelist_entry(struct kmem_cache *s, struct page *page, unsigned long *pos, void *start, unsigned long page_limit, unsigned long freelist_count)
static bool shuffle_freelist(struct kmem_cache *s, struct page *page)
return true; } static inline int init_cache_random_seq(struct kmem_cache *s)
return true; } static inline int init_cache_random_seq(struct kmem_cache *s)
return 0; } static inline bool shuffle_freelist(struct kmem_cache *s, struct page *page)
static struct page *allocate_slab(struct kmem_cache *s, gfp_t flags, int node)
static struct page *new_slab(struct kmem_cache *s, gfp_t flags, int node)
static void __free_slab(struct kmem_cache *s, struct page *page)
static void rcu_free_slab(struct rcu_head *h)
static void free_slab(struct kmem_cache *s, struct page *page)
static void discard_slab(struct kmem_cache *s, struct page *page)
static inline void __add_partial(struct kmem_cache_node *n, struct page *page, int tail)
static inline void add_partial(struct kmem_cache_node *n, struct page *page, int tail)
static inline void remove_partial(struct kmem_cache_node *n, struct page *page)
static inline void *acquire_slab(struct kmem_cache *s, struct kmem_cache_node *n, struct page *page, int mode, int *objects)
static void *get_partial_node(struct kmem_cache *s, struct kmem_cache_node *n, struct kmem_cache_cpu *c, gfp_t flags)
static void *get_any_partial(struct kmem_cache *s, gfp_t flags, struct kmem_cache_cpu *c)
static void *get_partial(struct kmem_cache *s, gfp_t flags, int node, struct kmem_cache_cpu *c)
static inline unsigned long next_tid(unsigned long tid)
static inline unsigned int tid_to_cpu(unsigned long tid)
static inline unsigned long tid_to_event(unsigned long tid)
static inline unsigned int init_tid(int cpu)
static inline void note_cmpxchg_failure(const char *n, const struct kmem_cache *s, unsigned long tid)
static void init_kmem_cache_cpus(struct kmem_cache *s)
static void deactivate_slab(struct kmem_cache *s, struct page *page, void *freelist, struct kmem_cache_cpu *c)
static void unfreeze_partials(struct kmem_cache *s, struct kmem_cache_cpu *c)
static void put_cpu_partial(struct kmem_cache *s, struct page *page, int drain)
static inline void flush_slab(struct kmem_cache *s, struct kmem_cache_cpu *c)
static inline void __flush_cpu_slab(struct kmem_cache *s, int cpu)
static void flush_cpu_slab(void *d)
static bool has_cpu_slab(int cpu, void *info)
static void flush_all(struct kmem_cache *s)
static int slub_cpu_dead(unsigned int cpu)
static inline int node_match(struct page *page, int node)
static int count_free(struct page *page)
static inline unsigned long node_nr_objs(struct kmem_cache_node *n)
static unsigned long count_partial(struct kmem_cache_node *n, int (*get_count)
(struct page *)
)
static noinline void slab_out_of_memory(struct kmem_cache *s, gfp_t gfpflags, int nid)
static inline void *new_slab_objects(struct kmem_cache *s, gfp_t flags, int node, struct kmem_cache_cpu **pc)
static inline bool pfmemalloc_match(struct page *page, gfp_t gfpflags)
static inline void *get_freelist(struct kmem_cache *s, struct page *page)
static void *___slab_alloc(struct kmem_cache *s, gfp_t gfpflags, int node, unsigned long addr, struct kmem_cache_cpu *c)
static void *__slab_alloc(struct kmem_cache *s, gfp_t gfpflags, int node, unsigned long addr, struct kmem_cache_cpu *c)
static __always_inline void *slab_alloc_node(struct kmem_cache *s, gfp_t gfpflags, int node, unsigned long addr)
static __always_inline void *slab_alloc(struct kmem_cache *s, gfp_t gfpflags, unsigned long addr)
void *kmem_cache_alloc(struct kmem_cache *s, gfp_t gfpflags)
void *kmem_cache_alloc_trace(struct kmem_cache *s, gfp_t gfpflags, size_t size)
void *kmem_cache_alloc_node(struct kmem_cache *s, gfp_t gfpflags, int node)
void *kmem_cache_alloc_node_trace(struct kmem_cache *s, gfp_t gfpflags, int node, size_t size)
static __always_inline void do_slab_free(struct kmem_cache *s, struct page *page, void *head, void *tail, int cnt, unsigned long addr)
static __always_inline void slab_free(struct kmem_cache *s, struct page *page, void *head, void *tail, int cnt, unsigned long addr)
void ___cache_free(struct kmem_cache *cache, void *x, unsigned long addr)
void kmem_cache_free(struct kmem_cache *s, void *x)
static inline int build_detached_freelist(struct kmem_cache *s, size_t size, void **p, struct detached_freelist *df)
void kmem_cache_free_bulk(struct kmem_cache *s, size_t size, void **p)
int kmem_cache_alloc_bulk(struct kmem_cache *s, gfp_t flags, size_t size, void **p)
static inline unsigned int slab_order(unsigned int size, unsigned int min_objects, unsigned int max_order, unsigned int fract_leftover)
static inline int calculate_order(unsigned int size)
static void init_kmem_cache_node(struct kmem_cache_node *n)
static inline int alloc_kmem_cache_cpus(struct kmem_cache *s)
static void early_kmem_cache_node_alloc(int node)
static void free_kmem_cache_nodes(struct kmem_cache *s)
void __kmem_cache_release(struct kmem_cache *s)
static int init_kmem_cache_nodes(struct kmem_cache *s)
static void set_min_partial(struct kmem_cache *s, unsigned long min)
static void set_cpu_partial(struct kmem_cache *s)
static int calculate_sizes(struct kmem_cache *s, int forced_order)
static int kmem_cache_open(struct kmem_cache *s, slab_flags_t flags)
static void list_slab_objects(struct kmem_cache *s, struct page *page, const char *text)
static void free_partial(struct kmem_cache *s, struct kmem_cache_node *n)
bool __kmem_cache_empty(struct kmem_cache *s)
int __kmem_cache_shutdown(struct kmem_cache *s)
static int __init setup_slub_min_order(char *str)
static int __init setup_slub_max_order(char *str)
static int __init setup_slub_min_objects(char *str)
void *__kmalloc(size_t size, gfp_t flags)
static void *kmalloc_large_node(size_t size, gfp_t flags, int node)
void *__kmalloc_node(size_t size, gfp_t flags, int node)
void __check_heap_object(const void *ptr, unsigned long n, struct page *page, bool to_user)
static size_t __ksize(const void *object)
size_t ksize(const void *object)
void kfree(const void *x)
int __kmem_cache_shrink(struct kmem_cache *s)
static void kmemcg_cache_deact_after_rcu(struct kmem_cache *s)
void __kmemcg_cache_deactivate(struct kmem_cache *s)
static int slab_mem_going_offline_callback(void *arg)
static void slab_mem_offline_callback(void *arg)
static int slab_mem_going_online_callback(void *arg)
static int slab_memory_callback(struct notifier_block *self, unsigned long action, void *arg)
static struct kmem_cache * __init bootstrap(struct kmem_cache *static_cache)
void __init kmem_cache_init(void)
void __init kmem_cache_init_late(void)
struct kmem_cache * __kmem_cache_alias(const char *name, unsigned int size, unsigned int align, slab_flags_t flags, void (*ctor)
(void *)
)
int __kmem_cache_create(struct kmem_cache *s, slab_flags_t flags)
void *__kmalloc_track_caller(size_t size, gfp_t gfpflags, unsigned long caller)
void *__kmalloc_node_track_caller(size_t size, gfp_t gfpflags, int node, unsigned long caller)
static int count_inuse(struct page *page)
static int count_total(struct page *page)
static int validate_slab(struct kmem_cache *s, struct page *page, unsigned long *map)
static void validate_slab_slab(struct kmem_cache *s, struct page *page, unsigned long *map)
static int validate_slab_node(struct kmem_cache *s, struct kmem_cache_node *n, unsigned long *map)
static long validate_slab_cache(struct kmem_cache *s)
static void free_loc_track(struct loc_track *t)
static int alloc_loc_track(struct loc_track *t, unsigned long max, gfp_t flags)
static int add_location(struct loc_track *t, struct kmem_cache *s, const struct track *track)
static void process_slab(struct loc_track *t, struct kmem_cache *s, struct page *page, enum track_item alloc, unsigned long *map)
static int list_locations(struct kmem_cache *s, char *buf, enum track_item alloc)
static void __init resiliency_test(void)
static int __init setup_slub_memcg_sysfs(char *str)
static ssize_t show_slab_objects(struct kmem_cache *s, char *buf, unsigned long flags)
static int any_slab_objects(struct kmem_cache *s)
static ssize_t slab_size_show(struct kmem_cache *s, char *buf)
static ssize_t align_show(struct kmem_cache *s, char *buf)
static ssize_t object_size_show(struct kmem_cache *s, char *buf)
static ssize_t objs_per_slab_show(struct kmem_cache *s, char *buf)
static ssize_t order_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t order_show(struct kmem_cache *s, char *buf)
static ssize_t min_partial_show(struct kmem_cache *s, char *buf)
static ssize_t min_partial_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t cpu_partial_show(struct kmem_cache *s, char *buf)
static ssize_t cpu_partial_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t ctor_show(struct kmem_cache *s, char *buf)
static ssize_t aliases_show(struct kmem_cache *s, char *buf)
static ssize_t partial_show(struct kmem_cache *s, char *buf)
static ssize_t cpu_slabs_show(struct kmem_cache *s, char *buf)
static ssize_t objects_show(struct kmem_cache *s, char *buf)
static ssize_t objects_partial_show(struct kmem_cache *s, char *buf)
static ssize_t slabs_cpu_partial_show(struct kmem_cache *s, char *buf)
static ssize_t reclaim_account_show(struct kmem_cache *s, char *buf)
static ssize_t reclaim_account_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t hwcache_align_show(struct kmem_cache *s, char *buf)
static ssize_t cache_dma_show(struct kmem_cache *s, char *buf)
static ssize_t usersize_show(struct kmem_cache *s, char *buf)
static ssize_t destroy_by_rcu_show(struct kmem_cache *s, char *buf)
static ssize_t slabs_show(struct kmem_cache *s, char *buf)
static ssize_t total_objects_show(struct kmem_cache *s, char *buf)
static ssize_t sanity_checks_show(struct kmem_cache *s, char *buf)
static ssize_t sanity_checks_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t trace_show(struct kmem_cache *s, char *buf)
static ssize_t trace_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t red_zone_show(struct kmem_cache *s, char *buf)
static ssize_t red_zone_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t poison_show(struct kmem_cache *s, char *buf)
static ssize_t poison_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t store_user_show(struct kmem_cache *s, char *buf)
static ssize_t store_user_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t validate_show(struct kmem_cache *s, char *buf)
static ssize_t validate_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t alloc_calls_show(struct kmem_cache *s, char *buf)
static ssize_t free_calls_show(struct kmem_cache *s, char *buf)
static ssize_t failslab_show(struct kmem_cache *s, char *buf)
static ssize_t failslab_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t shrink_show(struct kmem_cache *s, char *buf)
static ssize_t shrink_store(struct kmem_cache *s, const char *buf, size_t length)
static ssize_t remote_node_defrag_ratio_show(struct kmem_cache *s, char *buf)
static ssize_t remote_node_defrag_ratio_store(struct kmem_cache *s, const char *buf, size_t length)
static int show_stat(struct kmem_cache *s, char *buf, enum stat_item si)
static void clear_stat(struct kmem_cache *s, enum stat_item si)
define STAT_ATTR(si, text)
\ static ssize_t text_show(struct kmem_cache *s, char *buf)
\define STAT_ATTR(si, text)
\ static ssize_t text_show(struct kmem_cache *s, char *buf)
\return show_stat(s, buf, si)
;\ }\ static ssize_t text_store(struct kmem_cache *s, \ const char *buf, size_t length)
\ static ssize_t slab_attr_show(struct kobject *kobj, struct attribute *attr, char *buf)
static ssize_t slab_attr_store(struct kobject *kobj, struct attribute *attr, const char *buf, size_t len)
static void memcg_propagate_slab_attrs(struct kmem_cache *s)
static void kmem_cache_release(struct kobject *k)
static int uevent_filter(struct kset *kset, struct kobject *kobj)
static inline struct kset *cache_kset(struct kmem_cache *s)
static char *create_unique_id(struct kmem_cache *s)
static void sysfs_slab_remove_workfn(struct work_struct *work)
static int sysfs_slab_add(struct kmem_cache *s)
static void sysfs_slab_remove(struct kmem_cache *s)
void sysfs_slab_unlink(struct kmem_cache *s)
void sysfs_slab_release(struct kmem_cache *s)
static int sysfs_slab_alias(struct kmem_cache *s, const char *name)
static int __init slab_sysfs_init(void)
void get_slabinfo(struct kmem_cache *s, struct slabinfo *sinfo)
void slabinfo_show_stats(struct seq_file *m, struct kmem_cache *s)
ssize_t slabinfo_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
 171 struct kmem_cache *s
  52 struct page *page
  38 char *buf
  18 int node
  17 void *object
  15 struct kmem_cache_node *n
  14 size_t length
  14 const char *buf
  13 gfp_t flags
  12 unsigned long addr
  12 gfp_t gfpflags
  11 size_t size
   8 struct kmem_cache_cpu *c
   7 void
   5 unsigned long *map
   5 unsigned int size
   5 slab_flags_t flags
   5 const struct kmem_cache *s
   5 char *str
   4 void *x
   4 void *arg
   4 unsigned long tid
   4 struct loc_track *t
   4 enum track_item alloc
   4 const char *name
   3 void *tail
   3 void *p
   3 void *head
   3 void *ctor
   3 void **p
   3 void *
   3 struct kobject *kobj
   3 si
   3 int cpu
   3 enum stat_item si
   3 const char *n
   3 ...
   2 void *ptr
   2 void *freelist_old
   2 void *freelist_new
   2 unsigned long counters_old
   2 unsigned long counters_new
   2 unsigned long caller
   2 unsigned int order
   2 u8 val
   2 u8 *p
   2 u8 *object
   2 text
   2 struct kmem_cache_order_objects x
   2 struct attribute *attr
   2 int tail
   2 int objects
   2 int cnt
   2 const void *object
   2 char *fmt
   1 void *to
   1 void *start
   1 void *search
   1 void *ptr_addr
   1 void *info
   1 void *from
   1 void *freelist
   1 void *fp
   1 void *d
   1 void *addr
   1 void **tail
   1 void **head
   1 unsigned long ptr_addr
   1 unsigned long pr_time
   1 unsigned long page_limit
   1 unsigned long n
   1 unsigned long min
   1 unsigned long max
   1 unsigned long freelist_count
   1 unsigned long flags
   1 unsigned long action
   1 unsigned long *pos
   1 unsigned int value
   1 unsigned int object_size
   1 unsigned int min_objects
   1 unsigned int max_order
   1 unsigned int length
   1 unsigned int fract_leftover
   1 unsigned int cpu
   1 unsigned int bytes
   1 unsigned int align
   1 u8 data
   1 u8 *start
   1 u8 *addr
   1 struct work_struct *work
   1 struct track *t
   1 struct slabinfo *sinfo
   1 struct seq_file *m
   1 struct rcu_head *h
   1 struct page *
   1 struct notifier_block *self
   1 struct kset *kset
   1 struct kobject *k
   1 struct kmem_cache_order_objects oo
   1 struct kmem_cache_cpu **pc
   1 struct kmem_cache *static_cache
   1 struct kmem_cache *cache
   1 struct file *file
   1 struct detached_freelist *df
   1 static inline void remove_fullstruct kmem_cache *s
   1 static inline void add_fullstruct kmem_cache *s
   1 slab_flags_t kmem_cache_flagsunsigned int object_size
   1 size_t len
   1 size_t count
   1 s
   1 objects
   1 loff_t *ppos
   1 int nid
   1 int mode
   1 int forced_order
   1 int drain
   1 int bulk_cnt
   1 int alloc
   1 int *objects
   1 int *get_count
   1 const void *x
   1 const void *ptr
   1 const struct track *track
   1 const char __user *buffer
   1 const char *text
   1 const char *s
   1 const char *fmt
   1 char *what
   1 char *text
   1 char *reason
   1 char *message
   1 char *level
   1 buf
   1 bool to_user
   1 \ const char *buf
   1 4
   1 3
   1 &n->total_objects
   1 &n->nr_slabs
