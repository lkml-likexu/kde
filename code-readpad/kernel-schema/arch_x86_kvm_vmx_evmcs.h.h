
\n
static __always_inline int get_evmcs_offset(unsigned long field, u16 *clean_field)
static inline void evmcs_write64(unsigned long field, u64 value)
static inline void evmcs_write32(unsigned long field, u32 value)
static inline void evmcs_write16(unsigned long field, u16 value)
static inline u64 evmcs_read64(unsigned long field)
static inline u32 evmcs_read32(unsigned long field)
static inline u16 evmcs_read16(unsigned long field)
static inline void evmcs_touch_msr_bitmap(void)
static inline void evmcs_load(u64 phys_addr)
\n
      7 unsigned long field
      1 void
      1 u64 value
      1 u64 phys_addr
      1 u32 value
      1 u16 value
      1 u16 *clean_field
