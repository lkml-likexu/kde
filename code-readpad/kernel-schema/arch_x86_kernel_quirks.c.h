
\n
static void quirk_intel_irqbalance(struct pci_dev *dev)
static void ich_force_hpet_resume(void)
static void ich_force_enable_hpet(struct pci_dev *dev)
static void hpet_print_force_info(void)
static void old_ich_force_hpet_resume(void)
static void old_ich_force_enable_hpet(struct pci_dev *dev)
static void old_ich_force_enable_hpet_user(struct pci_dev *dev)
static void vt8237_force_hpet_resume(void)
static void vt8237_force_enable_hpet(struct pci_dev *dev)
static void ati_force_hpet_resume(void)
static u32 ati_ixp4x0_rev(struct pci_dev *dev)
static void ati_force_enable_hpet(struct pci_dev *dev)
static void nvidia_force_hpet_resume(void)
static void nvidia_force_enable_hpet(struct pci_dev *dev)
void force_hpet_resume(void)
static void e6xx_force_enable_hpet(struct pci_dev *dev)
static void force_disable_hpet_msi(struct pci_dev *unused)
static void quirk_amd_nb_node(struct pci_dev *dev)
static void amd_disable_seq_and_redirect_scrub(struct pci_dev *dev)
static void quirk_intel_brickland_xeon_ras_cap(struct pci_dev *pdev)
static void quirk_intel_purley_xeon_ras_cap(struct pci_dev *pdev)
void __init early_platform_quirks(void)
\n
     11 struct pci_dev *dev
      8 void
      2 struct pci_dev *pdev
      1 struct pci_dev *unused
