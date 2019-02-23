
\n
static inline int vmxon(uint64_t phys)
static inline void vmxoff(void)
static inline int vmclear(uint64_t vmcs_pa)
static inline int vmptrld(uint64_t vmcs_pa)
static inline int vmptrst(uint64_t *value)
static inline uint64_t vmptrstz(void)
static inline int vmlaunch(void)
static inline int vmresume(void)
static inline void vmcall(void)
static inline int vmread(uint64_t encoding, uint64_t *value)
static inline uint64_t vmreadz(uint64_t encoding)
static inline int vmwrite(uint64_t encoding, uint64_t value)
static inline uint32_t vmcs_revision(void)
\n
      6 void
      3 uint64_t encoding
      2 uint64_t vmcs_pa
      2 uint64_t *value
      1 uint64_t value
      1 uint64_t phys
