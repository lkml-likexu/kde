
EXPORT_SYMBOL_GPL(to_nd_region);
EXPORT_SYMBOL_GPL(nd_region_dev);
EXPORT_SYMBOL_GPL(to_nd_blk_region);
EXPORT_SYMBOL_GPL(nd_region_provider_data);
EXPORT_SYMBOL_GPL(nd_blk_region_provider_data);
EXPORT_SYMBOL_GPL(nd_blk_region_set_provider_data);
EXPORT_SYMBOL_GPL(nd_region_attribute_group);
EXPORT_SYMBOL_GPL(nd_mapping_attribute_group);
EXPORT_SYMBOL_GPL(nvdimm_pmem_region_create);
EXPORT_SYMBOL_GPL(nvdimm_blk_region_create);
EXPORT_SYMBOL_GPL(nvdimm_volatile_region_create);
EXPORT_SYMBOL_GPL(nvdimm_flush);
EXPORT_SYMBOL_GPL(nvdimm_has_flush);
EXPORT_SYMBOL_GPL(nvdimm_has_cache);
\n
static int nvdimm_map_flush(struct device *dev, struct nvdimm *nvdimm, int dimm, struct nd_region_data *ndrd)
int nd_region_activate(struct nd_region *nd_region)
static void nd_region_release(struct device *dev)
bool is_nd_pmem(struct device *dev)
bool is_nd_blk(struct device *dev)
bool is_nd_volatile(struct device *dev)
struct nd_region *to_nd_region(struct device *dev)
struct device *nd_region_dev(struct nd_region *nd_region)
struct nd_blk_region *to_nd_blk_region(struct device *dev)
void *nd_region_provider_data(struct nd_region *nd_region)
void *nd_blk_region_provider_data(struct nd_blk_region *ndbr)
void nd_blk_region_set_provider_data(struct nd_blk_region *ndbr, void *data)
int nd_region_to_nstype(struct nd_region *nd_region)
static ssize_t size_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t deep_flush_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t deep_flush_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
static ssize_t mappings_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t nstype_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t set_cookie_show(struct device *dev, struct device_attribute *attr, char *buf)
resource_size_t nd_region_available_dpa(struct nd_region *nd_region)
resource_size_t nd_region_allocatable_dpa(struct nd_region *nd_region)
static ssize_t available_size_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t max_available_extent_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t init_namespaces_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t namespace_seed_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t btt_seed_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t pfn_seed_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t dax_seed_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t read_only_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t read_only_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
static ssize_t region_badblocks_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t resource_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t persistence_domain_show(struct device *dev, struct device_attribute *attr, char *buf)
static umode_t region_visible(struct kobject *kobj, struct attribute *a, int n)
u64 nd_region_interleave_set_cookie(struct nd_region *nd_region, struct nd_namespace_index *nsindex)
u64 nd_region_interleave_set_altcookie(struct nd_region *nd_region)
void nd_mapping_free_labels(struct nd_mapping *nd_mapping)
static void nd_region_notify_driver_action(struct nvdimm_bus *nvdimm_bus, struct device *dev, bool probe)
void nd_region_probe_success(struct nvdimm_bus *nvdimm_bus, struct device *dev)
void nd_region_disable(struct nvdimm_bus *nvdimm_bus, struct device *dev)
static ssize_t mappingN(struct device *dev, char *buf, int n)
define REGION_MAPPING(idx)
\ static ssize_t mappingidx_show(struct device *dev, \ struct device_attribute *attr, char *buf)
\ static umode_t mapping_visible(struct kobject *kobj, struct attribute *a, int n)
int nd_blk_region_init(struct nd_region *nd_region)
unsigned int nd_region_acquire_lane(struct nd_region *nd_region)
void nd_region_release_lane(struct nd_region *nd_region, unsigned int lane)
static struct nd_region *nd_region_create(struct nvdimm_bus *nvdimm_bus, struct nd_region_desc *ndr_desc, struct device_type *dev_type, const char *caller)
struct nd_region *nvdimm_pmem_region_create(struct nvdimm_bus *nvdimm_bus, struct nd_region_desc *ndr_desc)
struct nd_region *nvdimm_blk_region_create(struct nvdimm_bus *nvdimm_bus, struct nd_region_desc *ndr_desc)
struct nd_region *nvdimm_volatile_region_create(struct nvdimm_bus *nvdimm_bus, struct nd_region_desc *ndr_desc)
void nvdimm_flush(struct nd_region *nd_region)
int nvdimm_has_flush(struct nd_region *nd_region)
int nvdimm_has_cache(struct nd_region *nd_region)
static int region_conflict(struct device *dev, void *data)
int nd_region_conflict(struct nd_region *nd_region, resource_size_t start, resource_size_t size)
void __exit nd_region_devs_exit(void)
\n
     31 struct device *dev
     18 struct device_attribute *attr
     18 char *buf
     15 struct nd_region *nd_region
      7 struct nvdimm_bus *nvdimm_bus
      4 struct nd_region_desc *ndr_desc
      3 int n
      2 void *data
      2 struct nd_blk_region *ndbr
      2 struct kobject *kobj
      2 struct attribute *a
      2 size_t len
      2 const char *buf
      1 void
      1 unsigned int lane
      1 to_nd_region
      1 to_nd_blk_region
      1 struct nvdimm *nvdimm
      1 struct nd_region_data *ndrd
      1 struct nd_namespace_index *nsindex
      1 struct nd_mapping *nd_mapping
      1 struct device_type *dev_type
      1 \ struct device_attribute *attr
      1 resource_size_t start
      1 resource_size_t size
      1 nvdimm_volatile_region_create
      1 nvdimm_pmem_region_create
      1 nvdimm_has_flush
      1 nvdimm_has_cache
      1 nvdimm_flush
      1 nvdimm_blk_region_create
      1 nd_region_provider_data
      1 nd_region_dev
      1 nd_region_attribute_group
      1 nd_mapping_attribute_group
      1 nd_blk_region_set_provider_data
      1 nd_blk_region_provider_data
      1 int dimm
      1 idx
      1 const char *caller
      1 bool probe
