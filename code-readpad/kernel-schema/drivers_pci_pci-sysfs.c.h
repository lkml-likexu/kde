
define pci_config_attr(field, format_string)
\ static ssize_t\ field_show(struct device *dev, struct device_attribute *attr, char *buf)
\ static ssize_t broken_parity_status_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t broken_parity_status_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t pci_dev_show_local_cpu(struct device *dev, bool list, struct device_attribute *attr, char *buf)
static ssize_t local_cpus_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t local_cpulist_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t cpuaffinity_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t cpulistaffinity_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t resource_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t max_link_speed_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t max_link_width_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t current_link_speed_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t current_link_width_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t secondary_bus_number_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t subordinate_bus_number_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t ari_enabled_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t modalias_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t enable_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t enable_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t numa_node_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t numa_node_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t dma_mask_bits_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t consistent_dma_mask_bits_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t msi_bus_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t msi_bus_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t bus_rescan_store(struct bus_type *bus, const char *buf, size_t count)
static ssize_t dev_rescan_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t remove_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t dev_bus_rescan_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t d3cold_allowed_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t d3cold_allowed_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t devspec_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t sriov_totalvfs_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t sriov_numvfs_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t sriov_numvfs_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t sriov_offset_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t sriov_stride_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t sriov_vf_device_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t sriov_drivers_autoprobe_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t sriov_drivers_autoprobe_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t driver_override_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t driver_override_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t boot_vga_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t pci_read_config(struct file *filp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
static ssize_t pci_write_config(struct file *filp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
static ssize_t pci_read_legacy_io(struct file *filp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
static ssize_t pci_write_legacy_io(struct file *filp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
static int pci_mmap_legacy_mem(struct file *filp, struct kobject *kobj, struct bin_attribute *attr, struct vm_area_struct *vma)
static int pci_mmap_legacy_io(struct file *filp, struct kobject *kobj, struct bin_attribute *attr, struct vm_area_struct *vma)
void __weak pci_adjust_legacy_attr(struct pci_bus *b, enum pci_mmap_state mmap_type)
void pci_create_legacy_files(struct pci_bus *b)
void pci_remove_legacy_files(struct pci_bus *b)
int pci_mmap_fits(struct pci_dev *pdev, int resno, struct vm_area_struct *vma, enum pci_mmap_api mmap_api)
static int pci_mmap_resource(struct kobject *kobj, struct bin_attribute *attr, struct vm_area_struct *vma, int write_combine)
static int pci_mmap_resource_uc(struct file *filp, struct kobject *kobj, struct bin_attribute *attr, struct vm_area_struct *vma)
static int pci_mmap_resource_wc(struct file *filp, struct kobject *kobj, struct bin_attribute *attr, struct vm_area_struct *vma)
static ssize_t pci_resource_io(struct file *filp, struct kobject *kobj, struct bin_attribute *attr, char *buf, loff_t off, size_t count, bool write)
static ssize_t pci_read_resource_io(struct file *filp, struct kobject *kobj, struct bin_attribute *attr, char *buf, loff_t off, size_t count)
static ssize_t pci_write_resource_io(struct file *filp, struct kobject *kobj, struct bin_attribute *attr, char *buf, loff_t off, size_t count)
static void pci_remove_resource_files(struct pci_dev *pdev)
static int pci_create_attr(struct pci_dev *pdev, int num, int write_combine)
static int pci_create_resource_files(struct pci_dev *pdev)
static ssize_t pci_write_rom(struct file *filp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
static ssize_t pci_read_rom(struct file *filp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
static ssize_t reset_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static int pci_create_capabilities_sysfs(struct pci_dev *dev)
int __must_check pci_create_sysfs_dev_files(struct pci_dev *pdev)
static void pci_remove_capabilities_sysfs(struct pci_dev *dev)
void pci_remove_sysfs_dev_files(struct pci_dev *pdev)
static int __init pci_sysfs_init(void)
static umode_t pci_dev_attrs_are_visible(struct kobject *kobj, struct attribute *a, int n)
static umode_t pci_dev_hp_attrs_are_visible(struct kobject *kobj, struct attribute *a, int n)
static umode_t pci_bridge_attrs_are_visible(struct kobject *kobj, struct attribute *a, int n)
static umode_t pcie_dev_attrs_are_visible(struct kobject *kobj, struct attribute *a, int n)
static umode_t sriov_attrs_are_visible(struct kobject *kobj, struct attribute *a, int n)
  43 struct device_attribute *attr
  43 struct device *dev
  40 char *buf
  22 size_t count
  19 struct kobject *kobj
  13 struct file *filp
  13 const char *buf
   9 loff_t off
   8 struct bin_attribute *attr
   6 struct vm_area_struct *vma
   6 struct pci_dev *pdev
   6 struct bin_attribute *bin_attr
   5 struct attribute *a
   5 int n
   3 struct pci_bus *b
   2 struct pci_dev *dev
   2 int write_combine
   1 void
   1 struct bus_type *bus
   1 int resno
   1 int num
   1 format_string
   1 field
   1 enum pci_mmap_state mmap_type
   1 enum pci_mmap_api mmap_api
   1 bool write
   1 bool list
