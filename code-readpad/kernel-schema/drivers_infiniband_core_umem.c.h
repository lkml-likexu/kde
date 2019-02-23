
\n
static void __ib_umem_release(struct ib_device *dev, struct ib_umem *umem, int dirty)
struct ib_umem *ib_umem_get(struct ib_ucontext *context, unsigned long addr, size_t size, int access, int dmasync)
static void __ib_umem_release_tail(struct ib_umem *umem)
static void ib_umem_release_defer(struct work_struct *work)
void ib_umem_release(struct ib_umem *umem)
int ib_umem_page_count(struct ib_umem *umem)
int ib_umem_copy_from(void *dst, struct ib_umem *umem, size_t offset, size_t length)
\n
      5 struct ib_umem *umem
      1 void *dst
      1 unsigned long addr
      1 struct work_struct *work
      1 struct ib_ucontext *context
      1 struct ib_device *dev
      1 size_t size
      1 size_t offset
      1 size_t length
      1 int dmasync
      1 int dirty
      1 int access
