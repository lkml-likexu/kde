
\n
static inline struct nd_device_driver *to_nd_device_driver( struct device_driver *drv)
static inline struct nd_namespace_common *to_ndns(struct device *dev)
static inline struct nd_namespace_io *to_nd_namespace_io(const struct device *dev)
static inline struct nd_namespace_pmem *to_nd_namespace_pmem(const struct device *dev)
static inline struct nd_namespace_blk *to_nd_namespace_blk(const struct device *dev)
static inline int nvdimm_read_bytes(struct nd_namespace_common *ndns, resource_size_t offset, void *buf, size_t size, unsigned long flags)
static inline int nvdimm_write_bytes(struct nd_namespace_common *ndns, resource_size_t offset, void *buf, size_t size, unsigned long flags)
struct nd_region; void nvdimm_region_notify(struct nd_region *nd_region, enum nvdimm_event event)
; int __must_check __nd_driver_register(struct nd_device_driver *nd_drv, struct module *module, const char *mod_name)
; static inline void nd_driver_unregister(struct nd_device_driver *drv)
\n
      3 const struct device *dev
      2 void *buf
      2 unsigned long flags
      2 struct nd_namespace_common *ndns
      2 size_t size
      2 resource_size_t offset
      1 struct nd_region *nd_region
      1 struct nd_device_driver *nd_drv
      1 struct nd_device_driver *drv
      1 struct module *module
      1 struct device_driver *drv
      1 struct device *dev
      1 enum nvdimm_event event
      1 const char *mod_name
