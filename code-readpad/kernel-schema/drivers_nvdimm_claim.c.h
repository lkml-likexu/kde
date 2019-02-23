
EXPORT_SYMBOL_GPL(devm_nsio_enable);
EXPORT_SYMBOL_GPL(devm_nsio_disable);
\n
void __nd_detach_ndns(struct device *dev, struct nd_namespace_common **_ndns)
void nd_detach_ndns(struct device *dev, struct nd_namespace_common **_ndns)
bool __nd_attach_ndns(struct device *dev, struct nd_namespace_common *attach, struct nd_namespace_common **_ndns)
bool nd_attach_ndns(struct device *dev, struct nd_namespace_common *attach, struct nd_namespace_common **_ndns)
static int namespace_match(struct device *dev, void *data)
static bool is_idle(struct device *dev, struct nd_namespace_common *ndns)
struct nd_pfn *to_nd_pfn_safe(struct device *dev)
static void nd_detach_and_reset(struct device *dev, struct nd_namespace_common **_ndns)
ssize_t nd_namespace_store(struct device *dev, struct nd_namespace_common **_ndns, const char *buf, size_t len)
u64 nd_sb_checksum(struct nd_gen_sb *nd_gen_sb)
static int nsio_rw_bytes(struct nd_namespace_common *ndns, resource_size_t offset, void *buf, size_t size, int rw, unsigned long flags)
int devm_nsio_enable(struct device *dev, struct nd_namespace_io *nsio)
void devm_nsio_disable(struct device *dev, struct nd_namespace_io *nsio)
\n
     11 struct device *dev
      6 struct nd_namespace_common **_ndns
      2 struct nd_namespace_io *nsio
      2 struct nd_namespace_common *ndns
      2 struct nd_namespace_common *attach
      1 void *data
      1 void *buf
      1 unsigned long flags
      1 struct nd_gen_sb *nd_gen_sb
      1 size_t size
      1 size_t len
      1 resource_size_t offset
      1 int rw
      1 devm_nsio_enable
      1 devm_nsio_disable
      1 const char *buf
