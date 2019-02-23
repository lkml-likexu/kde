
\n
static inline int gfpflags_to_migratetype(const gfp_t gfp_flags)
static inline bool gfpflags_allow_blocking(const gfp_t gfp_flags)
static inline enum zone_type gfp_zone(gfp_t flags)
static inline int gfp_zonelist(gfp_t flags)
static inline struct zonelist *node_zonelist(int nid, gfp_t flags)
static inline struct page * __alloc_pages(gfp_t gfp_mask, unsigned int order, int preferred_nid)
static inline struct page * __alloc_pages_node(int nid, gfp_t gfp_mask, unsigned int order)
static inline struct page *alloc_pages_node(int nid, gfp_t gfp_mask, unsigned int order)
static inline struct page * alloc_pages(gfp_t gfp_mask, unsigned int order)
extern bool pm_suspended_storage(void)
; static inline bool pm_suspended_storage(void)
\n
      4 unsigned int order
      4 gfp_t gfp_mask
      3 int nid
      3 gfp_t flags
      2 void
      2 const gfp_t gfp_flags
      1 int preferred_nid
