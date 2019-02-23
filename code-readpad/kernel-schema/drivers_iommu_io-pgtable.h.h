
\n
static inline void io_pgtable_tlb_flush_all(struct io_pgtable *iop)
static inline void io_pgtable_tlb_add_flush(struct io_pgtable *iop, unsigned long iova, size_t size, size_t granule, bool leaf)
static inline void io_pgtable_tlb_sync(struct io_pgtable *iop)
\n
      3 struct io_pgtable *iop
      1 unsigned long iova
      1 size_t size
      1 size_t granule
      1 bool leaf
