
\n
struct dax_device *dax_get_by_host(const char *host)
; struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
; void put_dax(struct dax_device *dax_dev)
; void kill_dax(struct dax_device *dax_dev)
; void dax_write_cache(struct dax_device *dax_dev, bool wc)
; bool dax_write_cache_enabled(struct dax_device *dax_dev)
; static inline struct dax_device *dax_get_by_host(const char *host)
struct dax_device *dax_get_by_host(const char *host)
; struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
; void put_dax(struct dax_device *dax_dev)
; void kill_dax(struct dax_device *dax_dev)
; void dax_write_cache(struct dax_device *dax_dev, bool wc)
; bool dax_write_cache_enabled(struct dax_device *dax_dev)
; static inline struct dax_device *dax_get_by_host(const char *host)
return NULL; } static inline struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
struct dax_device *dax_get_by_host(const char *host)
; struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
; void put_dax(struct dax_device *dax_dev)
; void kill_dax(struct dax_device *dax_dev)
; void dax_write_cache(struct dax_device *dax_dev, bool wc)
; bool dax_write_cache_enabled(struct dax_device *dax_dev)
; static inline struct dax_device *dax_get_by_host(const char *host)
return NULL; } static inline struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
return NULL; } static inline void put_dax(struct dax_device *dax_dev)
struct dax_device *dax_get_by_host(const char *host)
; struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
; void put_dax(struct dax_device *dax_dev)
; void kill_dax(struct dax_device *dax_dev)
; void dax_write_cache(struct dax_device *dax_dev, bool wc)
; bool dax_write_cache_enabled(struct dax_device *dax_dev)
; static inline struct dax_device *dax_get_by_host(const char *host)
return NULL; } static inline struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
return NULL; } static inline void put_dax(struct dax_device *dax_dev)
} static inline void kill_dax(struct dax_device *dax_dev)
struct dax_device *dax_get_by_host(const char *host)
; struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
; void put_dax(struct dax_device *dax_dev)
; void kill_dax(struct dax_device *dax_dev)
; void dax_write_cache(struct dax_device *dax_dev, bool wc)
; bool dax_write_cache_enabled(struct dax_device *dax_dev)
; static inline struct dax_device *dax_get_by_host(const char *host)
return NULL; } static inline struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
return NULL; } static inline void put_dax(struct dax_device *dax_dev)
} static inline void kill_dax(struct dax_device *dax_dev)
} static inline void dax_write_cache(struct dax_device *dax_dev, bool wc)
struct dax_device *dax_get_by_host(const char *host)
; struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
; void put_dax(struct dax_device *dax_dev)
; void kill_dax(struct dax_device *dax_dev)
; void dax_write_cache(struct dax_device *dax_dev, bool wc)
; bool dax_write_cache_enabled(struct dax_device *dax_dev)
; static inline struct dax_device *dax_get_by_host(const char *host)
return NULL; } static inline struct dax_device *alloc_dax(void *private, const char *host, const struct dax_operations *ops)
return NULL; } static inline void put_dax(struct dax_device *dax_dev)
} static inline void kill_dax(struct dax_device *dax_dev)
} static inline void dax_write_cache(struct dax_device *dax_dev, bool wc)
} static inline bool dax_write_cache_enabled(struct dax_device *dax_dev)
struct writeback_control; int bdev_dax_pgoff(struct block_device *, sector_t, size_t, pgoff_t *pgoff)
; bool __bdev_dax_supported(struct block_device *bdev, int blocksize)
; static inline bool bdev_dax_supported(struct block_device *bdev, int blocksize)
static inline struct dax_device *fs_dax_get_by_host(const char *host)
static inline void fs_put_dax(struct dax_device *dax_dev)
struct page *dax_layout_busy_page(struct address_space *mapping)
; dax_entry_t dax_lock_page(struct page *page)
; void dax_unlock_page(struct page *page, dax_entry_t cookie)
; static inline bool bdev_dax_supported(struct block_device *bdev, int blocksize)
static inline struct dax_device *fs_dax_get_by_host(const char *host)
static inline void fs_put_dax(struct dax_device *dax_dev)
static inline struct dax_device *fs_dax_get_by_bdev(struct block_device *bdev)
static inline struct page *dax_layout_busy_page(struct address_space *mapping)
static inline int dax_writeback_mapping_range(struct address_space *mapping, struct block_device *bdev, struct writeback_control *wbc)
static inline dax_entry_t dax_lock_page(struct page *page)
static inline void dax_unlock_page(struct page *page, dax_entry_t cookie)
int __dax_zero_page_range(struct block_device *bdev, struct dax_device *dax_dev, sector_t sector, unsigned int offset, unsigned int length)
; static inline int __dax_zero_page_range(struct block_device *bdev, struct dax_device *dax_dev, sector_t sector, unsigned int offset, unsigned int length)
static inline bool dax_mapping(struct address_space *mapping)
\n
     38 struct dax_device *dax_dev
     25 const char *host
     11 void *private
     11 const struct dax_operations *ops
      8 bool wc
      7 struct block_device *bdev
      4 struct page *page
      4 struct address_space *mapping
      3 int blocksize
      2 unsigned int offset
      2 unsigned int length
      2 sector_t sector
      2 dax_entry_t cookie
      1 struct writeback_control *wbc
      1 struct block_device *
      1 size_t
      1 sector_t
      1 pgoff_t *pgoff
