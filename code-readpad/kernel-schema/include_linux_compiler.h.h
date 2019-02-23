
\n
static __always_inline void __read_once_size(const volatile void *p, void *res, int size)
static __no_kasan_or_inline void __read_once_size_nocheck(const volatile void *p, void *res, int size)
static __always_inline void __write_once_size(volatile void *p, void *res, int size)
static __no_kasan_or_inline unsigned long read_word_at_a_time(const void *addr)
static inline void *offset_to_ptr(const int *off)
\n
      3 void *res
      3 int size
      2 const volatile void *p
      1 volatile void *p
      1 const void *addr
      1 const int *off
