
\n
static inline void __iomem *ndrd_get_flush_wpq(struct nd_region_data *ndrd, int dimm, int hint)
static inline void ndrd_set_flush_wpq(struct nd_region_data *ndrd, int dimm, int hint, void __iomem *flush)
static inline struct nd_namespace_index *to_namespace_index( struct nvdimm_drvdata *ndd, int i)
static inline struct nd_namespace_index *to_current_namespace_index( struct nvdimm_drvdata *ndd)
static inline struct nd_namespace_index *to_next_namespace_index( struct nvdimm_drvdata *ndd)
static inline unsigned nd_inc_seq(unsigned seq)
int nd_integrity_init(struct gendisk *disk, unsigned long meta_size)
; void wait_nvdimm_bus_probe_idle(struct device *dev)
; void nd_device_register(struct device *dev)
; void nd_device_unregister(struct device *dev, enum nd_async_mode mode)
; void nd_device_notify(struct device *dev, enum nvdimm_event event)
; int nd_uuid_store(struct device *dev, u8 **uuid_out, const char *buf, size_t len)
; ssize_t nd_size_select_show(unsigned long current_size, const unsigned long *supported, char *buf)
; ssize_t nd_size_select_store(struct device *dev, const char *buf, unsigned long *current_size, const unsigned long *supported)
; int __init nvdimm_init(void)
; int __init nd_region_init(void)
; int __init nd_label_init(void)
; void nvdimm_exit(void)
; void nd_region_exit(void)
; struct nvdimm; struct nvdimm_drvdata *to_ndd(struct nd_mapping *nd_mapping)
; int nvdimm_check_config_data(struct device *dev)
; int nvdimm_init_nsarea(struct nvdimm_drvdata *ndd)
; int nvdimm_init_config_data(struct nvdimm_drvdata *ndd)
; int nvdimm_get_config_data(struct nvdimm_drvdata *ndd, void *buf, size_t offset, size_t len)
; int nvdimm_set_config_data(struct nvdimm_drvdata *ndd, size_t offset, void *buf, size_t len)
; long nvdimm_clear_poison(struct device *dev, phys_addr_t phys, unsigned int len)
; void nvdimm_set_aliasing(struct device *dev)
; void nvdimm_set_locked(struct device *dev)
; void nvdimm_clear_locked(struct device *dev)
; int nvdimm_security_setup_events(struct device *dev)
; int nvdimm_security_unlock(struct device *dev)
; static inline int nvdimm_security_unlock(struct device *dev)
u64 nd_sb_checksum(struct nd_gen_sb *sb)
; int nd_btt_probe(struct device *dev, struct nd_namespace_common *ndns)
; bool is_nd_btt(struct device *dev)
; struct device *nd_btt_create(struct nd_region *nd_region)
; static inline int nd_btt_probe(struct device *dev, struct nd_namespace_common *ndns)
static inline bool is_nd_btt(struct device *dev)
static inline struct device *nd_btt_create(struct nd_region *nd_region)
int nd_pfn_probe(struct device *dev, struct nd_namespace_common *ndns)
; bool is_nd_pfn(struct device *dev)
; struct device *nd_pfn_create(struct nd_region *nd_region)
; struct device *nd_pfn_devinit(struct nd_pfn *nd_pfn, struct nd_namespace_common *ndns)
; int nd_pfn_validate(struct nd_pfn *nd_pfn, const char *sig)
; extern struct attribute_group nd_pfn_attribute_group; static inline int nd_pfn_probe(struct device *dev, struct nd_namespace_common *ndns)
static inline bool is_nd_pfn(struct device *dev)
static inline struct device *nd_pfn_create(struct nd_region *nd_region)
static inline int nd_pfn_validate(struct nd_pfn *nd_pfn, const char *sig)
struct nd_dax *to_nd_dax(struct device *dev)
; int nd_dax_probe(struct device *dev, struct nd_namespace_common *ndns)
; bool is_nd_dax(struct device *dev)
; struct device *nd_dax_create(struct nd_region *nd_region)
; static inline int nd_dax_probe(struct device *dev, struct nd_namespace_common *ndns)
static inline bool is_nd_dax(struct device *dev)
static inline struct device *nd_dax_create(struct nd_region *nd_region)
int nd_region_to_nstype(struct nd_region *nd_region)
; int nd_region_register_namespaces(struct nd_region *nd_region, int *err)
; u64 nd_region_interleave_set_cookie(struct nd_region *nd_region, struct nd_namespace_index *nsindex)
; u64 nd_region_interleave_set_altcookie(struct nd_region *nd_region)
; void nvdimm_bus_lock(struct device *dev)
; void nvdimm_bus_unlock(struct device *dev)
; bool is_nvdimm_bus_locked(struct device *dev)
; int nvdimm_revalidate_disk(struct gendisk *disk)
; void nvdimm_drvdata_release(struct kref *kref)
; void put_ndd(struct nvdimm_drvdata *ndd)
; int nd_label_reserve_dpa(struct nvdimm_drvdata *ndd)
; void nvdimm_free_dpa(struct nvdimm_drvdata *ndd, struct resource *res)
; struct resource *nvdimm_allocate_dpa(struct nvdimm_drvdata *ndd, struct nd_label_id *label_id, resource_size_t start, resource_size_t n)
; resource_size_t nvdimm_namespace_capacity(struct nd_namespace_common *ndns)
; bool nvdimm_namespace_locked(struct nd_namespace_common *ndns)
; struct nd_namespace_common *nvdimm_namespace_common_probe(struct device *dev)
; int nvdimm_namespace_attach_btt(struct nd_namespace_common *ndns)
; int nvdimm_namespace_detach_btt(struct nd_btt *nd_btt)
; const char *nvdimm_namespace_disk_name(struct nd_namespace_common *ndns, char *name)
; unsigned int pmem_sector_size(struct nd_namespace_common *ndns)
; void nvdimm_badblocks_populate(struct nd_region *nd_region, struct badblocks *bb, const struct resource *res)
; int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
; int devm_nsio_enable(struct device *dev, struct nd_namespace_io *nsio)
; void devm_nsio_disable(struct device *dev, struct nd_namespace_io *nsio)
; static inline int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
int nd_region_to_nstype(struct nd_region *nd_region)
; int nd_region_register_namespaces(struct nd_region *nd_region, int *err)
; u64 nd_region_interleave_set_cookie(struct nd_region *nd_region, struct nd_namespace_index *nsindex)
; u64 nd_region_interleave_set_altcookie(struct nd_region *nd_region)
; void nvdimm_bus_lock(struct device *dev)
; void nvdimm_bus_unlock(struct device *dev)
; bool is_nvdimm_bus_locked(struct device *dev)
; int nvdimm_revalidate_disk(struct gendisk *disk)
; void nvdimm_drvdata_release(struct kref *kref)
; void put_ndd(struct nvdimm_drvdata *ndd)
; int nd_label_reserve_dpa(struct nvdimm_drvdata *ndd)
; void nvdimm_free_dpa(struct nvdimm_drvdata *ndd, struct resource *res)
; struct resource *nvdimm_allocate_dpa(struct nvdimm_drvdata *ndd, struct nd_label_id *label_id, resource_size_t start, resource_size_t n)
; resource_size_t nvdimm_namespace_capacity(struct nd_namespace_common *ndns)
; bool nvdimm_namespace_locked(struct nd_namespace_common *ndns)
; struct nd_namespace_common *nvdimm_namespace_common_probe(struct device *dev)
; int nvdimm_namespace_attach_btt(struct nd_namespace_common *ndns)
; int nvdimm_namespace_detach_btt(struct nd_btt *nd_btt)
; const char *nvdimm_namespace_disk_name(struct nd_namespace_common *ndns, char *name)
; unsigned int pmem_sector_size(struct nd_namespace_common *ndns)
; void nvdimm_badblocks_populate(struct nd_region *nd_region, struct badblocks *bb, const struct resource *res)
; int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
; int devm_nsio_enable(struct device *dev, struct nd_namespace_io *nsio)
; void devm_nsio_disable(struct device *dev, struct nd_namespace_io *nsio)
; static inline int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
return -ENXIO; } static inline int devm_nsio_enable(struct device *dev, struct nd_namespace_io *nsio)
int nd_region_to_nstype(struct nd_region *nd_region)
; int nd_region_register_namespaces(struct nd_region *nd_region, int *err)
; u64 nd_region_interleave_set_cookie(struct nd_region *nd_region, struct nd_namespace_index *nsindex)
; u64 nd_region_interleave_set_altcookie(struct nd_region *nd_region)
; void nvdimm_bus_lock(struct device *dev)
; void nvdimm_bus_unlock(struct device *dev)
; bool is_nvdimm_bus_locked(struct device *dev)
; int nvdimm_revalidate_disk(struct gendisk *disk)
; void nvdimm_drvdata_release(struct kref *kref)
; void put_ndd(struct nvdimm_drvdata *ndd)
; int nd_label_reserve_dpa(struct nvdimm_drvdata *ndd)
; void nvdimm_free_dpa(struct nvdimm_drvdata *ndd, struct resource *res)
; struct resource *nvdimm_allocate_dpa(struct nvdimm_drvdata *ndd, struct nd_label_id *label_id, resource_size_t start, resource_size_t n)
; resource_size_t nvdimm_namespace_capacity(struct nd_namespace_common *ndns)
; bool nvdimm_namespace_locked(struct nd_namespace_common *ndns)
; struct nd_namespace_common *nvdimm_namespace_common_probe(struct device *dev)
; int nvdimm_namespace_attach_btt(struct nd_namespace_common *ndns)
; int nvdimm_namespace_detach_btt(struct nd_btt *nd_btt)
; const char *nvdimm_namespace_disk_name(struct nd_namespace_common *ndns, char *name)
; unsigned int pmem_sector_size(struct nd_namespace_common *ndns)
; void nvdimm_badblocks_populate(struct nd_region *nd_region, struct badblocks *bb, const struct resource *res)
; int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
; int devm_nsio_enable(struct device *dev, struct nd_namespace_io *nsio)
; void devm_nsio_disable(struct device *dev, struct nd_namespace_io *nsio)
; static inline int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
return -ENXIO; } static inline int devm_nsio_enable(struct device *dev, struct nd_namespace_io *nsio)
return -ENXIO; } static inline void devm_nsio_disable(struct device *dev, struct nd_namespace_io *nsio)
int nd_region_to_nstype(struct nd_region *nd_region)
; int nd_region_register_namespaces(struct nd_region *nd_region, int *err)
; u64 nd_region_interleave_set_cookie(struct nd_region *nd_region, struct nd_namespace_index *nsindex)
; u64 nd_region_interleave_set_altcookie(struct nd_region *nd_region)
; void nvdimm_bus_lock(struct device *dev)
; void nvdimm_bus_unlock(struct device *dev)
; bool is_nvdimm_bus_locked(struct device *dev)
; int nvdimm_revalidate_disk(struct gendisk *disk)
; void nvdimm_drvdata_release(struct kref *kref)
; void put_ndd(struct nvdimm_drvdata *ndd)
; int nd_label_reserve_dpa(struct nvdimm_drvdata *ndd)
; void nvdimm_free_dpa(struct nvdimm_drvdata *ndd, struct resource *res)
; struct resource *nvdimm_allocate_dpa(struct nvdimm_drvdata *ndd, struct nd_label_id *label_id, resource_size_t start, resource_size_t n)
; resource_size_t nvdimm_namespace_capacity(struct nd_namespace_common *ndns)
; bool nvdimm_namespace_locked(struct nd_namespace_common *ndns)
; struct nd_namespace_common *nvdimm_namespace_common_probe(struct device *dev)
; int nvdimm_namespace_attach_btt(struct nd_namespace_common *ndns)
; int nvdimm_namespace_detach_btt(struct nd_btt *nd_btt)
; const char *nvdimm_namespace_disk_name(struct nd_namespace_common *ndns, char *name)
; unsigned int pmem_sector_size(struct nd_namespace_common *ndns)
; void nvdimm_badblocks_populate(struct nd_region *nd_region, struct badblocks *bb, const struct resource *res)
; int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
; int devm_nsio_enable(struct device *dev, struct nd_namespace_io *nsio)
; void devm_nsio_disable(struct device *dev, struct nd_namespace_io *nsio)
; static inline int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
return -ENXIO; } static inline int devm_nsio_enable(struct device *dev, struct nd_namespace_io *nsio)
return -ENXIO; } static inline void devm_nsio_disable(struct device *dev, struct nd_namespace_io *nsio)
}endif int nd_blk_region_init(struct nd_region *nd_region)
; int nd_region_activate(struct nd_region *nd_region)
; void __nd_iostat_start(struct bio *bio, unsigned long *start)
; static inline bool nd_iostat_start(struct bio *bio, unsigned long *start)
*start = jiffies;generic_start_io_acct(disk->queue, bio_op(bio)
, bio_sectors(bio)
, &disk->part0)
;return true; } static inline void nd_iostat_end(struct bio *bio, unsigned long start)
generic_end_io_acct(disk->queue, bio_op(bio)
, &disk->part0, start)
; } static inline bool is_bad_pmem(struct badblocks *bb, sector_t sector, unsigned int len)
\n
     56 struct device *dev
     28 struct nd_region *nd_region
     27 struct nd_namespace_common *ndns
     23 struct nvdimm_drvdata *ndd
     13 struct nd_namespace_io *nsio
     11 struct nd_pfn *nd_pfn
      8 struct dev_pagemap *pgmap
      5 void
      5 struct gendisk *disk
      5 struct badblocks *bb
      4 struct resource *res
      4 struct nd_namespace_index *nsindex
      4 struct nd_label_id *label_id
      4 struct nd_btt *nd_btt
      4 struct kref *kref
      4 resource_size_t start
      4 resource_size_t n
      4 int *err
      4 const struct resource *res
      4 char *name
      3 struct bio *bio
      3 size_t len
      2 void *buf
      2 unsigned long *start
      2 unsigned int len
      2 struct nd_region_data *ndrd
      2 size_t offset
      2 int hint
      2 int dimm
      2 disk->queue
      2 const unsigned long *supported
      2 const char *sig
      2 const char *buf
      2 bio_opbio
      1 void __iomem *flush
      1 unsigned seq
      1 unsigned long start
      1 unsigned long meta_size
      1 unsigned long current_size
      1 unsigned long *current_size
      1 u8 **uuid_out
      1 struct nd_mapping *nd_mapping
      1 struct nd_gen_sb *sb
      1 sector_t sector
      1 phys_addr_t phys
      1 int i
      1 enum nvdimm_event event
      1 enum nd_async_mode mode
      1 char *buf
      1 bio
