
EXPORT_SYMBOL_GPL(balloon_stats);
EXPORT_SYMBOL_GPL(balloon_set_new_target);
\n
static void __balloon_append(struct page *page)
static void balloon_append(struct page *page)
static struct page *balloon_retrieve(bool require_lowmem)
static struct page *balloon_next_page(struct page *page)
static enum bp_state update_schedule(enum bp_state state)
static void release_memory_resource(struct resource *resource)
static struct resource *additional_memory_resource(phys_addr_t size)
static enum bp_state reserve_additional_memory(void)
static void xen_online_page(struct page *page)
static int xen_memory_notifier(struct notifier_block *nb, unsigned long val, void *v)
.notifier_call = xen_memory_notifier, .priority = 0 }; static enum bp_state reserve_additional_memory(void)
static long current_credit(void)
static bool balloon_is_inflated(void)
static enum bp_state increase_reservation(unsigned long nr_pages)
static enum bp_state decrease_reservation(unsigned long nr_pages, gfp_t gfp)
static void balloon_process(struct work_struct *work)
void balloon_set_new_target(unsigned long target)
static int add_ballooned_pages(int nr_pages)
int alloc_xenballooned_pages(int nr_pages, struct page **pages)
void free_xenballooned_pages(int nr_pages, struct page **pages)
static void __init balloon_add_region(unsigned long start_pfn, unsigned long pages)
static int __init balloon_init(void)
\n
      5 void
      4 struct page *page
      3 int nr_pages
      2 unsigned long nr_pages
      2 struct page **pages
      1 void *v
      1 unsigned long val
      1 unsigned long target
      1 unsigned long start_pfn
      1 unsigned long pages
      1 struct work_struct *work
      1 struct resource *resource
      1 struct notifier_block *nb
      1 phys_addr_t size
      1 gfp_t gfp
      1 enum bp_state state
      1 bool require_lowmem
      1 balloon_stats
      1 balloon_set_new_target
