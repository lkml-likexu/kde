
static __printf(1, 2)
__cold void vringh_bad(const char *fmt, ...)
static inline int __vringh_get_head(const struct vringh *vrh, int (*getu16)
(const struct vringh *vrh, u16 *val, const __virtio16 *p)
, u16 *last_avail_idx)
static inline ssize_t vringh_iov_xfer(struct vringh_kiov *iov, void *ptr, size_t len, int (*xfer)
(void *addr, void *ptr, size_t len)
)
static inline bool range_check(struct vringh *vrh, u64 addr, size_t *len, struct vringh_range *range, bool (*getrange)
(struct vringh *, u64, struct vringh_range *)
)
static inline bool no_range_check(struct vringh *vrh, u64 addr, size_t *len, struct vringh_range *range, bool (*getrange)
(struct vringh *, u64, struct vringh_range *)
)
static int move_to_indirect(const struct vringh *vrh, int *up_next, u16 *i, void *addr, const struct vring_desc *desc, struct vring_desc **descs, int *desc_max)
static int resize_iovec(struct vringh_kiov *iov, gfp_t gfp)
static u16 __cold return_from_indirect(const struct vringh *vrh, int *up_next, struct vring_desc **descs, int *desc_max)
static int slow_copy(struct vringh *vrh, void *dst, const void *src, bool (*rcheck)
(struct vringh *vrh, u64 addr, size_t *len, struct vringh_range *range, bool (*getrange)
(struct vringh *vrh, u64, struct vringh_range *)
)
, bool (*getrange)
(struct vringh *vrh, u64 addr, struct vringh_range *r)
, struct vringh_range *range, int (*copy)
(void *dst, const void *src, size_t len)
)
static inline int __vringh_iov(struct vringh *vrh, u16 i, struct vringh_kiov *riov, struct vringh_kiov *wiov, bool (*rcheck)
(struct vringh *vrh, u64 addr, size_t *len, struct vringh_range *range, bool (*getrange)
(struct vringh *, u64, struct vringh_range *)
)
, bool (*getrange)
(struct vringh *, u64, struct vringh_range *)
, gfp_t gfp, int (*copy)
(void *dst, const void *src, size_t len)
)
static inline int __vringh_complete(struct vringh *vrh, const struct vring_used_elem *used, unsigned int num_used, int (*putu16)
(const struct vringh *vrh, __virtio16 *p, u16 val)
, int (*putused)
(struct vring_used_elem *dst, const struct vring_used_elem*src, unsigned num)
)
static inline int __vringh_need_notify(struct vringh *vrh, int (*getu16)
(const struct vringh *vrh, u16 *val, const __virtio16 *p)
)
static inline bool __vringh_notify_enable(struct vringh *vrh, int (*getu16)
(const struct vringh *vrh, u16 *val, const __virtio16 *p)
, int (*putu16)
(const struct vringh *vrh, __virtio16 *p, u16 val)
)
static inline void __vringh_notify_disable(struct vringh *vrh, int (*putu16)
(const struct vringh *vrh, __virtio16 *p, u16 val)
)
static inline int getu16_user(const struct vringh *vrh, u16 *val, const __virtio16 *p)
static inline int putu16_user(const struct vringh *vrh, __virtio16 *p, u16 val)
static inline int copydesc_user(void *dst, const void *src, size_t len)
static inline int putused_user(struct vring_used_elem *dst, const struct vring_used_elem *src, unsigned int num)
static inline int xfer_from_user(void *src, void *dst, size_t len)
static inline int xfer_to_user(void *dst, void *src, size_t len)
int vringh_init_user(struct vringh *vrh, u64 features, unsigned int num, bool weak_barriers, struct vring_desc __user *desc, struct vring_avail __user *avail, struct vring_used __user *used)
int vringh_getdesc_user(struct vringh *vrh, struct vringh_iov *riov, struct vringh_iov *wiov, bool (*getrange)
(struct vringh *vrh, u64 addr, struct vringh_range *r)
, u16 *head)
ssize_t vringh_iov_pull_user(struct vringh_iov *riov, void *dst, size_t len)
ssize_t vringh_iov_push_user(struct vringh_iov *wiov, const void *src, size_t len)
void vringh_abandon_user(struct vringh *vrh, unsigned int num)
int vringh_complete_user(struct vringh *vrh, u16 head, u32 len)
int vringh_complete_multi_user(struct vringh *vrh, const struct vring_used_elem used[], unsigned num_used)
bool vringh_notify_enable_user(struct vringh *vrh)
void vringh_notify_disable_user(struct vringh *vrh)
int vringh_need_notify_user(struct vringh *vrh)
static inline int getu16_kern(const struct vringh *vrh, u16 *val, const __virtio16 *p)
static inline int putu16_kern(const struct vringh *vrh, __virtio16 *p, u16 val)
static inline int copydesc_kern(void *dst, const void *src, size_t len)
static inline int putused_kern(struct vring_used_elem *dst, const struct vring_used_elem *src, unsigned int num)
static inline int xfer_kern(void *src, void *dst, size_t len)
int vringh_init_kern(struct vringh *vrh, u64 features, unsigned int num, bool weak_barriers, struct vring_desc *desc, struct vring_avail *avail, struct vring_used *used)
int vringh_getdesc_kern(struct vringh *vrh, struct vringh_kiov *riov, struct vringh_kiov *wiov, u16 *head, gfp_t gfp)
ssize_t vringh_iov_pull_kern(struct vringh_kiov *riov, void *dst, size_t len)
ssize_t vringh_iov_push_kern(struct vringh_kiov *wiov, const void *src, size_t len)
void vringh_abandon_kern(struct vringh *vrh, unsigned int num)
int vringh_complete_kern(struct vringh *vrh, u16 head, u32 len)
bool vringh_notify_enable_kern(struct vringh *vrh)
void vringh_notify_disable_kern(struct vringh *vrh)
int vringh_need_notify_kern(struct vringh *vrh)
  28 struct vringh *vrh
  13 size_t len
  13 const struct vringh *vrh
  10 void *dst
   7 const void *src
   6 unsigned int num
   6 u64 addr
   5 u64
   5 u16 val
   5 u16 *val
   5 struct vringh_range *
   5 const __virtio16 *p
   5 bool *getrange
   5 __virtio16 *p
   4 struct vringh_range *range
   4 struct vringh *
   4 size_t *len
   3 void *src
   3 struct vringh_kiov *wiov
   3 struct vringh_kiov *riov
   3 struct vring_used_elem *dst
   3 int *getu16
   2 void *ptr
   2 void *addr
   2 u64 features
   2 u32 len
   2 u16 head
   2 struct vringh_range *r
   2 struct vringh_kiov *iov
   2 struct vringh_iov *wiov
   2 struct vringh_iov *riov
   2 struct vring_desc **descs
   2 int *up_next
   2 int *putu16
   2 int *desc_max
   2 gfp_t gfp
   2 const struct vring_used_elem *src
   2 bool weak_barriers
   2 bool *rcheck
   2 *getrange
   2 *copy
   1 unsigned num_used
   1 unsigned num
   1 unsigned int num_used
   1 u16 i
   1 u16 *i
   1 u16 *head
   1 struct vring_used __user *used
   1 struct vring_used *used
   1 struct vring_desc __user *desc
   1 struct vring_desc *desc
   1 struct vring_avail __user *avail
   1 struct vring_avail *avail
   1 int *xfer
   1 const struct vring_used_elem*src
   1 const struct vring_used_elem used[]
   1 const struct vring_used_elem *used
   1 const struct vring_desc *desc
   1 const char *fmt
   1 2
   1 1
   1 ...
   1 *putused
   1 *putu16
