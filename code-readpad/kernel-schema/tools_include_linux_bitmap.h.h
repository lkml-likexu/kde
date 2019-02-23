
\n
static inline void bitmap_zero(unsigned long *dst, int nbits)
static inline void bitmap_fill(unsigned long *dst, unsigned int nbits)
static inline int bitmap_empty(const unsigned long *src, unsigned nbits)
static inline int bitmap_full(const unsigned long *src, unsigned int nbits)
static inline int bitmap_weight(const unsigned long *src, int nbits)
static inline void bitmap_or(unsigned long *dst, const unsigned long *src1, const unsigned long *src2, int nbits)
static inline int test_and_set_bit(int nr, unsigned long *addr)
static inline int test_and_clear_bit(int nr, unsigned long *addr)
static inline unsigned long *bitmap_alloc(int nbits)
static inline int bitmap_and(unsigned long *dst, const unsigned long *src1, const unsigned long *src2, unsigned int nbits)
\n
      4 unsigned long *dst
      4 int nbits
      3 unsigned int nbits
      3 const unsigned long *src
      2 unsigned long *addr
      2 int nr
      2 const unsigned long *src2
      2 const unsigned long *src1
      1 unsigned nbits
