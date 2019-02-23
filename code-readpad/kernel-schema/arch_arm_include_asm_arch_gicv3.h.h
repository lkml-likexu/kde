
\n
define CPUIF_MAP(a32, a64)
\ static inline void write_a64(u32 val)
\define CPUIF_MAP(a32, a64)
\ static inline void write_a64(u32 val)
\write_sysreg(val, a32)
; \ }\ static inline u32 read_a64(void)
\define CPUIF_MAP_LO_HI(a32lo, a32hi, a64)
\ static inline void write_a64(u64 val)
\define CPUIF_MAP_LO_HI(a32lo, a32hi, a64)
\ static inline void write_a64(u64 val)
\write_sysreg(lower_32_bits(val)
, a32lo)
;\write_sysreg(upper_32_bits(val)
, a32hi)
;\ }\ static inline u64 read_a64(void)
\ static inline void gic_write_eoir(u32 irq)
static inline void gic_write_dir(u32 val)
static inline u32 gic_read_iar(void)
static inline void gic_write_ctlr(u32 val)
static inline u32 gic_read_ctlr(void)
static inline void gic_write_grpen1(u32 val)
static inline void gic_write_sgi1r(u64 val)
static inline u32 gic_read_sre(void)
static inline void gic_write_sre(u32 val)
static inline void gic_write_bpr1(u32 val)
static inline void __gic_writeq_nonatomic(u64 val, volatile void __iomem *addr)
static inline u64 __gic_readq_nonatomic(const volatile void __iomem *addr)
static inline void gits_write_vpendbaser(u64 val, void * __iomem addr)
\n
      7 u32 val
      5 void
      5 u64 val
      4 a64
      3 a32
      2 a32lo
      2 a32hi
      1 volatile void __iomem *addr
      1 void * __iomem addr
      1 val
      1 upper_32_bitsval
      1 u32 irq
      1 lower_32_bitsval
      1 const volatile void __iomem *addr
