
static int uncore_pcibus_to_physid(struct pci_bus *bus)
static void uncore_free_pcibus_map(void)
struct pci2phy_map *__find_pci2phy_map(int segment)
ssize_t uncore_event_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
struct intel_uncore_box *uncore_pmu_to_box(struct intel_uncore_pmu *pmu, int cpu)
u64 uncore_msr_read_counter(struct intel_uncore_box *box, struct perf_event *event)
struct event_constraint * uncore_get_constraint(struct intel_uncore_box *box, struct perf_event *event)
void uncore_put_constraint(struct intel_uncore_box *box, struct perf_event *event)
u64 uncore_shared_reg_config(struct intel_uncore_box *box, int idx)
static void uncore_assign_hw_event(struct intel_uncore_box *box, struct perf_event *event, int idx)
void uncore_perf_event_update(struct intel_uncore_box *box, struct perf_event *event)
static enum hrtimer_restart uncore_pmu_hrtimer(struct hrtimer *hrtimer)
void uncore_pmu_start_hrtimer(struct intel_uncore_box *box)
void uncore_pmu_cancel_hrtimer(struct intel_uncore_box *box)
static void uncore_pmu_init_hrtimer(struct intel_uncore_box *box)
static struct intel_uncore_box *uncore_alloc_box(struct intel_uncore_type *type, int node)
static bool is_box_event(struct intel_uncore_box *box, struct perf_event *event)
static int uncore_collect_events(struct intel_uncore_box *box, struct perf_event *leader, bool dogrp)
static struct event_constraint * uncore_get_event_constraint(struct intel_uncore_box *box, struct perf_event *event)
static void uncore_put_event_constraint(struct intel_uncore_box *box, struct perf_event *event)
static int uncore_assign_events(struct intel_uncore_box *box, int assign[], int n)
void uncore_pmu_event_start(struct perf_event *event, int flags)
void uncore_pmu_event_stop(struct perf_event *event, int flags)
int uncore_pmu_event_add(struct perf_event *event, int flags)
void uncore_pmu_event_del(struct perf_event *event, int flags)
void uncore_pmu_event_read(struct perf_event *event)
static int uncore_validate_group(struct intel_uncore_pmu *pmu, struct perf_event *event)
static int uncore_pmu_event_init(struct perf_event *event)
static ssize_t uncore_get_attr_cpumask(struct device *dev, struct device_attribute *attr, char *buf)
static int uncore_pmu_register(struct intel_uncore_pmu *pmu)
static void uncore_pmu_unregister(struct intel_uncore_pmu *pmu)
static void uncore_free_boxes(struct intel_uncore_pmu *pmu)
static void uncore_type_exit(struct intel_uncore_type *type)
static void uncore_types_exit(struct intel_uncore_type **types)
static int __init uncore_type_init(struct intel_uncore_type *type, bool setid)
static int __init uncore_types_init(struct intel_uncore_type **types, bool setid)
static int uncore_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
static void uncore_pci_remove(struct pci_dev *pdev)
static int __init uncore_pci_init(void)
static void uncore_pci_exit(void)
static void uncore_change_type_ctx(struct intel_uncore_type *type, int old_cpu, int new_cpu)
static void uncore_change_context(struct intel_uncore_type **uncores, int old_cpu, int new_cpu)
static int uncore_event_cpu_offline(unsigned int cpu)
static int allocate_boxes(struct intel_uncore_type **types, unsigned int pkg, unsigned int cpu)
static int uncore_event_cpu_online(unsigned int cpu)
static int __init type_pmu_register(struct intel_uncore_type *type)
static int __init uncore_msr_pmus_register(void)
static int __init uncore_cpu_init(void)
static int __init intel_uncore_init(void)
static void __exit intel_uncore_exit(void)
  15 struct perf_event *event
  14 struct intel_uncore_box *box
   7 void
   5 struct intel_uncore_type *type
   5 struct intel_uncore_pmu *pmu
   4 int flags
   3 unsigned int cpu
   3 struct intel_uncore_type **types
   2 struct pci_dev *pdev
   2 int old_cpu
   2 int new_cpu
   2 int idx
   2 char *buf
   2 bool setid
   1 unsigned int pkg
   1 struct perf_event *leader
   1 struct pci_bus *bus
   1 struct kobject *kobj
   1 struct kobj_attribute *attr
   1 struct intel_uncore_type **uncores
   1 struct hrtimer *hrtimer
   1 struct device_attribute *attr
   1 struct device *dev
   1 int segment
   1 int node
   1 int n
   1 int cpu
   1 int assign[]
   1 const struct pci_device_id *id
   1 bool dogrp
