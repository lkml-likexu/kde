
\n
static struct fsl_dma_domain *to_fsl_dma_domain(struct iommu_domain *dom)
static int __init iommu_init_mempool(void)
static phys_addr_t get_phys_addr(struct fsl_dma_domain *dma_domain, dma_addr_t iova)
static int map_subwins(int liodn, struct fsl_dma_domain *dma_domain)
static int map_win(int liodn, struct fsl_dma_domain *dma_domain)
static int map_liodn(int liodn, struct fsl_dma_domain *dma_domain)
static int update_liodn(int liodn, struct fsl_dma_domain *dma_domain, u32 wnd_nr)
static int update_liodn_stash(int liodn, struct fsl_dma_domain *dma_domain, u32 val)
static int pamu_set_liodn(int liodn, struct device *dev, struct fsl_dma_domain *dma_domain, struct iommu_domain_geometry *geom_attr, u32 win_cnt)
static int check_size(u64 size, dma_addr_t iova)
static struct fsl_dma_domain *iommu_alloc_dma_domain(void)
static void remove_device_ref(struct device_domain_info *info, u32 win_cnt)
static void detach_device(struct device *dev, struct fsl_dma_domain *dma_domain)
static void attach_device(struct fsl_dma_domain *dma_domain, int liodn, struct device *dev)
static phys_addr_t fsl_pamu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
static bool fsl_pamu_capable(enum iommu_cap cap)
static void fsl_pamu_domain_free(struct iommu_domain *domain)
static struct iommu_domain *fsl_pamu_domain_alloc(unsigned type)
static int pamu_set_domain_geometry(struct fsl_dma_domain *dma_domain, struct iommu_domain_geometry *geom_attr, u32 win_cnt)
static int update_domain_stash(struct fsl_dma_domain *dma_domain, u32 val)
static int update_domain_mapping(struct fsl_dma_domain *dma_domain, u32 wnd_nr)
static int disable_domain_win(struct fsl_dma_domain *dma_domain, u32 wnd_nr)
static void fsl_pamu_window_disable(struct iommu_domain *domain, u32 wnd_nr)
static int fsl_pamu_window_enable(struct iommu_domain *domain, u32 wnd_nr, phys_addr_t paddr, u64 size, int prot)
static int handle_attach_device(struct fsl_dma_domain *dma_domain, struct device *dev, const u32 *liodn, int num)
static int fsl_pamu_attach_device(struct iommu_domain *domain, struct device *dev)
static void fsl_pamu_detach_device(struct iommu_domain *domain, struct device *dev)
staticint configure_domain_geometry(struct iommu_domain *domain, void *data)
static int configure_domain_stash(struct fsl_dma_domain *dma_domain, void *data)
static int configure_domain_dma_state(struct fsl_dma_domain *dma_domain, bool enable)
static int fsl_pamu_set_windows(struct iommu_domain *domain, u32 w_count)
static int fsl_pamu_set_domain_attr(struct iommu_domain *domain, enum iommu_attr attr_type, void *data)
static int fsl_pamu_get_domain_attr(struct iommu_domain *domain, enum iommu_attr attr_type, void *data)
static struct iommu_group *get_device_iommu_group(struct device *dev)
staticbool check_pci_ctl_endpt_part(struct pci_controller *pci_ctl)
static struct iommu_group *get_shared_pci_device_group(struct pci_dev *pdev)
static struct iommu_group *get_pci_device_group(struct pci_dev *pdev)
static struct iommu_group *fsl_pamu_device_group(struct device *dev)
static int fsl_pamu_add_device(struct device *dev)
static void fsl_pamu_remove_device(struct device *dev)
int __init pamu_domain_init(void)
\n
     16 struct fsl_dma_domain *dma_domain
     10 struct iommu_domain *domain
     10 struct device *dev
      7 int liodn
      5 u32 wnd_nr
      4 void *data
      3 void
      3 u32 win_cnt
      3 dma_addr_t iova
      2 u64 size
      2 u32 val
      2 struct pci_dev *pdev
      2 struct iommu_domain_geometry *geom_attr
      2 enum iommu_attr attr_type
      1 unsigned type
      1 u32 w_count
      1 struct pci_controller *pci_ctl
      1 struct iommu_domain *dom
      1 struct device_domain_info *info
      1 phys_addr_t paddr
      1 int prot
      1 int num
      1 enum iommu_cap cap
      1 const u32 *liodn
      1 bool enable
