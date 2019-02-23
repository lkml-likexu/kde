
\n
static struct pci_root_info *x86_find_pci_root_info(int bus)
int x86_pci_root_bus_node(int bus)
void x86_pci_root_bus_resources(int bus, struct list_head *resources)
struct pci_root_info __init *alloc_pci_root_info(int bus_min, int bus_max, int node, int link)
void update_res(struct pci_root_info *info, resource_size_t start, resource_size_t end, unsigned long flags, int merge)
\n
      3 int bus
      1 unsigned long flags
      1 struct pci_root_info *info
      1 struct list_head *resources
      1 resource_size_t start
      1 resource_size_t end
      1 int node
      1 int merge
      1 int link
      1 int bus_min
      1 int bus_max
