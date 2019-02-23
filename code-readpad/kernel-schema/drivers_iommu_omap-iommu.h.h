
\n
static inline u32 iommu_read_reg(struct omap_iommu *obj, size_t offs)
static inline void iommu_write_reg(struct omap_iommu *obj, u32 val, size_t offs)
static inline int iotlb_cr_valid(struct cr_regs *cr)
\n
      2 struct omap_iommu *obj
      2 size_t offs
      1 u32 val
      1 struct cr_regs *cr
