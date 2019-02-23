
\n
static inline int mm_has_notifiers(struct mm_struct *mm)
static inline void mmu_notifier_release(struct mm_struct *mm)
static inline int mmu_notifier_clear_flush_young(struct mm_struct *mm, unsigned long start, unsigned long end)
static inline int mmu_notifier_clear_young(struct mm_struct *mm, unsigned long start, unsigned long end)
static inline int mmu_notifier_test_young(struct mm_struct *mm, unsigned long address)
static inline void mmu_notifier_change_pte(struct mm_struct *mm, unsigned long address, pte_t pte)
static inline void mmu_notifier_invalidate_range_start(struct mmu_notifier_range *range)
static inline int mmu_notifier_invalidate_range_start_nonblock(struct mmu_notifier_range *range)
static inline void mmu_notifier_invalidate_range_end(struct mmu_notifier_range *range)
static inline void mmu_notifier_invalidate_range_only_end(struct mmu_notifier_range *range)
static inline void mmu_notifier_invalidate_range(struct mm_struct *mm, unsigned long start, unsigned long end)
static inline void mmu_notifier_mm_init(struct mm_struct *mm)
static inline void mmu_notifier_mm_destroy(struct mm_struct *mm)
static inline void mmu_notifier_range_init(struct mmu_notifier_range *range, struct mm_struct *mm, unsigned long start, unsigned long end)
static inline void _mmu_notifier_range_init(struct mmu_notifier_range *range, unsigned long start, unsigned long end)
static inline int mm_has_notifiers(struct mm_struct *mm)
static inline void mmu_notifier_release(struct mm_struct *mm)
static inline int mmu_notifier_clear_flush_young(struct mm_struct *mm, unsigned long start, unsigned long end)
static inline int mmu_notifier_test_young(struct mm_struct *mm, unsigned long address)
static inline void mmu_notifier_change_pte(struct mm_struct *mm, unsigned long address, pte_t pte)
static inline void mmu_notifier_invalidate_range_start(struct mmu_notifier_range *range)
static inline int mmu_notifier_invalidate_range_start_nonblock(struct mmu_notifier_range *range)
static inline void mmu_notifier_invalidate_range_end(struct mmu_notifier_range *range)
static inline void mmu_notifier_invalidate_range_only_end(struct mmu_notifier_range *range)
static inline void mmu_notifier_invalidate_range(struct mm_struct *mm, unsigned long start, unsigned long end)
static inline void mmu_notifier_mm_init(struct mm_struct *mm)
static inline void mmu_notifier_mm_destroy(struct mm_struct *mm)
\n
     18 struct mm_struct *mm
     10 struct mmu_notifier_range *range
      7 unsigned long start
      7 unsigned long end
      4 unsigned long address
      2 pte_t pte
