
\n
static inline void mm_init_cpumask(struct mm_struct *mm)
static inline cpumask_t *mm_cpumask(struct mm_struct *mm)
static inline void init_tlb_flush_pending(struct mm_struct *mm)
static inline void inc_tlb_flush_pending(struct mm_struct *mm)
static inline void dec_tlb_flush_pending(struct mm_struct *mm)
static inline bool mm_tlb_flush_pending(struct mm_struct *mm)
static inline bool mm_tlb_flush_nested(struct mm_struct *mm)
\n
      7 struct mm_struct *mm
