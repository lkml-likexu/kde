
\n
struct device; void *devm_nvdimm_memremap(struct device *dev, resource_size_t offset, size_t size, unsigned long flags)
; static inline void __iomem *devm_nvdimm_ioremap(struct device *dev, resource_size_t offset, size_t size)
static inline struct nd_blk_region_desc *to_blk_region_desc( struct nd_region_desc *ndr_desc)
void badrange_init(struct badrange *badrange)
; int badrange_add(struct badrange *badrange, u64 addr, u64 length)
; void badrange_forget(struct badrange *badrange, phys_addr_t start, unsigned int len)
; int nvdimm_bus_add_badrange(struct nvdimm_bus *nvdimm_bus, u64 addr, u64 length)
; struct nvdimm_bus *nvdimm_bus_register(struct device *parent, struct nvdimm_bus_descriptor *nfit_desc)
; void nvdimm_bus_unregister(struct nvdimm_bus *nvdimm_bus)
; struct nvdimm_bus *to_nvdimm_bus(struct device *dev)
; struct nvdimm_bus *nvdimm_to_bus(struct nvdimm *nvdimm)
; struct nvdimm *to_nvdimm(struct device *dev)
; struct nd_region *to_nd_region(struct device *dev)
; struct device *nd_region_dev(struct nd_region *nd_region)
; struct nd_blk_region *to_nd_blk_region(struct device *dev)
; struct nvdimm_bus_descriptor *to_nd_desc(struct nvdimm_bus *nvdimm_bus)
; struct device *to_nvdimm_bus_dev(struct nvdimm_bus *nvdimm_bus)
; const char *nvdimm_name(struct nvdimm *nvdimm)
; struct kobject *nvdimm_kobj(struct nvdimm *nvdimm)
; unsigned long nvdimm_cmd_mask(struct nvdimm *nvdimm)
; void *nvdimm_provider_data(struct nvdimm *nvdimm)
; struct nvdimm *__nvdimm_create(struct nvdimm_bus *nvdimm_bus, void *provider_data, const struct attribute_group **groups, unsigned long flags, unsigned long cmd_mask, int num_flush, struct resource *flush_wpq, const char *dimm_id, const struct nvdimm_security_ops *sec_ops)
; static inline struct nvdimm *nvdimm_create(struct nvdimm_bus *nvdimm_bus, void *provider_data, const struct attribute_group **groups, unsigned long flags, unsigned long cmd_mask, int num_flush, struct resource *flush_wpq)
static inline int nvdimm_ctl(struct nvdimm *nvdimm, unsigned int cmd, void *buf, unsigned int buf_len, int *cmd_rc)
define ARCH_MEMREMAP_PMEM MEMREMAP_WB void arch_wb_cache_pmem(void *addr, size_t size)
; void arch_invalidate_pmem(void *addr, size_t size)
;define ARCH_MEMREMAP_PMEM MEMREMAP_WT static inline void arch_wb_cache_pmem(void *addr, size_t size)
define ARCH_MEMREMAP_PMEM MEMREMAP_WB void arch_wb_cache_pmem(void *addr, size_t size)
; void arch_invalidate_pmem(void *addr, size_t size)
;define ARCH_MEMREMAP_PMEM MEMREMAP_WT static inline void arch_wb_cache_pmem(void *addr, size_t size)
} static inline void arch_invalidate_pmem(void *addr, size_t size)
\n
      9 size_t size
      7 void *addr
      6 struct nvdimm *nvdimm
      6 struct nvdimm_bus *nvdimm_bus
      6 struct device *dev
      3 unsigned long flags
      3 struct badrange *badrange
      2 void *provider_data
      2 unsigned long cmd_mask
      2 u64 length
      2 u64 addr
      2 struct resource *flush_wpq
      2 resource_size_t offset
      2 int num_flush
      2 const struct attribute_group **groups
      1 void *buf
      1 unsigned int len
      1 unsigned int cmd
      1 unsigned int buf_len
      1 struct nvdimm_bus_descriptor *nfit_desc
      1 struct nd_region *nd_region
      1 struct nd_region_desc *ndr_desc
      1 struct device *parent
      1 phys_addr_t start
      1 int *cmd_rc
      1 const struct nvdimm_security_ops *sec_ops
      1 const char *dimm_id
