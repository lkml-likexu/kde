
EXPORT_SYMBOL_GPL(intel_svm_bind_mm);
EXPORT_SYMBOL_GPL(intel_svm_unbind_mm);
EXPORT_SYMBOL_GPL(intel_svm_is_pasid_valid);
\n
int intel_svm_init(struct intel_iommu *iommu)
int intel_svm_enable_prq(struct intel_iommu *iommu)
int intel_svm_finish_prq(struct intel_iommu *iommu)
static void intel_flush_svm_range_dev (struct intel_svm *svm, struct intel_svm_dev *sdev, unsigned long address, unsigned long pages, int ih, int gl)
static void intel_flush_svm_range(struct intel_svm *svm, unsigned long address, unsigned long pages, int ih, int gl)
static void intel_change_pte(struct mmu_notifier *mn, struct mm_struct *mm, unsigned long address, pte_t pte)
static void intel_invalidate_range(struct mmu_notifier *mn, struct mm_struct *mm, unsigned long start, unsigned long end)
static void intel_mm_release(struct mmu_notifier *mn, struct mm_struct *mm)
int intel_svm_bind_mm(struct device *dev, int *pasid, int flags, struct svm_dev_ops *ops)
int intel_svm_unbind_mm(struct device *dev, int pasid)
int intel_svm_is_pasid_valid(struct device *dev, int pasid)
static bool access_error(struct vm_area_struct *vma, struct page_req_dsc *req)
static bool is_canonical_address(u64 addr)
static irqreturn_t prq_event_thread(int irq, void *d)
\n
      3 unsigned long address
      3 struct mmu_notifier *mn
      3 struct mm_struct *mm
      3 struct intel_iommu *iommu
      3 struct device *dev
      2 unsigned long pages
      2 struct intel_svm *svm
      2 int pasid
      2 int ih
      2 int gl
      1 void *d
      1 unsigned long start
      1 unsigned long end
      1 u64 addr
      1 struct vm_area_struct *vma
      1 struct svm_dev_ops *ops
      1 struct page_req_dsc *req
      1 struct intel_svm_dev *sdev
      1 pte_t pte
      1 int *pasid
      1 int irq
      1 int flags
      1 intel_svm_unbind_mm
      1 intel_svm_is_pasid_valid
      1 intel_svm_bind_mm
