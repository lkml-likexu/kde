
\n
bool can_do_mlock(void)
void clear_page_mlock(struct page *page)
void mlock_vma_page(struct page *page)
static bool __munlock_isolate_lru_page(struct page *page, bool getpage)
static void __munlock_isolated_page(struct page *page)
static void __munlock_isolation_failed(struct page *page)
unsigned int munlock_vma_page(struct page *page)
static int __mlock_posix_error_return(long retval)
static bool __putback_lru_fast_prepare(struct page *page, struct pagevec *pvec, int *pgrescued)
static void __putback_lru_fast(struct pagevec *pvec, int pgrescued)
static void __munlock_pagevec(struct pagevec *pvec, struct zone *zone)
static unsigned long __munlock_pagevec_fill(struct pagevec *pvec, struct vm_area_struct *vma, struct zone *zone, unsigned long start, unsigned long end)
void munlock_vma_pages_range(struct vm_area_struct *vma, unsigned long start, unsigned long end)
static int mlock_fixup(struct vm_area_struct *vma, struct vm_area_struct **prev, unsigned long start, unsigned long end, vm_flags_t newflags)
static int apply_vma_lock_flags(unsigned long start, size_t len, vm_flags_t flags)
static int count_mm_mlocked_page_nr(struct mm_struct *mm, unsigned long start, size_t len)
static __must_check int do_mlock(unsigned long start, size_t len, vm_flags_t flags)
SYSCALL_DEFINE2(mlock, unsigned long, start, size_t, len)
SYSCALL_DEFINE3(mlock2, unsigned long, start, size_t, len, int, flags)
SYSCALL_DEFINE2(munlock, unsigned long, start, size_t, len)
static int apply_mlockall_flags(int flags)
SYSCALL_DEFINE1(mlockall, int, flags)
SYSCALL_DEFINE0(munlockall)
int user_shm_lock(size_t size, struct user_struct *user)
void user_shm_unlock(size_t size, struct user_struct *user)
\n
      7 struct page *page
      6 unsigned long start
      4 struct pagevec *pvec
      3 unsigned long end
      3 unsigned long
      3 struct vm_area_struct *vma
      3 start
      3 size_t len
      3 size_t
      3 len
      2 vm_flags_t flags
      2 struct zone *zone
      2 struct user_struct *user
      2 size_t size
      2 int
      2 flags
      1 void
      1 vm_flags_t newflags
      1 struct vm_area_struct **prev
      1 struct mm_struct *mm
      1 munlockall
      1 munlock
      1 mlockall
      1 mlock2
      1 mlock
      1 long retval
      1 int *pgrescued
      1 int pgrescued
      1 int flags
      1 bool getpage
