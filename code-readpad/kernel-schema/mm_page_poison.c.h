
EXPORT_SYMBOL_GPL(page_poisoning_enabled);
\n
static int __init early_page_poison_param(char *buf)
bool page_poisoning_enabled(void)
static void poison_page(struct page *page)
static void poison_pages(struct page *page, int n)
static bool single_bit_flip(unsigned char a, unsigned char b)
static void check_poison_mem(unsigned char *mem, size_t bytes)
static void unpoison_page(struct page *page)
static void unpoison_pages(struct page *page, int n)
void kernel_poison_pages(struct page *page, int numpages, int enable)
void __kernel_map_pages(struct page *page, int numpages, int enable)
\n
      6 struct page *page
      2 int numpages
      2 int n
      2 int enable
      1 void
      1 unsigned char *mem
      1 unsigned char b
      1 unsigned char a
      1 size_t bytes
      1 page_poisoning_enabled
      1 char *buf
