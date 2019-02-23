
\n
static inline __attribute_const__ int get_iommu_order(unsigned long size, struct iommu_table *tbl)
static inline void set_iommu_table_base(struct device *dev, struct iommu_table *base)
static inline void *get_iommu_table_base(struct device *dev)
extern void iommu_register_group(struct iommu_table_group *table_group, int pci_domain_number, unsigned long pe_num)
; extern int iommu_add_device(struct iommu_table_group *table_group, struct device *dev)
; extern void iommu_del_device(struct device *dev)
; extern long iommu_tce_xchg(struct mm_struct *mm, struct iommu_table *tbl, unsigned long entry, unsigned long *hpa, enum dma_data_direction *direction)
; static inline void iommu_register_group(struct iommu_table_group *table_group, int pci_domain_number, unsigned long pe_num)
static inline int iommu_add_device(struct iommu_table_group *table_group, struct device *dev)
static inline void iommu_del_device(struct device *dev)
static inline void *get_iommu_table_base(struct device *dev)
static inline int dma_iommu_dma_supported(struct device *dev, u64 mask)
static inline void iommu_save(void)
static inline void iommu_restore(void)
\n
      8 struct device *dev
      4 struct iommu_table_group *table_group
      2 void
      2 unsigned long pe_num
      2 struct iommu_table *tbl
      2 int pci_domain_number
      1 unsigned long size
      1 unsigned long *hpa
      1 unsigned long entry
      1 u64 mask
      1 struct mm_struct *mm
      1 struct iommu_table *base
      1 enum dma_data_direction *direction
