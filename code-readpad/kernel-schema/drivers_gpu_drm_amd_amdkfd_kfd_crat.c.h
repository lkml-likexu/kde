
static inline unsigned int get_and_inc_gpu_processor_id( unsigned int total_cu_count)
static void kfd_populated_cu_info_cpu(struct kfd_topology_device *dev, struct crat_subtype_computeunit *cu)
static void kfd_populated_cu_info_gpu(struct kfd_topology_device *dev, struct crat_subtype_computeunit *cu)
static int kfd_parse_subtype_cu(struct crat_subtype_computeunit *cu, struct list_head *device_list)
static struct kfd_mem_properties * find_subtype_mem(uint32_t heap_type, uint32_t flags, uint32_t width, struct kfd_topology_device *dev)
return NULL; }static int kfd_parse_subtype_mem(struct crat_subtype_memory *mem, struct list_head *device_list)
static int kfd_parse_subtype_cache(struct crat_subtype_cache *cache, struct list_head *device_list)
static int kfd_parse_subtype_iolink(struct crat_subtype_iolink *iolink, struct list_head *device_list)
static int kfd_parse_subtype(struct crat_subtype_generic *sub_type_hdr, struct list_head *device_list)
int kfd_parse_crat_table(void *crat_image, struct list_head *device_list, uint32_t proximity_domain)
static int fill_in_pcache(struct crat_subtype_cache *pcache, struct kfd_gpu_cache_info *pcache_info, struct kfd_cu_info *cu_info, int mem_available, int cu_bitmask, int cache_type, unsigned int cu_processor_id, int cu_block)
static int kfd_fill_gpu_cache_info(struct kfd_dev *kdev, int gpu_processor_id, int available_size, struct kfd_cu_info *cu_info, struct crat_subtype_cache *pcache, int *size_filled, int *num_of_entries)
int kfd_create_crat_image_acpi(void **crat_image, size_t *size)
static int kfd_fill_cu_for_cpu(int numa_node_id, int *avail_size, int proximity_domain, struct crat_subtype_computeunit *sub_type_hdr)
static int kfd_fill_mem_info_for_cpu(int numa_node_id, int *avail_size, int proximity_domain, struct crat_subtype_memory *sub_type_hdr)
static int kfd_fill_iolink_info_for_cpu(int numa_node_id, int *avail_size, uint32_t *num_entries, struct crat_subtype_iolink *sub_type_hdr)
static int kfd_create_vcrat_image_cpu(void *pcrat_image, size_t *size)
static int kfd_fill_gpu_memory_affinity(int *avail_size, struct kfd_dev *kdev, uint8_t type, uint64_t size, struct crat_subtype_memory *sub_type_hdr, uint32_t proximity_domain, const struct kfd_local_mem_info *local_mem_info)
static int kfd_fill_gpu_direct_io_link_to_cpu(int *avail_size, struct kfd_dev *kdev, struct crat_subtype_iolink *sub_type_hdr, uint32_t proximity_domain)
static int kfd_fill_gpu_xgmi_link_to_gpu(int *avail_size, struct kfd_dev *kdev, struct crat_subtype_iolink *sub_type_hdr, uint32_t proximity_domain_from, uint32_t proximity_domain_to)
static int kfd_create_vcrat_image_gpu(void *pcrat_image, size_t *size, struct kfd_dev *kdev, uint32_t proximity_domain)
int kfd_create_crat_image_virtual(void **crat_image, size_t *size, int flags, struct kfd_dev *kdev, uint32_t proximity_domain)
void kfd_destroy_crat_image(void *crat_image)
   6 struct list_head *device_list
   6 struct kfd_dev *kdev
   6 int *avail_size
   5 uint32_t proximity_domain
   4 size_t *size
   3 struct kfd_topology_device *dev
   3 struct crat_subtype_iolink *sub_type_hdr
   3 struct crat_subtype_computeunit *cu
   3 int numa_node_id
   2 void *pcrat_image
   2 void *crat_image
   2 void **crat_image
   2 struct kfd_cu_info *cu_info
   2 struct crat_subtype_memory *sub_type_hdr
   2 struct crat_subtype_cache *pcache
   2 int proximity_domain
   1 unsigned int total_cu_count
   1 unsigned int cu_processor_id
   1 uint8_t type
   1 uint64_t size
   1 uint32_t width
   1 uint32_t proximity_domain_to
   1 uint32_t proximity_domain_from
   1 uint32_t heap_type
   1 uint32_t flags
   1 uint32_t *num_entries
   1 struct kfd_gpu_cache_info *pcache_info
   1 struct crat_subtype_memory *mem
   1 struct crat_subtype_iolink *iolink
   1 struct crat_subtype_generic *sub_type_hdr
   1 struct crat_subtype_computeunit *sub_type_hdr
   1 struct crat_subtype_cache *cache
   1 int mem_available
   1 int gpu_processor_id
   1 int flags
   1 int cu_block
   1 int cu_bitmask
   1 int cache_type
   1 int available_size
   1 int *size_filled
   1 int *num_of_entries
   1 const struct kfd_local_mem_info *local_mem_info
