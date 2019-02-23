
EXPORT_SYMBOL_GPL(mmu_notifier_call_srcu);
EXPORT_SYMBOL_GPL(__mmu_notifier_invalidate_range_start);
EXPORT_SYMBOL_GPL(__mmu_notifier_invalidate_range_end);
EXPORT_SYMBOL_GPL(__mmu_notifier_invalidate_range);
EXPORT_SYMBOL_GPL(mmu_notifier_register);
EXPORT_SYMBOL_GPL(__mmu_notifier_register);
EXPORT_SYMBOL_GPL(mmu_notifier_unregister);
EXPORT_SYMBOL_GPL(mmu_notifier_unregister_no_release);
\n
void mmu_notifier_call_srcu(struct rcu_head *rcu, void (*func)
(struct rcu_head *rcu)
)
void __mmu_notifier_release(struct mm_struct *mm)
int __mmu_notifier_clear_flush_young(struct mm_struct *mm, unsigned long start, unsigned long end)
int __mmu_notifier_clear_young(struct mm_struct *mm, unsigned long start, unsigned long end)
int __mmu_notifier_test_young(struct mm_struct *mm, unsigned long address)
void __mmu_notifier_change_pte(struct mm_struct *mm, unsigned long address, pte_t pte)
int __mmu_notifier_invalidate_range_start(struct mmu_notifier_range *range)
void __mmu_notifier_invalidate_range_end(struct mmu_notifier_range *range, bool only_end)
void __mmu_notifier_invalidate_range(struct mm_struct *mm, unsigned long start, unsigned long end)
static int do_mmu_notifier_register(struct mmu_notifier *mn, struct mm_struct *mm, int take_mmap_sem)
int mmu_notifier_register(struct mmu_notifier *mn, struct mm_struct *mm)
int __mmu_notifier_register(struct mmu_notifier *mn, struct mm_struct *mm)
void __mmu_notifier_mm_destroy(struct mm_struct *mm)
void mmu_notifier_unregister(struct mmu_notifier *mn, struct mm_struct *mm)
void mmu_notifier_unregister_no_release(struct mmu_notifier *mn, struct mm_struct *mm)
\n
     12 struct mm_struct *mm
      5 struct mmu_notifier *mn
      3 unsigned long start
      3 unsigned long end
      2 unsigned long address
      2 struct rcu_head *rcu
      2 struct mmu_notifier_range *range
      1 void *func
      1 pte_t pte
      1 mmu_notifier_unregister_no_release
      1 mmu_notifier_unregister
      1 mmu_notifier_register
      1 __mmu_notifier_register
      1 __mmu_notifier_invalidate_range_start
      1 __mmu_notifier_invalidate_range_end
      1 __mmu_notifier_invalidate_range
      1 mmu_notifier_call_srcu
      1 int take_mmap_sem
      1 bool only_end
