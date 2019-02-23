
\n
static int vgpu_gem_get_pages( struct drm_i915_gem_object *obj)
static void vgpu_gem_put_pages(struct drm_i915_gem_object *obj, struct sg_table *pages)
static void dmabuf_gem_object_free(struct kref *kref)
static inline void dmabuf_obj_get(struct intel_vgpu_dmabuf_obj *obj)
static inline void dmabuf_obj_put(struct intel_vgpu_dmabuf_obj *obj)
static void vgpu_gem_release(struct drm_i915_gem_object *gem_obj)
static struct drm_i915_gem_object *vgpu_create_gem(struct drm_device *dev, struct intel_vgpu_fb_info *info)
static bool validate_hotspot(struct intel_vgpu_cursor_plane_format *c)
static int vgpu_get_plane_info(struct drm_device *dev, struct intel_vgpu *vgpu, struct intel_vgpu_fb_info *info, int plane_id)
static struct intel_vgpu_dmabuf_obj * pick_dmabuf_by_info(struct intel_vgpu *vgpu, struct intel_vgpu_fb_info *latest_info)
static struct intel_vgpu_dmabuf_obj * pick_dmabuf_by_num(struct intel_vgpu *vgpu, u32 id)
static void update_fb_info(struct vfio_device_gfx_plane_info *gvt_dmabuf, struct intel_vgpu_fb_info *fb_info)
int intel_vgpu_query_plane(struct intel_vgpu *vgpu, void *args)
int intel_vgpu_get_dmabuf(struct intel_vgpu *vgpu, unsigned int dmabuf_id)
void intel_vgpu_dmabuf_cleanup(struct intel_vgpu *vgpu)
\n
      6 struct intel_vgpu *vgpu
      2 struct intel_vgpu_fb_info *info
      2 struct intel_vgpu_dmabuf_obj *obj
      2 struct drm_i915_gem_object *obj
      2 struct drm_device *dev
      1 void *args
      1 unsigned int dmabuf_id
      1 u32 id
      1 struct vfio_device_gfx_plane_info *gvt_dmabuf
      1 struct sg_table *pages
      1 struct kref *kref
      1 struct intel_vgpu_fb_info *latest_info
      1 struct intel_vgpu_fb_info *fb_info
      1 struct intel_vgpu_cursor_plane_format *c
      1 struct drm_i915_gem_object *gem_obj
      1 int plane_id
