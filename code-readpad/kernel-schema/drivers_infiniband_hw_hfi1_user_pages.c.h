
\n
bool hfi1_can_pin_pages(struct hfi1_devdata *dd, struct mm_struct *mm, u32 nlocked, u32 npages)
int hfi1_acquire_user_pages(struct mm_struct *mm, unsigned long vaddr, size_t npages, bool writable, struct page **pages)
void hfi1_release_user_pages(struct mm_struct *mm, struct page **p, size_t npages, bool dirty)
\n
      3 struct mm_struct *mm
      2 size_t npages
      1 unsigned long vaddr
      1 u32 npages
      1 u32 nlocked
      1 struct page **pages
      1 struct page **p
      1 struct hfi1_devdata *dd
      1 bool writable
      1 bool dirty
