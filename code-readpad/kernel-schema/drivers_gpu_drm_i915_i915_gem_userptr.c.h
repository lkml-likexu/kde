
\n
static void cancel_userptr(struct work_struct *work)
static void add_object(struct i915_mmu_object *mo)
static void del_object(struct i915_mmu_object *mo)
static int i915_gem_userptr_mn_invalidate_range_start(struct mmu_notifier *_mn, const struct mmu_notifier_range *range)
static struct i915_mmu_notifier * i915_mmu_notifier_create(struct mm_struct *mm)
static void i915_gem_userptr_release__mmu_notifier(struct drm_i915_gem_object *obj)
static struct i915_mmu_notifier * i915_mmu_notifier_find(struct i915_mm_struct *mm)
static int i915_gem_userptr_init__mmu_notifier(struct drm_i915_gem_object *obj, unsigned flags)
static void i915_mmu_notifier_free(struct i915_mmu_notifier *mn, struct mm_struct *mm)
static void i915_gem_userptr_release__mmu_notifier(struct drm_i915_gem_object *obj)
static int i915_gem_userptr_init__mmu_notifier(struct drm_i915_gem_object *obj, unsigned flags)
static void i915_mmu_notifier_free(struct i915_mmu_notifier *mn, struct mm_struct *mm)
static struct i915_mm_struct * __i915_mm_struct_find(struct drm_i915_private *dev_priv, struct mm_struct *real)
static int i915_gem_userptr_init__mm_struct(struct drm_i915_gem_object *obj)
static void __i915_mm_struct_free__worker(struct work_struct *work)
static void __i915_mm_struct_free(struct kref *kref)
static void i915_gem_userptr_release__mm_struct(struct drm_i915_gem_object *obj)
static struct sg_table * __i915_gem_userptr_alloc_pages(struct drm_i915_gem_object *obj, struct page **pvec, int num_pages)
static int __i915_gem_userptr_set_active(struct drm_i915_gem_object *obj, bool value)
static void __i915_gem_userptr_get_pages_worker(struct work_struct *_work)
static struct sg_table * __i915_gem_userptr_get_pages_schedule(struct drm_i915_gem_object *obj)
static int i915_gem_userptr_get_pages(struct drm_i915_gem_object *obj)
static void i915_gem_userptr_put_pages(struct drm_i915_gem_object *obj, struct sg_table *pages)
static void i915_gem_userptr_release(struct drm_i915_gem_object *obj)
static int i915_gem_userptr_dmabuf_export(struct drm_i915_gem_object *obj)
int i915_gem_userptr_ioctl(struct drm_device *dev, void *data, struct drm_file *file)
int i915_gem_init_userptr(struct drm_i915_private *dev_priv)
void i915_gem_cleanup_userptr(struct drm_i915_private *dev_priv)
\n
     13 struct drm_i915_gem_object *obj
      3 struct mm_struct *mm
      3 struct drm_i915_private *dev_priv
      2 unsigned flags
      2 struct work_struct *work
      2 struct i915_mmu_object *mo
      2 struct i915_mmu_notifier *mn
      1 void *data
      1 struct work_struct *_work
      1 struct sg_table *pages
      1 struct page **pvec
      1 struct mmu_notifier *_mn
      1 struct mm_struct *real
      1 struct kref *kref
      1 struct i915_mm_struct *mm
      1 struct drm_file *file
      1 struct drm_device *dev
      1 int num_pages
      1 const struct mmu_notifier_range *range
      1 bool value
