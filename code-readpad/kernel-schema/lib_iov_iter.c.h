
EXPORT_SYMBOL_GPL(_copy_to_iter_mcsafe);
EXPORT_SYMBOL_GPL(_copy_from_iter_flushcache);
\n
static int copyout(void __user *to, const void *from, size_t n)
static int copyin(void *to, const void __user *from, size_t n)
static size_t copy_page_to_iter_iovec(struct page *page, size_t offset, size_t bytes, struct iov_iter *i)
static size_t copy_page_from_iter_iovec(struct page *page, size_t offset, size_t bytes, struct iov_iter *i)
static bool sanity(const struct iov_iter *i)
static inline int next_idx(int idx, struct pipe_inode_info *pipe)
static size_t copy_page_to_iter_pipe(struct page *page, size_t offset, size_t bytes, struct iov_iter *i)
int iov_iter_fault_in_readable(struct iov_iter *i, size_t bytes)
void iov_iter_init(struct iov_iter *i, unsigned int direction, const struct iovec *iov, unsigned long nr_segs, size_t count)
static void memcpy_from_page(char *to, struct page *page, size_t offset, size_t len)
static void memcpy_to_page(struct page *page, size_t offset, const char *from, size_t len)
static void memzero_page(struct page *page, size_t offset, size_t len)
static inline bool allocated(struct pipe_buffer *buf)
static inline void data_start(const struct iov_iter *i, int *idxp, size_t *offp)
static size_t push_pipe(struct iov_iter *i, size_t size, int *idxp, size_t *offp)
static size_t copy_pipe_to_iter(const void *addr, size_t bytes, struct iov_iter *i)
static __wsum csum_and_memcpy(void *to, const void *from, size_t len, __wsum sum, size_t off)
static size_t csum_and_copy_to_pipe_iter(const void *addr, size_t bytes, __wsum *csum, struct iov_iter *i)
size_t _copy_to_iter(const void *addr, size_t bytes, struct iov_iter *i)
static int copyout_mcsafe(void __user *to, const void *from, size_t n)
static unsigned long memcpy_mcsafe_to_page(struct page *page, size_t offset, const char *from, size_t len)
static size_t copy_pipe_to_iter_mcsafe(const void *addr, size_t bytes, struct iov_iter *i)
size_t _copy_to_iter_mcsafe(const void *addr, size_t bytes, struct iov_iter *i)
size_t _copy_from_iter(void *addr, size_t bytes, struct iov_iter *i)
bool _copy_from_iter_full(void *addr, size_t bytes, struct iov_iter *i)
size_t _copy_from_iter_nocache(void *addr, size_t bytes, struct iov_iter *i)
size_t _copy_from_iter_flushcache(void *addr, size_t bytes, struct iov_iter *i)
bool _copy_from_iter_full_nocache(void *addr, size_t bytes, struct iov_iter *i)
static inline bool page_copy_sane(struct page *page, size_t offset, size_t n)
size_t copy_page_to_iter(struct page *page, size_t offset, size_t bytes, struct iov_iter *i)
size_t copy_page_from_iter(struct page *page, size_t offset, size_t bytes, struct iov_iter *i)
static size_t pipe_zero(size_t bytes, struct iov_iter *i)
size_t iov_iter_zero(size_t bytes, struct iov_iter *i)
size_t iov_iter_copy_from_user_atomic(struct page *page, struct iov_iter *i, unsigned long offset, size_t bytes)
static inline void pipe_truncate(struct iov_iter *i)
static void pipe_advance(struct iov_iter *i, size_t size)
void iov_iter_advance(struct iov_iter *i, size_t size)
void iov_iter_revert(struct iov_iter *i, size_t unroll)
size_t iov_iter_single_seg_count(const struct iov_iter *i)
void iov_iter_kvec(struct iov_iter *i, unsigned int direction, const struct kvec *kvec, unsigned long nr_segs, size_t count)
void iov_iter_bvec(struct iov_iter *i, unsigned int direction, const struct bio_vec *bvec, unsigned long nr_segs, size_t count)
void iov_iter_pipe(struct iov_iter *i, unsigned int direction, struct pipe_inode_info *pipe, size_t count)
void iov_iter_discard(struct iov_iter *i, unsigned int direction, size_t count)
unsigned long iov_iter_alignment(const struct iov_iter *i)
unsigned long iov_iter_gap_alignment(const struct iov_iter *i)
static inline ssize_t __pipe_get_pages(struct iov_iter *i, size_t maxsize, struct page **pages, int idx, size_t *start)
static ssize_t pipe_get_pages(struct iov_iter *i, struct page **pages, size_t maxsize, unsigned maxpages, size_t *start)
ssize_t iov_iter_get_pages(struct iov_iter *i, struct page **pages, size_t maxsize, unsigned maxpages, size_t *start)
static struct page **get_pages_array(size_t n)
static ssize_t pipe_get_pages_alloc(struct iov_iter *i, struct page ***pages, size_t maxsize, size_t *start)
ssize_t iov_iter_get_pages_alloc(struct iov_iter *i, struct page ***pages, size_t maxsize, size_t *start)
size_t csum_and_copy_from_iter(void *addr, size_t bytes, __wsum *csum, struct iov_iter *i)
bool csum_and_copy_from_iter_full(void *addr, size_t bytes, __wsum *csum, struct iov_iter *i)
size_t csum_and_copy_to_iter(const void *addr, size_t bytes, void *csump, struct iov_iter *i)
size_t hash_and_copy_to_iter(const void *addr, size_t bytes, void *hashp, struct iov_iter *i)
int iov_iter_npages(const struct iov_iter *i, int maxpages)
const void *dup_iter(struct iov_iter *new, struct iov_iter *old, gfp_t flags)
int import_iovec(int type, const struct iovec __user * uvector, unsigned nr_segs, unsigned fast_segs, struct iovec **iov, struct iov_iter *i)
int compat_import_iovec(int type, const struct compat_iovec __user * uvector, unsigned nr_segs, unsigned fast_segs, struct iovec **iov, struct iov_iter *i)
int import_single_range(int rw, void __user *buf, size_t len, struct iovec *iov, struct iov_iter *i)
int iov_iter_for_each_range(struct iov_iter *i, size_t bytes, int (*f)
(struct kvec *vec, void *context)
, void *context)
\n
     42 struct iov_iter *i
     24 size_t bytes
     11 struct page *page
     10 size_t offset
      7 void *addr
      7 const void *addr
      6 size_t len
      6 const struct iov_iter *i
      5 unsigned int direction
      5 size_t *start
      5 size_t n
      5 size_t maxsize
      5 size_t count
      3 __wsum *csum
      3 unsigned long nr_segs
      3 struct page **pages
      3 size_t size
      3 const void *from
      2 void __user *to
      2 void *to
      2 unsigned nr_segs
      2 unsigned maxpages
      2 unsigned fast_segs
      2 struct pipe_inode_info *pipe
      2 struct page ***pages
      2 struct iovec **iov
      2 size_t *offp
      2 int type
      2 int *idxp
      2 int idx
      2 const char *from
      1 __wsum sum
      1 void __user *buf
      1 void *hashp
      1 void *csump
      1 void *context
      1 unsigned long offset
      1 struct pipe_buffer *buf
      1 struct kvec *vec
      1 struct iov_iter *old
      1 struct iov_iter *new
      1 struct iovec *iov
      1 size_t unroll
      1 size_t off
      1 int rw
      1 int maxpages
      1 int *f
      1 gfp_t flags
      1 _copy_to_iter_mcsafe
      1 _copy_from_iter_flushcache
      1 const void __user *from
      1 const struct kvec *kvec
      1 const struct iovec __user * uvector
      1 const struct iovec *iov
      1 const struct compat_iovec __user * uvector
      1 const struct bio_vec *bvec
      1 char *to
