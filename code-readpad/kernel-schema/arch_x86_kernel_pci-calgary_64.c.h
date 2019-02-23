
\n
static inline int translation_enabled(struct iommu_table *tbl)
static void iommu_range_reserve(struct iommu_table *tbl, unsigned long start_addr, unsigned int npages)
static unsigned long iommu_range_alloc(struct device *dev, struct iommu_table *tbl, unsigned int npages)
static dma_addr_t iommu_alloc(struct device *dev, struct iommu_table *tbl, void *vaddr, unsigned int npages, int direction)
static void iommu_free(struct iommu_table *tbl, dma_addr_t dma_addr, unsigned int npages)
static inline struct iommu_table *find_iommu_table(struct device *dev)
static void calgary_unmap_sg(struct device *dev, struct scatterlist *sglist, int nelems, enum dma_data_direction dir, unsigned long attrs)
static int calgary_map_sg(struct device *dev, struct scatterlist *sg, int nelems, enum dma_data_direction dir, unsigned long attrs)
static dma_addr_t calgary_map_page(struct device *dev, struct page *page, unsigned long offset, size_t size, enum dma_data_direction dir, unsigned long attrs)
static void calgary_unmap_page(struct device *dev, dma_addr_t dma_addr, size_t size, enum dma_data_direction dir, unsigned long attrs)
static void* calgary_alloc_coherent(struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t flag, unsigned long attrs)
static void calgary_free_coherent(struct device *dev, size_t size, void *vaddr, dma_addr_t dma_handle, unsigned long attrs)
static inline void __iomem * busno_to_bbar(unsigned char num)
static inline int busno_to_phbid(unsigned char num)
static inline unsigned long split_queue_offset(unsigned char num)
static inline unsigned long tar_offset(unsigned char num)
static inline unsigned long phb_offset(unsigned char num)
static inline void __iomem* calgary_reg(void __iomem *bar, unsigned long offset)
static inline int is_calioc2(unsigned short device)
static inline int is_calgary(unsigned short device)
static inline int is_cal_pci_dev(unsigned short device)
static void calgary_tce_cache_blast(struct iommu_table *tbl)
static void calioc2_tce_cache_blast(struct iommu_table *tbl)
static void __init calgary_reserve_mem_region(struct pci_dev *dev, u64 start, u64 limit)
static void __init calgary_reserve_peripheral_mem_1(struct pci_dev *dev)
static void __init calgary_reserve_peripheral_mem_2(struct pci_dev *dev)
static void __init calgary_reserve_regions(struct pci_dev *dev)
static int __init calgary_setup_tar(struct pci_dev *dev, void __iomem *bbar)
static void __init calgary_free_bus(struct pci_dev *dev)
static void calgary_dump_error_regs(struct iommu_table *tbl)
static void calioc2_dump_error_regs(struct iommu_table *tbl)
static void calgary_watchdog(struct timer_list *t)
static void __init calgary_set_split_completion_timeout(void __iomem *bbar, unsigned char busnum, unsigned long timeout)
static void __init calioc2_handle_quirks(struct iommu_table *tbl, struct pci_dev *dev)
static void __init calgary_handle_quirks(struct iommu_table *tbl, struct pci_dev *dev)
static void __init calgary_enable_translation(struct pci_dev *dev)
static void __init calgary_disable_translation(struct pci_dev *dev)
static void __init calgary_init_one_nontraslated(struct pci_dev *dev)
static int __init calgary_init_one(struct pci_dev *dev)
static int __init calgary_locate_bbars(void)
static int __init calgary_init(void)
static inline int __init determine_tce_table_size(void)
static int __init build_detail_arrays(void)
static int __init calgary_bus_has_devices(int bus, unsigned short pci_dev)
static void calgary_init_bitmap_from_tce_table(struct iommu_table *tbl)
static void __init get_tce_space_from_tar(void)
static int __init calgary_iommu_init(void)
int __init detect_calgary(void)
static int __init calgary_parse_options(char *p)
static void __init calgary_fixup_one_tce_space(struct pci_dev *dev)
static int __init calgary_fixup_tce_spaces(void)
\n
     13 struct pci_dev *dev
     12 struct iommu_table *tbl
      9 struct device *dev
      8 void
      6 unsigned long attrs
      5 unsigned char num
      4 unsigned int npages
      4 size_t size
      4 enum dma_data_direction dir
      3 unsigned short device
      2 void *vaddr
      2 void __iomem *bbar
      2 unsigned long offset
      2 int nelems
      2 dma_addr_t dma_addr
      1 void __iomem *bar
      1 unsigned short pci_dev
      1 unsigned long timeout
      1 unsigned long start_addr
      1 unsigned char busnum
      1 u64 start
      1 u64 limit
      1 struct timer_list *t
      1 struct scatterlist *sglist
      1 struct scatterlist *sg
      1 struct page *page
      1 int direction
      1 int bus
      1 gfp_t flag
      1 dma_addr_t dma_handle
      1 dma_addr_t *dma_handle
      1 char *p
