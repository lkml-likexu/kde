
\n
static inline void __iommu_flush_cache(struct intel_iommu *iommu, void *addr, int size)
static inline void dma_clear_pte(struct dma_pte *pte)
static inline u64 dma_pte_addr(struct dma_pte *pte)
static inline bool dma_pte_present(struct dma_pte *pte)
static inline bool dma_pte_superpage(struct dma_pte *pte)
static inline int first_pte_in_page(struct dma_pte *pte)
extern int iommu_calculate_agaw(struct intel_iommu *iommu)
; extern int iommu_calculate_max_sagaw(struct intel_iommu *iommu)
; extern int dmar_disabled; extern int intel_iommu_enabled; extern int intel_iommu_tboot_noforce; static inline int iommu_calculate_agaw(struct intel_iommu *iommu)
extern int iommu_calculate_agaw(struct intel_iommu *iommu)
; extern int iommu_calculate_max_sagaw(struct intel_iommu *iommu)
; extern int dmar_disabled; extern int intel_iommu_enabled; extern int intel_iommu_tboot_noforce; static inline int iommu_calculate_agaw(struct intel_iommu *iommu)
return 0; } static inline int iommu_calculate_max_sagaw(struct intel_iommu *iommu)
\n
      8 struct intel_iommu *iommu
      5 struct dma_pte *pte
      1 void *addr
      1 int size
