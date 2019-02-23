
\n
int gasket_page_table_init(struct gasket_page_table **ppg_tbl, const struct gasket_bar_data *bar_data, const struct gasket_page_table_config *page_table_config, struct device *device, struct pci_dev *pci_dev)
static bool gasket_is_pte_range_free(struct gasket_page_table_entry *ptes, uint num_entries)
static void gasket_free_extended_subtable(struct gasket_page_table *pg_tbl, struct gasket_page_table_entry *pte, u64 __iomem *slot)
static void gasket_page_table_garbage_collect_nolock(struct gasket_page_table *pg_tbl)
void gasket_page_table_garbage_collect(struct gasket_page_table *pg_tbl)
void gasket_page_table_cleanup(struct gasket_page_table *pg_tbl)
int gasket_page_table_partition(struct gasket_page_table *pg_tbl, uint num_simple_entries)
static int is_coherent(struct gasket_page_table *pg_tbl, ulong host_addr)
static bool gasket_release_page(struct page *page)
static int gasket_perform_mapping(struct gasket_page_table *pg_tbl, struct gasket_page_table_entry *ptes, u64 __iomem *slots, ulong host_addr, uint num_pages, int is_simple_mapping)
static int gasket_simple_page_idx(struct gasket_page_table *pg_tbl, ulong dev_addr)
static ulong gasket_extended_lvl0_page_idx(struct gasket_page_table *pg_tbl, ulong dev_addr)
static ulong gasket_extended_lvl1_page_idx(struct gasket_page_table *pg_tbl, ulong dev_addr)
static int gasket_alloc_simple_entries(struct gasket_page_table *pg_tbl, ulong dev_addr, uint num_pages)
static void gasket_perform_unmapping(struct gasket_page_table *pg_tbl, struct gasket_page_table_entry *ptes, u64 __iomem *slots, uint num_pages, int is_simple_mapping)
static void gasket_unmap_simple_pages(struct gasket_page_table *pg_tbl, ulong dev_addr, uint num_pages)
static void gasket_unmap_extended_pages(struct gasket_page_table *pg_tbl, ulong dev_addr, uint num_pages)
static inline bool gasket_addr_is_simple(struct gasket_page_table *pg_tbl, ulong addr)
static ulong gasket_components_to_dev_address(struct gasket_page_table *pg_tbl, int is_simple, uint page_index, uint offset)
static bool gasket_is_simple_dev_addr_bad(struct gasket_page_table *pg_tbl, ulong dev_addr, uint num_pages)
static bool gasket_is_extended_dev_addr_bad(struct gasket_page_table *pg_tbl, ulong dev_addr, uint num_pages)
static void gasket_page_table_unmap_nolock(struct gasket_page_table *pg_tbl, ulong dev_addr, uint num_pages)
static int gasket_map_simple_pages(struct gasket_page_table *pg_tbl, ulong host_addr, ulong dev_addr, uint num_pages)
static int gasket_alloc_extended_subtable(struct gasket_page_table *pg_tbl, struct gasket_page_table_entry *pte, u64 __iomem *slot)
static int gasket_alloc_extended_entries(struct gasket_page_table *pg_tbl, ulong dev_addr, uint num_entries)
static int gasket_map_extended_pages(struct gasket_page_table *pg_tbl, ulong host_addr, ulong dev_addr, uint num_pages)
int gasket_page_table_map(struct gasket_page_table *pg_tbl, ulong host_addr, ulong dev_addr, uint num_pages)
void gasket_page_table_unmap(struct gasket_page_table *pg_tbl, ulong dev_addr, uint num_pages)
static void gasket_page_table_unmap_all_nolock(struct gasket_page_table *pg_tbl)
void gasket_page_table_unmap_all(struct gasket_page_table *pg_tbl)
void gasket_page_table_reset(struct gasket_page_table *pg_tbl)
int gasket_page_table_lookup_page(struct gasket_page_table *pg_tbl, ulong dev_addr, struct page **ppage, ulong *poffset)
bool gasket_page_table_are_addrs_bad(struct gasket_page_table *pg_tbl, ulong host_addr, ulong dev_addr, ulong bytes)
bool gasket_page_table_is_dev_addr_bad(struct gasket_page_table *pg_tbl, ulong dev_addr, ulong bytes)
uint gasket_page_table_max_size(struct gasket_page_table *page_table)
uint gasket_page_table_num_entries(struct gasket_page_table *pg_tbl)
uint gasket_page_table_num_simple_entries(struct gasket_page_table *pg_tbl)
uint gasket_page_table_num_active_pages(struct gasket_page_table *pg_tbl)
int gasket_page_table_system_status(struct gasket_page_table *page_table)
int gasket_set_user_virt(struct gasket_dev *gasket_dev, u64 size, dma_addr_t dma_address, ulong vma)
int gasket_alloc_coherent_memory(struct gasket_dev *gasket_dev, u64 size, dma_addr_t *dma_address, u64 index)
int gasket_free_coherent_memory(struct gasket_dev *gasket_dev, u64 size, dma_addr_t dma_address, u64 index)
void gasket_free_coherent_memory_all(struct gasket_dev *gasket_dev, u64 index)
\n
     34 struct gasket_page_table *pg_tbl
     17 ulong dev_addr
     12 uint num_pages
      6 ulong host_addr
      4 struct gasket_dev *gasket_dev
      3 u64 size
      3 u64 index
      3 struct gasket_page_table_entry *ptes
      2 ulong bytes
      2 uint num_entries
      2 u64 __iomem *slots
      2 u64 __iomem *slot
      2 struct gasket_page_table *page_table
      2 struct gasket_page_table_entry *pte
      2 int is_simple_mapping
      2 dma_addr_t dma_address
      1 ulong vma
      1 ulong *poffset
      1 ulong addr
      1 uint page_index
      1 uint offset
      1 uint num_simple_entries
      1 struct pci_dev *pci_dev
      1 struct page **ppage
      1 struct page *page
      1 struct gasket_page_table **ppg_tbl
      1 struct device *device
      1 int is_simple
      1 dma_addr_t *dma_address
      1 const struct gasket_page_table_config *page_table_config
      1 const struct gasket_bar_data *bar_data
