
EXPORT_SYMBOL_GPL(page_init_poison);
\n
void __dump_page(struct page *page, const char *reason)
void dump_page(struct page *page, const char *reason)
void dump_vma(const struct vm_area_struct *vma)
void dump_mm(const struct mm_struct *mm)
static int __init setup_vm_debug(char *str)
void page_init_poison(struct page *page, size_t size)
\n
      3 struct page *page
      2 const char *reason
      1 size_t size
      1 page_init_poison
      1 const struct vm_area_struct *vma
      1 const struct mm_struct *mm
      1 char *str
