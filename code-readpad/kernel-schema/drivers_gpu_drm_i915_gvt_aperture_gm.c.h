
\n
static int alloc_gm(struct intel_vgpu *vgpu, bool high_gm)
static int alloc_vgpu_gm(struct intel_vgpu *vgpu)
static void free_vgpu_gm(struct intel_vgpu *vgpu)
void intel_vgpu_write_fence(struct intel_vgpu *vgpu, u32 fence, u64 value)
static void _clear_vgpu_fence(struct intel_vgpu *vgpu)
static void free_vgpu_fence(struct intel_vgpu *vgpu)
static int alloc_vgpu_fence(struct intel_vgpu *vgpu)
static void free_resource(struct intel_vgpu *vgpu)
static int alloc_resource(struct intel_vgpu *vgpu, struct intel_vgpu_creation_params *param)
void intel_vgpu_free_resource(struct intel_vgpu *vgpu)
void intel_vgpu_reset_resource(struct intel_vgpu *vgpu)
int intel_vgpu_alloc_resource(struct intel_vgpu *vgpu, struct intel_vgpu_creation_params *param)
\n
     12 struct intel_vgpu *vgpu
      2 struct intel_vgpu_creation_params *param
      1 u64 value
      1 u32 fence
      1 bool high_gm
