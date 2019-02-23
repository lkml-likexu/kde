
EXPORT_SYMBOL_GPL(pnv_pci_get_slot_id);
EXPORT_SYMBOL_GPL(pnv_pci_get_device_tree);
EXPORT_SYMBOL_GPL(pnv_pci_get_presence_state);
EXPORT_SYMBOL_GPL(pnv_pci_get_power_state);
EXPORT_SYMBOL_GPL(pnv_pci_set_power_state);
EXPORT_SYMBOL_GPL(pnv_pci_set_p2p);
EXPORT_SYMBOL_GPL(pnv_pci_enable_tunnel);
EXPORT_SYMBOL_GPL(pnv_pci_disable_tunnel);
EXPORT_SYMBOL_GPL(pnv_pci_set_tunnel_bar);
EXPORT_SYMBOL_GPL(pnv_pci_get_as_notify_info);
\n
int pnv_pci_get_slot_id(struct device_node *np, uint64_t *id)
int pnv_pci_get_device_tree(uint32_t phandle, void *buf, uint64_t len)
int pnv_pci_get_presence_state(uint64_t id, uint8_t *state)
int pnv_pci_get_power_state(uint64_t id, uint8_t *state)
int pnv_pci_set_power_state(uint64_t id, uint8_t state, struct opal_msg *msg)
int pnv_setup_msi_irqs(struct pci_dev *pdev, int nvec, int type)
void pnv_teardown_msi_irqs(struct pci_dev *pdev)
static void pnv_pci_dump_pest(__be64 pestA[], __be64 pestB[], int pest_size)
static void pnv_pci_dump_p7ioc_diag_data(struct pci_controller *hose, struct OpalIoPhbErrorCommon *common)
static void pnv_pci_dump_phb3_diag_data(struct pci_controller *hose, struct OpalIoPhbErrorCommon *common)
static void pnv_pci_dump_phb4_diag_data(struct pci_controller *hose, struct OpalIoPhbErrorCommon *common)
void pnv_pci_dump_phb_diag_data(struct pci_controller *hose, unsigned char *log_buff)
static void pnv_pci_handle_eeh_config(struct pnv_phb *phb, u32 pe_no)
static void pnv_pci_config_check_eeh(struct pci_dn *pdn)
int pnv_pci_cfg_read(struct pci_dn *pdn, int where, int size, u32 *val)
int pnv_pci_cfg_write(struct pci_dn *pdn, int where, int size, u32 val)
static bool pnv_pci_cfg_check(struct pci_dn *pdn)
return true; } static inline pnv_pci_cfg_check(struct pci_dn *pdn)
static int pnv_pci_read_config(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 *val)
static int pnv_pci_write_config(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 val)
struct iommu_table *pnv_pci_table_alloc(int nid)
void pnv_pci_dma_dev_setup(struct pci_dev *pdev)
void pnv_pci_dma_bus_setup(struct pci_bus *bus)
int pnv_pci_set_p2p(struct pci_dev *initiator, struct pci_dev *target, u64 desc)
struct device_node *pnv_pci_get_phb_node(struct pci_dev *dev)
int pnv_pci_enable_tunnel(struct pci_dev *dev, u64 *asnind)
int pnv_pci_disable_tunnel(struct pci_dev *dev)
int pnv_pci_set_tunnel_bar(struct pci_dev *dev, u64 addr, int enable)
int pnv_pci_get_as_notify_info(struct task_struct *task, u32 *lpid, u32 *pid, u32 *tid)
void pnv_pci_shutdown(void)
static void pnv_p7ioc_rc_quirk(struct pci_dev *dev)
void __init pnv_pci_init(void)
static int pnv_tce_iommu_bus_notifier(struct notifier_block *nb, unsigned long action, void *data)
static int __init pnv_tce_iommu_bus_notifier_init(void)
\n
      5 struct pci_dn *pdn
      5 struct pci_dev *dev
      4 struct pci_controller *hose
      4 int where
      4 int size
      3 void
      3 uint64_t id
      3 struct pci_dev *pdev
      3 struct pci_bus *bus
      3 struct OpalIoPhbErrorCommon *common
      2 unsigned int devfn
      2 uint8_t *state
      2 u32 *val
      2 u32 val
      1 void *data
      1 void *buf
      1 unsigned long action
      1 unsigned char *log_buff
      1 uint8_t state
      1 uint64_t len
      1 uint64_t *id
      1 uint32_t phandle
      1 u64 desc
      1 u64 *asnind
      1 u64 addr
      1 u32 *tid
      1 u32 *pid
      1 u32 pe_no
      1 u32 *lpid
      1 struct task_struct *task
      1 struct pnv_phb *phb
      1 struct pci_dev *target
      1 struct pci_dev *initiator
      1 struct opal_msg *msg
      1 struct notifier_block *nb
      1 struct device_node *np
      1 pnv_pci_set_tunnel_bar
      1 pnv_pci_set_power_state
      1 pnv_pci_set_p2p
      1 pnv_pci_get_slot_id
      1 pnv_pci_get_presence_state
      1 pnv_pci_get_power_state
      1 pnv_pci_get_device_tree
      1 pnv_pci_get_as_notify_info
      1 pnv_pci_enable_tunnel
      1 pnv_pci_disable_tunnel
      1 int type
      1 int pest_size
      1 int nvec
      1 int nid
      1 int enable
      1 __be64 pestB[]
      1 __be64 pestA[]
