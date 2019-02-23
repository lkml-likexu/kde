
\n
void pcibios_name_device(struct pci_dev *dev)
int pseries_send_map_pe(struct pci_dev *pdev, u16 num_vfs, struct pe_map_bar_entry *vf_pe_array)
void pseries_set_pe_num(struct pci_dev *pdev, u16 vf_index, __be16 pe_num)
int pseries_associate_pes(struct pci_dev *pdev, u16 num_vfs)
int pseries_pci_sriov_enable(struct pci_dev *pdev, u16 num_vfs)
int pseries_pcibios_sriov_enable(struct pci_dev *pdev, u16 num_vfs)
int pseries_pcibios_sriov_disable(struct pci_dev *pdev)
static void __init pSeries_request_regions(void)
void __init pSeries_final_fixup(void)
static void fixup_winbond_82c105(struct pci_dev* dev)
int pseries_root_bridge_prepare(struct pci_host_bridge *bridge)
\n
      6 struct pci_dev *pdev
      4 u16 num_vfs
      2 void
      1 u16 vf_index
      1 struct pe_map_bar_entry *vf_pe_array
      1 struct pci_host_bridge *bridge
      1 struct pci_dev* dev
      1 struct pci_dev *dev
      1 __be16 pe_num
