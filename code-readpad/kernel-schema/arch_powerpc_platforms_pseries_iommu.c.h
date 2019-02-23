
\n
static struct iommu_table_group *iommu_pseries_alloc_group(int node)
static void iommu_pseries_free_group(struct iommu_table_group *table_group, const char *node_name)
static int tce_build_pSeries(struct iommu_table *tbl, long index, long npages, unsigned long uaddr, enum dma_data_direction direction, unsigned long attrs)
static void tce_free_pSeries(struct iommu_table *tbl, long index, long npages)
static unsigned long tce_get_pseries(struct iommu_table *tbl, long index)
static int tce_build_pSeriesLP(struct iommu_table *tbl, long tcenum, long npages, unsigned long uaddr, enum dma_data_direction direction, unsigned long attrs)
static int tce_buildmulti_pSeriesLP(struct iommu_table *tbl, long tcenum, long npages, unsigned long uaddr, enum dma_data_direction direction, unsigned long attrs)
static void tce_free_pSeriesLP(struct iommu_table *tbl, long tcenum, long npages)
static void tce_freemulti_pSeriesLP(struct iommu_table *tbl, long tcenum, long npages)
static unsigned long tce_get_pSeriesLP(struct iommu_table *tbl, long tcenum)
static int tce_clearrange_multi_pSeriesLP(unsigned long start_pfn, unsigned long num_pfn, const void *arg)
static int tce_setrange_multi_pSeriesLP(unsigned long start_pfn, unsigned long num_pfn, const void *arg)
static int tce_setrange_multi_pSeriesLP_walk(unsigned long start_pfn, unsigned long num_pfn, void *arg)
static void iommu_table_setparms(struct pci_controller *phb, struct device_node *dn, struct iommu_table *tbl)
static void iommu_table_setparms_lpar(struct pci_controller *phb, struct device_node *dn, struct iommu_table *tbl, struct iommu_table_group *table_group, const __be32 *dma_window)
static void pci_dma_bus_setup_pSeries(struct pci_bus *bus)
static int tce_exchange_pseries(struct iommu_table *tbl, long index, unsigned long *tce, enum dma_data_direction *direction)
static void pci_dma_bus_setup_pSeriesLP(struct pci_bus *bus)
static void pci_dma_dev_setup_pSeries(struct pci_dev *dev)
static int __init disable_ddw_setup(char *str)
static void remove_ddw(struct device_node *np, bool remove_prop)
static u64 find_existing_ddw(struct device_node *pdn)
static int find_existing_ddw_windows(void)
static int query_ddw(struct pci_dev *dev, const u32 *ddw_avail, struct ddw_query_response *query)
static int create_ddw(struct pci_dev *dev, const u32 *ddw_avail, struct ddw_create_response *create, int page_shift, int window_shift)
static phys_addr_t ddw_memory_hotplug_max(void)
static u64 enable_ddw(struct pci_dev *dev, struct device_node *pdn)
static void pci_dma_dev_setup_pSeriesLP(struct pci_dev *dev)
static int dma_set_mask_pSeriesLP(struct device *dev, u64 dma_mask)
static u64 dma_get_required_mask_pSeriesLP(struct device *dev)
static int iommu_mem_notifier(struct notifier_block *nb, unsigned long action, void *data)
static int iommu_reconfig_notifier(struct notifier_block *nb, unsigned long action, void *data)
void iommu_init_early_pSeries(void)
static int __init disable_multitce(char *str)
static int tce_iommu_bus_notifier(struct notifier_block *nb, unsigned long action, void *data)
static int __init tce_iommu_bus_notifier_init(void)
\n
     11 struct iommu_table *tbl
      6 long npages
      5 struct pci_dev *dev
      5 long tcenum
      4 void
      4 long index
      3 void *data
      3 unsigned long uaddr
      3 unsigned long start_pfn
      3 unsigned long num_pfn
      3 unsigned long attrs
      3 unsigned long action
      3 struct notifier_block *nb
      3 enum dma_data_direction direction
      2 struct pci_controller *phb
      2 struct pci_bus *bus
      2 struct iommu_table_group *table_group
      2 struct device_node *pdn
      2 struct device_node *dn
      2 struct device *dev
      2 const void *arg
      2 const u32 *ddw_avail
      2 char *str
      1 void *arg
      1 unsigned long *tce
      1 u64 dma_mask
      1 struct device_node *np
      1 struct ddw_query_response *query
      1 struct ddw_create_response *create
      1 int window_shift
      1 int page_shift
      1 int node
      1 enum dma_data_direction *direction
      1 const char *node_name
      1 const __be32 *dma_window
      1 bool remove_prop
