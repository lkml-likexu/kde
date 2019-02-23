
\n
static __always_inline void set_bit(long nr, volatile unsigned long *addr)
static __always_inline void __set_bit(long nr, volatile unsigned long *addr)
static __always_inline void clear_bit(long nr, volatile unsigned long *addr)
static __always_inline void clear_bit_unlock(long nr, volatile unsigned long *addr)
static __always_inline void __clear_bit(long nr, volatile unsigned long *addr)
static __always_inline bool clear_bit_unlock_is_negative_byte(long nr, volatile unsigned long *addr)
static __always_inline void __clear_bit_unlock(long nr, volatile unsigned long *addr)
static __always_inline void __change_bit(long nr, volatile unsigned long *addr)
static __always_inline void change_bit(long nr, volatile unsigned long *addr)
static __always_inline bool test_and_set_bit(long nr, volatile unsigned long *addr)
static __always_inline bool test_and_set_bit_lock(long nr, volatile unsigned long *addr)
static __always_inline bool __test_and_set_bit(long nr, volatile unsigned long *addr)
static __always_inline bool test_and_clear_bit(long nr, volatile unsigned long *addr)
static __always_inline bool __test_and_clear_bit(long nr, volatile unsigned long *addr)
static __always_inline bool __test_and_change_bit(long nr, volatile unsigned long *addr)
static __always_inline bool test_and_change_bit(long nr, volatile unsigned long *addr)
static __always_inline bool constant_test_bit(long nr, const volatile unsigned long *addr)
static __always_inline bool variable_test_bit(long nr, volatile const unsigned long *addr)
static __always_inline unsigned long __ffs(unsigned long word)
static __always_inline unsigned long ffz(unsigned long word)
static __always_inline unsigned long __fls(unsigned long word)
static __always_inline int ffs(int x)
static __always_inline int fls(unsigned int x)
static __always_inline int fls64(__u64 x)
\n
     18 long nr
     16 volatile unsigned long *addr
      3 unsigned long word
      1 volatile const unsigned long *addr
      1 unsigned int x
      1 __u64 x
      1 int x
      1 const volatile unsigned long *addr
