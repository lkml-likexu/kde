
\n
static void put_all_pages(struct page **pages, int npages)
void afu_dma_region_init(struct dfl_feature_platform_data *pdata)
static int afu_dma_adjust_locked_vm(struct device *dev, long npages, bool incr)
static int afu_dma_pin_pages(struct dfl_feature_platform_data *pdata, struct dfl_afu_dma_region *region)
static void afu_dma_unpin_pages(struct dfl_feature_platform_data *pdata, struct dfl_afu_dma_region *region)
static bool afu_dma_check_continuous_pages(struct dfl_afu_dma_region *region)
static bool dma_region_check_iova(struct dfl_afu_dma_region *region, u64 iova, u64 size)
static int afu_dma_region_add(struct dfl_feature_platform_data *pdata, struct dfl_afu_dma_region *region)
static void afu_dma_region_remove(struct dfl_feature_platform_data *pdata, struct dfl_afu_dma_region *region)
void afu_dma_region_destroy(struct dfl_feature_platform_data *pdata)
struct dfl_afu_dma_region * afu_dma_region_find(struct dfl_feature_platform_data *pdata, u64 iova, u64 size)
static struct dfl_afu_dma_region * afu_dma_region_find_iova(struct dfl_feature_platform_data *pdata, u64 iova)
int afu_dma_map_region(struct dfl_feature_platform_data *pdata, u64 user_addr, u64 length, u64 *iova)
int afu_dma_unmap_region(struct dfl_feature_platform_data *pdata, u64 iova)
\n
     10 struct dfl_feature_platform_data *pdata
      6 struct dfl_afu_dma_region *region
      4 u64 iova
      2 u64 size
      1 u64 user_addr
      1 u64 length
      1 u64 *iova
      1 struct page **pages
      1 struct device *dev
      1 long npages
      1 int npages
      1 bool incr
