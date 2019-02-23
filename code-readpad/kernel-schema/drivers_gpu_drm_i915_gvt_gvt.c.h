
\n
static struct intel_vgpu_type *intel_gvt_find_vgpu_type(struct intel_gvt *gvt, const char *name)
static ssize_t available_instances_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t device_api_show(struct kobject *kobj, struct device *dev, char *buf)
static ssize_t description_show(struct kobject *kobj, struct device *dev, char *buf)
static bool intel_get_gvt_attrs(struct attribute ***type_attrs, struct attribute_group ***intel_vgpu_type_groups)
static bool intel_gvt_init_vgpu_type_groups(struct intel_gvt *gvt)
static void intel_gvt_cleanup_vgpu_type_groups(struct intel_gvt *gvt)
int intel_gvt_init_host(void)
static void init_device_info(struct intel_gvt *gvt)
static int gvt_service_thread(void *data)
static void clean_service_thread(struct intel_gvt *gvt)
static int init_service_thread(struct intel_gvt *gvt)
void intel_gvt_clean_device(struct drm_i915_private *dev_priv)
int intel_gvt_init_device(struct drm_i915_private *dev_priv)
\n
      6 struct intel_gvt *gvt
      3 struct kobject *kobj
      3 struct device *dev
      3 char *buf
      2 struct drm_i915_private *dev_priv
      1 void *data
      1 void
      1 struct attribute ***type_attrs
      1 struct attribute_group ***intel_vgpu_type_groups
      1 const char *name
