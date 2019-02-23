
\n
static inline unsigned int idr_get_cursor(const struct idr *idr)
static inline void idr_set_cursor(struct idr *idr, unsigned int val)
static inline void idr_init_base(struct idr *idr, int base)
static inline void idr_init(struct idr *idr)
static inline bool idr_is_empty(const struct idr *idr)
static inline void idr_preload_end(void)
static inline int ida_alloc(struct ida *ida, gfp_t gfp)
static inline int ida_alloc_min(struct ida *ida, unsigned int min, gfp_t gfp)
static inline int ida_alloc_max(struct ida *ida, unsigned int max, gfp_t gfp)
static inline void ida_init(struct ida *ida)
static inline bool ida_is_empty(const struct ida *ida)
\n
      4 struct ida *ida
      3 struct idr *idr
      3 gfp_t gfp
      2 const struct idr *idr
      1 void
      1 unsigned int val
      1 unsigned int min
      1 unsigned int max
      1 int base
      1 const struct ida *ida
