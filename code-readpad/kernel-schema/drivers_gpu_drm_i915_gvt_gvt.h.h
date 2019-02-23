
\n
static inline struct intel_gvt *to_gvt(struct drm_i915_private *i915)
static inline void intel_gvt_request_service(struct intel_gvt *gvt, int service)
static inline void intel_vgpu_write_pci_bar(struct intel_vgpu *vgpu, u32 offset, u32 val, bool low)
static inline u64 intel_vgpu_get_bar_gpa(struct intel_vgpu *vgpu, int bar)
static inline void mmio_hw_access_pre(struct drm_i915_private *dev_priv)
static inline void mmio_hw_access_post(struct drm_i915_private *dev_priv)
static inline void intel_gvt_mmio_set_accessed(struct intel_gvt *gvt, unsigned int offset)
static inline bool intel_gvt_mmio_is_cmd_access(struct intel_gvt *gvt, unsigned int offset)
static inline bool intel_gvt_mmio_is_unalign(struct intel_gvt *gvt, unsigned int offset)
static inline void intel_gvt_mmio_set_cmd_accessed(struct intel_gvt *gvt, unsigned int offset)
static inline bool intel_gvt_mmio_has_mode_mask(struct intel_gvt *gvt, unsigned int offset)
static inline bool intel_gvt_mmio_is_in_ctx(struct intel_gvt *gvt, unsigned int offset)
static inline void intel_gvt_mmio_set_in_ctx(struct intel_gvt *gvt, unsigned int offset)
\n
      8 struct intel_gvt *gvt
      7 unsigned int offset
      2 struct intel_vgpu *vgpu
      2 struct drm_i915_private *dev_priv
      1 u32 val
      1 u32 offset
      1 struct drm_i915_private *i915
      1 int service
      1 int bar
      1 bool low
