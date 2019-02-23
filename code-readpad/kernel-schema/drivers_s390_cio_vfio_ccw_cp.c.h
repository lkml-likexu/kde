
\n
static int pfn_array_alloc_pin(struct pfn_array *pa, struct device *mdev, u64 iova, unsigned int len)
static void pfn_array_unpin_free(struct pfn_array *pa, struct device *mdev)
static int pfn_array_table_init(struct pfn_array_table *pat, int nr)
static void pfn_array_table_unpin_free(struct pfn_array_table *pat, struct device *mdev)
static bool pfn_array_table_iova_pinned(struct pfn_array_table *pat, unsigned long iova)
return false; }static inline void pfn_array_table_idal_create_words(struct pfn_array_table *pat, unsigned long *idaws)
static long copy_from_iova(struct device *mdev, void *to, u64 iova, unsigned long n)
static long copy_ccw_from_iova(struct channel_program *cp, struct ccw1 *to, u64 iova, unsigned long len)
static struct ccwchain *ccwchain_alloc(struct channel_program *cp, int len)
static void ccwchain_free(struct ccwchain *chain)
static void ccwchain_cda_free(struct ccwchain *chain, int idx)
static void cp_unpin_free(struct channel_program *cp)
static int ccwchain_calc_length(u64 iova, struct channel_program *cp)
static int tic_target_chain_exists(struct ccw1 *tic, struct channel_program *cp)
static int ccwchain_handle_tic(struct ccw1 *tic, struct channel_program *cp)
static int ccwchain_loop_tic(struct ccwchain *chain, struct channel_program *cp)
static int ccwchain_fetch_tic(struct ccwchain *chain, int idx, struct channel_program *cp)
static int ccwchain_fetch_direct(struct ccwchain *chain, int idx, struct channel_program *cp)
static int ccwchain_fetch_idal(struct ccwchain *chain, int idx, struct channel_program *cp)
static int ccwchain_fetch_one(struct ccwchain *chain, int idx, struct channel_program *cp)
int cp_init(struct channel_program *cp, struct device *mdev, union orb *orb)
void cp_free(struct channel_program *cp)
int cp_prefetch(struct channel_program *cp)
union orb *cp_get_orb(struct channel_program *cp, u32 intparm, u8 lpm)
void cp_update_scsw(struct channel_program *cp, union scsw *scsw)
bool cp_iova_pinned(struct channel_program *cp, u64 iova)
\n
     17 struct channel_program *cp
      7 struct ccwchain *chain
      5 u64 iova
      5 struct device *mdev
      5 int idx
      4 struct pfn_array_table *pat
      2 struct pfn_array *pa
      2 struct ccw1 *tic
      1 void *to
      1 unsigned long n
      1 unsigned long len
      1 unsigned long iova
      1 unsigned long *idaws
      1 unsigned int len
      1 union scsw *scsw
      1 union orb *orb
      1 u8 lpm
      1 u32 intparm
      1 struct ccw1 *to
      1 int nr
      1 int len
