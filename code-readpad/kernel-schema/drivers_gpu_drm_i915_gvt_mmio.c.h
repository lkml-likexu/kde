
\n
int intel_vgpu_gpa_to_mmio_offset(struct intel_vgpu *vgpu, u64 gpa)
static void failsafe_emulate_mmio_rw(struct intel_vgpu *vgpu, uint64_t pa, void *p_data, unsigned int bytes, bool read)
int intel_vgpu_emulate_mmio_read(struct intel_vgpu *vgpu, uint64_t pa, void *p_data, unsigned int bytes)
int intel_vgpu_emulate_mmio_write(struct intel_vgpu *vgpu, uint64_t pa, void *p_data, unsigned int bytes)
void intel_vgpu_reset_mmio(struct intel_vgpu *vgpu, bool dmlr)
int intel_vgpu_init_mmio(struct intel_vgpu *vgpu)
void intel_vgpu_clean_mmio(struct intel_vgpu *vgpu)
\n
      7 struct intel_vgpu *vgpu
      3 void *p_data
      3 unsigned int bytes
      3 uint64_t pa
      1 u64 gpa
      1 bool read
      1 bool dmlr
