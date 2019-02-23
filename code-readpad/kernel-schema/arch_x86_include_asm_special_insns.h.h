
\n
static inline unsigned long native_read_cr0(void)
static inline void native_write_cr0(unsigned long val)
static inline unsigned long native_read_cr2(void)
static inline void native_write_cr2(unsigned long val)
static inline unsigned long __native_read_cr3(void)
static inline void native_write_cr3(unsigned long val)
static inline unsigned long native_read_cr4(void)
static inline void native_write_cr4(unsigned long val)
static inline unsigned long native_read_cr8(void)
static inline void native_write_cr8(unsigned long val)
static inline u32 __read_pkru(void)
static inline void __write_pkru(u32 pkru)
asm volatile(".byte 0x0f, 0x01, 0xef\n\t": : "a" (pkru)
, "c"(ecx)
, "d"(edx)
)
; } static inline u32 __read_pkru(void)
static inline void __write_pkru(u32 pkru)
static inline void native_wbinvd(void)
static inline unsigned long __read_cr4(void)
static inline unsigned long read_cr0(void)
static inline void write_cr0(unsigned long x)
static inline unsigned long read_cr2(void)
static inline void write_cr2(unsigned long x)
static inline unsigned long __read_cr3(void)
static inline void write_cr3(unsigned long x)
static inline void __write_cr4(unsigned long x)
static inline void wbinvd(void)
static inline unsigned long read_cr8(void)
static inline void write_cr8(unsigned long x)
static inline void load_gs_index(unsigned selector)
static inline void clflush(volatile void *__p)
static inline void clflushopt(volatile void *__p)
static inline void clwb(volatile void *__p)
\n
     14 void
      5 unsigned long x
      5 unsigned long val
      3 volatile void *__p
      2 u32 pkru
      1 unsigned selector
      1 edx
      1 ecx
      1 ".byte 0x0f
      1 0xef\n\t": : "a" pkru
      1 0x01
