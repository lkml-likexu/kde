
\n
static struct device *to_dev(struct pmem_device *pmem)
static struct nd_region *to_region(struct pmem_device *pmem)
static void hwpoison_clear(struct pmem_device *pmem, phys_addr_t phys, unsigned int len)
static blk_status_t pmem_clear_poison(struct pmem_device *pmem, phys_addr_t offset, unsigned int len)
static void write_pmem(void *pmem_addr, struct page *page, unsigned int off, unsigned int len)
static blk_status_t read_pmem(struct page *page, unsigned int off, void *pmem_addr, unsigned int len)
static blk_status_t pmem_do_bvec(struct pmem_device *pmem, struct page *page, unsigned int len, unsigned int off, unsigned int op, sector_t sector)
static blk_qc_t pmem_make_request(struct request_queue *q, struct bio *bio)
static int pmem_rw_page(struct block_device *bdev, sector_t sector, struct page *page, unsigned int op)
__weak long __pmem_direct_access(struct pmem_device *pmem, pgoff_t pgoff, long nr_pages, void **kaddr, pfn_t *pfn)
static long pmem_dax_direct_access(struct dax_device *dax_dev, pgoff_t pgoff, long nr_pages, void **kaddr, pfn_t *pfn)
static size_t pmem_copy_from_iter(struct dax_device *dax_dev, pgoff_t pgoff, void *addr, size_t bytes, struct iov_iter *i)
static size_t pmem_copy_to_iter(struct dax_device *dax_dev, pgoff_t pgoff, void *addr, size_t bytes, struct iov_iter *i)
static void pmem_release_queue(void *q)
static void pmem_freeze_queue(struct percpu_ref *ref)
static void pmem_release_disk(void *__pmem)
static void pmem_release_pgmap_ops(void *__pgmap)
static void fsdax_pagefree(struct page *page, void *data)
static int setup_pagemap_fsdax(struct device *dev, struct dev_pagemap *pgmap)
static int pmem_attach_disk(struct device *dev, struct nd_namespace_common *ndns)
static int nd_pmem_probe(struct device *dev)
static int nd_pmem_remove(struct device *dev)
static void nd_pmem_shutdown(struct device *dev)
static void nd_pmem_notify(struct device *dev, enum nvdimm_event event)
\n
      6 struct pmem_device *pmem
      6 struct device *dev
      5 unsigned int len
      5 struct page *page
      4 pgoff_t pgoff
      3 unsigned int off
      3 struct dax_device *dax_dev
      2 void *pmem_addr
      2 void **kaddr
      2 void *addr
      2 unsigned int op
      2 struct iov_iter *i
      2 size_t bytes
      2 sector_t sector
      2 pfn_t *pfn
      2 long nr_pages
      1 void *q
      1 void *__pmem
      1 void *__pgmap
      1 void *data
      1 struct request_queue *q
      1 struct percpu_ref *ref
      1 struct nd_namespace_common *ndns
      1 struct dev_pagemap *pgmap
      1 struct block_device *bdev
      1 struct bio *bio
      1 phys_addr_t phys
      1 phys_addr_t offset
      1 enum nvdimm_event event
