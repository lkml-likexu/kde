
\n
static void __qib_release_user_pages(struct page **p, size_t num_pages, int dirty)
static int __qib_get_user_pages(unsigned long start_page, size_t num_pages, struct page **p)
int qib_map_page(struct pci_dev *hwdev, struct page *page, dma_addr_t *daddr)
int qib_get_user_pages(unsigned long start_page, size_t num_pages, struct page **p)
void qib_release_user_pages(struct page **p, size_t num_pages)
\n
      4 struct page **p
      4 size_t num_pages
      2 unsigned long start_page
      1 struct pci_dev *hwdev
      1 struct page *page
      1 int dirty
      1 dma_addr_t *daddr
