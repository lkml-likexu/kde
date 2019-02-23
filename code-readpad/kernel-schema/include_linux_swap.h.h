
\n
static inline int current_is_kswapd(void)
static inline bool vm_swap_full(void)
static inline long get_nr_swap_pages(void)
static inline int swap_readpage(struct page *page, bool do_poll)
static inline struct swap_info_struct *swp_swap_info(swp_entry_t entry)
static inline void show_swap_cache_info(void)
static inline int add_swap_count_continuation(swp_entry_t swp, gfp_t gfp_mask)
static inline void swap_shmem_alloc(swp_entry_t swp)
static inline int swap_duplicate(swp_entry_t swp)
static inline void swap_free(swp_entry_t swp)
static inline void put_swap_page(struct page *page, swp_entry_t swp)
static inline struct page *swap_cluster_readahead(swp_entry_t entry, gfp_t gfp_mask, struct vm_fault *vmf)
static inline struct page *swapin_readahead(swp_entry_t swp, gfp_t gfp_mask, struct vm_fault *vmf)
static inline int swap_writepage(struct page *p, struct writeback_control *wbc)
static inline struct page *lookup_swap_cache(swp_entry_t swp, struct vm_area_struct *vma, unsigned long addr)
static inline int add_to_swap(struct page *page)
static inline int add_to_swap_cache(struct page *page, swp_entry_t entry, gfp_t gfp_mask)
static inline void __delete_from_swap_cache(struct page *page, swp_entry_t entry)
static inline void delete_from_swap_cache(struct page *page)
static inline int page_swapcount(struct page *page)
static inline int __swap_count(struct swap_info_struct *si, swp_entry_t entry)
static inline int __swp_swapcount(swp_entry_t entry)
static inline int swp_swapcount(swp_entry_t entry)
static inline int try_to_free_swap(struct page *page)
static inline swp_entry_t get_swap_page(struct page *page)
extern int split_swap_cluster(swp_entry_t entry)
; static inline int split_swap_cluster(swp_entry_t entry)
static inline int mem_cgroup_swappiness(struct mem_cgroup *memcg)
return memcg->swappiness; } static inline int mem_cgroup_swappiness(struct mem_cgroup *mem)
extern void mem_cgroup_throttle_swaprate(struct mem_cgroup *memcg, int node, gfp_t gfp_mask)
; static inline void mem_cgroup_throttle_swaprate(struct mem_cgroup *memcg, int node, gfp_t gfp_mask)
extern void mem_cgroup_swapout(struct page *page, swp_entry_t entry)
; extern int mem_cgroup_try_charge_swap(struct page *page, swp_entry_t entry)
; extern void mem_cgroup_uncharge_swap(swp_entry_t entry, unsigned int nr_pages)
; extern long mem_cgroup_get_nr_swap_pages(struct mem_cgroup *memcg)
; extern bool mem_cgroup_swap_full(struct page *page)
; static inline void mem_cgroup_swapout(struct page *page, swp_entry_t entry)
static inline int mem_cgroup_try_charge_swap(struct page *page, swp_entry_t entry)
static inline void mem_cgroup_uncharge_swap(swp_entry_t entry, unsigned int nr_pages)
static inline long mem_cgroup_get_nr_swap_pages(struct mem_cgroup *memcg)
static inline bool mem_cgroup_swap_full(struct page *page)
\n
     15 swp_entry_t entry
     15 struct page *page
      7 swp_entry_t swp
      6 gfp_t gfp_mask
      5 struct mem_cgroup *memcg
      4 void
      2 unsigned int nr_pages
      2 struct vm_fault *vmf
      2 int node
      1 unsigned long addr
      1 struct writeback_control *wbc
      1 struct vm_area_struct *vma
      1 struct swap_info_struct *si
      1 struct page *p
      1 struct mem_cgroup *mem
      1 bool do_poll
