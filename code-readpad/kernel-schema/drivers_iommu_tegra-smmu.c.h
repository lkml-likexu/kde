
static struct tegra_smmu_as *to_smmu_as(struct iommu_domain *dom)
static inline void smmu_writel(struct tegra_smmu *smmu, u32 value, unsigned long offset)
static inline u32 smmu_readl(struct tegra_smmu *smmu, unsigned long offset)
static unsigned int iova_pd_index(unsigned long iova)
static unsigned int iova_pt_index(unsigned long iova)
static bool smmu_dma_addr_valid(struct tegra_smmu *smmu, dma_addr_t addr)
static dma_addr_t smmu_pde_to_dma(u32 pde)
static void smmu_flush_ptc_all(struct tegra_smmu *smmu)
static inline void smmu_flush_ptc(struct tegra_smmu *smmu, dma_addr_t dma, unsigned long offset)
static inline void smmu_flush_tlb(struct tegra_smmu *smmu)
static inline void smmu_flush_tlb_asid(struct tegra_smmu *smmu, unsigned long asid)
static inline void smmu_flush_tlb_section(struct tegra_smmu *smmu, unsigned long asid, unsigned long iova)
static inline void smmu_flush_tlb_group(struct tegra_smmu *smmu, unsigned long asid, unsigned long iova)
static inline void smmu_flush(struct tegra_smmu *smmu)
static int tegra_smmu_alloc_asid(struct tegra_smmu *smmu, unsigned int *idp)
static void tegra_smmu_free_asid(struct tegra_smmu *smmu, unsigned int id)
static bool tegra_smmu_capable(enum iommu_cap cap)
static struct iommu_domain *tegra_smmu_domain_alloc(unsigned type)
static void tegra_smmu_domain_free(struct iommu_domain *domain)
static const struct tegra_smmu_swgroup * tegra_smmu_find_swgroup(struct tegra_smmu *smmu, unsigned int swgroup)
static void tegra_smmu_enable(struct tegra_smmu *smmu, unsigned int swgroup, unsigned int asid)
static void tegra_smmu_disable(struct tegra_smmu *smmu, unsigned int swgroup, unsigned int asid)
static int tegra_smmu_as_prepare(struct tegra_smmu *smmu, struct tegra_smmu_as *as)
static void tegra_smmu_as_unprepare(struct tegra_smmu *smmu, struct tegra_smmu_as *as)
static int tegra_smmu_attach_dev(struct iommu_domain *domain, struct device *dev)
static void tegra_smmu_detach_dev(struct iommu_domain *domain, struct device *dev)
static void tegra_smmu_set_pde(struct tegra_smmu_as *as, unsigned long iova, u32 value)
static u32 *tegra_smmu_pte_offset(struct page *pt_page, unsigned long iova)
static u32 *tegra_smmu_pte_lookup(struct tegra_smmu_as *as, unsigned long iova, dma_addr_t *dmap)
static u32 *as_get_pte(struct tegra_smmu_as *as, dma_addr_t iova, dma_addr_t *dmap)
static void tegra_smmu_pte_get_use(struct tegra_smmu_as *as, unsigned long iova)
static void tegra_smmu_pte_put_use(struct tegra_smmu_as *as, unsigned long iova)
static void tegra_smmu_set_pte(struct tegra_smmu_as *as, unsigned long iova, u32 *pte, dma_addr_t pte_dma, u32 val)
static int tegra_smmu_map(struct iommu_domain *domain, unsigned long iova, phys_addr_t paddr, size_t size, int prot)
static size_t tegra_smmu_unmap(struct iommu_domain *domain, unsigned long iova, size_t size)
static phys_addr_t tegra_smmu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
static struct tegra_smmu *tegra_smmu_find(struct device_node *np)
static int tegra_smmu_configure(struct tegra_smmu *smmu, struct device *dev, struct of_phandle_args *args)
static int tegra_smmu_add_device(struct device *dev)
static void tegra_smmu_remove_device(struct device *dev)
static const struct tegra_smmu_group_soc * tegra_smmu_find_group(struct tegra_smmu *smmu, unsigned int swgroup)
static struct iommu_group *tegra_smmu_group_get(struct tegra_smmu *smmu, unsigned int swgroup)
static struct iommu_group *tegra_smmu_device_group(struct device *dev)
static int tegra_smmu_of_xlate(struct device *dev, struct of_phandle_args *args)
static void tegra_smmu_ahb_enable(void)
static int tegra_smmu_swgroups_show(struct seq_file *s, void *data)
static int tegra_smmu_swgroups_open(struct inode *inode, struct file *file)
static int tegra_smmu_clients_show(struct seq_file *s, void *data)
static int tegra_smmu_clients_open(struct inode *inode, struct file *file)
static void tegra_smmu_debugfs_init(struct tegra_smmu *smmu)
static void tegra_smmu_debugfs_exit(struct tegra_smmu *smmu)
struct tegra_smmu *tegra_smmu_probe(struct device *dev, const struct tegra_smmu_soc *soc, struct tegra_mc *mc)
void tegra_smmu_remove(struct tegra_smmu *smmu)
  23 struct tegra_smmu *smmu
  12 unsigned long iova
   8 struct tegra_smmu_as *as
   8 struct device *dev
   6 struct iommu_domain *domain
   5 unsigned int swgroup
   3 unsigned long offset
   3 unsigned long asid
   2 void *data
   2 unsigned int asid
   2 u32 value
   2 struct seq_file *s
   2 struct of_phandle_args *args
   2 struct inode *inode
   2 struct file *file
   2 size_t size
   2 dma_addr_t iova
   2 dma_addr_t *dmap
   1 void
   1 unsigned type
   1 unsigned int id
   1 unsigned int *idp
   1 u32 val
   1 u32 pde
   1 u32 *pte
   1 struct tegra_mc *mc
   1 struct page *pt_page
   1 struct iommu_domain *dom
   1 struct device_node *np
   1 phys_addr_t paddr
   1 int prot
   1 enum iommu_cap cap
   1 dma_addr_t pte_dma
   1 dma_addr_t dma
   1 dma_addr_t addr
   1 const struct tegra_smmu_soc *soc
