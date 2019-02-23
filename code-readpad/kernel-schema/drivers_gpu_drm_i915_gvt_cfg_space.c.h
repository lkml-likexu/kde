
\n
static void vgpu_pci_cfg_mem_write(struct intel_vgpu *vgpu, unsigned int off, u8 *src, unsigned int bytes)
int intel_vgpu_emulate_cfg_read(struct intel_vgpu *vgpu, unsigned int offset, void *p_data, unsigned int bytes)
static int map_aperture(struct intel_vgpu *vgpu, bool map)
static int trap_gttmmio(struct intel_vgpu *vgpu, bool trap)
static int emulate_pci_command_write(struct intel_vgpu *vgpu, unsigned int offset, void *p_data, unsigned int bytes)
static int emulate_pci_rom_bar_write(struct intel_vgpu *vgpu, unsigned int offset, void *p_data, unsigned int bytes)
static int emulate_pci_bar_write(struct intel_vgpu *vgpu, unsigned int offset, void *p_data, unsigned int bytes)
int intel_vgpu_emulate_cfg_write(struct intel_vgpu *vgpu, unsigned int offset, void *p_data, unsigned int bytes)
void intel_vgpu_init_cfg_space(struct intel_vgpu *vgpu, bool primary)
void intel_vgpu_reset_cfg_space(struct intel_vgpu *vgpu)
\n
     10 struct intel_vgpu *vgpu
      6 unsigned int bytes
      5 void *p_data
      5 unsigned int offset
      1 unsigned int off
      1 u8 *src
      1 bool trap
      1 bool primary
      1 bool map
