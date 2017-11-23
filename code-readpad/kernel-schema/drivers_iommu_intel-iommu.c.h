
EXPORT_SYMBOL_GPL(intel_iommu_enabled);
EXPORT_SYMBOL_GPL(intel_iommu_gfx_mapped);
static inline int agaw_to_level(int agaw)
static inline int agaw_to_width(int agaw)
static inline int width_to_agaw(int width)
static inline unsigned int level_to_offset_bits(int level)
static inline int pfn_level_offset(unsigned long pfn, int level)
static inline unsigned long level_mask(int level)
static inline unsigned long level_size(int level)
static inline unsigned long align_to_level(unsigned long pfn, int level)
static inline unsigned long lvl_to_nr_pages(unsigned int lvl)
static inline unsigned long dma_to_mm_pfn(unsigned long dma_pfn)
static inline unsigned long mm_to_dma_pfn(unsigned long mm_pfn)
static inline unsigned long mm_to_dma_pfn(unsigned long mm_pfn)
return mm_pfn << (PAGE_SHIFT - VTD_PAGE_SHIFT)
; } static inline unsigned long page_to_dma_pfn(struct page *pg)
static inline unsigned long mm_to_dma_pfn(unsigned long mm_pfn)
return mm_pfn << (PAGE_SHIFT - VTD_PAGE_SHIFT)
; } static inline unsigned long page_to_dma_pfn(struct page *pg)
return mm_to_dma_pfn(page_to_pfn(pg)
)
; } static inline unsigned long virt_to_dma_pfn(void *p)
static phys_addr_t root_entry_lctp(struct root_entry *re)
static phys_addr_t root_entry_uctp(struct root_entry *re)
static inline void context_clear_pasid_enable(struct context_entry *context)
static inline bool context_pasid_enabled(struct context_entry *context)
static inline void context_set_copied(struct context_entry *context)
static inline bool context_copied(struct context_entry *context)
static inline bool __context_present(struct context_entry *context)
bool context_present(struct context_entry *context)
static inline void context_set_present(struct context_entry *context)
static inline void context_set_fault_enable(struct context_entry *context)
static inline void context_set_translation_type(struct context_entry *context, unsigned long value)
static inline void context_set_address_root(struct context_entry *context, unsigned long value)
static inline void context_set_address_width(struct context_entry *context, unsigned long value)
static inline void context_set_domain_id(struct context_entry *context, unsigned long value)
static inline int context_domain_id(struct context_entry *c)
static inline void context_clear_entry(struct context_entry *context)
static inline void dma_clear_pte(struct dma_pte *pte)
static inline u64 dma_pte_addr(struct dma_pte *pte)
static inline bool dma_pte_present(struct dma_pte *pte)
static inline bool dma_pte_superpage(struct dma_pte *pte)
static inline int first_pte_in_page(struct dma_pte *pte)
int for_each_device_domain(int (*fn)
(struct device_domain_info *info, void *data)
, void *data)
static bool translation_pre_enabled(struct intel_iommu *iommu)
static void clear_translation_pre_enabled(struct intel_iommu *iommu)
static void init_translation_status(struct intel_iommu *iommu)
static struct dmar_domain *to_dmar_domain(struct iommu_domain *dom)
static int __init intel_iommu_setup(char *str)
static struct dmar_domain* get_iommu_domain(struct intel_iommu *iommu, u16 did)
static void set_iommu_domain(struct intel_iommu *iommu, u16 did, struct dmar_domain *domain)
void *alloc_pgtable_page(int node)
void free_pgtable_page(void *vaddr)
static inline void *alloc_domain_mem(void)
static void free_domain_mem(void *vaddr)
static inline void * alloc_devinfo_mem(void)
static inline void free_devinfo_mem(void *vaddr)
static inline int domain_type_is_vm(struct dmar_domain *domain)
static inline int domain_type_is_si(struct dmar_domain *domain)
static inline int domain_type_is_vm_or_si(struct dmar_domain *domain)
static inline int domain_pfn_supported(struct dmar_domain *domain, unsigned long pfn)
static int __iommu_calculate_agaw(struct intel_iommu *iommu, int max_gaw)
int iommu_calculate_max_sagaw(struct intel_iommu *iommu)
int iommu_calculate_agaw(struct intel_iommu *iommu)
struct intel_iommu *domain_get_iommu(struct dmar_domain *domain)
static void domain_update_iommu_coherency(struct dmar_domain *domain)
static int domain_update_iommu_snooping(struct intel_iommu *skip)
static int domain_update_iommu_superpage(struct intel_iommu *skip)
static void domain_update_iommu_cap(struct dmar_domain *domain)
struct context_entry *iommu_context_addr(struct intel_iommu *iommu, u8 bus, u8 devfn, int alloc)
static int iommu_dummy(struct device *dev)
static struct intel_iommu *device_to_iommu(struct device *dev, u8 *bus, u8 *devfn)
static void domain_flush_cache(struct dmar_domain *domain, void *addr, int size)
static int device_context_mapped(struct intel_iommu *iommu, u8 bus, u8 devfn)
static void free_context_table(struct intel_iommu *iommu)
static struct dma_pte *pfn_to_dma_pte(struct dmar_domain *domain, unsigned long pfn, int *target_level)
static struct dma_pte *dma_pfn_level_pte(struct dmar_domain *domain, unsigned long pfn, int level, int *large_page)
static void dma_pte_clear_range(struct dmar_domain *domain, unsigned long start_pfn, unsigned long last_pfn)
static void dma_pte_free_level(struct dmar_domain *domain, int level, int retain_level, struct dma_pte *pte, unsigned long pfn, unsigned long start_pfn, unsigned long last_pfn)
static void dma_pte_free_pagetable(struct dmar_domain *domain, unsigned long start_pfn, unsigned long last_pfn, int retain_level)
static struct page *dma_pte_list_pagetables(struct dmar_domain *domain, int level, struct dma_pte *pte, struct page *freelist)
static struct page *dma_pte_clear_level(struct dmar_domain *domain, int level, struct dma_pte *pte, unsigned long pfn, unsigned long start_pfn, unsigned long last_pfn, struct page *freelist)
static struct page *domain_unmap(struct dmar_domain *domain, unsigned long start_pfn, unsigned long last_pfn)
static void dma_free_pagelist(struct page *freelist)
static void iova_entry_free(unsigned long data)
static int iommu_alloc_root_entry(struct intel_iommu *iommu)
static void iommu_set_root_entry(struct intel_iommu *iommu)
static void iommu_flush_write_buffer(struct intel_iommu *iommu)
static void __iommu_flush_context(struct intel_iommu *iommu, u16 did, u16 source_id, u8 function_mask, u64 type)
static void __iommu_flush_iotlb(struct intel_iommu *iommu, u16 did, u64 addr, unsigned int size_order, u64 type)
static struct device_domain_info * iommu_support_dev_iotlb (struct dmar_domain *domain, struct intel_iommu *iommu, u8 bus, u8 devfn)
static void domain_update_iotlb(struct dmar_domain *domain)
static void iommu_enable_dev_iotlb(struct device_domain_info *info)
static void iommu_disable_dev_iotlb(struct device_domain_info *info)
static void iommu_flush_dev_iotlb(struct dmar_domain *domain, u64 addr, unsigned mask)
static void iommu_flush_iotlb_psi(struct intel_iommu *iommu, struct dmar_domain *domain, unsigned long pfn, unsigned int pages, int ih, int map)
static inline void __mapping_notify_one(struct intel_iommu *iommu, struct dmar_domain *domain, unsigned long pfn, unsigned int pages)
static void iommu_flush_iova(struct iova_domain *iovad)
static void iommu_disable_protect_mem_regions(struct intel_iommu *iommu)
static void iommu_enable_translation(struct intel_iommu *iommu)
static void iommu_disable_translation(struct intel_iommu *iommu)
static int iommu_init_domains(struct intel_iommu *iommu)
static void disable_dmar_iommu(struct intel_iommu *iommu)
static void free_dmar_iommu(struct intel_iommu *iommu)
static struct dmar_domain *alloc_domain(int flags)
static int domain_attach_iommu(struct dmar_domain *domain, struct intel_iommu *iommu)
static int domain_detach_iommu(struct dmar_domain *domain, struct intel_iommu *iommu)
static int dmar_init_reserved_ranges(void)
static void domain_reserve_special_ranges(struct dmar_domain *domain)
static inline int guestwidth_to_adjustwidth(int gaw)
static int domain_init(struct dmar_domain *domain, struct intel_iommu *iommu, int guest_width)
static void domain_exit(struct dmar_domain *domain)
static int domain_context_mapping_one(struct dmar_domain *domain, struct intel_iommu *iommu, u8 bus, u8 devfn)
static int domain_context_mapping_cb(struct pci_dev *pdev, u16 alias, void *opaque)
static int domain_context_mapping(struct dmar_domain *domain, struct device *dev)
static int domain_context_mapped_cb(struct pci_dev *pdev, u16 alias, void *opaque)
static int domain_context_mapped(struct device *dev)
static inline unsigned long aligned_nrpages(unsigned long host_addr, size_t size)
static inline int hardware_largepage_caps(struct dmar_domain *domain, unsigned long iov_pfn, unsigned long phy_pfn, unsigned long pages)
static int __domain_mapping(struct dmar_domain *domain, unsigned long iov_pfn, struct scatterlist *sg, unsigned long phys_pfn, unsigned long nr_pages, int prot)
static int domain_mapping(struct dmar_domain *domain, unsigned long iov_pfn, struct scatterlist *sg, unsigned long phys_pfn, unsigned long nr_pages, int prot)
static inline int domain_sg_mapping(struct dmar_domain *domain, unsigned long iov_pfn, struct scatterlist *sg, unsigned long nr_pages, int prot)
static inline int domain_pfn_mapping(struct dmar_domain *domain, unsigned long iov_pfn, unsigned long phys_pfn, unsigned long nr_pages, int prot)
static void domain_context_clear_one(struct intel_iommu *iommu, u8 bus, u8 devfn)
static inline void unlink_domain_info(struct device_domain_info *info)
static void domain_remove_dev_info(struct dmar_domain *domain)
static struct dmar_domain *find_domain(struct device *dev)
static inline struct device_domain_info * dmar_search_domain_by_dev_info(int segment, int bus, int devfn)
static struct dmar_domain *dmar_insert_one_dev_info(struct intel_iommu *iommu, int bus, int devfn, struct device *dev, struct dmar_domain *domain)
static int get_last_alias(struct pci_dev *pdev, u16 alias, void *opaque)
static struct dmar_domain *find_or_alloc_domain(struct device *dev, int gaw)
static struct dmar_domain *set_domain_for_dev(struct device *dev, struct dmar_domain *domain)
static struct dmar_domain *get_domain_for_dev(struct device *dev, int gaw)
static int iommu_domain_identity_map(struct dmar_domain *domain, unsigned long long start, unsigned long long end)
static int domain_prepare_identity_map(struct device *dev, struct dmar_domain *domain, unsigned long long start, unsigned long long end)
static int iommu_prepare_identity_map(struct device *dev, unsigned long long start, unsigned long long end)
static inline int iommu_prepare_rmrr_dev(struct dmar_rmrr_unit *rmrr, struct device *dev)
static inline void iommu_prepare_isa(void)
pci_dev_put(pdev)
; } static inline void iommu_prepare_isa(void)
static int __init si_domain_init(int hw)
static int identity_mapping(struct device *dev)
static int domain_add_dev_info(struct dmar_domain *domain, struct device *dev)
static bool device_has_rmrr(struct device *dev)
static bool device_is_rmrr_locked(struct device *dev)
static int iommu_should_identity_map(struct device *dev, int startup)
static int __init dev_prepare_static_identity_mapping(struct device *dev, int hw)
static int __init iommu_prepare_static_identity_mapping(int hw)
static void intel_iommu_init_qi(struct intel_iommu *iommu)
static int copy_context_table(struct intel_iommu *iommu, struct root_entry *old_re, struct context_entry **tbl, int bus, bool ext)
static int copy_translation_tables(struct intel_iommu *iommu)
static int __init init_dmars(void)
static unsigned long intel_alloc_iova(struct device *dev, struct dmar_domain *domain, unsigned long nrpages, uint64_t dma_mask)
struct dmar_domain *get_valid_domain_for_dev(struct device *dev)
static int iommu_no_mapping(struct device *dev)
static dma_addr_t __intel_map_single(struct device *dev, phys_addr_t paddr, size_t size, int dir, u64 dma_mask)
static dma_addr_t intel_map_page(struct device *dev, struct page *page, unsigned long offset, size_t size, enum dma_data_direction dir, unsigned long attrs)
static void intel_unmap(struct device *dev, dma_addr_t dev_addr, size_t size)
static void intel_unmap_page(struct device *dev, dma_addr_t dev_addr, size_t size, enum dma_data_direction dir, unsigned long attrs)
static void *intel_alloc_coherent(struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t flags, unsigned long attrs)
static void intel_free_coherent(struct device *dev, size_t size, void *vaddr, dma_addr_t dma_handle, unsigned long attrs)
static void intel_unmap_sg(struct device *dev, struct scatterlist *sglist, int nelems, enum dma_data_direction dir, unsigned long attrs)
static int intel_nontranslate_map_sg(struct device *hddev, struct scatterlist *sglist, int nelems, int dir)
static int intel_map_sg(struct device *dev, struct scatterlist *sglist, int nelems, enum dma_data_direction dir, unsigned long attrs)
static int intel_mapping_error(struct device *dev, dma_addr_t dma_addr)
static inline int iommu_domain_cache_init(void)
static inline int iommu_devinfo_cache_init(void)
static int __init iommu_init_mempool(void)
static void __init iommu_exit_mempool(void)
static void quirk_ioat_snb_local_iommu(struct pci_dev *pdev)
static void __init init_no_remapping_devices(void)
static int init_iommu_hw(void)
static void iommu_flush_all(void)
static int iommu_suspend(void)
static void iommu_resume(void)
static void __init init_iommu_pm_ops(void)
int __init dmar_parse_one_rmrr(struct acpi_dmar_header *header, void *arg)
static struct dmar_atsr_unit *dmar_find_atsr(struct acpi_dmar_atsr *atsr)
int dmar_parse_one_atsr(struct acpi_dmar_header *hdr, void *arg)
static void intel_iommu_free_atsr(struct dmar_atsr_unit *atsru)
int dmar_release_one_atsr(struct acpi_dmar_header *hdr, void *arg)
int dmar_check_one_atsr(struct acpi_dmar_header *hdr, void *arg)
static int intel_iommu_add(struct dmar_drhd_unit *dmaru)
int dmar_iommu_hotplug(struct dmar_drhd_unit *dmaru, bool insert)
static void intel_iommu_free_dmars(void)
int dmar_find_matched_atsr_unit(struct pci_dev *dev)
int dmar_iommu_notify_scope_dev(struct dmar_pci_notify_info *info)
static int device_notifier(struct notifier_block *nb, unsigned long action, void *data)
static int intel_iommu_memory_notifier(struct notifier_block *nb, unsigned long val, void *v)
static void free_all_cpu_cached_iovas(unsigned int cpu)
static int intel_iommu_cpu_dead(unsigned int cpu)
static void intel_disable_iommus(void)
static inline struct intel_iommu *dev_to_intel_iommu(struct device *dev)
static ssize_t intel_iommu_show_version(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t intel_iommu_show_address(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t intel_iommu_show_cap(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t intel_iommu_show_ecap(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t intel_iommu_show_ndoms(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t intel_iommu_show_ndoms_used(struct device *dev, struct device_attribute *attr, char *buf)
int __init intel_iommu_init(void)
static int domain_context_clear_one_cb(struct pci_dev *pdev, u16 alias, void *opaque)
static void domain_context_clear(struct intel_iommu *iommu, struct device *dev)
static void __dmar_remove_one_dev_info(struct device_domain_info *info)
static void dmar_remove_one_dev_info(struct dmar_domain *domain, struct device *dev)
static int md_domain_init(struct dmar_domain *domain, int guest_width)
static struct iommu_domain *intel_iommu_domain_alloc(unsigned type)
static void intel_iommu_domain_free(struct iommu_domain *domain)
static int intel_iommu_attach_device(struct iommu_domain *domain, struct device *dev)
static void intel_iommu_detach_device(struct iommu_domain *domain, struct device *dev)
static int intel_iommu_map(struct iommu_domain *domain, unsigned long iova, phys_addr_t hpa, size_t size, int iommu_prot)
static size_t intel_iommu_unmap(struct iommu_domain *domain, unsigned long iova, size_t size)
static phys_addr_t intel_iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
static bool intel_iommu_capable(enum iommu_cap cap)
static int intel_iommu_add_device(struct device *dev)
static void intel_iommu_remove_device(struct device *dev)
static void intel_iommu_get_resv_regions(struct device *device, struct list_head *head)
static void intel_iommu_put_resv_regions(struct device *dev, struct list_head *head)
define MAX_NR_PASID_BITS (20)
static inline unsigned long intel_iommu_get_pts(struct device *dev)
int intel_iommu_enable_pasid(struct intel_iommu *iommu, struct intel_svm_dev *sdev)
struct intel_iommu *intel_svm_device_to_iommu(struct device *dev)
static void quirk_iommu_g4x_gfx(struct pci_dev *dev)
static void quirk_iommu_rwbf(struct pci_dev *dev)
static void quirk_calpella_no_shadow_gtt(struct pci_dev *dev)
static void __init check_tylersburg_isoch(void)
  46 struct device *dev
  43 struct dmar_domain *domain
  36 struct intel_iommu *iommu
  20 void
  13 struct context_entry *context
   9 unsigned long pfn
   9 size_t size
   9 int level
   8 struct dma_pte *pte
   6 unsigned long attrs
   6 struct iommu_domain *domain
   6 struct device_attribute *attr
   6 char *buf
   5 unsigned long start_pfn
   5 unsigned long last_pfn
   5 unsigned long iov_pfn
   5 u8 devfn
   5 u8 bus
   5 struct pci_dev *pdev
   5 struct device_domain_info *info
   4 void *vaddr
   4 void *opaque
   4 void *arg
   4 unsigned long value
   4 unsigned long nr_pages
   4 u16 did
   4 u16 alias
   4 struct pci_dev *dev
   4 int prot
   4 enum dma_data_direction dir
   3 unsigned long phys_pfn
   3 unsigned long mm_pfn
   3 unsigned long long start
   3 unsigned long long end
   3 struct scatterlist *sglist
   3 struct scatterlist *sg
   3 struct page *freelist
   3 struct acpi_dmar_header *hdr
   3 int nelems
   3 int hw
   3 int gaw
   3 int bus
   2 void *data
   2 unsigned long iova
   2 unsigned int pages
   2 unsigned int cpu
   2 u64 type
   2 u64 addr
   2 struct root_entry *re
   2 struct page *pg
   2 struct notifier_block *nb
   2 struct list_head *head
   2 struct intel_iommu *skip
   2 struct dmar_drhd_unit *dmaru
   2 int retain_level
   2 int guest_width
   2 int dir
   2 int devfn
   2 int agaw
   2 dma_addr_t dev_addr
   2 PAGE_SHIFT - VTD_PAGE_SHIFT
   1 void *v
   1 void *p
   1 void *addr
   1 unsigned type
   1 unsigned mask
   1 unsigned long val
   1 unsigned long phy_pfn
   1 unsigned long pages
   1 unsigned long offset
   1 unsigned long nrpages
   1 unsigned long host_addr
   1 unsigned long dma_pfn
   1 unsigned long data
   1 unsigned long action
   1 unsigned int size_order
   1 unsigned int lvl
   1 uint64_t dma_mask
   1 u8 function_mask
   1 u8 *devfn
   1 u8 *bus
   1 u64 dma_mask
   1 u16 source_id
   1 struct root_entry *old_re
   1 struct page *page
   1 struct iova_domain *iovad
   1 struct iommu_domain *dom
   1 struct intel_svm_dev *sdev
   1 struct dmar_rmrr_unit *rmrr
   1 struct dmar_pci_notify_info *info
   1 struct dmar_atsr_unit *atsru
   1 struct device *hddev
   1 struct device *device
   1 struct context_entry *c
   1 struct context_entry **tbl
   1 struct acpi_dmar_header *header
   1 struct acpi_dmar_atsr *atsr
   1 phys_addr_t paddr
   1 phys_addr_t hpa
   1 pdev
   1 page_to_pfnpg
   1 intel_iommu_gfx_mapped
   1 intel_iommu_enabled
   1 int width
   1 int startup
   1 int size
   1 int segment
   1 int node
   1 int max_gaw
   1 int map
   1 int iommu_prot
   1 int ih
   1 int flags
   1 int alloc
   1 int *target_level
   1 int *large_page
   1 int *fn
   1 gfp_t flags
   1 enum iommu_cap cap
   1 dma_addr_t iova
   1 dma_addr_t dma_handle
   1 dma_addr_t dma_addr
   1 dma_addr_t *dma_handle
   1 char *str
   1 bool insert
   1 bool ext
   1 20
