
\n
static inline int match_hid_uid(struct device *dev, struct acpihid_map_entry *entry)
static inline u16 get_pci_device_id(struct device *dev)
static inline int get_acpihid_device_id(struct device *dev, struct acpihid_map_entry **entry)
static inline int get_device_id(struct device *dev)
static struct protection_domain *to_pdomain(struct iommu_domain *dom)
static struct dma_ops_domain* to_dma_ops_domain(struct protection_domain *domain)
static struct iommu_dev_data *alloc_dev_data(u16 devid)
static struct iommu_dev_data *search_dev_data(u16 devid)
static int __last_alias(struct pci_dev *pdev, u16 alias, void *data)
static u16 get_alias(struct device *dev)
static struct iommu_dev_data *find_dev_data(u16 devid)
struct iommu_dev_data *get_dev_data(struct device *dev)
static struct iommu_group *acpihid_device_group(struct device *dev)
static bool pci_iommuv2_capable(struct pci_dev *pdev)
static bool pdev_pri_erratum(struct pci_dev *pdev, u32 erratum)
static bool check_device(struct device *dev)
static void init_iommu_group(struct device *dev)
static int iommu_init_device(struct device *dev)
static void iommu_ignore_device(struct device *dev)
static void iommu_uninit_device(struct device *dev)
static void dump_dte_entry(u16 devid)
static void dump_command(unsigned long phys_addr)
static void amd_iommu_report_page_fault(u16 devid, u16 domain_id, u64 address, int flags)
static void iommu_print_event(struct amd_iommu *iommu, void *__evt)
static void iommu_poll_events(struct amd_iommu *iommu)
static void iommu_handle_ppr_entry(struct amd_iommu *iommu, u64 *raw)
static void iommu_poll_ppr_log(struct amd_iommu *iommu)
int amd_iommu_register_ga_log_notifier(int (*notifier)
(u32)
)
static void iommu_poll_ga_log(struct amd_iommu *iommu)
irqreturn_t amd_iommu_int_thread(int irq, void *data)
irqreturn_t amd_iommu_int_handler(int irq, void *data)
static int wait_on_sem(volatile u64 *sem)
static void copy_cmd_to_buffer(struct amd_iommu *iommu, struct iommu_cmd *cmd)
static void build_completion_wait(struct iommu_cmd *cmd, u64 address)
static void build_inv_dte(struct iommu_cmd *cmd, u16 devid)
static void build_inv_iommu_pages(struct iommu_cmd *cmd, u64 address, size_t size, u16 domid, int pde)
static void build_inv_iotlb_pages(struct iommu_cmd *cmd, u16 devid, int qdep, u64 address, size_t size)
static void build_inv_iommu_pasid(struct iommu_cmd *cmd, u16 domid, int pasid, u64 address, bool size)
static void build_inv_iotlb_pasid(struct iommu_cmd *cmd, u16 devid, int pasid, int qdep, u64 address, bool size)
static void build_complete_ppr(struct iommu_cmd *cmd, u16 devid, int pasid, int status, int tag, bool gn)
static void build_inv_all(struct iommu_cmd *cmd)
static void build_inv_irt(struct iommu_cmd *cmd, u16 devid)
static int __iommu_queue_command_sync(struct amd_iommu *iommu, struct iommu_cmd *cmd, bool sync)
static int iommu_queue_command_sync(struct amd_iommu *iommu, struct iommu_cmd *cmd, bool sync)
static int iommu_queue_command(struct amd_iommu *iommu, struct iommu_cmd *cmd)
static int iommu_completion_wait(struct amd_iommu *iommu)
static int iommu_flush_dte(struct amd_iommu *iommu, u16 devid)
static void amd_iommu_flush_dte_all(struct amd_iommu *iommu)
static void amd_iommu_flush_tlb_all(struct amd_iommu *iommu)
static void amd_iommu_flush_all(struct amd_iommu *iommu)
static void iommu_flush_irt(struct amd_iommu *iommu, u16 devid)
static void amd_iommu_flush_irt_all(struct amd_iommu *iommu)
void iommu_flush_all_caches(struct amd_iommu *iommu)
static int device_flush_iotlb(struct iommu_dev_data *dev_data, u64 address, size_t size)
static int device_flush_dte(struct iommu_dev_data *dev_data)
static void __domain_flush_pages(struct protection_domain *domain, u64 address, size_t size, int pde)
static void domain_flush_pages(struct protection_domain *domain, u64 address, size_t size)
static void domain_flush_tlb(struct protection_domain *domain)
static void domain_flush_tlb_pde(struct protection_domain *domain)
static void domain_flush_complete(struct protection_domain *domain)
static void domain_flush_devices(struct protection_domain *domain)
static void free_page_list(struct page *freelist)
static struct page *free_pt_page(unsigned long pt, struct page *freelist)
define DEFINE_FREE_PT_FN(LVL, FN)
\ static struct page *free_pt_LVL (unsigned long __pt, struct page *freelist)
\ static struct page *free_sub_pt(unsigned long root, int mode, struct page *freelist)
static void free_pagetable(struct protection_domain *domain)
static bool increase_address_space(struct protection_domain *domain, gfp_t gfp)
static u64 *alloc_pte(struct protection_domain *domain, unsigned long address, unsigned long page_size, u64 **pte_page, gfp_t gfp)
static u64 *fetch_pte(struct protection_domain *domain, unsigned long address, unsigned long *page_size)
static struct page *free_clear_pte(u64 *pte, u64 pteval, struct page *freelist)
static int iommu_map_page(struct protection_domain *dom, unsigned long bus_addr, unsigned long phys_addr, unsigned long page_size, int prot, gfp_t gfp)
static unsigned long iommu_unmap_page(struct protection_domain *dom, unsigned long bus_addr, unsigned long page_size)
static unsigned long dma_ops_alloc_iova(struct device *dev, struct dma_ops_domain *dma_dom, unsigned int pages, u64 dma_mask)
static void dma_ops_free_iova(struct dma_ops_domain *dma_dom, unsigned long address, unsigned int pages)
static void add_domain_to_list(struct protection_domain *domain)
static void del_domain_from_list(struct protection_domain *domain)
static u16 domain_id_alloc(void)
static void domain_id_free(int id)
static void free_gcr3_tbl_level1(u64 *tbl)
static void free_gcr3_tbl_level2(u64 *tbl)
static void free_gcr3_table(struct protection_domain *domain)
static void dma_ops_domain_flush_tlb(struct dma_ops_domain *dom)
static void iova_domain_flush_tlb(struct iova_domain *iovad)
static void dma_ops_domain_free(struct dma_ops_domain *dom)
static struct dma_ops_domain *dma_ops_domain_alloc(void)
static bool dma_ops_domain(struct protection_domain *domain)
static void set_dte_entry(u16 devid, struct protection_domain *domain, bool ats, bool ppr)
static void clear_dte_entry(u16 devid)
static void do_attach(struct iommu_dev_data *dev_data, struct protection_domain *domain)
static void do_detach(struct iommu_dev_data *dev_data)
static int __attach_device(struct iommu_dev_data *dev_data, struct protection_domain *domain)
static void pdev_iommuv2_disable(struct pci_dev *pdev)
static int pri_reset_while_enabled(struct pci_dev *pdev)
static int pdev_iommuv2_enable(struct pci_dev *pdev)
static bool pci_pri_tlp_required(struct pci_dev *pdev)
static int attach_device(struct device *dev, struct protection_domain *domain)
static void __detach_device(struct iommu_dev_data *dev_data)
static void detach_device(struct device *dev)
static int amd_iommu_add_device(struct device *dev)
static void amd_iommu_remove_device(struct device *dev)
static struct iommu_group *amd_iommu_device_group(struct device *dev)
static struct protection_domain *get_domain(struct device *dev)
static void update_device_table(struct protection_domain *domain)
static void update_domain(struct protection_domain *domain)
static int dir2prot(enum dma_data_direction direction)
static dma_addr_t __map_single(struct device *dev, struct dma_ops_domain *dma_dom, phys_addr_t paddr, size_t size, enum dma_data_direction direction, u64 dma_mask)
static void __unmap_single(struct dma_ops_domain *dma_dom, dma_addr_t dma_addr, size_t size, int dir)
static dma_addr_t map_page(struct device *dev, struct page *page, unsigned long offset, size_t size, enum dma_data_direction dir, unsigned long attrs)
static void unmap_page(struct device *dev, dma_addr_t dma_addr, size_t size, enum dma_data_direction dir, unsigned long attrs)
static int sg_num_pages(struct device *dev, struct scatterlist *sglist, int nelems)
static int map_sg(struct device *dev, struct scatterlist *sglist, int nelems, enum dma_data_direction direction, unsigned long attrs)
static void unmap_sg(struct device *dev, struct scatterlist *sglist, int nelems, enum dma_data_direction dir, unsigned long attrs)
static void *alloc_coherent(struct device *dev, size_t size, dma_addr_t *dma_addr, gfp_t flag, unsigned long attrs)
static void free_coherent(struct device *dev, size_t size, void *virt_addr, dma_addr_t dma_addr, unsigned long attrs)
static int amd_iommu_dma_supported(struct device *dev, u64 mask)
static int init_reserved_iova_ranges(void)
int __init amd_iommu_init_api(void)
int __init amd_iommu_init_dma_ops(void)
static void cleanup_domain(struct protection_domain *domain)
static void protection_domain_free(struct protection_domain *domain)
static int protection_domain_init(struct protection_domain *domain)
static struct protection_domain *protection_domain_alloc(void)
static struct iommu_domain *amd_iommu_domain_alloc(unsigned type)
static void amd_iommu_domain_free(struct iommu_domain *dom)
static void amd_iommu_detach_device(struct iommu_domain *dom, struct device *dev)
static int amd_iommu_attach_device(struct iommu_domain *dom, struct device *dev)
static int amd_iommu_map(struct iommu_domain *dom, unsigned long iova, phys_addr_t paddr, size_t page_size, int iommu_prot)
static size_t amd_iommu_unmap(struct iommu_domain *dom, unsigned long iova, size_t page_size)
static phys_addr_t amd_iommu_iova_to_phys(struct iommu_domain *dom, dma_addr_t iova)
static bool amd_iommu_capable(enum iommu_cap cap)
static void amd_iommu_get_resv_regions(struct device *dev, struct list_head *head)
static void amd_iommu_put_resv_regions(struct device *dev, struct list_head *head)
static void amd_iommu_apply_resv_region(struct device *dev, struct iommu_domain *domain, struct iommu_resv_region *region)
static bool amd_iommu_is_attach_deferred(struct iommu_domain *domain, struct device *dev)
static void amd_iommu_flush_iotlb_all(struct iommu_domain *domain)
static void amd_iommu_iotlb_range_add(struct iommu_domain *domain, unsigned long iova, size_t size)
int amd_iommu_register_ppr_notifier(struct notifier_block *nb)
int amd_iommu_unregister_ppr_notifier(struct notifier_block *nb)
void amd_iommu_domain_direct_map(struct iommu_domain *dom)
int amd_iommu_domain_enable_v2(struct iommu_domain *dom, int pasids)
static int __flush_pasid(struct protection_domain *domain, int pasid, u64 address, bool size)
static int __amd_iommu_flush_page(struct protection_domain *domain, int pasid, u64 address)
int amd_iommu_flush_page(struct iommu_domain *dom, int pasid, u64 address)
static int __amd_iommu_flush_tlb(struct protection_domain *domain, int pasid)
int amd_iommu_flush_tlb(struct iommu_domain *dom, int pasid)
static u64 *__get_gcr3_pte(u64 *root, int level, int pasid, bool alloc)
static int __set_gcr3(struct protection_domain *domain, int pasid, unsigned long cr3)
static int __clear_gcr3(struct protection_domain *domain, int pasid)
int amd_iommu_domain_set_gcr3(struct iommu_domain *dom, int pasid, unsigned long cr3)
int amd_iommu_domain_clear_gcr3(struct iommu_domain *dom, int pasid)
int amd_iommu_complete_ppr(struct pci_dev *pdev, int pasid, int status, int tag)
struct iommu_domain *amd_iommu_get_v2_domain(struct pci_dev *pdev)
void amd_iommu_enable_device_erratum(struct pci_dev *pdev, u32 erratum)
int amd_iommu_device_info(struct pci_dev *pdev, struct amd_iommu_device_info *info)
static void set_dte_irq_entry(u16 devid, struct irq_remap_table *table)
static struct irq_remap_table *get_irq_table(u16 devid)
static struct irq_remap_table *__alloc_irq_table(void)
static void set_remap_table_entry(struct amd_iommu *iommu, u16 devid, struct irq_remap_table *table)
static struct irq_remap_table *alloc_irq_table(u16 devid)
static int alloc_irq_index(u16 devid, int count, bool align)
static int modify_irte_ga(u16 devid, int index, struct irte_ga *irte, struct amd_ir_data *data)
static int modify_irte(u16 devid, int index, union irte *irte)
static void free_irte(u16 devid, int index)
static void irte_prepare(void *entry, u32 delivery_mode, u32 dest_mode, u8 vector, u32 dest_apicid, int devid)
static void irte_ga_prepare(void *entry, u32 delivery_mode, u32 dest_mode, u8 vector, u32 dest_apicid, int devid)
static void irte_activate(void *entry, u16 devid, u16 index)
static void irte_ga_activate(void *entry, u16 devid, u16 index)
static void irte_deactivate(void *entry, u16 devid, u16 index)
static void irte_ga_deactivate(void *entry, u16 devid, u16 index)
static void irte_set_affinity(void *entry, u16 devid, u16 index, u8 vector, u32 dest_apicid)
static void irte_ga_set_affinity(void *entry, u16 devid, u16 index, u8 vector, u32 dest_apicid)
define IRTE_ALLOCATED (~1U)
static void irte_set_allocated(struct irq_remap_table *table, int index)
static void irte_ga_set_allocated(struct irq_remap_table *table, int index)
static bool irte_is_allocated(struct irq_remap_table *table, int index)
static bool irte_ga_is_allocated(struct irq_remap_table *table, int index)
static void irte_clear_allocated(struct irq_remap_table *table, int index)
static void irte_ga_clear_allocated(struct irq_remap_table *table, int index)
static int get_devid(struct irq_alloc_info *info)
static struct irq_domain *get_ir_irq_domain(struct irq_alloc_info *info)
static struct irq_domain *get_irq_domain(struct irq_alloc_info *info)
static void irq_remapping_prepare_irte(struct amd_ir_data *data, struct irq_cfg *irq_cfg, struct irq_alloc_info *info, int devid, int index, int sub_handle)
static int irq_remapping_alloc(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs, void *arg)
static void irq_remapping_free(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs)
static int irq_remapping_activate(struct irq_domain *domain, struct irq_data *irq_data, bool reserve)
static void irq_remapping_deactivate(struct irq_domain *domain, struct irq_data *irq_data)
static int amd_ir_set_vcpu_affinity(struct irq_data *data, void *vcpu_info)
static void amd_ir_update_irte(struct irq_data *irqd, struct amd_iommu *iommu, struct amd_ir_data *ir_data, struct irq_2_irte *irte_info, struct irq_cfg *cfg)
static int amd_ir_set_affinity(struct irq_data *data, const struct cpumask *mask, bool force)
static void ir_compose_msi_msg(struct irq_data *irq_data, struct msi_msg *msg)
int amd_iommu_create_irq_domain(struct amd_iommu *iommu)
int amd_iommu_update_ga(int cpu, bool is_run, void *data)
\n
     34 struct device *dev
     29 struct protection_domain *domain
     28 u16 devid
     20 struct amd_iommu *iommu
     14 int pasid
     13 struct iommu_domain *dom
     13 struct iommu_cmd *cmd
     12 u64 address
     12 size_t size
     11 struct pci_dev *pdev
     10 int index
      8 void *entry
      8 struct irq_remap_table *table
      7 void
      6 unsigned long attrs
      6 u16 index
      6 struct iommu_dev_data *dev_data
      5 struct page *freelist
      4 void *data
      4 u8 vector
      4 u32 dest_apicid
      4 struct irq_domain *domain
      4 struct irq_alloc_info *info
      4 struct iommu_domain *domain
      4 struct dma_ops_domain *dma_dom
      3 unsigned long page_size
      3 unsigned long iova
      3 unsigned long address
      3 struct scatterlist *sglist
      3 struct irq_data *irq_data
      3 int nelems
      3 int devid
      3 gfp_t gfp
      3 enum dma_data_direction direction
      3 enum dma_data_direction dir
      3 dma_addr_t dma_addr
      3 bool size
      2 unsigned long phys_addr
      2 unsigned long cr3
      2 unsigned long bus_addr
      2 unsigned int virq
      2 unsigned int pages
      2 unsigned int nr_irqs
      2 u64 *tbl
      2 u64 dma_mask
      2 u32 erratum
      2 u32 dest_mode
      2 u32 delivery_mode
      2 u16 domid
      2 struct protection_domain *dom
      2 struct notifier_block *nb
      2 struct list_head *head
      2 struct irq_data *data
      2 struct dma_ops_domain *dom
      2 struct amd_ir_data *data
      2 size_t page_size
      2 phys_addr_t paddr
      2 int tag
      2 int status
      2 int qdep
      2 int pde
      2 int irq
      2 bool sync
      1 volatile u64 *sem
      1 void *virt_addr
      1 void *vcpu_info
      1 void *__evt
      1 void *arg
      1 unsigned type
      1 unsigned long root
      1 unsigned long __pt
      1 unsigned long pt
      1 unsigned long *page_size
      1 unsigned long offset
      1 union irte *irte
      1 u64 *root
      1 u64 *raw
      1 u64 pteval
      1 u64 **pte_page
      1 u64 *pte
      1 u64 mask
      1 u32
      1 u16 domain_id
      1 u16 alias
      1 struct page *page
      1 struct msi_msg *msg
      1 struct irte_ga *irte
      1 struct irq_data *irqd
      1 struct irq_cfg *irq_cfg
      1 struct irq_cfg *cfg
      1 struct irq_2_irte *irte_info
      1 struct iova_domain *iovad
      1 struct iommu_resv_region *region
      1 struct amd_ir_data *ir_data
      1 struct amd_iommu_device_info *info
      1 struct acpihid_map_entry **entry
      1 struct acpihid_map_entry *entry
      1 LVL
      1 int sub_handle
      1 int prot
      1 int pasids
      1 int *notifier
      1 int mode
      1 int level
      1 int iommu_prot
      1 int id
      1 int flags
      1 int dir
      1 int cpu
      1 int count
      1 gfp_t flag
      1 FN
      1 enum iommu_cap cap
      1 dma_addr_t iova
      1 dma_addr_t *dma_addr
      1 const struct cpumask *mask
      1 bool reserve
      1 bool ppr
      1 bool is_run
      1 bool gn
      1 bool force
      1 bool ats
      1 bool alloc
      1 bool align
      1 ~1U
