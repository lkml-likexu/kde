
\n
static inline bool force_dma_unencrypted(void)
static void report_addr(struct device *dev, dma_addr_t dma_addr, size_t size)
static inline dma_addr_t phys_to_dma_direct(struct device *dev, phys_addr_t phys)
u64 dma_direct_get_required_mask(struct device *dev)
static gfp_t __dma_direct_optimal_gfp_mask(struct device *dev, u64 dma_mask, u64 *phys_mask)
static bool dma_coherent_ok(struct device *dev, phys_addr_t phys, size_t size)
struct page *__dma_direct_alloc_pages(struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t gfp, unsigned long attrs)
void *dma_direct_alloc_pages(struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t gfp, unsigned long attrs)
void __dma_direct_free_pages(struct device *dev, size_t size, struct page *page)
void dma_direct_free_pages(struct device *dev, size_t size, void *cpu_addr, dma_addr_t dma_addr, unsigned long attrs)
void *dma_direct_alloc(struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t gfp, unsigned long attrs)
void dma_direct_free(struct device *dev, size_t size, void *cpu_addr, dma_addr_t dma_addr, unsigned long attrs)
defined(CONFIG_SWIOTLB)
void dma_direct_sync_single_for_device(struct device *dev, dma_addr_t addr, size_t size, enum dma_data_direction dir)
void dma_direct_sync_sg_for_device(struct device *dev, struct scatterlist *sgl, int nents, enum dma_data_direction dir)
defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU_ALL)
|| \ defined(CONFIG_SWIOTLB)
void dma_direct_sync_single_for_cpu(struct device *dev, dma_addr_t addr, size_t size, enum dma_data_direction dir)
void dma_direct_sync_sg_for_cpu(struct device *dev, struct scatterlist *sgl, int nents, enum dma_data_direction dir)
void dma_direct_unmap_page(struct device *dev, dma_addr_t addr, size_t size, enum dma_data_direction dir, unsigned long attrs)
void dma_direct_unmap_sg(struct device *dev, struct scatterlist *sgl, int nents, enum dma_data_direction dir, unsigned long attrs)
static inline bool dma_direct_possible(struct device *dev, dma_addr_t dma_addr, size_t size)
dma_addr_t dma_direct_map_page(struct device *dev, struct page *page, unsigned long offset, size_t size, enum dma_data_direction dir, unsigned long attrs)
int dma_direct_map_sg(struct device *dev, struct scatterlist *sgl, int nents, enum dma_data_direction dir, unsigned long attrs)
int dma_direct_supported(struct device *dev, u64 mask)
\n
     21 struct device *dev
     13 size_t size
      9 unsigned long attrs
      8 enum dma_data_direction dir
      4 struct scatterlist *sgl
      4 int nents
      4 dma_addr_t dma_addr
      3 gfp_t gfp
      3 dma_addr_t *dma_handle
      3 dma_addr_t addr
      2 void *cpu_addr
      2 struct page *page
      2 phys_addr_t phys
      2 CONFIG_SWIOTLB
      1 void
      1 unsigned long offset
      1 u64 *phys_mask
      1 u64 mask
      1 u64 dma_mask
      1 CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU_ALL
