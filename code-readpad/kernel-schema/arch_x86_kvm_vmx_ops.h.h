
\n
static __always_inline void vmcs_check16(unsigned long field)
static __always_inline void vmcs_check32(unsigned long field)
static __always_inline void vmcs_check64(unsigned long field)
static __always_inline void vmcs_checkl(unsigned long field)
static __always_inline unsigned long __vmcs_readl(unsigned long field)
static __always_inline u16 vmcs_read16(unsigned long field)
static __always_inline u32 vmcs_read32(unsigned long field)
static __always_inline u64 vmcs_read64(unsigned long field)
static __always_inline unsigned long vmcs_readl(unsigned long field)
static noinline void vmwrite_error(unsigned long field, unsigned long value)
static __always_inline void __vmcs_writel(unsigned long field, unsigned long value)
static __always_inline void vmcs_write16(unsigned long field, u16 value)
static __always_inline void vmcs_write32(unsigned long field, u32 value)
static __always_inline void vmcs_write64(unsigned long field, u64 value)
static __always_inline void vmcs_writel(unsigned long field, unsigned long value)
static __always_inline void vmcs_clear_bits(unsigned long field, u32 mask)
static __always_inline void vmcs_set_bits(unsigned long field, u32 mask)
static inline void vmcs_clear(struct vmcs *vmcs)
static inline void vmcs_load(struct vmcs *vmcs)
static inline void __invvpid(unsigned long ext, u16 vpid, gva_t gva)
static inline void __invept(unsigned long ext, u64 eptp, gpa_t gpa)
static inline bool vpid_sync_vcpu_addr(int vpid, gva_t addr)
static inline void vpid_sync_vcpu_single(int vpid)
static inline void vpid_sync_vcpu_global(void)
static inline void vpid_sync_context(int vpid)
static inline void ept_sync_global(void)
static inline void ept_sync_context(u64 eptp)
\n
     17 unsigned long field
      3 unsigned long value
      3 int vpid
      2 void
      2 unsigned long ext
      2 u64 eptp
      2 u32 mask
      2 struct vmcs *vmcs
      1 u64 value
      1 u32 value
      1 u16 vpid
      1 u16 value
      1 gva_t gva
      1 gva_t addr
      1 gpa_t gpa
