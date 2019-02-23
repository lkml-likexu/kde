
\n
static inline struct ib_umem_odp *to_ib_umem_odp(struct ib_umem *umem)
static inline int ib_umem_mmu_notifier_retry(struct ib_umem_odp *umem_odp, unsigned long mmu_seq)
static inline int ib_umem_odp_get(struct ib_umem_odp *umem_odp, int access)
static inline struct ib_umem_odp * ib_alloc_odp_umem(struct ib_ucontext *context, unsigned long addr, size_t size)
\n
      2 struct ib_umem_odp *umem_odp
      1 unsigned long mmu_seq
      1 unsigned long addr
      1 struct ib_umem *umem
      1 struct ib_ucontext *context
      1 size_t size
      1 int access
