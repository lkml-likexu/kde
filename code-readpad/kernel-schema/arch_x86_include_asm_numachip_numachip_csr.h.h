
\n
static inline void *lcsr_address(unsigned long offset)
static inline unsigned int read_lcsr(unsigned long offset)
static inline void write_lcsr(unsigned long offset, unsigned int val)
static inline void __iomem *numachip2_lcsr_address(unsigned long offset)
static inline u32 numachip2_read32_lcsr(unsigned long offset)
static inline u64 numachip2_read64_lcsr(unsigned long offset)
static inline void numachip2_write32_lcsr(unsigned long offset, u32 val)
static inline void numachip2_write64_lcsr(unsigned long offset, u64 val)
static inline unsigned int numachip2_timer(void)
\n
      8 unsigned long offset
      1 void
      1 unsigned int val
      1 u64 val
      1 u32 val
