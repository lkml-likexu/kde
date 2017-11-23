
int intel_pasid_alloc_id(void *ptr, int start, int end, gfp_t gfp)
void intel_pasid_free_id(int pasid)
void *intel_pasid_lookup_id(int pasid)
static inline void device_attach_pasid_table(struct device_domain_info *info, struct pasid_table *pasid_table)
static inline void device_detach_pasid_table(struct device_domain_info *info, struct pasid_table *pasid_table)
static int search_pasid_table(struct device_domain_info *info, void *opaque)
static int get_alias_pasid_table(struct pci_dev *pdev, u16 alias, void *opaque)
int intel_pasid_alloc_table(struct device *dev)
void intel_pasid_free_table(struct device *dev)
struct pasid_table *intel_pasid_get_table(struct device *dev)
int intel_pasid_get_dev_max_id(struct device *dev)
struct pasid_entry *intel_pasid_get_entry(struct device *dev, int pasid)
static inline void pasid_clear_entry(struct pasid_entry *pe)
void intel_pasid_clear_entry(struct device *dev, int pasid)
   6 struct device *dev
   4 int pasid
   3 struct device_domain_info *info
   2 void *opaque
   2 struct pasid_table *pasid_table
   1 void *ptr
   1 u16 alias
   1 struct pci_dev *pdev
   1 struct pasid_entry *pe
   1 int start
   1 int end
   1 gfp_t gfp
