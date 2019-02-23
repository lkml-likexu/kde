
\n
static inline unsigned long iova_size(struct iova *iova)
static inline unsigned long iova_shift(struct iova_domain *iovad)
static inline unsigned long iova_mask(struct iova_domain *iovad)
static inline size_t iova_offset(struct iova_domain *iovad, dma_addr_t iova)
static inline size_t iova_align(struct iova_domain *iovad, size_t size)
static inline dma_addr_t iova_dma_addr(struct iova_domain *iovad, struct iova *iova)
static inline unsigned long iova_pfn(struct iova_domain *iovad, dma_addr_t iova)
struct iova *alloc_iova_mem(void)
; void free_iova_mem(struct iova *iova)
; void free_iova(struct iova_domain *iovad, unsigned long pfn)
; void __free_iova(struct iova_domain *iovad, struct iova *iova)
; struct iova *alloc_iova(struct iova_domain *iovad, unsigned long size, unsigned long limit_pfn, bool size_aligned)
; void free_iova_fast(struct iova_domain *iovad, unsigned long pfn, unsigned long size)
; void queue_iova(struct iova_domain *iovad, unsigned long pfn, unsigned long pages, unsigned long data)
; unsigned long alloc_iova_fast(struct iova_domain *iovad, unsigned long size, unsigned long limit_pfn, bool flush_rcache)
; struct iova *reserve_iova(struct iova_domain *iovad, unsigned long pfn_lo, unsigned long pfn_hi)
; void copy_reserved_iova(struct iova_domain *from, struct iova_domain *to)
; void init_iova_domain(struct iova_domain *iovad, unsigned long granule, unsigned long start_pfn)
; int init_iova_flush_queue(struct iova_domain *iovad, iova_flush_cb flush_cb, iova_entry_dtor entry_dtor)
; struct iova *find_iova(struct iova_domain *iovad, unsigned long pfn)
; void put_iova_domain(struct iova_domain *iovad)
; struct iova *split_and_remove_iova(struct iova_domain *iovad, struct iova *iova, unsigned long pfn_lo, unsigned long pfn_hi)
; void free_cpu_cached_iovas(unsigned int cpu, struct iova_domain *iovad)
; static inline int iova_cache_get(void)
static inline void iova_cache_put(void)
static inline struct iova *alloc_iova_mem(void)
static inline void free_iova_mem(struct iova *iova)
static inline void free_iova(struct iova_domain *iovad, unsigned long pfn)
static inline void __free_iova(struct iova_domain *iovad, struct iova *iova)
static inline struct iova *alloc_iova(struct iova_domain *iovad, unsigned long size, unsigned long limit_pfn, bool size_aligned)
static inline void free_iova_fast(struct iova_domain *iovad, unsigned long pfn, unsigned long size)
static inline void queue_iova(struct iova_domain *iovad, unsigned long pfn, unsigned long pages, unsigned long data)
static inline unsigned long alloc_iova_fast(struct iova_domain *iovad, unsigned long size, unsigned long limit_pfn, bool flush_rcache)
static inline struct iova *reserve_iova(struct iova_domain *iovad, unsigned long pfn_lo, unsigned long pfn_hi)
static inline void copy_reserved_iova(struct iova_domain *from, struct iova_domain *to)
static inline void init_iova_domain(struct iova_domain *iovad, unsigned long granule, unsigned long start_pfn)
static inline int init_iova_flush_queue(struct iova_domain *iovad, iova_flush_cb flush_cb, iova_entry_dtor entry_dtor)
static inline struct iova *find_iova(struct iova_domain *iovad, unsigned long pfn)
static inline void put_iova_domain(struct iova_domain *iovad)
static inline struct iova *split_and_remove_iova(struct iova_domain *iovad, struct iova *iova, unsigned long pfn_lo, unsigned long pfn_hi)
static inline void free_cpu_cached_iovas(unsigned int cpu, struct iova_domain *iovad)
\n
     32 struct iova_domain *iovad
      8 unsigned long pfn
      8 struct iova *iova
      6 unsigned long size
      4 void
      4 unsigned long pfn_lo
      4 unsigned long pfn_hi
      4 unsigned long limit_pfn
      2 unsigned long start_pfn
      2 unsigned long pages
      2 unsigned long granule
      2 unsigned long data
      2 unsigned int cpu
      2 struct iova_domain *to
      2 struct iova_domain *from
      2 iova_flush_cb flush_cb
      2 iova_entry_dtor entry_dtor
      2 dma_addr_t iova
      2 bool size_aligned
      2 bool flush_rcache
      1 size_t size
