
\n
static void radeon_mn_destroy(struct work_struct *work)
static void radeon_mn_release(struct mmu_notifier *mn, struct mm_struct *mm)
static int radeon_mn_invalidate_range_start(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static struct radeon_mn *radeon_mn_get(struct radeon_device *rdev)
int radeon_mn_register(struct radeon_bo *bo, unsigned long addr)
void radeon_mn_unregister(struct radeon_bo *bo)
\n
      2 struct radeon_bo *bo
      2 struct mmu_notifier *mn
      1 unsigned long addr
      1 struct work_struct *work
      1 struct radeon_device *rdev
      1 struct mm_struct *mm
      1 const struct mmu_notifier_range *range
