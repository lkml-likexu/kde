
\n
void populate_pvinfo_page(struct intel_vgpu *vgpu)
int intel_gvt_init_vgpu_types(struct intel_gvt *gvt)
void intel_gvt_clean_vgpu_types(struct intel_gvt *gvt)
static void intel_gvt_update_vgpu_types(struct intel_gvt *gvt)
void intel_gvt_activate_vgpu(struct intel_vgpu *vgpu)
void intel_gvt_deactivate_vgpu(struct intel_vgpu *vgpu)
void intel_gvt_release_vgpu(struct intel_vgpu *vgpu)
void intel_gvt_destroy_vgpu(struct intel_vgpu *vgpu)
struct intel_vgpu *intel_gvt_create_idle_vgpu(struct intel_gvt *gvt)
void intel_gvt_destroy_idle_vgpu(struct intel_vgpu *vgpu)
static struct intel_vgpu *__intel_gvt_create_vgpu(struct intel_gvt *gvt, struct intel_vgpu_creation_params *param)
struct intel_vgpu *intel_gvt_create_vgpu(struct intel_gvt *gvt, struct intel_vgpu_type *type)
void intel_gvt_reset_vgpu_locked(struct intel_vgpu *vgpu, bool dmlr, unsigned int engine_mask)
void intel_gvt_reset_vgpu(struct intel_vgpu *vgpu)
\n
      8 struct intel_vgpu *vgpu
      6 struct intel_gvt *gvt
      1 unsigned int engine_mask
      1 struct intel_vgpu_type *type
      1 struct intel_vgpu_creation_params *param
      1 bool dmlr
