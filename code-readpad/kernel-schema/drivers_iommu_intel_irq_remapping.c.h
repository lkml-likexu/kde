
\n
static bool ir_pre_enabled(struct intel_iommu *iommu)
static void clear_ir_pre_enabled(struct intel_iommu *iommu)
static void init_ir_status(struct intel_iommu *iommu)
static int alloc_irte(struct intel_iommu *iommu, int irq, struct irq_2_iommu *irq_iommu, u16 count)
static int qi_flush_iec(struct intel_iommu *iommu, int index, int mask)
static int modify_irte(struct irq_2_iommu *irq_iommu, struct irte *irte_modified)
static struct intel_iommu *map_hpet_to_ir(u8 hpet_id)
static struct intel_iommu *map_ioapic_to_ir(int apic)
static struct intel_iommu *map_dev_to_ir(struct pci_dev *dev)
static int clear_entries(struct irq_2_iommu *irq_iommu)
static void set_irte_sid(struct irte *irte, unsigned int svt, unsigned int sq, unsigned int sid)
static int set_ioapic_sid(struct irte *irte, int apic)
static int set_hpet_sid(struct irte *irte, u8 id)
static int set_msi_sid_cb(struct pci_dev *pdev, u16 alias, void *opaque)
static int set_msi_sid(struct irte *irte, struct pci_dev *dev)
static int iommu_load_old_irte(struct intel_iommu *iommu)
static void iommu_set_irq_remapping(struct intel_iommu *iommu, int mode)
static void iommu_enable_irq_remapping(struct intel_iommu *iommu)
static int intel_setup_irq_remapping(struct intel_iommu *iommu)
static void intel_teardown_irq_remapping(struct intel_iommu *iommu)
static void iommu_disable_irq_remapping(struct intel_iommu *iommu)
static int __init dmar_x2apic_optout(void)
static void __init intel_cleanup_irq_remapping(void)
static int __init intel_prepare_irq_remapping(void)
static inline void set_irq_posting_cap(void)
static int __init intel_enable_irq_remapping(void)
static int ir_parse_one_hpet_scope(struct acpi_dmar_device_scope *scope, struct intel_iommu *iommu, struct acpi_dmar_hardware_unit *drhd)
static int ir_parse_one_ioapic_scope(struct acpi_dmar_device_scope *scope, struct intel_iommu *iommu, struct acpi_dmar_hardware_unit *drhd)
static int ir_parse_ioapic_hpet_scope(struct acpi_dmar_header *header, struct intel_iommu *iommu)
static void ir_remove_ioapic_hpet_scope(struct intel_iommu *iommu)
static int __init parse_ioapics_under_ir(void)
static int __init ir_dev_scope_init(void)
static void disable_irq_remapping(void)
static int reenable_irq_remapping(int eim)
static void prepare_irte(struct irte *irte, int vector, unsigned int dest)
static struct irq_domain *intel_get_ir_irq_domain(struct irq_alloc_info *info)
static struct irq_domain *intel_get_irq_domain(struct irq_alloc_info *info)
static void intel_ir_reconfigure_irte(struct irq_data *irqd, bool force)
static int intel_ir_set_affinity(struct irq_data *data, const struct cpumask *mask, bool force)
static void intel_ir_compose_msi_msg(struct irq_data *irq_data, struct msi_msg *msg)
static int intel_ir_set_vcpu_affinity(struct irq_data *data, void *info)
static void intel_irq_remapping_prepare_irte(struct intel_ir_data *data, struct irq_cfg *irq_cfg, struct irq_alloc_info *info, int index, int sub_handle)
static void intel_free_irq_resources(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs)
static int intel_irq_remapping_alloc(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs, void *arg)
static void intel_irq_remapping_free(struct irq_domain *domain, unsigned int virq, unsigned int nr_irqs)
static int intel_irq_remapping_activate(struct irq_domain *domain, struct irq_data *irq_data, bool reserve)
static void intel_irq_remapping_deactivate(struct irq_domain *domain, struct irq_data *irq_data)
static int dmar_ir_add(struct dmar_drhd_unit *dmaru, struct intel_iommu *iommu)
int dmar_ir_hotplug(struct dmar_drhd_unit *dmaru, bool insert)
\n
     16 struct intel_iommu *iommu
      8 void
      5 struct irte *irte
      5 struct irq_domain *domain
      3 unsigned int virq
      3 unsigned int nr_irqs
      3 struct irq_data *irq_data
      3 struct irq_alloc_info *info
      3 struct irq_2_iommu *irq_iommu
      2 struct pci_dev *dev
      2 struct irq_data *data
      2 struct dmar_drhd_unit *dmaru
      2 struct acpi_dmar_hardware_unit *drhd
      2 struct acpi_dmar_device_scope *scope
      2 int index
      2 int apic
      2 bool force
      1 void *opaque
      1 void *info
      1 void *arg
      1 unsigned int svt
      1 unsigned int sq
      1 unsigned int sid
      1 unsigned int dest
      1 u8 id
      1 u8 hpet_id
      1 u16 count
      1 u16 alias
      1 struct pci_dev *pdev
      1 struct msi_msg *msg
      1 struct irte *irte_modified
      1 struct irq_data *irqd
      1 struct irq_cfg *irq_cfg
      1 struct intel_ir_data *data
      1 struct acpi_dmar_header *header
      1 int vector
      1 int sub_handle
      1 int mode
      1 int mask
      1 int irq
      1 int eim
      1 const struct cpumask *mask
      1 bool reserve
      1 bool insert
