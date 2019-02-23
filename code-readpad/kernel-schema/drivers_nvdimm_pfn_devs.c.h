
EXPORT_SYMBOL_GPL(nvdimm_setup_pfn);
\n
static void nd_pfn_release(struct device *dev)
bool is_nd_pfn(struct device *dev)
struct nd_pfn *to_nd_pfn(struct device *dev)
static ssize_t mode_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t mode_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
static ssize_t align_show(struct device *dev, struct device_attribute *attr, char *buf)
static const unsigned long *nd_pfn_supported_alignments(void)
static ssize_t align_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
static ssize_t uuid_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t uuid_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
static ssize_t namespace_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t namespace_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
static ssize_t resource_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t size_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t supported_alignments_show(struct device *dev, struct device_attribute *attr, char *buf)
static umode_t pfn_visible(struct kobject *kobj, struct attribute *a, int n)
struct device *nd_pfn_devinit(struct nd_pfn *nd_pfn, struct nd_namespace_common *ndns)
static struct nd_pfn *nd_pfn_alloc(struct nd_region *nd_region)
struct device *nd_pfn_create(struct nd_region *nd_region)
static int nd_pfn_clear_memmap_errors(struct nd_pfn *nd_pfn)
int nd_pfn_validate(struct nd_pfn *nd_pfn, const char *sig)
int nd_pfn_probe(struct device *dev, struct nd_namespace_common *ndns)
static unsigned long init_altmap_base(resource_size_t base)
static unsigned long init_altmap_reserve(resource_size_t base)
static int __nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
static u64 phys_pmem_align_down(struct nd_pfn *nd_pfn, u64 phys)
static void trim_pfn_device(struct nd_pfn *nd_pfn, u32 *start_pad, u32 *end_trunc)
static int nd_pfn_init(struct nd_pfn *nd_pfn)
int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
\n
     15 struct device *dev
     11 struct device_attribute *attr
      8 struct nd_pfn *nd_pfn
      7 char *buf
      4 size_t len
      4 const char *buf
      2 struct nd_region *nd_region
      2 struct nd_namespace_common *ndns
      2 struct dev_pagemap *pgmap
      2 resource_size_t base
      1 void
      1 u64 phys
      1 u32 *start_pad
      1 u32 *end_trunc
      1 struct kobject *kobj
      1 struct attribute *a
      1 nvdimm_setup_pfn
      1 int n
      1 const char *sig
