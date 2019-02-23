
\n
static inline unsigned long page_to_boot_pfn(struct page *page)
static inline struct page *boot_pfn_to_page(unsigned long boot_pfn)
static inline unsigned long phys_to_boot_phys(phys_addr_t phys)
static inline phys_addr_t boot_phys_to_phys(unsigned long boot_phys)
static inline unsigned long virt_to_boot_phys(void *addr)
static inline void *boot_phys_to_virt(unsigned long entry)
\n
      1 void *addr
      1 unsigned long entry
      1 unsigned long boot_phys
      1 unsigned long boot_pfn
      1 struct page *page
      1 phys_addr_t phys
