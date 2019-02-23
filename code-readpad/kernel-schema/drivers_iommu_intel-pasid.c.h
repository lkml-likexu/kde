
\n
int intel_pasid_alloc_id(void *ptr, int start, int end, gfp_t gfp)
void intel_pasid_free_id(int pasid)
void *intel_pasid_lookup_id(int pasid)
static inline void device_attach_pasid_table(struct device_domain_info *info, struct pasid_table *pasid_table)
static inline void device_detach_pasid_table(struct device_domain_info *info, struct pasid_table *pasid_table)
static int search_pasid_table(struct device_domain_info *info, void *opaque)
static int get_alias_pasid_table(struct pci_dev *pdev, u16 alias, void *opaque)
int intel_pasid_alloc_table(struct device *dev)
static inline bool pasid_pde_is_present(struct pasid_dir_entry *pde)
static inline struct pasid_entry * get_pasid_table_from_pde(struct pasid_dir_entry *pde)
void intel_pasid_free_table(struct device *dev)
struct pasid_table *intel_pasid_get_table(struct device *dev)
int intel_pasid_get_dev_max_id(struct device *dev)
struct pasid_entry *intel_pasid_get_entry(struct device *dev, int pasid)
static inline void pasid_clear_entry(struct pasid_entry *pe)
static void intel_pasid_clear_entry(struct device *dev, int pasid)
static inline void pasid_set_bits(u64 *ptr, u64 mask, u64 bits)
static inline void pasid_set_domain_id(struct pasid_entry *pe, u64 value)
static inline u16 pasid_get_domain_id(struct pasid_entry *pe)
static inline void pasid_set_slptr(struct pasid_entry *pe, u64 value)
static inline void pasid_set_address_width(struct pasid_entry *pe, u64 value)
static inline void pasid_set_translation_type(struct pasid_entry *pe, u64 value)
static inline void pasid_set_fault_enable(struct pasid_entry *pe)
static inline void pasid_set_sre(struct pasid_entry *pe)
static inline void pasid_set_present(struct pasid_entry *pe)
static inline void pasid_set_page_snoop(struct pasid_entry *pe, bool value)
static inline void pasid_set_flptr(struct pasid_entry *pe, u64 value)
static inline void pasid_set_flpm(struct pasid_entry *pe, u64 value)
static void pasid_cache_invalidation_with_pasid(struct intel_iommu *iommu, u16 did, int pasid)
static void iotlb_invalidation_with_pasid(struct intel_iommu *iommu, u16 did, u32 pasid)
static void devtlb_invalidation_with_pasid(struct intel_iommu *iommu, struct device *dev, int pasid)
void intel_pasid_tear_down_entry(struct intel_iommu *iommu, struct device *dev, int pasid)
int intel_pasid_setup_first_level(struct intel_iommu *iommu, struct device *dev, pgd_t *pgd, int pasid, u16 did, int flags)
int intel_pasid_setup_second_level(struct intel_iommu *iommu, struct dmar_domain *domain, struct device *dev, int pasid)
int intel_pasid_setup_pass_through(struct intel_iommu *iommu, struct dmar_domain *domain, struct device *dev, int pasid)
\n
     12 struct pasid_entry *pe
     11 struct device *dev
     10 int pasid
      7 struct intel_iommu *iommu
      6 u64 value
      3 u16 did
      3 struct device_domain_info *info
      2 void *opaque
      2 struct pasid_table *pasid_table
      2 struct pasid_dir_entry *pde
      2 struct dmar_domain *domain
      1 void *ptr
      1 u64 *ptr
      1 u64 mask
      1 u64 bits
      1 u32 pasid
      1 u16 alias
      1 struct pci_dev *pdev
      1 pgd_t *pgd
      1 int start
      1 int flags
      1 int end
      1 gfp_t gfp
      1 bool value
