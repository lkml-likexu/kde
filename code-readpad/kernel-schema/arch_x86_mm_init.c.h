
\n
__ref void *alloc_low_pages(unsigned int num)
define INIT_PGD_PAGE_COUNT6define INIT_PGD_PAGE_COUNT12endifdefine INIT_PGT_BUF_SIZE (INIT_PGD_PAGE_COUNT * PAGE_SIZE)
RESERVE_BRK(early_pgt_alloc, INIT_PGT_BUF_SIZE)
; void__init early_alloc_pgt_buf(void)
static void __init probe_page_size_mask(void)
static void setup_pcid(void)
static int __meminit save_mr(struct map_range *mr, int nr_range, unsigned long start_pfn, unsigned long end_pfn, unsigned long page_size_mask)
static void __ref adjust_range_page_size_mask(struct map_range *mr, int nr_range)
static const char *page_size_string(struct map_range *mr)
static int __meminit split_mem_range(struct map_range *mr, int nr_range, unsigned long start, unsigned long end)
static void add_pfn_range_mapped(unsigned long start_pfn, unsigned long end_pfn)
bool pfn_range_is_mapped(unsigned long start_pfn, unsigned long end_pfn)
unsigned long __ref init_memory_mapping(unsigned long start, unsigned long end)
static unsigned long __init init_range_memory_mapping( unsigned long r_start, unsigned long r_end)
static unsigned long __init get_new_step_size(unsigned long step_size)
static void __init memory_map_top_down(unsigned long map_start, unsigned long map_end)
static void __init memory_map_bottom_up(unsigned long map_start, unsigned long map_end)
void __init init_mem_mapping(void)
int devmem_is_allowed(unsigned long pagenr)
void free_init_pages(const char *what, unsigned long begin, unsigned long end)
void free_kernel_image_pages(void *begin, void *end)
void __ref free_initmem(void)
void __init free_initrd_mem(unsigned long start, unsigned long end)
void __init memblock_find_dma_reserve(void)
void __init zone_sizes_init(void)
void update_cache_mode_entry(unsigned entry, enum page_cache_mode cache)
unsigned long max_swapfile_size(void)
\n
      8 void
      4 unsigned long end
      4 struct map_range *mr
      3 unsigned long start_pfn
      3 unsigned long start
      3 unsigned long end_pfn
      3 int nr_range
      2 unsigned long map_start
      2 unsigned long map_end
      1 void *end
      1 void *begin
      1 unsigned long step_size
      1 unsigned long r_start
      1 unsigned long r_end
      1 unsigned long page_size_mask
      1 unsigned long pagenr
      1 unsigned long begin
      1 unsigned int num
      1 unsigned entry
      1 INIT_PGT_BUF_SIZE
      1 INIT_PGD_PAGE_COUNT * PAGE_SIZE
      1 enum page_cache_mode cache
      1 early_pgt_alloc
      1 const char *what
