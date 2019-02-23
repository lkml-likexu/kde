
\n
static inline int enable_vp_assist(uint64_t vp_assist_pa, void *vp_assist)
static inline int evmcs_vmptrld(uint64_t vmcs_pa, void *vmcs)
static inline int evmcs_vmptrst(uint64_t *value)
static inline int evmcs_vmread(uint64_t encoding, uint64_t *value)
static inline int evmcs_vmwrite(uint64_t encoding, uint64_t value)
static inline int evmcs_vmlaunch(void)
static inline int evmcs_vmresume(void)
\n
      2 void
      2 uint64_t *value
      2 uint64_t encoding
      1 void *vp_assist
      1 void *vmcs
      1 uint64_t vp_assist_pa
      1 uint64_t vmcs_pa
      1 uint64_t value
