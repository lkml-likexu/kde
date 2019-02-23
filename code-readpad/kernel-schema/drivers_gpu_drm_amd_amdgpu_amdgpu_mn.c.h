
\n
static void amdgpu_mn_destroy(struct work_struct *work)
static void amdgpu_mn_release(struct mmu_notifier *mn, struct mm_struct *mm)
void amdgpu_mn_lock(struct amdgpu_mn *mn)
void amdgpu_mn_unlock(struct amdgpu_mn *mn)
static int amdgpu_mn_read_lock(struct amdgpu_mn *amn, bool blockable)
static void amdgpu_mn_read_unlock(struct amdgpu_mn *amn)
static void amdgpu_mn_invalidate_node(struct amdgpu_mn_node *node, unsigned long start, unsigned long end)
static int amdgpu_mn_invalidate_range_start_gfx(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static int amdgpu_mn_invalidate_range_start_hsa(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static void amdgpu_mn_invalidate_range_end(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
struct amdgpu_mn *amdgpu_mn_get(struct amdgpu_device *adev, enum amdgpu_mn_type type)
int amdgpu_mn_register(struct amdgpu_bo *bo, unsigned long addr)
void amdgpu_mn_unregister(struct amdgpu_bo *bo)
\n
      4 struct mmu_notifier *mn
      3 const struct mmu_notifier_range *range
      2 struct amdgpu_mn *mn
      2 struct amdgpu_mn *amn
      2 struct amdgpu_bo *bo
      1 unsigned long start
      1 unsigned long end
      1 unsigned long addr
      1 struct work_struct *work
      1 struct mm_struct *mm
      1 struct amdgpu_mn_node *node
      1 struct amdgpu_device *adev
      1 enum amdgpu_mn_type type
      1 bool blockable
